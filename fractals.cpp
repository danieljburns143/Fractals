// fractals.cpp
// Daniel Burns
// Lab 11

#include <iostream>
#include <unistd.h>
#include <cmath>
#include "gfxnew.h"
using namespace std;

void sierpinski(int, int, int, int, int, int); // prototype for drawing the sierpinski triangle
void drawtriangle(int, int, int, int, int, int); // prototype for drawing a triangle
void shrinkingsquares(double, double, double); // prototype for drawing the shrinking squares
void spiralsquares(double, double, double); // prototype for drawing the spiral squares
void circularlace(double, double, double); // prototype for drawing the circular lace
void snowflake(double, double, double); // prototype for drawing the snowflake
void tree(double, double, double, double); // prototype for drawing the tree
void fern(double, double, double, double); // prototype for drawing the fern
void spiralofspirals(double, double, double, double, double); // prototype for drawing the spiral of spirals

int main() {
	bool loop{true};
	char c{' '};
	int xwindowsize{900}, ywindowsize{900};
	gfx_open(xwindowsize, ywindowsize, "Fractals Window");
	gfx_clear();
	while (c != 'q') {
		c = gfx_wait();
		switch (c) {
			case '1':
				gfx_clear();
				sierpinski(10, 10, xwindowsize-10, 10, xwindowsize/2, ywindowsize-10);
				break;
			case '2':
				gfx_clear();
				shrinkingsquares(250, 250, 400); 
				break;
			case '3':
				gfx_clear();
				spiralsquares(1, 2, 0);
				break;
			case '4':
				gfx_clear();
				circularlace(450, 450, 300);
				break;
			case '5':
				gfx_clear();
				snowflake(450, 450, 300);
				break;
			case '6':
				gfx_clear();
				tree(450, 890, 250, 90);
				break;
			case '7':
				gfx_clear();
				fern(450, 890, 600, 90.05);
				break;
			case '8':
				gfx_clear();
				spiralofspirals(450, 450, .8, 0, 500);
				break;
		}
	}
}

// function for drawing the spiral of spirals
void spiralofspirals(double xc, double yc, double rad, double theta, double max) {
	if (rad >= max) { return; }
	gfx_point(xc, yc);
	spiralofspirals(xc, yc, 1, theta, rad / 3);
	theta = theta - M_PI / 4;
	rad = rad * 1.12;
	spiralofspirals(xc + rad * cos(theta), yc + rad * sin(theta), rad, theta, max);
}

// function for drawing the fern
void fern(double x, double y, double length, double theta) {
	if (length < 2) { return; }
	gfx_line(x, y, x - length * cos(theta * M_PI / 180), y - length * sin(theta * M_PI/180));
	for (int i{1}; i < 5; i++) {
		double x2 = x - length*i/4 * cos(theta * M_PI / 180);
		double y2 = y - length*i/4 * sin(theta * M_PI / 180);
		fern(x2, y2, length * .35, theta + 33);
		fern(x2, y2, length * .35, theta - 33);
	}
}

// function for drawing the tree
void tree(double xc, double yc, double length, double theta) {
	if (length < 3) { return; }
	double xc2 = xc - length * cos(theta * 3.14159 / 180);
	double yc2 = yc - length * sin(theta * 3.14159 / 180);
	gfx_line(xc, yc, xc - length * cos(theta * 3.14159 / 180), yc - length * sin(theta * 3.14159 / 180)); 
        tree(xc2, yc2, length*.68, theta + 35);
        tree(xc2, yc2, length*.68, theta - 35);
}

// function for drawing the snowflake
void snowflake(double xc, double yc, double length) {
	if (length < 1) { return; }
	for (int theta{54}; theta < 360; theta += 72) {
		double xc2 = xc - length * cos(theta * 3.14159 / 180);
		double yc2 = yc - length * sin(theta * 3.14159 / 180);
		gfx_line(xc, yc, xc2, yc2);
		snowflake(xc2, yc2, length/3);
	}
}

// function for drawing the sierpinski triangle
void sierpinski(int x1, int y1, int x2, int y2, int x3, int y3) {
	if (abs(x2-x1) < 5) { return; }
	drawtriangle(x1, y1, x2, y2, x3, y3);
	sierpinski(x1, y1, (x1+x2)/2, (y1+y2)/2, (x1+x3)/2, (y1+y3)/2);
	sierpinski((x1+x2)/2, (y1+y2)/2, x2, y2, (x2+x3)/2, (y2+y3)/2);
	sierpinski((x1+x3)/2, (y1+y3)/2, (x2+x3)/2, (y2+y3)/2, x3, y3);
}

// function to draw a triangle
void drawtriangle(int x1, int y1, int x2, int y2, int x3, int y3) {
	gfx_line(x1, y1, x2, y2);
	gfx_line(x2, y2, x3, y3);
	gfx_line(x3, y3, x1, y1);
}

// function for drawing the shrinking squares
void shrinkingsquares(double x, double y, double s) {
	if (s < 2) { return; }
	gfx_rectangle(x, y, s, s);
	double x2 = x+s;
	double y2 = y+s;
	s = s*.46;
	shrinkingsquares(x-s/2, y-s/2, s);
	shrinkingsquares(x2-s/2,y-s/2, s);
	shrinkingsquares(x2-s/2, y2-s/2, s);
	shrinkingsquares(x-s/2, y2-s/2, s);
}

// function for drawing the spiral squares
void spiralsquares(double s, double r, double theta) {
	if (r > 450) { return; }
	int initialx = 450, initialy = 450;
	gfx_rectangle(initialx + r * cos(theta * 3.14159 / 180), initialy + r * sin(theta * 3.14159 / 180), s, s);
	spiralsquares(s * 1.13, r * 1.148, theta - 35.8);
}

// function for drawing the circular lace
void circularlace(double x, double y, double radius) {
	double pi = M_PI;
	if (radius < 1) { return; }
	gfx_circle(x, y, radius);
	circularlace(x + radius * cos(0), y + radius*sin(0), radius / 3);
	circularlace(x + radius * cos(pi/3), y + radius*sin(pi/3), radius / 3);
	circularlace(x + radius * cos(2 * pi/3), y + radius*sin(2 * pi/3), radius / 3);
	circularlace(x + radius * cos(3 * pi/3), y + radius*sin(3 * pi/3), radius / 3);
	circularlace(x + radius * cos(4 * pi/3), y + radius*sin(4 * pi/3), radius / 3);
	circularlace(x + radius * cos(5 * pi/3), y + radius*sin(5 * pi/3), radius / 3);
}
