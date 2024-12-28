/* 2351044 大数据 崔艺洋 */
#include "hw_check.h"

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
 ***************************************************************************/
int main(int argc, char** argv)
{
	args_analyse_tools args[] = {
		args_analyse_tools("--help",     ST_EXTARGS_TYPE::boolean,            0, false),
		args_analyse_tools("--debug",    ST_EXTARGS_TYPE::boolean,            0, false),
		args_analyse_tools("--action",   ST_EXTARGS_TYPE::str_with_set_error, 1, -1, Action_Name),	//参数-1无意义，表示无默认，必须指定
		args_analyse_tools("--cno",      ST_EXTARGS_TYPE::str,                1, string("")),
		args_analyse_tools("--stu",      ST_EXTARGS_TYPE::str,                1, string("")),
		args_analyse_tools("--file",     ST_EXTARGS_TYPE::str,                1, string("")),
		args_analyse_tools("--chapter",  ST_EXTARGS_TYPE::int_with_error,     1, -1, -1, 99), //参数-1表示不进行章节选择
		args_analyse_tools("--week",     ST_EXTARGS_TYPE::int_with_error,     1, -1, -1, 20), //参数-1表示不进行周次选择
		args_analyse_tools("--display",  ST_EXTARGS_TYPE::str,                1, string("11111")),
		args_analyse_tools("--cfgfile",  ST_EXTARGS_TYPE::str,                1, string("hw_check.conf")),
		args_analyse_tools()  //最后一个，用于结束
	};

	/* 不带任何参数做特殊处理，打印提示信息后结束 */
	if (argc == 1) {
		usage(argv[0]);
		return -1;
	}

	int need_fixed_args = 0;	//需要固定参数
	int cur_argc;

	/* 带--help参数做特殊处理，打印提示信息后结束 */
	if ((cur_argc = args_analyse_process(argc, argv, args, need_fixed_args)) < 0)
	{
		//错误信息在函数中已打印
		return -1;
	}

	///* 可变参数分析完成后，看是否还有固定参数，以及固定参数的数量是否符合要求 */
	//if (need_fixed_args) {
	//	if (cur_argc == argc) {  //说明后面没有跟需要的固定参数
	//		cout << "需要指定IP地址，但未给出" << endl;
	//		return -1;
	//	}
	//	if (argc - cur_argc != 2) {
	//		cout << "除可变参数外，必须给出转换的源文件名和目标文件名两个固定参数，但现在只给出了" << argc - cur_argc << "个固定参数" << endl;
	//		return -1;
	//	}
	//}

	check(argc, argv, args);

	return 0;
}

