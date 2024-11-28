/* 2351044 大数据 崔艺洋 */
#define _CRT_SECURE_NO_WARNINGS
#include "90-02-b1-gmw-pop_star.h"
#include "../include/tools.h"
#include "../include/cmd_gmw_tools.h"

void initial(CONSOLE_GRAPHICS_INFO* const pCGI)
{
	while (1) {
		cout << "请输入行数(8-10)：" << endl;
		cin >> pCGI->row_num;
		if (pCGI->row_num >= 8 && pCGI->row_num <= 10 && cin.good())
			break;
		else if (!cin.good()) {
			cin.clear();
			while (getchar() != '\n');
		}
	}
	while (1) {
		cout << "请输入列数(8-10)：" << endl;
		cin >> pCGI->col_num;
		if (pCGI->col_num >= 8 && pCGI->col_num <= 10 && cin.good())
			break;
		else if (!cin.good()) {
			cin.clear();
			while (getchar() != '\n');
		}
	}
	cout << endl;
	gmw_init(pCGI, pCGI->row_num, pCGI->col_num, 15, 0);
	gmw_set_frame_color(pCGI, 15, 0);
	gmw_set_font(pCGI, "新宋体", 12, 6);
	gmw_set_status_line_switch(pCGI, TOP_STATUS_LINE, 1);
	gmw_set_status_line_switch(pCGI, LOWER_STATUS_LINE, 1);
	gmw_set_status_line_color(pCGI, TOP_STATUS_LINE, 0, 15);
	gmw_set_status_line_color(pCGI, LOWER_STATUS_LINE, 0, 15);

	gmw_set_block_border_switch(pCGI, 1);
	pCGI->CFI.separator = 0;
	gmw_set_frame_style(pCGI, 6, 3, 0);

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
bool has_adjacent_same(int grid[MAX_ROWS][MAX_COLS], int ROWS, int COLS) {
	// 方向数组：上、下、左、右
	const int dx[] = { 1, -1, 0, 0 };
	const int dy[] = { 0, 0, 1, -1 };
	// 遍历每一个元素
	for (int x = 0; x < ROWS; ++x) {
		for (int y = 0; y < COLS; ++y) {
			// 检查该元素的上下左右
			for (int i = 0; i < 4; ++i) {
				int nx = x + dx[i];
				int ny = y + dy[i];

				// 判断是否在数组边界内
				if (nx >= 0 && nx < ROWS && ny >= 0 && ny < COLS) {
					// 如果相邻的值相同
					if (grid[x][y] == grid[nx][ny] && grid[x][y] != 0) {
						return true; // 有相邻相同值
					}
				}
			}
		}
	}

	return false; // 没有相邻相同值
}
void move_column_to_left(int array[MAX_ROWS][MAX_COLS], int ROWS, int COLS)
{
	int num_blank = 0;
	for (int j = 0; j < COLS; j++) {
		bool if_all_zero = true;

		// 检查该列是否全为0
		for (int i = 0; i < ROWS; i++) {
			if (array[i][j] != 0) {
				if_all_zero = false;
				break;
			}
		}

		// 如果该列全为0，则将该列移到最右边
		if (if_all_zero) {
			num_blank++;
			// 把从该列到最后一列依次左移
			for (int k = j; k < COLS - 1; k++) {
				for (int i = 0; i < ROWS; i++) {
					array[i][k] = array[i][k + 1];
				}
			}

			// 将最后一列置为全0
			for (int i = 0; i < ROWS; i++) {
				array[i][COLS - num_blank] = 0;
			}
		}
	}
}
void drop(int array[MAX_ROWS][MAX_COLS], int visited[MAX_ROWS][MAX_COLS], int ROWS, int COLS)
{
	// 把0移到列首
	int k;
	for (int j = 0;j < COLS;j++) {
		for (int i = ROWS - 1;i > 0;i--) {
			if (visited[i][j] == 1) {
				k = i - 1;
				while (k > 0 && visited[k][j] == 1) {
					k--;
				}
				array[i][j] = array[k][j];
				array[k][j] = 0;
				visited[i][j] = visited[k][j];
				visited[k][j] = 1;
			}
		}
	}

}
void dfs(int array[MAX_ROWS][MAX_COLS], int visited[MAX_ROWS][MAX_COLS], int ROWS, int COLS, int x, int y, int color)
{
	const int dx[] = { 1, -1, 0, 0 }; // 方向数组: 上、下、左、右
	const int dy[] = { 0, 0, 1, -1 };

	visited[x][y] = true;
	array[x][y] = 0;
	// 遍历四个方向
	for (int i = 0; i < 4; ++i) {
		int nx = x + dx[i];
		int ny = y + dy[i];
		// 检查新位置是否在边界内，且颜色相同，且未被访问
		if (nx >= 0 && nx < ROWS && ny >= 0 && ny < COLS &&
			array[nx][ny] == color && !visited[nx][ny])
		{
			dfs(array, visited, ROWS, COLS, nx, ny, color);
		}
	}
}
void draw_graph(int array[MAX_ROWS][MAX_COLS], int visited[MAX_ROWS][MAX_COLS], CONSOLE_GRAPHICS_INFO* const pCGI, BLOCK_DISPLAY_INFO* const bdi)
{
	gmw_draw_frame(pCGI);
	for (int i = 0; i < pCGI->row_num; i++)
		for (int j = 0; j < pCGI->col_num; j++) {
			if (visited[i][j] == 1) {
				gmw_draw_block(pCGI, i, j, 0, bdi);
			}
			else {
				(bdi + 1)->bgcolor = array[i][j];
				(bdi + 1)->fgcolor = 0;
				gmw_draw_block(pCGI, i, j, 1, bdi);
			}
		}
}
void game(int array[MAX_ROWS][MAX_COLS], CONSOLE_GRAPHICS_INFO* const pCGI, BLOCK_DISPLAY_INFO* const bdi)
{
	int ROWS = pCGI->row_num, COLS = pCGI->col_num;
	char info[256];
	int num_total = 0, score = 0, num_single = 0, num_old = 0, score_single = 0;
	int visited[MAX_ROWS][MAX_COLS] = { {0} }, visited_copy[MAX_ROWS][MAX_COLS] = { {0} };  ///
	int MX = 0, MY = 0, MAction, keycode1, keycode2;

	draw_graph(array, visited, pCGI, bdi);
	int i_old = ROWS, j_old = COLS;
	while (1) {
		cct_enable_mouse();
		int event = cct_read_keyboard_and_mouse(MX, MY, MAction, keycode1, keycode2);
		if (event == CCT_MOUSE_EVENT && MAction == MOUSE_ONLY_MOVED) {
			char MY_y = (MY - 2) / pCGI->CFI.block_high + 'A';
			int MX_x = (MX - 2) / pCGI->CFI.block_width;
			int i = int(MY_y - 'A');
			int j = MX_x;
			// 还原
			if (i_old == i && j_old == j) {
				continue;
			}
			else if (i_old >= 0 && i_old < ROWS && j_old >= 0 && j_old < COLS) {
				if (visited[i_old][j_old] != 1) {
					(bdi + 1)->bgcolor = array[i_old][j_old];
					(bdi + 1)->fgcolor = 0;
					gmw_draw_block(pCGI, i_old, j_old, 1, bdi);
				}
			}

			// 判断位置
			if (i >= 0 && i < ROWS && j >= 0 && j < COLS) {
				if (visited[i][j] != 1) {
					(bdi + 1)->bgcolor = array[i][j];
					(bdi + 1)->fgcolor = 15;
					gmw_draw_block(pCGI, i, j, 1, bdi);
				}
			}
			else {                                                 
				sprintf(info, "位置非法                                         ");
				gmw_status_line(pCGI, LOWER_STATUS_LINE, info);
				continue;
			}
			
			sprintf(info, "[当前光标] %c行%d列                                         ", MY_y, MX_x);
			gmw_status_line(pCGI, LOWER_STATUS_LINE, info);

		}
		else if (event == CCT_MOUSE_EVENT && MAction == MOUSE_LEFT_BUTTON_CLICK) {
			char MY_y = (MY - 2) / pCGI->CFI.block_high + 'A';
			int MX_x = (MX - 2) / pCGI->CFI.block_width;
			int i = int(MY_y - 'A');
			int j = MX_x;
			if (i >= 0 && i < ROWS && j >= 0 && j < COLS) {
				if (array[i][j] == array[i - 1][j] && i > 0
					|| array[i][j] == array[i][j - 1] && j > 0
					|| array[i][j] == array[i + 1][j] && i < ROWS - 1
					|| array[i][j] == array[i][j + 1] && j < COLS - 1)
				{
					for (int a = 0;a < ROWS;a++) {
						for (int b = 0;b < COLS;b++) {
							visited_copy[a][b] = visited[a][b];
						}
					}
					sprintf(info, "请确认是否把%c行%d列及周围的相同星星消除(Y / N / Q)：", MY_y, MX_x);
					gmw_status_line(pCGI, LOWER_STATUS_LINE, info);
					char choice;
					while (1) {
						choice = _getche();
						if (choice == 'Q' || choice == 'q')
							return;
						else if (choice == 'N' || choice == 'n') {
							for (int a = 0;a < ROWS;a++) {
								for (int b = 0;b < COLS;b++) {
									visited[a][b] = visited_copy[a][b];
								}
							}
							break;
						}
						else if (choice == 'Y' || choice == 'y') {
							// 消除
							num_old = num_total;
							num_total = 0;

							dfs(array, visited, ROWS, COLS, i, j, array[i][j]);
							draw_graph(array, visited, pCGI, bdi);
							for (int i = 0;i < ROWS;i++) {
								for (int j = 0;j < COLS;j++) {
									num_total += visited[i][j];
									if (visited[i][j] == 1) {
										bdi->bgcolor = 0;
										bdi->fgcolor = 0;
										gmw_draw_block(pCGI, i, j, 0, bdi);
									}
								}
							}
							Sleep(1000);
							drop(array, visited, ROWS, COLS);
							move_column_to_left(array, ROWS, COLS);
							draw_graph(array, visited, pCGI, bdi);
							for (int i = 0;i < ROWS;i++) {
								for (int j = 0;j < COLS;j++) {
									if (visited[i][j] == 1) {
										bdi->bgcolor = 0;
										bdi->fgcolor = 0;
										gmw_draw_block(pCGI, i, j, 0, bdi);
									}
								}
							}

							num_single = num_total - num_old;
							score_single = num_single * num_single * 5;
							score += score_single;

							sprintf(info, "本次得: %d, 总得分: %d                                         ", score_single, score);
							gmw_status_line(pCGI, LOWER_STATUS_LINE, info);
							Sleep(2000);
							
							break;
						}
					}
					if (choice == 'N' || choice == 'n')
						continue;
				}
				else {
					sprintf(info, "周围无相同值，请重新选择                                         ");
					gmw_status_line(pCGI, LOWER_STATUS_LINE, info);
					continue;
				}
			}
		}

		if (!has_adjacent_same(array, ROWS, COLS)) {
			int num_left = ROWS * COLS - num_total;
			if (num_left < 10)
				score += (10 - num_left) * 180;
			sprintf(info, "游戏结束, 剩余数量: %d, 总得分: %d                                         ", num_left, score);
			gmw_status_line(pCGI, LOWER_STATUS_LINE, info);
			
			return;
		}

	}
}
void operate(CONSOLE_GRAPHICS_INFO* const pCGI, BLOCK_DISPLAY_INFO* const bdi)
{
	int array[MAX_ROWS][MAX_COLS] = { 0 };
	generate_array(array, pCGI->row_num, pCGI->col_num);
	game(array, pCGI, bdi);
}