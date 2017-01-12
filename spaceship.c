#include "spaceship.h"
#include "global.h"

#include <allegro5/allegro_primitives.h>
#include <math.h>

enum {MoveForward, MoveBackward, TurnLeft, TurnRight};
bool actions[4];

void handleBoundaries(Spaceship *spaceship)
{
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

void moveChanged(Spaceship *spaceship)
{
    if (spaceship->direction != spaceship->heading)
	spaceship->speed = 0.0;
    spaceship->direction = spaceship->heading;
}

Spaceship *createSpaceship()
{
    ALLEGRO_DISPLAY_MODE adm;
    al_get_display_mode(al_get_num_display_modes() - 1, &adm);

    Spaceship *spaceship = (Spaceship *)malloc(sizeof(Spaceship));
    spaceship->x = adm.width / 2;
    spaceship->y = adm.height / 2;
    spaceship->heading = degreesToRadians(90.0);
    spaceship->direction = spaceship->heading;
    spaceship->speed = 0.25;
    spaceship->color = al_map_rgb(0, 255, 0);
    return spaceship;
}

void destroySpaceship(Spaceship *spaceship)
{
    free(spaceship);
}

void drawSpaceship(Spaceship *spaceship)
{
    ALLEGRO_TRANSFORM transform;
    al_identity_transform(&transform);
    al_rotate_transform(&transform, degreesToRadians(90.0) - spaceship->heading);
    al_translate_transform(&transform, spaceship->x, spaceship->y);
    al_use_transform(&transform);
    al_draw_line(-8, 9, 0, -11, spaceship->color, 3.0f);
    al_draw_line(0, -11, 8, 9, spaceship->color, 3.0f);
    al_draw_line(-6, 4, -1, 4, spaceship->color, 3.0f);
    al_draw_line(6, 4, 1, 4, spaceship->color, 3.0f);
}

void updateSpaceship(Spaceship *spaceship)
{
    handleBoundaries(spaceship);

    if (actions[MoveForward]) {
	moveChanged(spaceship);
	if (spaceship->speed < 15.0)
	    spaceship->speed += 0.25;
    }
    else if (actions[MoveBackward]) {
	moveChanged(spaceship);
	if (spaceship->speed > -15.0)
	    spaceship->speed -= 0.25;
    }
    else if (actions[TurnLeft]) {
	spaceship->heading += degreesToRadians(5.0);
    }
    else if (actions[TurnRight]) {
	spaceship->heading -= degreesToRadians(5.0);
    }

    spaceship->x += cos(spaceship->direction) * spaceship->speed;
    spaceship->y -= sin(spaceship->direction) * spaceship->speed;
}

void moveSpaceshipForwardOn()
{
    actions[MoveForward] = true;
}

void moveSpaceshipBackwardOn()
{
    actions[MoveBackward] = true;
}

void turnSpaceshipLeftOn()
{
    actions[TurnLeft] = true;
}

void turnSpaceshipRightOn()
{
    actions[TurnRight] = true;
}

void moveSpaceshipForwardOff()
{
    actions[MoveForward] = false;
}

void moveSpaceshipBackwardOff()
{
    actions[MoveBackward] = false;
}

void turnSpaceshipLeftOff()
{
    actions[TurnLeft] = false;
}

void turnSpaceshipRightOff()
{
    actions[TurnRight] = false;
}
