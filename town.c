#include "town.h"
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>

struct Town_t{
	const char *name;
	double x;
	double y;

};



Town *createTown(const char *name, double x, double y){
	assert(name != NULL);
	Town *town = (Town*) malloc(sizeof(Town));
	town->name = malloc(sizeof(name));
	town->name = name;
	town->x = x;
	town->y = y;
	return town;
}

double getTownX(Town *town){
	return town->x;
}

double getTownY(Town *town){
	return town->y;
}

const char *getTownName(Town *town){
	return town->name;
}

double distanceBetweenTowns(Town *town1, Town *town2){
	double distance;

	distance = hypot((town2->x-town1->x), (town2->y-town1->y));
	return distance;
}

void freeTown(Town *town){
	free(&town->name);
	free(town);
}
