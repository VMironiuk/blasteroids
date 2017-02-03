#include "global.h"

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <math.h>

#include <allegro5/allegro_primitives.h>

void error(const char *msg)
{
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    exit(1);
}

float degreesToRadians(float degrees)
{
    return degrees * M_PI / 180;
}

int isBoundingBoxCollision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2)
{
    return !((x1 > x2 + w2 - 1) || (y1 > y2 + h2 - 1) || (x2 > x1 + w1 - 1) || (y2 > y1 + h1 - 1));
}

void drawLive(float x, float y)
{
    ALLEGRO_TRANSFORM transform;
    al_identity_transform(&transform);
    // al_rotate_transform(&transform, degreesToRadians(90.0) - spaceship->heading);
    al_translate_transform(&transform, x, y);
    al_use_transform(&transform);
    al_draw_line(-8, 9, 0, -11, al_map_rgb(0, 255, 0), 3.0f);
    al_draw_line(0, -11, 8, 9, al_map_rgb(0, 255, 0), 3.0f);
    al_draw_line(-6, 4, -1, 4, al_map_rgb(0, 255, 0), 3.0f);
    al_draw_line(6, 4, 1, 4, al_map_rgb(0, 255, 0), 3.0f);
}