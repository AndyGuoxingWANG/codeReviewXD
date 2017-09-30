/*
 * assignment-6.c
 *
 *  Created on: Sep 25, 2017
 *      Author: Audrey
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

/** struct that defines a Point,  */
typedef struct Point {
	double x;
	double y;
} Point;

/** struct that defines a Circle*/
typedef struct Circle {
	double radius;
	Point center;
} Circle;

/** struct that defines a Rectangle*/
typedef struct Rectangle {
	Point origin; // top left corner
	double width;
	double height;
} Rectangle;


/**
 * This function calculate the distance of two Points
 * @param a Point a
 * @param b Point b
 * @return the distance of Points a and b
 */
double distanceofPoints(const Point* a, const Point* b) {

	double xDiff = a->x - b->x; // difference of x between Point a and b
	double yDiff = a->y - b->y; // difference of y between Point a and b
	double distance = sqrt(xDiff * xDiff + yDiff * yDiff);

	return distance;
}


/**
 * This function check if two Circles intersect
 * @param *circle1 pointer to circle1
 * @param *circle2 pointer to circle2
 * @return if the two Circles intersect
 */
bool intersectsCircles(const Circle* circle1, const Circle* circle2) {

	Point center1 = circle1->center; // center of circle1
	Point center2 = circle2->center; // center of circle2
	// calculate distance between center1 and center2
	double distance = distanceofPoints(&center1, &center2);

	//if distance is less than the sum of two radius, do not intersect
	//otherwise, intersect
	return (distance < circle1->radius + circle2->radius);
}


/**
 * This function generate the bounding box of a given Circle
 * @param *circle pointer to the given circle to get bounding box
 * @param *boundingBox pointer to an uninitiated Rectangle to store return bounding box
 * @return a pointer to the generated bounding box
 */
Rectangle* getBoundingBox(const Circle* circle, Rectangle* boundingBox) {

	double originX = circle->center.x - circle->radius; //x of top left corner point
	double originY = circle->center.y + circle->radius; //y of top left corner point
	Point origin = { //top left point
		originX,
		originY
	};

	double width = (circle->radius) * 2;
	double height = (circle->radius) * 2;

	boundingBox->origin = origin;
	boundingBox->width = width;
	boundingBox->height = height;

	return boundingBox;
}


/**
 * This function tests intersectsCircles and getBoundingBox
 */
int main(void) {

	Circle circle1 = { // circle1 at 0, 0, radius 10
		10,
		{0,0}
	};

	Circle circle2 = { // circle2 at 21, 0, radius 10
		10,
		{21,0}
	};

	Circle circle3 = { // circle3 at 20, 0, radius 10
		10,
		{20,0}
	};

	Circle circle4 = { // circle4 at 19, 0, radius 10
		10,
		{19,0}
	};

	//test intersectsCircles
	bool test1 = intersectsCircles(&circle1, &circle2);
	bool test2 = intersectsCircles(&circle1, &circle3);
	bool test3 = intersectsCircles(&circle1, &circle4);

	//print results of intersectsCircles tests
	printf("circle1 at 0,0 radius 10 and circle2 at 21,0 radius 10: %s\n",
			test1 ? "intersect" : "do not intersect");
	printf("circle1 at 0,0 radius 10 and circle3 at 20,0 radius 10: %s\n",
			test2 ? "intersect" : "do not intersect");
	printf("circle1 at 0,0 radius 10 and circle4 at 19,0 radius 10: %s\n",
			test3 ? "intersect" : "do not intersect");

	printf("\n");

	//test getBoundingBox
	Rectangle boundingBox1;
	Rectangle boundingBox2;
	Rectangle boundingBox3;
	Rectangle boundingBox4;

	Rectangle* rec1 = getBoundingBox(&circle1, &boundingBox1);
	Rectangle* rec2 = getBoundingBox(&circle2, &boundingBox2);
	Rectangle* rec3 = getBoundingBox(&circle3, &boundingBox3);
	Rectangle* rec4 = getBoundingBox(&circle4, &boundingBox4);

	//print results of getBoundingBox
	printf("bounding box of circle1: origin x:%5.1f y:%.1f, width:%.1f, height:%.1f\n",
				rec1->origin.x, rec1->origin.y, rec1->width, rec1->height);
	printf("bounding box of circle2: origin x:%5.1f y:%.1f, width:%.1f, height:%.1f\n",
				rec2->origin.x, rec2->origin.y, rec2->width, rec2->height);
	printf("bounding box of circle3: origin x:%5.1f y:%.1f, width:%.1f, height:%.1f\n",
				rec3->origin.x, rec3->origin.y, rec3->width, rec3->height);
	printf("bounding box of circle4: origin x:%5.1f y:%.1f, width:%.1f, height:%.1f\n",
				rec4->origin.x, rec4->origin.y, rec4->width, rec4->height);

	return EXIT_SUCCESS;
}
