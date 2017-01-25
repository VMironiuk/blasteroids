#ifndef GLOBAL_H
#define GLOBAL_H

#define FPS 60

void error(const char *msg);
float degreesToRadians(float degrees);
int isBoundingBoxCollision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2);

#endif
