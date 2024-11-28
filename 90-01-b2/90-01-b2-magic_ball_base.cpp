/* 2351044 大数据 崔艺洋 */

#include "90-01-b2-magic_ball.h"

void print_array(int n, int array[MAX_ROWS][MAX_COLS], int ROWS, int COLS)
{
	int x, y;
	cout << "  | ";
	for (int i = 0;i < COLS;i++) {
		cout << " " << i + 1 << " ";
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
			if (n == 2 && array[i][j] == 0) {
				array[i][j] = rand() % 9 + 1;
			}
			if (i == 0 && j == 0)
				cct_getxy(x, y);  // 基准位置
			cout << " ";
			if (array[i][j] == 0 && n == 4) {
				cct_setcolor(14, 8);
			}
			cout << array[i][j];
			cct_setcolor(0, 7);
			cout << " ";
		}
		cout << endl;
	}
}
void generate_array(int array[MAX_ROWS][MAX_COLS], int ROWS, int COLS)
{
	int x, y;
	cct_getxy(x, y);
	print_array(2, array, ROWS, COLS);

	cout << endl;
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
void show_array_with_mark(int array[MAX_ROWS][MAX_COLS], int ROWS, int COLS)
{
	int x, y;
	cct_getxy(x, y);
	x = x + 4;
	y = y + 2;
	print_array(3, array, ROWS, COLS);

	for (int i = 0;i < ROWS;i++) {
		for (int j = 0;j < COLS;j++) {
			if (!(i == ROWS - 1 || i == ROWS - 2) &&
				array[i][j] == array[i + 1][j] && array[i][j] == array[i + 2][j]) {
				cct_showint(x + 3 * j + 1, y + i, array[i][j], 14, 8);
				cct_showint(x + 3 * j + 1, y + (i + 1), array[i + 1][j], 14, 8);
				cct_showint(x + 3 * j + 1, y + (i + 2), array[i + 2][j], 14, 8);
			}  // 检查纵向并标记
			if (!(j == COLS - 1 || j == COLS - 2) &&
				array[i][j] == array[i][j + 1] && array[i][j] == array[i][j + 2]) {
				cct_showint(x + 3 * j + 1, y + i, array[i][j], 14, 8);
				cct_showint(x + 3 * (j + 1) + 1, y + i, array[i][j + 1], 14, 8);
				cct_showint(x + 3 * (j + 2) + 1, y + i, array[i][j + 2], 14, 8);
			}  // 检查横向并标记
		}
	}
	cct_setcolor(0, 7);
	cct_gotoxy(0, y + ROWS + 1);
}
void show_array_with_zero_and_fill(int array[MAX_ROWS][MAX_COLS], int ROWS, int COLS)
{// 在循环检查时，检查旧的数组，改变新的数组，从而只消除旧数组的相连项
	int x, y;
	cct_getxy(x, y);
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

	print_array(4, array1, ROWS, COLS);

	cct_setcolor(0, 7);
	cct_gotoxy(0, y + ROWS + 1);
	cout << endl << "按回车键进行新值填充…";
	while (getchar() != '\n');
	cout << "新值填充后的数组（不同色标识）：" << endl;
	cct_getxy(x, y);
	print_array(2, array1, ROWS, COLS);  //
	// 拷贝，更新旧数组
	for (int i = 0; i < ROWS; i++)
		for (int j = 0; j < COLS; j++)
			array[i][j] = array1[i][j];
	cout << endl;
	cout << "按回车键进行寻找初始可消除的操作…";
	while (getchar() != '\n');
}
void hints(int array[MAX_ROWS][MAX_COLS], int ROWS, int COLS)
{
	int x, y;
	cct_getxy(x, y);
	x = x + 4;
	y = y + 2;

	print_array(3, array, ROWS, COLS);

	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			// 检查垂直方向连续相等，并处理边界问题
			if (i < ROWS - 1 && array[i][j] == array[i + 1][j]) {
				if (i > 0 && j > 0 && array[i][j] == array[i - 1][j - 1]) {
					cct_showint(x + 3 * (j - 1) + 1, y + i - 1, array[i - 1][j - 1], 14, 8);
					cct_showint(x + 3 * j + 1, y + i - 1, array[i - 1][j], 14, 8);
				}  // 左上角
				if (i < ROWS - 2 && j > 0 && array[i][j] == array[i + 2][j - 1]) {
					cct_showint(x + 3 * (j - 1) + 1, y + i + 2, array[i + 2][j - 1], 14, 8);
					cct_showint(x + 3 * j + 1, y + i + 2, array[i + 2][j], 14, 8);
				}  // 左下角
				if (i < ROWS - 2 && j < COLS - 1 && array[i][j] == array[i + 2][j + 1]) {
					cct_showint(x + 3 * (j + 1) + 1, y + i + 2, array[i + 2][j + 1], 14, 8);
					cct_showint(x + 3 * j + 1, y + i + 2, array[i + 2][j], 14, 8);
				}  // 右下角
				if (i > 0 && j < COLS - 1 && array[i][j] == array[i - 1][j + 1]) {
					cct_showint(x + 3 * (j + 1) + 1, y + i - 1, array[i - 1][j + 1], 14, 8);
					cct_showint(x + 3 * j + 1, y + i - 1, array[i - 1][j], 14, 8);
				}  // 右上角
				if (i > 1 && array[i][j] == array[i - 2][j]) {
					cct_showint(x + 3 * j + 1, y + i - 2, array[i - 2][j], 14, 8);
					cct_showint(x + 3 * j + 1, y + i - 1, array[i - 1][j], 14, 8);
				}  // 上
				if (i < ROWS - 2 && array[i][j] == array[i + 3][j]) {
					cct_showint(x + 3 * j + 1, y + i + 3, array[i + 3][j], 14, 8);
					cct_showint(x + 3 * j + 1, y + i + 2, array[i + 2][j], 14, 8);
				}  // 下
			}
			// 检查水平方向连续相等，并处理边界问题
			if (j < COLS - 1 && array[i][j] == array[i][j + 1]) {
				if (i > 0 && j > 0 && array[i][j] == array[i - 1][j - 1]) {
					cct_showint(x + 3 * (j - 1) + 1, y + i - 1, array[i - 1][j - 1], 14, 8);
					cct_showint(x + 3 * (j - 1) + 1, y + i, array[i][j - 1], 14, 8);
				}  // 左上角
				if (i < ROWS - 1 && j > 0 && array[i][j] == array[i + 1][j - 1]) {
					cct_showint(x + 3 * (j - 1) + 1, y + i + 1, array[i + 1][j - 1], 14, 8);
					cct_showint(x + 3 * (j - 1) + 1, y + i, array[i][j - 1], 14, 8);
				}  // 左下角
				if (i < ROWS - 1 && j < COLS - 2 && array[i][j] == array[i + 1][j + 2]) {
					cct_showint(x + 3 * (j + 2) + 1, y + i + 1, array[i + 1][j + 2], 14, 8);
					cct_showint(x + 3 * (j + 2) + 1, y + i, array[i][j + 2], 14, 8);
				}  // 右下角
				if (i > 0 && j < COLS - 2 && array[i][j] == array[i - 1][j + 2]) {
					cct_showint(x + 3 * (j + 2) + 1, y + i - 1, array[i - 1][j + 2], 14, 8);
					cct_showint(x + 3 * (j + 2) + 1, y + i, array[i][j + 2], 14, 8);
				}  // 右上角
				if (j > 1 && array[i][j] == array[i][j - 2]) {
					cct_showint(x + 3 * (j - 2) + 1, y + i, array[i][j - 2], 14, 8);
					cct_showint(x + 3 * (j - 1) + 1, y + i, array[i][j - 1], 14, 8);
				}  // 左
				if (j < COLS - 2 && array[i][j] == array[i][j + 3]) {
					cct_showint(x + 3 * (j + 3) + 1, y + i, array[i][j + 3], 14, 8);
					cct_showint(x + 3 * (j + 2) + 1, y + i, array[i][j + 2], 14, 8);
				}  // 右
			}
			// 检查垂直方向间隔相等，并处理边界问题
			if (i < ROWS - 2 && array[i][j] == array[i + 2][j]) {
				if (i > 0 && j > 0 && array[i][j] == array[i + 1][j - 1]) {
					cct_showint(x + 3 * (j - 1) + 1, y + i + 1, array[i + 1][j - 1], 14, 8);
					cct_showint(x + 3 * j + 1, y + i + 1, array[i + 1][j], 14, 8);
				}  // 左
				if (i < ROWS - 2 && j < COLS - 1 && array[i][j] == array[i + 1][j + 1]) {
					cct_showint(x + 3 * (j + 1) + 1, y + i + 1, array[i + 1][j + 1], 14, 8);
					cct_showint(x + 3 * j + 1, y + i + 1, array[i + 1][j], 14, 8);
				}  // 右
			}
			// 检查水平方向间隔相等，并处理边界问题
			if (j < COLS - 2 && array[i][j] == array[i][j + 2]) {
				if (i > 0 && j > 0 && array[i][j] == array[i - 1][j + 1]) {
					cct_showint(x + 3 * (j + 1) + 1, y + i - 1, array[i - 1][j + 1], 14, 8);
					cct_showint(x + 3 * (j + 1) + 1, y + i, array[i][j + 1], 14, 8);
				}  // 上
				if (i < ROWS - 2 && j < COLS - 2 && array[i][j] == array[i + 1][j + 1]) {
					cct_showint(x + 3 * (j + 1) + 1, y + i + 1, array[i + 1][j + 1], 14, 8);
					cct_showint(x + 3 * (j + 1) + 1, y + i, array[i][j + 1], 14, 8);
				}  // 下
			}
		}
	}
	cct_setcolor(0, 7);
	cct_gotoxy(0, y + ROWS + 1);

}
void operate_array(int array[MAX_ROWS][MAX_COLS], int option, int ROWS, int COLS)
{
	while (getchar() != '\n')
		;
	cout << "按回车键进行寻找初始可消除的操作…";
	while (getchar() != '\n')
		; // 等待回车键
	while (1) {
		if (find_if(array, ROWS, COLS)) {  //
			cout << "初始可消除项（不同色标识）：" << endl;
			show_array_with_mark(array, ROWS, COLS);  //
			if (option == 1)
				return;
			if (option >= 2) {
				cout << endl << "按回车键进行数组下落除0的操作…";
				while (getchar() != '\n');
				cout << "下落除0后的数组（不同色标识）：" << endl;
				show_array_with_zero_and_fill(array, ROWS, COLS);  //
			}
		}
		else {
			cout << "初始已无可消除项" << endl;
			if (option == 3) {
				cout << endl << "可选择的消除提示（不同色标识）：" << endl;
				hints(array, ROWS, COLS);
			}
			break;
		}
	}
}