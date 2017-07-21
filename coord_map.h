/*
 * This map is a dynamically growing 2-dimensional array.
 * Values can be set at arbitary x/y-coordinates, either positive or negative.
 *
 * ## Example
 *
 * ```c
 * coord_map map;
 *
 * // initialize map
 * coord_map_init(&map);
 *
 * // set values at given coordinates
 * coord_map_set(&map, 12, -6, 1);
 * coord_map_set(&map, 12, 8, 2);
 * coord_map_set(&map, 400, 3000, 3);
 * coord_map_set(&map, 5000, -1000, 4);
 *
 * // get values form given coordinates
 * int a = coord_map_get(&map, 12, -6);
 * int b = coord_map_get(&map, 12, 8);
 * int c = coord_map_get(&map, 400, 3000);
 * int d = coord_map_get(&map, 5000, -1000);
 * int e = coord_map_get(&map, -150, 40); // not set = 0
 *
 * // print values: 1, 2, 3, 4, 0
 * printf("%d %d %d %d %d\n", a, b, c, d, e);
 *
 * // free map
 * coord_map_free(&map);
 * ```
 */

#pragma once

#include <stdlib.h>

/**
 * Defines values of an x-coordinate.
 */
typedef struct {
	size_t size; ///< The number of y-coordinates.
	int items[]; ///< The values of the y-coordinates.
} coord_axis;

/**
 * The map which holds the values.
 */
typedef struct {
	size_t size;         ///< The number of y-coordinates.
	coord_axis** coords; ///< The x-coordinates.
} coord_map;

/**
 * Initialize map.
 *
 * @param map The map to initialize.
 *
 * @return 0 on success.
 */
extern int coord_map_init(coord_map* map);

/**
 * Free map.
 *
 * @param map The map to free.
 */
extern void coord_map_free(coord_map* map);

/**
 * Get value at given coordinate.
 *
 * @param map The map to add the value.
 * @param x The x-coordinate.
 * @param y The y-coordinate.
 *
 * @return The value at the speciafied coordinates or 0 if not found.
 */
extern int coord_map_get(coord_map* map, int x, int y);

/**
 * Set value at given coordinate.
 *
 * @param map The map to add the value
 * @param x The x-coordinate.
 * @param y The y-coordinate.
 * @param value The value to set at the specified coordinates.
 *
 * @return 0 on success.
 */
extern int coord_map_set(coord_map* map, int x, int y, int value);
