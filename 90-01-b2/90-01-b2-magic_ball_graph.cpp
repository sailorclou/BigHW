/* 2351044 大数据 崔艺洋 */

#include "90-01-b2-magic_ball.h"

bool is_matching(int array[MAX_ROWS][MAX_COLS], int ROWS, int COLS, int i, int j)
{
	if ((array[i][j] == array[i][j + 1] && array[i][j] == array[i][j + 2] && j < COLS - 2
		|| array[i][j] == array[i][j - 1] && array[i][j] == array[i][j + 1] && j < COLS - 1 && j > 0
		|| array[i][j] == array[i][j - 1] && array[i][j] == array[i][j - 2] && j > 1
		|| array[i][j] == array[i + 1][j] && array[i][j] == array[i + 2][j] && i < ROWS - 2
		|| array[i][j] == array[i - 1][j] && array[i][j] == array[i + 1][j] && i < ROWS - 1 && i > 0
		|| array[i][j] == array[i - 2][j] && array[i][j] == array[i - 1][j] && i > 1))
		return true;
	else
		return false;
}
bool are_adjacent(int selected[2][2])
{
	if (selected[0][0] == selected[1][0] &&
		(selected[0][1] == selected[1][1] + 1 || selected[0][1] == selected[1][1] - 1)) {
		return true;
	}
	if (selected[0][1] == selected[1][1] &&
		(selected[0][0] == selected[1][0] + 1 || selected[0][0] == selected[1][0] - 1)) {
		return true;
	}
	return false;
}
bool can_swap(int array[MAX_ROWS][MAX_COLS], int selected[2][2], int ROWS, int COLS)
{
	int c = 0;
	c = array[selected[0][0]][selected[0][1]];
	array[selected[0][0]][selected[0][1]] = array[selected[1][0]][selected[1][1]];
	array[selected[1][0]][selected[1][1]] = c;

	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			if (is_matching(array, ROWS, COLS, i, j)) {
				return true;
			}
		}
	}
	return false;
}
void hints2(int array[MAX_ROWS][MAX_COLS], int mark[MAX_ROWS][MAX_COLS], int ROWS, int COLS)
{
	int x = 0, y = 1;
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			// 检查垂直方向连续相等，并处理边界问题
			if (i < ROWS - 1 && array[i][j] == array[i + 1][j]) {
				if (i > 0 && j > 0 && array[i][j] == array[i - 1][j - 1]) {
					cct_showstr(4 * (x + j - 1) + 2, y + 2 * (i - 1) + 1, "◎", array[i - 1][j - 1], 0);
					cct_showstr(4 * (x + j) + 2, y + 2 * (i - 1) + 1, "◎", array[i - 1][j], 0);
					mark[i - 1][j - 1] = 1;
					mark[i - 1][j] = 1;
				}  // 左上角
				if (i < ROWS - 2 && j > 0 && array[i][j] == array[i + 2][j - 1]) {
					cct_showstr(4 * (x + j - 1) + 2, y + 2 * (i + 2) + 1, "◎", array[i + 2][j - 1], 0);
					cct_showstr(4 * (x + j) + 2, y + 2 * (i + 2) + 1, "◎", array[i + 2][j], 0);
					mark[i + 2][j - 1] = 1;
					mark[i + 2][j] = 1;
				}  // 左下角
				if (i < ROWS - 2 && j < COLS - 1 && array[i][j] == array[i + 2][j + 1]) {
					cct_showstr(4 * (x + j + 1) + 2, y + 2 * (i + 2) + 1, "◎", array[i + 2][j + 1], 0);
					cct_showstr(4 * (x + j) + 2, y + 2 * (i + 2) + 1, "◎", array[i + 2][j], 0);
					mark[i + 2][j + 1] = 1;
					mark[i + 2][j] = 1;
				}  // 右下角
				if (i > 0 && j < COLS - 1 && array[i][j] == array[i - 1][j + 1]) {
					cct_showstr(4 * (x + j + 1) + 2, y + 2 * (i - 1) + 1, "◎", array[i - 1][j + 1], 0);
					cct_showstr(4 * (x + j) + 2, y + 2 * (i - 1) + 1, "◎", array[i - 1][j], 0);
					mark[i - 1][j + 1] = 1;
					mark[i - 1][j] = 1;
				}  // 右上角
				if (i > 1 && array[i][j] == array[i - 2][j]) {
					cct_showstr(4 * (x + j) + 2, y + 2 * (i - 2) + 1, "◎", array[i - 2][j], 0);
					cct_showstr(4 * (x + j) + 2, y + 2 * (i - 1) + 1, "◎", array[i - 1][j], 0);
					mark[i - 2][j] = 1;
					mark[i - 1][j] = 1;
				}  // 上
				if (i < ROWS - 2 && array[i][j] == array[i + 3][j]) {
					cct_showstr(4 * (x + j) + 2, y + 2 * (i + 3) + 1, "◎", array[i + 3][j], 0);
					cct_showstr(4 * (x + j) + 2, y + 2 * (i + 2) + 1, "◎", array[i + 2][j], 0);
					mark[i + 3][j] = 1;
					mark[i + 2][j] = 1;
				}  // 下
			}
			// 检查水平方向连续相等，并处理边界问题
			if (j < COLS - 1 && array[i][j] == array[i][j + 1]) {
				if (i > 0 && j > 0 && array[i][j] == array[i - 1][j - 1]) {
					cct_showstr(4 * (x + j - 1) + 2, y + 2 * (i - 1) + 1, "◎", array[i - 1][j - 1], 0);
					cct_showstr(4 * (x + j - 1) + 2, y + 2 * i + 1, "◎", array[i][j - 1], 0);
					mark[i - 1][j - 1] = 1;
					mark[i][j - 1] = 1;
				}  // 左上角
				if (i < ROWS - 1 && j > 0 && array[i][j] == array[i + 1][j - 1]) {
					cct_showstr(4 * (x + j - 1) + 2, y + 2 * (i + 1) + 1, "◎", array[i + 1][j - 1], 0);
					cct_showstr(4 * (x + j - 1) + 2, y + 2 * i + 1, "◎", array[i][j - 1], 0);
					mark[i + 1][j - 1] = 1;
					mark[i][j - 1] = 1;
				}  // 左下角
				if (i < ROWS - 1 && j < COLS - 2 && array[i][j] == array[i + 1][j + 2]) {
					cct_showstr(4 * (x + j + 2) + 2, y + 2 * (i + 1) + 1, "◎", array[i + 1][j + 2], 0);
					cct_showstr(4 * (x + j + 2) + 2, y + 2 * i + 1, "◎", array[i][j + 2], 0);
					mark[i + 1][j + 2] = 1;
					mark[i][j + 2] = 1;
				}  // 右下角
				if (i > 0 && j < COLS - 2 && array[i][j] == array[i - 1][j + 2]) {
					cct_showstr(4 * (x + j + 2) + 2, y + 2 * (i - 1) + 1, "◎", array[i - 1][j + 2], 0);
					cct_showstr(4 * (x + j + 2) + 2, y + 2 * i + 1, "◎", array[i][j + 2], 0);
					mark[i - 1][j + 2] = 1;
					mark[i][j + 2] = 1;
				}  // 右上角
				if (j > 1 && array[i][j] == array[i][j - 2]) {
					cct_showstr(4 * (x + j - 2) + 2, y + 2 * i + 1, "◎", array[i][j - 2], 0);
					cct_showstr(4 * (x + j - 1) + 2, y + 2 * i + 1, "◎", array[i][j - 1], 0);
					mark[i][j - 2] = 1;
					mark[i][j - 1] = 1;
				}  // 左
				if (j < COLS - 2 && array[i][j] == array[i][j + 3]) {
					cct_showstr(4 * (x + j + 3) + 2, y + 2 * i + 1, "◎", array[i][j + 3], 0);
					cct_showstr(4 * (x + j + 2) + 2, y + 2 * i + 1, "◎", array[i][j + 2], 0);
					mark[i][j + 3] = 1;
					mark[i][j + 2] = 1;
				}  // 右
			}
			// 检查垂直方向间隔相等，并处理边界问题
			if (i < ROWS - 2 && array[i][j] == array[i + 2][j]) {
				if (i > 0 && j > 0 && array[i][j] == array[i + 1][j - 1]) {
					cct_showstr(4 * (x + j - 1) + 2, y + 2 * (i + 1) + 1, "◎", array[i + 1][j - 1], 0);
					cct_showstr(4 * (x + j) + 2, y + 2 * (i + 1) + 1, "◎", array[i + 1][j], 0);
					mark[i + 1][j - 1] = 1;
					mark[i + 1][j] = 1;
				}  // 左
				if (i < ROWS - 2 && j < COLS - 1 && array[i][j] == array[i + 1][j + 1]) {
					cct_showstr(4 * (x + j + 1) + 2, y + 2 * (i + 1) + 1, "◎", array[i + 1][j + 1], 0);
					cct_showstr(4 * (x + j) + 2, y + 2 * (i + 1) + 1, "◎", array[i + 1][j], 0);
					mark[i + 1][j + 1] = 1;
					mark[i + 1][j] = 1;
				}  // 右
			}
			// 检查水平方向间隔相等，并处理边界问题
			if (j < COLS - 2 && array[i][j] == array[i][j + 2]) {
				if (i > 0 && j > 0 && array[i][j] == array[i - 1][j + 1]) {
					cct_showstr(4 * (x + j + 1) + 2, y + 2 * (i - 1) + 1, "◎", array[i - 1][j + 1], 0);
					cct_showstr(4 * (x + j + 1) + 2, y + 2 * i + 1, "◎", array[i][j + 1], 0);
					mark[i - 1][j + 1] = 1;
					mark[i][j + 1] = 1;
				}  // 上
				if (i < ROWS - 2 && j < COLS - 2 && array[i][j] == array[i + 1][j + 1]) {
					cct_showstr(4 * (x + j + 1) + 2, y + 2 * (i + 1) + 1, "◎", array[i + 1][j + 1], 0);
					cct_showstr(4 * (x + j + 1) + 2, y + 2 * i + 1, "◎", array[i][j + 1], 0);
					mark[i + 1][j + 1] = 1;
					mark[i][j + 1] = 1;
				}  // 下
			}
		}
	}
	cct_setcolor(0, 7);
	cct_gotoxy(0, ROWS + 1);
}
void blink_and_remove(int array_old[MAX_ROWS][MAX_COLS], int num, int i, int j)
{
	int x = 0, y = 1;
	cct_showstr(4 * (x + j) + 2, y + 2 * i + 1, "¤", array_old[i][j], 0);
	Sleep(100);
	cct_showstr(4 * (x + j) + 2, y + 2 * i + 1, "○", array_old[i][j], 0);
	Sleep(100);
	cct_showstr(4 * (x + j) + 2, y + 2 * i + 1, "¤", array_old[i][j], 0);
	Sleep(200);
	cct_showstr(4 * (x + j) + 2, y + 2 * i + 1, "○", array_old[i][j], 0);
	Sleep(100);
	cct_showstr(4 * (x + j) + 2, y + 2 * i + 1, "¤", array_old[i][j], 0);
	Sleep(100);
	cct_showstr(4 * (x + j) + 2, y + 2 * i + 1, "  ", 15, 15);
}
void show_graph_with_blank_and_fill(int option, int array[MAX_ROWS][MAX_COLS], int ROWS, int COLS, int* SCORE)
{
	/* 在循环检查时，检查旧的数组，改变新的数组，从而只消除旧数组的相连项 */

	int array1[MAX_ROWS][MAX_COLS];
	// 拷贝
	for (int i = 0; i < ROWS; i++)
		for (int j = 0; j < COLS; j++)
			array1[i][j] = array[i][j];
	// 置零
	for (int i = ROWS - 1;i >= 0;i--)
		for (int j = 0;j < COLS;j++) {
			if (!(i == ROWS - 1 || i == ROWS - 2) &&
				array[i][j] == array[i + 1][j] && array[i][j] == array[i + 2][j]) {
				array1[i][j] = 0;
				array1[i + 1][j] = 0;
				array1[i + 2][j] = 0;
			}  // 检查纵向并置零
			if (!(j == COLS - 1 || j == COLS - 2) &&
				array[i][j] == array[i][j + 1] && array[i][j] == array[i][j + 2]) {
				array1[i][j] = 0;
				array1[i][j + 1] = 0;
				array1[i][j + 2] = 0;
			}  // 检查横向并置零
		}
	// 把0移到列首
	int k;
	for (int j = 0;j < COLS;j++) {
		for (int i = ROWS - 1;i > 0;i--) {
			if (array1[i][j] == 0) {
				k = i - 1;
				while (k > 0 && array1[k][j] == 0) {
					k--;
				}
				array1[i][j] = array1[k][j];
				array1[k][j] = 0;
			}
		}
	}

	print_graph(28, array1, array, ROWS, COLS, SCORE);  // 消除操作

	cct_setcolor(0, 7);
	if (option <= 7) {
		cout << "按回车键进行新值填充…                          ";
		while (getchar() != '\n');
	}
	else {
		Sleep(1000);
	}

	print_graph(13, array1, array1, ROWS, COLS, SCORE);  // 新值填充后的数组


	// 拷贝，更新旧数组
	for (int i = 0; i < ROWS; i++)
		for (int j = 0; j < COLS; j++)
			array[i][j] = array1[i][j];
}
void print_graph(int n, int array[MAX_ROWS][MAX_COLS], int array_old[MAX_ROWS][MAX_COLS], int ROWS, int COLS, int* SCORE)
{
	int x = 0, y = 1;
	cout << endl;
	if (n == 4 || n == 6) {
		cct_showstr(2 * x, y, "╔", 15, 0);
		cct_showstr(2 * (x + 1), y, "═", 15, 0, COLS);
		cct_showstr(2 * (x + COLS + 1), y, "╗", 15, 0);
	}
	else if (n == 5 || !(n % 7)) {
		cct_showstr(2 * x, y, "╔", 15, 0);
		cct_showstr(2 * (x + 1), y, "═╦", 15, 0, COLS - 1);
		cct_showstr(4 * (x + COLS - 1) + 2, y, "═", 15, 0, 1);
		cct_showstr(4 * (x + COLS), y, "╗", 15, 0);
	}
	for (int i = 0;i < ROWS;i++) {
		for (int j = -1;j <= COLS;j++) {
			if (n == 13) {  // 填充
				if (j != -1 && j != COLS && array[i][j] == 0)
					array_old[i][j] = rand() % 9 + 1;
				//continue;
			}
			if (j == -1 || j == COLS) {
				if (n == 4 || n == 6)
					cct_showstr(2 * (x + j + 1), y + i + 1, "║", 15, 0);
				if ((n == 5 || !(n % 7)) && j == -1) {
					cct_showstr(2 * (x + j + 1), y + 2 * i + 1, "║", 15, 0);
					if (i != ROWS - 1)
						cct_showstr(2 * (x + j + 1), y + 2 * i + 2, "╠", 15, 0);
				}
			}
			else {
				if (n == 4 || n == 6) {
					if (n == 6 && is_matching(array, ROWS, COLS, i, j))
						cct_showstr(2 * (x + j + 1), y + i + 1, "●", array[i][j], 0);
					else
						cct_showstr(2 * (x + j + 1), y + i + 1, "○", array[i][j], 0);
				}
				if (n == 5 || !(n % 7) || n == 8 || n == 13) {
					if (n >= 7 && is_matching(array_old, ROWS, COLS, i, j))
						cct_showstr(4 * (x + j) + 2, y + 2 * i + 1, "●", array_old[i][j], 0);

					else
						cct_showstr(4 * (x + j) + 2, y + 2 * i + 1, "○", array_old[i][j], 0);

					cct_showstr(4 * (x + j) + 4, y + 2 * i + 1, "║", 15, 0);
					if (i != ROWS - 1)
						cct_showstr(4 * (x + j) + 2, y + 2 * i + 2, "═", 15, 0);
					if (j != COLS - 1 && i != ROWS - 1)
						cct_showstr(4 * (x + j) + 4, y + 2 * i + 2, "╬", 15, 0);
					else if (i != ROWS - 1 && j == COLS - 1)
						cct_showstr(4 * (x + j) + 4, y + 2 * i + 2, "╣", 15, 0);
				}
			}
		}
	}

	if (n == 35) {  // 可交换提示
		int array0[MAX_ROWS][MAX_COLS] = { 0 };
		hints2(array, array0, ROWS, COLS);
	}

	x = 0;
	y = (n % 2 + 1) * ROWS + 1 + !(n % 2);
	if (!(n % 7))
		y = (7 % 2 + 1) * ROWS + 1 + !(7 % 2);

	if (n == 4 || n == 6) {
		cct_showstr(2 * x, y, "╚", 15, 0);
		cct_showstr(2 * (x + 1), y, "═", 15, 0, COLS);
		cct_showstr(2 * (x + COLS + 1), y, "╝", 15, 0);
	}
	else if (n == 5 || !(n % 7) || n == 8 || n == 9) {
		cct_showstr(2 * x, y, "╚", 15, 0);
		cct_showstr(2 * (x + 1), y, "═╩", 15, 0, COLS - 1);
		cct_showstr(4 * (x + COLS - 1) + 2, y, "═", 15, 0, 1);
		cct_showstr(4 * (x + COLS), y, "╝", 15, 0);
	}

	if (n == 28) {  // 消除演示
		x = 0;
		y = 1;
		for (int i = 0;i < ROWS;i++) {
			for (int j = 0;j < COLS;j++) {
				if (is_matching(array_old, ROWS, COLS, i, j)) {
					blink_and_remove(array_old, array_old[i][j], i, j);
					(*SCORE)++;
				}
			}
		}
	}

	x = 0;
	y = 2 * ROWS + 1;
	cct_gotoxy(x, y);
	cct_setcolor(0, 7);
	cout << endl << endl;
}
void operate_graph(int array[MAX_ROWS][MAX_COLS], int option, int ROWS, int COLS)
{
	int score = 0;
	cout << "按回车键显示图形…                        ";
	while (getchar() != '\n');
	cct_cls();
	int x = 0, y = 1;
	print_graph(option, array, array, ROWS, COLS, NULL);
	if (option == 7) {
		while (1) {
			if (find_if(array, ROWS, COLS)) {
				cout << "按回车键进行消除及下落除0的操作…                         ";
				while (getchar() != '\n');
				show_graph_with_blank_and_fill(option, array, ROWS, COLS, &score);
			}
			else {
				cout << "按回车键显示消除提示…                       ";
				while (getchar() != '\n');
				print_graph(35, array, array, ROWS, COLS, &score);
				break;
			}
		}
		x = 0;
		y = (option % 2 + 1) * ROWS + 1;
		cct_gotoxy(x, y + 2);
	}
}
void operate_game(int array[MAX_ROWS][MAX_COLS], int option, int ROWS, int COLS)
{
	static int score = 0;
	int mark[MAX_ROWS][MAX_COLS] = { 0 };
	int x = 0, y = 1;
	int selected[2][2] = { 0 };
	int num = 0;

	int MX, MY, MAction, keycode1, keycode2;
	while (1) {  // 初始消除
		if (find_if(array, ROWS, COLS)) {
			show_graph_with_blank_and_fill(option, array, ROWS, COLS, &score);
			Sleep(1000);
		}
		else {
			print_graph(35, array, array, ROWS, COLS, &score);
			hints2(array, mark, ROWS, COLS);
			break;
		}
	}
	cct_gotoxy(0, 0);
	cout << "（当前分数：" << score << " 右键退出）" << endl;

	while (true) {  // 正式游戏
		int array_for_swap_check[MAX_ROWS][MAX_COLS];
		// 拷贝
		for (int i = 0; i < ROWS; i++)
			for (int j = 0; j < COLS; j++)
				array_for_swap_check[i][j] = array[i][j];

		cct_enable_mouse();
		int event = cct_read_keyboard_and_mouse(MX, MY, MAction, keycode1, keycode2);

		cct_gotoxy(0, 0);
		cout << "（当前分数：" << score << " 右键退出）" << endl;
		cct_gotoxy(x, 2 * ROWS + 2);
		cout << "[当前光标] ";

		char MY_y = MY / 2 + 'A' - 1;
		int MX_x = (MX + 1) / 4;
		// 判断位置
		if (MY_y >= 'A' && MY_y <= (ROWS + 'A' - 1) && MX_x >= 1 && MX_x <= COLS &&
			!(MY % 2) && !((MX + 1) % 4)) {
		}
		else if (MY_y >= 'A' && MY_y <= (ROWS + 'A' - 1) && MX_x >= 0 && MX_x <= COLS &&
			!(MY % 2) && !((MX + 2) % 4)) {
			MX_x = (MX + 2) / 4;
		}
		else {
			cout << "位置非法                                                      ";
			continue;
		}
		// 判断动作
		if (event == CCT_MOUSE_EVENT && MAction == MOUSE_ONLY_MOVED)
		{
			cout << MY_y << "行" << MX_x << "列                                   ";
		}
		else if (event == CCT_MOUSE_EVENT && MAction == MOUSE_LEFT_BUTTON_CLICK) {
			cct_gotoxy(0, 2 * ROWS + 2);
			if (mark[int(MY_y - 'A')][MX_x - 1]) {

				if (option == 8) {
					cout << "当前选择" << MY_y << "行" << MX_x << "列                  ";
					break;
				}

				else if (option == 9) {

					if (num == 0)
						cout << "当前选择" << MY_y << "行" << MX_x << "列                  ";

					if (MX_x != selected[0][1] || int(MY_y - 'A' + 1) != selected[0][2]) {
						selected[num][0] = int(MY_y - 'A');
						selected[num][1] = MX_x - 1;
						if (num == 0) {
							num++;
							continue;
						}
					}
					else
						continue;

					if (num == 1 && (!are_adjacent(selected) || are_adjacent(selected) && !can_swap(array_for_swap_check, selected, ROWS, COLS))) {
						cout << "不能交换                       ";
						num = 0;
						for (int i = 0; i < 2; ++i) {
							for (int j = 0; j < 2; ++j) {
								selected[i][j] = 0;
							}
						}
						continue;
					}
					else if (num == 1 && are_adjacent(selected)) {
						for (int i = 0; i < ROWS; i++)
							for (int j = 0; j < COLS; j++)
								array_for_swap_check[i][j] = array[i][j];
						if (can_swap(array_for_swap_check, selected, ROWS, COLS)) {
							cout << "当前选择" << MY_y << "行" << MX_x << "列                  ";

							for (int i = 0; i < ROWS; i++)  // 更新数组
								for (int j = 0; j < COLS; j++)
									array[i][j] = array_for_swap_check[i][j];

							show_graph_with_blank_and_fill(option, array, ROWS, COLS, &score);

							for (int i = 0; i < ROWS; i++) {
								for (int j = 0; j < COLS; j++) {
									if (mark[i][j]) {// 检查是否还能继续游戏
										num = 0;
										for (int i = 0; i < 2; ++i) {
											for (int j = 0; j < 2; ++j) {
												selected[i][j] = 0;
											}
										}
										operate_game(array, option, ROWS, COLS);
										score = 0;
										return;
									}
								}
							}

						}
					}

				}
			}
			else {
				cct_gotoxy(x, 2 * ROWS + 2);
				cout << "不能选择" << MY_y << "行" << MX_x << "列                  ";
			}

		}
		else if (event == CCT_MOUSE_EVENT && MAction == MOUSE_RIGHT_BUTTON_CLICK) {
			return;
		}
		cct_gotoxy(x, y + 1);
	}
}