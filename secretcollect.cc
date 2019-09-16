#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <iostream>
using namespace std;

//function to detect collision
//paramaters are x & y coordinates of top left corner of first box, then its width and height
//then same for other box
int bounding_box_collision(int b1_x, int b1_y, int b1_w, int b1_h, int b2_x, int b2_y, int b2_w, int b2_h);
int wall3_collision2(int w3_x, int w3_y, int w3_w, int w3_h, int b1_x, int b1_y, int b1_w, int b1_h);
int wall4_collision3(int w4_x, int w4_y, int w4_w, int w4_h, int b1_x, int b1_y, int b1_w, int b1_h);
//using constants in this game so you have sensible words, not unknown numbers in code
const float FPS = 60;
const int SCREEN_W = 640;
const int SCREEN_H = 480;
const int BOUNCER_SIZE = 32;

//an enumeration is like a user-defined variable, with all the given values it can hold
enum MYKEYS {
   KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT
};
enum MYKEYS2 {
   KEY_W, KEY_S, KEY_A, KEY_D
};

 
int main(int argc, char **argv)
{
   ALLEGRO_DISPLAY *display = NULL;
   ALLEGRO_EVENT_QUEUE *event_queue = NULL;
   ALLEGRO_TIMER *timer = NULL;
   ALLEGRO_BITMAP *bouncer = NULL;
   float bouncer_x = 586;
   float bouncer_y = 12;
   bool key[4] = { false, false, false, false };
   ALLEGRO_BITMAP *bouncer2 = NULL;
   float bouncer2_x = 30;
   float bouncer2_y = 40;
   ALLEGRO_BITMAP *wall = NULL;
   ALLEGRO_BITMAP *wall2 = NULL;
   ALLEGRO_BITMAP *wall3 = NULL;
   ALLEGRO_BITMAP *wall4 = NULL;
   float wall_x = 80;
   float wall_y = 120;
   float wall2_x = 450;
   float wall2_y = 50;
   float wall3_x = 270;
   float wall3_y = 0;
   float wall4_x = 270;
   float wall4_y = 290;

   bool key2[4] = { false, false, false, false };
   bool redraw = true;
   bool doexit = false;
 
   //including some error messages to help debug
   if(!al_init()) {
      fprintf(stderr, "failed to initialize allegro!\n");
      return -1;
   }
 
   if(!al_install_keyboard()) {
      fprintf(stderr, "failed to initialize the keyboard!\n");
      return -1;
   } 
 
   timer = al_create_timer(1.0 / FPS);
   if(!timer) {
      fprintf(stderr, "failed to create timer!\n");
      return -1;
   }
 
   display = al_create_display(SCREEN_W, SCREEN_H);
   if(!display) {
      fprintf(stderr, "failed to create display!\n");
      al_destroy_timer(timer);
      return -1;
   }

   //hook up fonts for on-screen text
   al_init_font_addon(); 
   al_init_ttf_addon();
   ALLEGRO_FONT *font = al_load_ttf_font("Candara.ttf",72,0 );
 
   //set up the two squares
   bouncer = al_create_bitmap(BOUNCER_SIZE, BOUNCER_SIZE);
  
   bouncer2 = al_create_bitmap(BOUNCER_SIZE, BOUNCER_SIZE);

   wall = al_create_bitmap(150,300);
 
   al_set_target_bitmap(wall);
   
   al_clear_to_color(al_map_rgb(0,255,255));

   wall2 = al_create_bitmap(100, 375);

   al_set_target_bitmap(wall2);

   al_clear_to_color(al_map_rgb(0,255,255));
   
   wall3 = al_create_bitmap(125,250);

   al_set_target_bitmap(wall3);

   al_clear_to_color(al_map_rgb(0,255,255));

   wall4 = al_create_bitmap(125,500);

   al_set_target_bitmap(wall4);

   al_clear_to_color(al_map_rgb(0,255,255));   
   
   al_set_target_bitmap(bouncer);
 
   al_clear_to_color(al_map_rgb(255, 255, 0));

   al_set_target_bitmap(bouncer2);
 
   al_clear_to_color(al_map_rgb(0, 200, 255));
 
   al_set_target_bitmap(al_get_backbuffer(display));
 
   //set up your event queue
   event_queue = al_create_event_queue();
   if(!event_queue) {
      fprintf(stderr, "failed to create event_queue!\n");
      al_destroy_bitmap(bouncer);
      al_destroy_display(display);
      al_destroy_timer(timer);
      return -1;
   }
 
   al_register_event_source(event_queue, al_get_display_event_source(display));
 
   al_register_event_source(event_queue, al_get_timer_event_source(timer));
 
   al_register_event_source(event_queue, al_get_keyboard_event_source());
 
   //draw the initial screen, start up the timer
   al_clear_to_color(al_map_rgb(0,0,0));
 
   al_flip_display();
 
   al_start_timer(timer);
 
   while(!doexit) 
   { cout<<bouncer_x<<"  "<<bouncer_y<<endl;
      ALLEGRO_EVENT ev;
      al_wait_for_event(event_queue, &ev);
 	  //if a clock ticks, check if we should be moving a square (by checking key or key2)
      if(ev.type == ALLEGRO_EVENT_TIMER) {
         if((key[KEY_UP]&& !((bouncer_x > 50) && (bouncer_x < 228) && (bouncer_y < 425) && (bouncer_y > 84)) && !((bouncer_x + 32> 452) && (bouncer_x < 552) && (bouncer_y-2 < 427) && (bouncer_y > 390)))){
            bouncer_y -= 4.0;
         }
		 
 
         if((key[KEY_DOWN] && !((bouncer_x < 232) && (bouncer_x > 48) && (bouncer_y < 90) &&(bouncer_y > 80)) && !((bouncer_x < 552) && (bouncer_x > 420) && (bouncer_y < 20) &&(bouncer_y+32 > 44)))){ 
            bouncer_y += 4.0;
         }
 
		 if((key[KEY_LEFT] && !((bouncer_x < 235) && (bouncer_x > 200) && (bouncer_y < 420) && (bouncer_y > 88)) && !((bouncer_x < 555) && (bouncer_x > 520) && (bouncer_y < 424) && (bouncer_y > 20)))){
            bouncer_x -= 4.0;
         }
 
         if((key[KEY_RIGHT] && !((bouncer_x+32 > 72) && (bouncer_x < 80) && (bouncer_y < 420) && (bouncer_y+32 > 120)) && !((bouncer_x > 415) && (bouncer_x < 552) && (bouncer_y < 427) && (bouncer_y > 16)))){
            bouncer_x += 4.0;
         }

		
 
         redraw = true;
      }
	  //kill program if window "X" has been clicked
      else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
         break;
      }

	  //update key/key2 if a key has been pressed
      else if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {
         switch(ev.keyboard.keycode) {

            case ALLEGRO_KEY_UP:
               key[KEY_UP] = true;
               break;
 
            case ALLEGRO_KEY_DOWN:
               key[KEY_DOWN] = true;
               break;
 
            case ALLEGRO_KEY_LEFT: 
               key[KEY_LEFT] = true;
               break;
 
            case ALLEGRO_KEY_RIGHT:
               key[KEY_RIGHT] = true;
               break;

	
			   
         }
      }
	  //update key/key2 if a key has been released
      else if(ev.type == ALLEGRO_EVENT_KEY_UP) {
         switch(ev.keyboard.keycode) {

            case ALLEGRO_KEY_UP:
               key[KEY_UP] = false;
               break;
 
            case ALLEGRO_KEY_DOWN:
               key[KEY_DOWN] = false;
               break;
 
            case ALLEGRO_KEY_LEFT: 
               key[KEY_LEFT] = false;
               break;
 
            case ALLEGRO_KEY_RIGHT:
               key[KEY_RIGHT] = false;
               break;

	

			 
         }
      }
     

			//take all the above information and update screen
         al_clear_to_color(al_map_rgb(0,0,0));
 
         al_draw_bitmap(bouncer, bouncer_x, bouncer_y, 0);
 
		 al_draw_bitmap(bouncer2, bouncer2_x, bouncer2_y, 0);

		 al_draw_bitmap(wall, wall_x, wall_y, 0); 

		 al_draw_bitmap(wall2, wall2_x, wall2_y, 0);
		 
		 al_draw_bitmap(wall3, wall3_x, wall3_y, 0);

		 al_draw_bitmap(wall4, wall4_x, wall4_y, 0);

		 if(  wall3_collision2( bouncer_x, bouncer_y, 32,32,wall3_x, wall3_y, 125,250)){
			 bouncer_x= 586;
			 bouncer_y = 12;
		 }

		  if(  wall4_collision3( bouncer_x, bouncer_y, 32,32, wall4_x, wall4_y, 125,500)){
			 bouncer_x= 586;
			 bouncer_y = 12;
		 }
		 
			 //call the bounding box function. if it returns 1, print out your collision message
		 if (bounding_box_collision(bouncer_x, bouncer_y, 32, 32, bouncer2_x, bouncer2_y, 32, 32))
			 al_draw_text(font, al_map_rgb(255,255,255), 640/2, (480/4),ALLEGRO_ALIGN_CENTRE, "SECRET COLLECT!!!!");

         al_flip_display();
     
   }
 
   al_destroy_bitmap(bouncer);
   al_destroy_timer(timer);
   al_destroy_display(display);
   al_destroy_event_queue(event_queue);
 
   return 0;
}

int bounding_box_collision(int b1_x, int b1_y, int b1_w, int b1_h, int b2_x, int b2_y, int b2_w, int b2_h)
{
    if ((b1_x > b2_x + b2_w - 1) || // is b1 on the right side of b2?
        (b1_y > b2_y + b2_h - 1) || // is b1 under b2?
        (b2_x > b1_x + b1_w - 1) || // is b2 on the right side of b1?
        (b2_y > b1_y + b1_h - 1))   // is b2 under b1?
    {
        // no collision
        return 0;
    }
 
    // collision
    return 1;
}

int wall3_collision2(int w3_x, int w3_y, int w3_w, int w3_h, int b1_x, int b1_y, int b1_w, int b1_h)
{
    if ((w3_x > b1_x + b1_w - 1) || // is b1 on the right side of b2?
        (w3_y > b1_y + b1_h - 1) || // is b1 under b2?
        (b1_x > w3_x + w3_w - 1) || // is b2 on the right side of b1?
        (b1_y > w3_y + w3_h - 1))   // is b2 under b1?
    {
        // no collision
        return 0;
    }
 
    // collision
    return 1;
}

int wall4_collision3(int w4_x, int w4_y, int w4_w, int w4_h, int b1_x, int b1_y, int b1_w, int b1_h)
{
    if ((w4_x > b1_x + b1_w - 1) || // is b1 on the right side of b2?
        (w4_y > b1_y + b1_h - 1) || // is b1 under b2?
        (b1_x > w4_x + w4_w - 1) || // is b2 on the right side of b1?
        (b1_y > w4_y + w4_h - 1))   // is b2 under b1?
    {
        // no collision
        return 0;
    }
 
    // collision
    return 1;
}

