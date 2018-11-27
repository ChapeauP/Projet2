#ifndef _TOWN_H
#define _TOWN_H

typedef struct Town_t Town;

Town *createTown(const char *name, double x, double y);
double getTownX(Town *town);
double getTownY(Town *town);
const char *getTownName(Town *town);
double distanceBetweenTowns(Town *town1, Town *town2);
void freeTown(Town *town);

#endif