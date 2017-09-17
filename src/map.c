#include "map.h"

#include <stdio.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>

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
struct t_map* map_create(const unsigned int width, const unsigned int height)
{
    struct t_map *map;
    unsigned int i;
    unsigned int j;

    map = (struct t_map*)malloc(sizeof(struct t_map));

    map->width = width;
    map->height = height;

    map->tiles = (struct t_tile*)malloc(width*height*sizeof(struct t_tile));

    for (i=0; i<width*height; i++)
    {
        map->tiles[i].id = i;
        map->tiles[i].weight = 0.0f;

        map->tiles[i].subtiles = (struct t_subtile*)malloc(SUBTILE_WIDTH_PER_TILE*SUBTILE_HEIGHT_PER_TILE*sizeof(struct t_subtile));

        for (j=0; j<SUBTILE_WIDTH_PER_TILE*SUBTILE_HEIGHT_PER_TILE; j++)
        {
            map->tiles[i].subtiles[j].id = j;
            map->tiles[i].subtiles[j].occupied = SUBTILE_OCCUPIED;
        }
    }

    return map;
}

/* Function: map_destroy
 * ---------------------
 * frees up heap resources associated with a map instance
 *
 * map: pointer to the map structure in memory
 *
 * returns: 0 on success
 *          <anything else> on failure
 */
const int map_destroy(struct t_map* map)
{
    unsigned int w;
    unsigned int h;
    unsigned int i;

    if (map != NULL)
    {
        h = map_get_height(map);
        w = map_get_width(map);

        for (i=0; i<w*h; i++)
        {
            /* Free the subtiles */
            free(map->tiles[i].subtiles);
        }
        free(map->tiles);

        free(map);
        return 0;
    }
    return 1;
}

/* Function: map_get_width
 * ----------------------
 * gets the width (in tiles) of the map
 *
 * map: pointer to the map structure in memory
 *
 * returns: width of the map (in tiles)
 */
const unsigned int map_get_width(const struct t_map* map)
{
    return map->width;
}

/* Function: map_get_height
 * ------------------------
 * gets the height (in tiles) of the map
 *
 * map: pointer to the map structure in memory
 *
 * returns: height of the map (in tiles)
 */
const unsigned int map_get_height(const struct t_map* map)
{
    return map->height;
}

