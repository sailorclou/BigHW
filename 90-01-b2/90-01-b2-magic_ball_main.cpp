/* 2351044 ������ ������ */

#include "90-01-b2-magic_ball.h"
#include "../include/cmd_menu.h"

int main()
{
	while (1) {
		int option;
		int ROWS, COLS;
		const char* content[] = { "1.�ڲ����飬���ɳ�ʼ״̬��Ѱ���Ƿ��г�ʼ��������", "2.�ڲ����飬������ʼ����������0�����䲢��0���",\
			"3.�ڲ����飬������ʼ������������������ʾ", "4.n*n�Ŀ��(�޷ָ���)����ʾ��ʼ״̬", "5.n*n�Ŀ��(�зָ���)����ʾ��ʼ״̬",\
			"6.n*n�Ŀ��(�޷ָ���)����ʾ��ʼ״̬����ʼ��������", "7.n*n�Ŀ��(�зָ���)��������ʼ�����������ʾ������ʾ",\
			"8.cmdͼ�ν���������(�зָ��ߣ�����ƶ�ʱ��ʾ���꣬�Ҽ��˳�)", "9.cmdͼ�ν���������", "0.�˳�"};
		
		cct_setcolor(0, 7);
		cct_cls();
		cct_setconsoleborder(100, 40);
		cct_setfontsize("������", 32, 0);
		option = int(menu(content, 10)-'0');
		cct_cls();
		if (option == 0)
			return 0;
		initial(option, &ROWS, &COLS);
		operate(option, ROWS, COLS);
	}

	return 0;
}