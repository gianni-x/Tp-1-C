#ifndef _AIRTRIP_HH_
#define _AIRTRIP_HH_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

struct airport {
    char* name;
    float latitude;
    float longitude;
    struct airport* next;
};

struct airTrip {
    char* plane;
    float totalLength;
    struct airport* first;
};

char* strDup(char* src);

int strCmp(char* str1, char* str2);

char* strCnt(char* src1, char* src2);

float flyLength(struct airport* a1, struct airport* a2);

struct airTrip* airTripNew(char* plane);

void airTripAddLast(struct airTrip* trip, char* name, float longitude, float latitude);

void airTripAddBest(struct airTrip* trip, char* name, float longitude, float latitude);

void airTripJoin(struct airTrip** tripJoin, struct airTrip* trip1, struct airTrip* trip2);

void airTripDelLast(struct airTrip* trip);

void airTripRemoveDuplicates(struct airTrip* trip);

char* airTripGetTrip(struct airTrip* trip);

void airTripPrint(struct airTrip* trip);

void airTripDelete(struct airTrip* trip);

#endif

