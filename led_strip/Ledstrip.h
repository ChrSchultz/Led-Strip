#pragma once
#if!defined LEDSTRIP_H
#define LEDSTRIP_H

#include<iostream>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_color.h>
#include <iostream>
#include <cmath>

class Ledstrip
{
public:
	//Ledstrip();
	Ledstrip(float dist = 20.0f);
	~Ledstrip();
	void draw_strip(float x, float y, int num_led, const char* color, float w = 5.0F, int num_row = 2);
	void draw_LedCircle(float start_x, float start_y, float dm);
	void draw_blinking_strip(float x , float y, int num_led, const char* color, float w = 5.0f, int num_row = 2, int cycle = 10);
	void draw_rotating_strip(float x, float y, int num_led, const char* color, const char* ncolor, int great = 3, float w = 5.0f, int num_row = 2);
	void draw_Circle(float cx, float cy, float r, const char* color, float angle = 5.0f);

	ALLEGRO_DISPLAY *disp = NULL;
	ALLEGRO_EVENT_QUEUE *queue = NULL;
	ALLEGRO_TIMER *tmr = NULL;
	ALLEGRO_BITMAP *bitmp;

private:
	ALLEGRO_COLOR get_allegroColor(const char* color);
	char * _col;
	ALLEGRO_COLOR _c;
	float _dist;
};
#endif
