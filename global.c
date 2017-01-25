#include "global.h"

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <math.h>

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
