#include "Ledstrip.h"




/*Ledstrip::Ledstrip()
{
	al_init();
	al_init_primitives_addon();
	al_install_keyboard();
	//tmr = al_create_timer(1.0 / 30.0);
	//disp = al_create_display(400, 295);
	//queue = al_create_event_queue();
	//al_register_event_source(queue, al_get_keyboard_event_source());
	//al_register_event_source(queue, al_get_timer_event_source(tmr));

}*/

Ledstrip::Ledstrip(float dist)
{
al_init();
al_init_primitives_addon();
al_install_keyboard();
_dist = dist;
}

Ledstrip::~Ledstrip()
{
	al_shutdown_primitives_addon();
	al_destroy_event_queue(queue);
	al_destroy_display(disp);
	al_uninstall_keyboard();
	al_uninstall_system();
}

void Ledstrip::draw_strip(float x, float y, int num_led, const char *color, float w , int num_row  )
{
	float red=0, green=0, blue =0;
	_c = get_allegroColor(color);
/*	if (al_color_name_to_rgb(color ,&red, &green, &blue))
*	{
*		std::cout << red << green << blue;
*	}
*	al_draw_filled_circle(x, y, w, _c);
*/	al_clear_to_color(al_color_name("black"));
	float x_max = 10.0F *(float)num_row;
	//std::cout << x_max << std::endl;
	float y_max = y + (6.0F * (float)num_led);
	//std::cout << y_max << std::endl;


	for (int i = 0; i < num_led; i++)
	{

		for ( y;  y < y_max;  y += 6.0F)
		{
			//std::cout << "x: " << x << "y: " << y << std::endl;
			//al_draw_filled_circle(x, y, w, _c);
			if (num_row > 1)
			{
				for (float x2=20.0f; x2 <= 20 * num_row; x2+=20.0f)
				{
					al_draw_filled_circle(x2, y, w, _c);
				}
			}
		}
	}
}

void Ledstrip::draw_LedCircle(float start_x, float start_y, float dm)
{
	ALLEGRO_COLOR red = al_color_name("red");
	float x = dm / 2, y = 0, err = 0;
	while (x >= y)
	{
		al_draw_filled_circle(start_x + x, start_y + y, 5.0F, red);
		al_draw_filled_circle(start_x + y, start_y + x, 5.0F, red);
		al_draw_filled_circle(start_x - y, start_y + x, 5.0F, red);
		al_draw_filled_circle(start_x - x, start_y + y, 5.0F, red);
		al_draw_filled_circle(start_x - x, start_y - y, 5.0F, red);
		al_draw_filled_circle(start_x - y, start_y - x, 5.0F, red);
		al_draw_filled_circle(start_x + y, start_y - x, 5.0F, red);
		al_draw_filled_circle(start_x + x, start_y - y, 5.0F, red);

		if (err <= 0)
		{
			y += 1.0F;
			err += 2 * y + 1;
		}
		if (err > 0)
		{
			x -= 1.0F;
			err -= 2 * x + 1;
		}
	}
}


ALLEGRO_COLOR Ledstrip::get_allegroColor(const char* color)
{
	_c = al_color_name(color);
	return _c;
}

void Ledstrip::draw_blinking_strip(float x, float y, int num_led, const char* color, float w, int num_row, int cycle)
{
    for (int i = 0; i<= cycle; i++)
    {
        draw_strip(x, y, num_led, color, w, num_row);
        al_flip_display();
        al_rest(0.5);
        draw_strip(x, y, num_led, "black", w, num_row);
        al_flip_display();
        al_rest(0.5);
    }
}

void Ledstrip::draw_rotating_strip(float x, float y, int num_led, const char* color, const char* ncolor, int great, float w, int num_row)
{
    float y_max = y +(12.0f*(float)num_led);
    float x_max = 30*(float)num_row;
    ALLEGRO_COLOR c = get_allegroColor(color);
    ALLEGRO_COLOR nc = get_allegroColor(ncolor);
   // draw_strip(x, y, num_led, color, w, num_row);
    //al_flip_display();

    for (x; x <=x_max; x +=30.0f)
    {
        //std::cout << x << std::endl;
        float _x = x;
        int t = (int)_x % 20;
        //std::cout << "t: " << t << std::endl;
        if (t != 0)
        {
           //std::cout << "ungerade" << std::endl;
            for (float f = y; f < y_max-3; f += 12.0f)
            {
                x = (float)x;
                al_draw_filled_circle(x, f, w, c);
                al_draw_filled_circle(x, f+12.0f, w, c);
                al_draw_filled_circle(x, f+24.0f, w, c);
                al_rest(0.3);
                al_flip_display();
            }
        }
        else
        {
            //std:: cout << "gerade" << std::endl;
            for (float f = (y_max +12.0f); f >= (y + 24.0f); f-= 12.0f)
            {
                //x= (float)x;
               al_draw_filled_circle(x, f, w, c);
                al_draw_filled_circle(x, f-12.0f, w, c);
                al_draw_filled_circle(x, f-24.0f, w, c);
                al_rest(0.3);
                al_flip_display();
            }
        }
    }

}

void Ledstrip::draw_Circle(float cx, float cy, float r, const char * color, float angle)
{
	ALLEGRO_COLOR c = get_allegroColor(color);
	bitmp = al_create_bitmap(6, 6);
	al_set_target_bitmap(bitmp);
	
	al_clear_to_color(c);
	//al_draw_pixel(0,6, al_color_name("red"));
	al_set_target_bitmap(al_get_backbuffer(disp));
	for (float f = 0.0f; f <= 360.0f; f+=angle)
	{
		float a = f *( ALLEGRO_PI / 180);
		float x = (r*std::cos(a)) + cx;
		float y = (r*std::sin(a)) + cy;
		
		al_draw_rotated_bitmap(bitmp, 3, 3, x, y, a, 0);
	}
	al_flip_display();

}

 