all:
	g++ -g -o PlotCh src/PlotCh.cpp src/ReadBinary.cpp `root-config --cflags --glibs` && ./PlotCh

clear:
	rm -f src/*.o
clean:
	rm -f src/*.o PlotCh                                                      
