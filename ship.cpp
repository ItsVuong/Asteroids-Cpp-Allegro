#include "ship.h"
#include <allegro5/allegro_primitives.h>
#include <allegro5/color.h>
void createShip(Ship &ship) {
  ship.width = 40;
  ship.height = 30;
  ship.coorX = 0.0;
  ship.coorY = 0.0;
  ship.angle = 0.0;

  ship.acceleration = 0;
  ship.velocityX = 0.0;
  ship.velocityY = 0.0;

  ship.lives = 3;
  ship.score = 0;
  ship.boundX = 6;
  ship.boundY = 7;
}

void drawShip(Ship &ship) {
  //Because the thinkness of the outline is 3, the 1.5 is so that the lines do not go out of the bitmap
  //Filled the ship with black
  al_draw_filled_triangle(1.5, ship.height - 1.5, 1.5, 0 + 1.5, ship.width,
                          ship.height / 2.0, al_map_rgb(0, 0, 0));
  //Draw the outline of the ship
  al_draw_triangle(1.5, ship.height - 1.5, 1.5, 0 + 1.5, ship.width,
                   ship.height / 2.0, al_map_rgb(255, 255, 255), 3);
}

void rotate_right(Ship &ship) {
  ship.angle -= 2.3;
  if (ship.angle < -180)
    ship.angle = 180;
}
void rotate_left(Ship &ship) {
  ship.angle += 2.3;
  if (ship.angle > 180)
    ship.angle = -180;
}
void move_ship(Ship &ship) {
  // accelerator: reach max speed at 9/60 frame (without friction)
  if (ship.acceleration < 0.15) {
    ship.acceleration += 0.05;
  }
  // Capping the speed at 9 pixel/frame
  float speed =
      sqrt(ship.velocityX * ship.velocityX + ship.velocityY * ship.velocityY);
  if (speed < 7) {
    ship.velocityX += ship.acceleration * cos(ship.angle * (M_PI / 180.0));
    ship.velocityY += ship.acceleration * sin(ship.angle * (M_PI / 180.0));
  }
}

void friction(Ship &ship) {
  // Apply friction
  ship.velocityX *= 0.991;
  ship.velocityY *= 0.991;
}
