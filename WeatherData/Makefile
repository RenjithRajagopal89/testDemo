CC=gcc
CFLAGS=-Wall
LDFLAGS=-lcurl

OBJECTS=WeatherFetch.o

WeatherFetch: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o WeatherFetch $(LDFLAGS)

all:WeatherFetch

.PHONY: clean
clean:
	rm -f *~ *.o WeatherFetch
