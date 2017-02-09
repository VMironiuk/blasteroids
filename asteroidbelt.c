#include "asteroidbelt.h"
#include "asteroid.h"
#include "blast.h"
#include "global.h"
#include "spaceship.h"

#include <stdlib.h>
#include <assert.h>

#define ASTEROID_CREATING_INTERVAL 5

typedef struct Node Node;

struct Node
{
    Asteroid *asteroid;
    Node *previous;
    Node *next;
};
typedef Node *Link;

struct AsteroidBelt
{
    Link head;
    Link tail;
};

void pushBackAsteroid(AsteroidBelt *asteroidBelt, Asteroid *asteroid)
{
    Link temp = (Node *)malloc(sizeof *temp);
    temp->asteroid = asteroid;
    temp->previous = 0;
    temp->next = 0;
    
    if (!asteroidBelt->tail) {
        asteroidBelt->head = temp;
        asteroidBelt->tail = temp;
    } else {
        asteroidBelt->tail->next = temp;
        temp->previous = asteroidBelt->tail;
        asteroidBelt->tail = temp;
    }
}

void pushNewAsteroid(AsteroidBelt *asteroidBelt)
{
    static float oldTime = 0.0;
    
    // create and push back new asteroids every 5 seconds
    float currentTime = al_current_time();
    if (currentTime - oldTime > ASTEROID_CREATING_INTERVAL) {
        oldTime = currentTime;
        Link temp = (Node *)malloc(sizeof *temp);
        pushBackAsteroid(asteroidBelt, createAsteroid(1.0));
    }
}

Link eraseAsteroid(AsteroidBelt *ab, Link node)
{
    Link result = node->next;
    
    if (node->next)
        node->next->previous = node->previous;
    
    if (node->previous)
        node->previous->next = node->next;
    
    if (node == ab->head)
        ab->head = ab->head->next;
    
    if (node == ab->tail)
        ab->tail = ab->tail->previous;
    
    destroyAsteroid(node->asteroid);
    free(node);
    
    return result;
}

AsteroidBelt *createAsteroidBelt()
{
    AsteroidBelt *ab = (AsteroidBelt *)malloc(sizeof *ab);

    assert(ab);

    ab->head = 0;
    ab->tail = 0;
    return ab;
}

void destroyAsteroidBelt(AsteroidBelt *asteroidBelt)
{
    while (asteroidBelt->head) {
        Link temp = asteroidBelt->head->next;
        destroyAsteroid(asteroidBelt->head->asteroid);
        free(asteroidBelt->head);
        asteroidBelt->head = temp;
    }

    free(asteroidBelt);
}

void drawAsteroidBelt(AsteroidBelt *asteroidBelt)
{
    Link current = asteroidBelt->head;
    while (current) {
        drawAsteroid(current->asteroid);
        current = current->next;
    }
}

void updateAsteroidBelt(AsteroidBelt *asteroidBelt)
{
    Link current = asteroidBelt->head;
    while (current) {
        updateAsteroid(current->asteroid);
        current = current->next;
    }
    
    pushNewAsteroid(asteroidBelt);
}

bool isBlastHitToAsteroid(Blast *blast, AsteroidBelt *asteroidBelt)
{
    Link current = asteroidBelt->head;
    while (current) {
        Asteroid *asteroid = current->asteroid;
        int x1 = blastX(blast) - BLAST_WIDTH / 2;
        int y1 = blastY(blast) - BLAST_HEIGHT / 2;
        int w1 = BLAST_WIDTH;
        int h1 = BLAST_HEIGHT;
        int x2 = asteroidX(asteroid) - ASTEROID_WIDTH / 2;
        int y2 = asteroidY(asteroid) - ASTEROID_HEIGHT / 2;
        int w2 = ASTEROID_WIDTH;
        int h2 = ASTEROID_HEIGHT;
        if (isBoundingBoxCollision(x1, y1, w1, h1, x2, y2, w2, h2)) {
            if (!isAsteroidBroken(asteroid)) {
                Asteroid *leftAsteroid = 0;
                Asteroid *rightAsteroid = 0;
                breakAsteroid(asteroid, &leftAsteroid, &rightAsteroid);
                pushBackAsteroid(asteroidBelt, leftAsteroid);
                pushBackAsteroid(asteroidBelt, rightAsteroid);
            }
            eraseAsteroid(asteroidBelt, current);
            return true;
        }
        current = current->next;
    }
    return false;
}

bool isAsteroidHitToSpaceship(struct Spaceship *spaceship, AsteroidBelt *asteroidBelt)
{
    Link current = asteroidBelt->head;
    while (current) {
        Asteroid *asteroid = current->asteroid;
        int x1 = spaceshipX(spaceship) - SPACESHIP_WIDTH / 2;
        int y1 = spaceshipY(spaceship) - SPACESHIP_HEIGHT / 2;
        int w1 = SPACESHIP_WIDTH;
        int h1 = SPACESHIP_HEIGHT;
        int x2 = asteroidX(asteroid) - ASTEROID_WIDTH / 2;
        int y2 = asteroidY(asteroid) - ASTEROID_HEIGHT / 2;
        int w2 = ASTEROID_WIDTH;
        int h2 = ASTEROID_HEIGHT;

        if (isBoundingBoxCollision(x1, y1, w1, h1, x2, y2, w2, h2))
            return true;

        current = current->next;
    }
    return false;
}