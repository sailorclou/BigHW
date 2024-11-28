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

using namespace std;

const int MAX_ROWS = 9;
const int MAX_COLS = 9;

int main();
/* 菜单函数 */
//int menu();
/* 初始化函数 */
void initial(int option, int* ROWS, int* COLS);

/* 根据选项进行相应的操作 */
void operate(int option, int ROWS, int COLS);
/* 进行数组操作 */
void operate_array(int array[MAX_ROWS][MAX_COLS], int option, int ROWS, int COLS);
/* 进行图形操作 */
void operate_graph(int array[MAX_ROWS][MAX_COLS], int option, int ROWS, int COLS);
/* 游戏模式 */
void operate_game(int array[MAX_ROWS][MAX_COLS], int option, int ROWS, int COLS);

/* 生成内部数组 */
void generate_array(int array[MAX_ROWS][MAX_COLS], int ROWS, int COLS);
/* 寻找是否有可消除的操作 */
bool find_if(int array[MAX_ROWS][MAX_COLS], int ROWS, int COLS);
/* 按各种要求打印数组 */
void print_array(int n, int array[MAX_ROWS][MAX_COLS], int ROWS, int COLS);
/* 标记可消除项 */
void show_array_with_mark(int array[MAX_ROWS][MAX_COLS], int ROWS, int COLS);
/* 用0模拟下落并进行新值填充 */
void show_array_with_zero_and_fill(int array[MAX_ROWS][MAX_COLS], int ROWS, int COLS);
/* 数组消除提示 */
void hints(int array[MAX_ROWS][MAX_COLS], int ROWS, int COLS);

void print_graph(int n, int array[MAX_ROWS][MAX_COLS], int array_old[MAX_ROWS][MAX_COLS], int ROWS, int COLS, int* SCORE);

void show_graph_with_blank_and_fill(int option, int array[MAX_ROWS][MAX_COLS], int ROWS, int COLS, int* SCORE);
/* 图表消除提示 */
void hints2(int array[MAX_ROWS][MAX_COLS], int mark[MAX_ROWS][MAX_COLS], int ROWS, int COLS);
