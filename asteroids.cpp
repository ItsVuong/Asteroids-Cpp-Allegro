#include "object.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/bitmap.h>
#include <allegro5/bitmap_draw.h>
#include <allegro5/color.h>
#include <allegro5/display.h>
#include <allegro5/drawing.h>
#include <allegro5/events.h>
#include <allegro5/keyboard.h>
#include <allegro5/keycodes.h>
#include <allegro5/system.h>
#include <allegro5/timer.h>
#include <cmath>

const int WIDTH = 700;
const int HEIGHT = 700;
const float FPS = 60.0;

enum KEYS { UP, DOWN, LEFT, RIGHT, SPACE };

void InitShip(SpaceShip &ship);
void DrawShip(SpaceShip &ship);

int main() {
  bool running = true;
  bool redraw = true;
  bool keys[5] = {false, false, false, false, false};
  int pos_x = 0;
  int pos_y = 0;
  int angle = 0;
  float velocity = 0.1f;

  // Objects
  SpaceShip ship;

  // Allegro variables
  ALLEGRO_DISPLAY *display = NULL;
  ALLEGRO_TIMER *timer = NULL;
  ALLEGRO_EVENT_QUEUE *event_queue = NULL;
  ALLEGRO_FONT *font = NULL;
  ALLEGRO_BITMAP *image = NULL;
  ALLEGRO_BITMAP *image22 = NULL;

  // Initialization functions
  al_init();
  al_init_primitives_addon();
  al_install_keyboard();

  InitShip(ship);

  display = al_create_display(WIDTH, HEIGHT);
  event_queue = al_create_event_queue();
  timer = al_create_timer(1.0 / FPS);
  font = al_create_builtin_font();
  image = al_create_bitmap(40, 40);
  al_set_target_bitmap(image);
  DrawShip(ship);
  // al_clear_to_color(al_map_rgb(255, 255, 255));
  al_set_target_bitmap(al_get_backbuffer(display));

  al_register_event_source(event_queue, al_get_display_event_source(display));
  al_register_event_source(event_queue, al_get_timer_event_source(timer));
  al_register_event_source(event_queue, al_get_keyboard_event_source());
  al_start_timer(timer);
  while (running) {
    ALLEGRO_EVENT event;
    al_wait_for_event(event_queue, &event);
    if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
      switch (event.keyboard.keycode) {
      case ALLEGRO_KEY_UP:
        keys[UP] = true;
        break;
      case ALLEGRO_KEY_LEFT:
        keys[LEFT] = true;
        break;
      }
    }
    if (event.type == ALLEGRO_EVENT_KEY_UP) {
      switch (event.keyboard.keycode) {
      case ALLEGRO_KEY_UP:
        keys[UP] = false;
        break;
      case ALLEGRO_KEY_LEFT:
        keys[LEFT] = false;
        break;
      }
    }

    if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
      running = false;
    } else if (event.type == ALLEGRO_EVENT_TIMER) {
      if (keys[UP] && velocity < 7)
        velocity += 1;
      if (!keys[UP] && velocity > 0)
        velocity -= 1;
      if (keys[LEFT])
        angle += 1;

      if (velocity > 7)
        velocity = 7;
      if (velocity < 0)
        velocity = 0;
      if (angle <= -180)
        angle = 180;
      if (angle >= 180)
        angle = -180;
      pos_y -= velocity*sin(angle*(M_PI/180.0));
      pos_x += velocity*cos(angle*(M_PI/180.0));
      redraw = true;
    }

    if (redraw && al_is_event_queue_empty(event_queue)) {
      redraw = false;
      al_clear_to_color(al_map_rgb(0, 0, 0));
      // al_draw_bitmap(image, pos_x + 325, pos_y + 325, 0);
      al_draw_rotated_bitmap(image, ship.x / 2, ship.y / 2, pos_x + 325,
                             pos_y + 325, -angle*(M_PI/180.0), 0);
      al_draw_textf(font, al_map_rgb(255, 255, 255), 10, 10, 0,
                    "Allegro is working! %d %f %f", angle, sin(angle), cos(angle));
      al_flip_display();
    }
  }

  al_destroy_timer(timer);
  al_destroy_display(display);
  al_destroy_bitmap(image);
  al_destroy_event_queue(event_queue);
}

void InitShip(SpaceShip &ship) {
  ship.ID = PLAYERS;
  ship.x = 26;
  ship.y = 26;
  ship.lives = 3;
  ship.velocity = 7;
  ship.boundX = 6;
  ship.boundY = 7;
  ship.score = 0;
}

void DrawShip(SpaceShip &ship) {
  al_draw_triangle(0, ship.y, 0, 0, ship.x, ship.y/2,
                   al_map_rgb(255, 255, 255), 2);
}
