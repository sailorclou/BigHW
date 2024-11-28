/* 2351044 ������ ������ */
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
/* �˵����� */
//int menu();
/* ��ʼ������ */
void initial(int option, int* ROWS, int* COLS);

/* ����ѡ�������Ӧ�Ĳ��� */
void operate(int option, int ROWS, int COLS);
/* ����������� */
void operate_array(int array[MAX_ROWS][MAX_COLS], int option, int ROWS, int COLS);
/* ����ͼ�β��� */
void operate_graph(int array[MAX_ROWS][MAX_COLS], int option, int ROWS, int COLS);
/* ��Ϸģʽ */
void operate_game(int array[MAX_ROWS][MAX_COLS], int option, int ROWS, int COLS);

/* �����ڲ����� */
void generate_array(int array[MAX_ROWS][MAX_COLS], int ROWS, int COLS);
/* Ѱ���Ƿ��п������Ĳ��� */
bool find_if(int array[MAX_ROWS][MAX_COLS], int ROWS, int COLS);
/* ������Ҫ���ӡ���� */
void print_array(int n, int array[MAX_ROWS][MAX_COLS], int ROWS, int COLS);
/* ��ǿ������� */
void show_array_with_mark(int array[MAX_ROWS][MAX_COLS], int ROWS, int COLS);
/* ��0ģ�����䲢������ֵ��� */
void show_array_with_zero_and_fill(int array[MAX_ROWS][MAX_COLS], int ROWS, int COLS);
/* ����������ʾ */
void hints(int array[MAX_ROWS][MAX_COLS], int ROWS, int COLS);

void print_graph(int n, int array[MAX_ROWS][MAX_COLS], int array_old[MAX_ROWS][MAX_COLS], int ROWS, int COLS, int* SCORE);

void show_graph_with_blank_and_fill(int option, int array[MAX_ROWS][MAX_COLS], int ROWS, int COLS, int* SCORE);
/* ͼ��������ʾ */
void hints2(int array[MAX_ROWS][MAX_COLS], int mark[MAX_ROWS][MAX_COLS], int ROWS, int COLS);
