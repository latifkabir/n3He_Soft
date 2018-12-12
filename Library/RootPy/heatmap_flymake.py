"Generate some maps of the neutron capture signal inside the detector."

import n3he

run = n3he.TTreeRaw( 39390 )
pulserange = arange( 97, 687 ) ## no drops for this range

collector   = n3he.DAQ(tree=run, dtype=int32)
accumulator = n3he.DAQ(dtype=double)

for pulse in pulserange:
    collector.GetEntry(pulse)
    for adc in accumulator.keys():
        accumulator[adc].buffer += collector[adc].buffer

for adc in accumulator.keys():
        accumulator[adc].buffer /= len(pulserange)
        accumulator[adc].buffer *= 2 * 2**-31

fig,ax = subplots( nrows=4, ncols=1,
                   sharex=True, sharey=True,
                   figsize=(8.5,11), )
fig.subplots_adjust( hspace=0.05, wspace=0.05, )

layer = arange(16); wire = arange(9)

binrange = arange(12)
for i in xrange(len(ax)):
    ax[i].  contourf(   layer, wire,
                        [ [ mean( accumulator(l,w)[i*12 + binrange] )
                          for l in layer ]
                        for w in wire ],
                        linspace(0,0.5,20,),
                        )
    ax[i].plot( *meshgrid(layer, wire),
                color='red', marker='.', linestyle='', alpha=0.1 )

ax[3].set_xlabel( 'wire plane' )
ax[2].set_ylabel( 'wire number' )
ax[0].set_title( 'ionization signal in chamber' )
ax[0].text( 14,7, 'early in pulse',
            verticalalignment='top', horizontalalignment='right',
            bbox=dict(color='white', alpha=0.5) )
ax[3].text( 14,7, 'late in pulse',
            verticalalignment='top', horizontalalignment='right',
            bbox=dict(color='white', alpha=0.5) )
