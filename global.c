#include "global.h"

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

#include <allegro5/allegro.h>

void error(const char *msg) {
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    exit(1);
}

float degrees_to_radians(float degrees) {
    return degrees * ALLEGRO_PI / 180;
}