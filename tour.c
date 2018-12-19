#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "tour.h"
#include "town.h"
#include "tsp.h"

Tour *createEmptyTour(void){
	
	Tour *tr = malloc(sizeof(Tour));
	if(!tr){
		printf("impossible d'allouer la memoire\n");
		return NULL;
	}
	tr->town_s= NULL;
	tr->town_f= NULL;
	tr->tour_size= 0;
	return tr;
}

Tour *createTourFromFile(char *filename){
	FILE *fp = fopen(filename,"r");
	if(!fp){
		printf("impossible d'ouvrir le fichier\n");
		return NULL;
	}
	Tour *tr=createEmptyTour();
	TourPosition *tn2 = malloc(sizeof(TourPosition));
	char *name = malloc(256*sizeof(char));
	char *nametmp = malloc(256*sizeof(char));
	int i = 0;
	while(1){
		i++;
		if(fgets(name,256,fp) == NULL){
			break;
		}
		double x,y;
		tr->tour_size++;
		sscanf(name,"%s %lf %lf",nametmp,&x,&y);
		//sscanf(name,"%[^,],%lf,%lf",nametmp,&x,&y);
		const char *namec = nametmp;
		Town *t = createTown(namec,x,y);
		TourPosition *tn2 = malloc(sizeof(TourPosition));
		tn2->Town=t;
		tn2->next_town=NULL;
		if(tr->town_f){
			addTownAfterTourPosition(tr,tr->town_f,t);
		}
		else{
			tr->town_s = tn2;
		}
		tr->town_f = tn2;
	}
	tn2->next_town = tr->town_s;
	tr->town_f = tr->town_s;
	free(name);
	free(tn2);
	fclose(fp);
	return tr;
}
void freeTour(Tour *tour, int freetown){
	TourPosition *tn = tour->town_s;
	while(tn){
		TourPosition *tnNext = tn->next_town;
		if(freetown>=1){
			freeTown(tn->Town);
		}
		free(tn);
		tn=tnNext;
	}
	free(tour);
}
void addTownAtTourEnd(Tour *tour, Town *town){
	TourPosition *tn = malloc(sizeof(TourPosition));
	tn->Town = town;
	tn->next_town=NULL;
	tour->town_f=tn;
	tour->tour_size++;
}
void addTownAfterTourPosition(Tour *tour, TourPosition *pos, Town *town){
	TourPosition *tn = malloc(sizeof(TourPosition));
	tn->Town = town;
	tn->next_town=pos->next_town;
	pos->next_town=tn;
	tour->tour_size++;
}
TourPosition *getTourStartPosition(Tour *tour){
	return tour->town_s;
}
TourPosition *getTourNextPosition(Tour *tour, TourPosition *pos){
	return pos->next_town;
}
Town *getTownAtPosition(Tour *tour, TourPosition *pos){
	return pos->Town;
	//Position de la ville dans le cas de tours diff????? peut etre changer les structs

}
int getTourSize(Tour *tour){
	return tour->tour_size;
}
double getTourLength(Tour *tour){
	double Length = 0;
	TourPosition *tp;
	tp = getTourStartPosition(tour);
	while(tp != getTourStartPosition(tour) || Length == 0){
		Length += distanceBetweenTowns(getTownAtPosition(tour,tp),getTownAtPosition(tour,getTourNextPosition(tour,tp)));
		tp = getTourNextPosition(tour,tp);
	}
	return Length;
}

