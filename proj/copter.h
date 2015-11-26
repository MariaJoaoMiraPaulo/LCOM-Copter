#pragma once


typdef struct {

	int x, y, w, h, distance;
	//imagem

}copter;

Copter* newCopter();

void draw_copter(Copter* Copter);

void delete_copter(Copter* Copter);

void update_copter(Copter* Copter);
