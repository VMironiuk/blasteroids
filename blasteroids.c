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

void init()
{
    if (!al_init())
	error("Failed to initialize allegro");
    if (!al_init_image_addon())
	error("Failed to initialize the image addon");
    if (!al_init_primitives_addon())
	error("Failed to initialize the primitives addon");
    al_init_font_addon();
}

int main(int argc, char **argv)
{
    init();

    ALLEGRO_DISPLAY_MODE adm;
    al_get_display_mode(al_get_num_display_modes() - 1, &adm);
    al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);

    ALLEGRO_DISPLAY *display = al_create_display(adm.width, adm.height);
    if (!display)
	error("Failed to create window");

    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_flip_display();
    al_rest(10.0);
    al_destroy_display(display);

    return 0;
}
