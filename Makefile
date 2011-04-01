CC=g++
CFLAGS=-Wall -pedantic -g
OBJS=parser.o main.o data.o taskcontainer.o calendar.o

parser: $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

$(OBJS): %.o:%.cpp
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -f *.o parser

.PHONY: all clean
