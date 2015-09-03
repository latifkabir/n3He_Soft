"""
n3he.py: a PyROOT interface to the n3He data stream
Rob Mahurin 2015-08-22

You'll need at a minimum:
    * ROOT compiled with python support
    * working libn3He.so
    * python access to ROOT.py, perhaps by running
        source $(root-config --prefix)/bin/thisroot.sh
      in your shell
    * numerical python (numpy)

You'll probably want ipython, matplotlib, python-scipy.  If a script
doesn't run under the standard python shell, try using
    ipython --pylab=auto -i scriptname.py

Two classes included here:

    * ADC: data from a single adc is stored in a single numpy array,
      which can be set as a branch address using .attach(tree,branch)
      and filled with tree.GetEntry(entry).  Accessor functions let
      you slice out the header, each data channel, and each time bin.

    * DAQ: a python dictionary containing five ADCs with appropriate
      sizes and similar accessor functions.
"""

import numpy
import ROOT
ROOT.gSystem.Load("libn3He.so")
from ROOT import TTreeRaw

class ADC:
    """Data from an n-3He analog-to-digital converter."""

    ## self.shape will be drawn from this dictionary, which can be
    ## expanded if the DAQ is modified for special runs.  The code
    ## currently assumes that the number of integers in the header is
    ## the same as the number of channels.
    ##
    ## I'm currently guessing about the tbins_total (the number of
    ## time bins there would be if the DAQ ran at the same frequency
    ## without deadtime).
    _shape = {
        'clean': {
            ## This corresponds to the leaf description "h[48]/I:d[49][48]/I"
            'channels':     48,
            'tbins':        49,
            'tbins_total':  53,
            'dtype':        numpy.int32,
            },
        'dirty': {
            ## This corresponds to the leaf description "h[2]/I:d[1624][2]/I"
            'channels':     2,
            'tbins':        1624,
            'tbins_total':  1650,
            'dtype':        numpy.int32,
            },
    }

    def __init__( self,
                  which=None,
                  tree=None, branch=None,
                  copy_of=None,
                  dtype=numpy.int32,
                  ):
        if copy_of:
            ## note that copied data isn't checked for sizes
            ## consistency and isn't automatically attached to trees
            self.which = copy_of.which
            self.buffer = copy_of.buffer.copy()
            return

        self.which = which
        try:
            self.shape = self._shape[which]
        except KeyError:
            raise KeyError("Argument 'which' must be one of ",
                           self._shape.keys() )

        self.buffer = numpy.ndarray(
            shape=(
                self.shape['tbins'] + 1,
                self.shape['channels'],
                ),
            dtype=dtype,
            order="C",
            )

        if tree and branch:
            self.attach(tree, branch)

    def header(self):
        "Return the header vector for the ADC"
        # The header is the first row of the data buffer
        return self.buffer[0,:].squeeze()

    def channel(self,n):
        "Return the time data for the n-th ADC channel"
        return self.buffer[1:,n].squeeze()

    def tbin(self, n):
        "Return the data from all channels for the n-th time bin"
        return self.buffer[ 1+n, :].squeeze()

    def attach(self, tree, branch):
        "Enable filling of this object with tree.GetEntry(entry)"
        if self.buffer.dtype != self.shape['dtype']:
            ## The variable type matters here; don't get it wrong
            raise TypeError(
                "Wrong dtype '{}'; please expand ADC._shape if necessary"
                .format( self.buffer.dtype ),
                )
        self.tree = tree
        self.branch = branch
        tree.SetBranchAddress( branch, self.buffer )

    def __call__ (self, n):
        "Function-like access to .channel()"
        return self.channel(n)

class DAQ (dict):
    "Store data from all five ADCs for one neutron pulse"

    def __init__(self,
                 run=None,
                 tree=None,
                 copy_of=None,
                 dtype=numpy.int32,
                 ):
        if copy_of:
            ## Note that copied data isn't automatically attached to trees
            for adc in copy_of:
                self[adc] = ADC( copy_of= copy_of[adc] )
            return

        for adc in [21,22,23,24]:
            self[adc]  = ADC(which='clean', dtype=dtype)
        self[30]       = ADC(which='dirty', dtype=dtype)

        ## Does you no good to specify both "run" and "tree"
        if run:
            tree = TTreeRaw(run)

        if tree:
            self.attach(tree)

    def header  (self,adc):
        "Wrapper for ADC.header()"
        return self[adc].header()

    def channel (self,adc,n):
        "Wrapper for ADC.channel()"
        return self[adc].channel(n)

    def tbin    (self,adc,n):
        "Wrapper for ADC.tbin()"
        return self[adc].tbin(n)

    def attach  (self,tree):
        """Enable filling of this object with tree.GetEntry(entry)
        or self.GetEntry(entry)"""
        self.tree = tree
        for adc in self.keys():
            self[adc].attach(tree,"b{}".format(adc))

    def GetEntry (self, entry=0, getall=0):
        "If there is an associated tree, get the requested entry."
        # Will raise an AttributeError is there's no tree
        self.tree.GetEntry( entry, getall )

    ## This information is taken from Irakli via Noah
    daq_map_id = [  21,23, 21,23, 21,23, 21,23,
                    22,24, 22,24, 22,24, 22,24, ]
    active_channel_id = numpy.array(
        [
            [0,1,2,3,4,5,6,7,8],
            [0,1,2,3,4,5,6,7,8],
            [9,10,11,12,13,14,15,16,17],
            [9,10,11,12,13,14,15,16,17],
            [24,25,26,27,28,29,30,31,32],
            [24,25,26,27,28,29,30,31,32],
            [33,34,35,36,37,38,39,40,41],
            [33,34,35,36,37,38,39,40,41],
            [0,1,2,3,4,5,6,7,8],
            [0,1,2,3,4,5,6,7,8],
            [9,10,11,12,13,14,15,16,17],
            [9,10,11,12,13,14,15,16,17],
            [24,25,26,27,28,29,30,31,32],
            [24,25,26,27,28,29,30,31,32],
            [33,34,35,36,37,38,39,40,41],
            [33,34,35,36,37,38,39,40,41],
        ], dtype=int,
        )

    def pw (self, plane, wire):
        """Return the adc and channel corresponding
        to the requested plane and wire"""
        adc = self.daq_map_id[plane]
        ch  = self.active_channel_id[plane,wire]
        return adc,ch

    def __call__(self, plane, wire):
        """Return all time bins of the signal from
        the requested plane and wire in the target chamber"""
        return self.channel( *self.pw( plane, wire ) )

## time bins for each ADC.which that go from zero to one, with a
## reasonable gap for data transfer time.
##
## Auxiliary variable names have underscores so they won't get exported
tbins = dict()
for _name, _shape in ADC._shape.iteritems():
    tbins[_name] = 1.0 * numpy.arange(_shape['tbins']) / _shape['tbins_total']
