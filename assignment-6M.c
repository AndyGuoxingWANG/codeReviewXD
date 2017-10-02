#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<stdbool.h>

/**
 * build a struct of point
 * @param x the x-axis location of a point
 * @param y the y-axis location of a point
 */
typedef struct Point {
	double x;
	double y;
} Point;

/**
 * build a struct of circle
 * @param radius the radius of the circle
 * @param center the location of center point of the circle
 */
typedef struct Circle {
	double radius;
	Point center;
} Circle;

/**
 * build a struct of rectangle
 * @param origin the location of the top left point of the rectangle
 * @param width the length of the rectangle in x-axis
 * @param height the length of the rectangle in y-axis
 */
typedef struct Rectangle{
	Point origin;
	double width;
	double height;
} Rectangle;

/**
 * calculate the distance between two points
 * @param *point1 the pointer to the first point
 * @param *point2 the pointer to the second point
 * return the distance
 */
double distanceofPoints (Point *point1, Point *point2){
	double distance = sqrt(pow(point1->x-point2->x,2)+pow(point1->y-point2->y,2));
	return distance;
}

/**
 * determine if two circles intersect with each other
 * @param *circle1 the pointer to the information (center, radius) of the first circle
 * @param *circle2 the pointer to the information (center, radius) of the second circle
 * return boolean (true or false) if the two circles intersect
 */
bool intersectsCircles (Circle *circle1, Circle *circle2){
	//centerDistance calculates the distance between the two center points of the two circles
	double centerDistance = distanceofPoints (&circle1->center,&circle2->center);
	//radiiSum calculates the sum of the radius of the two circles
	double radiiSum = circle1->radius + circle2->radius;
	return (centerDistance < radiiSum ? true:false);
}

/**
 * getBoundingBox calculate the origin, width and height of a bounding box to a circle
 * @param *circle the pointer to the information (center, radius) of a circle
 * @param *boundingBox the pointer to the information (origin, width, and height) of the bounding box to the circle
 * return the pointer to the bounding box (*boundingBox)
 */
Rectangle getBoundingBox (Circle *circle, Rectangle *boundingBox){
	 boundingBox->origin.x = circle->center.x-circle->radius;
	 boundingBox->origin.y = circle->center.y+circle->radius;
	 boundingBox->width = 2 * circle->radius;
	 boundingBox->height = 2 * circle->radius;
	 return *boundingBox;
}

/**
 * test the intersectsCircles and getBoundingBox functions
 * return EXIT_SUCCESS
 */
int main (void){
	Circle circle1 = {
			10,
			{0,0}
	};

	Circle circle2 = {
			10,
			{21,0}
	};
	Circle circle3 = {
			10,
			{20,0}
	};
	Circle circle4 = {
			10,
			{19,0}
	};


	printf ("circle1 at %.0f, %.0f radius %.0f, and circle2 at %.0f,%.0f, radius %.0f: ",circle1.center.x, circle1.center.y,circle1.radius,circle2.center.x, circle2.center.y,circle2.radius);
	intersectsCircles(&circle1, &circle2) ? printf ("intersect\n") : printf (	"do not intersect\n");
	printf ("circle1 at %.0f, %.0f radius %.0f, and circle3 at %.0f,%.0f, radius %.0f: ",circle1.center.x, circle1.center.y,circle1.radius,circle3.center.x, circle3.center.y,circle3.radius);
	intersectsCircles(&circle1, &circle3) ? printf ("intersect\n") : printf (	"do not intersect\n");
	printf ("circle1 at %.0f, %.0f radius %.0f, and circle4 at %.0f,%.0f, radius %.0f: ",circle1.center.x, circle1.center.y,circle1.radius,circle4.center.x, circle4.center.y,circle4.radius);
	intersectsCircles(&circle1, &circle4) ? printf ("intersect\n\n") : printf (	"do not intersect\n");

	Rectangle boundingBox;
	getBoundingBox (&circle1,&boundingBox);
	printf ("circle1 bounding box\n origin: %.0f, %.0f\n width: %.0f,\n height: %.0f\n\n", boundingBox.origin.x, boundingBox.origin.y, boundingBox.width, boundingBox.height);
	getBoundingBox (&circle2,&boundingBox);
	printf ("circle2 bounding box\n origin: %.0f, %.0f\n width: %.0f,\n height: %.0f\n\n", boundingBox.origin.x, boundingBox.origin.y, boundingBox.width, boundingBox.height);
	getBoundingBox (&circle3,&boundingBox);
	printf ("circle3 bounding box\n origin: %.0f, %.0f\n width: %.0f,\n height: %.0f\n\n", boundingBox.origin.x, boundingBox.origin.y, boundingBox.width, boundingBox.height);
	getBoundingBox (&circle4,&boundingBox);
	printf ("circle4 bounding box\n origin: %.0f, %.0f\n width: %.0f,\n height: %.0f\n\n", boundingBox.origin.x, boundingBox.origin.y, boundingBox.width, boundingBox.height);

	return EXIT_SUCCESS;
}
