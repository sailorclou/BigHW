/* 2351044 ������ ������ */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
/* ����Լ���Ҫ��ͷ�ļ���ע������ */
#include "../include/class_cft.h"
using namespace std;

/* ���������Զ��庯����ʵ�֣��Ѹ��������ݲ�ȫ�� */
// string�Ƚϣ���Сд�����У�
bool cmp_ignore_case(const string& str1, const string& str2) 
{
	string lowerStr1 = str1;
	string lowerStr2 = str2;

	transform(lowerStr1.begin(), lowerStr1.end(), lowerStr1.begin(), ::tolower);
	transform(lowerStr2.begin(), lowerStr2.end(), lowerStr2.begin(), ::tolower);

	return lowerStr1 == lowerStr2;
}
string config_file_tools::trim(const std::string& str) const
{
	const std::string whitespace = " \t";
	size_t start = str.find_first_not_of(whitespace);
	size_t end = str.find_last_not_of(whitespace);
	return (start == std::string::npos) ? "" : str.substr(start, end - start + 1);
}
bool config_file_tools::get_key_value(string item, string& key, string& value) const
{
	if (item_separate_character_type == BREAK_CTYPE::Equal) {
		size_t break_pos = item.find('=');
		if (break_pos != string::npos) {  //�й涨�ķָ���
			key = trim(item.substr(0, break_pos));
			value = trim(item.substr(break_pos + 1));
			return true;
		}
	}
	else {
		size_t break_pos = item.find(' ');
		if (break_pos != string::npos) {  //�й涨�ķָ���
			key = trim(item.substr(0, break_pos));
			value = trim(item.substr(break_pos + 1));
			return true;
		}
	}
	return false;
}
bool config_file_tools::is_valid_ip(const string& str_ipaddr) const
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
const unsigned int config_file_tools::get_int_ipaddr(const string& str_ipaddr) const
{
	unsigned int ip = 0;
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
  ˵    ����
***************************************************************************/
config_file_tools::config_file_tools(const char* const _cfgname, const enum BREAK_CTYPE _bctype)
{
	/* ������� */
	//���ݳ�Ա
	cfgname = string(_cfgname);
	item_separate_character_type = _bctype;
	//���ļ�
	ifstream cfg_file(cfgname, ios::binary);
	if (!cfg_file.is_open()) {
		return;
	}
	//���ж�ȡ
	string line;
	int line_count = 0;
	string current_group_name;
	cfgGroup current_group;
	while (getline(cfg_file, line)) {
		line_count++;
		if (line.length() > MAX_LINE) {
			cout << "�Ƿ���ʽ�������ļ�,��[" << line_count << "]�г�����󳤶� 1024." << endl;
			return;
		}
		//ȥ��ע��
		size_t comment_pos = line.find_first_of("#");
		if (line.find("//") < comment_pos)
			comment_pos = line.find("//");
		if (comment_pos != string::npos) {
			line = line.substr(0, comment_pos);
		}
		//ȥ��ǰ��ո��Ʊ��
		line.erase(0, line.find_first_not_of(" \t"));
		line.erase(line.find_last_not_of(" \t") + 1);
		//ȥ������
		if (line.empty()) {
			continue;
		}
		if (line.front() == '[' && line.back() == ']') {  //��
			size_t first_bracket = line.find('[');
			size_t last_bracket = line.find_last_of(']');
			if (first_bracket != string::npos && last_bracket != string::npos) {
				if (!current_group_name.empty()) {
					current_group.item_num = static_cast<int>(current_group.items.size());
					groups.push_back(current_group);
					current_group_name = "";
					current_group = cfgGroup();
				}
				current_group_name = trim(line.substr(first_bracket, last_bracket - first_bracket));
				current_group.group_name = current_group_name;
			}
			else {
				continue;
			}
		}
		else if (!current_group_name.empty()) {  //��
			current_group.items.push_back(line);
		}

		else {  //û������,������
			if (groups.empty()) {
				// ��ʼ����һ��Ԫ��
				cfgGroup new_group;
				new_group.group_name = "";
				groups.push_back(new_group);
			}
			groups[0].items.push_back(line);
			groups[0].item_num++;
		}
	}
	if (!current_group_name.empty()) {
		current_group.item_num = static_cast<int>(current_group.items.size());
		groups.push_back(current_group);
		current_group_name = "";
		current_group = cfgGroup();
	}
	cfg_file.close();
	read_success = true;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
config_file_tools::config_file_tools(const string& _cfgname, const enum BREAK_CTYPE _bctype)
{
	/* ������� */
	//���ݳ�Ա
	cfgname = _cfgname;	
	item_separate_character_type = _bctype;
	//���ļ�
	ifstream cfg_file(cfgname, ios::binary);
	if (!cfg_file.is_open()) {
		return;
	}
	//���ж�ȡ
	string line;
	int line_count = 0;
	string current_group_name;
	cfgGroup current_group;
	while (getline(cfg_file, line)) {
		line_count++;
		if (line.length() > MAX_LINE) {
			cout << "�Ƿ���ʽ�������ļ�,��[" << line_count << "]�г�����󳤶� 1024." << endl;
			return;
		}
		//ȥ��ע��
		size_t comment_pos = line.find_first_of("#");
		if (line.find("//") < comment_pos)
			comment_pos = line.find("//");
		if (comment_pos != string::npos) {
			line = line.substr(0, comment_pos);
		}
		//ȥ��ǰ��ո��Ʊ��
		line.erase(0, line.find_first_not_of(" \t"));
		line.erase(line.find_last_not_of(" \t") + 1);
		//ȥ������
		if (line.empty()) {
			continue;
		}
		if (line.front() == '[' && line.back() == ']') {  //��
			size_t first_bracket = line.find('[');
			size_t last_bracket = line.find_last_of(']');
			if (first_bracket != string::npos && last_bracket != string::npos) {
				if (!current_group_name.empty()) {
					current_group.item_num = static_cast<int>(current_group.items.size());
					groups.push_back(current_group);
					current_group_name = "";
					current_group = cfgGroup();
				}
				current_group_name = trim(line.substr(first_bracket, last_bracket - first_bracket + 1));
				current_group.group_name = current_group_name;
			}
			else {
				continue;
			}
		}
		else if (!current_group_name.empty()) {  //��
			current_group.items.push_back(line);
		}
		else {  //û������,������
			if (groups.empty()) {
				// ��ʼ����һ��Ԫ��
				cfgGroup new_group;
				new_group.group_name = "";
				groups.push_back(new_group);
			}
			groups[0].items.push_back(line);
			groups[0].item_num++;
		}
	}
	if (!current_group_name.empty()) {
		current_group.item_num = static_cast<int>(current_group.items.size());
		groups.push_back(current_group);
		current_group_name = "";
		current_group = cfgGroup();
	}
	cfg_file.close();
	read_success = true;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
config_file_tools::~config_file_tools()
{
	/* ������� */
	
}


/***************************************************************************
  �������ƣ�
  ��    �ܣ��ж϶������ļ��Ƿ�ɹ�
  ���������
  �� �� ֵ��true - �ɹ����Ѷ������е���/��
		   false - ʧ�ܣ��ļ�ĳ�г���/�ļ�ȫ����ע�����
  ˵    ����
***************************************************************************/
bool config_file_tools::is_read_succeeded() const
{
	/* ������ɣ�������Ҫ�ı�return��ֵ */
	return read_success;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ����������ļ��е�������
  ���������vector <string>& ret : vector ��ÿ��Ϊһ������
  �� �� ֵ������������������������ļ���������Ϊ1������Ϊ"��
  ˵    ����
***************************************************************************/
int config_file_tools::get_all_group(vector <string>& ret)
{
	/* ������ɣ�������Ҫ�ı�return��ֵ */
	int group_num;
	group_num = groups.empty() ? 0 : static_cast<int>(groups.size());
	for (int i = 0;i < group_num;i++) {
		ret.push_back(groups[i].group_name);
	}

	return group_num;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�����ָ�����������������ԭʼ����
  ���������const char* const group_name������
		   vector <string>& ret��vector ��ÿ��Ϊһ�����ԭʼ����
		   const bool is_case_sensitive = false : �����Ƿ��Сд���У�true-��Сд���� / Ĭ��false-��Сд������
  �� �� ֵ�����������0��ʾ��
  ˵    ����
***************************************************************************/
int config_file_tools::get_all_item(const char* const group_name, vector <string>& ret, const bool is_case_sensitive)
{
	/* ������ɣ�������Ҫ�ı�return��ֵ */
	int group_num = -1, item_num = -1, index = -1;
	group_num = groups.empty() ? 0 : static_cast<int>(groups.size());
	for (int i = 0;i < group_num;i++) {
		bool equal = false;
		if (is_case_sensitive)
			equal = groups[i].group_name == string(group_name);
		else
			equal = cmp_ignore_case(groups[i].group_name, string(group_name));
		if (equal) {
			index = i;
			break;
		}
		if (i == group_num - 1) {
			return -1;
		}
	}
	
	item_num = groups[index].items.empty() ? 0 : static_cast<int>(groups[index].items.size());
	for (int i = 0;i < item_num;i++) {
		ret.push_back(groups[index].items[i]);
	}
	return item_num;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�����/��ĿΪstring��ʽ������ͬ��
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int config_file_tools::get_all_item(const string& group_name, vector <string>& ret, const bool is_case_sensitive)
{
	/* ������ɣ�������Ҫ�ı�return��ֵ */
	int group_num = 0, item_num = 0, index = -1;
	group_num = groups.empty() ? 0 : static_cast<int>(groups.size());
	for (int i = 0;i < group_num;i++) {
		bool equal = false;
		if (is_case_sensitive)
			equal = groups[i].group_name == group_name;
		else
			equal = cmp_ignore_case(groups[i].group_name, group_name);
		if (equal) {
			index = i;
			break;
		}
		if (i == group_num - 1) {
			return -1;
		}
	}
	item_num = groups[index].items.empty() ? 0 : static_cast<int>(groups[index].items.size());
	for (int i = 0;i < item_num;i++) {
		ret.push_back(groups[index].items[i]);
	}
	return item_num;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�ȡĳ���ԭʼ���ݣ�=��������ַ���string��ʽ��
  ���������const char* const group_name
		   const char* const item_name
		   string &ret
		   const bool group_is_case_sensitive = false : �����Ƿ��Сд���У�true-��Сд���� / Ĭ��false-��Сд������
		   const bool item_is_case_sensitive = false  : �����Ƿ��Сд���У�true-��Сд���� / Ĭ��false-��Сд������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int config_file_tools::item_get_raw(const char* const group_name, const char* const item_name, string& ret, const bool group_is_case_sensitive, const bool item_is_case_sensitive)
{
	/* ������ɣ�������Ҫ�ı�return��ֵ */
	int group_num, item_num, index = -1;
	string key, value;
	group_num = groups.empty() ? 0 : static_cast<int>(groups.size());
	for (int i = 0;i < group_num;i++) {
		bool equal = false;
		if (group_is_case_sensitive)
			equal = groups[i].group_name == string(group_name);
		else
			equal = cmp_ignore_case(groups[i].group_name, string(group_name));
		if (equal) {
			index = i;
			item_num = groups[index].items.empty() ? 0 : static_cast<int>(groups[index].items.size());
			for (int j = 0;j < item_num;j++) {
				bool got = get_key_value(groups[index].items[j], key, value);
				if (item_is_case_sensitive)
					equal = key == string(item_name);
				else
					equal = cmp_ignore_case(key, string(item_name));
				if (got && equal) {
					ret = value;
					return 1;
				}
			}
			break;
		}
	}
	return 0;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�����/��ĿΪstring��ʽ������ͬ��
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int config_file_tools::item_get_raw(const string& group_name, const string& item_name, string& ret, const bool group_is_case_sensitive, const bool item_is_case_sensitive)
{
	/* ��������ʵ�� */
	return this->item_get_raw(group_name.c_str(), item_name.c_str(), ret, group_is_case_sensitive, item_is_case_sensitive);
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�ȡĳ������ݣ���������Ϊchar��
  ���������const char* const group_name               ������
		   const char* const item_name                ������
		   const bool group_is_case_sensitive = false : �����Ƿ��Сд���У�true-��Сд���� / Ĭ��false-��Сд������
		   const bool item_is_case_sensitive = false  : �����Ƿ��Сд���У�true-��Сд���� / Ĭ��false-��Сд������
  �� �� ֵ��1 - �������������
		   0 - ���������������
  ˵    ����
***************************************************************************/
int config_file_tools::item_get_null(const char* const group_name, const char* const item_name, const bool group_is_case_sensitive, const bool item_is_case_sensitive)
{
	/* ������ɣ�������Ҫ�ı�return��ֵ */
	int group_num, item_num, index = -1;
	string key, value;
	group_num = groups.empty() ? 0 : static_cast<int>(groups.size());
	for (int i = 0;i < group_num;i++) {
		bool equal = false;
		if (group_is_case_sensitive)
			equal = groups[i].group_name == string(group_name);
		else
			equal = cmp_ignore_case(groups[i].group_name, string(group_name));
		if (equal) {
			index = i;
			item_num = groups[index].items.empty() ? 0 : static_cast<int>(groups[index].items.size());
			for (int j = 0;j < item_num;j++) {
				bool got = get_key_value(groups[index].items[j], key, value);
				if (item_is_case_sensitive)
					equal = key == string(item_name);
				else
					equal = cmp_ignore_case(key, string(item_name));
				if (got && equal) {
					return 1;
				}
			}
			break;
		}
	}
	return 0;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�����/��ĿΪstring��ʽ������ͬ��
  ���������
  �� �� ֵ��
  ˵    ������Ϊ���ߺ���һ���ڳ����ʼ���׶α����ã������ڳ���ִ���б���Ƶ�ε��ã�
		   �������ֱ���׿ǣ�����΢Ӱ��Ч�ʣ�����Ӱ���������ܣ��Ը�Ƶ�ε��ã��˷������ʺϣ�
***************************************************************************/
int config_file_tools::item_get_null(const string& group_name, const string& item_name, const bool group_is_case_sensitive, const bool item_is_case_sensitive)
{
	/* ��������ʵ�� */
	return this->item_get_null(group_name.c_str(), item_name.c_str(), group_is_case_sensitive, item_is_case_sensitive);
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�ȡĳ������ݣ���������Ϊchar��
  ���������const char* const group_name               ������
		   const char* const item_name                ������
		   char& value                                ��������char��ֵ������1ʱ���ţ�����0�򲻿��ţ�
		   const char* const choice_set = nullptr     ���Ϸ���char�ļ��ϣ����磺"YyNn"��ʾ�Ϸ�����ΪY/N�Ҳ��ִ�Сд���ò�����Ĭ��ֵnullptr����ʾȫ���ַ���������飩
		   const char def_value = DEFAULT_CHAR_VALUE  ��������/�����Ƿ�������µ�Ĭ��ֵ���ò�����Ĭ��ֵDEFAULT_CHAR_VALUE�����������
															��ֵ��   DEFAULT_CHAR_VALUE ʱ������0��ֵ�����ţ�
															��ֵ���� DEFAULT_CHAR_VALUE ʱ����value=def_value������1
		   const bool group_is_case_sensitive = false : �����Ƿ��Сд���У�true-��Сд���� / Ĭ��false-��Сд������
		   const bool item_is_case_sensitive = false  : �����Ƿ��Сд���У�true-��Сд���� / Ĭ��false-��Сд������
  �� �� ֵ��1 - ȡ����ȷֵ
			   δȡ��ֵ/δȡ����ȷֵ��������ȱʡֵ��������Ϊȱʡֵ��
		   0 - δȡ����ֻ��Ϊδָ��Ĭ��ֵ������²Ż᷵��0��
  ˵    ����
***************************************************************************/
int config_file_tools::item_get_char(const char* const group_name, const char* const item_name, char& value,
	const char* const choice_set, const char def_value, const bool group_is_case_sensitive, const bool item_is_case_sensitive)
{
	/* ������ɣ�������Ҫ�ı�return��ֵ */
	int group_num, item_num, index = -1;
	string key, v;
	bool got = false;
	group_num = groups.empty() ? 0 : static_cast<int>(groups.size());
	for (int i = 0;i < group_num;i++) {
		bool equal = false;
		if (group_is_case_sensitive)
			equal = groups[i].group_name == string(group_name);
		else
			equal = cmp_ignore_case(groups[i].group_name, string(group_name));
		if (equal) {
			index = i;
			item_num = groups[index].items.empty() ? 0 : static_cast<int>(groups[index].items.size());
			for (int j = 0;j < item_num;j++) {
				got = get_key_value(groups[index].items[j], key, v);
				if (item_is_case_sensitive)
					equal = key == string(item_name);
				else
					equal = cmp_ignore_case(key, string(item_name));
				if (got && equal && v.length() == 1) {
					if (string(choice_set).find(v) != string::npos) {
						value = v[0];
						return 1;
					}
				}
			}
		}
	}
	if (def_value != DEFAULT_CHAR_VALUE) {
		value = def_value;
		return 1;
	}
	return 0;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�����/��ĿΪstring��ʽ������ͬ��
  ���������
  �� �� ֵ��
  ˵    ������Ϊ���ߺ���һ���ڳ����ʼ���׶α����ã������ڳ���ִ���б���Ƶ�ε��ã�
		   �������ֱ���׿ǣ�����΢Ӱ��Ч�ʣ�����Ӱ���������ܣ��Ը�Ƶ�ε��ã��˷������ʺϣ�
***************************************************************************/
int config_file_tools::item_get_char(const string& group_name, const string& item_name, char& value,
	const char* const choice_set, const char def_value, const bool group_is_case_sensitive, const bool item_is_case_sensitive)
{
	/* ��������ʵ�� */
	return this->item_get_char(group_name.c_str(), item_name.c_str(), value, choice_set, def_value, group_is_case_sensitive, item_is_case_sensitive);
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�ȡĳ������ݣ���������Ϊint��
  ���������const char* const group_name               ������
		   const char* const item_name                ������
		   int& value                                 ��������int��ֵ������1ʱ���ţ�����0�򲻿��ţ�
		   const int min_value = INT_MIN              : �������ݷ�Χ�����ޣ�Ĭ��ΪINT_MIN
		   const int max_value = INT_MAX              : �������ݷ�Χ�����ޣ�Ĭ��ΪINT_MAX
		   const int def_value = DEFAULT_INT_VALUE    ��������/�����Ƿ�������µ�Ĭ��ֵ���ò�����Ĭ��ֵ DEFAULT_INT_VALUE�����������
															��ֵ��   DEFAULT_INT_VALUE ʱ������0��ֵ�����ţ�
															��ֵ���� DEFAULT_INT_VALUE ʱ����value=def_value������1
		   const bool group_is_case_sensitive = false : �����Ƿ��Сд���У�true-��Сд���� / Ĭ��false-��Сд������
		   const bool item_is_case_sensitive = false  : �����Ƿ��Сд���У�true-��Сд���� / Ĭ��false-��Сд������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int config_file_tools::item_get_int(const char* const group_name, const char* const item_name, int& value,
	const int min_value, const int max_value, const int def_value, const bool group_is_case_sensitive, const bool item_is_case_sensitive)
{
	/* ������ɣ�������Ҫ�ı�return��ֵ */
	int group_num, item_num, index = -1;
	string key, v;
	bool got = false;
	group_num = groups.empty() ? 0 : static_cast<int>(groups.size());
	for (int i = 0;i < group_num;i++) {
		bool equal = false;
		if (group_is_case_sensitive)
			equal = groups[i].group_name == string(group_name);
		else
			equal = cmp_ignore_case(groups[i].group_name, string(group_name));
		if (equal) {
			index = i;
			item_num = groups[index].items.empty() ? 0 : static_cast<int>(groups[index].items.size());
			for (int j = 0;j < item_num;j++) {
				got = get_key_value(groups[index].items[j], key, v);
				if (item_is_case_sensitive)
					equal = key == string(item_name);
				else
					equal = cmp_ignore_case(key, string(item_name));
				if (got && equal) {
					int back_pos = string(v).find(' ');
					if (back_pos != string::npos) {
						v = v.substr(0, back_pos);
					}
					if (stoi(v) >= min_value && stoi(v) <= max_value) {
						value = stoi(v);
						return 1;
					}
				}
			}
		}
	}
	if (def_value != DEFAULT_INT_VALUE) {
		value = def_value;
		return 1;
	}
	return 0;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�����/��ĿΪstring��ʽ������ͬ��
  ���������
  �� �� ֵ��
  ˵    ������Ϊ���ߺ���һ���ڳ����ʼ���׶α����ã������ڳ���ִ���б���Ƶ�ε��ã�
		   �������ֱ���׿ǣ�����΢Ӱ��Ч�ʣ�����Ӱ���������ܣ��Ը�Ƶ�ε��ã��˷������ʺϣ�
***************************************************************************/
int config_file_tools::item_get_int(const string& group_name, const string& item_name, int& value,
	const int min_value, const int max_value, const int def_value, const bool group_is_case_sensitive, const bool item_is_case_sensitive)
{
	/* ��������ʵ�� */
	return this->item_get_int(group_name.c_str(), item_name.c_str(), value, min_value, max_value, def_value, group_is_case_sensitive, item_is_case_sensitive);
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�ȡĳ������ݣ���������Ϊdouble��
  ���������const char* const group_name                  ������
		   const char* const item_name                   ������
		   double& value                                 ��������int��ֵ������1ʱ���ţ�����0�򲻿��ţ�
		   const double min_value = __DBL_MIN__          : �������ݷ�Χ�����ޣ�Ĭ��ΪINT_MIN
		   const double max_value = __DBL_MAX__          : �������ݷ�Χ�����ޣ�Ĭ��ΪINT_MAX
		   const double def_value = DEFAULT_DOUBLE_VALUE ��������/�����Ƿ�������µ�Ĭ��ֵ���ò�����Ĭ��ֵDEFAULT_DOUBLE_VALUE�����������
																��ֵ��   DEFAULT_DOUBLE_VALUE ʱ������0��ֵ�����ţ�
																��ֵ���� DEFAULT_DOUBLE_VALUE ʱ����value=def_value������1
		   const bool group_is_case_sensitive = false     : �����Ƿ��Сд���У�true-��Сд���� / Ĭ��false-��Сд������
		   const bool item_is_case_sensitive = false      : �����Ƿ��Сд���У�true-��Сд���� / Ĭ��false-��Сд������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int config_file_tools::item_get_double(const char* const group_name, const char* const item_name, double& value,
	const double min_value, const double max_value, const double def_value, const bool group_is_case_sensitive, const bool item_is_case_sensitive)
{
	/* ������ɣ�������Ҫ�ı�return��ֵ */
	int group_num, item_num, index = -1;
	string key, v;
	bool got = false;
	group_num = groups.empty() ? 0 : static_cast<int>(groups.size());
	for (int i = 0;i < group_num;i++) {
		bool equal = false;
		if (group_is_case_sensitive)
			equal = groups[i].group_name == string(group_name);
		else
			equal = cmp_ignore_case(groups[i].group_name, string(group_name));
		if (equal) {
			index = i;
			item_num = groups[index].items.empty() ? 0 : static_cast<int>(groups[index].items.size());
			for (int j = 0;j < item_num;j++) {
				got = get_key_value(groups[index].items[j], key, v);
				if (item_is_case_sensitive)
					equal = key == string(item_name);
				else
					equal = cmp_ignore_case(key, string(item_name));
				if (got && equal) {
					int back_pos = string(v).find(' ');
					if (back_pos != string::npos) {
						v = v.substr(0, back_pos);
					}
					if (stod(v) >= min_value && stod(v) <= max_value) {
						value = stod(v);
						return 1;
					}
				}
			}
		}
	}
	if (def_value != DEFAULT_DOUBLE_VALUE) {
		value = def_value;
		return 1;
	}
	return 0;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�����/��ĿΪstring��ʽ������ͬ��
  ���������
  �� �� ֵ��
  ˵    ������Ϊ���ߺ���һ���ڳ����ʼ���׶α����ã������ڳ���ִ���б���Ƶ�ε��ã�
		   �������ֱ���׿ǣ�����΢Ӱ��Ч�ʣ�����Ӱ���������ܣ��Ը�Ƶ�ε��ã��˷������ʺϣ�
***************************************************************************/
int config_file_tools::item_get_double(const string& group_name, const string& item_name, double& value,
	const double min_value, const double max_value, const double def_value, const bool group_is_case_sensitive, const bool item_is_case_sensitive)
{
	/* ��������ʵ�� */
	return this->item_get_double(group_name.c_str(), item_name.c_str(), value, min_value, max_value, def_value, group_is_case_sensitive, item_is_case_sensitive);
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�ȡĳ������ݣ���������Ϊchar * / char []��
  ���������const char* const group_name                  ������
		   const char* const item_name                   ������
		   char *const value                             ��������C��ʽ���ַ���������1ʱ���ţ�����0�򲻿��ţ�
		   const int str_maxlen                          ��ָ��Ҫ������󳤶ȣ���β�㣩
																���<1�򷵻ؿմ�(����DEFAULT_CSTRING_VALUE����Ȼ����������ͬ����Ҫ����defaultֵ���ܻ��)
																���>MAX_STRLEN ������ΪMAX_STRLEN
		   const char* const def_str                     ������������µ�Ĭ��ֵ���ò�����Ĭ��ֵDEFAULT_CSTRING_VALUE�����������
																��ֵ��   DEFAULT_CSTRING_VALUE ʱ������0��ֵ�����ţ�
																��ֵ���� DEFAULT_CSTRING_VALUE ʱ����value=def_value������1��ע�⣬����ֱ��=��
		   const bool group_is_case_sensitive = false : �����Ƿ��Сд���У�true-��Сд���� / Ĭ��false-��Сд������
		   const bool item_is_case_sensitive = false  : �����Ƿ��Сд���У�true-��Сд���� / Ĭ��false-��Сд������
  �� �� ֵ��
  ˵    ����1��Ϊ�򻯣�δ��\"����ת�崦��������ͨ�ַ�
		   2����β�����󳤶�Ϊstr_maxlen������ʱҪ��֤���㹻�ռ�
		   3����� str_maxlen ������ϵͳԤ������� MAX_STRLEN���� MAX_STRLEN ȡ
***************************************************************************/
int config_file_tools::item_get_cstring(const char* const group_name, const char* const item_name, char* const value,
	const int str_maxlen, const char* const def_value, const bool group_is_case_sensitive, const bool item_is_case_sensitive)
{
	/* ������ɣ�������Ҫ�ı�return��ֵ */
	if (str_maxlen < 1) {
		strcpy(value, "\0");
		return 1;
	}
	int group_num, item_num, index = -1;
	string key, v;
	bool got = false;
	group_num = groups.empty() ? 0 : static_cast<int>(groups.size());
	for (int i = 0;i < group_num;i++) {
		bool equal = false;
		if (group_is_case_sensitive)
			equal = groups[i].group_name == string(group_name);
		else
			equal = cmp_ignore_case(groups[i].group_name, string(group_name));
		if (equal) {
			index = i;
			item_num = groups[index].items.empty() ? 0 : static_cast<int>(groups[index].items.size());
			for (int j = 0;j < item_num;j++) {
				got = get_key_value(groups[index].items[j], key, v);
				if (item_is_case_sensitive)
					equal = key == string(item_name);
				else
					equal = cmp_ignore_case(key, string(item_name));
				if (got && equal) {
					int back_pos = string(v).find(' ');
					if (back_pos != string::npos) {
						v = v.substr(0, back_pos);
					}
					if (strlen(v.c_str()) + 1 <= static_cast<size_t>(str_maxlen) && 
						strlen(v.c_str()) + 1 <= static_cast<size_t>(MAX_STRLEN)) {
						strcpy(value, v.c_str());
						return 1;
					}
					else{
						strncpy(value, v.c_str(), min(str_maxlen, MAX_STRLEN));
						value[min(str_maxlen, MAX_STRLEN) -1] = '\0';
						return 1;
					}
				}
			}
		}
	}
	if (strcmp(def_value, DEFAULT_CSTRING_VALUE) != 0) {
		strcpy(value, def_value);
		return 1;
	}
	return 0;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�����/��ĿΪstring��ʽ������ͬ��
  ���������
  �� �� ֵ��
  ˵    ������Ϊ���ߺ���һ���ڳ����ʼ���׶α����ã������ڳ���ִ���б���Ƶ�ε��ã�
		   �������ֱ���׿ǣ�����΢Ӱ��Ч�ʣ�����Ӱ���������ܣ��Ը�Ƶ�ε��ã��˷������ʺϣ�
***************************************************************************/
int config_file_tools::item_get_cstring(const string& group_name, const string& item_name, char* const value,
	const int str_maxlen, const char* const def_value, const bool group_is_case_sensitive, const bool item_is_case_sensitive)

{
	/* ��������ʵ�� */
	return item_get_cstring(group_name.c_str(), item_name.c_str(), value, str_maxlen, def_value, group_is_case_sensitive, item_is_case_sensitive);
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�ȡĳ������ݣ���������Ϊ string ��
  ���������const char* const group_name               ������
		   const char* const item_name                ������
		   string &value                              ��������string��ʽ���ַ���������1ʱ���ţ�����0�򲻿��ţ�
		   const string &def_value                    ������������µ�Ĭ��ֵ���ò�����Ĭ��ֵDEFAULT_STRING_VALUE�����������
															��ֵ��   DEFAULT_STRING_VALUE ʱ������0��ֵ�����ţ�
															��ֵ���� DEFAULT_STRING_VALUE ʱ����value=def_value������1
		   const bool group_is_case_sensitive = false : �����Ƿ��Сд���У�true-��Сд���� / Ĭ��false-��Сд������
		   const bool item_is_case_sensitive = false  : �����Ƿ��Сд���У�true-��Сд���� / Ĭ��false-��Сд������
  �� �� ֵ��
  ˵    ����Ϊ�򻯣�δ��\"����ת�崦��������ͨ�ַ�
***************************************************************************/
int config_file_tools::item_get_string(const char* const group_name, const char* const item_name, string& value,
	const string& def_value, const bool group_is_case_sensitive, const bool item_is_case_sensitive)
{
	/* ������ɣ�������Ҫ�ı�return��ֵ */
	int group_num, item_num, index = -1;
	string key, v;
	bool got = false;
	group_num = groups.empty() ? 0 : static_cast<int>(groups.size());
	for (int i = 0;i < group_num;i++) {
		bool equal = false;
		if (group_is_case_sensitive)
			equal = groups[i].group_name == string(group_name);
		else
			equal = cmp_ignore_case(groups[i].group_name, string(group_name));
		if (equal) {
			index = i;
			item_num = groups[index].items.empty() ? 0 : static_cast<int>(groups[index].items.size());
			for (int j = 0;j < item_num;j++) {
				got = get_key_value(groups[index].items[j], key, v);
				if (item_is_case_sensitive)
					equal = key == string(item_name);
				else
					equal = cmp_ignore_case(key, string(item_name));
				if (got && equal) {
					int back_pos = string(v).find(' ');
					if (back_pos != string::npos) {
						v = v.substr(0, back_pos);
					}
					value = v;
					return 1;
				}
			}
		}
	}
	if (def_value != DEFAULT_STRING_VALUE) {
		value = def_value;
		return 1;
	}
	return 0;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�����/��ĿΪstring��ʽ������ͬ��
  ���������
  �� �� ֵ��
  ˵    ������Ϊ���ߺ���һ���ڳ����ʼ���׶α����ã������ڳ���ִ���б���Ƶ�ε��ã�
		   �������ֱ���׿ǣ�����΢Ӱ��Ч�ʣ�����Ӱ���������ܣ��Ը�Ƶ�ε��ã��˷������ʺϣ�
***************************************************************************/
int config_file_tools::item_get_string(const string& group_name, const string& item_name, string& value,
	const string& def_value, const bool group_is_case_sensitive, const bool item_is_case_sensitive)
{
	/* ��������ʵ�� */
	return this->item_get_string(group_name.c_str(), item_name.c_str(), value, def_value, group_is_case_sensitive, item_is_case_sensitive);
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�ȡĳ������ݣ���������Ϊ IPv4 ��ַ��32bit���ͣ�������
  ���������const char* const group_name               ������
		   const char* const item_name                ������
		   unsigned int &value                        ��������IP��ַ��32λ���ͷ�ʽ������1ʱ���ţ�����0�򲻿��ţ�
		   const unsigned int &def_value              ������������µ�Ĭ��ֵ���ò�����Ĭ��ֵDEFAULT_IPADDR_VALUE�����������
															��ֵ��   DEFAULT_IPADDR_VALUE ʱ������0��ֵ�����ţ�
															��ֵ���� DEFAULT_IPADDR_VALUE ʱ����value=def_value������1
		   const bool group_is_case_sensitive = false : �����Ƿ��Сд���У�true-��Сд���� / Ĭ��false-��Сд������
		   const bool item_is_case_sensitive = false  : �����Ƿ��Сд���У�true-��Сд���� / Ĭ��false-��Сд������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int config_file_tools::item_get_ipaddr(const char* const group_name, const char* const item_name, unsigned int& value,
	const unsigned int& def_value, const bool group_is_case_sensitive, const bool item_is_case_sensitive)
{
	/* ������ɣ�������Ҫ�ı�return��ֵ */
	int group_num, item_num, index = -1;
	string key, v;
	bool got = false;
	group_num = groups.empty() ? 0 : static_cast<int>(groups.size());
	for (int i = 0;i < group_num;i++) {
		bool equal = false;
		if (group_is_case_sensitive)
			equal = groups[i].group_name == string(group_name);
		else
			equal = cmp_ignore_case(groups[i].group_name, string(group_name));
		if (equal) {
			index = i;
			item_num = groups[index].items.empty() ? 0 : static_cast<int>(groups[index].items.size());
			for (int j = 0;j < item_num;j++) {
				got = get_key_value(groups[index].items[j], key, v);
				if (item_is_case_sensitive)
					equal = key == string(item_name);
				else
					equal = cmp_ignore_case(key, string(item_name));
				if (got && equal) {
					int back_pos = string(v).find(' ');
					if (back_pos != string::npos) {
						v = v.substr(0, back_pos);
					}
					if (is_valid_ip(v)) {
						value = get_int_ipaddr(v);
						return 1;
					}
				}
			}
		}
	}
	if (def_value != DEFAULT_IPADDR_VALUE) {
		value = def_value;
		return 1;
	}
	return 0;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�����/��ĿΪstring��ʽ������ͬ��
  ���������
  �� �� ֵ��
  ˵    ������Ϊ���ߺ���һ���ڳ����ʼ���׶α����ã������ڳ���ִ���б���Ƶ�ε��ã�
		   �������ֱ���׿ǣ�����΢Ӱ��Ч�ʣ�����Ӱ���������ܣ��Ը�Ƶ�ε��ã��˷������ʺϣ�
***************************************************************************/
int config_file_tools::item_get_ipaddr(const string& group_name, const string& item_name, unsigned int& value,
	const unsigned int& def_value, const bool group_is_case_sensitive, const bool item_is_case_sensitive)
{
	/* ��������ʵ�� */
	return this->item_get_ipaddr(group_name.c_str(), item_name.c_str(), value, def_value, group_is_case_sensitive, item_is_case_sensitive);
}
