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

