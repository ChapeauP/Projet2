#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include "town.h"
#include "tour.h"
#include "tsp.h"


Tour *heuristic1(Tour *tour){
	assert(tour != NULL);
	Tour *t=createEmptyTour();
	addTownAtTourEnd(t,getTownAtPosition(tour,getTourStartPosition(tour)));
	addTownAfterTourPosition(t,getTourStartPosition(t),getTownAtPosition(tour,getNextTourPosition(tour,getTourStartPosition(tour))));
	double dis_ref;
	double dis;
	TourPosition *towntmp;
	TourPosition *towntmp2;
	TourPosition *town_closest;
	towntmp = NULL;
	towntmp2 = NULL;
	town_closest = NULL;
	towntmp = getNextTourPosition(tour, getTourStartPosition(tour));
	
	while(towntmp != NULL){
		towntmp2 = getTourStartPosition(t);
		dis_ref = distanceBetweenTowns(getTownAtPosition(t,towntmp2),getTownAtPosition(tour, towntmp));
		town_closest = towntmp2;
		while(getNextTourPosition(t, towntmp2) != NULL){
			towntmp2 = getNextTourPosition(t, towntmp2);
			dis = distanceBetweenTowns(getTownAtPosition(t, towntmp2), getTownAtPosition(tour, towntmp));
			if(dis < dis_ref){
				town_closest = towntmp2;
				dis_ref = dis;
			}
		}
		addTownAfterTourPosition(t,town_closest, getTownAtPosition(tour, towntmp));
		towntmp = getNextTourPosition(tour, towntmp);
	}
	return t;
}

int main(){
	Tour *t1 = createTourFromFile("xy-belgium-towns.csv");

	printf("%d\n",t1->tour_size);
	printf("%s\n",getTownName(getTownAtPosition(t1,getTourStartPosition(t1))));
	printf("%s\n",getTownName(getTownAtPosition(t1,getNextTourPosition(t1,getTourStartPosition(t1)))));
	printf("%s\n",getTownName(getTownAtPosition(t1,getNextTourPosition(t1,getNextTourPosition(t1,getTourStartPosition(t1))))));
	double dis = getTourLength(t1);
	printf("%lf\n",dis);
	//freeTour(t1,1);
	Tour *t2 = heuristic1(t1);
	printf("%s\n",getTownName(getTownAtPosition(t2,getTourStartPosition(t2))));
	printf("%s\n",getTownName(getTownAtPosition(t2,getNextTourPosition(t2,getTourStartPosition(t2)))));
	printf("%s\n",getTownName(getTownAtPosition(t2,getNextTourPosition(t2,getNextTourPosition(t2,getTourStartPosition(t2))))));
	double dis2 = getTourLength(t2);
	printf("%lf\n",dis2);
	//double dis2 = getTourLength(t2);
	//printf("%lf\n",dis2);
	free(t2);
	free(t1);
}
