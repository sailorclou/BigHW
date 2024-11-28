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

const int MAX_ROWS = 10;
const int MAX_COLS = 10;

void initial(CONSOLE_GRAPHICS_INFO* const pCGI);
void generate_array(int array[MAX_ROWS][MAX_COLS], int ROWS, int COLS);
bool has_adjacent_same(int grid[MAX_ROWS][MAX_COLS], int ROWS, int COLS);
void move_column_to_left(int array[MAX_ROWS][MAX_COLS], int ROWS, int COLS);
void drop(int array[MAX_ROWS][MAX_COLS], int visited[MAX_ROWS][MAX_COLS], int ROWS, int COLS);
void dfs(int array[MAX_ROWS][MAX_COLS], int visited[MAX_ROWS][MAX_COLS], int ROWS, int COLS, int x, int y, int color);
void draw_graph(int array[MAX_ROWS][MAX_COLS], int visited[MAX_ROWS][MAX_COLS], CONSOLE_GRAPHICS_INFO* const pCGI, BLOCK_DISPLAY_INFO* const bdi);
void game(int array[MAX_ROWS][MAX_COLS], CONSOLE_GRAPHICS_INFO* const pCGI, BLOCK_DISPLAY_INFO* const bdi);
void operate(CONSOLE_GRAPHICS_INFO* const pCGI, BLOCK_DISPLAY_INFO* const bdi);