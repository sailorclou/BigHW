/* 2351044 ������ ������ */

#include "90-01-b2-gmw-magic_ball.h"

int main()
{

	CONSOLE_GRAPHICS_INFO MyCGI;
	BLOCK_DISPLAY_INFO bdi[] = {
		{BDI_VALUE_BLANK, -1, -1, "  "},						//0����ʾ���ÿո���伴��
		{1,  COLOR_HBLACK, -1, "��"},				//�����������1������ʾ������
		{2,  COLOR_HBLUE, COLOR_HYELLOW, "��"},	//�����������2������ʾ˫�߿�����
		{3,  COLOR_HBLUE, COLOR_HYELLOW, "��"},	//�����������3
		{4,  COLOR_HRED, -1, NULL},				//�����������4����ֱ����ʾ4��NULL��ʾֱ����ʾ���֣�
		{5,  COLOR_HBLUE, COLOR_HYELLOW, "��"},	//�����������5
		{BDI_VALUE_END, -1, -1, NULL}			//��BDI_VALUE_END������һ��Ҫ��!!!
	};
	cct_setcolor(0, 7);
	cct_cls();
	cct_setconsoleborder(50, 30);
	cct_setfontsize("������", 18, 0);
	cct_cls();
	initial(&MyCGI);
	operate(&MyCGI, bdi);

	return 0;
}