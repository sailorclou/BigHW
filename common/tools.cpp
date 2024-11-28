/* 2351044 大数据 崔艺洋 */
#include <iostream>
#include <conio.h>
using namespace std;
#include "../include/cmd_console_tools.h"

char tolower(char ch) {
	if (ch >= 'A' && ch <= 'Z') {
		return ch + ('a' - 'A');
	}
	return ch;
}
int strcasecmp(const char* s1, const char* s2) {
	while (*s1 && *s2) {
		if (tolower(*s1) != tolower(*s2)) {
			return tolower(*s1) - tolower(*s2);
		}
		++s1;
		++s2;
	}
	return tolower(*s1) - tolower(*s2);
}
void to_end()
{
	int x, y;
	cout << "本小题结束， 请输入End继续…";
	cct_getxy(x, y);
	char prompt[4] = { 0 };
	for (int i = 0;i < 3;i++) {
		cin >> prompt[i];
		if (prompt[i] == '\r') {
			prompt[i] = 0;
			break;
		}
	}
	prompt[3] = '\0';
	while (getchar() != '\n');
	while (strcasecmp("End", prompt)) {
		cout << "输入错误，请重新输入";
		cct_gotoxy(x, y);
		for (int i = 0;i < 80;i++) {
			cout << ' ';
		}
		cct_gotoxy(x, y + 1);
		for (int i = 0;i < 80;i++) {
			cout << ' ';
		}
		cct_gotoxy(x, y);
		for (int i = 0;i < 3;i++) {
			cin >> prompt[i];
		}
		prompt[3] = '\0';
		while (getchar() != '\n');
	}
}