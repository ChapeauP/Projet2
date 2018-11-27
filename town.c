#include <stdio.h>
#include <math.h>
#include <assert.h>


typedef struct {
	char name;
	double x;
	double y;

}Town;

Town *createTown(const char *name, double x, double y){
	assert(name != NULL);
	Town *createTown = town;
	town->name = name;
	town->x = x;
	town->y = y;

}

double getTownX(Town *town){
	return town->x;
}

double getTown
