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
      break;
    }
  }
}

void drawBullet(Bullet bullets[], int size) {
  for (int i = 0; i < size; i++) {
    if (bullets[i].isAlive) {
      al_draw_circle(bullets[i].coorX + 500 +2* cos(bullets[i].angle * (M_PI / 180.0)), 
                     bullets[i].coorY + 350 -2* sin(bullets[i].angle * (M_PI / 180.0)), 1,
                     al_map_rgb(255, 255, 255), 2);
    }
  }
}

void updateBullets(Bullet bullets[], int size){
  for (int i = 0; i < size; i++) {
    if(bullets[i].isAlive){
      bullets[i].coorX += bullets[i].speed * cos(bullets[i].angle * (M_PI / 180.0));
      bullets[i].coorY -= bullets[i].speed * sin(bullets[i].angle * (M_PI / 180.0));
    }
  }
}
