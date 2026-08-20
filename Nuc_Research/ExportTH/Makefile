CXX:=/usr/bin/c++
CFLAGS:=`root-config --cflags`
LFLAGS:=`root-config --libs` -Wl,-rpath,/opt/ROOT/install/lib

all: export_th2d export_th1d

export_th2d: export_th2d.o
	$(CXX) $(CFLAGS) $(LFLAGS) $^ -o $@

export_th1d: export_th1d.o
	$(CXX) $(CFLAGS) $(LFLAGS) $^ -o $@

%.o: %.cpp
	$(CXX) $(CFLAGS) -c $^ -o $@

.PHONY: all clean

clean:
	rm -rf *.o export_th2d export_th1d
