#pragma once

#include "main.h"

extern unsigned int game_render_texture;

void game_render_initialize();
void game_render_terminate();
void game_render_rescale(float width, float height);
void game_render();