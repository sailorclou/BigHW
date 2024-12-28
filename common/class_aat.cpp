/* 2351044 大数据 崔艺洋 */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include "../include/class_aat.h"
//如有必要，可以加入其它头文件
#include <cstring>
//#include <sstream>
#include <algorithm>
using namespace std;

#if !ENABLE_LIB_COMMON_TOOLS //不使用lib才有效

/* ---------------------------------------------------------------
	 允许加入其它需要static函数（内部工具用）
   ---------------------------------------------------------------- */
static bool isInt(const string& str) 
{
	try {
		int value = stoi(str);  // 捕获返回值以避免警告
		(void)value;                 // 明确表明不会使用该值
		return true;
	}
	catch (invalid_argument&) {
		return false;  // 如果无法转换为数字，抛出异常
	}
	catch (out_of_range&) {
		return false;  // 如果超出范围
	}
}
static bool isDouble(const string& str) 
{
	try {
		double value = stod(str);  // 捕获返回值以避免警告
		(void)value;                 // 明确表明不会使用该值
		return true;
	}
	catch (invalid_argument&) {
		return false;  // 如果无法转换为数字，抛出异常
	}
	catch (out_of_range&) {
		return false;  // 如果超出范围
	}
}
static bool is_valid_ip(const string& str_ipaddr) 
{
	int bytes[4];
	char dot;
	istringstream iss(str_ipaddr);

	// 检查格式是否为 "byte1.byte2.byte3.byte4"
	if (!(iss >> bytes[0] >> dot >> bytes[1] >> dot >> bytes[2] >> dot >> bytes[3])) {
		return false;
	}

	// 检查每个字节是否在 [0, 255] 范围内
	for (int i = 0; i < 4; ++i) {
		if (bytes[i] < 0 || bytes[i] > 255) {
			return false;
		}
	}

	return true;
}
static const string ip_to_str(const u_int &int_ipaddr_default)
{
	ostringstream ip;

	// 提取每个字节，并拼接成 "byte1.byte2.byte3.byte4" 格式
	ip << ((int_ipaddr_default >> 24) & 0xFF) << "."
		<< ((int_ipaddr_default >> 16) & 0xFF) << "."
		<< ((int_ipaddr_default >> 8) & 0xFF) << "."
		<< (int_ipaddr_default & 0xFF);

	return ip.str();
}
static const u_int get_int_ipaddr(const string& str_ipaddr)
{
	u_int ip = 0;
	int bytes[4];
	char dot;

	istringstream iss(str_ipaddr);
	iss >> bytes[0] >> dot >> bytes[1] >> dot >> bytes[2] >> dot >> bytes[3];
	ip = (bytes[0] << 24) | (bytes[1] << 16) | (bytes[2] << 8) | bytes[3];

	return ip;
}
/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：null
 ***************************************************************************/
args_analyse_tools::args_analyse_tools() : args_name(""), extargs_type(ST_EXTARGS_TYPE::null), extargs_num(0), args_existed(0),
					args_exists(0), extargs_int_set(nullptr), extargs_string_set(nullptr), extargs_double_set(nullptr)
{
	memset(pad, 0, sizeof(pad));
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：boolean
 ***************************************************************************/
args_analyse_tools::args_analyse_tools(const char* name, const ST_EXTARGS_TYPE type, const int ext_num, const bool def) : 
					args_name(name), extargs_type(type), extargs_num(ext_num), extargs_bool_default(def), args_existed(0), args_exists(0),
	extargs_int_set(nullptr), extargs_string_set(nullptr), extargs_double_set(nullptr)
{
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：int_with_default、int_with_error
 ***************************************************************************/
args_analyse_tools::args_analyse_tools(const char* name, const ST_EXTARGS_TYPE type, const int ext_num, const int def, const int _min, const int _max) :
					args_name(name), extargs_type(type), extargs_num(ext_num), extargs_int_default(def), extargs_int_value(def), extargs_int_min(_min), extargs_int_max(_max), args_existed(0), args_exists(0),
	extargs_int_set(nullptr), extargs_string_set(nullptr), extargs_double_set(nullptr)
{
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：int_with_set_default、int_with_set_error
 ***************************************************************************/
args_analyse_tools::args_analyse_tools(const char* name, const enum ST_EXTARGS_TYPE type, const int ext_num, const int def_of_set_pos, const int* const set) :
					args_name(name), extargs_type(type), extargs_num(ext_num), args_existed(0), args_exists(0), 
	extargs_int_set(nullptr), extargs_string_set(nullptr), extargs_double_set(nullptr)
{
	if (set) {
		int i = 0;
		for (i = 0;;++i) {
			if (set[i] == INVALID_INT_VALUE_OF_SET)
				break;
		}
		// 分配内存
		extargs_int_set = new int[++i];

		// 复制数据
		for (i = 0;;++i) {
			extargs_int_set[i] = set[i];
			if (set[i] == INVALID_INT_VALUE_OF_SET)
				break;
		}

		// 如果 def_of_set_pos 有效，则初始化默认值
		if (def_of_set_pos >= 0 && def_of_set_pos <= i) {
			extargs_int_default = set[def_of_set_pos];
			extargs_int_value = set[def_of_set_pos];
		}
	}
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：str、ipaddr_with_default、ipaddr_with_erro
 ***************************************************************************/
args_analyse_tools::args_analyse_tools(const char* name, const ST_EXTARGS_TYPE type, const int ext_num, const string def) : 
					args_name(name), extargs_type(type), extargs_num(ext_num), args_existed(0), args_exists(0),
	extargs_int_set(nullptr), extargs_string_set(nullptr), extargs_double_set(nullptr)
{
	if (type == ST_EXTARGS_TYPE::str || type == ST_EXTARGS_TYPE::str_with_set_default || type == ST_EXTARGS_TYPE::str_with_set_error) {
		extargs_string_default = def;
		extargs_string_value = def;
	}
	else if (def == "") {
		extargs_ipaddr_default = 0;
		extargs_ipaddr_value = 0;
	}
	else {
		extargs_ipaddr_default = get_int_ipaddr(def);
		extargs_ipaddr_value = get_int_ipaddr(def);
	}
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：str_with_set_default、str_with_set_error
 ***************************************************************************/
args_analyse_tools::args_analyse_tools(const char* name, const ST_EXTARGS_TYPE type, const int ext_num, const int def_of_set_pos, const string* const set):
					args_name(name), extargs_type(type), extargs_num(ext_num), args_existed(0), args_exists(0), 
	extargs_int_set(nullptr), extargs_string_set(nullptr), extargs_double_set(nullptr)
{
	if (set) {
		
		int i = 0;
		for (i = 0;;++i) {
			if (set[i] == "")
				break;
		}
		// 分配内存
		extargs_string_set = new string[++i];

		// 复制数据
		for (i = 0;;++i) {
			extargs_string_set[i] = set[i];
			if (set[i] == "")
				break;
		}

		// 如果 def_of_set_pos 有效，则初始化默认值
		if (def_of_set_pos >= 0 && def_of_set_pos <= i) {
			extargs_string_default = set[def_of_set_pos];
			extargs_string_value = set[def_of_set_pos];
		}
	}
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：double_with_default、double_with_error
 ***************************************************************************/
args_analyse_tools::args_analyse_tools(const char* name, const ST_EXTARGS_TYPE type, const int ext_num, const double	def, const double _min, const double _max) :
					args_name(name), extargs_type(type), extargs_num(ext_num), extargs_double_default(def), extargs_double_value(def), extargs_double_min(_min), extargs_double_max(_max), args_existed(0), args_exists(0),
	extargs_int_set(nullptr), extargs_string_set(nullptr), extargs_double_set(nullptr)
{
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：double_with_set_default、double_with_set_error
 ***************************************************************************/
args_analyse_tools::args_analyse_tools(const char* name, const enum ST_EXTARGS_TYPE type, const int ext_num, const int def_of_set_pos, const double* const set) :
					args_name(name), extargs_type(type), extargs_num(ext_num), args_existed(0), args_exists(0),
	extargs_int_set(nullptr), extargs_string_set(nullptr), extargs_double_set(nullptr)
{
	if (set) {
		int i = 0;
		for (i = 0;;++i) {
			if (set[i] == INVALID_DOUBLE_VALUE_OF_SET)
				break;
		}
		// 分配内存
		extargs_double_set = new double[++i];

		// 复制数据
		for (i = 0;;++i) {
			extargs_double_set[i] = set[i];
			if (set[i] == INVALID_DOUBLE_VALUE_OF_SET)
				break;
		}

		// 如果 def_of_set_pos 有效，则初始化默认值
		if (def_of_set_pos >= 0 && def_of_set_pos <= i) {
			extargs_double_default = set[def_of_set_pos];
			extargs_double_value = set[def_of_set_pos];
		}
	}
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
 ***************************************************************************/
args_analyse_tools::~args_analyse_tools()
{
	// 释放整数集合
	if (extargs_int_set) {
		delete[] extargs_int_set;
		extargs_int_set = nullptr;
	}

	// 释放字符串集合
	if (extargs_string_set) {
		delete[] extargs_string_set;
		extargs_string_set = nullptr;
	}

	// 释放双精度浮点集合
	if (extargs_double_set) {
		delete[] extargs_double_set;
		extargs_double_set = nullptr;
	}
}

/* ---------------------------------------------------------------
	 允许AAT中自定义成员函数的实现（private）
   ---------------------------------------------------------------- */

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：已实现，不要动
 ***************************************************************************/
const string args_analyse_tools::get_name() const
{
	return this->args_name;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：加!!后，只能是0/1
			已实现，不要动
 ***************************************************************************/
const int args_analyse_tools::existed() const
{
	return !!this->args_existed;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：已实现，不要动
 ***************************************************************************/
const int args_analyse_tools::get_int() const
{
	return this->extargs_int_value;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：已实现，不要动
 ***************************************************************************/
const double args_analyse_tools::get_double() const
{
	return this->extargs_double_value;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：已实现，不要动
 ***************************************************************************/
const string args_analyse_tools::get_string() const
{
	return this->extargs_string_value;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：已实现，不要动
 ***************************************************************************/
const unsigned int args_analyse_tools::get_ipaddr() const
{
	return this->extargs_ipaddr_value;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：将 extargs_ipaddr_value 的值从 0x7f000001 转为 "127.0.0.1"
 ***************************************************************************/
const string args_analyse_tools::get_str_ipaddr() const
{
	ostringstream ip;
	ip << ((extargs_ipaddr_value >> 24) & 0xFF) << "."
		<< ((extargs_ipaddr_value >> 16) & 0xFF) << "."
		<< ((extargs_ipaddr_value >> 8) & 0xFF) << "."
		<< (extargs_ipaddr_value & 0xFF);
	return ip.str(); //此句根据需要修改
}


/***************************************************************************
  函数名称：
  功    能：
  输入参数：follow_up_args：是否有后续参数
			0  ：无后续参数
			1  ：有后续参数
  返 回 值：
  说    明：友元函数
***************************************************************************/
int args_analyse_process(const int argc, const char* const *const argv, args_analyse_tools* const args, const int follow_up_args)
{
	//int cur_argc = 0;
	int i = 0;
	for (i = 1;i < argc;i++) {
		string arg = argv[i];
		bool match = false;
		for (int j = 0;args[j].get_name() != "";j++) {
			if (arg == args[j].get_name()) {
				match = true;
				if (args[j].args_exists) {
					cout << "参数[" << args[j].get_name() << "]重复." << endl;
					return -1;
				}
				switch (args[j].extargs_type) {
					case ST_EXTARGS_TYPE::boolean: {
						args[j].args_existed = true;
						args[j].args_exists = true;
					}
						break;
					case ST_EXTARGS_TYPE::int_with_default: {
						args[j].args_existed = true;
						if (i + 1 < argc && isInt(argv[i + 1])) {
							args[j].args_exists = true;
							int value = stoi(argv[++i]);
							if (value > args[j].extargs_int_max || value < args[j].extargs_int_min) {
								args[j].extargs_int_value = args[j].extargs_int_default;
							}
							else {
								args[j].extargs_int_value = value;
							}
						}
						else if (i + 1 >= argc) {
							cout << "参数[" << arg << "]的附加参数不足. (类型:int, 范围[" << args[j].extargs_int_min << ".." << args[j].extargs_int_max << "])" << endl;
							return -1;
						}
						else {
							cout << "参数[" << arg << "]的附加参数不是整数. (类型:int, 范围[" << args[j].extargs_int_min << ".." << args[j].extargs_int_max << "])" << endl;
							return -1;
						}
					}
						break;
					case ST_EXTARGS_TYPE::int_with_error: {
						args[j].args_existed = true;
						if (i + 1 < argc && isInt(argv[i + 1])) {
							int value = stoi(argv[++i]);
							if (value > args[j].extargs_int_max || value < args[j].extargs_int_min) {
								cout << "参数[" << arg << "]的附加参数值(" << value << ")非法. (类型:int, 范围[" << args[j].extargs_int_min << ".." << args[j].extargs_int_max << "])" << endl;
								return -1;
							}
							else {
								args[j].args_exists = true;
								args[j].extargs_int_value = value;
							}
						}
						else if (i + 1 >= argc) {
							cout << "参数[" << arg << "]的附加参数不足. (类型:int, 范围[" << args[j].extargs_int_min << ".." << args[j].extargs_int_max << "])" << endl;
							return -1;
						}
						else {
							cout << "参数[" << arg << "]的附加参数不是整数. (类型:int, 范围[" << args[j].extargs_int_min << ".." << args[j].extargs_int_max << "])" << endl;
							return -1;
						}
					}
						break;
					case ST_EXTARGS_TYPE::int_with_set_default: {
						args[j].args_existed = true;
						if (i + 1 < argc && isInt(argv[i + 1])) {
							args[j].args_exists = true;
							int value = stoi(argv[++i]);
							bool find = 0;
							for (int p = 0;;++p) {
								if (args[j].extargs_int_set[p] == INVALID_INT_VALUE_OF_SET)
									break;
								if (value == args[j].extargs_int_set[p]) {
									find = true;
									break;
								}
							}
							if (!find) {  //不在数组中
								args[j].extargs_int_value = args[j].extargs_int_default;
							}
							else {
								args[j].extargs_int_value = value;
							}
						}
						else if (i + 1 >= argc) {
							cout << "参数[" << arg << "]的附加参数不足. (类型:int, 可取值[";
							for (int p = 0;;++p) {
								if (args[j].extargs_int_set[p] == INVALID_INT_VALUE_OF_SET)
									break;
								cout << args[j].extargs_int_set[p];
								if (args[j].extargs_int_set[p + 1] != INVALID_INT_VALUE_OF_SET)
									cout << "/";
							}
							cout << "] 缺省:" << args[j].extargs_int_default << ")" << endl;
							return -1;
						}
						else {
							cout << "参数[" << arg << "]的附加参数不是整数. (类型:int, 可取值[";
							for (int p = 0;;++p) {
								if (args[j].extargs_int_set[p] == INVALID_INT_VALUE_OF_SET)
									break;
								cout << args[j].extargs_int_set[p];
								if (args[j].extargs_int_set[p + 1] != INVALID_INT_VALUE_OF_SET)
									cout << "/";
							}
							cout << "] 缺省:" << args[j].extargs_int_default << ")" << endl;
							return -1;
						}
					}
						break;
					case ST_EXTARGS_TYPE::int_with_set_error: {
						args[j].args_existed = true;
						if (i + 1 < argc && isInt(argv[i + 1])) {
							int value = stoi(argv[++i]);
							bool find = 0;
							for (int p = 0;;++p) {
								if (args[j].extargs_int_set[p] == INVALID_INT_VALUE_OF_SET)
									break;
								if (value == args[j].extargs_int_set[p]) {
									find = true;
									break;
								}
							}
							if (!find) {  //不在数组中
								cout << "参数[" << arg << "]的附加参数值(" << value << ")非法. (类型:int, 可取值[";
								for (int p = 0;;++p) {
									if (args[j].extargs_int_set[p] == INVALID_INT_VALUE_OF_SET)
										break;
									cout << args[j].extargs_int_set[p];
									if(args[j].extargs_int_set[p+1] != INVALID_INT_VALUE_OF_SET)
										cout << "/";
								}
								cout << "])" << endl;
								return -1;
							}
							else {
								args[j].args_exists = true;
								args[j].extargs_int_value = value;
							}
						}
						else if (i + 1 >= argc) {
							cout << "参数[" << arg << "]的附加参数不足. (类型:int, 可取值[";
							for (int p = 0;;++p) {
								if (args[j].extargs_int_set[p] == INVALID_INT_VALUE_OF_SET)
									break;
								cout << args[j].extargs_int_set[p];
								if (args[j].extargs_int_set[p + 1] != INVALID_INT_VALUE_OF_SET)
									cout << "/";
							}
							cout << "])" << endl;
							return -1;
						}
						else {
							cout << "参数[" << arg << "]的附加参数不是整数. (类型:int, 可取值[";
							for (int p = 0;;++p) {
								if (args[j].extargs_int_set[p] == INVALID_INT_VALUE_OF_SET)
									break;
								cout << args[j].extargs_int_set[p];
								if (args[j].extargs_int_set[p + 1] != INVALID_INT_VALUE_OF_SET)
									cout << "/";
							}
							cout << "]" << endl;
							return -1;
						}
					}
						break;
					case ST_EXTARGS_TYPE::double_with_default: {
						args[j].args_existed = true;
						if (i + 1 < argc && isDouble(argv[i + 1])) {
							args[j].args_exists = true;
							double value = stod(argv[++i]);
							if (value > args[j].extargs_double_max || value < args[j].extargs_double_min) {
								args[j].extargs_double_value = args[j].extargs_double_default;
							}
							else {
								args[j].extargs_double_value = value;
							}
						}
						else if (i + 1 >= argc) {
							cout << "参数[" << arg << "]的附加参数不足. (类型:double, 范围[" << args[j].extargs_double_min << ".." << args[j].extargs_double_max << "])" << endl;
							return -1;
						}
						else {
							cout << "参数[" << arg << "]的附加参数不是整数. (类型:double, 范围[" << args[j].extargs_double_min << ".." << args[j].extargs_double_max << "])" << endl;
							return -1;
						}
					}
						break;
					case ST_EXTARGS_TYPE::double_with_error: {
						args[j].args_existed = true;
						if (i + 1 < argc && isDouble(argv[i + 1])) {
							double value = stod(argv[++i]);
							if (value > args[j].extargs_double_max || value < args[j].extargs_double_min) {
								cout << "参数[" << arg << "]的附加参数值(" << value << ")非法. (类型:double, 范围[" << args[j].extargs_double_min << ".." << args[j].extargs_double_max << "])" << endl;
								return -1;
							}
							else {
								args[j].args_exists = true;
								args[j].extargs_double_value = value;
							}
						}
						else if (i + 1 >= argc) {
							cout << "参数[" << arg << "]的附加参数不足. (类型:double, 范围[" << args[j].extargs_double_min << ".." << args[j].extargs_double_max << "])" << endl;
							return -1;
						}
						else {
							cout << "参数[" << arg << "]的附加参数不是整数. (类型:double, 范围[" << args[j].extargs_double_min << ".." << args[j].extargs_double_max << "])" << endl;
							return -1;
						}
					}
						break;
					case ST_EXTARGS_TYPE::double_with_set_default: {
						args[j].args_existed = true;
						if (i + 1 < argc && isDouble(argv[i + 1])) {
							args[j].args_exists = true;
							double value = stod(argv[++i]);
							bool find = 0;
							for (int p = 0;;++p) {
								if (args[j].extargs_double_set[p] == INVALID_DOUBLE_VALUE_OF_SET)
									break;
								if (value == args[j].extargs_double_set[p]) {
									find = true;
									break;
								}
							}
							if (!find) {  //不在数组中
								args[j].extargs_double_value = args[j].extargs_double_default;
							}
							else {
								args[j].extargs_double_value = value;
							}
						}
						else if (i + 1 >= argc) {
							cout << "参数[" << arg << "]的附加参数不足. (类型:double, 可取值[";
							for (int p = 0;;++p) {
								if (args[j].extargs_double_set[p] == INVALID_DOUBLE_VALUE_OF_SET)
									break;
								cout << args[j].extargs_double_set[p];
								if (args[j].extargs_double_set[p + 1] != INVALID_DOUBLE_VALUE_OF_SET)
									cout << "/";
							}
							cout << "] 缺省:" << args[j].extargs_double_default << ")" << endl;
							return -1;
						}
						else {
							cout << "参数[" << arg << "]的附加参数不是整数. (类型:double, 可取值[";
							for (int p = 0;;++p) {
								if (args[j].extargs_double_set[p] == INVALID_DOUBLE_VALUE_OF_SET)
									break;
								cout << args[j].extargs_double_set[p];
								if (args[j].extargs_double_set[p + 1] != INVALID_DOUBLE_VALUE_OF_SET)
									cout << "/";
							}
							cout << "] 缺省:" << args[j].extargs_double_default << ")" << endl;
							return -1;
						}
					}
						break;
					case ST_EXTARGS_TYPE::double_with_set_error: {
						args[j].args_existed = true;
						if (i + 1 < argc && isDouble(argv[i + 1])) {
							double value = stod(argv[++i]);
							bool find = 0;
							for (int p = 0;;++p) {
								if (args[j].extargs_double_set[p] == INVALID_DOUBLE_VALUE_OF_SET)
									break;
								if (value == args[j].extargs_double_set[p]) {
									find = true;
									break;
								}
							}
							if (!find) {  //不在数组中
								cout << "参数[" << arg << "]的附加参数值(" << value << ")非法. (类型:double, 可取值[";
								for (int p = 0;;++p) {
									if (args[j].extargs_double_set[p] == INVALID_DOUBLE_VALUE_OF_SET)
										break;
									cout << args[j].extargs_double_set[p];
									if (args[j].extargs_double_set[p + 1] != INVALID_DOUBLE_VALUE_OF_SET)
										cout << "/";
								}
								cout << "])" << endl;
								return -1;
							}
							else {
								args[j].args_exists = true;
								args[j].extargs_double_value = value;
							}
						}
						else if (i + 1 >= argc) {
							cout << "参数[" << arg << "]的附加参数不足. (类型:double, 可取值[";
							for (int p = 0;;++p) {
								if (args[j].extargs_double_set[p] == INVALID_DOUBLE_VALUE_OF_SET)
									break;
								cout << args[j].extargs_double_set[p];
								if (args[j].extargs_double_set[p + 1] != INVALID_DOUBLE_VALUE_OF_SET)
									cout << "/";
							}
							cout << "])" << endl;
							return -1;
						}
						else {
							cout << "参数[" << arg << "]的附加参数不是整数. (类型:double, 可取值[";
							for (int p = 0;;++p) {
								if (args[j].extargs_double_set[p] == INVALID_DOUBLE_VALUE_OF_SET)
									break;
								cout << args[j].extargs_double_set[p];
								if (args[j].extargs_double_set[p + 1] != INVALID_DOUBLE_VALUE_OF_SET)
									cout << "/";
							}
							cout << "])" << endl;
						}
					}
							break;
					case ST_EXTARGS_TYPE::str: {
						args[j].args_existed = true;
						if (i + 1 < argc && strncmp("--", argv[i+1], 2)) {
							args[j].args_exists = true;
							args[j].extargs_string_value = argv[++i];
						}
						else {
							if (args[j].extargs_string_default != "")
								cout << "参数[" << arg << "]缺少附加参数. (类型:string 缺省:" << args[j].extargs_string_default << ")" << endl;
							else
								cout << "参数[" << arg << "]缺少附加参数. (类型:string)" << endl;
							return -1;
						}
					}
						break;
					case ST_EXTARGS_TYPE::str_with_set_default: {
						args[j].args_existed = true;
						if (i + 1 < argc && strncmp("--", argv[i + 1], 2)) {
							args[j].args_exists = true;
							string value = argv[++i];
							bool find = 0;
							for (int p = 0;;++p) {
								if (args[j].extargs_string_set[p] == "")
									break;
								if (value == args[j].extargs_string_set[p]) {
									find = true;
									break;
								}
							}
							if (!find) {  //不在数组中
								args[j].extargs_string_value = args[j].extargs_string_default;
							}
							else {
								args[j].extargs_string_value = value;
							}
						}
						else {
							cout << "参数[" << arg << "]的附加参数不足. (类型:string, 可取值[";
							for (int p = 0;;++p) {
								if (args[j].extargs_string_set[p] == "")
									break;
								cout << args[j].extargs_string_set[p];
								if (args[j].extargs_string_set[p + 1] != "")
									cout << "/";
							}
							cout << "] 缺省:" << args[j].extargs_string_default << ")" << endl;
							return -1;
						}
					}
						break;
					case ST_EXTARGS_TYPE::str_with_set_error: {
						args[j].args_existed = true;
						if (i + 1 < argc && strncmp("--", argv[i + 1], 2)) {
							string value = argv[++i];
							bool find = 0;
							for (int p = 0;;++p) {
								if (args[j].extargs_string_set[p] == "")
									break;
								if (value == args[j].extargs_string_set[p]) {
									find = true;
									break;
								}
							}
							if (!find) {  //不在数组中
								cout << "参数[" << arg << "]的附加参数值(" << value << ")非法. (类型:string, 可取值[";
								for (int p = 0;;++p) {
									if (args[j].extargs_string_set[p] == "")
										break;
									cout << args[j].extargs_string_set[p];
									if (args[j].extargs_string_set[p + 1] != "")
										cout << "/";
								}
								cout << "])" << endl;
								return -1;
							}
							args[j].args_exists = true;
							args[j].extargs_string_value = value;
						}
						else {
							cout << "参数[" << arg << "]的附加参数不足. (类型:string, 可取值[";
							for (int p = 0;;++p) {
								if (args[j].extargs_string_set[p] == "")
									break;
								cout << args[j].extargs_string_set[p];
								if (args[j].extargs_string_set[p + 1] != "")
									cout << "/";
							}
							cout << "])" << endl;
							return -1;
						}
					}
						break;
					case ST_EXTARGS_TYPE::ipaddr_with_default: {
						args[j].args_existed = true;
						if (i + 1 < argc && strncmp("--", argv[i + 1], 2)) {
							string value_str = argv[++i];
							u_int value_int = get_int_ipaddr(value_str);
							if (is_valid_ip(value_str)) {
								args[j].extargs_ipaddr_value = get_int_ipaddr(value_str);
							}
							else {
								args[j].extargs_ipaddr_value = args[j].extargs_ipaddr_default;
							}
							args[j].args_exists = true;
							
						}
						else {
								cout << "参数[" << arg << "]的附加参数不足. (类型:string)" << endl;
							return -1;
						}
					}
						break;
					case ST_EXTARGS_TYPE::ipaddr_with_error: {
						args[j].args_existed = true;
						if (i + 1 < argc && strncmp("--", argv[i + 1], 2)) {
							string value_str = argv[++i];
							u_int value_int = get_int_ipaddr(value_str);
							if (!is_valid_ip(value_str)) {
								cout << "参数[" << arg << "]的附加参数值(" << value_str << ")非法. (类型:IP地址)" << endl;
								return -1;
							}
							args[j].args_exists = true;
							args[j].extargs_ipaddr_value = get_int_ipaddr(value_str);
						}
						else {
							if (args[j].extargs_string_default != "")
								cout << "参数[" << arg << "]的附加参数不足. (类型:string 缺省:" << args[j].extargs_ipaddr_default << ")" << endl;
							else
								cout << "参数[" << arg << "]的附加参数不足. (类型:string)" << endl;
							return -1;
						}
					}
						break;
					default:
						return -1;
						
				}
				break;
			}
			
		}
		if (!match) {
			if (follow_up_args) {
				return i;
			}
			else {
				if (arg.compare(0, 2,  "--") != 0)
					cout << "参数[" << arg << "]格式非法(不是--开头的有效内容)." << endl;
				else
					cout << "参数[" << arg << "]非法." << endl;
				return -1;
			}
		}
		
	}
	return i; //此句根据需要修改
}


/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：友元函数
***************************************************************************/
int args_analyse_print(const args_analyse_tools* const args)
{
	cout.setf(ios::left);
	cout.setf(ios::fixed);

	/* 打印参数表 */
	/*unsigned int w1 = 15, w2 = 21, w3 = 15, w4 = 7, w5 = 6, w6 = 46;*/
	u_int w1 = 5, w2 = 5, w3 = 8, w4 = 7, w5 = 6, w6 = 10;
	//unsigned int max_len5 = w5;
	for (int i = 0;args[i].extargs_type != ST_EXTARGS_TYPE::null;i++) {
		//name w1
		if (args[i].get_name().length() + 1 > w1) {
			w1 = args[i].get_name().length() + 1;
		}
		//type w2
		if (TYPE_NAME[(int)args[i].extargs_type].length() + 1 > w2) {
			w2 = TYPE_NAME[(int)args[i].extargs_type].length() + 1;
		}
		//default w3
		if ((args[i].extargs_type == ST_EXTARGS_TYPE::int_with_default || args[i].extargs_type == ST_EXTARGS_TYPE::int_with_set_default) && to_string(args[i].extargs_int_default).length() + 1 > w3) {
			w3 = to_string(args[i].extargs_int_default).length() + 1;
		}
		else if ((args[i].extargs_type == ST_EXTARGS_TYPE::double_with_default || args[i].extargs_type == ST_EXTARGS_TYPE::double_with_set_default) && to_string(args[i].extargs_double_default).length() + 1 > w3) {
			w3 = to_string(args[i].extargs_double_default).length() + 1;
		}
		else if ((args[i].extargs_type == ST_EXTARGS_TYPE::str || args[i].extargs_type == ST_EXTARGS_TYPE::str_with_set_default) && args[i].extargs_string_default.length() + 1 > w3) {
			w3 = args[i].extargs_string_default.length() + 1;
		}
		else if ((args[i].extargs_type == ST_EXTARGS_TYPE::ipaddr_with_default) && to_string(args[i].extargs_ipaddr_default).length() + 1 > w3) {
			w3 = to_string(args[i].extargs_ipaddr_default).length() + 1;
		}
		//value w5
		if (args[i].extargs_type == ST_EXTARGS_TYPE::int_with_default || args[i].extargs_type == ST_EXTARGS_TYPE::int_with_error || args[i].extargs_type == ST_EXTARGS_TYPE::int_with_set_default || args[i].extargs_type == ST_EXTARGS_TYPE::int_with_set_error) {
			if (args[i].args_exists && to_string(args[i].get_int()).length() + 1 > w5) {
				w5 = to_string(args[i].get_int()).length() + 1;
			}
		}
		else if (args[i].extargs_type == ST_EXTARGS_TYPE::double_with_default || args[i].extargs_type == ST_EXTARGS_TYPE::double_with_error || args[i].extargs_type == ST_EXTARGS_TYPE::double_with_set_default || args[i].extargs_type == ST_EXTARGS_TYPE::double_with_set_error) {
			if (args[i].args_exists && to_string(args[i].get_double()).length() + 1 > w5) {
				w5 = to_string(args[i].get_double()).length() + 1;
			}
		}
		else if (args[i].extargs_type == ST_EXTARGS_TYPE::str || args[i].extargs_type == ST_EXTARGS_TYPE::str_with_set_default || args[i].extargs_type == ST_EXTARGS_TYPE::str_with_set_error) {
			if (args[i].args_exists && args[i].get_string().length() + 1 > w5) {
				w5 = args[i].get_string().length() + 1;
			}
		}
		else if (args[i].extargs_type == ST_EXTARGS_TYPE::ipaddr_with_default || args[i].extargs_type == ST_EXTARGS_TYPE::ipaddr_with_error) {
			if (args[i].args_exists && args[i].get_str_ipaddr().length() + 1 > w5) {
				w5 = args[i].get_str_ipaddr().length() + 1;
			}
		}
		//range/set w6
		if (args[i].extargs_type == ST_EXTARGS_TYPE::int_with_default || args[i].extargs_type == ST_EXTARGS_TYPE::int_with_error) {
			u_int len = 4;
			len = len + to_string(args[i].extargs_int_min).length() + to_string(args[i].extargs_int_max).length();
			if (len + 1 > w6) {
				w6 = len + 1;
			}
		}
		else if (args[i].extargs_type == ST_EXTARGS_TYPE::int_with_set_default || args[i].extargs_type == ST_EXTARGS_TYPE::int_with_set_error) {
			u_int len = 0;
			for (int k = 0;args[i].extargs_int_set[k] != INVALID_INT_VALUE_OF_SET;k++) {
				len += to_string(args[i].extargs_int_set[k]).length();
				if (args[i].extargs_int_set[k + 1] != INVALID_INT_VALUE_OF_SET)
					len++;
			}
			if (len + 1 > w6) {
				w6 = len + 1;
			}
		}
		else if (args[i].extargs_type == ST_EXTARGS_TYPE::double_with_default || args[i].extargs_type == ST_EXTARGS_TYPE::double_with_error) {
			u_int len = 4;
			len = len + to_string(args[i].extargs_double_min).length() + to_string(args[i].extargs_double_max).length();
			if (len + 1 > w6) {
				w6 = len + 1;
			}
		}
		else if (args[i].extargs_type == ST_EXTARGS_TYPE::double_with_set_default || args[i].extargs_type == ST_EXTARGS_TYPE::double_with_set_error) {
			u_int len = 0;
			for (int k = 0;args[i].extargs_double_set[k] != INVALID_DOUBLE_VALUE_OF_SET;k++) {
				len += to_string(args[i].extargs_double_set[k]).length();
				if (args[i].extargs_double_set[k + 1] != INVALID_DOUBLE_VALUE_OF_SET)
					len++;
			}
			if (len + 1 > w6) {
				w6 = len + 1;
			}
		}
		else if (args[i].extargs_type == ST_EXTARGS_TYPE::str) {
		}
		else if (args[i].extargs_type == ST_EXTARGS_TYPE::str_with_set_default || args[i].extargs_type == ST_EXTARGS_TYPE::str_with_set_error) {
			u_int len = 0;
			for (int k = 0;args[i].extargs_string_set[k] != "";k++) {
				len += args[i].extargs_string_set[k].length();
				if (args[i].extargs_string_set[k + 1] != "")
					len++;
			}
			if (len + 1 > w6) {
				w6 = len + 1;
			}
		}
		else {
		}
	}
	/* 打印标题及横线 */
	cout << setw(1 + w1 + w2 + w3 + w4 + w5 + w6) << setfill('=') << '=' << setfill(' ') << endl;
	cout << " " << setw(w1) << "name" << setw(w2) << "type" << setw(w3) << "default" << setw(w4) << "exists" << setw(w5) << "value" << "range/set" << endl;
	cout << setw(1 + w1 + w2 + w3 + w4 + w5 + w6) << setfill('=') << '=' << setfill(' ') << endl;
	
	for (int i = 0;args[i].extargs_type != ST_EXTARGS_TYPE::null;i++) {
		switch (args[i].extargs_type) {
			case ST_EXTARGS_TYPE::boolean:
				cout << " " << setw(w1) << args[i].get_name() << setw(w2) << "Bool" << setw(w3) << (args[i].extargs_bool_default ? "true" : "false") << setw(w4) << args[i].args_exists << setw(w5) << (args[i].args_exists ? "true" : "/") << "/" << endl; //bool型，只要existed，就认为是true，没有单独的get_bool()函数
				break;
			case ST_EXTARGS_TYPE::int_with_default: {
				cout << " " << setw(w1) << args[i].get_name() << setw(w2) << "IntWithDefault" << setw(w3) << args[i].extargs_int_default << setw(w4) << args[i].args_exists << setw(w5) << (args[i].args_exists ? to_string(args[i].get_int()) : "/");
				cout << "[" << args[i].extargs_int_min << ".." << args[i].extargs_int_max << "]" << endl;

			}
				break;
			case ST_EXTARGS_TYPE::int_with_error: {
				cout << " " << setw(w1) << args[i].get_name() << setw(w2) << "IntWithError" << setw(w3) << "/" << setw(w4) << args[i].args_exists << setw(w5) << (args[i].args_exists ? to_string(args[i].get_int()) : "/");
				cout << "[" << args[i].extargs_int_min << ".." << args[i].extargs_int_max << "]" << endl;

			}
				break;
			case ST_EXTARGS_TYPE::int_with_set_default: {
				cout << " " << setw(w1) << args[i].get_name() << setw(w2) << "IntSETWithDefault" << setw(w3) << args[i].extargs_int_default << setw(w4) << args[i].args_exists << setw(w5) << (args[i].args_exists ? to_string(args[i].get_int()) : "/");
				for (int k = 0;args[i].extargs_int_set[k] != INVALID_INT_VALUE_OF_SET;k++) {
					cout << args[i].extargs_int_set[k];
					if (args[i].extargs_int_set[k + 1] != INVALID_INT_VALUE_OF_SET)
						cout << "/";
				}
				cout << endl;
			}
				break;
			case ST_EXTARGS_TYPE::int_with_set_error: {
				cout << " " << setw(w1) << args[i].get_name() << setw(w2) << "IntSETWithError" << setw(w3) << "/" << setw(w4) << args[i].args_exists << setw(w5) << (args[i].args_exists ? to_string(args[i].get_int()) : "/");
				int* p = args[i].extargs_int_set;
				for (int k = 0;p[k] != INVALID_INT_VALUE_OF_SET;k++) {
					cout << p[k];
					if (p[k + 1] != INVALID_INT_VALUE_OF_SET)
						cout << "/";
				}
				cout << endl;
			}
				break;
			case ST_EXTARGS_TYPE::double_with_default: {
				cout << " " << setw(w1) << args[i].get_name() << setw(w2) << "DoubleWithDefault" << setw(w3) << args[i].extargs_double_default << setw(w4) << args[i].args_exists << setw(w5) << (args[i].args_exists ? to_string(args[i].get_double()) : "/");
				cout << "[" << args[i].extargs_double_min << ".." << args[i].extargs_double_max << "]" << endl;

			}
				 break;
			case ST_EXTARGS_TYPE::double_with_error:{
				cout << " " << setw(w1) << args[i].get_name() << setw(w2) << "DoubleWithError" << setw(w3) << "/" << setw(w4) << args[i].args_exists << setw(w5) << (args[i].args_exists ? to_string(args[i].get_double()) : "/");
				cout << "[" << args[i].extargs_double_min << ".." << args[i].extargs_double_max << "]" << endl;
			}
				break;
			case ST_EXTARGS_TYPE::double_with_set_default: {
				cout << " " << setw(w1) << args[i].get_name() << setw(w2) << "DoubleSETWithDefault" << setw(w3) << args[i].extargs_double_default << setw(w4) << args[i].args_exists << setw(w5) << (args[i].args_exists ? to_string(args[i].get_double()) : "/");
				double* p = args[i].extargs_double_set;
				for (int k = 0;p[k] != INVALID_DOUBLE_VALUE_OF_SET;k++) {
					cout << p[k];
					if (p[k + 1] != INVALID_DOUBLE_VALUE_OF_SET)
						cout << "/";
				}
				cout << endl;
			}
				break;
			case ST_EXTARGS_TYPE::double_with_set_error: {
				cout << " " << setw(w1) << args[i].get_name() << setw(w2) << "DoubleSETWithError" << setw(w3) << "/" << setw(w4) << args[i].args_exists << setw(w5) << (args[i].args_exists ? to_string(args[i].get_double()) : "/");
				double* p = args[i].extargs_double_set;
				for (int k = 0;p[k] != INVALID_DOUBLE_VALUE_OF_SET;k++) {
					cout << p[k];
					if (p[k + 1] != INVALID_DOUBLE_VALUE_OF_SET)
						cout << "/";
				}
				cout << endl;
			}
				break;
			case ST_EXTARGS_TYPE::str:
				cout << " " << setw(w1) << args[i].get_name() << setw(w2) << "String" << setw(w3) << (args[i].extargs_string_default!="" ? args[i].extargs_string_default : "/") << setw(w4) << args[i].args_exists << setw(w5) << (args[i].args_exists ? args[i].get_string() : "/") << "/" <<endl;
				break;
			case ST_EXTARGS_TYPE::str_with_set_default: {
				cout << " " << setw(w1) << args[i].get_name() << setw(w2) << "StringSETWithDefault" << setw(w3) << args[i].extargs_string_default << setw(w4) << args[i].args_exists << setw(w5) << (args[i].args_exists ? args[i].get_string() : "/");
				string* p = args[i].extargs_string_set;
				for (int k = 0;p[k] != "";k++) {
					cout << p[k];
					if (p[k + 1] != "")
						cout << "/";
				}
				cout << endl;
			}
				break;
			case ST_EXTARGS_TYPE::str_with_set_error:{
				cout << " " << setw(w1) << args[i].get_name() << setw(w2) << "StringSETWithError" << setw(w3) << "/" << setw(w4) << args[i].args_exists << setw(w5) << (args[i].args_exists ? args[i].get_string() : "/");
				string* p = args[i].extargs_string_set;
				for (int k = 0;p[k] != "";k++) {
					cout << p[k];
					if (p[k + 1] != "")
						cout << "/";
				}
				cout << endl;
			}
				break;			
			case ST_EXTARGS_TYPE::ipaddr_with_default:
				cout << " " << setw(w1) << args[i].get_name() << setw(w2) << "IPAddrWithDefault" << setw(w3) << (args[i].extargs_ipaddr_default != 0 ? ip_to_str(args[i].extargs_ipaddr_default) : "/") << setw(w4) << args[i].args_exists << setw(w5) << (args[i].args_exists ? args[i].get_str_ipaddr() : "/") << "/" << endl;
				break;
			case ST_EXTARGS_TYPE::ipaddr_with_error:
				cout << " " << setw(w1) << args[i].get_name() << setw(w2) << "IPAddrWithError" << setw(w3) << "/" << setw(w4) << args[i].args_exists << setw(w5) << (args[i].args_exists ? args[i].get_str_ipaddr() : "/") << "/" << endl;
				break;
}
	}
	/* 打印横线 */
	cout << setw(1 + w1 + w2 + w3 + w4 + w5 + w6) << setfill('=') << '=' << setfill(' ') << endl;

	cout.unsetf(ios::fixed);
	cout << endl;
	return 0; //此句根据需要修改
}

#endif // !ENABLE_LIB_COMMON_TOOLS
