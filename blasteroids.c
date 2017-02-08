#include "spaceship.h"
#include "global.h"
#include "blastqueue.h"
#include "asteroidbelt.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <stdio.h>

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
    if (!al_init_ttf_addon())
        error("Failed to initialize the ttf addon");
}

int main(/*int argc, char **argv*/)
{
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
    
    ALLEGRO_EVENT_QUEUE *eventQueue = al_create_event_queue();
    if (!eventQueue) {
        al_destroy_display(display);
        al_destroy_timer(timer);
        error("Failed to create event queue");
    }
    
    al_register_event_source(eventQueue, al_get_keyboard_event_source());
    al_register_event_source(eventQueue, al_get_timer_event_source(timer));
    
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_flip_display();
    al_start_timer(timer);

    Spaceship *sulaco = createSpaceship();
    BlastQueue *blastQueue = createBlastQueue();
    AsteroidBelt *asteroidBelt = createAsteroidBelt();

    ALLEGRO_FONT *font = al_load_font("Planetium_X_Shadowed.otf", 72, 0);
    if (!font) {
        destroyAsteroidBelt(asteroidBelt);
        destroyBlastQueue(blastQueue);
        destroySpaceship(sulaco);
        al_destroy_event_queue(eventQueue);
        al_destroy_display(display);
        al_destroy_timer(timer);
        error("Failed to load font");
    }
    
    unsigned score = 0;
    size_t lives = 3;
    bool doExit = false;
    while (!doExit) {
        if (isSpaceshipGone(sulaco)) {
            destroySpaceship(sulaco);
            sulaco = createSpaceship();
        }


        ALLEGRO_EVENT event;
        al_wait_for_event(eventQueue, &event);
        
        if (event.type == ALLEGRO_EVENT_TIMER) {
            al_clear_to_color(al_map_rgb(0, 0, 0));

            updateSpaceship(sulaco);
            updateSpaceshipsBlaster(sulaco, blastQueue);
            drawSpaceship(sulaco);
            
            updateBlastQueue(blastQueue);
            drawBlastQueue(blastQueue);
            
            updateAsteroidBelt(asteroidBelt);
            drawAsteroidBelt(asteroidBelt);

            score += checkBlastAsteroidCollision(blastQueue, asteroidBelt);
            lives -= checkSpaceshipAsteroidCollision(sulaco, asteroidBelt);

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
                drawLive(x, y);

            al_flip_display();
        }

        if (!lives)
            break;
        
        if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
            switch (event.keyboard.keycode) {
            case ALLEGRO_KEY_ESCAPE:
                doExit = true;
                break;
            case ALLEGRO_KEY_UP:
                moveSpaceshipForwardOn();
                break;
            case ALLEGRO_KEY_DOWN:
                moveSpaceshipBackwardOn();
                break;
            case ALLEGRO_KEY_LEFT:
                turnSpaceshipLeftOn();
                break;
            case ALLEGRO_KEY_RIGHT:
                turnSpaceshipRightOn();
                break;
            case ALLEGRO_KEY_SPACE:
                shootSpaceshipOn();
                break;
            default:
                break;
            }
        }
        
        if (event.type == ALLEGRO_EVENT_KEY_UP) {
            switch (event.keyboard.keycode) {
            case ALLEGRO_KEY_UP:
                moveSpaceshipForwardOff();
                break;
            case ALLEGRO_KEY_DOWN:
                moveSpaceshipBackwardOff();
                break;
            case ALLEGRO_KEY_LEFT:
                turnSpaceshipLeftOff();
                break;
            case ALLEGRO_KEY_RIGHT:
                turnSpaceshipRightOff();
                break;
            case ALLEGRO_KEY_SPACE:
                shootSpaceshipOff();
                break;
            default:
                break;
            }
        }
    }

    al_destroy_font(font);
    destroyAsteroidBelt(asteroidBelt);
    destroyBlastQueue(blastQueue);
    destroySpaceship(sulaco);
    al_destroy_event_queue(eventQueue);
    al_destroy_display(display);
    al_destroy_timer(timer);
    
    return 0;
}
