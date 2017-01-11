#include "spaceship.h"
#include "global.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>

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

    Spaceship *spaceship = createSpaceship();

    bool doExit = false;
    while (!doExit) {
	al_clear_to_color(al_map_rgb(0, 0, 0));
	drawSpaceship(spaceship);
	al_flip_display();

	ALLEGRO_EVENT event;
	al_wait_for_event(eventQueue, &event);
	if (event.type == ALLEGRO_EVENT_KEY_CHAR) {
	    switch (event.keyboard.keycode) {
	    case ALLEGRO_KEY_ESCAPE:
		doExit = true;
		break;
	    case ALLEGRO_KEY_UP:
		moveSpaceshipForward(spaceship);
		break;
	    case ALLEGRO_KEY_DOWN:
		moveSpaceshipBackward(spaceship);
		break;
	    case ALLEGRO_KEY_LEFT:
		turnSpaceshipLeft(spaceship);
		break;
	    case ALLEGRO_KEY_RIGHT:
		turnSpaceshipRight(spaceship);
		break;
	    default:
		break;
	    }
	}
    }

    destroySpaceship(spaceship);
    al_destroy_display(display);
    al_destroy_event_queue(eventQueue);

    return 0;
}
