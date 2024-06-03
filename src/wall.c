#include <math.h>
#include "../headers/header.h"

/**
 * changeColorIntensity - change color intensity
 * based on a factor value between 0 and 1
 * @color: color for intensity
 * @factor: intensity factor
 */
void changeColorIntensity(color_t *color, float factor)
{
	color_t a = (*color & 0xFF000000);
	color_t r = (*color & 0x00FF0000) * factor;
	color_t g = (*color & 0x0000FF00) * factor;
	color_t b = (*color & 0x000000FF) * factor;

	*color = a | (r & 0x00FF0000) | (g & 0x0000FF00) | (b & 0x000000FF);
}

/**
 * renderFloor - render floor projection
 * @wallBottomPixel: wall bottom pixel
 * @texelColor: texture color for current pixel
 * @x: current element in the rays array
 */
void renderFloor(int wallBottomPixel, color_t *texelColor, int x)
{
	int y, texture_height, texture_width, textureOffsetY, textureOffsetX;

	texture_width = wallTextures[3].width;
	texture_height = wallTextures[3].height;

	if (texture_height == 0 || wallTextures[4].texture_buffer == NULL)
		return;

	for (y = wallBottomPixel - 1; y < SCREEN_HEIGHT; y++)
	{
		textureOffsetY = (int)(fabs((float)y * texture_height / SCREEN_HEIGHT)) % texture_height;
		textureOffsetX = (int)(fabs((float)x * texture_width / SCREEN_WIDTH)) % texture_width;

		int texelIndex = (texture_width * textureOffsetY) + textureOffsetX;
		if (texelIndex >= 0 && texelIndex < texture_width * texture_height)
		{
			*texelColor = wallTextures[4].texture_buffer[texelIndex];
			drawPixel(x, y, *texelColor);
		}
	}
}

/**
 * renderCeil - render Ceil projection
 * @wallTopPixel: wall top pixel
 * @texelColor: texture color for current pixel
 * @x: current element in the rays array
 */
void renderCeil(int wallTopPixel, color_t *texelColor, int x)
{
	int y, texture_width, texture_height, textureOffsetY, textureOffsetX;

	texture_width = wallTextures[3].width;
	texture_height = wallTextures[3].height;

	if (texture_height == 0 || wallTextures[6].texture_buffer == NULL)
		return;

	for (y = 0; y < wallTopPixel; y++)
	{
		textureOffsetY = (int)(fabs((float)y * texture_height / SCREEN_HEIGHT)) % texture_height;
		textureOffsetX = (int)(fabs((float)x * texture_width / SCREEN_WIDTH)) % texture_width;

		int texelIndex = (texture_width * textureOffsetY) + textureOffsetX;
		if (texelIndex >= 0 && texelIndex < texture_width * texture_height)
		{
			*texelColor = wallTextures[6].texture_buffer[texelIndex];
			drawPixel(x, y, *texelColor);
		}
	}
}

/**
 * renderWall - render wall projection
 */
void renderWall(void)
{
	int x, y, texNum, texture_width, texture_height;
	int textureOffsetX, wallBottomPixel, wallStripHeight;
	int wallTopPixel, distanceFromTop, textureOffsetY;
	float perpDistance, projectedWallHeight;
	color_t texelColor;

	for (x = 0; x < NUM_RAYS; x++)
	{
		perpDistance = rays[x].distance * cos(rays[x].rayAngle - player.rotationAngle);
		projectedWallHeight = (TILE_SIZE / perpDistance) * PROJ_PLANE;
		wallStripHeight = (int)projectedWallHeight;
		wallTopPixel = (SCREEN_HEIGHT / 2) - (wallStripHeight / 2);
		wallTopPixel = wallTopPixel < 0 ? 0 : wallTopPixel;
		wallBottomPixel = (SCREEN_HEIGHT / 2) + (wallStripHeight / 2);
		wallBottomPixel = wallBottomPixel > SCREEN_HEIGHT ? SCREEN_HEIGHT : wallBottomPixel;
		texNum = rays[x].wallHitContent - 1;
		texture_width = wallTextures[texNum].width;
		texture_height = wallTextures[texNum].height;

		if (wallTextures[texNum].texture_buffer != NULL && texture_width > 0 && texture_height > 0)
		{
			renderFloor(wallBottomPixel, &texelColor, x);
			renderCeil(wallTopPixel, &texelColor, x);

			if (rays[x].wasHitVertical)
				textureOffsetX = (int)rays[x].wallHitY % TILE_SIZE;
			else
				textureOffsetX = (int)rays[x].wallHitX % TILE_SIZE;

			for (y = wallTopPixel; y < wallBottomPixel; y++)
			{
				distanceFromTop = y + (wallStripHeight / 2) - (SCREEN_HEIGHT / 2);
				textureOffsetY = distanceFromTop * ((float)texture_height / wallStripHeight);
				texelColor = wallTextures[texNum].texture_buffer[(texture_width * textureOffsetY) + textureOffsetX];
				if (rays[x].wasHitVertical)
					changeColorIntensity(&texelColor, 0.5);
				drawPixel(x, y, texelColor);
			}
		}
	}
}
