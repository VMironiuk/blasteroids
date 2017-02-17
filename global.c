#include "global.h"
#include "spaceship.h"
#include "blastqueue.h"
#include "asteroidbelt.h"
#include "collisions.h"

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>

void draw_live_indicator(size_t lives) {
    float x = 25.0;
    float y = 110.0;
    size_t i;
    for (i = 0; i < lives; ++i, x += 40.0) {
        ALLEGRO_TRANSFORM transform;
        al_identity_transform(&transform);
        al_translate_transform(&transform, x, y);
        al_use_transform(&transform);
        al_draw_line(-8, 9, 0, -11, al_map_rgb(0, 255, 0), 3.0f);
        al_draw_line(0, -11, 8, 9, al_map_rgb(0, 255, 0), 3.0f);
        al_draw_line(-6, 4, -1, 4, al_map_rgb(0, 255, 0), 3.0f);
        al_draw_line(6, 4, 1, 4, al_map_rgb(0, 255, 0), 3.0f);
    }
}

void draw_score(ALLEGRO_FONT *font, unsigned score) {
    ALLEGRO_TRANSFORM transform;
    al_identity_transform(&transform);
    al_use_transform(&transform);
                
    char score_str[16];
    sprintf(score_str, "%u", score);
    al_draw_text(font, al_map_rgb(192, 192, 192), 10, 10, ALLEGRO_ALIGN_LEFT, score_str);
}

void draw_game_over(ALLEGRO_FONT *font) {
    ALLEGRO_DISPLAY_MODE adm;
    al_get_display_mode(al_get_num_display_modes() - 1, &adm);
    al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);

    const char *text = "GAME OVER";
    int w = al_get_text_width(font, text);
    int h = al_get_font_line_height(font);
    int x = adm.width / 2 - w / 2;
    int y = adm.height / 2 - h;
    al_draw_text(font, al_map_rgb(192, 192, 192), x, y, ALLEGRO_ALIGN_LEFT, text);
}

void draw_message(ALLEGRO_FONT *font) {
    ALLEGRO_DISPLAY_MODE adm;
    al_get_display_mode(al_get_num_display_modes() - 1, &adm);
    al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);

    char *text = "Press Esc to exit the game";
    int w = al_get_text_width(font, text);
    int h = al_get_font_line_height(font);
    int x = adm.width / 2 - w / 2;
    int y = adm.height / 2 + h;
    al_draw_text(font, al_map_rgb(192, 192, 192), x, y, ALLEGRO_ALIGN_LEFT, text);

    text = "Press Enter to start new game";
    w = al_get_text_width(font, text);
    x = adm.width / 2 - w / 2;
    y += h;
    al_draw_text(font, al_map_rgb(192, 192, 192), x, y, ALLEGRO_ALIGN_LEFT, text);
}

void update_game_elements(GameData *game) {
    al_clear_to_color(al_map_rgb(0, 0, 0));
                
    update_spaceship(game->spaceship);
    update_spaceship_blaster(game->spaceship, game->blast_queue);
    draw_spaceship(game->spaceship);
                
    update_blast_queue(game->blast_queue);
    draw_blast_queue(game->blast_queue);
                
    update_asteroid_belt(game->asteroid_belt);
    draw_asteroid_belt(game->asteroid_belt);
                
    game->score += check_blast_asteroid_collision(game->blast_queue, game->asteroid_belt);
    game->lives -= check_spaceship_asteroid_collision(game->spaceship, game->asteroid_belt);

    draw_score(game->score_font, game->score);
    draw_live_indicator(game->lives);
                
    al_flip_display();

}

bool update_game_state(GameData *game) {
    al_clear_to_color(al_map_rgb(0, 0, 0));
                
    ALLEGRO_TRANSFORM transform;
    al_identity_transform(&transform);
    al_use_transform(&transform);

    draw_score(game->score_font, game->score);
    draw_game_over(game->game_over_font);
    draw_message(game->message_font);

    al_flip_display();
                
    while (true) {
        ALLEGRO_EVENT event;
        al_wait_for_event(game->event_queue, &event);
        if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
            if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
                return true;
            if (event.keyboard.keycode == ALLEGRO_KEY_ENTER) {
                destroy_asteroid_belt(game->asteroid_belt);
                destroy_blast_queue(game->blast_queue);
                destroy_spaceship(game->spaceship);
                game->spaceship = create_spaceship();
                game->blast_queue = create_blast_queue();
                game->asteroid_belt = create_asteroid_belt();
                game->score = 0;
                game->lives = 3;
                break;
            }
        }
    }
    return false;
}


bool blasteroids_update(GameData *game) {
    if (game->lives != 0) {
        update_game_elements(game);
        return false;
    }
    return update_game_state(game);
}

void error(const char *msg) {
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    exit(1);
}

float degrees_to_radians(float degrees) {
    return degrees * ALLEGRO_PI / 180;
}