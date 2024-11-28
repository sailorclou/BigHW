/* 2351044 ������ ������ */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <climits>
#include <conio.h>
#include <windows.h>
#include "../include/cmd_console_tools.h"
#include "../include/cmd_gmw_tools.h"
using namespace std;

/* --------------------------------------------------
		�˴����Ը�����Ҫ�ľ�̬ȫ�ֱ������������٣����û�У�����̬ȫ��ֻ������/�궨�壨�������ޣ���
   -------------------------------------------------- */


   /* --------------------------------------------------
		   �˴����Ը�����Ҫ���ڲ��������ߺ���
		   1�����������ޣ�����Ϊ gmw_inner_*
		   2����������
		   3��������static������ȷ��ֻ�ڱ�Դ�ļ���ʹ��
	  -------------------------------------------------- */
static int gmw_inner_getNumLen(int num) 
{
	int len = 0;
	while (num != 0) {
		num /= 10;
		len++;
	}
	return len;
}

	  /* -----------------------------------------------
			  ʵ����������ĺ���������������׼����
		 ----------------------------------------------- */
		 /***************************************************************************
		   �������ƣ�
		   ��    �ܣ�������Ϸ����ܵ�������
		   ���������CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
					 const int row						������(������Ϊ0���������ޣ���Ϊ��֤��ȷ��)
					 const int col						������(������Ϊ0���������ޣ���Ϊ��֤��ȷ��)
		   �� �� ֵ��
		   ˵    ����1��ָ��������Ϸ�ľ������������ֵ
					 2�����еı仯�ᵼ��CONSOLE_GRAPHICS_INFO�ṹ����������Աֵ�ı仯��Ҫ����
		 ***************************************************************************/
int gmw_set_rowcol(CONSOLE_GRAPHICS_INFO* const pCGI, const int row, const int col)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;
	pCGI->row_num = row;
	pCGI->col_num = col;
	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ������������ڣ�����Ϸ�������������ڵ�����cmd���ڣ�����ɫ
  ���������CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
		   const int bg_color					��ǰ��ɫ��ȱʡCOLOR_BLACK��
		   const int fg_color					������ɫ��ȱʡCOLOR_WHITE��
		   const bool cascade					���Ƿ�����ȱʡΪtrue-������
  �� �� ֵ��
  ˵    ����1��cascade = trueʱ
				ͬ���޸���Ϸ���������ɫ
				ͬ���޸�����״̬���������ı��ı���ɫ��ǰ��ɫ����Ŀ�ı��ı���ɫ��ǰ��ɫ���䣩
			2���������ɫֵ���󼰳�ͻ����Ҫ��Ϊ��֤
				������ɫ��0-15
					ǰ��ɫ����ɫ��ֵһ�µ����޷���������
					ǰ��ɫ������״̬����Ŀǰ��ɫ�������޷�������Ŀ��ʾ
					...
***************************************************************************/
int gmw_set_color(CONSOLE_GRAPHICS_INFO* const pCGI, const int bgcolor, const int fgcolor, const bool cascade)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;
	cct_setcolor(bgcolor, fgcolor);
	pCGI->area_bgcolor = bgcolor;
	pCGI->area_fgcolor = fgcolor;
	if (cascade) {
		pCGI->CFI.bgcolor = pCGI->area_bgcolor;
		pCGI->CFI.fgcolor = pCGI->area_fgcolor;
		pCGI->SLI.top_normal_bgcolor = pCGI->area_bgcolor;
		pCGI->SLI.top_normal_fgcolor = pCGI->area_fgcolor;
		pCGI->SLI.lower_normal_bgcolor = pCGI->area_bgcolor;
		pCGI->SLI.lower_normal_fgcolor = pCGI->area_fgcolor;
		pCGI->SLI.top_catchy_bgcolor = pCGI->area_bgcolor;
		//pCGI->SLI.top_catchy_fgcolor = 14;
		pCGI->SLI.lower_catchy_bgcolor = pCGI->area_bgcolor;
		//pCGI->SLI.lower_catchy_fgcolor = 14;
	}
	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ����ô��ڵ�����
  ���������CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
		   const char *fontname					���������ƣ�ֻ����"Terminal"��"������"���֣������򷵻�-1�����ı����壩
		   const int fs_high					������߶ȣ�ȱʡ������Ϊ16�������������ƣ���Ϊ��֤��
		   const int fs_width					������߶ȣ�ȱʡ������Ϊ8�������������ƣ���Ϊ��֤��
  �� �� ֵ��
  ˵    ����1����cmd_console_tools�е�setfontsize���ƣ�Ŀǰֻ֧�֡��������塱�͡������塱
			2������������������ֱ�ӷ��أ�����ԭ�������ò���
***************************************************************************/
int gmw_set_font(CONSOLE_GRAPHICS_INFO* const pCGI, const char* fontname, const int fs_high, const int fs_width)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;
	cct_setfontsize(fontname, 16, 8);
	if (!strcmp(fontname, "Terminal") && !strcmp(fontname, "������"))
		return -1;
	cct_setfontsize(fontname, fs_high, fs_width);
	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�������ʱ
  ���������CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
		   const int type						����ʱ�����ͣ�ĿǰΪ3�֣�
		   const int delay_ms					����msΪ��λ����ʱ
			   ���߿����ʱ��0 ~ �������ޣ���Ϊ��֤��ȷ��<0����0��
			   ��ɫ�����ʱ��0 ~ �������ޣ���Ϊ��֤��ȷ��<0����0��
			   ɫ���ƶ�����ʱ��BLOCK_MOVED_DELAY_MS ~ �������ޣ���Ϊ��֤��ȷ�� <BLOCK_MOVED_DELAY_MS ���� BLOCK_MOVED_DELAY_MS��
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int gmw_set_delay(CONSOLE_GRAPHICS_INFO* const pCGI, const int type, const int delay_ms)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;
	switch (type) {
		case 0:
			pCGI->delay_of_draw_frame = delay_ms;
			break;
		case 1:
			pCGI->delay_of_draw_block = delay_ms;
			break;
		case 2:
			pCGI->delay_of_block_moved = delay_ms;
			break;
	}
	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ���������������Ϸ����ܽṹ֮����Ҫ�����Ķ�������
  ��    �ܣ�CONSOLE_GRAPHICS_INFO *const pCGI	��
		   const int up_lines					���ϲ�������У�ȱʡ������Ϊ0���������ޣ���Ϊ��֤��
		   const int down_lines				���²�������У�ȱʡ������Ϊ0���������ޣ���Ϊ��֤��
		   const int left_cols					����߶�����У�ȱʡ������Ϊ0���������ޣ���Ϊ��֤��
		   const int right_cols				���ұ߶�����У�ȱʡ������Ϊ0���������ޣ���Ϊ��֤��
  �� �� ֵ��
  ˵    �����������еı仯�ᵼ��CONSOLE_GRAPHICS_INFO�ṹ����������Աֵ�ı仯��Ҫ����
***************************************************************************/
int gmw_set_ext_rowcol(CONSOLE_GRAPHICS_INFO* const pCGI, const int up_lines, const int down_lines, const int left_cols, const int right_cols)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;
	pCGI->extern_up_lines += up_lines;
	pCGI->extern_down_lines += down_lines;
	pCGI->extern_left_cols += left_cols;
	pCGI->extern_right_cols += right_cols;
	pCGI->SLI.top_start_x = pCGI->extern_left_cols;
	pCGI->SLI.lower_start_x = pCGI->extern_left_cols;
	pCGI->SLI.top_start_y = pCGI->extern_up_lines;
	pCGI->SLI.lower_start_y = pCGI->extern_up_lines + pCGI->draw_frame_with_col_no + pCGI->SLI.is_top_status_line\
		+ pCGI->row_num * pCGI->CFI.block_high + 2 + (pCGI->row_num - 1) * pCGI->CFI.separator;
	pCGI->start_x = pCGI->extern_left_cols + pCGI->draw_frame_with_row_no;
	pCGI->start_y = pCGI->extern_up_lines + pCGI->draw_frame_with_col_no + pCGI->SLI.is_top_status_line;
	pCGI->lines = pCGI->row_num * pCGI->CFI.block_high + 2 + (pCGI->row_num - 1) * pCGI->CFI.separator + \
		pCGI->extern_up_lines + pCGI->extern_down_lines + pCGI->SLI.is_top_status_line\
		+ pCGI->SLI.is_lower_status_line + pCGI->draw_frame_with_col_no;
	pCGI->cols = pCGI->col_num * pCGI->CFI.block_width + 2 + 2 * (pCGI->col_num - 1) * pCGI->CFI.separator + \
		pCGI->extern_left_cols + pCGI->extern_right_cols + 2 * pCGI->draw_frame_with_row_no;
	
	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���� CONSOLE_FRAME_TYPE �ṹ�е�11�����ͣ�ȱʡ4�֣�
  ���������CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
			const int type						��1 - ȫ�� 2 - ȫ���� 3 - ��˫���� 4 - �ᵥ��˫
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int gmw_set_frame_default_linetype(CONSOLE_GRAPHICS_INFO* const pCGI, const int type)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;
	switch (type) {
		case 1:
			strcpy(pCGI->CFI.top_left, "�X");
			strcpy(pCGI->CFI.lower_left, "�^");
			strcpy(pCGI->CFI.top_right, "�[");
			strcpy(pCGI->CFI.lower_right, "�a");
			strcpy(pCGI->CFI.h_normal, "�T");    // Horizontal
			strcpy(pCGI->CFI.v_normal, "�U");    // Vertical
			strcpy(pCGI->CFI.h_top_separator, "�j");
			strcpy(pCGI->CFI.h_lower_separator, "�m");
			strcpy(pCGI->CFI.v_left_separator, "�d");
			strcpy(pCGI->CFI.v_right_separator, "�g");
			strcpy(pCGI->CFI.mid_separator, "�p");
			break;
		case 2:
			strcpy(pCGI->CFI.top_left, "��");
			strcpy(pCGI->CFI.lower_left, "��");
			strcpy(pCGI->CFI.top_right, "��");
			strcpy(pCGI->CFI.lower_right, "��");
			strcpy(pCGI->CFI.h_normal, "��");    // Horizontal
			strcpy(pCGI->CFI.v_normal, "��");    // Vertical
			strcpy(pCGI->CFI.h_top_separator, "��");
			strcpy(pCGI->CFI.h_lower_separator, "��");
			strcpy(pCGI->CFI.v_left_separator, "��");
			strcpy(pCGI->CFI.v_right_separator, "��");
			strcpy(pCGI->CFI.mid_separator, "��");
			break;
		case 3:
			strcpy(pCGI->CFI.top_left, "�V");
			strcpy(pCGI->CFI.lower_left, "�\");
			strcpy(pCGI->CFI.top_right, "�Y");
			strcpy(pCGI->CFI.lower_right, "�_");
			strcpy(pCGI->CFI.h_normal, "�T");    // Horizontal
			strcpy(pCGI->CFI.v_normal, "��");    // Vertical
			strcpy(pCGI->CFI.h_top_separator, "�h");
			strcpy(pCGI->CFI.h_lower_separator, "�k");
			strcpy(pCGI->CFI.v_left_separator, "�b");
			strcpy(pCGI->CFI.v_right_separator, "�e");
			strcpy(pCGI->CFI.mid_separator, "�n");
			break;
		case 4:
			strcpy(pCGI->CFI.top_left, "�W");
			strcpy(pCGI->CFI.lower_left, "�]");
			strcpy(pCGI->CFI.top_right, "�Z");
			strcpy(pCGI->CFI.lower_right, "�`");
			strcpy(pCGI->CFI.h_normal, "��");    // Horizontal
			strcpy(pCGI->CFI.v_normal, "�U");    // Vertical
			strcpy(pCGI->CFI.h_top_separator, "�i");
			strcpy(pCGI->CFI.h_lower_separator, "�l");
			strcpy(pCGI->CFI.v_left_separator, "�c");
			strcpy(pCGI->CFI.v_right_separator, "�f");
			strcpy(pCGI->CFI.mid_separator, "�o");
			break;
	}
	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���� CONSOLE_FRAME_TYPE �ṹ�е�11������
  ���������CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
			const char *...						����11�֣������.h���˴���
  �� �� ֵ��
  ˵    ����Լ��Ϊһ�������Ʊ��������ʹ���������ݣ���Ϊ��֤2�ֽ�
			1������2�ֽ���ֻȡǰ2�ֽ�
			2�������NULL���������ո����
			3�������1�ֽڣ���һ���ո������˶�������ʾ�ң������
***************************************************************************/
int gmw_set_frame_linetype(CONSOLE_GRAPHICS_INFO* const pCGI, const char* top_left, const char* lower_left, const char* top_right,
	const char* lower_right, const char* h_normal, const char* v_normal, const char* h_top_separator,
	const char* h_lower_separator, const char* v_left_separator, const char* v_right_separator, const char* mid_separator)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;
	strcpy(pCGI->CFI.top_left, top_left);
	strcpy(pCGI->CFI.lower_left, lower_left);
	strcpy(pCGI->CFI.top_right, top_right);
	strcpy(pCGI->CFI.lower_right, lower_right);
	strcpy(pCGI->CFI.h_normal, h_normal);
	strcpy(pCGI->CFI.v_normal, v_normal);
	strcpy(pCGI->CFI.h_top_separator, h_top_separator);
	strcpy(pCGI->CFI.h_lower_separator, h_lower_separator);
	strcpy(pCGI->CFI.v_left_separator, v_left_separator);
	strcpy(pCGI->CFI.v_right_separator, v_right_separator);
	strcpy(pCGI->CFI.mid_separator, mid_separator);
	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���� CONSOLE_FRAME_TYPE �ṹ�е�ɫ��������С���Ƿ���Ҫ�ָ��ߵ�
  ������������������CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
			const int block_width						����ȣ�����ȱʡ2����ΪԼ�������Ϊ�����Ʊ�����������������Ҫ+1��
			const int block_high						���߶ȣ�����ȱʡ1��
			const bool separator						���Ƿ���Ҫ�ָ��ߣ�ȱʡΪtrue����Ҫ�ָ��ߣ�
  �� �� ֵ��
  ˵    ������ܴ�С/�Ƿ���Ҫ�ָ��ߵȵı仯�ᵼ��CONSOLE_GRAPHICS_INFO�ṹ����������Աֵ�ı仯��Ҫ����
***************************************************************************/
int gmw_set_frame_style(CONSOLE_GRAPHICS_INFO* const pCGI, const int block_width, const int block_high, const bool separator)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;
	
	pCGI->CFI.block_width = block_width;
	if (pCGI->CFI.block_width % 2)
		pCGI->CFI.block_width += 1;
	pCGI->CFI.block_high = block_high;
	pCGI->CFI.separator = separator;
	pCGI->SLI.top_start_x = pCGI->extern_left_cols;
	pCGI->SLI.lower_start_x = pCGI->extern_left_cols;
	pCGI->SLI.top_start_y = pCGI->extern_up_lines;
	pCGI->SLI.lower_start_y = pCGI->extern_up_lines + pCGI->draw_frame_with_col_no + pCGI->SLI.is_top_status_line\
		+ pCGI->row_num * pCGI->CFI.block_high + 2 + (pCGI->row_num - 1) * pCGI->CFI.separator;
	pCGI->start_x = pCGI->extern_left_cols + 2 * pCGI->draw_frame_with_row_no;
	pCGI->start_y = pCGI->extern_up_lines + pCGI->draw_frame_with_col_no + pCGI->SLI.is_top_status_line;
	pCGI->lines = pCGI->row_num * pCGI->CFI.block_high + 2 + (pCGI->row_num - 1) * pCGI->CFI.separator + \
		pCGI->extern_up_lines + pCGI->extern_down_lines + pCGI->SLI.is_top_status_line\
		+ pCGI->SLI.is_lower_status_line + pCGI->draw_frame_with_col_no;
	pCGI->cols = pCGI->col_num * pCGI->CFI.block_width + 2 + 2*(pCGI->col_num - 1) * pCGI->CFI.separator + \
		pCGI->extern_left_cols + pCGI->extern_right_cols + 2 * pCGI->draw_frame_with_row_no;
	cct_setconsoleborder(pCGI->cols, pCGI->lines);
	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���� CONSOLE_BORDER_TYPE �ṹ�е���ɫ
  ���������CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
			const int bg_color					������ɫ��ȱʡ -1��ʾ�ô��ڱ���ɫ��
			const int fg_color					��ǰ��ɫ��ȱʡ -1��ʾ�ô���ǰ��ɫ��
  �� �� ֵ��
  ˵    �����������ɫֵ���󼰳�ͻ����Ҫ��Ϊ��֤
				������ɫ��0-15��ǰ��ɫ����ɫ��ֵһ�µ����޷��������ݵ�
***************************************************************************/
int gmw_set_frame_color(CONSOLE_GRAPHICS_INFO* const pCGI, const int bgcolor, const int fgcolor)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;
	pCGI->CFI.bgcolor = bgcolor;
	pCGI->CFI.fgcolor = fgcolor;
	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���� CONSOLE_BLOCK_INFO �ṹ�е�6�����ͣ�ȱʡ4�֣�
  ���������CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
			const int type						��1 - ȫ˫�� 2 - ȫ���� 3 - ��˫���� 4 - �ᵥ��˫
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int gmw_set_block_default_linetype(CONSOLE_GRAPHICS_INFO* const pCGI, const int type)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;
	
	switch (type) {
		case 1:
			strcpy(pCGI->CBI.top_left, "�X");
			strcpy(pCGI->CBI.lower_left, "�^");
			strcpy(pCGI->CBI.top_right, "�[");
			strcpy(pCGI->CBI.lower_right, "�a");
			strcpy(pCGI->CBI.h_normal, "�T");
			strcpy(pCGI->CBI.v_normal, "�U");
			break;
		case 2:
			strcpy(pCGI->CBI.top_left, "��");
			strcpy(pCGI->CBI.lower_left, "��");
			strcpy(pCGI->CBI.top_right, "��");
			strcpy(pCGI->CBI.lower_right, "��");
			strcpy(pCGI->CBI.h_normal, "��");    // Horizontal
			strcpy(pCGI->CBI.v_normal, "��");    // Vertical
			break;
		case 3:
			strcpy(pCGI->CBI.top_left, "�V");
			strcpy(pCGI->CBI.lower_left, "�\");
			strcpy(pCGI->CBI.top_right, "�Y");
			strcpy(pCGI->CBI.lower_right, "�_");
			strcpy(pCGI->CBI.h_normal, "�T");    // Horizontal
			strcpy(pCGI->CBI.v_normal, "��");    // Vertical
			break;
		case 4:
			strcpy(pCGI->CBI.top_left, "�W");
			strcpy(pCGI->CBI.lower_left, "�]");
			strcpy(pCGI->CBI.top_right, "�Z");
			strcpy(pCGI->CBI.lower_right, "�`");
			strcpy(pCGI->CBI.h_normal, "��");    // Horizontal
			strcpy(pCGI->CBI.v_normal, "�U");    // Vertical
			break;
	}
	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���� CONSOLE_BLOCK_INFO �ṹ�е�6������
  ���������CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
		   const char *...					����6�֣������.h���˴���
  �� �� ֵ��
  ˵    ����Լ��Ϊһ�������Ʊ��������ʹ���������ݣ���Ϊ��֤2�ֽ�
			1������2�ֽ���ֻȡǰ2�ֽ�
			2�������NULL���������ո����
			3�������1�ֽڣ���һ���ո������˶�������ʾ�ң������
***************************************************************************/
int gmw_set_block_linetype(CONSOLE_GRAPHICS_INFO* const pCGI, const char* top_left, const char* lower_left, const char* top_right, const char* lower_right, const char* h_normal, const char* v_normal)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;
	strcpy(pCGI->CBI.top_left, top_left);
	strcpy(pCGI->CBI.lower_left, lower_left);
	strcpy(pCGI->CBI.top_right, top_right);
	strcpy(pCGI->CBI.lower_right, lower_right);
	strcpy(pCGI->CBI.h_normal, h_normal);    // Horizontal
	strcpy(pCGI->CBI.v_normal, v_normal);    // Vertical
	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�����ÿ����Ϸɫ��(����)�Ƿ���ҪС�߿�
  ���������CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
		   const bool on_off					��true - ��Ҫ flase - ����Ҫ��ȱʡfalse��
  �� �� ֵ��
  ˵    �����߿�Լ��Ϊ�����Ʊ����˫��
***************************************************************************/
int gmw_set_block_border_switch(CONSOLE_GRAPHICS_INFO* const pCGI, const bool on_off)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;
	pCGI->CBI.block_border = on_off;
	gmw_set_block_default_linetype(pCGI, 1);
	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ������Ƿ���ʾ����״̬��
  ���������CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
			const int type						��״̬�����ͣ���/�£�
			const bool on_off					��true - ��Ҫ flase - ����Ҫ��ȱʡtrue��
  �� �� ֵ��
  ˵    ����1��״̬�������Լ�����£�
			   1.1����״̬��ֻ��һ�У������������Ϸ�����/�б�����棬Ϊ��������ʼһ�У�����������Ͻ����������״̬�������꣩
			   1.2����״̬��ֻ��һ�У������������·����ߵ�����
			   1.3��״̬���Ŀ��Ϊ�������ȣ������Ϣ������ض�
		   2�����еı仯�ᵼ��CONSOLE_GRAPHICS_INFO�ṹ����������Աֵ�ı仯��Ҫ����
***************************************************************************/
int gmw_set_status_line_switch(CONSOLE_GRAPHICS_INFO* const pCGI, const int type, const bool on_off)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;
	if (type == TOP_STATUS_LINE) {
		pCGI->top_status_line = on_off;
		pCGI->SLI.is_top_status_line = on_off;
	}
	else if (type == LOWER_STATUS_LINE) {
		pCGI->lower_status_line = on_off;
		pCGI->SLI.is_lower_status_line = on_off;
	}
	pCGI->SLI.top_start_y = pCGI->extern_up_lines;
	pCGI->SLI.lower_start_y = pCGI->extern_up_lines + pCGI->draw_frame_with_col_no + pCGI->SLI.is_top_status_line\
		+ pCGI->row_num * pCGI->CFI.block_high + 2 + (pCGI->row_num - 1) * pCGI->CFI.separator;
	pCGI->start_x = pCGI->extern_left_cols + 2 * pCGI->draw_frame_with_row_no;
	pCGI->start_y = pCGI->extern_up_lines + pCGI->draw_frame_with_col_no + pCGI->SLI.is_top_status_line;
	pCGI->lines = pCGI->row_num * pCGI->CFI.block_high + 2 + (pCGI->row_num - 1) * pCGI->CFI.separator + \
		pCGI->extern_up_lines + pCGI->extern_down_lines + pCGI->SLI.is_top_status_line\
		+ pCGI->SLI.is_lower_status_line + pCGI->draw_frame_with_col_no;
	pCGI->cols = pCGI->col_num * pCGI->CFI.block_width + 2 + 2 * (pCGI->col_num - 1) * pCGI->CFI.separator + \
		pCGI->extern_left_cols + pCGI->extern_right_cols + 2 * pCGI->draw_frame_with_row_no;
	cct_setconsoleborder(pCGI->cols, pCGI->lines);

	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���������״̬������ɫ
  ���������CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
			const int type						��״̬�����ͣ���/�£�
			const int normal_bgcolor			�������ı�����ɫ��ȱʡ -1��ʾʹ�ô��ڱ���ɫ��
			const int normal_fgcolor			�������ı�ǰ��ɫ��ȱʡ -1��ʾʹ�ô���ǰ��ɫ��
			const int catchy_bgcolor			����Ŀ�ı�����ɫ��ȱʡ -1��ʾʹ�ô��ڱ���ɫ��
			const int catchy_fgcolor			����Ŀ�ı�ǰ��ɫ��ȱʡ -1��ʾʹ������ɫ��
  ���������
  �� �� ֵ��
  ˵    �����������ɫֵ���󼰳�ͻ����Ҫ��Ϊ��֤
				������ɫ��0-15��ǰ��ɫ����ɫ��ֵһ�µ����޷��������ݵ�
***************************************************************************/
int gmw_set_status_line_color(CONSOLE_GRAPHICS_INFO* const pCGI, const int type, const int normal_bgcolor, const int normal_fgcolor, const int catchy_bgcolor, const int catchy_fgcolor)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;
	if (type == TOP_STATUS_LINE) {
		if (normal_bgcolor == -1) 
			pCGI->SLI.top_normal_bgcolor = pCGI->area_bgcolor;
		else
			pCGI->SLI.top_normal_bgcolor = normal_bgcolor;
		if (normal_fgcolor == -1)
			pCGI->SLI.top_normal_fgcolor = pCGI->area_fgcolor;
		else
			pCGI->SLI.top_normal_fgcolor = normal_fgcolor;
		if (catchy_bgcolor == -1)
			pCGI->SLI.top_catchy_bgcolor = pCGI->area_bgcolor;
		else
			pCGI->SLI.top_catchy_bgcolor = catchy_bgcolor;
		if (catchy_fgcolor == -1)
			pCGI->SLI.top_catchy_bgcolor = 14;
		else
			pCGI->SLI.top_catchy_fgcolor = catchy_fgcolor;
	}
	else if (type == LOWER_STATUS_LINE) {
		if (normal_bgcolor == -1)
			pCGI->SLI.lower_normal_bgcolor = pCGI->area_bgcolor;
		else
			pCGI->SLI.lower_normal_bgcolor = normal_bgcolor;
		if (normal_fgcolor == -1)
			pCGI->SLI.lower_normal_fgcolor = pCGI->area_fgcolor;
		else
			pCGI->SLI.lower_normal_fgcolor = normal_fgcolor;
		if (catchy_bgcolor == -1)
			pCGI->SLI.lower_catchy_bgcolor = pCGI->area_bgcolor;
		else
			pCGI->SLI.lower_catchy_bgcolor = catchy_bgcolor;
		if (catchy_fgcolor == -1)
			pCGI->SLI.lower_catchy_fgcolor = 14;
		else
			pCGI->SLI.lower_catchy_fgcolor = catchy_fgcolor;
	}
	
	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ������Ƿ���ʾ�к�
  ���������CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
			const bool on_off					��true - ��ʾ flase - ����ʾ��ȱʡfalse��
  �� �� ֵ��
  ˵    ����1���к�Լ��Ϊ��ĸA��ʼ�������У��������26�����a��ʼ������52��ͳһΪ*��ʵ��Ӧ�ò����ܣ�
			2���Ƿ���ʾ�кŵı仯�ᵼ��CONSOLE_GRAPHICS_INFO�ṹ����������Աֵ�ı仯��Ҫ����
***************************************************************************/
int gmw_set_rowno_switch(CONSOLE_GRAPHICS_INFO* const pCGI, const bool on_off)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;
	pCGI->draw_frame_with_row_no = on_off;
	pCGI->SLI.top_start_y = pCGI->extern_up_lines;
	pCGI->SLI.lower_start_y = pCGI->extern_up_lines + pCGI->draw_frame_with_col_no + pCGI->SLI.is_top_status_line\
		+ pCGI->row_num * pCGI->CFI.block_high + 2 + (pCGI->row_num - 1) * pCGI->CFI.separator;
	pCGI->start_x = pCGI->extern_left_cols + 2 * pCGI->draw_frame_with_row_no;
	pCGI->start_y = pCGI->extern_up_lines + pCGI->draw_frame_with_col_no + pCGI->SLI.is_top_status_line;
	pCGI->lines = pCGI->row_num * pCGI->CFI.block_high + 2 + (pCGI->row_num - 1) * pCGI->CFI.separator + \
		pCGI->extern_up_lines + pCGI->extern_down_lines + pCGI->SLI.is_top_status_line\
		+ pCGI->SLI.is_lower_status_line + pCGI->draw_frame_with_col_no;
	pCGI->cols = pCGI->col_num * pCGI->CFI.block_width + 2 + 2 * (pCGI->col_num - 1) * pCGI->CFI.separator + \
		pCGI->extern_left_cols + pCGI->extern_right_cols + 2 * pCGI->draw_frame_with_row_no;
	cct_setconsoleborder(pCGI->cols, pCGI->lines);

	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ������Ƿ���ʾ�б�
  ���������CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
			const bool on_off					��true - ��ʾ flase - ����ʾ��ȱʡfalse��
  �� �� ֵ��
  ˵    ����1���б�Լ��Ϊ����0��ʼ�������У�����0-99������99ͳһΪ**��ʵ��Ӧ�ò����ܣ�
			2���Ƿ���ʾ�б�ı仯�ᵼ��CONSOLE_GRAPHICS_INFO�ṹ����������Աֵ�ı仯��Ҫ����
***************************************************************************/
int gmw_set_colno_switch(CONSOLE_GRAPHICS_INFO* const pCGI, const bool on_off)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;
	pCGI->draw_frame_with_col_no = on_off;
	pCGI->SLI.top_start_y = pCGI->extern_up_lines;
	pCGI->SLI.lower_start_y = pCGI->extern_up_lines + pCGI->draw_frame_with_col_no + pCGI->SLI.is_top_status_line\
		+ pCGI->row_num * pCGI->CFI.block_high + 2 + (pCGI->row_num - 1) * pCGI->CFI.separator;
	pCGI->start_x = pCGI->extern_left_cols + 2 * pCGI->draw_frame_with_row_no;
	pCGI->start_y = pCGI->extern_up_lines + pCGI->draw_frame_with_col_no + pCGI->SLI.is_top_status_line;
	pCGI->lines = pCGI->row_num * pCGI->CFI.block_high + 2 + (pCGI->row_num - 1) * pCGI->CFI.separator + \
		pCGI->extern_up_lines + pCGI->extern_down_lines + pCGI->SLI.is_top_status_line\
		+ pCGI->SLI.is_lower_status_line + pCGI->draw_frame_with_col_no;
	pCGI->cols = pCGI->col_num * pCGI->CFI.block_width + 2 + 2 * (pCGI->col_num - 1) * pCGI->CFI.separator + \
		pCGI->extern_left_cols + pCGI->extern_right_cols + 2 * pCGI->draw_frame_with_row_no;
	cct_setconsoleborder(pCGI->cols, pCGI->lines);

	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���ӡ CONSOLE_GRAPHICS_INFO �ṹ���еĸ���Աֵ
  ���������
  �� �� ֵ��
  ˵    ����1�����������ã���ӡ��ʽ�Զ���
			2������������������δ���ù������Բ�ʵ��
***************************************************************************/
int gmw_print(const CONSOLE_GRAPHICS_INFO* const pCGI)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;

	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ��� CONSOLE_GRAPHICS_INFO �ṹ����ȱʡֵ���г�ʼ��
  ���������CONSOLE_GRAPHICS_INFO *const pCGI������ṹָ��
		   const int row					����Ϸ����ɫ��������ȱʡ10��
		   const int col					����Ϸ����ɫ��������ȱʡ10��
		   const int bgcolor				���������ڱ���ɫ��ȱʡ COLOR_BLACK��
		   const int fgcolor				���������ڱ���ɫ��ȱʡ COLOR_WHITE��
  �� �� ֵ��
  ˵    �������ڱ�����/ǰ���ף�����16*8�����������޶������У�����״̬�����У����к�/�б꣬�������Ϊ˫�ߣ�ɫ����2/�߶�1/��С�߿���ɫ��
***************************************************************************/
int gmw_init(CONSOLE_GRAPHICS_INFO* const pCGI, const int row, const int col, const int bgcolor, const int fgcolor)
{
	/* �����ñ�� */
	pCGI->inited = CGI_INITED;
	if (!row && !col) {
		pCGI->row_num = 10;
		pCGI->col_num = 10;
	}
	else {
		pCGI->row_num = row;
		pCGI->col_num = col;
	}
	pCGI->CFI.separator = 1;
	pCGI->CFI.block_width = 2;
	pCGI->CFI.block_high = 1;
	pCGI->CBI.block_border = 0;
	if (!(bgcolor || fgcolor)) {
		pCGI->area_bgcolor = 0;
		pCGI->area_fgcolor = 15;
	}
	else {
		pCGI->area_bgcolor = bgcolor;
		pCGI->area_fgcolor = fgcolor;
	}
	strcpy(pCGI->CFT.font_type, "Terminal");
	pCGI->CFT.font_size_width = 8;
	pCGI->CFT.font_size_high = 16;
	pCGI->delay_of_draw_frame = 0;
	pCGI->delay_of_draw_block = 0;
	pCGI->delay_of_block_moved = 3;
	pCGI->extern_up_lines = 0;
	pCGI->extern_down_lines = 4;
	pCGI->extern_left_cols = 0;
	pCGI->extern_right_cols = 3;
	pCGI->SLI.is_top_status_line = 1;
	pCGI->SLI.is_lower_status_line = 1;
	gmw_set_frame_color(pCGI, 0, 7);
	pCGI->draw_frame_with_col_no = 0;
	pCGI->draw_frame_with_row_no = 0;
	pCGI->SLI.top_normal_bgcolor = pCGI->area_bgcolor;
	pCGI->SLI.top_normal_fgcolor = pCGI->area_fgcolor;
	pCGI->SLI.lower_normal_bgcolor = pCGI->area_bgcolor;
	pCGI->SLI.lower_normal_fgcolor = pCGI->area_fgcolor;
	pCGI->SLI.top_catchy_bgcolor = pCGI->area_bgcolor;
	pCGI->SLI.top_catchy_fgcolor = 14;
	pCGI->SLI.lower_catchy_bgcolor = pCGI->area_bgcolor;
	pCGI->SLI.lower_catchy_fgcolor = 14;
	pCGI->SLI.top_start_x = 0;
	pCGI->SLI.top_start_y = pCGI->extern_up_lines;
	pCGI->SLI.lower_start_x = 0;
	pCGI->SLI.lower_start_y = pCGI->extern_up_lines + pCGI->draw_frame_with_col_no + pCGI->SLI.is_top_status_line\
		+ pCGI->row_num * pCGI->CFI.block_high + 2 + (pCGI->row_num - 1) * pCGI->CFI.separator;
	gmw_set_frame_default_linetype(pCGI, 1);
	pCGI->start_x = pCGI->extern_left_cols + 2*pCGI->draw_frame_with_row_no;
	pCGI->start_y = pCGI->extern_up_lines + 2*pCGI->draw_frame_with_col_no + pCGI->SLI.is_top_status_line;
	pCGI->lines = pCGI->row_num * pCGI->CFI.block_high + 2 + (pCGI->row_num - 1) * pCGI->CFI.separator+ \
		pCGI->extern_up_lines + pCGI->extern_down_lines + pCGI->SLI.is_top_status_line\
		+ pCGI->SLI.is_lower_status_line + pCGI->draw_frame_with_col_no;
	pCGI->cols = pCGI->col_num * pCGI->CFI.block_width + 2 + 2 *(pCGI->col_num - 1) * pCGI->CFI.separator + \
		pCGI->extern_left_cols + pCGI->extern_right_cols + 2 * pCGI->draw_frame_with_row_no;
	cct_setconsoleborder(pCGI->cols, pCGI->lines);
	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�������Ϸ���
  ���������const CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
  �� �� ֵ��
  ˵    ��������ɲο�demo��Ч��
***************************************************************************/
int gmw_draw_frame(const CONSOLE_GRAPHICS_INFO* const pCGI)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;
	if (pCGI->draw_frame_with_col_no) {
		for (int i = 0;i < pCGI->col_num;i++) {
			if (gmw_inner_getNumLen(i) > pCGI->CFI.block_width + 2*pCGI->CFI.separator)
				cct_showch(pCGI->start_x + pCGI->CFI.block_width / 2 + i * (2 * pCGI->CFI.separator + pCGI->CFI.block_width), pCGI->start_y - 1, '*', pCGI->CFI.bgcolor, pCGI->CFI.fgcolor, pCGI->CFI.block_width + 2 * pCGI->CFI.separator);
			else 
				cct_showint(pCGI->start_x + 1 + i * (2* pCGI->CFI.separator + pCGI->CFI.block_width)+(1+pCGI->CFI.block_width + 2 * pCGI->CFI.separator- gmw_inner_getNumLen(i))/2, pCGI->start_y - 1, i, pCGI->area_bgcolor, pCGI->area_fgcolor);
			}
	}
	//��һ��
	cct_showstr(pCGI->start_x, pCGI->start_y, pCGI->CFI.top_left, pCGI->CFI.bgcolor, pCGI->CFI.fgcolor);
	Sleep(pCGI->delay_of_draw_frame);
	if (pCGI->CFI.separator) {
		int j;
		for (j = 0;j < pCGI->col_num - 1;j++) {
			cct_showstr(pCGI->start_x + 2 + (2* pCGI->CFI.separator + pCGI->CFI.block_width) * j, pCGI->start_y, pCGI->CFI.h_normal, pCGI->CFI.bgcolor, pCGI->CFI.fgcolor, pCGI->CFI.block_width/2);
			Sleep(pCGI->delay_of_draw_frame);
			cct_showstr(pCGI->start_x + (2* pCGI->CFI.separator + pCGI->CFI.block_width) * (j+1), pCGI->start_y, pCGI->CFI.h_top_separator, pCGI->CFI.bgcolor, pCGI->CFI.fgcolor);
		}
		cct_showstr(pCGI->start_x + 2 + (2* pCGI->CFI.separator + pCGI->CFI.block_width) * j, pCGI->start_y, pCGI->CFI.h_normal, pCGI->CFI.bgcolor, pCGI->CFI.fgcolor, pCGI->CFI.block_width / 2);
		Sleep(pCGI->delay_of_draw_frame);
		cct_showstr(pCGI->start_x + (2* pCGI->CFI.separator + pCGI->CFI.block_width) * (j + 1), pCGI->start_y, pCGI->CFI.top_right, pCGI->CFI.bgcolor, pCGI->CFI.fgcolor);
	}
	else {
		cct_showstr(pCGI->start_x + 2, pCGI->start_y, pCGI->CFI.h_normal, pCGI->CFI.bgcolor, pCGI->CFI.fgcolor, pCGI->col_num * pCGI->CFI.block_width / 2);
		cct_showstr(pCGI->start_x + pCGI->CFI.block_width * pCGI->col_num + 2, pCGI->start_y, pCGI->CFI.top_right, pCGI->CFI.bgcolor, pCGI->CFI.fgcolor);
	}
	//�м�
	for (int i = 0;i < pCGI->row_num;i++) {
		if (pCGI->draw_frame_with_row_no) {
			if ('a' + i + 'A' - 'Z' - 1> 'z')
				cct_showch(pCGI->start_x - 2, pCGI->start_y + 1 + pCGI->CFI.block_high / 2 + i * (pCGI->CFI.separator + pCGI->CFI.block_high), '*', pCGI->area_bgcolor, pCGI->area_fgcolor);
			else if ('A'+i<='Z')
				cct_showch(pCGI->start_x - 2, pCGI->start_y + 1+pCGI->CFI.block_high / 2 + i * (pCGI->CFI.separator + pCGI->CFI.block_high), 'A' + i, pCGI->area_bgcolor, pCGI->area_fgcolor);
			else
				cct_showch(pCGI->start_x - 2, pCGI->start_y + 1 + pCGI->CFI.block_high / 2 + i * (pCGI->CFI.separator + pCGI->CFI.block_high), 'a' + i + 'A' - 'Z' - 1, pCGI->area_bgcolor, pCGI->area_fgcolor);
		}
		if (pCGI->CFI.separator && i != pCGI->row_num - 1) {
			Sleep(pCGI->delay_of_draw_frame);
			cct_showstr(pCGI->start_x, pCGI->start_y + (pCGI->CFI.separator + pCGI->CFI.block_high) * (i+1), pCGI->CFI.v_left_separator, pCGI->CFI.bgcolor, pCGI->CFI.fgcolor);
		}
		for (int j = 0;j < pCGI->col_num;j++) {
			Sleep(pCGI->delay_of_draw_frame);
			if (pCGI->CFI.separator) {
				cct_showstr(pCGI->start_x + (2* pCGI->CFI.separator + pCGI->CFI.block_width) * j+2, pCGI->start_y + (pCGI->CFI.separator + pCGI->CFI.block_high) * (i+1), pCGI->CFI.h_normal, pCGI->CFI.bgcolor, pCGI->CFI.fgcolor, pCGI->CFI.block_width / 2);
				for (int k = 0;k < pCGI->CFI.block_high;k++) {
					Sleep(pCGI->delay_of_draw_frame);
					cct_showstr(pCGI->start_x + (2* pCGI->CFI.separator + pCGI->CFI.block_width) * j, pCGI->start_y + (pCGI->CFI.separator + pCGI->CFI.block_high) * i + 1 + k, pCGI->CFI.v_normal, pCGI->CFI.bgcolor, pCGI->CFI.fgcolor);
				}
				if (i != pCGI->row_num - 1 && j != pCGI->col_num - 1) {
					Sleep(pCGI->delay_of_draw_frame);
					cct_showstr(pCGI->start_x + (2 + pCGI->CFI.block_width) * (j + 1), pCGI->start_y + (1 + pCGI->CFI.block_high) * (i + 1), pCGI->CFI.mid_separator, pCGI->CFI.bgcolor, pCGI->CFI.fgcolor);
				}
			}
			else {
				if (j == 0 || j == pCGI->col_num - 1) {
					for (int k = 0;k < pCGI->CFI.block_high;k++) {
						cct_showstr(pCGI->start_x + pCGI->CFI.block_width * (j + 1) * !!j + 2*!!j, pCGI->start_y + pCGI->CFI.block_high * i + 1 + k, pCGI->CFI.v_normal, pCGI->CFI.bgcolor, pCGI->CFI.fgcolor);
					}
				}
			}
		}
		if (pCGI->CFI.separator && i != pCGI->row_num - 1) {
			for (int k = 0;k < pCGI->CFI.block_high;k++) {
				cct_showstr(pCGI->start_x + 2 + pCGI->CFI.block_width * pCGI->col_num + 2 * (pCGI->col_num - 1) * pCGI->CFI.separator, pCGI->start_y + (pCGI->CFI.separator + pCGI->CFI.block_high) * i + 1 + k, pCGI->CFI.v_normal, pCGI->CFI.bgcolor, pCGI->CFI.fgcolor);
			}
			cct_showstr(pCGI->start_x + 2 + pCGI->CFI.block_width * pCGI->col_num + 2 * (pCGI->col_num - 1) * pCGI->CFI.separator, pCGI->start_y + (pCGI->CFI.separator + pCGI->CFI.block_high) * i + 1 + pCGI->CFI.block_high, pCGI->CFI.v_right_separator, pCGI->CFI.bgcolor, pCGI->CFI.fgcolor);
		}
	}
	//���һ��
	cct_showstr(pCGI->start_x, pCGI->start_y + 1 + pCGI->row_num*pCGI->CFI.block_high + (pCGI->row_num - 1) * pCGI->CFI.separator, pCGI->CFI.lower_left, pCGI->CFI.bgcolor, pCGI->CFI.fgcolor);
	if (pCGI->CFI.separator) {
		for (int j = 0;j < pCGI->col_num;j++) {
			cct_showstr(pCGI->start_x + 2 + (2* pCGI->CFI.separator + pCGI->CFI.block_width) * j, pCGI->start_y + 1 + pCGI->row_num * pCGI->CFI.block_high + (pCGI->row_num - 1) * pCGI->CFI.separator, pCGI->CFI.h_normal, pCGI->CFI.bgcolor, pCGI->CFI.fgcolor);
			cct_showstr(pCGI->start_x + (2* pCGI->CFI.separator + pCGI->CFI.block_width) * (j + 1), pCGI->start_y + 1 + pCGI->row_num * pCGI->CFI.block_high + (pCGI->row_num - 1) * pCGI->CFI.separator, pCGI->CFI.h_lower_separator, pCGI->CFI.bgcolor, pCGI->CFI.fgcolor);
		}
		cct_showstr(pCGI->start_x + pCGI->CFI.block_width * pCGI->col_num + 2 * (pCGI->col_num - 1) * pCGI->CFI.separator, pCGI->start_y + 1 + pCGI->row_num * pCGI->CFI.block_high + (pCGI->row_num - 1) * pCGI->CFI.separator, pCGI->CFI.h_normal, pCGI->CFI.bgcolor, pCGI->CFI.fgcolor);
		cct_showstr(pCGI->start_x + 2 + pCGI->CFI.block_width * pCGI->col_num + 2 * (pCGI->col_num - 1) * pCGI->CFI.separator, pCGI->start_y + 1 + pCGI->row_num * pCGI->CFI.block_high + (pCGI->row_num - 1) * pCGI->CFI.separator, pCGI->CFI.lower_right, pCGI->CFI.bgcolor, pCGI->CFI.fgcolor);
		for (int k = 0;k < pCGI->CFI.block_high;k++) {
			cct_showstr(pCGI->start_x + 2 + pCGI->CFI.block_width * pCGI->col_num + 2 * (pCGI->col_num - 1) * pCGI->CFI.separator, pCGI->start_y + (pCGI->CFI.separator + pCGI->CFI.block_high) * (pCGI->row_num-1) + 1 + k, pCGI->CFI.v_normal, pCGI->CFI.bgcolor, pCGI->CFI.fgcolor);
		}
	}
	else {
		cct_showstr(pCGI->start_x + 2, pCGI->start_y + 1 + pCGI->row_num * pCGI->CFI.block_high, pCGI->CFI.h_normal, pCGI->CFI.bgcolor, pCGI->CFI.fgcolor, pCGI->col_num * pCGI->CFI.block_width / 2);
		cct_showstr(pCGI->start_x + pCGI->CFI.block_width * pCGI->col_num + 2, pCGI->start_y + 1 + pCGI->row_num * pCGI->CFI.block_high + (pCGI->row_num - 1) * pCGI->CFI.separator, pCGI->CFI.lower_right, pCGI->CFI.bgcolor, pCGI->CFI.fgcolor);
	}
	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���״̬������ʾ��Ϣ
  ���������const CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
		   const int type							��ָ������/��״̬��
		   const char *msg						��������Ϣ
		   const char *catchy_msg					����Ҫ�ر��ע����Ϣ����������Ϣǰ��ʾ��
  �� �� ֵ��
  ˵    ����1���������޶�Ϊ����ܵĿ�ȣ����к��б�λ�ã����������ȥ
			2��������һ���ַ���ĳ���ֵ�ǰ������ᵼ�º������룬Ҫ����
***************************************************************************/
int gmw_status_line(const CONSOLE_GRAPHICS_INFO* const pCGI, const int type, const char* msg, const char* catchy_msg)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;
	if (type == 0 && pCGI->top_status_line) {
		if (catchy_msg) {
			cct_showstr(pCGI->SLI.top_start_x, pCGI->SLI.top_start_y, catchy_msg, pCGI->SLI.top_catchy_bgcolor, pCGI->SLI.top_catchy_fgcolor);
			cct_showstr(pCGI->SLI.top_start_x + !(!int(catchy_msg)) * strlen(catchy_msg), pCGI->SLI.top_start_y, msg, pCGI->SLI.top_normal_bgcolor, pCGI->SLI.top_normal_fgcolor);
		}
		else
			cct_showstr(pCGI->SLI.top_start_x, pCGI->SLI.top_start_y, msg, pCGI->SLI.top_normal_bgcolor, pCGI->SLI.top_normal_fgcolor);

	}
	else if (type == 1 && pCGI->lower_status_line) {
		if (catchy_msg) {
			cct_showstr(pCGI->SLI.lower_start_x, pCGI->SLI.lower_start_y, catchy_msg, pCGI->SLI.lower_catchy_bgcolor, pCGI->SLI.lower_catchy_fgcolor);
			cct_showstr(pCGI->SLI.lower_start_x + !(!int(catchy_msg)) * strlen(catchy_msg), pCGI->SLI.lower_start_y, msg, pCGI->SLI.lower_normal_bgcolor, pCGI->SLI.lower_normal_fgcolor);
		}
		else
			cct_showstr(pCGI->SLI.lower_start_x, pCGI->SLI.lower_start_y, msg, pCGI->SLI.lower_normal_bgcolor, pCGI->SLI.lower_normal_fgcolor);

	}
	else {
		return -1;
	}
	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���ʾĳһ��ɫ��(����Ϊ�ַ���������Ϊrow/col)
  ���������const CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
		   const int row_no						���кţ���0��ʼ����Ϊ��֤��ȷ�ԣ����򲻼�飩
		   const int col_no						���кţ���0��ʼ����Ϊ��֤��ȷ�ԣ����򲻼�飩
		   const int bdi_value						����Ҫ��ʾ��ֵ
		   const BLOCK_DISPLAY_INFO *const bdi		����Ÿ�ֵ��Ӧ����ʾ��Ϣ�Ľṹ������
  �� �� ֵ��
  ˵    ����1��BLOCK_DISPLAY_INFO �ĺ����ͷ�ļ����÷��ο���������
			2��bdi_valueΪ BDI_VALUE_BLANK ��ʾ�հ׿飬Ҫ���⴦��
***************************************************************************/
int gmw_draw_block(const CONSOLE_GRAPHICS_INFO* const pCGI, const int row_no, const int col_no, const int bdi_value, const BLOCK_DISPLAY_INFO* const bdi)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;
	int start_x, start_y, x, y;
	int bg, fg;
	start_x = pCGI->start_x + (2 * pCGI->CFI.separator + pCGI->CFI.block_width) * col_no + 2;
	start_y = pCGI->start_y + (pCGI->CFI.separator + pCGI->CFI.block_high) * row_no + 1;
	x = ((pCGI->start_x + (2 * pCGI->CFI.separator + pCGI->CFI.block_width) * col_no + 2) + (pCGI->start_x + (2 * pCGI->CFI.separator + pCGI->CFI.block_width) * col_no + 2 + pCGI->CFI.block_width)) / 2-1;
	y = ((pCGI->start_y + (pCGI->CFI.separator + pCGI->CFI.block_high) * row_no + 1) + (pCGI->start_y + (pCGI->CFI.separator + pCGI->CFI.block_high) * row_no + 1 + pCGI->CFI.block_high)) / 2;
	if ((bdi + bdi_value)->bgcolor == -1) 
		bg = pCGI->area_bgcolor;
	else
		bg = (bdi + bdi_value)->bgcolor;
	if ((bdi + bdi_value)->fgcolor == -1)
		fg = pCGI->area_fgcolor;
	else
		fg = (bdi + bdi_value)->fgcolor;
	//��䱳��
	if ((bdi + bdi_value)->value >= 0 && (bdi + bdi_value)->value <= 5) {
		for (int i = 0;i < pCGI->CFI.block_high;i++) {
			for (int j = 0;j < pCGI->CFI.block_width;j++) {
				Sleep(pCGI->delay_of_draw_block);
				if (pCGI->CBI.block_border) {
					if (i == 0 && j == 0)
						cct_showstr(start_x + j, start_y + i, pCGI->CBI.top_left, bg, fg);
					else if (i == 0 && j == pCGI->CFI.block_width - 2)
						cct_showstr(start_x + j, start_y + i, pCGI->CBI.top_right, bg, fg);
					else if (i == pCGI->CFI.block_high - 1 && j == pCGI->CFI.block_width - 2)
						cct_showstr(start_x + j, start_y + i, pCGI->CBI.lower_right, bg, fg);
					else if (i == pCGI->CFI.block_high - 1 && j == 0)
						cct_showstr(start_x + j, start_y + i, pCGI->CBI.lower_left, bg, fg);
					else if (i == 0 && j == 2 || i == pCGI->CFI.block_high - 1 && j == 2)
						cct_showstr(start_x + j, start_y + i, pCGI->CBI.h_normal, bg, fg);
					else if (i == 1 && j == 0 || i == 1 && j == pCGI->CFI.block_width - 2)
						cct_showstr(start_x + j, start_y + i, pCGI->CBI.v_normal, bg, fg);
					else {
						cct_showch(start_x + j, start_y + i, ' ', bg, fg);
						j--;
					}
					j++;
				}
				else {
					cct_showch(start_x + j, start_y + i, ' ', bg, fg);
				}
			}
		}
	}
	//����ַ�
	switch ((bdi + bdi_value)->value) {
		case -999:
			return 0;
		default:
			Sleep(pCGI->delay_of_draw_block);
			if ((bdi + bdi_value)->content == NULL) {
				cct_showint(x, y, (bdi + bdi_value)->value, bg, fg);
			}
			else {
				cct_showstr(x, y, (bdi + bdi_value)->content, bg, fg);
			}
	}
	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ��ƶ�ĳһ��ɫ��
  ���������const CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
		   const int row_no						���кţ���0��ʼ����Ϊ��֤��ȷ�ԣ����򲻼�飩
		   const int col_no						���кţ���0��ʼ����Ϊ��֤��ȷ�ԣ����򲻼�飩
		   const int bdi_value						����Ҫ��ʾ��ֵ
		   const int blank_bdi_value				���ƶ����������ڶ���Ч����ʾʱ���ڱ�ʾ�հ׵�ֵ��һ��Ϊ0���˴���Ϊ�������룬�ǿ��ǵ����ܳ��ֵ����������
		   const BLOCK_DISPLAY_INFO *const bdi		�������ʾֵ/�հ�ֵ��Ӧ����ʾ��Ϣ�Ľṹ������
		   const int direction						���ƶ�����һ�����֣������cmd_gmw_tools.h
		   const int distance						���ƶ����루��1��ʼ����Ϊ��֤��ȷ�ԣ����򲻼�飩
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int gmw_move_block(const CONSOLE_GRAPHICS_INFO* const pCGI, const int row_no, const int col_no, const int bdi_value, const int blank_bdi_value, const BLOCK_DISPLAY_INFO* const bdi, const int direction, const int distance)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;

	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ������̻����
  ���������const CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
		   int &MAction							��������� CCT_MOUSE_EVENT�����ֵ��Ч��Ϊ MOUSE_ONLY_MOVED/MOUSE_LEFT_BUTTON_CLICK/MOUSE_RIGHT_BUTTON_CLICK ����֮һ
													   ������� CCT_KEYBOARD_EVENT�����ֵ��Ч
		   int &MRow								��������� CCT_MOUSE_EVENT �� MAction = MOUSE_ONLY_MOVED/MOUSE_LEFT_BUTTON_CLICK�����ֵ��Ч����ʾ���ѡ�����Ϸ������кţ���0��ʼ��
												  ���������ֵ��Ч�����������Чֵ���´��󣬲��Ǳ������Ĵ�!!!��
		   int &MCol								��������� CCT_MOUSE_EVENT �� MAction = MOUSE_ONLY_MOVED/MOUSE_LEFT_BUTTON_CLICK�����ֵ��Ч����ʾ���ѡ�����Ϸ������кţ���0��ʼ��
												  ���������ֵ��Ч�����������Чֵ���´��󣬲��Ǳ������Ĵ�!!!��
		   int &KeyCode1							��������� CCT_KEYBOARD_EVENT�����ֵ��Ч��Ϊ�����ļ��루���˫���룬��Ϊ��һ����
												  ���������ֵ��Ч�����������Чֵ���´��󣬲��Ǳ������Ĵ�!!!��
		   int &KeyCode2							��������� CCT_KEYBOARD_EVENT�����ֵ��Ч��Ϊ�����ļ��루���˫���룬��Ϊ�ڶ���������ǵ����룬��Ϊ0��
												  ���������ֵ��Ч�����������Чֵ���´��󣬲��Ǳ������Ĵ�!!!��
		   const bool update_lower_status_line		������ƶ�ʱ���Ƿ�Ҫ�ڱ���������ʾ"[��ǰ���] *��*��/λ�÷Ƿ�"����Ϣ��true=��ʾ��false=����ʾ��ȱʡΪtrue��
  �� �� ֵ����������Լ��
		   1�����������ƶ����õ���MRow/MCol�봫�����ͬ(���ָ��΢С���ƶ�)���򲻷��أ�������
							  �õ����зǷ�λ�ã��򲻷��أ����� update_lower_status_line ����������״̬����ʾ"[��ǰ���] λ�÷Ƿ�"
							  �õ���MRow/MCol�봫��Ĳ�ͬ(��������һ���仯)������ update_lower_status_line ����������״̬����ʾ"[��ǰ���] *��*��"���ٷ���MOUSE_ONLY_MOVED����Щ��Ϸ���غ�Ҫ����ɫ��Ĳ�ͬ��ɫ��ʾ��
		   2������ǰ������������ҵ�ǰ���ָ��ͣ��������Ϸ�����*��*���ϣ��򷵻� CCT_MOUSE_EVENT ��MAction Ϊ MOUSE_LEFT_BUTTON_CLICK, MRow Ϊ�кţ�MCol Ϊ�б�
								  �ҵ�ǰ���ָ��ͣ���ڷǷ����򣨷���Ϸ������Ϸ�����еķָ��ߣ����򲻷��أ����� update_lower_status_line ����������״̬����ʾ"[��ǰ���] λ�÷Ƿ�"
		   3������ǰ�������Ҽ������ж����ָ��ͣ�������Ƿ�Ϸ���ֱ�ӷ��� CCT_MOUSE_EVENT ��MAction Ϊ MOUSE_RIGHT_BUTTON_CLICK, MRow��MColȡ��ǰֵ����Ϊ�������ǵ��Ҽ������Ҫ���꣩
		   4��������¼����ϵ�ĳ������˫���밴��������ֱ�ӷ��� CCT_KEYBOARD_EVENT��KeyCode1/KeyCode2��Ϊ��Ӧ�ļ���ֵ
 ˵    ����ͨ������ cmd_console_tools.cpp �е� read_keyboard_and_mouse ����ʵ��
***************************************************************************/
int gmw_read_keyboard_and_mouse(const CONSOLE_GRAPHICS_INFO* const pCGI, int& MAction, int& MRow, int& MCol, int& KeyCode1, int& KeyCode2, const bool update_lower_status_line)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;

	return 0; //�˾�ɸ�����Ҫ�޸�
}
