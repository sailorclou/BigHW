/* 2351044 ������ ������ */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include "../include/class_aat.h"
//���б�Ҫ�����Լ�������ͷ�ļ�
#include <cstring>
//#include <sstream>
#include <algorithm>
using namespace std;

#if !ENABLE_LIB_COMMON_TOOLS //��ʹ��lib����Ч

/* ---------------------------------------------------------------
	 �������������Ҫstatic�������ڲ������ã�
   ---------------------------------------------------------------- */
static bool isInt(const string& str) 
{
	try {
		int value = stoi(str);  // ���񷵻�ֵ�Ա��⾯��
		(void)value;                 // ��ȷ��������ʹ�ø�ֵ
		return true;
	}
	catch (invalid_argument&) {
		return false;  // ����޷�ת��Ϊ���֣��׳��쳣
	}
	catch (out_of_range&) {
		return false;  // ���������Χ
	}
}
static bool isDouble(const string& str) 
{
	try {
		double value = stod(str);  // ���񷵻�ֵ�Ա��⾯��
		(void)value;                 // ��ȷ��������ʹ�ø�ֵ
		return true;
	}
	catch (invalid_argument&) {
		return false;  // ����޷�ת��Ϊ���֣��׳��쳣
	}
	catch (out_of_range&) {
		return false;  // ���������Χ
	}
}
static bool is_valid_ip(const string& str_ipaddr) 
{
	int bytes[4];
	char dot;
	istringstream iss(str_ipaddr);

	// ����ʽ�Ƿ�Ϊ "byte1.byte2.byte3.byte4"
	if (!(iss >> bytes[0] >> dot >> bytes[1] >> dot >> bytes[2] >> dot >> bytes[3])) {
		return false;
	}

	// ���ÿ���ֽ��Ƿ��� [0, 255] ��Χ��
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

	// ��ȡÿ���ֽڣ���ƴ�ӳ� "byte1.byte2.byte3.byte4" ��ʽ
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
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����null
 ***************************************************************************/
args_analyse_tools::args_analyse_tools() : args_name(""), extargs_type(ST_EXTARGS_TYPE::null), extargs_num(0), args_existed(0),
					args_exists(0), extargs_int_set(nullptr), extargs_string_set(nullptr), extargs_double_set(nullptr)
{
	memset(pad, 0, sizeof(pad));
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����boolean
 ***************************************************************************/
args_analyse_tools::args_analyse_tools(const char* name, const ST_EXTARGS_TYPE type, const int ext_num, const bool def) : 
					args_name(name), extargs_type(type), extargs_num(ext_num), extargs_bool_default(def), args_existed(0), args_exists(0),
	extargs_int_set(nullptr), extargs_string_set(nullptr), extargs_double_set(nullptr)
{
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����int_with_default��int_with_error
 ***************************************************************************/
args_analyse_tools::args_analyse_tools(const char* name, const ST_EXTARGS_TYPE type, const int ext_num, const int def, const int _min, const int _max) :
					args_name(name), extargs_type(type), extargs_num(ext_num), extargs_int_default(def), extargs_int_value(def), extargs_int_min(_min), extargs_int_max(_max), args_existed(0), args_exists(0),
	extargs_int_set(nullptr), extargs_string_set(nullptr), extargs_double_set(nullptr)
{
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����int_with_set_default��int_with_set_error
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
		// �����ڴ�
		extargs_int_set = new int[++i];

		// ��������
		for (i = 0;;++i) {
			extargs_int_set[i] = set[i];
			if (set[i] == INVALID_INT_VALUE_OF_SET)
				break;
		}

		// ��� def_of_set_pos ��Ч�����ʼ��Ĭ��ֵ
		if (def_of_set_pos >= 0 && def_of_set_pos <= i) {
			extargs_int_default = set[def_of_set_pos];
			extargs_int_value = set[def_of_set_pos];
		}
	}
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����str��ipaddr_with_default��ipaddr_with_erro
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
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����str_with_set_default��str_with_set_error
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
		// �����ڴ�
		extargs_string_set = new string[++i];

		// ��������
		for (i = 0;;++i) {
			extargs_string_set[i] = set[i];
			if (set[i] == "")
				break;
		}

		// ��� def_of_set_pos ��Ч�����ʼ��Ĭ��ֵ
		if (def_of_set_pos >= 0 && def_of_set_pos <= i) {
			extargs_string_default = set[def_of_set_pos];
			extargs_string_value = set[def_of_set_pos];
		}
	}
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����double_with_default��double_with_error
 ***************************************************************************/
args_analyse_tools::args_analyse_tools(const char* name, const ST_EXTARGS_TYPE type, const int ext_num, const double	def, const double _min, const double _max) :
					args_name(name), extargs_type(type), extargs_num(ext_num), extargs_double_default(def), extargs_double_value(def), extargs_double_min(_min), extargs_double_max(_max), args_existed(0), args_exists(0),
	extargs_int_set(nullptr), extargs_string_set(nullptr), extargs_double_set(nullptr)
{
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����double_with_set_default��double_with_set_error
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
		// �����ڴ�
		extargs_double_set = new double[++i];

		// ��������
		for (i = 0;;++i) {
			extargs_double_set[i] = set[i];
			if (set[i] == INVALID_DOUBLE_VALUE_OF_SET)
				break;
		}

		// ��� def_of_set_pos ��Ч�����ʼ��Ĭ��ֵ
		if (def_of_set_pos >= 0 && def_of_set_pos <= i) {
			extargs_double_default = set[def_of_set_pos];
			extargs_double_value = set[def_of_set_pos];
		}
	}
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
 ***************************************************************************/
args_analyse_tools::~args_analyse_tools()
{
	// �ͷ���������
	if (extargs_int_set) {
		delete[] extargs_int_set;
		extargs_int_set = nullptr;
	}

	// �ͷ��ַ�������
	if (extargs_string_set) {
		delete[] extargs_string_set;
		extargs_string_set = nullptr;
	}

	// �ͷ�˫���ȸ��㼯��
	if (extargs_double_set) {
		delete[] extargs_double_set;
		extargs_double_set = nullptr;
	}
}

/* ---------------------------------------------------------------
	 ����AAT���Զ����Ա������ʵ�֣�private��
   ---------------------------------------------------------------- */

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ������ʵ�֣���Ҫ��
 ***************************************************************************/
const string args_analyse_tools::get_name() const
{
	return this->args_name;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ������!!��ֻ����0/1
			��ʵ�֣���Ҫ��
 ***************************************************************************/
const int args_analyse_tools::existed() const
{
	return !!this->args_existed;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ������ʵ�֣���Ҫ��
 ***************************************************************************/
const int args_analyse_tools::get_int() const
{
	return this->extargs_int_value;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ������ʵ�֣���Ҫ��
 ***************************************************************************/
const double args_analyse_tools::get_double() const
{
	return this->extargs_double_value;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ������ʵ�֣���Ҫ��
 ***************************************************************************/
const string args_analyse_tools::get_string() const
{
	return this->extargs_string_value;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ������ʵ�֣���Ҫ��
 ***************************************************************************/
const unsigned int args_analyse_tools::get_ipaddr() const
{
	return this->extargs_ipaddr_value;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ������ extargs_ipaddr_value ��ֵ�� 0x7f000001 תΪ "127.0.0.1"
 ***************************************************************************/
const string args_analyse_tools::get_str_ipaddr() const
{
	ostringstream ip;
	ip << ((extargs_ipaddr_value >> 24) & 0xFF) << "."
		<< ((extargs_ipaddr_value >> 16) & 0xFF) << "."
		<< ((extargs_ipaddr_value >> 8) & 0xFF) << "."
		<< (extargs_ipaddr_value & 0xFF);
	return ip.str(); //�˾������Ҫ�޸�
}


/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������follow_up_args���Ƿ��к�������
			0  ���޺�������
			1  ���к�������
  �� �� ֵ��
  ˵    ������Ԫ����
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
					cout << "����[" << args[j].get_name() << "]�ظ�." << endl;
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
							cout << "����[" << arg << "]�ĸ��Ӳ�������. (����:int, ��Χ[" << args[j].extargs_int_min << ".." << args[j].extargs_int_max << "])" << endl;
							return -1;
						}
						else {
							cout << "����[" << arg << "]�ĸ��Ӳ�����������. (����:int, ��Χ[" << args[j].extargs_int_min << ".." << args[j].extargs_int_max << "])" << endl;
							return -1;
						}
					}
						break;
					case ST_EXTARGS_TYPE::int_with_error: {
						args[j].args_existed = true;
						if (i + 1 < argc && isInt(argv[i + 1])) {
							int value = stoi(argv[++i]);
							if (value > args[j].extargs_int_max || value < args[j].extargs_int_min) {
								cout << "����[" << arg << "]�ĸ��Ӳ���ֵ(" << value << ")�Ƿ�. (����:int, ��Χ[" << args[j].extargs_int_min << ".." << args[j].extargs_int_max << "])" << endl;
								return -1;
							}
							else {
								args[j].args_exists = true;
								args[j].extargs_int_value = value;
							}
						}
						else if (i + 1 >= argc) {
							cout << "����[" << arg << "]�ĸ��Ӳ�������. (����:int, ��Χ[" << args[j].extargs_int_min << ".." << args[j].extargs_int_max << "])" << endl;
							return -1;
						}
						else {
							cout << "����[" << arg << "]�ĸ��Ӳ�����������. (����:int, ��Χ[" << args[j].extargs_int_min << ".." << args[j].extargs_int_max << "])" << endl;
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
							if (!find) {  //����������
								args[j].extargs_int_value = args[j].extargs_int_default;
							}
							else {
								args[j].extargs_int_value = value;
							}
						}
						else if (i + 1 >= argc) {
							cout << "����[" << arg << "]�ĸ��Ӳ�������. (����:int, ��ȡֵ[";
							for (int p = 0;;++p) {
								if (args[j].extargs_int_set[p] == INVALID_INT_VALUE_OF_SET)
									break;
								cout << args[j].extargs_int_set[p];
								if (args[j].extargs_int_set[p + 1] != INVALID_INT_VALUE_OF_SET)
									cout << "/";
							}
							cout << "] ȱʡ:" << args[j].extargs_int_default << ")" << endl;
							return -1;
						}
						else {
							cout << "����[" << arg << "]�ĸ��Ӳ�����������. (����:int, ��ȡֵ[";
							for (int p = 0;;++p) {
								if (args[j].extargs_int_set[p] == INVALID_INT_VALUE_OF_SET)
									break;
								cout << args[j].extargs_int_set[p];
								if (args[j].extargs_int_set[p + 1] != INVALID_INT_VALUE_OF_SET)
									cout << "/";
							}
							cout << "] ȱʡ:" << args[j].extargs_int_default << ")" << endl;
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
							if (!find) {  //����������
								cout << "����[" << arg << "]�ĸ��Ӳ���ֵ(" << value << ")�Ƿ�. (����:int, ��ȡֵ[";
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
							cout << "����[" << arg << "]�ĸ��Ӳ�������. (����:int, ��ȡֵ[";
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
							cout << "����[" << arg << "]�ĸ��Ӳ�����������. (����:int, ��ȡֵ[";
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
							cout << "����[" << arg << "]�ĸ��Ӳ�������. (����:double, ��Χ[" << args[j].extargs_double_min << ".." << args[j].extargs_double_max << "])" << endl;
							return -1;
						}
						else {
							cout << "����[" << arg << "]�ĸ��Ӳ�����������. (����:double, ��Χ[" << args[j].extargs_double_min << ".." << args[j].extargs_double_max << "])" << endl;
							return -1;
						}
					}
						break;
					case ST_EXTARGS_TYPE::double_with_error: {
						args[j].args_existed = true;
						if (i + 1 < argc && isDouble(argv[i + 1])) {
							double value = stod(argv[++i]);
							if (value > args[j].extargs_double_max || value < args[j].extargs_double_min) {
								cout << "����[" << arg << "]�ĸ��Ӳ���ֵ(" << value << ")�Ƿ�. (����:double, ��Χ[" << args[j].extargs_double_min << ".." << args[j].extargs_double_max << "])" << endl;
								return -1;
							}
							else {
								args[j].args_exists = true;
								args[j].extargs_double_value = value;
							}
						}
						else if (i + 1 >= argc) {
							cout << "����[" << arg << "]�ĸ��Ӳ�������. (����:double, ��Χ[" << args[j].extargs_double_min << ".." << args[j].extargs_double_max << "])" << endl;
							return -1;
						}
						else {
							cout << "����[" << arg << "]�ĸ��Ӳ�����������. (����:double, ��Χ[" << args[j].extargs_double_min << ".." << args[j].extargs_double_max << "])" << endl;
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
							if (!find) {  //����������
								args[j].extargs_double_value = args[j].extargs_double_default;
							}
							else {
								args[j].extargs_double_value = value;
							}
						}
						else if (i + 1 >= argc) {
							cout << "����[" << arg << "]�ĸ��Ӳ�������. (����:double, ��ȡֵ[";
							for (int p = 0;;++p) {
								if (args[j].extargs_double_set[p] == INVALID_DOUBLE_VALUE_OF_SET)
									break;
								cout << args[j].extargs_double_set[p];
								if (args[j].extargs_double_set[p + 1] != INVALID_DOUBLE_VALUE_OF_SET)
									cout << "/";
							}
							cout << "] ȱʡ:" << args[j].extargs_double_default << ")" << endl;
							return -1;
						}
						else {
							cout << "����[" << arg << "]�ĸ��Ӳ�����������. (����:double, ��ȡֵ[";
							for (int p = 0;;++p) {
								if (args[j].extargs_double_set[p] == INVALID_DOUBLE_VALUE_OF_SET)
									break;
								cout << args[j].extargs_double_set[p];
								if (args[j].extargs_double_set[p + 1] != INVALID_DOUBLE_VALUE_OF_SET)
									cout << "/";
							}
							cout << "] ȱʡ:" << args[j].extargs_double_default << ")" << endl;
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
							if (!find) {  //����������
								cout << "����[" << arg << "]�ĸ��Ӳ���ֵ(" << value << ")�Ƿ�. (����:double, ��ȡֵ[";
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
							cout << "����[" << arg << "]�ĸ��Ӳ�������. (����:double, ��ȡֵ[";
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
							cout << "����[" << arg << "]�ĸ��Ӳ�����������. (����:double, ��ȡֵ[";
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
								cout << "����[" << arg << "]ȱ�ٸ��Ӳ���. (����:string ȱʡ:" << args[j].extargs_string_default << ")" << endl;
							else
								cout << "����[" << arg << "]ȱ�ٸ��Ӳ���. (����:string)" << endl;
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
							if (!find) {  //����������
								args[j].extargs_string_value = args[j].extargs_string_default;
							}
							else {
								args[j].extargs_string_value = value;
							}
						}
						else {
							cout << "����[" << arg << "]�ĸ��Ӳ�������. (����:string, ��ȡֵ[";
							for (int p = 0;;++p) {
								if (args[j].extargs_string_set[p] == "")
									break;
								cout << args[j].extargs_string_set[p];
								if (args[j].extargs_string_set[p + 1] != "")
									cout << "/";
							}
							cout << "] ȱʡ:" << args[j].extargs_string_default << ")" << endl;
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
							if (!find) {  //����������
								cout << "����[" << arg << "]�ĸ��Ӳ���ֵ(" << value << ")�Ƿ�. (����:string, ��ȡֵ[";
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
							cout << "����[" << arg << "]�ĸ��Ӳ�������. (����:string, ��ȡֵ[";
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
								cout << "����[" << arg << "]�ĸ��Ӳ�������. (����:string)" << endl;
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
								cout << "����[" << arg << "]�ĸ��Ӳ���ֵ(" << value_str << ")�Ƿ�. (����:IP��ַ)" << endl;
								return -1;
							}
							args[j].args_exists = true;
							args[j].extargs_ipaddr_value = get_int_ipaddr(value_str);
						}
						else {
							if (args[j].extargs_string_default != "")
								cout << "����[" << arg << "]�ĸ��Ӳ�������. (����:string ȱʡ:" << args[j].extargs_ipaddr_default << ")" << endl;
							else
								cout << "����[" << arg << "]�ĸ��Ӳ�������. (����:string)" << endl;
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
					cout << "����[" << arg << "]��ʽ�Ƿ�(����--��ͷ����Ч����)." << endl;
				else
					cout << "����[" << arg << "]�Ƿ�." << endl;
				return -1;
			}
		}
		
	}
	return i; //�˾������Ҫ�޸�
}


/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ������Ԫ����
***************************************************************************/
int args_analyse_print(const args_analyse_tools* const args)
{
	cout.setf(ios::left);
	cout.setf(ios::fixed);

	/* ��ӡ������ */
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
	/* ��ӡ���⼰���� */
	cout << setw(1 + w1 + w2 + w3 + w4 + w5 + w6) << setfill('=') << '=' << setfill(' ') << endl;
	cout << " " << setw(w1) << "name" << setw(w2) << "type" << setw(w3) << "default" << setw(w4) << "exists" << setw(w5) << "value" << "range/set" << endl;
	cout << setw(1 + w1 + w2 + w3 + w4 + w5 + w6) << setfill('=') << '=' << setfill(' ') << endl;
	
	for (int i = 0;args[i].extargs_type != ST_EXTARGS_TYPE::null;i++) {
		switch (args[i].extargs_type) {
			case ST_EXTARGS_TYPE::boolean:
				cout << " " << setw(w1) << args[i].get_name() << setw(w2) << "Bool" << setw(w3) << (args[i].extargs_bool_default ? "true" : "false") << setw(w4) << args[i].args_exists << setw(w5) << (args[i].args_exists ? "true" : "/") << "/" << endl; //bool�ͣ�ֻҪexisted������Ϊ��true��û�е�����get_bool()����
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
	/* ��ӡ���� */
	cout << setw(1 + w1 + w2 + w3 + w4 + w5 + w6) << setfill('=') << '=' << setfill(' ') << endl;

	cout.unsetf(ios::fixed);
	cout << endl;
	return 0; //�˾������Ҫ�޸�
}

#endif // !ENABLE_LIB_COMMON_TOOLS
