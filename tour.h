#ifndef _TOUR_H
#define _TOUR_H
#include "town.h"
typedef struct Tour_p TourPosition;

typedef struct Tour_t Tour;

Tour *createEmptyTour(void);
Tour *createTourFromFile(char *filename);
void freeTour(Tour *tour, int freetown);
void addTownAtTourEnd(Tour *tour, Town *town);
void addTownAfterTourPosition(Tour *tour, TourPosition *pos, Town *town);
TourPosition *getTourStartPosition(Tour *tour);
TourPosition *getNextTourPosition(Tour *tour, TourPosition *pos);
Town *getTownAtPosition(Tour *tour, TourPosition *pos);
int getTourSize(Tour *tour);
double getTourLength(Tour *tour);

#endif
