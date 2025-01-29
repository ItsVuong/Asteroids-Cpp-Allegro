#ifndef _BULLET_
#define _BULLET_

#include "ship.h"
#include <allegro5/allegro_primitives.h>
#include <allegro5/color.h>
#include <cmath>

#define BULLET_SPEED 16.0;
struct Bullet{
  double coorX;
  double coorY;
  bool isAlive;
  double speed;
  double angle;
};

void createBullets(Bullet bullets[], int size); 
void fireBullet(Bullet bullets[], int size, Ship ship);
void drawBullet(Bullet bullets[], int size);
void updateBullets(Bullet bullets[], int size);
#endif
