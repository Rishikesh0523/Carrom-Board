#include "headers/Math.h"
#include <cmath>

double distanceSq(double x1, double y1, double x2, double y2) {

	return (x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1);

}

double distance(double x1, double y1, double x2, double y2) {

	return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));

}