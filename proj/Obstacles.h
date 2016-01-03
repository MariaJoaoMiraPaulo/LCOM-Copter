#ifndef __OBSTACLES_H
#define __OBSTACLES_H

typedef struct {
	short x,y;
} Obstacle;

Obstacle* newObstacle( );

void setObstacle(Obstacle* obs);

void deleteObstacle(Obstacle* obs);

void drawObstacle(Obstacle* obs);

void obsPullToTheLeft(Obstacle* obs);

#endif /* __OBSTACLES_H */
