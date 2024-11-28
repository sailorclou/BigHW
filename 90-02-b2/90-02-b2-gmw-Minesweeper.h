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

const int MAX_ROWS = 45;
const int MAX_COLS = 45;

void initial(CONSOLE_GRAPHICS_INFO* const pCGI);
void operate(CONSOLE_GRAPHICS_INFO* const pCGI, BLOCK_DISPLAY_INFO* const bdi);
bool isMine(int minefield[MAX_ROWS][MAX_COLS], int x, int y);
void placeMines(int minefield[MAX_ROWS][MAX_COLS], int ROWS, int COLS, int numMines);
int countMines(int minefield[MAX_ROWS][MAX_COLS], int ROWS, int COLS, int x, int y);
void updateNumbers(int minefield[MAX_ROWS][MAX_COLS], int ROWS, int COLS);
bool leftOnlyMines(int minefield[MAX_ROWS][MAX_COLS], int visited[MAX_ROWS][MAX_COLS], int ROWS, int COLS);
void touchBoundary(int minefield[MAX_ROWS][MAX_COLS], int visited[MAX_ROWS][MAX_COLS], int x, int y, int ROWS, int COLS);
void drawMinefield(int minefield[MAX_ROWS][MAX_COLS], int visited[MAX_ROWS][MAX_COLS], CONSOLE_GRAPHICS_INFO* const pCGI, BLOCK_DISPLAY_INFO* const bdi, int ROWS, int COLS);
void game(int minefield[MAX_ROWS][MAX_COLS], CONSOLE_GRAPHICS_INFO* const pCGI, BLOCK_DISPLAY_INFO* const bdi, int numMines);
void operate(CONSOLE_GRAPHICS_INFO* const pCGI, BLOCK_DISPLAY_INFO* const bdi);


