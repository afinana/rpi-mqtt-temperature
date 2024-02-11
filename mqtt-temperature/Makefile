CC = gcc
CFLAGS = -Wall  -Wextra -std=c99  -g -O0 -DDEBUG
LIBS = -lmosquitto
all : clean mqtt-temperature

mqtt-temperature: main.c connect.c publish.c connect.h publish.h suscribe.h
	$(CC) $(CFLAGS) -o mqtt-temperature main.c connect.c publish.c suscribe.c $(LIBS)

clean:
	rm -f mqtt-temperature