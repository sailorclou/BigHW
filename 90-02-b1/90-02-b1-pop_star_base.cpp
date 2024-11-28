/* 2351044 ������ ������ */

#include "90-02-b1-pop_star.h"


// ����Ƿ������ڵ���ֵͬ
bool has_adjacent_same(int grid[MAX_ROWS][MAX_COLS], int ROWS, int COLS) {
	// �������飺�ϡ��¡�����
	const int dx[] = { 1, -1, 0, 0 };
	const int dy[] = { 0, 0, 1, -1 };
	// ����ÿһ��Ԫ��
	for (int x = 0; x < ROWS; ++x) {
		for (int y = 0; y < COLS; ++y) {
			// ����Ԫ�ص���������
			for (int i = 0; i < 4; ++i) {
				int nx = x + dx[i];
				int ny = y + dy[i];

				// �ж��Ƿ�������߽���
				if (nx >= 0 && nx < ROWS && ny >= 0 && ny < COLS) {
					// ������ڵ�ֵ��ͬ
					if (grid[x][y] == grid[nx][ny]) {
						return true; // ��������ֵͬ
					}
				}
			}
		}
	}

	return false; // û��������ֵͬ
}
void move_column_to_right(int array[MAX_ROWS][MAX_COLS], int ROWS, int COLS) 
{
	for (int j = 0; j < COLS; j++) {
		bool if_all_zero = true;

		// �������Ƿ�ȫΪ0
		for (int i = 0; i < ROWS; i++) {
			if (array[i][j] != 0) {
				if_all_zero = false;
				break;
			}
		}

		// �������ȫΪ0���򽫸����Ƶ����ұ�
		if (if_all_zero) {
			// �ѴӸ��е����һ����������
			for (int k = j; k < COLS - 1; k++) {
				for (int i = 0; i < ROWS; i++) {
					array[i][k] = array[i][k + 1];
				}
			}

			// �����һ����Ϊȫ0
			for (int i = 0; i < ROWS; i++) {
				array[i][COLS - 1] = 0;
			}
		}
	}
}
void drop(int array[MAX_ROWS][MAX_COLS], int visited[MAX_ROWS][MAX_COLS], int ROWS, int COLS)
{
	// ��0�Ƶ�����
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
	const int dx[] = { 1, -1, 0, 0 }; // ��������: �ϡ��¡�����
	const int dy[] = { 0, 0, 1, -1 };

	visited[x][y] = true;
	// �����ĸ�����
	for (int i = 0; i < 4; ++i) {
		int nx = x + dx[i];
		int ny = y + dy[i];
		// �����λ���Ƿ��ڱ߽��ڣ�����ɫ��ͬ����δ������
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
		cout << " " << i << " ";   /// ��0��ʼ
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
			// ��ͨ��ӡ
			if (n == 0) {
				cout << array[i][j];
			}
			// ������ӡ
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
			// ����
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
			cout << "������ĸ + ������ʽ[����c2]����������꣺";
			cin >> row >> col;
			cout << "\n����Ϊ" << row << "��" << col << "��\n" << endl;
			if (array[int(row - 'a')][col] == 0) {
				cout << "����ľ�������λ��Ϊ0���Ƿ�λ�ã�������������" << endl;
				continue;
			}
			
			if (array[int(row - 'a')][col] == array[int(row - 'a') - 1][col] && int(row - 'a') > 0
				|| array[int(row - 'a')][col] == array[int(row - 'a')][col - 1] && col > 0
				|| array[int(row - 'a')][col] == array[int(row - 'a') + 1][col] && int(row - 'a') < ROWS - 1
				|| array[int(row - 'a')][col] == array[int(row - 'a')][col + 1] && col < COLS - 1)
			{
				cout << "���ҽ�����飺" << endl;
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
				cout << "����ľ�������λ�ô���������ֵͬ������������" << endl;
				continue;
			}
		}
		cout << "��ǰ����(��ͬɫ��ʶ)��" << endl;
		print_array(2, array, visited, ROWS, COLS);//

		if (option == 1)
			return;

		cout << "��ȷ���Ƿ��" << row << "��" << col << "�м���Χ����ֵͬ����(Y / N / Q)��";
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
				cout << "\n��ֵͬ�鲢�������(��ͬɫ��ʶ)��" << endl;
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
		cout << "���ε÷֣�" << score_single << " �ܵ÷֣�" << score << endl;
		while (getchar() != '\n');
		cout << endl << "���س����������������0�Ĳ�����";
		while (getchar() != '\n');
		cout << "\n�����0������飨��ͬɫ��ʶ����" << endl;
		drop(array, visited, ROWS, COLS);
		print_array(2, array, visited, ROWS, COLS);//
		move_column_to_right(array, ROWS, COLS);
		print_array(2, array, visited, ROWS, COLS);//

		if (option == 2)
			return;

		cout << "�����������������س���������һ�ε�����...";
		while (getchar() != '\n');
		if (!has_adjacent_same(array, ROWS, COLS))
		{
			int num_left = ROWS * COLS - num_total;
			if (num_left < 10)
				score += (10 - num_left) * 180;
			cout << "��Ϸ����" << endl;
			cout << "ʣ������: " << num_left << endl;
			cout << "�ܵ÷֣�" << score << endl;
			return;
		}
		cout << "\n��ǰ����(��ͬɫ��ʶ)��" << endl;
		print_array(2, array, visited, ROWS, COLS);//
		int visited[MAX_ROWS][MAX_COLS] = { {0} };
		cout << endl;
	}
}