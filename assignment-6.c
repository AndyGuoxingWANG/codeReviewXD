/*
 * assignment-6.c
 *
 *  Created on: Sep 30, 2017
 *      Author: esandar
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<math.h>

/** Define and typedef a struct Point */
typedef struct {
	double x;  // x-coordinate in Cartsian space
	double y;  // y-coordinate in Carstian space
} Point;

/** Define and typedef a struct Circle */
typedef struct {
	double radius;	//radius of the circle
	Point center;	//coordinate of the center in Carstian space
} Circle;

/** Define and typedef a struct Rectangle */
typedef struct {
	Point origin;	//coordinate of top left corner of the rectangle
	double width;	//width of the rectangle
	double height;	//height of the rectangle
} Rectangle;

/**
 * Function to compute the distance between two points
 * @Param point1 the struct point1
 * @Param point2 the struct point2
 * @return an double value of the distance
 */
double distanceofPoints (Point *point1, Point *point2) {
	double deltax = ((*point1).x - (*point2).x), deltay = ((*point1).y - (*point2).y);
	//Compute the difference in x and y
	return sqrt(deltax * deltax + deltay * deltay);
}

/**
 * Function to compute if two circles are intersect
 * @Param circle1 the first circle
 * @Param circle2 the second circle
 * @return true if intersects, false otherwise
 */
bool intersectsCircles (Circle *circle1, Circle *circle2) {
	return (circle1->radius + circle2->radius) > distanceofPoints (&(circle1->center), &(circle2->center));
	//Make decision if two circles are intersect
}
/**
 * Function to sets the fields of Rectangle to the bounding box that encloses the circle
 * @Param circle the circle for computing
 * @Param rectangle the rectangle for computing
 * @return a pointer to the Rectangle result parameter
 */

Rectangle *getBoundingBox(const Circle *circle, Rectangle *boundingbox) {
	boundingbox->origin.x = (circle->center.x - circle->radius);
	boundingbox->origin.y = (circle->center.y + circle->radius);
	boundingbox->height = 2 * circle->radius;
	boundingbox->width = 2 * circle->radius;
	return boundingbox;
}

int main() {
	Circle circle1 = {
			10,
			{0, 0}
	};
	Circle circle2 = {
			10,
			{21, 0}
	};
	Circle circle3 = {
			10,
			{20, 0}
	};
	Circle circle4 = {
			10,
			{19, 0}
	};

	bool test = 0;
	//compare circle 1 and circle 2
	test = intersectCircles(&circle1, &circle2);
	printf("circle1 and circle2:");
	if (test == 1) {
		printf("intersect\n");
	} else {printf("do not intersect\n");
	}
	//compare circle 1 and circle 3
	test = intersectCircles(&circle1, &circle3);
	printf("circle1 and circle3:");
	if (test == 1) {
			printf("intersect\n");
	} else {printf("do not intersect\n");
	}
	//compare circle 1 and circle 4
	test = intersectCircles(&circle1, &circle4);
	printf("circle1 and circle4:");
	if (test == 1) {
			printf("intersect\n");
	} else {printf("do not intersect\n");
	}
	Rectangle boundingbox;
	boundingbox = *getBoundingBox(&circle1, &boundingbox);
	printf("origin: (%f,%f), width: %f, height: %f for circle1", boundingbox.origin.x,
			boundingbox.origin.y, boundingbox.width, boundingbox.height);

}
