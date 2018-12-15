#include "town.h"
#include "tour.h"
#include "tsp.h"
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>


Town *createTown(const char *name, double x, double y){
	assert(name != NULL);
	Town *town = (Town*) malloc(sizeof(Town));
	town->name = malloc(100*sizeof(char));
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
	printf("bla\n");
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