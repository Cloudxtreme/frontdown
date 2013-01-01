TARGET=frontdown
OBJS=$(patsubst %.c,%.o,$(wildcard *.c))
CC=gcc
CFLAGS=-L./ -Wall -g -lpthread -lcurl -D_GNU_SOURCE `pkg-config gtk+-2.0 --cflags --libs`

all: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)
	
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

distclean: clean
	rm -f $(TARGET)
	rm -f $(TARGET).exe
	
new: distclean all
