/* 2351044 ������ ������ */

#include "90-02-b1-gmw-pop_star.h"

int main()
{
	CONSOLE_GRAPHICS_INFO MyCGI;
	BLOCK_DISPLAY_INFO bdi[] = {
		{BDI_VALUE_BLANK, -1, -1, "  "},						//0����ʾ���ÿո���伴��
		{1,  COLOR_HBLACK, -1, "��"},			
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