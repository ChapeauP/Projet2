#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "town.h"
#include "tour.h"
#include "tsp.h"


Tour *heuristic1(Tour *tour){
	Tour *t=createEmptyTour();
	addTownAtTourEnd(t,getTownAtPosition(tour,getTourStartPosition(tour)));
	t->tour_size = 1;
	TourPosition *Town_ref = malloc(sizeof(TourPosition));
	for (int i = 0; i < tour->tour_size-2; ++i){
		TourPosition *tmp = malloc(sizeof(TourPosition));
		if(i == 0){
			Town_ref = getTourNextPosition(tour,tour->town_s->next_town);
		}
		else{
			Town_ref = getTourNextPosition(tour,Town_ref);
		}
		double d_ref = 99999;
		TourPosition *town_comp = malloc(sizeof(TourPosition));
		for (int j = 0; j < t->tour_size; ++j){
			if(t->tour_size == 1){
				addTownAfterTourPosition(t,getTourStartPosition(t),getTownAtPosition(tour,getTourStartPosition(t)->next_town));
				d_ref = distanceBetweenTowns(t->town_s->Town,t->town_s->next_town->Town);
				town_comp = getTourStartPosition(t);
				t->tour_size = 2;
				//printf("%lf %lf\n",getTownX(t->town_s->Town), getTownX(t->town_s->next_town->Town) );
			}
			else{
				if(t->tour_size == 2 || j == 0){
					town_comp= getTourStartPosition(t);
				}
				else{
					town_comp = getTourNextPosition(t,town_comp);
				}
				double dis = distanceBetweenTowns(getTownAtPosition(tour,Town_ref),getTownAtPosition(t,town_comp));
				if(dis < d_ref){
					d_ref = dis;
					tmp = town_comp;
					//printf("%s\n",getTownName(getTownAtPosition(t,tmp)));
				}
			}
		}
		addTownAfterTourPosition(t,tmp,getTownAtPosition(tour,Town_ref));
		t->town_f = Town_ref;
		if(t->tour_size < tour->tour_size){
			t->tour_size++;
		}
	}
	t->town_f = t->town_s;
	return t;
}

int main(){
	Tour *t1 = createTourFromFile("xy-belgium-towns.csv");
	printf("%s\n",getTownName(getTownAtPosition(t1,getTourStartPosition(t1))));
	printf("%s\n",getTownName(getTownAtPosition(t1,getTourNextPosition(t1,getTourStartPosition(t1)))));
	printf("%s\n",getTownName(getTownAtPosition(t1,getTourNextPosition(t1,getTourNextPosition(t1,getTourStartPosition(t1))))));
	double dis = getTourLength(t1);
	printf("%lf\n",dis);
	//freeTour(t1,1);
	Tour *t2 = heuristic1(t1);
	printf("%s\n",getTownName(getTownAtPosition(t2,getTourStartPosition(t2))));
	printf("%s\n",getTownName(getTownAtPosition(t2,getTourNextPosition(t2,getTourStartPosition(t2)))));
	printf("%s\n",getTownName(getTownAtPosition(t2,getTourNextPosition(t2,getTourNextPosition(t2,getTourStartPosition(t2))))));
	double dis2 = getTourLength(t2);
	printf("%lf\n",dis2);
	//double dis2 = getTourLength(t2);
	//printf("%lf\n",dis2);
	free(t2);
	free(t1);
}
