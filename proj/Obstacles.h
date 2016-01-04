#ifndef __OBSTACLES_H
#define __OBSTACLES_H

/** @defgroup obstacles Obstacles
 * @{
 *
 * Module that create and control everything that is related to obstacles
 *
 */

/** @name Obstacle structure */
/** @{
 *
 * Obstacle structure
 */
typedef struct {
	short x,y;
} Obstacle;
/** @} end of Obstacle */

/*
 * @brief obstacle constructor
 *
 * @return pointer to obstacle
 */
Obstacle* newObstacle( );

/*
 * @brief edits the coordinates of the obstacle to push to the right side
 *
 * @param obs obstacle to be edited
 */
void setObstacle(Obstacle* obs);

/*
 * @brief to delete a obstacle
 *
 * @param obs obstacle to be deleted
 */
void deleteObstacle(Obstacle* obs);

/*
 * @brief draws a obstacle
 *
 * @param obs obstacle to be draw
 */
void drawObstacle(Obstacle* obs);

/*
 * @brief pull to the left the obstacle
 *
 * @param obs obstacle to be pushed
 */
void obsPullToTheLeft(Obstacle* obs);


/** @} end of Obstacles */

#endif /* __OBSTACLES_H */
