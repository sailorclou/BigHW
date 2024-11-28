/* 2351044 大数据 崔艺洋 */
#include <iostream>
#include <conio.h>
using namespace std;

int menu(const char* content[], int num)
{
	while (1) {
		char choice;
		int max_length = 0;
		for (int i = 0; i < num - 1; ++i) {
			if (strlen(content[i + 1]) > strlen(content[i])) {
				max_length = strlen(content[i + 1]);
			}
		}
		for (int i = 0;i < max_length;i++) {
			cout << "-";
		}
		cout << endl;
		for (int i = 0; i < num; ++i) {
			cout << content[i] << endl;
		}
		for (int i = 0;i < max_length;i++) {
			cout << "-";
		}
		cout << endl;
		cout << "[请选择:] ";
		choice = _getche();
		choice = toupper(choice);
		// 验证选择是否有效
		bool valid = false;
		for (int i = 0; i < num; ++i) {
			if (toupper(content[i][0]) == choice) {
				valid = true;
				break;
			}
		}
		if (valid) {
			return choice;
		}
		else {
			continue;
		}
	}
}