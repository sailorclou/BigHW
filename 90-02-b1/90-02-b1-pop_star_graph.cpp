/* 2351044 大数据 崔艺洋 */

#include "90-02-b1-pop_star.h"

void print_graph(int n, int array[MAX_ROWS][MAX_COLS], int visited[MAX_ROWS][MAX_COLS], int ROWS, int COLS)
{
	int x = 0, y = 1;
	cct_gotoxy(x, y);
	if (n == 5) {
		cct_showstr(2 * x, y, "╔", 15, 0);
		cct_showstr(2 * (x + 1), y, "═╦", 15, 0, COLS - 1);
		cct_showstr(4 * (x + COLS - 1) + 2, y, "═", 15, 0, 1);
		cct_showstr(4 * (x + COLS), y, "╗", 15, 0);
	}
	else if (n >= 4) {
		cct_showstr(2 * x, y, "╔", 15, 0);
		cct_showstr(2 * (x + 1), y, "═", 15, 0, COLS);
		cct_showstr(2 * (x + COLS + 1), y, "╗", 15, 0);
	}
	for (int i = 0;i < ROWS;i++) {
		for (int j = -1;j <= COLS;j++) {
			
			if (j == -1 || j == COLS) {
				if ((n == 5) && j == -1) {
					cct_showstr(2 * (x + j + 1), y + 2 * i + 1, "║", 15, 0);
					if (i != ROWS - 1)
						cct_showstr(2 * (x + j + 1), y + 2 * i + 2, "╠", 15, 0);
				}
				else if (n >= 4 && n != 5) {
					cct_showstr(2 * (x + j + 1), y + i + 1, "║", 15, 0);
				}
				
			}
			else {
				if (n == 5) {
					cct_showstr(4 * (x + j) + 2, y + 2 * i + 1, "★", array[i][j], 0);

					cct_showstr(4 * (x + j) + 4, y + 2 * i + 1, "║", 15, 0);

					if (i != ROWS - 1)
						cct_showstr(4 * (x + j) + 2, y + 2 * i + 2, "═", 15, 0);
					if (j != COLS - 1 && i != ROWS - 1)
						cct_showstr(4 * (x + j) + 4, y + 2 * i + 2, "╬", 15, 0);
					else if (i != ROWS - 1 && j == COLS - 1)
						cct_showstr(4 * (x + j) + 4, y + 2 * i + 2, "╣", 15, 0);
				}
				else if (n >= 4) {
					if (visited[i][j] == 1) {
						cct_showstr(2 * (x + j + 1), y + i + 1, "  ", 7, 0);
					
					}
					else {
						cct_showstr(2 * (x + j + 1), y + i + 1, "★", array[i][j], 0);
					}
				}
				
			}
		}
	}

	x = 0;
	y = ROWS + 2;
	if (n == 5) {
		y = 2 * ROWS + 1;
	}

	if (n == 5) {
		cct_showstr(2 * x, y, "╚", 15, 0);
		cct_showstr(2 * (x + 1), y, "═╩", 15, 0, COLS - 1);
		cct_showstr(4 * (x + COLS - 1) + 2, y, "═", 15, 0, 1);
		cct_showstr(4 * (x + COLS), y, "╝", 15, 0);
	}
	else if (n >= 4) {
		cct_showstr(2 * x, y, "╚", 15, 0);
		cct_showstr(2 * (x + 1), y, "═", 15, 0, COLS);
		cct_showstr(2 * (x + COLS + 1), y, "╝", 15, 0);
	}

	x = 0;
	y = 2 * ROWS + 1;
	cct_gotoxy(x, y);
	cct_setcolor(0, 7);
	cout << endl << endl;
}
void operate_graph_no_wall(int array[MAX_ROWS][MAX_COLS], int option, int ROWS, int COLS)
{
	//int row, col;
	int num_total = 0, score = 0, num_single = 0, num_old = 0, score_single = 0;
	int visited[MAX_ROWS][MAX_COLS] = { {0} }, visited_copy[MAX_ROWS][MAX_COLS] = { {0} };  ///
	int MX=0, MY=0, MAction, keycode1, keycode2;
	int MX_old, MY_old;

	print_graph(option, array, visited, ROWS, COLS);
	int i_old = ROWS, j_old = COLS;
	while (1) {
		cct_enable_mouse();
		int event = cct_read_keyboard_and_mouse(MX, MY, MAction, keycode1, keycode2);
		if (event == CCT_MOUSE_EVENT && MAction == MOUSE_ONLY_MOVED) {
			char MY_y = MY + 'A' - 2;
			int MX_x = (MX - 2) / 2;
			int i = MY - 2;
			int j = MX_x;
			// 还原
			if (i_old == i && j_old == j) {
				continue;
			}
			else if (i_old >= 0 && i_old < ROWS && j_old >= 0 && j_old < COLS) {
				if (visited[i_old][j_old] != 1)
					cct_showstr(MX_old, MY_old, "★", array[i_old][j_old], 0);
				cct_setcolor(0, 7);
			}

			// 判断位置
			if (i >= 0 && i < ROWS && j >= 0 && j < COLS) {
				if (visited[i][j] != 1)
					cct_showstr((MX_x + 1) * 2, MY, "★", array[i][j], 7);
				cct_setcolor(0, 7);
			}
			else {
				cct_gotoxy(0, ROWS + 3);
				cout << "[当前光标]" << "位置非法                                                      ";
				continue;
			}
			cct_gotoxy(0, ROWS + 3);
			cout << "[当前光标]" << MY_y << "行" << MX_x << "列                ";

			i_old = MY - 2;
			j_old = MX_x;
			MY_old = MY;
			MX_old = (MX_x + 1) * 2;
		}
		else if (event == CCT_MOUSE_EVENT && MAction == MOUSE_LEFT_BUTTON_CLICK) {
			char MY_y = MY + 'A' - 2;
			int MX_x = (MX - 2) / 2;
			int i = MY - 2;
			int j = MX_x;
			if (i >= 0 && i < ROWS && j >= 0 && j < COLS) {
				if (option == 4) {
					cout << "\n选中了" << MY_y << "行" << MX_x << "列                  \n";
					return;
				}
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
					cct_gotoxy(0, ROWS + 3);
					cout << "请确认是否把" << MY_y << "行" << MX_x << "列及周围的相同星星消除(Y / N / Q)：";
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
							cout << endl;
							break;
						}
						else if (choice == 'Y' || choice == 'y') {
							// 消除
							num_old = num_total;
							num_total = 0;
							
							dfs(array, visited, ROWS, COLS, i, j, array[i][j]);
							print_graph(option, array, visited, ROWS, COLS);
							for (int i = 0;i < ROWS;i++) {
								for (int j = 0;j < COLS;j++) {
									num_total += visited[i][j];
								}
							}
							if (option == 6)
								return;
							cct_gotoxy(0, ROWS + 3);
							while (getchar() != '\n');
							cout <<"按回车键进行下落操作…                                         ";
							while (getchar() != '\n');
							drop(array, visited, ROWS, COLS);
							move_column_to_right(array, ROWS, COLS);
							print_graph(option, array, visited, ROWS, COLS);//

							num_single = num_total - num_old;
							score_single = num_single * num_single * 5;
							score += score_single;

							cct_gotoxy(0, ROWS + 3);
							cout << "本次得分：" << score_single << " 总得分：" << score << "                              " << endl;
							cct_gotoxy(0, ROWS + 4);
							cout << "本次消除结束，按回车键继续新一次的消除...                     ";
							while (getchar() != '\n');
							cct_gotoxy(0, ROWS + 4);
							cout << "                                                        ";
							break;
						}
					}
					if (choice == 'N' || choice == 'n')
						continue;
				}
				else {
					cct_gotoxy(0, ROWS + 3);
					cout << "周围无相同值，请重新选择                              ";
					continue;
				}
			}
		}

		if (!has_adjacent_same(array, ROWS, COLS)) {
			int num_left = ROWS * COLS - num_total;
			if (num_left < 10)
				score += (10 - num_left) * 180;
			cout << "游戏结束" << endl;
			cout << "剩余数量: " << num_left << endl;
			cout << "总得分：" << score << endl;
			return;
		}
		
	}
}
void operate_graph(int array[MAX_ROWS][MAX_COLS], int option, int ROWS, int COLS)
{
	int num_total = 0, score = 0, num_single = 0, num_old = 0, score_single = 0;
	int visited[MAX_ROWS][MAX_COLS] = { {0} };  ///
	int MX = 0, MY = 0, MAction, keycode1, keycode2;
	int MX_old=0, MY_old=0;

	//while (1) {
	print_graph(option, array, visited, ROWS, COLS);
	//}
	int i_old = ROWS, j_old = COLS;
	while (1) {
		cct_enable_mouse();
		int event = cct_read_keyboard_and_mouse(MX, MY, MAction, keycode1, keycode2);
		if (event == CCT_MOUSE_EVENT && MAction == MOUSE_ONLY_MOVED) {
			char MY_y = MY / 2 + 'A' - 1;
			int MX_x = (MX - 2) / 4;
			int i = MY / 2 - 1;
			int j = MX_x;
			// 还原
			if (i_old == i && j_old == j) {
				continue;
			}
			else if (i_old >= 0 && i_old < ROWS && j_old >= 0 && j_old < COLS
				&& !(MY_old % 2) && (MX_old - 2) % 4 >= 0 && (MX_old - 2) % 4 <= 1) {
				cct_showstr(MX_old, MY_old, "★", array[i_old][j_old], 0);
				cct_setcolor(0, 7);
			}

			// 判断位置
			if (i >= 0 && i < ROWS && j > 0 && j < COLS 
				&& !(MY%2) && (MX-2)%4>=0 && (MX-2)%4<=1) {
				cct_showstr(MX_x *4 + 2, MY, "★", array[i][j], 7);
				cct_setcolor(0, 7);
			}
			else {
				cct_gotoxy(0, 2*ROWS + 3);
				cout << "[当前光标]" << "位置非法                                                      ";
				continue;
			}
			cct_gotoxy(0, 2*ROWS + 3);
			cout << "[当前光标]" << MY_y << "行" << MX_x << "列                ";

			i_old = MY / 2 - 1;
			j_old = MX_x;
			MY_old = MY;
			MX_old = MX_x * 4 + 2;
		}
		else if (event == CCT_MOUSE_EVENT && MAction == MOUSE_LEFT_BUTTON_CLICK) {
			char MY_y = MY / 2 + 'A' - 1;
			int MX_x = (MX - 2) / 4;
			int i = MY / 2 - 1;
			int j = MX_x;
			if (i >= 0 && i < ROWS && j >= 0 && j < COLS) {
				cout << "\n选中了" << MY_y << "行" << MX_x << "列                  \n";
				if (option == 5) //
					return;
			}
		}

	}

}