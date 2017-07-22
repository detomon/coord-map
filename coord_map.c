#include <string.h>
#include "coord_map.h"

#define MIN_SIZE 33
#define ABS(a) ((a) < 0 ? -(a) : (a))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

static inline size_t size_for_coord(int a) {
	return ABS(a) * 2 + 1;
}

static inline int coord_in_list(int a, size_t size) {
	return size_for_coord(a) <= size;
}

static int coord_map_resize(coord_map* map, int x) {
	size_t size = size_for_coord(x);
	size_t old_size = map->size;
	size_t new_size = old_size;
	coord_axis** coords = map->coords;

	while (new_size < size) {
		new_size = MAX(MIN_SIZE, new_size * 2 + 1);
	}

	coords = realloc(coords, sizeof(coord_axis*) * new_size);

	if (!coords) {
		return -1;
	}

	if (old_size) {
		size_t hdiff = (new_size - old_size) / 2;

		memmove(&coords[hdiff], coords, sizeof(coord_axis*) * old_size);
		memset(&coords[0], 0, sizeof(coord_axis*) * hdiff);
		memset(&coords[new_size - hdiff], 0, sizeof(coord_axis*) * hdiff);
	}
	else {
		memset(coords, 0, sizeof(coord_axis*) * new_size);
	}

	map->size = new_size;
	map->coords = coords;

	return 0;
}

static coord_axis* coord_map_resize_axis(coord_axis** axis_ref, int y) {
	coord_axis* axis = *axis_ref;
	size_t size = size_for_coord(y);
	size_t old_size = axis ? axis->size : 0;
	size_t new_size = old_size;
	size_t const type_size = sizeof(typeof(axis->items[0]));

	while (new_size < size) {
		new_size = MAX(MIN_SIZE, new_size * 2 + 1);
	}

	axis = realloc(axis, sizeof(coord_axis) + type_size * new_size);

	if (!axis) {
		return NULL;
	}

	if (old_size) {
		size_t hdiff = (new_size - old_size) / 2;

		memmove(&axis->items[hdiff], &axis->items, type_size * old_size);
		memset(&axis->items[0], 0, type_size * hdiff);
		memset(&axis->items[new_size - hdiff], 0, type_size * hdiff);
	}
	else {
		memset(axis->items, 0, type_size * new_size);
	}

	axis->size = new_size;
	*axis_ref = axis;

	return axis;
}

int coord_map_init(coord_map* map) {
	*map = (coord_map) {
		.size = 0,
	};

	return 0;
}

int coord_map_get(coord_map* map, int x, int y) {
	if (coord_in_list(x, map->size)) {
		size_t cx = map->size / 2;
		coord_axis* axis = map->coords[cx + x];

		if (axis && coord_in_list(y, axis->size)) {
			size_t cy = axis->size / 2;

			return axis->items[cy + y];
		}
	}

	return 0;
}

int coord_map_set(coord_map* map, int x, int y, int value) {
	size_t cx;
	size_t cy;
	coord_axis* axis;

	if (!coord_in_list(x, map->size)) {
		if (coord_map_resize(map, x) != 0) {
			return -1;
		}
	}

	cx = map->size / 2;
	axis = map->coords[cx + x];

	if (!axis || !coord_in_list(y, axis->size)) {
		if (!(axis = coord_map_resize_axis(&map->coords[cx + x], y))) {
			return -1;
		}
	}

	cy = axis->size / 2;
	axis->items[cy + y] = value;

	return 0;
}

void coord_map_free(coord_map* map) {
	for (size_t i = 0; i < map->size; i++) {
		free(map->coords[i]);
	}

	free(map->coords);
}
