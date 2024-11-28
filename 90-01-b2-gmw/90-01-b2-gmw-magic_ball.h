/* 2351044 大数据 崔艺洋 */
#pragma once

#include <iostream>
#include <conio.h>
#include <limits>
#include <ctime>
#include <cstdlib>
#include <cstring>
#include <Windows.h>
#include "../include/cmd_console_tools.h"
#include "../include/tools.h"
#include "../include/cmd_gmw_tools.h"

using namespace std;

const int MAX_ROWS = 9;
const int MAX_COLS = 9;

void initial(CONSOLE_GRAPHICS_INFO* const pCGI);
void operate(CONSOLE_GRAPHICS_INFO* const pCGI, BLOCK_DISPLAY_INFO* const bdi);

bool find_if(int array[MAX_ROWS][MAX_COLS], int ROWS, int COLS);
bool is_matching(int array[MAX_ROWS][MAX_COLS], int ROWS, int COLS, int i, int j);
bool are_adjacent(int selected[2][2]);
bool can_swap(int array[MAX_ROWS][MAX_COLS], int selected[2][2], int ROWS, int COLS);
void hints(int array[MAX_ROWS][MAX_COLS], int mark[MAX_ROWS][MAX_COLS], CONSOLE_GRAPHICS_INFO* const pCGI, BLOCK_DISPLAY_INFO* const bdi, int ROWS, int COLS);
void remove(int array_old[MAX_ROWS][MAX_COLS], CONSOLE_GRAPHICS_INFO* const pCGI, int i, int j, BLOCK_DISPLAY_INFO* const bdi);
void check_setzero_update(int array[MAX_ROWS][MAX_COLS], CONSOLE_GRAPHICS_INFO* const pCGI, int ROWS, int COLS, int* SCORE, BLOCK_DISPLAY_INFO* const bdi);
void draw_graph(int array[MAX_ROWS][MAX_COLS], CONSOLE_GRAPHICS_INFO* const pCGI, BLOCK_DISPLAY_INFO* const bdi);
void game(int array[MAX_ROWS][MAX_COLS], CONSOLE_GRAPHICS_INFO* const pCGI, BLOCK_DISPLAY_INFO* const bdi);





