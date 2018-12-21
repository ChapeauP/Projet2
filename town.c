#include "town.h"
#include "tour.h"
#include "tsp.h"
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>


Town *createTown(const char *name, double x, double y){
	assert(name != NULL);
	Town *town = malloc(sizeof(Town));
	town->name = malloc(100*sizeof(char));
	strcpy(town->name,name);
	town->x = x;
	town->y = y;
	return town;
}

double getTownX(Town *town){
	assert(town != NULL);
	return town->x;
}

double getTownY(Town *town){
	assert(town != NULL);
	return town->y;
}

const char *getTownName(Town *town){
	assert(town != NULL);
	return town->name;
}

double distanceBetweenTowns(Town *town1, Town *town2){
	assert(town1 != NULL && town2 != NULL);
	return hypot((getTownX(town1)-getTownX(town2)),getTownY(town1)-getTownY(town2));
}

void freeTown(Town *town){
	assert(town != NULL);
	free(&town->name);
	free(town);
}