#ifndef SPACESHIP_H
#define SPACESHIP_H

#include <allegro5/allegro.h>

#define SPACESHIP_WIDTH 21.0
#define SPACESHIP_HEIGHT 21.0
#define SPACESHIP_COLOR al_map_rgb(0, 255, 0)

struct BlastQueue;

typedef struct Spaceship Spaceship;

Spaceship *create_spaceship();
void destroy_spaceship(Spaceship *spaceship);
void draw_spaceship(Spaceship *spaceship);
void update_spaceship(Spaceship *spaceship);
void update_spaceship_blaster(Spaceship *spaceship, struct BlastQueue *queue);
float spaceship_x(const Spaceship *spaceship);
float spaceship_y(const Spaceship *spaceship);
float spaceship_heading(const Spaceship *spaceship);
void move_spaceship_forward_on();
void move_spaceship_backward_on();
void turn_spaceship_left_on();
void turn_spaceship_right_on();
void move_spaceship_forward_off();
void move_spaceship_backward_off();
void turn_spaceship_left_off();
void turn_spaceship_right_off();
void shoot_spaceship_on();
void shoot_spaceship_off();
void set_spaceship_gone(Spaceship *spaceship, bool is_gone);
bool is_spaceship_gone(Spaceship *spaceship);

#endif
