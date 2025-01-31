#include "bullet.h"

void createBullets(Bullet bullets[], int size) {
  for (int i = 0; i < size; i++) {
    bullets[i].isAlive = false;
    bullets[i].speed = BULLET_SPEED;
  }
}

void fireBullet(Bullet bullets[], int size, Ship ship) {
  for (int i = 0; i < size; i++) {
    if (!bullets[i].isAlive) {
      bullets[i].isAlive = true;
      bullets[i].angle = ship.angle;
      bullets[i].coorX = ship.coorX;
      bullets[i].coorY = ship.coorY;
      bullets[i].velocityX = ship.velocityX;
      bullets[i].velocityY = ship.velocityY;
      break;
    }
  }
}

void drawBullet(Bullet bullets[], int size, int screendWidth, int screenHeight) {
  for (int i = 0; i < size; i++) {
    if (bullets[i].isAlive) {
      al_draw_circle(
          bullets[i].coorX + screendWidth/2.0,
          bullets[i].coorY + screenHeight/2.0,
          1, al_map_rgb(255, 255, 255), 2);
    }
  }
}

void updateBullets(Bullet bullets[], int size) {
  for (int i = 0; i < size; i++) {
    if (bullets[i].isAlive) {
      //The foward velocity of the bullet + the velocity of the ship at the time the bullet is fired
      bullets[i].coorX +=
          bullets[i].speed * cos(bullets[i].angle * (M_PI / 180.0)) + bullets[i].velocityX;
      bullets[i].coorY -=
          bullets[i].speed * sin(bullets[i].angle * (M_PI / 180.0)) + bullets[i].velocityY;
      //Increase the time that the bullet has lived each iteration
      bullets[i].lifeTime++;
      
      if (bullets[i].lifeTime > BULLET_LIFE_TIME) {
        bullets[i].isAlive = false;
        bullets[i].lifeTime = 0;
      }
    }
  }
}
