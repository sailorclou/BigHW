/* 2351044 ������ ������ */
#include <iostream>
#include "90-02-b1-pop_star.h"
#include "../include/cmd_console_tools.h"
#include "../include/cmd_menu.h"
using namespace std;

int main()
{
	while (1) {
		char option;
		int ROWS, COLS;
		const char* content[] = { "A.�������ҳ����������ʶ","B.���������һ���������ֲ�����ʾ��",\
			"C.���������һ�أ��ֲ�����ʾ��","D.αͼ�ν����������ѡ��һ��ɫ�飨�޷ָ��ߣ�",\
			"E.αͼ�ν����������ѡ��һ��ɫ�飨�зָ��ߣ�","F.αͼ�ν������һ���������ֲ��裩",\
			"G.αͼ�ν���������","Q.�˳�"};
		cct_setcolor(0, 7);

		option = menu(content, 8);
		cout << '\n' << endl;
		cct_cls();
		if (option == 'Q')
			return 0;
		initial(int(option - 'A' + 1), &ROWS, &COLS);
		operate(int(option - 'A' + 1), ROWS, COLS);
	}
	return 0;
}








