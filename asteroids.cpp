#include <allegro5/allegro.h>
#include <allegro5/display.h>
#include <allegro5/events.h>
#include <allegro5/system.h>
#include <allegro5/timer.h>
#include <allegro5/allegro_font.h>
#include "object.h"

const int WIDTH = 700;
const int HEIGHT = 700;
const float FPS = 60.0;

int main(){
  bool running = true;
  //Objects
  SpaceShip ship;

  //Allegro variables
  ALLEGRO_DISPLAY *display = NULL;
  ALLEGRO_TIMER *timer = NULL;
  ALLEGRO_EVENT_QUEUE *event_queue = NULL;
  ALLEGRO_FONT *font = NULL;

  //Initialization functions
  al_init();
  display = al_create_display(WIDTH, HEIGHT);
  event_queue = al_create_event_queue();
  timer = al_create_timer(1.0/FPS);
  font = al_create_builtin_font();

  al_register_event_source(event_queue, al_get_display_event_source(display));
  al_register_event_source(event_queue, al_get_timer_event_source(timer));
  al_start_timer(timer);

  while(running){
    ALLEGRO_EVENT event;
    al_wait_for_event(event_queue, &event);
    if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
      running = false;
    }
    al_draw_text(font, al_map_rgb(255, 255, 255), WIDTH/2, HEIGHT/2, 0, "Allegro is working!");
    al_flip_display();
  }

  al_destroy_timer(timer);
  al_destroy_display(display);
  al_destroy_event_queue(event_queue);
}

