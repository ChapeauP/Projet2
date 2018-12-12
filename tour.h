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

#endif
