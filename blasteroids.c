#include "spaceship.h"
#include "global.h"
#include "blastqueue.h"
#include "asteroidbelt.h"
#include "collisions.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <stdio.h>

void init() {
    if (!al_init())
        error("Failed to initialize allegro");
    if (!al_init_image_addon())
        error("Failed to initialize the image addon");
    if (!al_init_primitives_addon())
        error("Failed to initialize the primitives addon");
    if (!al_install_keyboard())
        error("Failed to install a keyboard driver");
    al_init_font_addon();
    if (!al_init_ttf_addon())
        error("Failed to initialize the ttf addon");
}

int main(/*int argc, char **argv*/) {
    init();
    
    ALLEGRO_TIMER *timer = al_create_timer(1.0 / FPS);
    if (!timer)
        error("Failed to create timer");
    
    ALLEGRO_DISPLAY_MODE adm;
    al_get_display_mode(al_get_num_display_modes() - 1, &adm);
    al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);
    
    ALLEGRO_DISPLAY *display = al_create_display(adm.width, adm.height);
    if (!display) {
        al_destroy_timer(timer);
        error("Failed to create display");
    }
    
    ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
    if (!event_queue) {
        al_destroy_display(display);
        al_destroy_timer(timer);
        error("Failed to create event queue");
    }
    
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_flip_display();
    al_start_timer(timer);
    
    Spaceship *sulaco = create_spaceship();
    BlastQueue *blast_queue = create_blast_queue();
    AsteroidBelt *asteroid_belt = create_asteroid_belt();
    
    ALLEGRO_FONT *score_font = al_load_font("Planetium_X_Shadowed.otf", 72, 0);
    if (!score_font) {
        destroy_asteroid_belt(asteroid_belt);
        destroy_blast_queue(blast_queue);
        destroy_spaceship(sulaco);
        al_destroy_event_queue(event_queue);
        al_destroy_display(display);
        al_destroy_timer(timer);
        error("Failed to load font");
    }

    ALLEGRO_FONT *game_over_font = al_load_font("Planetium_X_Shadowed.otf", 144, 0);
    if (!game_over_font) {
        al_destroy_font(score_font);
        destroy_asteroid_belt(asteroid_belt);
        destroy_blast_queue(blast_queue);
        destroy_spaceship(sulaco);
        al_destroy_event_queue(event_queue);
        al_destroy_display(display);
        al_destroy_timer(timer);
        error("Failed to load font");
    }

    ALLEGRO_FONT *message_font = al_load_font("Planetium_X_Shadowed.otf", 48, 0);
    if (!message_font) {
        al_destroy_font(game_over_font);
        al_destroy_font(score_font);
        destroy_asteroid_belt(asteroid_belt);
        destroy_blast_queue(blast_queue);
        destroy_spaceship(sulaco);
        al_destroy_event_queue(event_queue);
        al_destroy_display(display);
        al_destroy_timer(timer);
        error("Failed to load font");
    }

    GameData game_data;
    game_data.spaceship = sulaco;
    game_data.asteroid_belt = asteroid_belt;
    game_data.blast_queue = blast_queue;
    game_data.score_font = score_font;
    game_data.game_over_font = game_over_font;
    game_data.message_font = message_font;
    game_data.event_queue = event_queue;
    game_data.score = 0;
    game_data.lives = 3;
    bool do_exit = false;
    while (!do_exit) {
        if (is_spaceship_gone(sulaco)) {
            destroy_spaceship(sulaco);
            sulaco = create_spaceship();
        }
        
        
        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue, &event);
        
        if (event.type == ALLEGRO_EVENT_TIMER)
            do_exit = blasteroids_update(&game_data);
        
        if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
            switch (event.keyboard.keycode) {
            case ALLEGRO_KEY_ESCAPE:
                do_exit = true;
                break;
            case ALLEGRO_KEY_UP:
                move_spaceship_forward_on();
                break;
            case ALLEGRO_KEY_DOWN:
                move_spaceship_backward_on();
                break;
            case ALLEGRO_KEY_LEFT:
                turn_spaceship_left_on();
                break;
            case ALLEGRO_KEY_RIGHT:
                turn_spaceship_right_on();
                break;
            case ALLEGRO_KEY_SPACE:
                shoot_spaceship_on();
                break;
            default:
                break;
            }
        }
        
        if (event.type == ALLEGRO_EVENT_KEY_UP) {
            switch (event.keyboard.keycode) {
            case ALLEGRO_KEY_UP:
                move_spaceship_forward_off();
                break;
            case ALLEGRO_KEY_DOWN:
                move_spaceship_backward_off();
                break;
            case ALLEGRO_KEY_LEFT:
                turn_spaceship_left_off();
                break;
            case ALLEGRO_KEY_RIGHT:
                turn_spaceship_right_off();
                break;
            case ALLEGRO_KEY_SPACE:
                shoot_spaceship_off();
                break;
            default:
                break;
            }
        }
    }
    
    al_destroy_font(message_font);
    al_destroy_font(game_over_font);
    al_destroy_font(score_font);
    destroy_asteroid_belt(asteroid_belt);
    destroy_blast_queue(blast_queue);
    destroy_spaceship(sulaco);
    al_destroy_event_queue(event_queue);
    al_destroy_display(display);
    al_destroy_timer(timer);
    
    return 0;
}
