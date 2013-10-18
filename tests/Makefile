CXXFLAGS= -I$(PREFIX)/include -O0 -g -Wall -I..
LDFLAGS = -L$(PREFIX)/lib -lpthread -ltermcapparser -lgtest -L.. -L/usr/lib
OBJECTS = test.o cell.o row.o state.o palette.o termcapparser.o

all: test runtest

.PHONY:
runtest: test
	./test

.PHONY:
clean:
	rm -f $(OBJECTS) test

test: $(OBJECTS)
	$(CXX) -o test $(LDFLAGS) $(OBJECTS)

%.o: %.cc
	$(CXX) -c -o $@ $< $(CXXFLAGS)
