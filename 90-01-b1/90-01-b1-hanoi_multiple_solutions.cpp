/* 2351044 大数据 崔艺洋 */
#include <iostream>
#include "90-01-b1-hanoi.h"
#include "../include/cmd_console_tools.h"
using namespace std;

/* ----------------------------------------------------------------------------------

     本文件功能：
    1、存放被 hanoi_main.cpp 中根据菜单返回值调用的各菜单项对应的执行函数

     本文件要求：
    1、不允许定义外部全局变量（const及#define不在限制范围内）
    2、允许定义静态全局变量（具体需要的数量不要超过文档显示，全局变量的使用准则是：少用、慎用、能不用尽量不用）
    3、静态局部变量的数量不限制，但使用准则也是：少用、慎用、能不用尽量不用
    4、按需加入系统头文件、自定义头文件、命名空间等

   ----------------------------------------------------------------------------------- */

static int step, top1, top2, top3;
static int SRC[10], TMP[10], DST[10];
const int max_pan = 10;
const int base_pan = 2 * max_pan + 3;

/***************************************************************************
  函数名称：
  功    能：输入并初始化
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void setpace(int interval)
{
    int ch;
    if (interval >= 0) {
        if (interval)
            Sleep(1 / (interval * interval * 1000000));
        else {
            while (1) {
                ch = _getch();
                if (ch == '\r')
                    break;
            }
        }
    }
}
void opt8init1(int n, char src, char tmp, char dst, int position, int* in)
{
    step = 0;
    *in = -1;
    while (!cin.good() || *in < 0 || *in > 5) {
        cin.clear();
        cout << "请输入移动速度(0-5: 0-按回车单步演示 1-延时最长 5-延时最短)" << endl;
        cin >> *in;
        if (!cin.good()) {
            cin.clear();
            while (getchar() != '\n');
        }
    }

}
void opt8init2(int n, char src, char tmp, char dst, int position, int* in)
{
    step = 0;
    int i;
    cct_gotoxy(base_x, base_y + position);
    cout << "初始:               ";
    // 打印数组

    cout << " A:";
    for (i = 0;i < 10;i++) {
        if (i < top1)
            cout << setw(2) << SRC[i];
        else
            cout << "  ";
    }
    cout << " B:";
    for (i = 0;i < 10;i++) {
        if (i < top2)
            cout << setw(2) << TMP[i];
        else
            cout << "  ";
    }
    cout << " C:";
    for (i = 0;i < 10;i++) {
        if (i < top3)
            cout << setw(2) << DST[i];
        else
            cout << "  ";
    }
    // 打印塔
    cct_gotoxy(base_x + 10, base_y - 5 + position);
    cout << "=========================" << endl;
    cct_gotoxy(base_x + 10, base_y - 4 + position);
    cout << "  A         B         C";
    // A
    for (i = 0;i < 10;i++) {
        if (i < top1) {
            cct_gotoxy(11, base_y - 5 - i - 1 + position);
            cout << setw(2) << SRC[i];
        }
        else {
            cct_gotoxy(11, base_y - 5 - i - 1 + position);
            cout << "  ";
        }
    }
    // B
    for (i = 0;i < 10;i++) {
        if (i < top2) {
            cct_gotoxy(21, base_y - 5 - i - 1 + position);
            cout << setw(2) << TMP[i];
        }
        else {
            cct_gotoxy(21, base_y - 5 - i - 1 + position);
            cout << "  ";
        }
    }
    // C
    for (i = 0;i < 10;i++) {
        if (i < top3) {
            cct_gotoxy(31, base_y - 5 - i - 1 + position);
            cout << setw(2) << DST[i];
        }
        else {
            cct_gotoxy(31, base_y - 5 - i - 1 + position);
            cout << "  ";
        }
    }
    setpace(*in);
    cct_gotoxy(base_x, base_y + position);
    for (i = 0;i < 5 * base_x;i++)
        cout << ' ';
    setpace(*in);
}
void opt4init(int n, char src, char tmp, char dst, int position, int* in)
{
    step = 0;
    int i;
    while (!cin.good() || *in < 0 || *in > 5) {
        cin.clear();
        cout << "请输入移动速度(0-5: 0-按回车单步演示 1-延时最长 5-延时最短)" << endl;
        cin >> *in;
        if (!cin.good()) {
            cin.clear();
            while (getchar() != '\n');
        }
    }

    cct_cls();
    cout << "从 " << src << " 移动到 " << dst << " ，共 " << n << " 层，延时设置为 "
        << *in << "，";

    cct_gotoxy(base_x, base_y);
    cout << "初始:               ";
    // 打印数组

    cout << " A:";
    for (i = 0;i < 10;i++) {
        if (i < top1)
            cout << setw(2) << SRC[i];
        else
            cout << "  ";
    }
    cout << " B:";
    for (i = 0;i < 10;i++) {
        if (i < top2)
            cout << setw(2) << TMP[i];
        else
            cout << "  ";
    }
    cout << " C:";
    for (i = 0;i < 10;i++) {
        if (i < top3)
            cout << setw(2) << DST[i];
        else
            cout << "  ";
    }
    // 打印塔
    cct_gotoxy(base_x + 10, base_y - 5 + position);
    cout << "=========================" << endl;
    cct_gotoxy(base_x + 10, base_y - 4 + position);
    cout << "  A         B         C";
    // A
    for (i = 0;i < 10;i++) {
        if (i < top1) {
            cct_gotoxy(11, base_y - 5 - i - 1 + position);
            cout << setw(2) << SRC[i];
        }
        else {
            cct_gotoxy(11, base_y - 5 - i - 1 + position);
            cout << "  ";
        }
    }
    // B
    for (i = 0;i < 10;i++) {
        if (i < top2) {
            cct_gotoxy(21, base_y - 5 - i - 1 + position);
            cout << setw(2) << TMP[i];
        }
        else {
            cct_gotoxy(21, base_y - 5 - i - 1 + position);
            cout << "  ";
        }
    }
    // C
    for (i = 0;i < 10;i++) {
        if (i < top3) {
            cct_gotoxy(31, base_y - 5 - i - 1 + position);
            cout << setw(2) << DST[i];
        }
        else {
            cct_gotoxy(31, base_y - 5 - i - 1 + position);
            cout << "  ";
        }
    }
    setpace(*in);
    cct_gotoxy(base_x, base_y + position);
    for (i = 0;i < 50;i++)
        cout << ' ';
}
void initial(int* n, char* s, char* t, char* d, int option, int* in)
{
    step = 0;
    top1 = 0, top2 = 0, top3 = 0;
    *in = -1;
    int i, flag1 = 1, flag2 = 1, flag3 = 1;

    while (flag1) {
        cout << "请输入汉诺塔的层数(1-10)" << endl;
        cin >> *n;
        flag1 = cin.good() == 0 || *n < 1 || *n > 16;
        if (flag1) {
            cin.clear();  // 清除错误状态标志
        }
        while (getchar() != '\n'); // 清除输入缓冲区
    }
    while (flag2) {
        cout << "请输入起始柱(A-C)" << endl;
        cin >> *s;

        flag2 = cin.good() == 0 || !(*s >= 'A' && *s <= 'C') && !(*s >= 'a' && *s <= 'c');
        if (flag2) {
            cin.clear();  // 清除错误状态标志
        }
        else {
            if (*s >= 'a' && *s <= 'c')
                *s = char(*s + 'A' - 'a');
        }
        while (getchar() != '\n'); // 清除输入缓冲区
    }
    while (flag3) {
        cout << "请输入目标柱(A-C)" << endl;
        cin >> *d;
        flag3 = cin.good() == 0 || !(*d >= 'A' && *d <= 'C') && !(*d >= 'a' && *d <= 'c');
        if (flag3) {
            cin.clear();  // 清除错误状态标志
        }
        else {
            if (*d >= 'a' && *d <= 'c')
                *d = char(*d + 'A' - 'a');
            if (*d == *s) {
                flag3 = 1;
                cout << "目标柱(" << *d << ")不能与起始柱(" << *d << ")相同" << endl;
            }

        }
        while (getchar() != '\n'); // 清除输入缓冲区
    }

    *t = 'A' + 'B' + 'C' - *s - *d;

    // 初始化
    if (*s == 'A') {
        for (i = *n;i > 0;i--) {
            SRC[top1++] = i;
        }
    }
    else if (*s == 'B') {
        for (i = *n;i > 0;i--) {
            TMP[top2++] = i;
        }
    }
    else if (*s == 'C') {
        for (i = *n;i > 0;i--) {
            DST[top3++] = i;
        }
    }

    //
    if (option == 4)
        opt4init(*n, *s, *t, *d, 2, in);
    else if (option == 8) {
        opt8init1(*n, *s, *t, *d, 17, in);
        cct_cls();
        cct_setcolor(0, 7);
        opt8init2(*n, *s, *t, *d, 17, in);
    }
    else if (option == 9) {
        cct_cls();
        cct_setcolor(0, 7);
        opt8init2(*n, *s, *t, *d, 17, in);
    }
}
void print_tower(int n, char src, char tmp, char dst, int position)
{
    char ch = '0';

    cct_gotoxy(base_x + 10, base_y - 5 + position);
    cout << "=========================" << endl;
    cct_gotoxy(base_x + 10, base_y - 4 + position);
    cout << "  A         B         C";

    if (src == 'A' && dst == 'B') {
        cct_gotoxy(11, base_y - 5 - top1 - 1 + position);
        cout << setw(2) << ' ';
        cct_gotoxy(21, base_y - 5 - top2 + position);
        cout << setw(2) << TMP[top2 - 1];
    }
    else if (src == 'A' && dst == 'C') {
        cct_gotoxy(11, base_y - 5 - top1 - 1 + position);
        cout << setw(2) << ' ';
        cct_gotoxy(31, base_y - 5 - top3 + position);
        cout << setw(2) << DST[top3 - 1];
    }

    else if (src == 'B' && dst == 'A') {
        cct_gotoxy(21, base_y - 5 - top2 - 1 + position);
        cout << setw(2) << ' ';
        cct_gotoxy(11, base_y - 5 - top1 + position);
        cout << setw(2) << SRC[top1 - 1];
    }
    else if (src == 'B' && dst == 'C') {
        cct_gotoxy(21, base_y - 5 - top2 - 1 + position);
        cout << setw(2) << ' ';
        cct_gotoxy(31, base_y - 5 - top3 + position);
        cout << setw(2) << DST[top3 - 1];
    }
    else if (src == 'C' && dst == 'A') {
        cct_gotoxy(31, base_y - 5 - top3 - 1 + position);
        cout << setw(2) << ' ';
        cct_gotoxy(11, base_y - 5 - top1 + position);
        cout << setw(2) << SRC[top1 - 1];
    }
    else if (src == 'C' && dst == 'B') {
        cct_gotoxy(31, base_y - 5 - top3 - 1 + position);
        cout << setw(2) << ' ';
        cct_gotoxy(21, base_y - 5 - top2 + position);
        cout << setw(2) << TMP[top2 - 1];
    }


    return;
}
void print_array(int n, char src, char tmp, char dst, int position)
{
    int i;
    char ch = '0';

    cout << " A:";
    for (i = 0;i < 10;i++) {
        if (i < top1)
            cout << setw(2) << SRC[i];
        else
            cout << "  ";
    }
    cout << " B:";
    for (i = 0;i < 10;i++) {
        if (i < top2)
            cout << setw(2) << TMP[i];
        else
            cout << "  ";
    }
    cout << " C:";
    for (i = 0;i < 10;i++) {
        if (i < top3)
            cout << setw(2) << DST[i];
        else
            cout << "  ";
    }

    return;
}
void show_and_erase2(int flag, int i, int j, int k, int n, char src, char tmp, char dst)
{
    int x, y;
    int srcX, dstX;

    // 计算起始柱子和目标柱子在屏幕上的位置
    if (src == 'A')
        srcX = base_x + 1 + max_pan;
    else if (src == 'B')
        srcX = base_x + 6 + base_pan + max_pan;
    else if (src == 'C')
        srcX = base_x + 11 + 2 * base_pan + max_pan;

    if (dst == 'A')
        dstX = base_x + 1 + max_pan;
    else if (dst == 'B')
        dstX = base_x + 6 + base_pan + max_pan;
    else if (dst == 'C')
        dstX = base_x + 11 + 2 * base_pan + max_pan;

    if (flag) {
        for (i = 1;i <= 2 * j + 1;i++) {  // 一个盘打印2n+1次
            if (src == 'A')
                cct_showch(srcX - j + i, base_y + k, ' ', j, 0, 1);
            if (src == 'B')
                cct_showch(srcX - j + i, base_y + k, ' ', j, 0, 1);
            if (src == 'C')
                cct_showch(srcX - j + i, base_y + k, ' ', j, 0, 1);
        }
    }
    else {
        for (i = 1;i <= 2 * j + 1;i++) {  // 消除
            cct_getxy(x, y);
            if (src == 'A') {
                if (x != (base_x + 1 + base_pan / 2))
                    cct_showch(srcX - j + i, base_y + k, ' ', 0, 0, 1);
                else if (k >= -11)
                    cct_showch(srcX - j + i, base_y + k, ' ', 14, 0, 1);
                else
                    cct_showch(srcX - j + i, base_y + k, ' ', 0, 0, 1);
            }
            if (src == 'B') {
                if (x != (base_x + 6 + 3 * base_pan / 2))
                    cct_showch(srcX - j + i, base_y + k, ' ', 0, 0, 1);
                else if (k >= -11)
                    cct_showch(srcX - j + i, base_y + k, ' ', 14, 0, 1);
                else
                    cct_showch(srcX - j + i, base_y + k, ' ', 0, 0, 1);
            }
            if (src == 'C') {
                if (x != (base_x + 11 + 5 * base_pan / 2))
                    cct_showch(srcX - j + i, base_y + k, ' ', 0, 0, 1);
                else if (k >= -11)
                    cct_showch(srcX - j + i, base_y + k, ' ', 14, 0, 1);
                else
                    cct_showch(srcX - j + i, base_y + k, ' ', 0, 0, 1);
            }
        }
    }

}
void shuiping_move2(int i, int j, int k, int n, char src, char tmp, char dst)
{
    int steps = (5 + base_pan) * (dst - src);
    int direction = (dst > src) ? 1 : -1;  // 移动方向，右为正，左为负
    int srcX, dstX;

    // 计算起始柱子和目标柱子在屏幕上的位置
    if (src == 'A')
        srcX = base_x + 1 + max_pan;
    else if (src == 'B')
        srcX = base_x + 6 + base_pan + max_pan;
    else if (src == 'C')
        srcX = base_x + 11 + 2 * base_pan + max_pan;

    if (dst == 'A')
        dstX = base_x + 1 + max_pan;
    else if (dst == 'B')
        dstX = base_x + 6 + base_pan + max_pan;
    else if (dst == 'C')
        dstX = base_x + 11 + 2 * base_pan + max_pan;

    for (int p = 1;p <= fabs(steps);p++) {
        // 显示
        for (i = 1;i <= 2 * j + 1;i++) {  // 一个盘打印2n+1次
            if (src == 'A')
                cct_showch(srcX + p * direction - j + i, base_y + k, ' ', j, 0, 1);
            if (src == 'B')
                cct_showch(srcX + p * direction - j + i, base_y + k, ' ', j, 0, 1);
            if (src == 'C')
                cct_showch(srcX + p * direction - j + i, base_y + k, ' ', j, 0, 1);
        }
        Sleep(10);
        // 擦除
        for (i = 1;i <= 2 * j + 1;i++) {  // 一个盘打印2n+1次
            if (src == 'A')
                cct_showch(srcX + p * direction - j + i, base_y + k, ' ', 0, 0, 1);
            if (src == 'B')
                cct_showch(srcX + p * direction - j + i, base_y + k, ' ', 0, 0, 1);
            if (src == 'C')
                cct_showch(srcX + p * direction - j + i, base_y + k, ' ', 0, 0, 1);
        }
    }


}
void move(int choice, int flag, int i, int j, int k, int n, char src, char tmp, char dst)
{
    switch (choice) {
        case 1:
            show_and_erase2(flag, i, j, k, n, src, tmp, dst);
            break;
        case 2:
            shuiping_move2(i, j, k, n, src, tmp, dst);
            break;
    }
}
void print_column(int n, char src, char tmp, char dst, int option, int interval)
{
    if (option >= 6) {
        cct_gotoxy(0, 0);
        cct_setcolor(0, 7);
        cout << "从 " << src << " 移动到 " << dst << " ，共 " << n << " 层 ";
    }
    cct_setcolor(14, 0);
    cct_gotoxy(base_x, base_y);
    cct_setcursor(CURSOR_INVISIBLE);
    cct_showch(base_x + 1, base_y, ' ', 14, 0, base_pan);
    cct_showch(base_x + 6 + base_pan, base_y, ' ', 14, 0, base_pan);
    cct_showch(base_x + 11 + 2 * base_pan, base_y, ' ', 14, 0, base_pan);
    for (int i = 1;i < 12;i++) {
        cct_showch(base_x + 1 + base_pan / 2, base_y - i, ' ', 14, 0, 1);
        cct_showch(base_x + 6 + 3 * base_pan / 2, base_y - i, ' ', 14, 0, 1);
        cct_showch(base_x + 11 + 5 * base_pan / 2, base_y - i, ' ', 14, 0, 1);
        Sleep(100);
    }

    int i = 0, j = 0, k = 0;;
    if (option >= 6) {
        cct_gotoxy(0, 0);
        cct_setcolor(0, 7);
        cout << "从 " << src << " 移动到 " << dst << " ，共 " << n << " 层 ";
        if (option == 8)
            cout << "，延时设置为 " << interval;
        for (j = n;j > 0;j--) {  // 盘号
            for (i = 1;i <= 2 * j + 1;i++) {  // 一个盘打印2n+1次
                if (src == 'A')
                    cct_showch(base_x + 1 + max_pan - j + i, base_y - n - 1 + j, ' ', j, 0, 1);
                if (src == 'B')
                    cct_showch(base_x + 6 + base_pan + max_pan - j + i, base_y - n - 1 + j, ' ', j, 0, 1);
                if (src == 'C')
                    cct_showch(base_x + 11 + 2 * base_pan + max_pan - j + i, base_y - n - 1 + j, ' ', j, 0, 1);
            }
            Sleep(100);
        }
    }

    i = 1;
    j++;

    cct_gotoxy(base_x, base_y + 2);
    cct_setcursor(CURSOR_VISIBLE_NORMAL);
    cct_setcolor(0, 7);
}
void output(int n, char src, char tmp, char dst, int option, int interval)
{
    int j = 0, k = 0, TOP1 = 0, TOP3 = 0;
    if (option != 7 && option != 6) {
        if (option >= 2) {
            if (option == 4)
                cct_gotoxy(base_x, base_y);
            if (option >= 8) {
                cct_setcolor(0, 7);
                cct_gotoxy(base_x, base_y + 17);
            }
            cout << "第" << setw(4) << step << " 步( ";
        }

        cout << setw(2) << n << "# " << src << "-->" << dst;

        if (option >= 2)
            cout << "  )";
    }
    if (src == 'A' && dst == 'B') {
        TOP1 = top1;
        TOP3 = top2;
        j = SRC[top1 - 1];
        TMP[top2++] = SRC[--top1];
    }
    else if (src == 'A' && dst == 'C') {
        TOP1 = top1;
        TOP3 = top3;
        j = SRC[top1 - 1];
        DST[top3++] = SRC[--top1];
    }
    else if (src == 'B' && dst == 'A') {
        TOP1 = top2;
        TOP3 = top1;
        j = TMP[top2 - 1];
        SRC[top1++] = TMP[--top2];
    }
    else if (src == 'B' && dst == 'C') {
        TOP1 = top2;
        TOP3 = top3;
        j = TMP[top2 - 1];
        DST[top3++] = TMP[--top2];
    }
    else if (src == 'C' && dst == 'A') {
        TOP1 = top3;
        TOP3 = top1;
        j = DST[top3 - 1];
        SRC[top1++] = DST[--top3];
    }
    else if (src == 'C' && dst == 'B') {
        TOP1 = top3;
        TOP3 = top2;
        j = DST[top3 - 1];
        TMP[top2++] = DST[--top3];
    }
    if (option == 3)
        print_array(n, src, tmp, dst, 0);
    if (option == 4) {
        print_array(n, src, tmp, dst, 0);
        setpace(interval);
        print_tower(n, src, tmp, dst, 2);
        setpace(interval);
        return;
    }
    if (option >= 7) {
        int i = 1;
        if (option == 7)
            n = 1;
        cct_setcolor(0, 7);
        if (option != 7) {
            print_array(n, src, tmp, dst, 17);
            setpace(interval);
            print_tower(n, src, tmp, dst, 17);
            setpace(interval);
        }
        move(1, 0, i, n, -TOP1, top1 + top2 + top3, src, tmp, dst);
        for (k = -1 - TOP1;k >= -13 + TOP1;k--) {
            move(1, 1, i, n, k, top1 + top2 + top3, src, tmp, dst);
            Sleep(10);
            move(1, 0, i, n, k, top1 + top2 + top3, src, tmp, dst);
        }
        move(2, 0, i, n, -13, top1 + top2 + top3, src, tmp, dst);
        for (k = -13;k <= -2 - TOP3;k++) {
            move(1, 1, i, n, k, top1 + top2 + top3, dst, tmp, src);
            Sleep(10);
            move(1, 0, i, n, k, top1 + top2 + top3, dst, tmp, src);
        }
        move(1, 1, i, n, k, top1 + top2 + top3, dst, tmp, src);
    }
    cct_setcolor(0, 7);
    cout << endl;
    return;
}
void game(int interval, int D, int TOP3)
{
    while (1) {
        int x = 0, y = 0;
        char src = 'A', tmp = 'B', dst = 'C';
        int flag = 1;
        int n = 0, j = 0;

        while (flag) {
            x = 0, y = 0;
            src = 'A', tmp = 'B', dst = 'C';
            flag = 1;
            n = 0, j = 0;
            cct_gotoxy(base_x, base_y + 19);
            cout << "请输入移动的柱号(命令形式：AC=A顶端的盘子移动到C，Q=退出) ：";
            cct_getxy(x, y);

            src = getchar();
            if (src == 'q')
                return;
            dst = getchar();
            while (getchar() != '\n'); // 清除输入缓冲区
            if (src == 'Q')
                return;
            if (src >= 'a' && src <= 'c')
                src = char(src + 'A' - 'a');
            if (dst >= 'a' && dst <= 'c')
                dst = char(dst + 'A' - 'a');
            flag = !cin.good() || !(src >= 'A' && src <= 'C') && !(src >= 'a' && src <= 'c')
                || !(dst >= 'A' && dst <= 'C') && !(dst >= 'a' && dst <= 'c') || dst == src;

            if (flag) {
                cin.clear();  // 清除错误状态标志
                //cct_getxy(x, y);
                cct_gotoxy(x, y);
                cout << "  ";
                cct_gotoxy(x, y);
                //   while (getchar() != '\n');
                continue;
            }
            else {
                if (src >= 'a' && src <= 'c')
                    src = char(src + 'A' - 'a');
                if (dst >= 'a' && dst <= 'c')
                    dst = char(dst + 'A' - 'a');

                if (src == 'A' && dst == 'B') {
                    n = SRC[top1 - 1];
                    if (top2 > 0)
                        j = TMP[top2 - 1];
                    else
                        j = 0;
                    //    TMP[top2++] = SRC[--top1];
                }
                else if (src == 'A' && dst == 'C') {
                    n = SRC[top1 - 1];
                    if (top3 > 0)
                        j = DST[top3 - 1];
                    else
                        j = 0;
                    //    DST[top3++] = SRC[--top1];
                }
                else if (src == 'B' && dst == 'A') {
                    n = TMP[top2 - 1];
                    if (top1 > 0)
                        j = SRC[top1 - 1];
                    else
                        j = 0;
                    //    SRC[top1++] = TMP[--top2];
                }
                else if (src == 'B' && dst == 'C') {
                    n = TMP[top2 - 1];
                    if (top3 > 0)
                        j = DST[top3 - 1];
                    else
                        j = 0;
                    //    DST[top3++] = TMP[--top2];
                }
                else if (src == 'C' && dst == 'A') {
                    n = DST[top3 - 1];
                    if (top1 > 0)
                        j = SRC[top1 - 1];
                    else
                        j = 0;
                    //   SRC[top1++] = DST[--top3];
                }
                else if (src == 'C' && dst == 'B') {
                    n = DST[top3 - 1];
                    if (top2 > 0)
                        j = TMP[top2 - 1];
                    else
                        j = 0;
                    //    TMP[top2++] = DST[--top3];
                }

                if (n <= 0) {
                    cin.clear();  // 清除错误状态标志
                    flag = 1;
                    cct_gotoxy(x, y);
                    cout << "  ";
                    cout << '\n' << "源柱为空！";
                    Sleep(1000);
                    cct_gotoxy(0, y + 1);
                    cout << "                   ";
                    cct_gotoxy(x, y);
                    continue;
                }
                else if (n > j && j > 0) {
                    cin.clear();  // 清除错误状态标志
                    flag = 1;
                    cct_gotoxy(x, y);
                    cout << "  ";
                    cout << '\n' << "大盘压小盘，非法移动！";
                    Sleep(1000);
                    cct_gotoxy(0, y + 1);
                    cout << "                     ";
                    cct_gotoxy(x, y);
                    continue;
                }

            }
            break;
            while (getchar() != '\n'); // 清除输入缓冲区
        }

        tmp = 'A' + 'B' + 'C' - src - dst;

        step++;
        output(n, src, tmp, dst, 9, interval);
        cct_setcolor(0, 7);

        cct_gotoxy(x, y);
        cout << "  ";
        cct_gotoxy(x, y);

        int N = top1 + top2 + top3;

        if (D == 'A' && top1 == N || D == 'B' && top2 == N || D == 'C' && top3 == N) {

            return;
        }
        else {
            continue;
        }
    }
}
void hanoi(int n, char src, char tmp, char dst, int option, int interval)
{
    if (n == 1) {
        step++;
        output(n, src, tmp, dst, option, interval);
    }
    else {
        hanoi(n - 1, src, dst, tmp, option, interval);
        step++;
        output(n, src, tmp, dst, option, interval);
        hanoi(n - 1, tmp, src, dst, option, interval);
    }
}
