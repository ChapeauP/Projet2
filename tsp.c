#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "town.h"
#include "tour.h"
#include "tsp.h"

int recu_i = 0;

TourPosition *recu_get_town(Tour *tour, TourPosition *tour_p, int num_town){
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

Tour *heuristic1(Tour *tour){
	Tour *t;
	t->town_s = tour->town_s;
	t->town_f = tour->town_s;
	t->town_s->next_town = NULL;
	t->town_f->next_town = NULL;
	t->tour_size = 1;
	for (int i = 0; i < tour->tour_size; ++i){
		recu_i = 0;
		TourPosition *Town_ref = malloc(sizeof(TourPosition));
		Town_ref = recu_get_town(tour, tour->town_s, i);
		double d_ref;
		int town_pos;
		for (int j = 0; j < t->tour_size; ++j){
			if(t->tour_size == 1){
				t->town_s->next_town = tour->town_s->next_town;
				d_ref = distanceBetweenTowns(t->town_s->Town,t->town_s->next_town->Town);
			}
			else{
				recu_i = 0;
				TourPosition *town_comp = recu_get_town(t,t->town_s,j);
				double dis = distanceBetweenTowns(Town_ref->Town,town_comp->Town);
				if(d_ref > dis){
					d_ref = dis;
					town_pos = j;
				}
			}
		}
		recu_i = 0;
		recu_get_town(t,t->town_s,town_pos)->next_town = Town_ref;
		t->tour_size++;
	}
	return t;
}


Tour *heuristic2(Tour *tour){
	Tour *t;

}


int main(){
	Tour *t = createTourFromFile("xy-belgium-towns.csv");
	printf("%d\n",t->tour_size);
}