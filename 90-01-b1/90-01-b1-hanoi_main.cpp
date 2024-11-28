/* 2351044 ������ ������ */
#include <iostream>
#include <conio.h>
#include "90-01-b1-hanoi.h"
#include "../include/cmd_console_tools.h"
#include "../include/cmd_menu.h"
using namespace std;


int main()
{
	while (1) {
		int n = 0;
		int option;
		char src = 'A', * s = &src, tmp = 'B', * t = &tmp, dst = 'C', * d = &dst;
		char D = *d, TOP3 = n;
		int interval = -1;
		const char* content[] = {"1.������","2.������(������¼)","3.�ڲ�������ʾ(����)","4.�ڲ�������ʾ(����+����)",\
			"5.ͼ�ν�-Ԥ��-������Բ��","6.ͼ�ν�-Ԥ��-����ʼ���ϻ�n������","7.ͼ�ν�-Ԥ��-��һ���ƶ�",\
			"8.ͼ�ν�-�Զ��ƶ��汾","9.ͼ�ν�-��Ϸ��","0.�˳�"};
		/* demo������ִ�д˾䣬��cmd��������Ϊ40��x120�У����������120�У�����9000�У���cmd�����Ҳ���д�ֱ�����ˣ�*/
		cct_setconsoleborder(120, 40, 120, 9000);

		
		/* �˵� */
		option = int(menu(content, 10)-'0');
		cct_cls();
		switch (option) {
			case 1:
			case 2:
			case 3:
			case 4:
				initial(&n, &src, &tmp, &dst, option, &interval);
				hanoi(n, src, tmp, dst, option, interval);
				cout << endl;
				break;
			case 5:
				cct_cls();
				cct_setcolor(0, 7);
				print_column(n, src, tmp, dst, option, interval);
				cout << endl;
				break;
			case 6:
			case 7:
				initial(&n, &src, &tmp, &dst, option, &interval);
				cct_cls();
				cct_setcolor(0, 7);
				print_column(n, src, tmp, dst, option, interval);
				output(n, src, tmp, dst, option, interval);
				cout << endl;
				break;
			case 8:
				initial(&n, &src, &tmp, &dst, option, &interval);
				print_column(n, src, tmp, dst, option, interval);
				hanoi(n, src, tmp, dst, option, interval);
				cout << endl;
				break;
			case 9:
				initial(&n, &src, &tmp, &dst, option, &interval);
				D = *d, TOP3 = n;
				print_column(n, src, tmp, dst, option, interval);
				game(interval, D, TOP3);
				cct_gotoxy(base_x, base_y + 19);
				cout << '\n' << "��Ϸ����" << endl;
				cout << endl;
				break;
			case 0:
				return 0;
		}
		if (option == 4)
			cct_gotoxy(base_x, base_y + 2);

		/*cout << "���س�����";
		while (1) {
			char ch = _getch();
			if (ch == '\r')
				break;
		}*/
		//	system("pause");
		//	if (option) {
		//		main();
		//	}
	}
	return 0;
}
