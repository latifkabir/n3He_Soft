PlotCh
======
This script can plot ADC count vs entry number for specied channel starting from specified point. 
This is purely C++ script but the final plot is shown thgrough ROOT.

Steps
----
* Do `make`
* Give channel number for which the graph to be plotted
* Give specific starting point.
* Graph will be plotted for next 10000 entries starting from the specified point.
* For further execution just do:`./PlotCh` followed by channel number and starting point.