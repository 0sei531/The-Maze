#include "../headers/header.h"

/**
 * distanceBetweenPoints - Calculate the distance between two points
 * @x1: x coordinate of the starting point
 * @y1: y coordinate of the starting point
 * @x2: x coordinate of the end point
 * @y2: y coordinate of the end point
 *
 * Return: The distance between the two points
 */
float distanceBetweenPoints(float x1, float y1, float x2, float y2)
{
    return sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));
}

/**
 * isRayFacingDown - Check if the ray is facing downwards
 * @angle: Current ray angle
 *
 * Return: true if the ray is facing downwards, false otherwise
 */
bool isRayFacingDown(float angle)
{
    return (angle > 0 && angle < PI);
}

/**
 * isRayFacingUp - Check if the ray is facing upwards
 * @angle: Current ray angle
 *
 * Return: true if the ray is facing upwards, false otherwise
 */
bool isRayFacingUp(float angle)
{
    return !isRayFacingDown(angle);
}

/**
 * isRayFacingRight - Check if the ray is facing to the right
 * @angle: Current ray angle
 *
 * Return: true if the ray is facing to the right, false otherwise
 */
bool isRayFacingRight(float angle)
{
    return (angle < 0.5 * PI || angle > 1.5 * PI);
}

/**
 * isRayFacingLeft - Check if the ray is facing to the left
 * @angle: Current ray angle
 *
 * Return: true if the ray is facing to the left, false otherwise
 */
bool isRayFacingLeft(float angle)
{
    return !isRayFacingRight(angle);
}

