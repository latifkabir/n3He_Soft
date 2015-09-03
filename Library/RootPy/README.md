ROOT-Python interface for n3He data
========================

rsm, 2015-08-23

Short example: plotting the spin flipper signal for run 39390, pulses [100,110):

		$ ipython --pylab
		In [1]: from n3he import *
		In [2]: d = DAQ( run=39390 )
		In [3]: for pulse in xrange(100,110):
		   ...:    d.GetEntry(pulse)
		   ...:    plot( pulse + tbins['dirty'], d[30](2) )

In a new window, add a plot of plane 1, wire 4 (second layer, center
wire) over the same interval:

		In [4]: figure()
		In [5]: for pulse in xrange(100,110):
		   ...:    d.GetEntry(pulse)
		   ...:    plot( pulse + tbins['clean'], d( 1, 4) )

Quick start on nucleon.mtsu.edu:
---------------------------

* Make sure your shell is set up to use the currently-installed ROOT
  in `/usr/local`:

		$ source /usr/local/bin/thisroot.sh

  Some people like to put this command in their `.bashrc` or
  `.bash_profile` scripts, so that it runs every time they log in.
  Note that it's possible to run ROOT without polluting your
  environment like this, but not for python to find ROOT's libraries.

* Make sure you have a working `libn3He.so` from Kabir:

		$ git clone https://github.com/latifkabir/n3He_Soft.git
		[in n3He_Soft/Library/libn3He] $ make
		[in n3He_Soft/Library/libn3He] $ cp lib/libn3He.so ~/your/n3he_rootpy/

  You'll want to have edited `Library/libn3He/src/Constants.h` to
  search for data in `/home/data`.  (Let me know if you have some data
  runs you would like available at MTSU.)

* Have a peek at some sample scripts

		$ ipython --pylab=auto -i misspulse_spectrum.py
		$ ipython --pylab=auto -i heatmap.py

  The locution `ipython -i script.py` runs the script and then
  deposits you at a Python prompt with all the variables from the
  script in the current namespace, so you can poke around at them.
