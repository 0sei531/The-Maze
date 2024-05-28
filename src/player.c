#include "../headers/header.h"
#include <math.h>

void movePlayer(float DeltaTime)
{
    float moveStep, newPlayerX, newPlayerY;
    float cosRotation = cos(player.rotationAngle);
    float sinRotation = sin(player.rotationAngle);

    player.rotationAngle += player.turnDirection * player.turnSpeed * DeltaTime;
    moveStep = player.walkDirection * player.walkSpeed * DeltaTime;

    newPlayerX = player.x + cosRotation * moveStep;
    newPlayerY = player.y + sinRotation * moveStep;

    if (!DetectCollision(newPlayerX, newPlayerY))
    {
        player.x = newPlayerX;
        player.y = newPlayerY;
    }
}

void renderPlayer(void)
{
    drawRect(player.x * MINIMAP_SCALE_FACTOR,
             player.y * MINIMAP_SCALE_FACTOR,
             player.width * MINIMAP_SCALE_FACTOR,
             player.height * MINIMAP_SCALE_FACTOR,
             0xFFFFFFFF);
}

