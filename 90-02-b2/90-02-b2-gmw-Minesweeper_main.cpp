/* 2351044 大数据 崔艺洋 */

#include "90-02-b2-gmw-Minesweeper.h"

int main()
{
	CONSOLE_GRAPHICS_INFO MyCGI;
	BLOCK_DISPLAY_INFO bdi[] = {
		{BDI_VALUE_BLANK, COLOR_YELLOW, COLOR_YELLOW, "  "},	//0不显示，用空格填充即可
		{1,  COLOR_WHITE, COLOR_HBLUE, NULL},
		{2,  COLOR_WHITE, COLOR_HGREEN, NULL},
		{3,  COLOR_WHITE, COLOR_BLUE, NULL},
		{4,  COLOR_WHITE, COLOR_HRED, NULL},
		{5,  COLOR_WHITE, COLOR_HPINK, NULL},
		{6,  COLOR_WHITE, COLOR_BLACK, "¤"},
		{BDI_VALUE_END, -1, -1, NULL}	
	};
	cct_setcolor(0, 7);
	cct_cls();
	cct_setconsoleborder(60, 30);
	cct_setfontsize("新宋体", 18, 0);
	cct_cls();
	initial(&MyCGI);
	operate(&MyCGI, bdi);
	cct_setcolor(0, 7);
	return 0;
}