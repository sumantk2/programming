/* This code can be used subjected to terms of GPL */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define offset_of(type, member) \
		((size_t) &((type *)0)->member)

/* code is taken from kernel.h */
#define container_of(ptr, type, member) ({	\
	const typeof( ((type *)0)->member ) *__mptr = (ptr);	\
	(type *)((char *)__mptr - offset_of(type, member));})

struct car_spare_cost {
	int tyre;
	int glass;
	int gearbox;
}*fiat;

int main()
{	
	struct car_spare_cost *fiat_dup;
	fiat = (struct car_spare_cost *)malloc(sizeof(struct car_spare_cost));
	if(!fiat)
		return -ENOMEM;
	printf("\n size of car_space_cost = %d", sizeof(struct car_spare_cost));
	printf("\n address of fiat after malloc = %x", fiat);
	printf("\n address of gearbox = %x", (size_t)&fiat->gearbox);
	fiat->tyre = 10000;
	fiat->glass = 5000;
	fiat->gearbox = 2000;
	
	printf("\n printing offset_of macro = %d", offset_of(struct car_spare_cost, \
		gearbox));
	fiat_dup = container_of(&fiat->gearbox, struct car_spare_cost, gearbox);
	printf("\n address of fiat_dup = %x", fiat_dup);
	free(fiat);
	return 0;	
}
