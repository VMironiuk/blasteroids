CFLAGS = -g -Wall

%: %.c
	gcc $(CFLAGS) $^ -lallegro -lallegro_main -lallegro_image \
		-lallegro_font -lallegro_primitives -o $@

clean:
	rm -f *~ *.o blasteroids
