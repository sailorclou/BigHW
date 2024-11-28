/* 2351044 大数据 崔艺洋 */
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
		const char* content[] = {"1.基本解","2.基本解(步数记录)","3.内部数组显示(横向)","4.内部数组显示(纵向+横向)",\
			"5.图形解-预备-画三个圆柱","6.图形解-预备-在起始柱上画n个盘子","7.图形解-预备-第一次移动",\
			"8.图形解-自动移动版本","9.图形解-游戏版","0.退出"};
		/* demo中首先执行此句，将cmd窗口设置为40行x120列（缓冲区宽度120列，行数9000行，即cmd窗口右侧带有垂直滚动杆）*/
		cct_setconsoleborder(120, 40, 120, 9000);

		
		/* 菜单 */
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
				cout << '\n' << "游戏结束" << endl;
				cout << endl;
				break;
			case 0:
				return 0;
		}
		if (option == 4)
			cct_gotoxy(base_x, base_y + 2);

		/*cout << "按回车继续";
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
