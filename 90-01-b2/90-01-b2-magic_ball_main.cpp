/* 2351044 大数据 崔艺洋 */

#include "90-01-b2-magic_ball.h"
#include "../include/cmd_menu.h"

int main()
{
	while (1) {
		int option;
		int ROWS, COLS;
		const char* content[] = { "1.内部数组，生成初始状态，寻找是否有初始可消除项", "2.内部数组，消除初始可消除项后非0项下落并用0填充",\
			"3.内部数组，消除初始可消除项后查找消除提示", "4.n*n的框架(无分隔线)，显示初始状态", "5.n*n的框架(有分隔线)，显示初始状态",\
			"6.n*n的框架(无分隔线)，显示初始状态及初始可消除项", "7.n*n的框架(有分隔线)，消除初始可消除项后显示消除提示",\
			"8.cmd图形界面完整版(有分隔线，鼠标移动时显示坐标，右键退出)", "9.cmd图形界面完整版", "0.退出"};
		
		cct_setcolor(0, 7);
		cct_cls();
		cct_setconsoleborder(100, 40);
		cct_setfontsize("新宋体", 32, 0);
		option = int(menu(content, 10)-'0');
		cct_cls();
		if (option == 0)
			return 0;
		initial(option, &ROWS, &COLS);
		operate(option, ROWS, COLS);
	}

	return 0;
}