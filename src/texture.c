#include <stdlib.h>
#include <stdio.h>
#include <upng.h>
#include "../headers/header.h"

/**
 * endian_swap - Swap the endianness of a 32-bit unsigned integer
 * @value: The value to be swapped
 *
 * Return: The value with swapped endianness
 */
static unsigned int endian_swap(unsigned int value)
{
	return ((value & 0xFF000000) >> 24) |
	       ((value & 0x00FF0000) >> 8) |
	       ((value & 0x0000FF00) << 8) |
	       ((value & 0x000000FF) << 24);
}

/* Definition and initialization of wallTextures */
texture_t wallTextures[NUM_TEXTURES];

/* Static array to store file names of textures */
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
	int i, j, pixel_count;
	upng_t *upng;
	unsigned int *buffer;

	for (i = 0; i < NUM_TEXTURES; i++)
	{
		upng = upng_new_from_file(textureFileNames[i]);
		if (upng != NULL)
		{
			upng_decode(upng);
			if (upng_get_error(upng) == UPNG_EOK)
			{
				wallTextures[i].upngTexture = upng;
				wallTextures[i].width = upng_get_width(upng);
				wallTextures[i].height = upng_get_height(upng);
				buffer = (unsigned int *)upng_get_buffer(upng);
				if (buffer != NULL)
				{
					pixel_count = wallTextures[i].width * wallTextures[i].height;
					wallTextures[i].texture_buffer = malloc(pixel_count * sizeof(color_t));
					if (wallTextures[i].texture_buffer != NULL)
					{
						for (j = 0; j < pixel_count; j++)
							wallTextures[i].texture_buffer[j] = endian_swap(buffer[j]);
					}
					else
					{
						fprintf(stderr, "Error: Failed to allocate memory for texture buffer %d\n", i);
					}
				}
				else
				{
					fprintf(stderr, "Error: Invalid texture buffer for texture %d\n", i);
				}
			}
			else
			{
				fprintf(stderr, "Error: Failed to decode texture %d\n", i);
				upng_free(upng);
			}
		}
		else
		{
			fprintf(stderr, "Error: Failed to load texture %s\n", textureFileNames[i]);
		}
	}
}

/**
 * freeWallTextures - Free memory allocated for wall textures
 */
void freeWallTextures(void)
{
	int i;

	for (i = 0; i < NUM_TEXTURES; i++)
	{
		if (wallTextures[i].texture_buffer != NULL)
			free(wallTextures[i].texture_buffer);
		if (wallTextures[i].upngTexture != NULL)
			upng_free(wallTextures[i].upngTexture);
	}
}
