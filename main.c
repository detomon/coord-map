#include <stdio.h>
#include "coord_map.h"

int main() {
	coord_map map;

	// initialize map
	coord_map_init(&map);

	// set values at given coordinates
	coord_map_set(&map, 16, -6, 1);
	coord_map_set(&map, 16, 8, 2);
	coord_map_set(&map, 400, 3000, 3);
	coord_map_set(&map, 5000, -1000, 4);

	// get values form given coordinates
	int a = coord_map_get(&map, 16, -6);
	int b = coord_map_get(&map, 16, 8);
	int c = coord_map_get(&map, 400, 3000);
	int d = coord_map_get(&map, 5000, -1000);
	int e = coord_map_get(&map, -150, 40); // not set = 0

	// print values: 1, 2, 3, 4, 0
	printf("%d %d %d %d %d\n", a, b, c, d, e);

	// free map
	coord_map_free(&map);

	return 0;
}
