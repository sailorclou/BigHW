/* 2351044 ������ ������ */
#pragma once

/* ------------------------------------------------------------------------------------------------------

	 ���ļ����ܣ�
	1��Ϊ�˱�֤ hanoi_main.cpp/hanoi_menu.cpp/hanoi_multiple_solutions.cpp ���໥���ʺ����ĺ�������
	2��һ�����ϵ�cpp���õ��ĺ궨�壨#define����ȫ��ֻ����const����������������
	3�����Բο� cmd_console_tools.h ��д���������Ķ�����ᣩ
   ------------------------------------------------------------------------------------------------------ */
#include <conio.h>
#include <Windows.h>
#include <iomanip>


const int base_x = 0, base_y = 15;

/* �˵����� */
//int menu();
/* ��ʼ������ */
void initial(int* n, char* s, char* t, char* d, int option, int* in);
void opt4init(int n, char src, char tmp, char dst, int position, int* in);
void opt8init1(int n, char src, char tmp, char dst, int position, int* in);
void opt8init2(int n, char src, char tmp, char dst, int position, int* in);
/* ��ŵ���ݹ麯�� */
void hanoi(int n, char src, char tmp, char dst, int option, int interval);
/* ��ӡԲ�� */
void print_column(int n, char src, char tmp, char dst, int option, int interval);
void output(int n, char src, char tmp, char dst, int option, int interval);
void game(int interval, int D, int TOP3);
