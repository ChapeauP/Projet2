#ifndef _TOUR_H
#define _TOUR_H
#include "town.h"
typedef struct Tour_p{
	Town *Town;
	struct Tour_p *next_town;
}TourPosition;

typedef struct Tour_t{
	TourPosition *town_s;
	TourPosition *town_f;
	int tour_size;
}Tour;

Tour *createEmptyTour(void);
Tour *createTourFromFile(char *filename);
void freeTour(Tour *tour, int freetown);
void addTownAtTourEnd(Tour *tour, Town *town);
void addTownAfterTourPosition(Tour *tour, TourPosition *pos, Town *town);
TourPosition *getTourStartPosition(Tour *tour);
TourPosition *getTourNextPosition(Tour *tour, TourPosition *pos);
Town *getTownAtPosition(Tour *tour, TourPosition *pos);
int getTourSize(Tour *tour);

#endif
