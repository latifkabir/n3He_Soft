all:
	g++ -g -std=c++11 -o histo src/histo.cpp src/ReadBinary.cpp `root-config --cflags --glibs`

clear:
	rm -f src/*.o
clean:
	rm -f src/*.o histo                                                      
