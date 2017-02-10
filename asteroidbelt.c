#include "asteroidbelt.h"
#include "asteroid.h"
#include "blast.h"
#include "global.h"
#include "spaceship.h"
#include "collisions.h"

#include <stdlib.h>
#include <assert.h>

#define ASTEROID_CREATING_INTERVAL 5

typedef struct Node Node;

struct Node {
    Asteroid *asteroid;
    Node *previous;
    Node *next;
};
typedef Node *Link;

struct AsteroidBelt {
    Link head;
    Link tail;
};

void push_back_asteroid(AsteroidBelt *asteroid_belt, Asteroid *asteroid) {
    Link temp = (Node *)malloc(sizeof *temp);
    temp->asteroid = asteroid;
    temp->previous = 0;
    temp->next = 0;
    
    if (!asteroid_belt->tail) {
        asteroid_belt->head = temp;
        asteroid_belt->tail = temp;
    } else {
        asteroid_belt->tail->next = temp;
        temp->previous = asteroid_belt->tail;
        asteroid_belt->tail = temp;
    }
}

void push_new_asteroid(AsteroidBelt *asteroid_belt) {
    static float old_time = 0.0;
    
    // create and push back new asteroids every 5 seconds
    float current_time = al_current_time();
    if (current_time - old_time > ASTEROID_CREATING_INTERVAL) {
        old_time = current_time;
        Link temp = (Node *)malloc(sizeof *temp);
        push_back_asteroid(asteroid_belt, create_asteroid(1.0));
    }
}

Link erase_asteroid(AsteroidBelt *ab, Link node) {
    Link result = node->next;
    
    if (node->next)
        node->next->previous = node->previous;
    
    if (node->previous)
        node->previous->next = node->next;
    
    if (node == ab->head)
        ab->head = ab->head->next;
    
    if (node == ab->tail)
        ab->tail = ab->tail->previous;
    
    destroy_asteroid(node->asteroid);
    free(node);
    
    return result;
}

AsteroidBelt *create_asteroid_belt() {
    AsteroidBelt *ab = (AsteroidBelt *)malloc(sizeof *ab);

    assert(ab);

    ab->head = 0;
    ab->tail = 0;
    return ab;
}

void destroy_asteroid_belt(AsteroidBelt *asteroid_belt) {
    while (asteroid_belt->head) {
        Link temp = asteroid_belt->head->next;
        destroy_asteroid(asteroid_belt->head->asteroid);
        free(asteroid_belt->head);
        asteroid_belt->head = temp;
    }

    free(asteroid_belt);
}

void draw_asteroid_belt(AsteroidBelt *asteroid_belt) {
    Link current = asteroid_belt->head;
    while (current) {
        draw_asteroid(current->asteroid);
        current = current->next;
    }
}

void update_asteroid_belt(AsteroidBelt *asteroid_belt) {
    Link current = asteroid_belt->head;
    while (current) {
        update_asteroid(current->asteroid);
        current = current->next;
    }
    
    push_new_asteroid(asteroid_belt);
}

bool is_blast_hit_to_asteroid(AsteroidBelt *asteroid_belt, Blast *blast) {
    Link current = asteroid_belt->head;
    while (current) {
        Asteroid *asteroid = current->asteroid;
        int x1 = blast_x(blast) - BLAST_WIDTH / 2;
        int y1 = blast_y(blast) - BLAST_HEIGHT / 2;
        int w1 = BLAST_WIDTH;
        int h1 = BLAST_HEIGHT;
        int x2 = asteroid_x(asteroid) - ASTEROID_WIDTH / 2;
        int y2 = asteroid_y(asteroid) - ASTEROID_HEIGHT / 2;
        int w2 = ASTEROID_WIDTH;
        int h2 = ASTEROID_HEIGHT;
        if (is_bounding_box_collision(x1, y1, w1, h1, x2, y2, w2, h2)) {
            if (!is_asteroid_broken(asteroid)) {
                Asteroid *left = 0;
                Asteroid *right = 0;
                break_asteroid(asteroid, &left, &right);
                push_back_asteroid(asteroid_belt, left);
                push_back_asteroid(asteroid_belt, right);
            }
            erase_asteroid(asteroid_belt, current);
            return true;
        }
        current = current->next;
    }
    return false;
}

bool is_asteroid_hit_to_spaceship(AsteroidBelt *asteroid_belt, struct Spaceship *spaceship) {
    Link current = asteroid_belt->head;
    while (current) {
        Asteroid *asteroid = current->asteroid;
        int x1 = spaceship_x(spaceship) - SPACESHIP_WIDTH / 2;
        int y1 = spaceship_y(spaceship) - SPACESHIP_HEIGHT / 2;
        int w1 = SPACESHIP_WIDTH;
        int h1 = SPACESHIP_HEIGHT;
        int x2 = asteroid_x(asteroid) - ASTEROID_WIDTH / 2;
        int y2 = asteroid_y(asteroid) - ASTEROID_HEIGHT / 2;
        int w2 = ASTEROID_WIDTH;
        int h2 = ASTEROID_HEIGHT;

        if (is_bounding_box_collision(x1, y1, w1, h1, x2, y2, w2, h2))
            return true;

        current = current->next;
    }
    return false;
}