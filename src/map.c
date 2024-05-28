#include "../headers/header.h"

static const int map[MAP_NUM_ROWS][MAP_NUM_COLS] = {
    {6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6},
    {6, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 6},
    {6, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 6, 0, 0, 0, 6, 0, 0, 0, 6},
    {6, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 6, 0, 7, 7, 0, 0, 0, 0, 6},
    {6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 7, 0, 6},
    {6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 6},
    {6, 0, 0, 0, 0, 0, 7, 7, 7, 0, 0, 1, 0, 0, 0, 0, 7, 7, 0, 6},
    {6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6},
    {6, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 1, 0, 6},
    {6, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 7, 0, 0, 0, 0, 1, 0, 6},
    {6, 0, 0, 6, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6},
    {6, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6},
    {6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6}
};

bool DetectCollision(float x, float y)
{
    if (x < 0 || x >= MAP_NUM_COLS * TILE_SIZE ||
        y < 0 || y >= MAP_NUM_ROWS * TILE_SIZE)
        return true;

    int mapGridX = floor(x / TILE_SIZE);
    int mapGridY = floor(y / TILE_SIZE);
    return map[mapGridY][mapGridX] != 0;
}

bool isInsideMap(float x, float y)
{
    return x >= 0 && x <= MAP_NUM_COLS * TILE_SIZE &&
           y >= 0 && y <= MAP_NUM_ROWS * TILE_SIZE;
}

int getMapValue(int row, int col)
{
    return map[row][col];
}

void renderMap(void)
{
    int tileX, tileY;
    color_t tileColor;

    for (int i = 0; i < MAP_NUM_ROWS; i++)
    {
        for (int j = 0; j < MAP_NUM_COLS; j++)
        {
            tileX = j * TILE_SIZE * MINIMAP_SCALE_FACTOR;
            tileY = i * TILE_SIZE * MINIMAP_SCALE_FACTOR;
            tileColor = map[i][j] != 0 ? 0xFFFFFFFF : 0x00000000;

            drawRect(tileX, tileY,
                     TILE_SIZE * MINIMAP_SCALE_FACTOR,
                     TILE_SIZE * MINIMAP_SCALE_FACTOR,
                     tileColor);
        }
    }
}
