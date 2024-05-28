#include "../headers/header.h"

static const char *textureFileNames[NUM_TEXTURES] = {
    "./images/redbrick.png",
    "./images/purplestone.png",
    "./images/mossystone.png",
    "./images/graystone.png",
    "./images/colorstone.png",
    "./images/bluestone.png",
    "./images/wood.png",
    "./images/eagle.png",
};

/**
 * WallTexturesready - Load textures from file and prepare them for rendering
 */
void WallTexturesready(void)
{
    for (int i = 0; i < NUM_TEXTURES; i++)
    {
        upng_t *upng = upng_new_from_file(textureFileNames[i]);

        if (upng != NULL)
        {
            upng_decode(upng);
            if (upng_get_error(upng) == UPNG_EOK)
            {
                wallTextures[i].upngTexture = upng;
                wallTextures[i].width = upng_get_width(upng);
                wallTextures[i].height = upng_get_height(upng);
                wallTextures[i].texture_buffer = (color_t *)upng_get_buffer(upng);
            }
        }
    }
}

/**
 * freeWallTextures - Free memory allocated for wall textures
 */
void freeWallTextures(void)
{
    for (int i = 0; i < NUM_TEXTURES; i++)
        upng_free(wallTextures[i].upngTexture);
}

