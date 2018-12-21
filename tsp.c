#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <time.h>
#include "town.h"
#include "tour.h"
#include "tsp.h"


Tour *heuristic1(Tour *tour){
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
	while(getNextTourPosition(tour,towntmp) != NULL){
		towntmp2 = getTourStartPosition(t);
		dis_ref = distanceBetweenTowns(getTownAtPosition(t,towntmp2),getTownAtPosition(tour, towntmp));
		town_closest = towntmp2;
		while(getNextTourPosition(t, towntmp2) != NULL && towntmp != towntmp2){
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
	addTownAfterTourPosition(t,towntmp2,getTownAtPosition(t,getTourStartPosition(t)));
	return t;
}
Tour *heuristic2(Tour *tour){
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
	while(getNextTourPosition(tour,towntmp) != NULL){
		towntmp2 = getTourStartPosition(t);
		town_closest = towntmp2;
		towntmp = getNextTourPosition(tour, towntmp);
		dis_ref = distanceBetweenTowns(getTownAtPosition(tour,towntmp),getTownAtPosition(t,towntmp2)) + distanceBetweenTowns(getTownAtPosition(tour,towntmp),getTownAtPosition(t,getNextTourPosition(t,towntmp2))) - distanceBetweenTowns(getTownAtPosition(t,towntmp2),getTownAtPosition(t,getNextTourPosition(t,towntmp2)));
		while(getNextTourPosition(t, towntmp2) != NULL && towntmp != towntmp2){
			towntmp2 = getNextTourPosition(t, towntmp2);
			if(getNextTourPosition(t, towntmp2) == NULL){
				dis = distanceBetweenTowns(getTownAtPosition(tour,towntmp),getTownAtPosition(t,towntmp2)) + distanceBetweenTowns(getTownAtPosition(tour,towntmp),getTownAtPosition(t,getTourStartPosition(t))) - distanceBetweenTowns(getTownAtPosition(t,towntmp2),getTownAtPosition(t,getTourStartPosition(t)));
			}
			else{
				dis = distanceBetweenTowns(getTownAtPosition(tour,towntmp),getTownAtPosition(t,towntmp2)) + distanceBetweenTowns(getTownAtPosition(tour,towntmp),getTownAtPosition(t,getNextTourPosition(t,towntmp2))) - distanceBetweenTowns(getTownAtPosition(t,towntmp2),getTownAtPosition(t,getNextTourPosition(t,towntmp2)));
			}
			if(dis < dis_ref){
				dis_ref = dis;
				town_closest = towntmp2;
			}
		}
		addTownAfterTourPosition(t,town_closest, getTownAtPosition(tour, towntmp));
	}
	addTownAfterTourPosition(t,towntmp2,getTownAtPosition(t,getTourStartPosition(t)));
	return t;
}
