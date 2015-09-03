"Use dropped accelerator pulses to find a frame-overlap spectrum."

import n3he

run = n3he.TTreeRaw(39390)
p = n3he.DAQ( tree=run )

## which channel to take the spectrum of
if 1:
    titletext = 'adc 30, channel 0'
    channel = lambda: p.channel(30, 0) # or p[30](0)
    channel = lambda: p[30](0) # or p[30](0)
else:
    titletext = 'plane 2, wire 4'
    channel = lambda: p( 2, 4 )

## how many frames to search for overlap
trainlength=20
summed_pulsetrain = [ zeros_like( channel(), dtype=int64 )
                      for i in xrange(1+trainlength) ]
sumsqd_pulsetrain = [ zeros_like( channel(), dtype=float )
                      for i in xrange(1+trainlength) ]
count             = [ 0.0
                      for i in xrange(1+trainlength) ]

def thispulse_missing(p):
    "Identify missing pulses. Always use beam monitor."
    return mean( p.channel(30,0)[-16:] ) < 0.4e9

class MissedPulse (Exception): "Can't contstruct the pulse train"

## first few entries are bad
entry = 10
lastmissed = entry
i = 0
while entry < run.GetEntries()-trainlength:
    entry += 1
    run.GetEntry(entry)

    if thispulse_missing(p):
        if entry - lastmissed > trainlength:
            # First pulse missing after a long while.
            # Construct the pulse train
            run.GetEntry( entry-1 )
            pulsetrain = [ channel().copy() ]
            try:
                for i in xrange( trainlength ):
                    run.GetEntry( entry + i )
                    if i and thispulse_missing(p):
                        raise MissedPulse(i)
                    pulsetrain.append( pulsetrain[0] - channel() )

                print 'event {}'.format(entry)
                entry -= 1

                for pp in xrange(len(pulsetrain)):
                    summed_pulsetrain[pp] += pulsetrain[pp]
                    ## This locution converts to floating-point before
                    ## squaring, avoiding integer overflow
                    sumsqd_pulsetrain[pp] += \
                      (1.0 * pulsetrain[pp]) * pulsetrain[pp]
                    count[pp] += 1

                entry += i

            except MissedPulse as mp:
                print "event {}, missing {}".format(
                    entry, entry+i)
                lastmissed = entry + i
                entry += i
        else:
            lastmissed = entry

fig, (a1,a2) = subplots( 2,1, sharex=True )
a1.set_title( titletext )
a1.set_ylabel( 'signal (volts?)' )
a2.set_ylabel( 'signal (fraction of total)' )
a2.set_xlabel( 'pulses (each 1/60 s)' )

for pp in xrange(len(pulsetrain)):
    ## \sigma^2 = <x^2> - <x>^2
    meanx  = summed_pulsetrain[pp] / count[pp] ## count is float64
    sigma2 = sumsqd_pulsetrain[pp] / count[pp] - meanx**2
    ## But I want the error on the mean,
    ## not the width of the distribution
    sigma2 /= count[pp]

    ## Combine some time bins
    if len(meanx) == 1624:
        reshape=4*7
        tbins = n3he.tbins['dirty'][::reshape]
        meanx =       mean( meanx. reshape( (-1,reshape) ), 1 )
        sigma = sqrt( mean( sigma2.reshape( (-1,reshape) ), 1 ) )
    else:
        tbins = n3he.tbins['clean']
        sigma = sqrt( sigma2 )

    if pp == 0:
        mean0 = meanx
        sigma0 = sigma

    a1.errorbar( -1 + pp + tbins,
                 meanx * 2 * 2**-31,
                 sigma * 2 * 2**-31,
                 fmt='.', capsize=0 )

    a2.plot    ( -1 + pp + tbins,
                 meanx / mean0,
                 '.',
                 )

a2.set_ylim( 0,1 )
a2.set_xlim( xmin=-1 )
