#include "blast.h"
#include "spaceship.h"
#include "blastqueue.h"
#include "global.h"

#include <allegro5/allegro_primitives.h>
#include <math.h>
#include <assert.h>

struct Blast
{
    float x;
    float y;
    float heading;
    float speed;
    ALLEGRO_COLOR color;
};

int isBlastOutOfBoundaries(Blast *blast)
{
    ALLEGRO_DISPLAY_MODE adm;
    al_get_display_mode(al_get_num_display_modes() - 1, &adm);

    int result = 0;

    if (blast->y < 0)
        result = 1;
    else if (blast->y > adm.height)
        result = 1;
    else if (blast->x < 0)
        result = 1;
    else if (blast->x > adm.width)
        result = 1;

    return result;
}


Blast *createBlast(const Spaceship *spaceship)
{
    Blast *blast = (Blast*)malloc(sizeof(Blast));

    assert(blast);

    blast->x = spaceshipsX(spaceship);
    blast->y = spaceshipsY(spaceship);
    blast->heading = spaceshipsHeading(spaceship);
    blast->speed = 20;
    blast->color = spaceshipsColor(spaceship);
    return blast;
}

void destroyBlast(Blast *blast)
{
    free(blast);
}

void drawBlast(Blast *blast)
{
    ALLEGRO_TRANSFORM transform;
    al_identity_transform(&transform);
    al_rotate_transform(&transform, degreesToRadians(90.0) - blast->heading);
    al_translate_transform(&transform, blast->x, blast->y);
    al_use_transform(&transform);
    al_draw_line(0, 9, 0, 0, blast->color, 1.0f);
}

void updateBlast(Blast *blast)
{
    blast->x += cos(blast->heading) * blast->speed;
    blast->y -= sin(blast->heading) * blast->speed;
}

void drawBlastQueue(BlastQueue *queue)
{
    while (blastQueueHasNext(queue))
        drawBlast(blastQueueNext(queue));
}

void updateBlastQueue(BlastQueue *queue)
{
    while (blastQueueHasNext(queue)) {
        Blast *blast = blastQueueNext(queue);
        if (isBlastOutOfBoundaries(blast))
            popBlast(queue);
        else
            updateBlast(blast);
    }
}

float blastsX(Blast *blast)
{
    return blast->x;
}

float blastsY(Blast *blast)
{
    return blast->y;
}

float blastsWidth()
{
    static const float width = 1.0;
    return width;
}

float blastsHeight()
{
    static const float height = 9.0;
    return height;
}
