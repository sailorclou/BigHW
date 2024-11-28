/* 2351044 大数据 崔艺洋 */
#define _CRT_SECURE_NO_WARNINGS
#include "90-01-b2-gmw-magic_ball.h"
#include "../include/tools.h"
#include "../include/cmd_gmw_tools.h"

void initial(CONSOLE_GRAPHICS_INFO* const pCGI)
{
	while (1) {
		cout << "请输入行数(5-9)：" << endl;
		cin >> pCGI->row_num;
		if (pCGI->row_num >= 5 && pCGI->row_num <= 9 && cin.good())
			break;
		else if (!cin.good()) {
			cin.clear();
			while (getchar() != '\n');
		}
	}
	while (1) {
		cout << "请输入列数(5-9)：" << endl;
		cin >> pCGI->col_num;
		if (pCGI->col_num >= 5 && pCGI->col_num <= 9 && cin.good())
			break;
		else if (!cin.good()) {
			cin.clear();
			while (getchar() != '\n');
		}
	}
	cout << endl;
	gmw_init(pCGI, pCGI->row_num, pCGI->col_num, 15, 0);
	gmw_set_frame_color(pCGI, 15, 0);
	gmw_set_font(pCGI, "新宋体", 16, 8);
	gmw_set_status_line_switch(pCGI, TOP_STATUS_LINE, 1);
	gmw_set_status_line_switch(pCGI, LOWER_STATUS_LINE, 1);
	gmw_set_status_line_color(pCGI, TOP_STATUS_LINE, 0, 15);
	gmw_set_status_line_color(pCGI, LOWER_STATUS_LINE, 0, 15);

	return;
}
void generate_array(int array[MAX_ROWS][MAX_COLS], int ROWS, int COLS)
{
	srand(unsigned int(time(0)));
	for (int i = 0;i < ROWS;i++) {
		for (int j = 0;j < COLS;j++) {
			if (!array[i][j])
				array[i][j] = rand() % 9 + 1;
		}
	}
}
bool find_if(int array[MAX_ROWS][MAX_COLS], int ROWS, int COLS)
{
	for (int i = 0;i < ROWS;i++)
		for (int j = 0;j < COLS;j++) {
			if (array[i][j]) {
				if (!(i == ROWS - 1 || i == ROWS - 2) &&
					array[i][j] == array[i + 1][j] && array[i][j] == array[i + 2][j])
					return true;  // 纵向检查
				if (!(j == COLS - 1 || j == COLS - 2) &&
					array[i][j] == array[i][j + 1] && array[i][j] == array[i][j + 2])
					return true;  // 横向检查
			}
		}

	return false;
}
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
void hints(int array[MAX_ROWS][MAX_COLS], int mark[MAX_ROWS][MAX_COLS], CONSOLE_GRAPHICS_INFO* const pCGI, BLOCK_DISPLAY_INFO* const bdi, int ROWS, int COLS)
{
	(bdi + 2)->fgcolor = 0;
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			// 检查垂直方向连续相等，并处理边界问题
			if (i < ROWS - 1 && array[i][j] == array[i + 1][j]) {
				if (i > 0 && j > 0 && array[i][j] == array[i - 1][j - 1]) {
					(bdi + 2)->bgcolor = array[i-1][j-1];
					gmw_draw_block(pCGI, i-1, j-1, 2, bdi);
					(bdi + 2)->bgcolor = array[i-1][j];
					gmw_draw_block(pCGI, i-1, j, 2, bdi);
					mark[i - 1][j - 1] = 1;
					mark[i - 1][j] = 1;
				}  // 左上角
				if (i < ROWS - 2 && j > 0 && array[i][j] == array[i + 2][j - 1]) {
					(bdi + 2)->bgcolor = array[i + 2][j - 1];
					gmw_draw_block(pCGI, i + 2, j - 1, 2, bdi);
					(bdi + 2)->bgcolor = array[i + 2][j];
					gmw_draw_block(pCGI, i + 2, j, 2, bdi);
					mark[i + 2][j - 1] = 1;
					mark[i + 2][j] = 1;
				}  // 左下角
				if (i < ROWS - 2 && j < COLS - 1 && array[i][j] == array[i + 2][j + 1]) {
					(bdi + 2)->bgcolor = array[i + 2][j + 1];
					gmw_draw_block(pCGI, i + 2, j + 1, 2, bdi);
					(bdi + 2)->bgcolor = array[i + 2][j];
					gmw_draw_block(pCGI, i + 2, j, 2, bdi);
					mark[i + 2][j + 1] = 1;
					mark[i + 2][j] = 1;
				}  // 右下角
				if (i > 0 && j < COLS - 1 && array[i][j] == array[i - 1][j + 1]) {
					(bdi + 2)->bgcolor = array[i - 1][j + 1];
					gmw_draw_block(pCGI, i - 1, j + 1, 2, bdi);
					(bdi + 2)->bgcolor = array[i - 1][j];
					gmw_draw_block(pCGI, i - 1, j, 2, bdi);
					mark[i - 1][j + 1] = 1;
					mark[i - 1][j] = 1;
				}  // 右上角
				if (i > 1 && array[i][j] == array[i - 2][j]) {
					(bdi + 2)->bgcolor = array[i - 2][j];
					gmw_draw_block(pCGI, i - 2, j, 2, bdi);
					(bdi + 2)->bgcolor = array[i - 1][j];
					gmw_draw_block(pCGI, i - 1, j, 2, bdi);
					mark[i - 2][j] = 1;
					mark[i - 1][j] = 1;
				}  // 上
				if (i < ROWS - 2 && array[i][j] == array[i + 3][j]) {
					(bdi + 2)->bgcolor = array[i + 3][j];
					gmw_draw_block(pCGI, i + 3, j, 2, bdi);
					(bdi + 2)->bgcolor = array[i + 2][j];
					gmw_draw_block(pCGI, i + 2, j, 2, bdi);
					mark[i + 3][j] = 1;
					mark[i + 2][j] = 1;
				}  // 下
			}
			// 检查水平方向连续相等，并处理边界问题
			if (j < COLS - 1 && array[i][j] == array[i][j + 1]) {
				if (i > 0 && j > 0 && array[i][j] == array[i - 1][j - 1]) {
					(bdi + 2)->bgcolor = array[i - 1][j - 1];
					gmw_draw_block(pCGI, i - 1, j - 1, 2, bdi);
					(bdi + 2)->bgcolor = array[i][j - 1];
					gmw_draw_block(pCGI, i, j - 1, 2, bdi);
					mark[i - 1][j - 1] = 1;
					mark[i][j - 1] = 1;
				}  // 左上角
				if (i < ROWS - 1 && j > 0 && array[i][j] == array[i + 1][j - 1]) {
					(bdi + 2)->bgcolor = array[i + 1][j - 1];
					gmw_draw_block(pCGI, i + 1, j - 1, 2, bdi);
					(bdi + 2)->bgcolor = array[i][j - 1];
					gmw_draw_block(pCGI, i, j - 1, 2, bdi);
					mark[i + 1][j - 1] = 1;
					mark[i][j - 1] = 1;
				}  // 左下角
				if (i < ROWS - 1 && j < COLS - 2 && array[i][j] == array[i + 1][j + 2]) {
					(bdi + 2)->bgcolor = array[i + 1][j + 2];
					gmw_draw_block(pCGI, i + 1, j + 2, 2, bdi);
					(bdi + 2)->bgcolor = array[i][j + 2];
					gmw_draw_block(pCGI, i, j + 2, 2, bdi);
					mark[i + 1][j + 2] = 1;
					mark[i][j + 2] = 1;
				}  // 右下角
				if (i > 0 && j < COLS - 2 && array[i][j] == array[i - 1][j + 2]) {
					(bdi + 2)->bgcolor = array[i - 1][j + 2];
					gmw_draw_block(pCGI, i - 1, j + 2, 2, bdi);
					(bdi + 2)->bgcolor = array[i][j + 2];
					gmw_draw_block(pCGI, i, j + 2, 2, bdi);
					mark[i - 1][j + 2] = 1;
					mark[i][j + 2] = 1;
				}  // 右上角
				if (j > 1 && array[i][j] == array[i][j - 2]) {
					(bdi + 2)->bgcolor = array[i][j - 2];
					gmw_draw_block(pCGI, i, j - 2, 2, bdi);
					(bdi + 2)->bgcolor = array[i][j - 1];
					gmw_draw_block(pCGI, i, j - 1, 2, bdi);
					mark[i][j - 2] = 1;
					mark[i][j - 1] = 1;
				}  // 左
				if (j < COLS - 2 && array[i][j] == array[i][j + 3]) {
					(bdi + 2)->bgcolor = array[i][j + 3];
					gmw_draw_block(pCGI, i, j + 3, 2, bdi);
					(bdi + 2)->bgcolor = array[i][j + 2];
					gmw_draw_block(pCGI, i, j + 2, 2, bdi);
					mark[i][j + 3] = 1;
					mark[i][j + 2] = 1;
				}  // 右
			}
			// 检查垂直方向间隔相等，并处理边界问题
			if (i < ROWS - 2 && array[i][j] == array[i + 2][j]) {
				if (i > 0 && j > 0 && array[i][j] == array[i + 1][j - 1]) {
					(bdi + 2)->bgcolor = array[i + 1][j - 1];
					gmw_draw_block(pCGI, i + 1, j - 1, 2, bdi);
					(bdi + 2)->bgcolor = array[i + 1][j];
					gmw_draw_block(pCGI, i + 1, j, 2, bdi);
					mark[i + 1][j - 1] = 1;
					mark[i + 1][j] = 1;
				}  // 左
				if (i < ROWS - 2 && j < COLS - 1 && array[i][j] == array[i + 1][j + 1]) {
					(bdi + 2)->bgcolor = array[i + 1][j + 1];
					gmw_draw_block(pCGI, i + 1, j + 1, 2, bdi);
					(bdi + 2)->bgcolor = array[i + 1][j];
					gmw_draw_block(pCGI, i + 1, j, 2, bdi);
					mark[i + 1][j + 1] = 1;
					mark[i + 1][j] = 1;
				}  // 右
			}
			// 检查水平方向间隔相等，并处理边界问题
			if (j < COLS - 2 && array[i][j] == array[i][j + 2]) {
				if (i > 0 && j > 0 && array[i][j] == array[i - 1][j + 1]) {
					(bdi + 2)->bgcolor = array[i - 1][j + 1];
					gmw_draw_block(pCGI, i - 1, j + 1, 2, bdi);
					(bdi + 2)->bgcolor = array[i][j + 1];
					gmw_draw_block(pCGI, i, j + 1, 2, bdi);
					mark[i - 1][j + 1] = 1;
					mark[i][j + 1] = 1;
				}  // 上
				if (i < ROWS - 2 && j < COLS - 2 && array[i][j] == array[i + 1][j + 1]) {
					(bdi + 2)->bgcolor = array[i + 1][j + 1];
					gmw_draw_block(pCGI, i + 1, j + 1, 2, bdi);
					(bdi + 2)->bgcolor = array[i][j + 1];
					gmw_draw_block(pCGI, i, j + 1, 2, bdi);
					mark[i + 1][j + 1] = 1;
					mark[i][j + 1] = 1;
				}  // 下
			}
		}
	}
	cct_setcolor(0, 7);
}//
void remove(int array_old[MAX_ROWS][MAX_COLS], CONSOLE_GRAPHICS_INFO* const pCGI, int i, int j, BLOCK_DISPLAY_INFO* const bdi)
{
	(bdi + 1)->bgcolor = array_old[i][j];
	(bdi + 1)->fgcolor = 0;
	for (int k = 0;k < 3;k++) {
		gmw_draw_block(pCGI, i, j, 3, bdi);
		Sleep(100);
		gmw_draw_block(pCGI, i, j, 1, bdi);
	}
	Sleep(100);
	gmw_draw_block(pCGI, i, j, 0, bdi);
}
void check_setzero_update(int array[MAX_ROWS][MAX_COLS], CONSOLE_GRAPHICS_INFO* const pCGI, int ROWS, int COLS, int* SCORE, BLOCK_DISPLAY_INFO* const bdi)
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
	//消除
	for (int i = 0;i < ROWS;i++) {
		for (int j = 0;j < COLS;j++) {
			if (is_matching(array, ROWS, COLS, i, j)) {
				(bdi + 5)->bgcolor = array[i][j];
				(bdi + 5)->fgcolor = 0;
				gmw_draw_block(pCGI, i, j, 5, bdi);
			}
		}
	}

	for (int i = 0;i < ROWS;i++) {
		for (int j = 0;j < COLS;j++) {
			if (is_matching(array, ROWS, COLS, i, j)) {
				remove(array1, pCGI, i, j, bdi);  // 消除操作
				(*SCORE)++;
			}
		}
	}

	Sleep(1000);
	generate_array(array1, ROWS, COLS);
	draw_graph(array1, pCGI, bdi);  // 新值填充后的数组

	// 拷贝，更新旧数组
	for (int i = 0; i < ROWS; i++)
		for (int j = 0; j < COLS; j++)
			array[i][j] = array1[i][j];
}
void draw_graph(int array[MAX_ROWS][MAX_COLS], CONSOLE_GRAPHICS_INFO* const pCGI, BLOCK_DISPLAY_INFO* const bdi)
{
	gmw_draw_frame(pCGI);
	for (int i = 0; i < pCGI->row_num; i++)
		for (int j = 0; j < pCGI->col_num; j++) {
			(bdi+1)->bgcolor = array[i][j];
			(bdi+1)->fgcolor = 0;
			gmw_draw_block(pCGI, i, j, 1, bdi);
		}
}
void game(int array[MAX_ROWS][MAX_COLS], CONSOLE_GRAPHICS_INFO* const pCGI, BLOCK_DISPLAY_INFO* const bdi)
{
	static int score = 0;
	char info[256];
	int ROWS = pCGI->row_num, COLS = pCGI->col_num;
	int mark[MAX_ROWS][MAX_COLS] = { 0 };
	int x = 0, y = 1;
	int selected[2][2] = { 0 };
	int num = 0;
	draw_graph(array, pCGI, bdi);
	int MX, MY, MAction, keycode1, keycode2;
	while (1) {  // 初始消除
		hints(array, mark, pCGI, bdi, ROWS, COLS);
		Sleep(1000);
		if (find_if(array, ROWS, COLS)) {
			check_setzero_update(array, pCGI, ROWS, COLS, &score, bdi);
			Sleep(1000);
		}
		else {
			break;
		}
	}

	sprintf(info, "当前分数: %d, 右键退出", score);
	gmw_status_line(pCGI, TOP_STATUS_LINE, info);

	while (true) {  // 正式游戏
		int array_for_swap_check[MAX_ROWS][MAX_COLS];
		// 拷贝
		for (int i = 0; i < ROWS; i++)
			for (int j = 0; j < COLS; j++)
				array_for_swap_check[i][j] = array[i][j];

		cct_enable_mouse();
		int event = cct_read_keyboard_and_mouse(MX, MY, MAction, keycode1, keycode2);

		sprintf(info, "当前分数: %d, 右键退出", score);
		gmw_status_line(pCGI, TOP_STATUS_LINE, info);

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
			sprintf(info, "位置非法                                 ");
			gmw_status_line(pCGI, LOWER_STATUS_LINE, info);
			continue;
		}
		// 判断动作
		if (event == CCT_MOUSE_EVENT && MAction == MOUSE_ONLY_MOVED)
		{
			sprintf(info, "[当前光标] %c行%d列                                         ", MY_y, MX_x);
			gmw_status_line(pCGI, LOWER_STATUS_LINE, info);
		}
		else if (event == CCT_MOUSE_EVENT && MAction == MOUSE_LEFT_BUTTON_CLICK) {
			cct_gotoxy(0, 2 * ROWS + 2);
			if (mark[int(MY_y - 'A')][MX_x - 1]) {
				if (num == 0) {
					sprintf(info, "当前选择 %c行%d列                                     ", MY_y, MX_x);
					gmw_status_line(pCGI, LOWER_STATUS_LINE, info);
				}

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
					sprintf(info, "不能交换                                             ");
					gmw_status_line(pCGI, LOWER_STATUS_LINE, info);
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
						sprintf(info, "当前选择 %c行%d列                                ", MY_y, MX_x);
						gmw_status_line(pCGI, LOWER_STATUS_LINE, info);

						for (int i = 0; i < ROWS; i++)  // 更新数组
							for (int j = 0; j < COLS; j++)
								array[i][j] = array_for_swap_check[i][j];

						draw_graph(array, pCGI, bdi);
						check_setzero_update(array, pCGI, ROWS, COLS, &score, bdi);

						for (int i = 0; i < ROWS; i++) {
							for (int j = 0; j < COLS; j++) {
								if (mark[i][j]) {// 检查是否还能继续游戏
									num = 0;
									for (int i = 0; i < 2; ++i) {
										for (int j = 0; j < 2; ++j) {
											selected[i][j] = 0;
										}
									}
									game(array, pCGI, bdi);
									score = 0;
									return;
								}
							}
						}

					}
				}

			}

			else {
				cct_gotoxy(x, 2 * ROWS + 2);
				sprintf(info, "不能选择 %c行%d列                                          ", MY_y, MX_x);
				gmw_status_line(pCGI, LOWER_STATUS_LINE, info);
			}

		}
		else if (event == CCT_MOUSE_EVENT && MAction == MOUSE_RIGHT_BUTTON_CLICK) {
			return;
		}
		cct_gotoxy(x, y + 1);
	}
}
void operate(CONSOLE_GRAPHICS_INFO* const pCGI, BLOCK_DISPLAY_INFO* const bdi)
{
	int array[MAX_ROWS][MAX_COLS] = { 0 };
	generate_array(array, pCGI->row_num, pCGI->col_num);
	game(array, pCGI, bdi);
}