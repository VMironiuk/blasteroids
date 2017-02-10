#include "spaceship.h"
#include "global.h"
#include "blast.h"
#include "blastqueue.h"
#include "asteroidbelt.h"

#include <allegro5/allegro_primitives.h>
#include <math.h>
#include <assert.h>

struct Spaceship {
    float x;
    float y;
    float heading;
    float movement_direction;
    float speed;
    bool is_gone;
    ALLEGRO_COLOR color;
};

enum {MoveForward, MoveBackward, TurnLeft, TurnRight, Shoot};
bool actions[5];

void limit_boundaries_for_spaceship(Spaceship *spaceship) {
    ALLEGRO_DISPLAY_MODE adm;
    al_get_display_mode(al_get_num_display_modes() - 1, &adm);
    
    if (spaceship->y < 0)
        spaceship->y = adm.height;
    else if (spaceship->y > adm.height)
        spaceship->y = 0;
    else if (spaceship->x < 0)
        spaceship->x = adm.width;
    else if (spaceship->x > adm.width)
        spaceship->x = 0;
}

void movement_changed(Spaceship *spaceship) {
    if (spaceship->movement_direction != spaceship->heading)
        spaceship->speed = 0.0;
    spaceship->movement_direction = spaceship->heading;
}

Spaceship *create_spaceship() {
    ALLEGRO_DISPLAY_MODE adm;
    al_get_display_mode(al_get_num_display_modes() - 1, &adm);
    
    Spaceship *spaceship = (Spaceship *)malloc(sizeof *spaceship);
    
    assert(spaceship);
    
    spaceship->x = adm.width / 2;
    spaceship->y = adm.height / 2;
    spaceship->heading = degrees_to_radians(90.0);
    spaceship->movement_direction = spaceship->heading;
    spaceship->speed = 0.25;
    spaceship->is_gone = false;
    spaceship->color = SPACESHIP_COLOR;
    return spaceship;
}

void destroy_spaceship(Spaceship *spaceship) {
    free(spaceship);
}

void draw_spaceship(Spaceship *spaceship) {
    ALLEGRO_TRANSFORM transform;
    al_identity_transform(&transform);
    al_rotate_transform(&transform, degrees_to_radians(90.0) - spaceship->heading);
    al_translate_transform(&transform, spaceship->x, spaceship->y);
    al_use_transform(&transform);
    al_draw_line(-8, 9, 0, -11, spaceship->color, 3.0f);
    al_draw_line(0, -11, 8, 9, spaceship->color, 3.0f);
    al_draw_line(-6, 4, -1, 4, spaceship->color, 3.0f);
    al_draw_line(6, 4, 1, 4, spaceship->color, 3.0f);
}

void update_spaceship(Spaceship *spaceship) {
    limit_boundaries_for_spaceship(spaceship);
    
    if (actions[MoveForward]) {
        movement_changed(spaceship);
        if (spaceship->speed < 15.0)
            spaceship->speed += 0.25;
    }
    
    if (actions[MoveBackward]) {
        movement_changed(spaceship);
        if (spaceship->speed > -15.0)
            spaceship->speed -= 0.25;
    }
    
    if (actions[TurnLeft])
        spaceship->heading += degrees_to_radians(5.0);
    
    if (actions[TurnRight])
        spaceship->heading -= degrees_to_radians(5.0);
    
    spaceship->x += cos(spaceship->movement_direction) * spaceship->speed;
    spaceship->y -= sin(spaceship->movement_direction) * spaceship->speed;
}

void update_spaceship_blaster(Spaceship *spaceship, BlastQueue *queue) {
    if (actions[Shoot])
        push_blast(queue, create_blast(spaceship));
}

float spaceship_x(const Spaceship *spaceship) {
    return spaceship->x;
}

float spaceship_y(const Spaceship *spaceship) {
    return spaceship->y;
}

float spaceship_heading(const Spaceship *spaceship) {
    return spaceship->heading;
}

void move_spaceship_forward_on() {
    actions[MoveForward] = true;
}

void move_spaceship_backward_on() {
    actions[MoveBackward] = true;
}

void turn_spaceship_left_on() {
    actions[TurnLeft] = true;
}

void turn_spaceship_right_on() {
    actions[TurnRight] = true;
}

void move_spaceship_forward_off() {
    actions[MoveForward] = false;
}

void move_spaceship_backward_off() {
    actions[MoveBackward] = false;
}

void turn_spaceship_left_off() {
    actions[TurnLeft] = false;
}

void turn_spaceship_right_off() {
    actions[TurnRight] = false;
}

void shoot_spaceship_on() {
    actions[Shoot] = true;
}

void shoot_spaceship_off() {
    actions[Shoot] = false;
}

void set_spaceship_gone(Spaceship *spaceship, bool is_gone) {
    spaceship->is_gone = is_gone;
}

bool is_spaceship_gone(Spaceship *spaceship) {
    return spaceship->is_gone;
}