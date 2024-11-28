/* 2351044 大数据 崔艺洋 */
#pragma once

#include <iostream>
#include <conio.h>
#include <limits>
#include <ctime>
#include <cstdlib>
#include <cstring>
#include <Windows.h>
#include <cmath>
#include "../include/cmd_console_tools.h"
#include "../include/tools.h"

using namespace std;

const int MAX_ROWS = 10;
const int MAX_COLS = 10;

/* 菜单函数 */
//int menu();
/* 初始化函数 */
void initial(int option, int* ROWS, int* COLS);
/* 根据选项进行相应的操作 */
void operate(int option, int ROWS, int COLS);
/* 进行数组操作 */
void operate_array(int array[MAX_ROWS][MAX_COLS], int option, int ROWS, int COLS);
/* 生成内部数组 */
void generate_array(int array[MAX_ROWS][MAX_COLS], int ROWS, int COLS);
/* 打印数组 */
void print_array(int n, int array[MAX_ROWS][MAX_COLS], int visited[MAX_ROWS][MAX_COLS], int ROWS, int COLS);
/* 进行图形操作 */
void operate_graph_no_wall(int array[MAX_ROWS][MAX_COLS], int option, int ROWS, int COLS);
/* 游戏模式 */
void operate_graph(int array[MAX_ROWS][MAX_COLS], int option, int ROWS, int COLS);
/* 搜索 */
void dfs(int array[MAX_ROWS][MAX_COLS], int visited[MAX_ROWS][MAX_COLS], int ROWS, int COLS, int x, int y, int color);
void move_column_to_right(int array[MAX_ROWS][MAX_COLS], int ROWS, int COLS);
void drop(int array[MAX_ROWS][MAX_COLS], int visited[MAX_ROWS][MAX_COLS], int ROWS, int COLS);
bool has_adjacent_same(int grid[MAX_ROWS][MAX_COLS], int ROWS, int COLS);
