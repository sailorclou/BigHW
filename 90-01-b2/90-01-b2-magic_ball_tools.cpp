/* 2351044 大数据 崔艺洋 */

#include "90-01-b2-magic_ball.h"
#include "../include/tools.h"

void initial(int option, int* r, int* c)
{
	while (1) {
		cout << "请输入行数(5-9)：" << endl;
		cin >> *r;
		if (*r >= 5 && *r <= 9 && cin.good())
			break;
		else if (!cin.good()) {
			cin.clear();
			while (getchar() != '\n');
		}
	}
	while (1) {
		cout << "请输入列数(5-9)：" << endl;
		cin >> *c;
		if (*c >= 5 && *c <= 9 && cin.good())
			break;
		else if (!cin.good()) {
			cin.clear();
			while (getchar() != '\n');
		}
	}
	cout << endl;

	cct_setconsoleborder(60, 30, 60, 1000);
	return;
}


void operate(int option, int ROWS, int COLS)
{
	int array[MAX_ROWS][MAX_COLS] = { 0 };

	cout << "初始数组：" << endl;
	generate_array(array, ROWS, COLS);

	if (option <= 3 && option >= 1) {
		operate_array(array, option, ROWS, COLS);
	}
	if (option >= 4 && option <= 7) {
		operate_graph(array, option, ROWS, COLS);
	}
	if (option >= 8) {
		operate_game(array, option, ROWS, COLS);
	}
	if (option > 3)
		cct_gotoxy(0, 2 * ROWS + 3);
	to_end();
}