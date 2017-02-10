#include "blast.h"
#include "spaceship.h"
#include "global.h"

#include <allegro5/allegro_primitives.h>
#include <math.h>
#include <assert.h>

struct Blast {
    float x;
    float y;
    float heading;
    float speed;
    ALLEGRO_COLOR color;
};

Blast *create_blast(const Spaceship *spaceship) {
    Blast *blast = (Blast*)malloc(sizeof(Blast));
    
    assert(blast);
    
    blast->x = spaceship_x(spaceship);
    blast->y = spaceship_y(spaceship);
    blast->heading = spaceship_heading(spaceship);
    blast->speed = 20;
    blast->color = SPACESHIP_COLOR;
    return blast;
}

void destroy_blast(Blast *blast) {
    free(blast);
}

void draw_blast(Blast *blast) {
    ALLEGRO_TRANSFORM transform;
    al_identity_transform(&transform);
    al_rotate_transform(&transform, degrees_to_radians(90.0) - blast->heading);
    al_translate_transform(&transform, blast->x, blast->y);
    al_use_transform(&transform);
    al_draw_line(0, 9, 0, 0, blast->color, 1.0f);
}

void update_blast(Blast *blast) {
    blast->x += cos(blast->heading) * blast->speed;
    blast->y -= sin(blast->heading) * blast->speed;
}

float blast_x(Blast *blast) {
    return blast->x;
}

float blast_y(Blast *blast) {
    return blast->y;
}