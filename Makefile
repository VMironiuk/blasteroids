# Compiler, tools and options

CC = gcc
LINK = gcc
CFLAGS = -pipe -g -Wall -W -fPIC
DEL_FILE = rm -f
INCPATH = -I.
LIBS = -lallegro -lallegro_main -lallegro_image -lallegro_font -lallegro_primitives -lm

# Files

OBJECTS = blasteroids.o \
	spaceship.o \
	global.o \
	blast.o \
	blastqueue.o
TARGET = blasteroids

# Build rules

$(TARGET): $(OBJECTS)
	$(LINK) -o $(TARGET) $(OBJECTS) $(LIBS)

# Compile

blasteroids.o: blasteroids.c global.h
	$(CC) -c $(CFLAGS) $(INCPATH) -o blasteroids.o blasteroids.c

spaceship.o: spaceship.c spaceship.h global.h
	$(CC) -c $(CFLAGS) $(INCPATH) -o spaceship.o spaceship.c

global.o: global.c global.h
	$(CC) -c $(CFLAGS) $(INCPATH) -o global.o global.c

blast.o: blast.c blast.h spaceship.h
	$(CC) -c $(CFLAGS) $(INCPATH) -o blast.o blast.c

blastqueue.o: blastqueue.c blastqueue.h
	$(CC) -c $(CFLAGS) $(INCPATH) -o blastqueue.o blastqueue.c

clean:
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) $(TARGET)
	-$(DEL_FILE) *~
