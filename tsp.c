#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "town.h"
#include "tour.h"
#include "tsp.h"


Tour *heuristic1(Tour *tour){
	Tour *t=createEmptyTour();
	t->town_s = tour->town_s;
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
		free(Town_ref);
		if(t->tour_size < tour->tour_size){
			t->tour_size++;
		}
	}
	return t;
}

/*Tour *heuristic2(Tour *tour){
	Tour *t=createEmptyTour();
	t->town_s = tour->town_s;
	t->tour_size = 1;
	TourPosition *Town_ref = malloc(sizeof(TourPosition));
	for (int i = 0; i < tour->tour_size-2; ++i){
		TourPosition *tmp = malloc(sizeof(TourPosition));
		printf("i=%d\n",i);
		if(i == 0){
			Town_ref = getTourNextPosition(tour,tour->town_s->next_town);
		}
		else{
			Town_ref = getTourNextPosition(tour,Town_ref);
		}
		double d_tot_ref = 99999;
		TourPosition *town_comp = malloc(sizeof(TourPosition));
		for (int j = 0; j < t->tour_size; ++j){
			printf("j=%d\n",j);
			if(t->tour_size == 1){
				addTownAfterTourPosition(t,getTourStartPosition(t),getTownAtPosition(tour,getTourStartPosition(t)->next_town));
				d_tot_ref = 2 * distanceBetweenTowns(t->town_s->Town,t->town_s->next_town->Town);
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
				double dis_tot = ;
				//printf("%lf\n",dis);
				if(dis_tot < d_tot_ref){
					d_tot_ref = dis_tot;
					tmp = town_comp;
					printf("%lf\n",d_ref);
					//printf("%s\n",getTownName(getTownAtPosition(t,tmp)));
				}
			}
		}
		addTownAfterTourPosition(t,tmp,getTownAtPosition(tour,Town_ref));
		free(Town_ref);
		if(t->tour_size < tour->tour_size){
			t->tour_size++;
		}
	}
	return t;
}
*/

int main(){
	Tour *t1 = createTourFromFile("Doc.txt");
	double dis = getTourLength(t1);
	printf("%s\n",getTownName(getTownAtPosition(t1,getTourStartPosition(t1))));
	printf("%lf\n",dis);
	Town *t = createTown("liege",0,0);
	freeTown(t);
	//freeTour(t1,1);
	/*Tour *t2 = heuristic1(t1);
	double dis2 = getTourLength(t2);
	printf("%lf\n",dis2);
	free(t2);*/
	free(t1);
}
