#include "spaceship.h"
#include "global.h"
#include "blast.h"
#include "blastqueue.h"
#include "asteroidbelt.h"

#include <allegro5/allegro_primitives.h>
#include <math.h>
#include <assert.h>

struct Spaceship
{
    float x;
    float y;
    float heading;
    float movingDirection;
    float speed;
    ALLEGRO_COLOR color;
};

enum {MoveForward, MoveBackward, TurnLeft, TurnRight, Shoot};
bool actions[5];

void limitBoundariesForSpaceship(Spaceship *spaceship)
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
    if (spaceship->movingDirection != spaceship->heading)
	spaceship->speed = 0.0;
    spaceship->movingDirection = spaceship->heading;
}

Spaceship *createSpaceship()
{
    ALLEGRO_DISPLAY_MODE adm;
    al_get_display_mode(al_get_num_display_modes() - 1, &adm);

    Spaceship *spaceship = (Spaceship *)malloc(sizeof *spaceship);

    assert(spaceship);

    spaceship->x = adm.width / 2;
    spaceship->y = adm.height / 2;
    spaceship->heading = degreesToRadians(90.0);
    spaceship->movingDirection = spaceship->heading;
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
    limitBoundariesForSpaceship(spaceship);

    if (actions[MoveForward]) {
	moveChanged(spaceship);
	if (spaceship->speed < 15.0)
	    spaceship->speed += 0.25;
    }

    if (actions[MoveBackward]) {
	moveChanged(spaceship);
	if (spaceship->speed > -15.0)
	    spaceship->speed -= 0.25;
    }

    if (actions[TurnLeft])
	spaceship->heading += degreesToRadians(5.0);

    if (actions[TurnRight])
	spaceship->heading -= degreesToRadians(5.0);

    spaceship->x += cos(spaceship->movingDirection) * spaceship->speed;
    spaceship->y -= sin(spaceship->movingDirection) * spaceship->speed;
}

void updateSpaceshipsBlaster(Spaceship *spaceship, BlastQueue *queue)
{
    if (actions[Shoot])
	pushBlast(queue, createBlast(spaceship));
}

float spaceshipsX(const Spaceship *spaceship)
{
    return spaceship->x;
}

float spaceshipsY(const Spaceship *spaceship)
{
    return spaceship->y;
}

float spaceshipsHeading(const Spaceship *spaceship)
{
    return spaceship->heading;
}

ALLEGRO_COLOR spaceshipsColor(const Spaceship *spaceship)
{
    return spaceship->color;
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

void shootSpaceshipOn()
{
    actions[Shoot] = true;
}

void shootSpaceshipOff()
{
    actions[Shoot] = false;
}

int checkSpaceshipAsteroidCollision(Spaceship *spaceship, AsteroidBelt *asteroidBelt)
{
    return 0;
}
