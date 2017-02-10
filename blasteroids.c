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

void draw_live(float x, float y) {
    ALLEGRO_TRANSFORM transform;
    al_identity_transform(&transform);
    al_translate_transform(&transform, x, y);
    al_use_transform(&transform);
    al_draw_line(-8, 9, 0, -11, al_map_rgb(0, 255, 0), 3.0f);
    al_draw_line(0, -11, 8, 9, al_map_rgb(0, 255, 0), 3.0f);
    al_draw_line(-6, 4, -1, 4, al_map_rgb(0, 255, 0), 3.0f);
    al_draw_line(6, 4, 1, 4, al_map_rgb(0, 255, 0), 3.0f);
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

    ALLEGRO_FONT *font = al_load_font("Planetium_X_Shadowed.otf", 72, 0);
    if (!font) {
        destroy_asteroid_belt(asteroid_belt);
        destroy_blast_queue(blast_queue);
        destroy_spaceship(sulaco);
        al_destroy_event_queue(event_queue);
        al_destroy_display(display);
        al_destroy_timer(timer);
        error("Failed to load font");
    }
    
    unsigned score = 0;
    size_t lives = 3;
    bool do_exit = false;
    while (!do_exit) {
        if (is_spaceship_gone(sulaco)) {
            destroy_spaceship(sulaco);
            sulaco = create_spaceship();
        }


        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue, &event);
        
        if (event.type == ALLEGRO_EVENT_TIMER) {
            al_clear_to_color(al_map_rgb(0, 0, 0));

            update_spaceship(sulaco);
            update_spaceship_blaster(sulaco, blast_queue);
            draw_spaceship(sulaco);
            
            update_blast_queue(blast_queue);
            draw_blast_queue(blast_queue);
            
            update_asteroid_belt(asteroid_belt);
            draw_asteroid_belt(asteroid_belt);

            score += check_blast_asteroid_collision(blast_queue, asteroid_belt);
            lives -= check_spaceship_asteroid_collision(sulaco, asteroid_belt);

            ALLEGRO_TRANSFORM transform;
            al_identity_transform(&transform);
            al_use_transform(&transform);

            char score_str[16];
            sprintf(score_str, "%u", score);
            al_draw_text(font, al_map_rgb(192, 192, 192), 10, 10, ALLEGRO_ALIGN_LEFT, score_str);

            size_t i;
            float x = 25.0;
            const float y = 110.0;
            for (i = 0; i < lives; ++i, x += 40.0)
                draw_live(x, y);

            al_flip_display();
        }

        if (!lives)
            break;
        
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

    al_destroy_font(font);
    destroy_asteroid_belt(asteroid_belt);
    destroy_blast_queue(blast_queue);
    destroy_spaceship(sulaco);
    al_destroy_event_queue(event_queue);
    al_destroy_display(display);
    al_destroy_timer(timer);
    
    return 0;
}
