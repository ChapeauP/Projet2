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
	while(feof(fp) == 0){
		double x,y;
		char name;
		char tmp;
		fscanf(fp,"%s %lf %lf %c",&name,&x,&y,&tmp);
		const char *namec = &name;
		Town *t = createTown(namec,x,y);
		TourPosition *tn = malloc(sizeof(TourPosition));
		if(tn == NULL){
			printf("la ville ne peut etre ajoutée\n");
		}
		tn->Town=t;
		tn->next_town=NULL;
		if(tr->town_f){
			tr->town_f->next_town = tn;
		}
		else {
			tr->town_s=tn;
			tr->town_f=tn;
			tr->tour_size++;
		}

	}
	tr->town_f=tr->town_s;
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
	TourPosition *tn;
	tn->Town = town;
	tn->next_town=NULL;
	tour->town_f->next_town=tn;
	tour->town_f=tn;
	tour->tour_size++;
}
void addTownAfterTourPosition(Tour *tour, TourPosition *pos, Town *town){
	TourPosition *tn;
	tn->Town = town;
	tn->next_town=pos->next_town;
	pos->next_town=tn;
	tour->tour_size++;
}
TourPosition *getTourStartPosition(Tour *tour){
	return tour->town_s;
}
TourPosition *getTourNextPosition(Tour *tour, TourPosition *pos){
	if(pos!=tour->town_f){
		return pos->next_town;
	}
	return NULL;
}
Town *getTownAtPosition(Tour *tour, TourPosition *pos){
	return pos->Town;
	//Position de la ville dans le cas de tours diff????? peut etre changer les structs

}
int getTourSize(Tour *tour){
	return tour->tour_size;
}
