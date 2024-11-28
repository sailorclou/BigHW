/* 2351044 大数据 崔艺洋 */

#include "90-02-b1-gmw-pop_star.h"

int main()
{
	CONSOLE_GRAPHICS_INFO MyCGI;
	BLOCK_DISPLAY_INFO bdi[] = {
		{BDI_VALUE_BLANK, -1, -1, "  "},						//0不显示，用空格填充即可
		{1,  COLOR_HBLACK, -1, "★"},			
		{BDI_VALUE_END, -1, -1, NULL}			//以BDI_VALUE_END结束，一定要有!!!
	};
	cct_setcolor(0, 7);
	cct_cls();
	cct_setconsoleborder(50, 30);
	cct_setfontsize("新宋体", 18, 0);
	cct_cls();
	initial(&MyCGI);
	operate(&MyCGI, bdi);

	return 0;
}