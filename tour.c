#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include "tour.h"
#include "town.h"
#include "tsp.h"

struct Tour_p{
	Town *Town;
	struct Tour_p *next_town;
};
struct Tour_t{
	TourPosition *town_s;
	TourPosition *town_f;
	int tour_size;
};

Tour *createEmptyTour(void){
	
	Tour *tr = malloc(sizeof(Tour));
	if(!tr){
		printf("impossible d'allouer la memoire\n");
		return NULL;
	}
	tr->town_s=NULL;
	tr->town_f=NULL;
	tr->tour_size= 0;
	return tr;
}

Tour *createTourFromFile(char *filename){
	assert(filename != NULL);
	FILE *fp = fopen(filename,"r");
	if(!fp){
		printf("impossible d'ouvrir le fichier\n");
		return NULL;
	}
	Tour *tr=createEmptyTour();
	char *name = malloc(256*sizeof(char));
	char *nametmp = malloc(256*sizeof(char));
	while(fgets(name,256,fp) != NULL){
		double x,y;
		tr->tour_size++;
		sscanf(name,"%[^,],%lf,%lf",nametmp,&x,&y);
		const char *namec = nametmp;
		Town *t = createTown(namec,x,y);
		TourPosition *tn2 = malloc(sizeof(TourPosition));
		tn2->Town=t;
		tn2->next_town=NULL;
		if(tr->town_f){
			tr->town_f->next_town = tn2;
		}
		else{
			tr->town_s = tn2;
		}
		tr->town_f = tn2;
	}
	free(nametmp);
	free(name);
	fclose(fp);
	return tr;
}
void freeTour(Tour *tour, int freetown){
	assert(tour !=NULL);
	TourPosition *tn = tour->town_s;
	while(tn){
		TourPosition *tnNext = tn->next_town;
		if(freetown>=1){
			freeTown(getTownAtPosition(tour,tn));
		}
		free(tn);
		tn=tnNext;
	}
	free(tour);
}
void addTownAtTourEnd(Tour *tour, Town *town){
	assert(tour != NULL && town != NULL);
	TourPosition *tn = malloc(sizeof(TourPosition));
	tn->Town = town;
	tn->next_town=NULL;
	if(tour->tour_size == 0){
		tour->town_s = tn;
		tour->tour_size = 1;
		return;
	}
	tour->town_f=tn;
	tour->tour_size++;
}
void addTownAfterTourPosition(Tour *tour, TourPosition *pos, Town *town){
	assert(tour != NULL && pos != NULL && town != NULL);
	TourPosition *tn = malloc(sizeof(TourPosition));
	tn->Town = town;
	tn->next_town = getNextTourPosition(tour, pos);
	pos->next_town=tn;
	tour->tour_size++;
}
TourPosition *getTourStartPosition(Tour *tour){
	assert(tour != NULL);
	return tour->town_s;
}
TourPosition *getNextTourPosition(Tour *tour, TourPosition *pos){
	assert(tour != NULL && pos != NULL);
	return pos->next_town;
}
Town *getTownAtPosition(Tour *tour, TourPosition *pos){
	assert(tour != NULL && pos != NULL);
	return pos->Town;
}
int getTourSize(Tour *tour){
	assert(tour != NULL);
	return tour->tour_size;
}
double getTourLength(Tour *tour){
	assert(tour != NULL);
	double Length = 0;
	TourPosition *tp;
	tp = getTourStartPosition(tour);
	while(tp->next_town !=NULL){
		Length += distanceBetweenTowns(getTownAtPosition(tour,tp),getTownAtPosition(tour,getNextTourPosition(tour,tp)));
		tp = getNextTourPosition(tour,tp);
	}
	return Length;
}

