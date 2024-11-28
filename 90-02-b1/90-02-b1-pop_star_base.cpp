/* 2351044 大数据 崔艺洋 */

#include "90-02-b1-pop_star.h"


// 检查是否有相邻的相同值
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
					if (grid[x][y] == grid[nx][ny]) {
						return true; // 有相邻相同值
					}
				}
			}
		}
	}

	return false; // 没有相邻相同值
}
void move_column_to_right(int array[MAX_ROWS][MAX_COLS], int ROWS, int COLS) 
{
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
			// 把从该列到最后一列依次左移
			for (int k = j; k < COLS - 1; k++) {
				for (int i = 0; i < ROWS; i++) {
					array[i][k] = array[i][k + 1];
				}
			}

			// 将最后一列置为全0
			for (int i = 0; i < ROWS; i++) {
				array[i][COLS - 1] = 0;
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
void print_array(int n, int array[MAX_ROWS][MAX_COLS], int visited[MAX_ROWS][MAX_COLS], int ROWS, int COLS)
{
	cout << "  | ";
	for (int i = 0;i < COLS;i++) {
		cout << " " << i << " ";   /// 从0开始
	}
	cout << endl;
	cout << "--+-";
	for (int i = 0;i < COLS;i++) {
		cout << "---";
	}
	cout << endl;
	srand(unsigned int(time(0)));
	for (int i = 0;i < ROWS;i++) {
		cout << char('A' + i) << " | ";
		for (int j = 0;j < COLS;j++) {
			cout << " ";
			// 普通打印
			if (n == 0) {
				cout << array[i][j];
			}
			// 其他打印
			else if (visited[i][j] == 1) {
				if (n == 2) {
					cct_setcolor(14, 8);
					cout << array[i][j];
					cct_setcolor(0, 7);
					array[i][j] = 0;
				}
				else if (n == 1) {
					cout << '*';
				}
			}
			else if (visited[i][j] == 0) {
				if (n == 2) {
					cout << array[i][j];
				}
				else if (n == 1) {
					cout << 0;
				}
			}
			//
			cout << " ";
			
		}
		cout << endl;
	}
	cout << endl;
}
void generate_array(int array[MAX_ROWS][MAX_COLS], int ROWS, int COLS)
{
	for (int i = 0;i < ROWS;i++) {
		for (int j = 0;j < COLS;j++) {
			// 生成
			array[i][j] = rand() % 9 + 1;
		}
	}
	//print_array(0, array, array, ROWS, COLS);//
}
void operate_array(int array[MAX_ROWS][MAX_COLS], int option, int ROWS, int COLS)
{
	char row;
	int col;
	int num_total = 0, score = 0, num_single = 0, num_old = 0, score_single = 0;
	int visited[MAX_ROWS][MAX_COLS] = { {0} }, visited_copy[MAX_ROWS][MAX_COLS] = { {0} };  ///

	while (1) {
		while (1) {
			cout << "请以字母 + 数字形式[例：c2]输入矩阵坐标：";
			cin >> row >> col;
			cout << "\n输入为" << row << "行" << col << "列\n" << endl;
			if (array[int(row - 'a')][col] == 0) {
				cout << "输入的矩阵坐标位置为0（非法位置），请重新输入" << endl;
				continue;
			}
			
			if (array[int(row - 'a')][col] == array[int(row - 'a') - 1][col] && int(row - 'a') > 0
				|| array[int(row - 'a')][col] == array[int(row - 'a')][col - 1] && col > 0
				|| array[int(row - 'a')][col] == array[int(row - 'a') + 1][col] && int(row - 'a') < ROWS - 1
				|| array[int(row - 'a')][col] == array[int(row - 'a')][col + 1] && col < COLS - 1)
			{
				cout << "查找结果数组：" << endl;
				print_array(1, array, visited, ROWS, COLS);//
				for (int i = 0;i < ROWS;i++) {
					for (int j = 0;j < COLS;j++) {
						visited_copy[i][j] = visited[i][j];
					}
				}
				dfs(array, visited, ROWS, COLS, int(row - 'a'), col, array[int(row - 'a')][col]);  //

				break;
			}
			else
			{
				cout << "输入的矩阵坐标位置处无连续相同值，请重新输入" << endl;
				continue;
			}
		}
		cout << "当前数组(不同色标识)：" << endl;
		print_array(2, array, visited, ROWS, COLS);//

		if (option == 1)
			return;

		cout << "请确认是否把" << row << "行" << col << "列及周围的相同值消除(Y / N / Q)：";
		char choice;
		while (1) {
			choice = _getche();
			if (choice == 'Q' || choice == 'q')
				return;
			else if (choice == 'N' || choice == 'n') {
				for (int i = 0;i < ROWS;i++) {
					for (int j = 0;j < COLS;j++) {
						visited[i][j] = visited_copy[i][j];
					}
				}
				cout << endl;
				break;
			}
			else if (choice == 'Y' || choice == 'y') {
				cout << "\n相同值归并后的数组(不同色标识)：" << endl;
				num_old = num_total;
				num_total = 0;
				for (int i = 0;i < ROWS;i++) {
					for (int j = 0;j < COLS;j++) {
						num_total += visited[i][j];
					}
				}
				num_single = num_total - num_old;
				print_array(2, array, visited, ROWS, COLS);//
				break;
			}
		}
		if (choice == 'N' || choice == 'n')
			continue;
		score_single = num_single * num_single * 5;
		score += score_single;
		cout << "本次得分：" << score_single << " 总得分：" << score << endl;
		while (getchar() != '\n');
		cout << endl << "按回车键进行数组下落除0的操作…";
		while (getchar() != '\n');
		cout << "\n下落除0后的数组（不同色标识）：" << endl;
		drop(array, visited, ROWS, COLS);
		print_array(2, array, visited, ROWS, COLS);//
		move_column_to_right(array, ROWS, COLS);
		print_array(2, array, visited, ROWS, COLS);//

		if (option == 2)
			return;

		cout << "本次消除结束，按回车键继续新一次的消除...";
		while (getchar() != '\n');
		if (!has_adjacent_same(array, ROWS, COLS))
		{
			int num_left = ROWS * COLS - num_total;
			if (num_left < 10)
				score += (10 - num_left) * 180;
			cout << "游戏结束" << endl;
			cout << "剩余数量: " << num_left << endl;
			cout << "总得分：" << score << endl;
			return;
		}
		cout << "\n当前数组(不同色标识)：" << endl;
		print_array(2, array, visited, ROWS, COLS);//
		int visited[MAX_ROWS][MAX_COLS] = { {0} };
		cout << endl;
	}
}