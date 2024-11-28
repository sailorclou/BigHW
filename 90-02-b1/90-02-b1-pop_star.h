/* 2351044 ������ ������ */
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

/* �˵����� */
//int menu();
/* ��ʼ������ */
void initial(int option, int* ROWS, int* COLS);
/* ����ѡ�������Ӧ�Ĳ��� */
void operate(int option, int ROWS, int COLS);
/* ����������� */
void operate_array(int array[MAX_ROWS][MAX_COLS], int option, int ROWS, int COLS);
/* �����ڲ����� */
void generate_array(int array[MAX_ROWS][MAX_COLS], int ROWS, int COLS);
/* ��ӡ���� */
void print_array(int n, int array[MAX_ROWS][MAX_COLS], int visited[MAX_ROWS][MAX_COLS], int ROWS, int COLS);
/* ����ͼ�β��� */
void operate_graph_no_wall(int array[MAX_ROWS][MAX_COLS], int option, int ROWS, int COLS);
/* ��Ϸģʽ */
void operate_graph(int array[MAX_ROWS][MAX_COLS], int option, int ROWS, int COLS);
/* ���� */
void dfs(int array[MAX_ROWS][MAX_COLS], int visited[MAX_ROWS][MAX_COLS], int ROWS, int COLS, int x, int y, int color);
void move_column_to_right(int array[MAX_ROWS][MAX_COLS], int ROWS, int COLS);
void drop(int array[MAX_ROWS][MAX_COLS], int visited[MAX_ROWS][MAX_COLS], int ROWS, int COLS);
bool has_adjacent_same(int grid[MAX_ROWS][MAX_COLS], int ROWS, int COLS);
