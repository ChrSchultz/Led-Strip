#include "Ledstrip.h"
/*include <allegro5/allegro5.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_primitives.h>*/


//Ledstrip *strip = new Ledstrip();
const char *col[10] = { "white",  "yellow", "orange", "red", "purple", "violet", "blue", "forestgreen", "green", "olivedrab" };

int main(int argc, char **argv)
{
	Ledstrip* npixel = new Ledstrip();

	npixel->queue = al_create_event_queue();
	npixel->tmr = al_create_timer(1.0 / 30.0);
	al_set_new_display_flags(ALLEGRO_WINDOWED|ALLEGRO_RESIZABLE | ALLEGRO_OPENGL_3_0);
	//al_set_new_display_flags(ALLEGRO_RESIZABLE);
	npixel->disp = al_create_display(600, 400);

	al_register_event_source(npixel->queue, al_get_keyboard_event_source());
	al_register_event_source(npixel->queue, al_get_timer_event_source(npixel->tmr));
	al_register_event_source(npixel->queue, al_get_display_event_source(npixel->disp));


	ALLEGRO_EVENT event;

	bool redraw = true;




	al_start_timer(npixel->tmr);
	while (1)
	{   al_wait_for_event(npixel->queue, &event);
		if (event.type == ALLEGRO_EVENT_TIMER)
			redraw = true;
		else if ((event.type == ALLEGRO_EVENT_KEY_DOWN) || (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE))
			break;
		if (redraw && al_is_event_queue_empty(npixel->queue))
		{
			for (int i = 0; i < 9; i+=2)
			{
				/*npixel->draw_strip(10.0, 10.0, 20,  col[i]);
				al_flip_display();
				al_rest(5.0);
				al_clear_to_color(al_color_name("black"));
				npixel->draw_LedCircle(200.0, 150.0,200.0);
                al_flip_display();
                al_rest(5.0);
				al_clear_to_color(al_color_name("black"));
				npixel->draw_blinking_strip(10.0f, 10.0f, 20, "red");
				al_flip_display();
				al_rest(5.0);*/


				//npixel->draw_rotating_strip(10.0f, 10.0f, 20, col[i], col[i+1]);
				//al_flip_display();
				//npixel->draw_Circle(300.0f, 200.0f, 100.0f, "blue");
				npixel->draw_rotating_mcolorstrip(10,10,20,col[i],col[i+1]);


			redraw = false;
            }
        }
    }

	return 0;
}
