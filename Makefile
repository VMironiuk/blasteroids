# Compiler, tools and options

CC = gcc
LINK = gcc
CFLAGS = -pipe -g -Wall -W -fPIC
DEL_FILE = rm -f
INCPATH = -I.
LIBS = -lallegro -lallegro_main -lallegro_image -lallegro_font -lallegro_primitives

# Files

OBJECTS = blasteroids.o \
		spaceship.o
TARGET = blasteroids

# Build rules

$(TARGET): $(OBJECTS)
	$(LINK) -o $(TARGET) $(OBJECTS) $(LIBS)

# Compile

blasteroids.o: blasteroids.c
	$(CC) -c $(CFLAGS) $(INCPATH) -o blasteroids.o blasteroids.c

spaceship.o: spaceship.c spaceship.h
	$(CC) -c $(CFLAGS) $(INCPATH) -o spaceship.o spaceship.c

clean:
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) $(TARGET)
	-$(DEL_FILE) *~