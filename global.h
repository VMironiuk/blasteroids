#ifndef GLOBAL_H
#define GLOBAL_H

#include <stdlib.h>
#include <stdbool.h>

#define FPS 60

struct Spaceship;
struct AsteroidBelt;
struct BlastQueue;
struct ALLEGRO_FONT;
struct ALLEGRO_EVENT_QUEUE;
struct GameData {
    struct Spaceship *spaceship;
    struct AsteroidBelt *asteroid_belt;
    struct BlastQueue *blast_queue;
    struct ALLEGRO_FONT *score_font;
    struct ALLEGRO_FONT *game_over_font;
    struct ALLEGRO_FONT *message_font;
    struct ALLEGRO_EVENT_QUEUE *event_queue;
    unsigned score;
    size_t lives;
};
typedef struct GameData GameData;

bool blasteroids_update(struct GameData *game);
void error(const char *msg);
float degrees_to_radians(float degrees);

#endif
