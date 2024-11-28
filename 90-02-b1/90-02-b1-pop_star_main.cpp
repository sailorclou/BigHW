/* 2351044 大数据 崔艺洋 */
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
		const char* content[] = { "A.命令行找出可消除项并标识","B.命令行完成一次消除（分步骤显示）",\
			"C.命令行完成一关（分步骤显示）","D.伪图形界面下用鼠标选择一个色块（无分隔线）",\
			"E.伪图形界面下用鼠标选择一个色块（有分隔线）","F.伪图形界面完成一次消除（分步骤）",\
			"G.伪图形界面完整版","Q.退出"};
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








