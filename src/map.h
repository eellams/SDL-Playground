#ifndef MAP_H__
#define MAP_H__

#include <stdlib.h>
#include <stdint.h>

#include <SDL2/SDL.h>

#define SUBTILE_WIDTH_PER_TILE  4
#define SUBTILE_HEIGHT_PER_TILE 4

enum t_subtile_occupied {
    SUBTILE_EMPTY,
    SUBTILE_OCCUPIED
};

struct t_subtile {
    unsigned int id;
    enum t_subtile_occupied occupied;
};

struct t_tile {
    unsigned int id;
    float weight;
    struct t_subtile *subtiles;
};

struct t_map {
    unsigned int width;
    unsigned int height;

    struct t_tile *tiles;
};


/* Function: map_create
 * --------------------
 * creates the map of given width and height on the heap
 *     and sets values to defaults
 *
 * width: the width of the map in tiles
 * height: the height of the map in tiles
 *
 * returns: pointer to the map structure on the heap
 */
struct t_map* map_create(const unsigned int width, const unsigned int height);

/* Function: map_destroy
 * ---------------------
 * frees up heap resources associated with a map instance
 *
 * map: pointer to the map structure in memory
 *
 * returns: 0 on success
 *          <anything else> on failure
 */
const int map_destroy(struct t_map* map);


/* Function: map_get_width
 * ----------------------
 * gets the width (in tiles) of the map
 *
 * map: pointer to the map structure in memory
 *
 * returns: width of the map (in tiles)
 */
const unsigned int map_get_width(const struct t_map* map);

/* Function: map_get_height
 * ------------------------
 * gets the height (in tiles) of the map
 *
 * map: pointer to the map structure in memory
 *
 * returns: height of the map (in tiles)
 */
const unsigned int map_get_height(const struct t_map* map);

#endif

