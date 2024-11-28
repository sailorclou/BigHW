/* 2351044 大数据 崔艺洋 */
#pragma once

/* ------------------------------------------------------------------------------------------------------

	 本文件功能：
	1、为了保证 hanoi_main.cpp/hanoi_menu.cpp/hanoi_multiple_solutions.cpp 能相互访问函数的函数声明
	2、一个以上的cpp中用到的宏定义（#define）或全局只读（const）变量，个数不限
	3、可以参考 cmd_console_tools.h 的写法（认真阅读并体会）
   ------------------------------------------------------------------------------------------------------ */
#include <conio.h>
#include <Windows.h>
#include <iomanip>


const int base_x = 0, base_y = 15;

/* 菜单函数 */
//int menu();
/* 初始化函数 */
void initial(int* n, char* s, char* t, char* d, int option, int* in);
void opt4init(int n, char src, char tmp, char dst, int position, int* in);
void opt8init1(int n, char src, char tmp, char dst, int position, int* in);
void opt8init2(int n, char src, char tmp, char dst, int position, int* in);
/* 汉诺塔递归函数 */
void hanoi(int n, char src, char tmp, char dst, int option, int interval);
/* 打印圆柱 */
void print_column(int n, char src, char tmp, char dst, int option, int interval);
void output(int n, char src, char tmp, char dst, int option, int interval);
void game(int interval, int D, int TOP3);
