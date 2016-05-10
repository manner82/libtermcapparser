CXXFLAGS= -I$(PREFIX)/include -O0 -g -Wall -I..
LDFLAGS = -L$(PREFIX)/lib -lpthread -ltermcapparser -L.. -L/usr/lib -lgmock -lgtest -lpthread
OBJECTS = test.o cell.o row.o state.o palette.o termcapparser.o

all: test runtest

.PHONY:
runtest: test
	./test

.PHONY:
clean:
	rm -f $(OBJECTS) test

test: $(OBJECTS)
	$(CXX) -o test $(OBJECTS) $(LDFLAGS)

%.o: %.cc
	$(CXX) -c -o $@ $< $(CXXFLAGS)
