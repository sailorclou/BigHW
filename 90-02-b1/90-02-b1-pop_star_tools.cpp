/* 2351044 大数据 崔艺洋 */
#include "90-02-b1-pop_star.h"
#include "../include/tools.h"

void initial(int option, int* r, int* c)
{
	while (1) {
		cout << "请输入行数(8-10)：" << endl;
		cin >> *r;
		if (*r >= 8 && *r <= 10 && cin.good())
			break;
		else if (!cin.good()) {
			cin.clear();
			while (getchar() != '\n');
		}
	}
	while (1) {
		cout << "请输入列数(8-10)：" << endl;
		cin >> *c;
		if (*c >= 8 && *c <= 10 && cin.good())
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
	generate_array(array, ROWS, COLS);

	if (option <= 3 && option >= 1) {
		cout << "初始数组：" << endl;
		print_array(0, array, array, ROWS, COLS);
		operate_array(array, option, ROWS, COLS);
	}
	else if (option == 5) {
		operate_graph(array, option, ROWS, COLS);
	}
	else if (option >= 4) {
		operate_graph_no_wall(array, option, ROWS, COLS);
	}
	to_end();
}