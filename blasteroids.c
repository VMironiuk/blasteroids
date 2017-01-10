#include "spaceship.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

void error(const char *msg)
{
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    exit(1);
}

void debug(const char *msg)
{
    printf("%s\n", msg);
}

void init()
{
    if (!al_init())
    	error("Failed to initialize allegro");
    if (!al_init_image_addon())
    	error("Failed to initialize the image addon");
    if (!al_init_primitives_addon())
    	error("Failed to initialize the primitives addon");
    if (!al_install_keyboard())
        error("Failed to install a keyboard driver");
    al_init_font_addon();
}

int main(/*int argc, char **argv*/)
{
    init();

    ALLEGRO_DISPLAY_MODE adm;
    al_get_display_mode(al_get_num_display_modes() - 1, &adm);
    al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);

    ALLEGRO_DISPLAY *display = al_create_display(adm.width, adm.height);
    if (!display)
    	error("Failed to create display");

    ALLEGRO_EVENT_QUEUE *eventQueue = al_create_event_queue();
    if (!eventQueue) {
        al_destroy_display(display);
        error("Failed to create event queue");
    }

    al_register_event_source(eventQueue, al_get_keyboard_event_source());

    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_flip_display();

    Spaceship *spaceship = createSpaceship(&adm);

    while (1) {
        ALLEGRO_EVENT event;
        bool hasEvent = al_get_next_event(eventQueue, &event);
	if (hasEvent && event.type == ALLEGRO_EVENT_KEY_CHAR) {
	    if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
		break;
	    }
	    if (event.keyboard.keycode == ALLEGRO_KEY_UP) {
		if (spaceship->y < 0)
		    spaceship->y = adm.height;
		spaceship->y -= 4.0;
	    }
	    if (event.keyboard.keycode == ALLEGRO_KEY_DOWN) {
		if (spaceship->y > adm.height)
		    spaceship->y = 0;
		spaceship->y += 4.0;
	    }
	    if (event.keyboard.keycode == ALLEGRO_KEY_LEFT) {
		if (spaceship->x < 0)
		    spaceship->x = adm.width;
		spaceship->x -= 4.0;
	    }
	    if (event.keyboard.keycode == ALLEGRO_KEY_RIGHT) {
		if (spaceship->x > adm.width)
		    spaceship->x = 0;
		spaceship->x += 4.0;
	    }
	}

        al_clear_to_color(al_map_rgb(0, 0, 0));
	drawSpaceship(spaceship);
        al_flip_display();
    }

    al_destroy_display(display);
    al_destroy_event_queue(eventQueue);
    destroySpaceship(spaceship);

    return 0;
}
