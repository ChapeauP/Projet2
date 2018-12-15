#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "town.h"
#include "tour.h"
#include "tsp.h"

int recu_i = 0;
//TourPosition *recu(Tour *tour, )

/*TourPosition *recu_get_town(Tour *tour, TourPosition *tour_p, int num_town){
	if(num_town > tour->tour_size){
		printf("le tour ne contient pas cette position\n");
		return NULL;
	}
	if(recu_i < num_town){
		recu_get_town(tour, tour_p->next_town,num_town);
		recu_i++;
	}
	return tour_p;
}
*/

Tour *heuristic1(Tour *tour){
	Tour *t=createEmptyTour();
	t->town_s = tour->town_s;
	t->tour_size++;
	TourPosition *Town_ref = malloc(sizeof(TourPosition));
	for (int i = 1; i < tour->tour_size; ++i){
		/*recu_i = 0;
		Town_ref = recu_get_town(tour, tour->town_s, i);*/
		if(i == 1){
			Town_ref = getTourStartPosition(tour);
		}
		Town_ref = getTourNextPosition(tour,Town_ref);
		double d_ref;
		for (int j = 1; j < t->tour_size; ++j){
			if(t->tour_size == 1){
				t->town_s->next_town = tour->town_s->next_town;
				d_ref = distanceBetweenTowns(t->town_s->Town,t->town_s->next_town->Town);
			}
			else{
				recu_i = 0;
				TourPosition *town_comp = malloc(sizeof(TourPosition));
				/*town_comp = recu_get_town(t,t->town_s,j);*/
				if(j == 1){
					town_comp = getTourStartPosition(t);
				}
				town_comp = getTourNextPosition(t,town_comp);
				double dis = distanceBetweenTowns(Town_ref->Town,town_comp->Town);
				printf("%lf\n",dis );
				if(d_ref > dis){
					d_ref = dis;
					addTownAfterTourPosition(t, Town_ref, town_comp->Town);
				}
			}
		}
		t->tour_size++;
		
		/*recu_i = 0;
		recu_get_town(t,t->town_s,town_pos)->next_town = Town_ref;
		*/
	}
	printf("%d\n", t->tour_size );
	return t;
}

/*Tour *heuristic2(Tour *tour){
	Tour *t;

}*/


int main(){
	Tour *t = createTourFromFile("Doc.txt");
	t = heuristic1(t);
}
