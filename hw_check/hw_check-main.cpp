/* 2351044 ������ ������ */
#include "hw_check.h"

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
 ***************************************************************************/
int main(int argc, char** argv)
{
	args_analyse_tools args[] = {
		args_analyse_tools("--help",     ST_EXTARGS_TYPE::boolean,            0, false),
		args_analyse_tools("--debug",    ST_EXTARGS_TYPE::boolean,            0, false),
		args_analyse_tools("--action",   ST_EXTARGS_TYPE::str_with_set_error, 1, -1, Action_Name),	//����-1�����壬��ʾ��Ĭ�ϣ�����ָ��
		args_analyse_tools("--cno",      ST_EXTARGS_TYPE::str,                1, string("")),
		args_analyse_tools("--stu",      ST_EXTARGS_TYPE::str,                1, string("")),
		args_analyse_tools("--file",     ST_EXTARGS_TYPE::str,                1, string("")),
		args_analyse_tools("--chapter",  ST_EXTARGS_TYPE::int_with_error,     1, -1, -1, 99), //����-1��ʾ�������½�ѡ��
		args_analyse_tools("--week",     ST_EXTARGS_TYPE::int_with_error,     1, -1, -1, 20), //����-1��ʾ�������ܴ�ѡ��
		args_analyse_tools("--display",  ST_EXTARGS_TYPE::str,                1, string("11111")),
		args_analyse_tools("--cfgfile",  ST_EXTARGS_TYPE::str,                1, string("hw_check.conf")),
		args_analyse_tools()  //���һ�������ڽ���
	};

	/* �����κβ��������⴦����ӡ��ʾ��Ϣ����� */
	if (argc == 1) {
		usage(argv[0]);
		return -1;
	}

	int need_fixed_args = 0;	//��Ҫ�̶�����
	int cur_argc;

	/* ��--help���������⴦����ӡ��ʾ��Ϣ����� */
	if ((cur_argc = args_analyse_process(argc, argv, args, need_fixed_args)) < 0)
	{
		//������Ϣ�ں������Ѵ�ӡ
		return -1;
	}

	///* �ɱ����������ɺ󣬿��Ƿ��й̶��������Լ��̶������������Ƿ����Ҫ�� */
	//if (need_fixed_args) {
	//	if (cur_argc == argc) {  //˵������û�и���Ҫ�Ĺ̶�����
	//		cout << "��Ҫָ��IP��ַ����δ����" << endl;
	//		return -1;
	//	}
	//	if (argc - cur_argc != 2) {
	//		cout << "���ɱ�����⣬�������ת����Դ�ļ�����Ŀ���ļ��������̶�������������ֻ������" << argc - cur_argc << "���̶�����" << endl;
	//		return -1;
	//	}
	//}

	check(argc, argv, args);

	return 0;
}

