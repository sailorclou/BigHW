/* 2351044 ������ ������ */
#define _CRT_SECURE_NO_WARNINGS
#include "90-02-b2-gmw-Minesweeper.h"
#include "../include/tools.h"
#include "../include/cmd_gmw_tools.h"


void initial(CONSOLE_GRAPHICS_INFO* const pCGI)
{
	int level = 1, rows = 0, cols = 0;
	while (1) {
		cout << "������ɨ����Ϸ�ĵȼ������֣�������\\�м�\\�߼���1\\2\\3��";
		level = int(_getch() - '0');
		if (level >= 1 && level <= 3 && cin.good())
			break;
		else if (!cin.good()) {
			cin.clear();
			while (getchar() != '\n');
		}
	}
    switch (level) {
        case 1:
            rows = 9;
            cols = 9;
            break;
        case 2:
            rows = 16;
            cols = 16;
            break;
        case 3:
            rows = 16;
            cols = 30;
            break;
    }
	gmw_init(pCGI, rows, cols);
	gmw_set_frame_color(pCGI, 15, 0);
	gmw_set_font(pCGI, "������", 16, 8);

	gmw_set_rowno_switch(pCGI, 1);
	gmw_set_colno_switch(pCGI, 1);
	gmw_set_status_line_switch(pCGI, TOP_STATUS_LINE, 1);
	gmw_set_status_line_switch(pCGI, LOWER_STATUS_LINE, 1);
	gmw_set_status_line_color(pCGI, TOP_STATUS_LINE, 0, 15);
	gmw_set_status_line_color(pCGI, LOWER_STATUS_LINE, 0, 15);

	gmw_set_block_border_switch(pCGI, 0);
	gmw_set_frame_style(pCGI, 4, 2, 1);

	return;
}
// ������λ���Ƿ��Ѿ�������Ϊ��
bool isMine(int minefield[MAX_ROWS][MAX_COLS], int x, int y)
{
    return minefield[x][y] == -1;
}
// �����������������
void placeMines(int minefield[MAX_ROWS][MAX_COLS], int ROWS, int COLS, int numMines)
{
    while (numMines > 0) {
        int x = rand() % ROWS;
        int y = rand() % COLS;
        if (minefield[x][y] != -1) { // �����λ��û���ף��������
            minefield[x][y] = -1;
            numMines--;
        }
    }
}
// �������λ����Χ������
int countMines(int minefield[MAX_ROWS][MAX_COLS], int ROWS, int COLS, int x, int y)
{
    int count = 0;
    for (int i = max(0, x - 1); i < min(ROWS, x + 2); i++) {
        for (int j = max(0, y - 1); j < min(COLS, y + 2); j++) {
            if (isMine(minefield, i, j)) { // �����Χ����
                count++;
            }
        }
    }
    return count;
}
// ���������з���λ�õ�����
void updateNumbers(int minefield[MAX_ROWS][MAX_COLS], int ROWS, int COLS)
{
    for (int x = 0; x < ROWS; x++) {
        for (int y = 0; y < COLS; y++) {
            if (!isMine(minefield, x, y)) { // ���������
                minefield[x][y] = countMines(minefield, ROWS, COLS, x, y);
            }
        }
    }
}
// �����Ƿ�ֻʣ��
bool leftOnlyMines(int minefield[MAX_ROWS][MAX_COLS], int visited[MAX_ROWS][MAX_COLS], int ROWS, int COLS)
{
	for (int i = 0;i < ROWS;i++) {
		for (int j = 0;j < COLS;j++) {
			if (!isMine(minefield, i, j) && !visited[i][j]) {
				return false;
			}
		}
	}
	return true;
}
// ����ǿո��������
void touchBoundary(int minefield[MAX_ROWS][MAX_COLS], int visited[MAX_ROWS][MAX_COLS], int x, int y, int ROWS, int COLS)
{
	const int dx[] = { 1, -1, 0, 0 }; // ��������: �ϡ��¡�����
	const int dy[] = { 0, 0, 1, -1 };
	visited[x][y] = 1;
	// �����ĸ�����
	for (int i = 0; i < 4; ++i) {
		int nx = x + dx[i];
		int ny = y + dy[i];
		if (nx >= 0 && nx < ROWS && ny >= 0 && ny < COLS &&
			!minefield[nx][ny] && !visited[nx][ny]) //�ǿո�
		{
			touchBoundary(minefield, visited, nx, ny, ROWS, COLS);
		}
		else if (nx >= 0 && nx < ROWS && ny >= 0 && ny < COLS &&
			     minefield[nx][ny] > 0 && !visited[nx][ny])   //������
		{
			visited[nx][ny] = 1;
		}
	}
}
// ��������
void drawMinefield(int minefield[MAX_ROWS][MAX_COLS], int visited[MAX_ROWS][MAX_COLS], CONSOLE_GRAPHICS_INFO* const pCGI, BLOCK_DISPLAY_INFO* const bdi, int ROWS, int COLS)
{
	gmw_draw_frame(pCGI);
    for (int x = 0; x < ROWS; x++) {
        for (int y = 0; y < COLS; y++) {
			if (visited[x][y] == 1) {
				if (isMine(minefield, x, y)) { // ����㵽�ף���ӡ*
					gmw_draw_block(pCGI, x, y, 6, bdi);
				}
				else if (minefield[x][y]) { // ��������ף���ӡ��Χ����
					gmw_draw_block(pCGI, x, y, minefield[x][y], bdi);
				}
				else if (!minefield[x][y]) { //�ո�
					bdi->bgcolor = COLOR_WHITE;
					bdi->fgcolor = COLOR_WHITE;
					gmw_draw_block(pCGI, x, y, 0, bdi);
					bdi->bgcolor = COLOR_YELLOW;
					bdi->fgcolor = COLOR_YELLOW;
				}
			}
			else {
				gmw_draw_block(pCGI, x, y, 0, bdi);
			}
        }
    }
}
// ��Ϸ����
void game(int minefield[MAX_ROWS][MAX_COLS], CONSOLE_GRAPHICS_INFO* const pCGI, BLOCK_DISPLAY_INFO* const bdi, int numMines)
{
	int ROWS = pCGI->row_num, COLS = pCGI->col_num;
	char info[256];
	int visited[MAX_ROWS][MAX_COLS] = { {0} };
	int MX = 0, MY = 0, MAction, keycode1, keycode2;
	
	drawMinefield(minefield, visited, pCGI, bdi, ROWS, COLS);
	while (1) {
		cct_enable_mouse();
		int event = cct_read_keyboard_and_mouse(MX, MY, MAction, keycode1, keycode2);
		char MY_y = (MY - pCGI->start_y - 1) / (pCGI->CFI.block_high + pCGI->CFI.separator) + 'A';
		int MX_x = (MX - pCGI->start_x - 2) / (pCGI->CFI.block_width + 2 * pCGI->CFI.separator);
		int i = int(MY_y - 'A');
		int j = MX_x;
		if (event == CCT_MOUSE_EVENT && MAction == MOUSE_ONLY_MOVED) {			
			// �ж�λ��
			if (i >= 0 && i < ROWS && j >= 0 && j < COLS) {
			}
			else {
				sprintf(info, "λ�÷Ƿ�                                         ");
				gmw_status_line(pCGI, LOWER_STATUS_LINE, info);
				continue;
			}
			sprintf(info, "[��ǰ���] %c��%d��                                         ", MY_y, MX_x);
			gmw_status_line(pCGI, LOWER_STATUS_LINE, info);
		}
		else if (event == CCT_MOUSE_EVENT && MAction == MOUSE_LEFT_BUTTON_CLICK) {			
			if (i >= 0 && i < ROWS && j >= 0 && j < COLS) {
				if (isMine(minefield, i, j)) {
					visited[i][j] = 1;
					drawMinefield(minefield, visited, pCGI, bdi, ROWS, COLS);
					sprintf(info, "��ʧ����                                         ");
					gmw_status_line(pCGI, LOWER_STATUS_LINE, info);
					Sleep(1000);
					return;
				}
				else {
					if (!minefield[i][j]) { //�ո�
						touchBoundary(minefield, visited, i, j, ROWS, COLS);
					}
					else {
						visited[i][j] = 1;
					}
					drawMinefield(minefield, visited, pCGI, bdi, ROWS, COLS);
				}
			}
		}

		if (leftOnlyMines(minefield, visited, ROWS, COLS)) { //ֻʣ��
			sprintf(info, "��ɹ���                                         ");
			gmw_status_line(pCGI, TOP_STATUS_LINE, info);
			Sleep(1000);
			return;
		}

	}

}
// ׼������
void operate(CONSOLE_GRAPHICS_INFO* const pCGI, BLOCK_DISPLAY_INFO* const bdi)
{
    srand(unsigned(time(0))); 
    //��ʼ������λ��Ϊ0����ʾû����
    int minefield[MAX_ROWS][MAX_COLS] = { 0 };
    int numMines = 0; // �׵�����
    int ROWS = pCGI->row_num, COLS = pCGI->col_num;
    switch (ROWS * COLS) {
        case 81:
            numMines = 10;
            break;
        case 256:
            numMines = 40;
            break;
        case 480:
            numMines = 99;
            break;
    }
    placeMines(minefield, ROWS, COLS, numMines); // ������
    updateNumbers(minefield, ROWS, COLS); // ��������
	game(minefield, pCGI, bdi, numMines);
}