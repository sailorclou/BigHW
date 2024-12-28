/* 2351044 大数据 崔艺洋 */
#include "hw_check.h"
//const char* dbserver = "10.80.42.230";
//const char* dbuser = "hwcheck";
//const char* dbpasswd = "hw_CheCk-For24251*oOP";
//const char* dbname = "homework";

/* 
	基础检查
*/
bool hasExtension(const string& filename, const string& ext)
{
	if (filename.length() < ext.length())
		return false;
	return filename.compare(filename.length() - ext.length(), ext.length(), ext) == 0;
}
int hw_max_length(MYSQL_RES* hw_result, int choice)
{
	int maxLength = 0;
	MYSQL_ROW  hw_row;

	while (hw_row = mysql_fetch_row(hw_result)) {
		string filename(hw_row[5]);
		if (choice &&
			!(hasExtension(filename, ".h") || hasExtension(filename, ".hpp") ||
				hasExtension(filename, ".c") || hasExtension(filename, ".cpp"))) {
			continue;
		}
			int length = strlen(hw_row[5]);
			if (length > maxLength) {
				maxLength = length;
			}
	}

	return maxLength;
}
bool is_PDF(ifstream& file)
{
	char buffer[5] = { 0 };
	file.read(buffer, 4);
	if (strcmp(buffer, "%PDF") == 0) {
		return true;
	}
	return false;
}
//bool is_ASCII(const string& content) 
//{
//	for (unsigned char ch : content) {
//		if (ch > 0x7F) { // ASCII 范围内的字符 0x00 ~ 0x7F
//			return false;
//		}
//	}
//	return true;
//}
bool is_utf8(const string& content)
{/*
	char mark[25];
	strncpy(mark, content.c_str(), 24);*/
	if (strncmp(content.c_str(), "\xEF\xBB\xBF", 3) == 0) {
		return true;
	}
	else {
		return false;
	}
}
// 判断一个字节是否是 UTF-8 的后续字节
bool is_utf8_continuation_byte(unsigned char byte) 
{
	return (byte & 0xC0) == 0x80; // 检查前两位是否为 10
}
bool is_all_english(const string& content)
{
	size_t i = 0;
	while (i < content.size()) {
		unsigned char ch = static_cast<unsigned char>(content[i]);
		if (ch > 0x7F) { // 单字节 ASCII
			return false;
		}
		i++;
	}
	return true;
}
bool is_utf8_encoded(const string& content) 
{
	size_t i = 0;
	if (is_all_english(content)) {
		return false;
	}
	while (i < content.size()) {
		unsigned char byte = static_cast<unsigned char>(content[i]);
		// 1 字节字符 (ASCII 字符)
		if ((byte & 0x80) == 0) {
			i++;
			continue;
		}
		// 2 字节字符
		if ((byte & 0xE0) == 0xC0) {
			if (i + 1 >= content.size() || !is_utf8_continuation_byte(static_cast<unsigned char>(content[i + 1]))) {
				return false; // 无效的 UTF-8 编码
			}
			i += 2;
			continue;
		}
		// 3 字节字符
		if ((byte & 0xF0) == 0xE0) {
			if (i + 2 >= content.size() || !is_utf8_continuation_byte(static_cast<unsigned char>(content[i + 1])) ||
				!is_utf8_continuation_byte(static_cast<unsigned char>(content[i + 2]))) {
				return false; // 无效的 UTF-8 编码
			}
			i += 3;
			continue;
		}
		// 4 字节字符
		if ((byte & 0xF8) == 0xF0) {
			if (i + 3 >= content.size() || !is_utf8_continuation_byte(static_cast<unsigned char>(content[i + 1])) ||
				!is_utf8_continuation_byte(static_cast<unsigned char>(content[i + 2])) ||
				!is_utf8_continuation_byte(static_cast<unsigned char>(content[i + 3]))) {
				return false; // 无效的 UTF-8 编码
			}
			i += 4;
			continue;
		}
		// 非法字节
		return false;
	}

	return true; // 所有字节都符合 UTF-8 编码规则
}

bool is_GB(const string& content) 
{
	size_t i = 0;
	while (i < content.size()) {
		unsigned char ch = content[i];
		if (ch <= 0x7F) { // 单字节 ASCII
			i++;
		}
		else if (ch >= 0x81 && ch <= 0xFE) {
			if (i + 1 >= content.size())
				return false;
			unsigned char next_ch = static_cast<unsigned char>(content[i + 1]);
			if ((next_ch >= 0x40 && next_ch <= 0xFE) && next_ch != 0x7F) {
				i += 2; // 有效的双字节
			}
			else {
				return false;
			}
		}
		//else if (ch >= 0xA1 && ch <= 0xA9) {
		//	// GBK 双字节范围：水准1
		//	if (i + 1 >= content.size())
		//		return false;
		//	unsigned char next_ch = static_cast<unsigned char>(content[i + 1]);
		//	unsigned short hanzi = (ch << 8) + next_ch;
		//	if (hanzi >= 0xA1A1 && hanzi <= 0xA9FE) {
		//		i += 2; // 有效的双字节
		//	}
		//	else {
		//		return false;
		//	}
		//}
		//else if (ch >= 0xB0 && ch <= 0xF7) {
		//	// GBK 双字节范围：水准2
		//	if (i + 1 >= content.size())
		//		return false;
		//	unsigned char next_ch = static_cast<unsigned char>(content[i + 1]);
		//	unsigned short hanzi = (ch << 8) + next_ch;
		//	if (hanzi >= 0xB0A1 && hanzi <= 0xF7FE) {
		//		i += 2; // 有效的双字节
		//	}
		//	else {
		//		return false;
		//	}
		//}
		//else if (ch >= 0x81 && ch <= 0xA0) {
		//	// GBK 双字节范围：水准3
		//	if (i + 1 >= content.size())
		//		return false;
		//	unsigned char next_ch = static_cast<unsigned char>(content[i + 1]);
		//	unsigned short hanzi = (ch << 8) + next_ch;
		//	if ((hanzi >= 0x8140 && hanzi <= 0xA0FE) && next_ch != 0x7F) {
		//		i += 2; // 有效的双字节
		//	}
		//	else {
		//		return false;
		//	}
		//}
		//else if (ch >= 0xAA && ch <= 0xFE) {
		//	// GBK 双字节范围：水准4
		//	if (i + 1 >= content.size()) 
		//		return false; // 双字节不完整
		//	unsigned char next_ch = static_cast<unsigned char>(content[i + 1]);
		//	unsigned short hanzi = (ch << 8) + next_ch;
		//	if ((hanzi >= 0xAA40 && hanzi <= 0xFEA0) && next_ch != 0x7F) {
		//		i += 2; // 有效的双字节
		//	}
		//	else {
		//		return false;
		//	}
		//}
		//else if (ch >= 0xA8 && ch <= 0xA9) {
		//	// GBK 双字节范围：水准5
		//	if (i + 1 >= content.size())
		//		return false; // 双字节不完整
		//	unsigned char next_ch = static_cast<unsigned char>(content[i + 1]);
		//	unsigned short hanzi = (ch << 8) + next_ch;
		//	if ((hanzi >= 0xA840 && hanzi <= 0xA9A0) && next_ch != 0x7F) {
		//		i += 2; // 有效的双字节
		//	}
		//	else {
		//		return false;
		//	}
		//}
		//else if (ch >= 0x81 && ch <= 0xFE) {
		//	// 检查双字节 (0x81-0xFE)
		//	if (i + 1 >= content.size()) {
		//		return false; // 不完整的双字节
		//	}
		//	unsigned char next_ch = content[i + 1];
		//	if ((next_ch >= 0x40 && next_ch <= 0xFE) && next_ch != 0x7F) {
		//		i += 2; // 有效的双字节
		//	}
		//	else {
		//		return false;
		//	}
		//}
		//else if ((ch & 0xE0) == 0xC0) { // 两字节 UTF-8
		//	if (i + 1 >= content.size() || (content[i + 1] & 0xC0) != 0x80) {
		//		//cout << hex << (content[i + 1] & 0xC0);
		//		return false;
		//	}
		//	i += 2;
		//}
		//else if ((ch & 0xF0) == 0xE0) { // 三字节 UTF-8
		//	if (i + 2 >= content.size() ||
		//		(content[i + 1] & 0xC0) != 0x80 || (content[i + 2] & 0xC0) != 0x80) {
		//		return false;
		//	}
		//	i += 3;
		//}
		//else if ((ch & 0xF8) == 0xF0) { // 四字节 UTF-8
		//	if (i + 3 >= content.size() ||
		//		(content[i + 1] & 0xC0) != 0x80 || (content[i + 2] & 0xC0) != 0x80 ||
		//		(content[i + 3] & 0xC0) != 0x80) {
		//		return false;
		//	}
		//	i += 4;
		//}
		else { // 非法 UTF-8 字节
			return false;
		}
	}
	return true;
}
bool isDosFormat(ifstream& file)
{
	string content((istreambuf_iterator<char>(file)),
		istreambuf_iterator<char>());
	size_t i = 0;
	while (i < content.size()) {
		unsigned char byte = static_cast<unsigned char>(content[i]);
		if (byte == '\r' && i + 1 < content.size() && static_cast<unsigned char>(content[i + 1]) != '\n') {
			return false;
		}
		i++;
	}
	return true;
}
bool encode_check(ifstream& file)
{
	
	//bool is_utf8 = false;
	/*unsigned char bom[3];
	file.read(reinterpret_cast<char*>(bom), 3);*/

	//if (bom[0] == 0xEF && bom[1] == 0xBB && bom[2] == 0xBF) {
	//	is_utf8 = true; // UTF-8 BOM
	//}
	//else {
	//	file.seekg(0, ios::beg);
	//}
	// 读取文件内容到字符串
	string content((istreambuf_iterator<char>(file)),
		istreambuf_iterator<char>());
	/*if (is_all_english(content)) {
		return true;
	}*/
	if (is_utf8_encoded(content) && !is_all_english(content)) {
		return false;
	}
	/*if (!is_GB(content)) {
		return false;
	}*/
	return true;
}
string replaceChar(const char* input)
{
	string output(input);
	size_t length = output.length();
	for (size_t i = 0;i < length - 1;i++) {
		if (static_cast<unsigned char>(output[i]) == 161 &&
			static_cast<unsigned char>(output[i + 1]) == 164) {
			// -95 和 -92 在无符号 char 表示中分别是 161 和 164
			output[i] = '.';
			output.erase(i + 1, 1); // 删除下一个字符
			--length; // 调整字符串长度
		}
	}
	return output;
}

/***************************************************************************
  函数名称：
  功    能：基础检查
  输入参数：
  返 回 值：
  说    明：
 ***************************************************************************/
bool base_check(MYSQL_RES* stu_result, MYSQL_RES* hw_result, string file_root)
{
	MYSQL_ROW  stu_row, hw_row;
	unsigned long long hw_num = mysql_num_rows(hw_result);
	int max_len = hw_max_length(hw_result, 0);
	mysql_data_seek(hw_result, 0);
	int i = 0;
	int correct = 0, unsub = 0, pdf_error = 0, gb_encode_error = 0, vs_encode_error = 0;
	int total_correct = 0, total_unsub = 0, total_pdf_error = 0, total_gb_encode_error = 0, total_vs_encode_error = 0;
	int setw_n = 2;
	char* filename = new char[max_len + 1];
	unsigned long stu_num = static_cast<unsigned long>(mysql_num_rows(stu_result));

	// 如果 hw_result 为空，直接输出整体详细信息并返回
	if (hw_num == 0) {
		int setw_n = 2;
		cout << endl;
		cout << "共完成0个学生的检查，文件总数:0，通过总数:0，本次通过0个" << endl;
		cout << setw(setw_n + 7) << setfill('=') << "============" << endl;
		cout << setfill(' ');
		cout << "整体详细信息" << endl;
		cout << setw(setw_n + 7) << setfill('=') << "============" << endl;
		cout << setw(setw_n + 7) << setfill('=') << "============" << endl;
		delete[]filename;
		return 0;
	}

	while ((stu_row = mysql_fetch_row(stu_result)) != NULL) {

		correct = 0, unsub = 0, pdf_error = 0, gb_encode_error = 0, vs_encode_error = 0, setw_n = 2;
		//cout << setiosflags(ios::left) << setw(static_cast<int>(ceil(log10(stu_num)))) << ++i;
		cout << setiosflags(ios::left) << setw(3) << ++i;
		cout << resetiosflags(ios::left);
		cout << ": 学号-" << stu_row[2] << " 姓名-" << replaceChar(stu_row[3]) << " 课号-" << stu_row[7] << " 文件数量-" << hw_num << endl;
		while ((hw_row = mysql_fetch_row(hw_result)) != NULL) {
			strcpy(filename, hw_row[5]);
			cout << "  " << setiosflags(ios::left) << setw(max_len) << filename << " : ";
			cout << resetiosflags(ios::left);
			string filepath = file_root + "/" + stu_row[7] + "-" + stu_row[2] + "/" + filename;
			ifstream file(filepath, ios::in);
			/*if (!file.is_open()) {
				cout << filename << ":[--严重错误--] 不应该的文件打开失败." << endl;
				return false;
			}*/
			if (!file) {
				cout << "未提交" << endl;
				unsub++;
				continue;
			}
			else if (hasExtension(filename, ".pdf") && !is_PDF(file)) {
				cout << "PDF文件格式不正确" << endl;
				pdf_error++;
				file.close();
				continue;
			}
			else if ((hasExtension(filename, ".h") || hasExtension(filename, ".hpp") ||
				hasExtension(filename, ".c") || hasExtension(filename, ".cpp"))) {
				// 检查 DOS 格式
				file.clear();
				file.seekg(0, ios::beg);
				if (!isDosFormat(file)) {
					cout << "源文件格式不正确(VS无法识别)" << endl;
					vs_encode_error++;
					file.close();
					continue;
				}

				// 检查 GB 编码
				file.clear();
				file.seekg(0, ios::beg);
				if (!encode_check(file)) {
					cout << "源文件格式不正确(非GB编码)" << endl;
					gb_encode_error++;
					file.close();
					continue;
				}
			}
			/*else if ((hasExtension(filename, ".h") || hasExtension(filename, ".hpp") ||
				hasExtension(filename, ".c") || hasExtension(filename, ".cpp")) &&
				!isDosFormat(file)) {
				cout << "源文件格式不正确(VS无法识别)" << endl;
				vs_encode_error++;
			}
			else if ((hasExtension(filename, ".h") || hasExtension(filename, ".hpp") ||
				hasExtension(filename, ".c") || hasExtension(filename, ".cpp")) &&
				!encode_check(file)) {
				cout << "源文件格式不正确(非GB编码)" << endl;
				gb_encode_error++;
			}*/
			/*else if (strstr(filename, ".pdf") && strlen(strstr(filename, ".pdf")) == strlen(".pdf") && !is_PDF(file)) {
				cout << "PDF文件格式不正确" << endl;
				pdf_error++;
			}
			else if ((
				strstr(filename, ".h") && strlen(strstr(filename, ".h")) == strlen(".h") ||
				strstr(filename, ".hpp") && strlen(strstr(filename, ".hpp")) == strlen(".hpp") ||
				strstr(filename, ".c") && strlen(strstr(filename, ".c")) == strlen(".c") ||
				strstr(filename, ".cpp") && strlen(strstr(filename, ".cpp")) == strlen(".cpp")
				) && !isDosFormat(file))
			{
				cout << "源文件格式不正确(VS无法识别)" << endl;
				vs_encode_error++;
			}
			else if ((
				strstr(filename, ".h") && strlen(strstr(filename, ".h")) == strlen(".h") ||
				strstr(filename, ".hpp") && strlen(strstr(filename, ".hpp")) == strlen(".hpp") ||
				strstr(filename, ".c") && strlen(strstr(filename, ".c")) == strlen(".c") ||
				strstr(filename, ".cpp") && strlen(strstr(filename, ".cpp")) == strlen(".cpp")
				) && !encode_check(file))
			{
				cout << "源文件格式不正确(非GB编码)" << endl;
				gb_encode_error++;
			}*/
			
				cout << "正确" << endl;
				correct++;
			

			file.close();
		}
		mysql_data_seek(hw_result, 0);
		total_correct += correct;
		total_unsub += unsub;
		total_pdf_error += pdf_error;
		total_gb_encode_error += gb_encode_error;
		total_vs_encode_error += vs_encode_error;

		setw_n = 2;
		if (vs_encode_error)
			setw_n += 31;
		else if (gb_encode_error)
			setw_n += 29;
		else if (pdf_error)
			setw_n += 20;
		else if (unsub)
			setw_n += 9;
		else if (correct)
			setw_n += 7;

		cout << setiosflags(ios::right);
		cout << "检查通过" << correct << "/" << hw_num << "个文件，本次通过" << correct << "个" << endl;
		cout << setw(setw_n + 7) << setfill('-') << "-----" << endl;
		cout << setfill(' ');
		cout << "学生详细信息" << endl;
		cout << setw(setw_n + 7) << setfill('-') << "-----" << endl;
		cout << setfill(' ');

		if (correct) {
			cout << setw(setw_n) << "正确 : ";
			cout << correct << endl;
		}
		if (unsub) {
			cout << setw(setw_n) << "未提交 : ";
			cout << unsub << endl;
		}
		if (pdf_error) {
			cout << setw(setw_n) << "PDF文件格式不正确 : ";
			cout << pdf_error << endl;
		}
		if (vs_encode_error) {
			cout << setw(setw_n) << "源文件格式不正确(VS无法识别) : ";
			cout << vs_encode_error << endl;
		}
		if (gb_encode_error) {
			cout << setw(setw_n) << "源文件格式不正确(非GB编码) : ";
			cout << gb_encode_error << endl;
		}
		cout << setw(setw_n + 7) << setfill('-') << "-----" << endl;
		cout << setfill(' ');
		cout << endl;

		cout << resetiosflags(ios::right);
	}
	cout << endl;

	setw_n = 2;
	if (total_vs_encode_error)
		setw_n += 31;
	else if (total_gb_encode_error)
		setw_n += 29;
	else if (total_pdf_error)
		setw_n += 20;
	else if (total_unsub)
		setw_n += 9;
	else if (total_correct)
		setw_n += 7;

	cout << setiosflags(ios::right);
	cout << "共完成" << i << "个学生的检查，文件总数:" << hw_num * i << "，通过总数:" << total_correct << "，本次通过" << total_correct << "个" << endl;
	cout << setw(setw_n + 7) << setfill('=') << "=====" << endl;
	cout << setfill(' ');	cout << "整体详细信息" << endl;
	cout << setw(setw_n + 7) << setfill('=') << "=====" << endl;
	cout << setfill(' ');	
	if (total_correct) {
		cout << setw(setw_n) << "正确 : ";
		cout << total_correct << endl;
	}
	if (total_unsub) {
		cout << setw(setw_n) << "未提交 : ";
		cout << total_unsub << endl;
	}
	if (total_pdf_error) {
		cout << setw(setw_n) << "PDF文件格式不正确 : ";
		cout << total_pdf_error << endl;
	}
	if (total_vs_encode_error) {
		cout << setw(setw_n) << "源文件格式不正确(VS无法识别) : ";
		cout << total_vs_encode_error << endl;
	}
	if (total_gb_encode_error) {
		cout << setw(setw_n) << "源文件格式不正确(非GB编码) : ";
		cout << total_gb_encode_error << endl;
	}
	cout << setw(setw_n + 7) << setfill('=') << "=====" << endl;
	cout << setfill(' ');
	cout << resetiosflags(ios::right);
	delete[]filename;
	return 0;
}
/*
	首行检查
*/
string trim(const string& line)
{
	size_t start = line.find_first_not_of(" \t\r\n");
	if (start == string::npos) 
		return ""; // 空字符串
	size_t end = line.find_last_not_of(" \t\r\n");
	return line.substr(start, end - start + 1);
}
vector<string> split(const string& str, const string& delimiters = " \t") 
{
	// 预处理：移除注释符，但保留注释内部内容
	string cleaned = str;
	// 移除行注释符 "//"
	if (cleaned.find("//") == 0) {
		cleaned = cleaned.substr(2);
	}
	// 移除块注释符 "/*" 和 "*/"
	else if (cleaned.find("/*") == 0) {
		cleaned = cleaned.substr(2); // 移除开头 "/*"
		size_t end_pos = cleaned.find("*/");
		if (end_pos != string::npos) {
			cleaned = cleaned.substr(0, end_pos); // 移除结尾 "*/"
		}
	}
	// 去掉多余的首尾空格
	cleaned = trim(cleaned);

	vector<string> tokens;
	size_t start = cleaned.find_first_not_of(delimiters), end = 0;
	while (start != string::npos) {
		end = cleaned.find_first_of(delimiters, start);
		tokens.push_back(cleaned.substr(start, end - start));
		start = cleaned.find_first_not_of(delimiters, end);
	}
	return tokens;
}
bool is_annotation(const string& line)
{
	if (line.find("//") == 0) { // 行注释
		return true;
	}
	else if (line.find("/*") == 0 && line.find("*/") != string::npos) { // 块注释放在同一行
		return true;
	}
	else {
		return false;
	}
}
bool anno_format(string line)
{
	if (line.find("//") == 0) {
		return true;
	}
	//多行函数格式
	if (line.find("/*") == 0) {
		if (line.find("*/") == string::npos) {
			return false;
		}
		else if (line.find("*/") + 2 < line.size()) {
			return false;
		}
		return true;
	}
	return true;
}
int anno_item(string line, string stu_no, string stu_name, string stu_class_fname, string stu_class_sname)
{
	vector<string> tokens = split(line); // 按空格/Tab 分隔注释内容
	if (tokens.size() != 3) {
		return -1;
	}
	vector<string> list;
	vector<int> found_item;
	list.push_back(stu_no);
	list.push_back(stu_name);
	list.push_back(stu_class_fname);
	list.push_back(stu_class_sname);
	for (const string& token : tokens) {
		auto it = find(list.begin(), list.end(), token);
		if (it != list.end()) {
			int index = distance(list.begin(), it);
			found_item.push_back(index);
		}
		else {
			vector<string> sname_classes = split(stu_class_sname, "|");
			for (size_t i = 0;i < sname_classes.size();i++) {
				if (token == sname_classes[i]) {
					found_item.push_back(3);
					break;
				}
			}
		}
	}

	bool correct = true;
	if (find(found_item.begin(), found_item.end(), 0) == found_item.end() ||
		find(found_item.begin(), found_item.end(), 1) == found_item.end() ||
		(find(found_item.begin(), found_item.end(), 2) == found_item.end() &&
			find(found_item.begin(), found_item.end(), 3) == found_item.end()
			)
		) {
		correct = false;
		cout << "首行";
	}
	if (find(found_item.begin(), found_item.end(), 0) == found_item.end()) {
		cout << "学号不匹配";
	}
	if (find(found_item.begin(), found_item.end(), 1) == found_item.end()) {
		cout << "姓名不匹配";
	}
	if (find(found_item.begin(), found_item.end(), 2) == found_item.end() &&
		find(found_item.begin(), found_item.end(), 3) == found_item.end()) {
		cout << "班级不匹配";
	}
	return correct ? 0 : -2;
}

bool first_line_check(MYSQL_RES* stu_result, MYSQL_RES* hw_result, string file_root)
{
	MYSQL_ROW  stu_row, hw_row;
	unsigned long long hw_num = mysql_num_rows(hw_result), exclude_file = 0;
	unsigned long long min_exclude = hw_num;
	int max_len = hw_max_length(hw_result, 1);
	mysql_data_seek(hw_result, 0);
	int i = 0;
	int correct = 0, unsub = 0, gb_encode_error = 0, vs_encode_error = 0, anno_format_error = 0, not_anno = 0, not_threeitem = 0, first_line_error = 0;
	int total_correct = 0, total_unsub = 0, total_gb_encode_error = 0, total_vs_encode_error = 0, total_anno_format_error = 0, total_not_anno = 0, total_not_threeitem = 0, total_first_line_error = 0;
	int setw_n = 2;
	char* filename = new char[max_len + 1];
	unsigned long stu_num = static_cast<unsigned long>(mysql_num_rows(stu_result));
	string line;

	// 如果 hw_result 为空，直接输出整体详细信息并返回
	if (hw_num == 0) {
		int setw_n = 2;
		cout << endl;
		cout << "共完成0个学生的检查，文件总数:0，通过总数:0，本次通过0个" << endl;
		cout << setw(setw_n + 7) << setfill('=') << "============" << endl;
		cout << setfill(' ');
		cout << "整体详细信息" << endl;
		cout << setw(setw_n + 7) << setfill('=') << "============" << endl;
		cout << setw(setw_n + 7) << setfill('=') << "============" << endl;
		delete[]filename;
		return 0;
	}

		while ((hw_row = mysql_fetch_row(hw_result)) != NULL) {
			if (!(
				hasExtension(hw_row[5], ".h") || hasExtension(hw_row[5], ".hpp") ||
					hasExtension(hw_row[5], ".c") || hasExtension(hw_row[5], ".cpp")
				))
			{
				exclude_file++;
			}
		}
		mysql_data_seek(hw_result, 0);
	

	while ((stu_row = mysql_fetch_row(stu_result)) != NULL) {
		correct = 0, unsub = 0, gb_encode_error = 0, vs_encode_error = 0, setw_n = 2, anno_format_error = 0, not_anno = 0, not_threeitem = 0, first_line_error = 0;
		//cout << static_cast<int>(floor(log10(stu_num)));
		//cout << setiosflags(ios::left) << setw(static_cast<int>(ceil(log10(stu_num)))) << ++i;
		cout << setiosflags(ios::left) << setw(3) << ++i;
		cout << resetiosflags(ios::left);

		cout << ": 学号-" << stu_row[2] << " 姓名-" << replaceChar(stu_row[3]) << " 课号-" << stu_row[7] << " 文件数量-" << hw_num - exclude_file << endl;
		while ((hw_row = mysql_fetch_row(hw_result)) != NULL) {
			
			if (!(
				hasExtension(hw_row[5], ".h") || hasExtension(hw_row[5], ".hpp") ||
				hasExtension(hw_row[5], ".c") || hasExtension(hw_row[5], ".cpp")
				))
			{
				//exclude_file++;
				continue;
			}
			strcpy(filename, hw_row[5]);
			cout << "  " << setiosflags(ios::left) << setw(max_len) << filename << " : ";
			cout << resetiosflags(ios::left);
			string filepath = file_root + "/" + stu_row[7] + "-" + stu_row[2] + "/" + filename;
			ifstream file(filepath, ios::in | ios::binary);
			/*if (!file.is_open()) {
				cout << filename << ":[--严重错误--] 不应该的文件打开失败." << endl;
				return false;
			}*/
			if (!file) {
				cout << "未提交" << endl;
				unsub++;
				continue;
			}
			else {
				while (1) {
					getline(file, line);
					if (!trim(line).empty()) {
						break;
					}
				}
				line = trim(line);
				int anno = 0;
				file.clear();
				file.seekg(0, ios::beg);

				if ((hasExtension(filename, ".h") || hasExtension(filename, ".hpp") ||
					hasExtension(filename, ".c") || hasExtension(filename, ".cpp"))) {
					// 检查 DOS 格式
					file.clear();
					file.seekg(0, ios::beg);
					if (!isDosFormat(file)) {
						cout << "源文件格式不正确(VS无法识别)" << endl;
						vs_encode_error++;
						file.close();
						continue;
					}

					// 检查 GB 编码
					file.clear();
					file.seekg(0, ios::beg);
					if (!encode_check(file)) {
						cout << "源文件格式不正确(非GB编码)" << endl;
						gb_encode_error++;
						file.close();
						continue;
					}
				}

				if (!anno_format(line)) {
					cout << "首行不是符合要求的/* */格式 [" << line << "]" << endl;
					anno_format_error++;
					file.close();
					continue;
				}
				if (!is_annotation(line)) {
					cout << "首行不是注释行 [" << line << "]" << endl;
					not_anno++;
					file.close();
					continue;
				}
				if ((anno = anno_item(line, stu_row[2], stu_row[3], stu_row[5], stu_row[6])) == -1) {
					cout << "首行不是三项 [" << line << "]" << endl;
					not_threeitem++;
					file.close();
					continue;
				}
				if (anno == -2) {
					cout << " [" << line << "]" << endl;
					first_line_error++;
					file.close();
					continue;
				}
				cout << "正确" << endl;
				correct++;

			}
			file.close();
		}
		mysql_data_seek(hw_result, 0);
		total_correct += correct;
		total_unsub += unsub;
		total_not_anno += not_anno;
		total_gb_encode_error += gb_encode_error;
		total_vs_encode_error += vs_encode_error;
		total_anno_format_error += anno_format_error;
		total_not_threeitem += not_threeitem;
		total_first_line_error += first_line_error;

		setw_n = 2;
		if (vs_encode_error)
			setw_n += 31;
		else if (gb_encode_error)
			setw_n += 29;
		else if (anno_format_error)
			setw_n += 25;
		else if (not_anno)
			setw_n += 17;
		else if (not_threeitem || first_line_error)
			setw_n += 15;
		else if (unsub)
			setw_n += 9;
		else if (correct)
			setw_n += 7;
		
		
		cout << setiosflags(ios::right);
		if (correct == hw_num - exclude_file) {
			cout << "全部通过" << correct << "/" << hw_num - exclude_file << "个文件，本次通过" << correct << "个" << endl;

		}
		else {
			cout << "检查通过" << correct << "/" << hw_num - exclude_file << "个文件，本次通过" << correct << "个" << endl;
		}
		cout << setw(setw_n + 7) << setfill('-') << "-----" << endl;
		cout << setfill(' ');
		cout << "学生详细信息" << endl;
		cout << setw(setw_n + 7) << setfill('-') << "-----" << endl;
		cout << setfill(' ');

		if (correct) {
			cout << setw(setw_n) << "正确 : ";
			cout << correct << endl;
		}
		if (unsub) {
			cout << setw(setw_n) << "未提交 : ";
			cout << unsub << endl;
		}
		if (vs_encode_error) {
			cout << setw(setw_n) << "源文件格式不正确(VS无法识别) : ";
			cout << vs_encode_error << endl;
		}
		if (gb_encode_error) {
			cout << setw(setw_n) << "源文件格式不正确(非GB编码) : ";
			cout << gb_encode_error << endl;
		}
		if (anno_format_error) {
			cout << setw(setw_n) << "首行多行注释格式不正确 : ";
			cout << anno_format_error << endl;
		}
		if (not_anno) {
			cout << setw(setw_n) << "首行不是注释行 : ";
			cout << not_anno << endl;
		}
		if (not_threeitem) {
			cout << setw(setw_n) << "首行不是三项 : ";
			cout << not_threeitem << endl;;
		}
		if (first_line_error) {
			cout << setw(setw_n) << "首行检查出错 : ";
			cout << first_line_error << endl;;
		}
		cout << setw(setw_n + 7) << setfill('-') << "-----" << endl;
		cout << setfill(' ');
		cout << endl;

		cout << resetiosflags(ios::right);
	}
	cout << endl;

	setw_n = 2;
	if (total_vs_encode_error)
		setw_n += 31;
	else if (total_gb_encode_error)
		setw_n += 29;
	else if (total_not_anno)
		setw_n += 17;
	else if (total_not_threeitem || total_first_line_error)
		setw_n += 15;
	else if (total_unsub)
		setw_n += 9;
	else if (total_correct)
		setw_n += 7;

	cout << setiosflags(ios::right);
	cout << "共完成" << i << "个学生的检查，文件总数:" << (hw_num - exclude_file) * i << "，通过总数:" << total_correct << "，本次通过" << total_correct << "个" << endl;
	cout << setw(setw_n + 7) << setfill('=') << "=====" << endl;
	cout << setfill(' ');	
	cout << "整体详细信息" << endl;
	cout << setw(setw_n + 7) << setfill('=') << "=====" << endl;
	cout << setfill(' ');
	if (total_correct) {
		cout << setw(setw_n) << "正确 : ";
		cout << total_correct << endl;
	}
	if (total_unsub) {
		cout << setw(setw_n) << "未提交 : ";
		cout << total_unsub << endl;
	}
	if (total_vs_encode_error) {
		cout << setw(setw_n) << "源文件格式不正确(VS无法识别) : ";
		cout << total_vs_encode_error << endl;
	}
	if (total_gb_encode_error) {
		cout << setw(setw_n) << "源文件格式不正确(非GB编码) : ";
		cout << total_gb_encode_error << endl;
	}
	if (total_anno_format_error) {
		cout << setw(setw_n) << "首行多行注释格式不正确 : ";
		cout << total_anno_format_error << endl;
	}
	if (total_not_anno) {
		cout << setw(setw_n) << "首行不是注释行 : ";
		cout << total_not_anno << endl;
	}
	if (total_not_threeitem) {
		cout << setw(setw_n) << "首行不是三项 : ";
		cout << total_not_threeitem << endl;;
	}
	if (total_first_line_error) {
		cout << setw(setw_n) << "首行检查出错 : ";
		cout << total_first_line_error << endl;;
	}
	cout << setw(setw_n + 7) << setfill('=') << "=====" << endl;
	cout << setfill(' ');
	cout << resetiosflags(ios::right);
	delete[]filename;
	return 0;

}
/*
	次行检查
*/
int info_max_length(MYSQL_RES* stu_result)
{
	int maxLength = 0;
	MYSQL_ROW  stu_row;

	while (stu_row = mysql_fetch_row(stu_result)) {
		int length = strlen(stu_row[2]) + strlen(stu_row[3]) + 1;

		if (length > maxLength) {
			maxLength = length;
		}
	}

	return maxLength;
}
bool secondline_error_info(const string& line, string stu_no, string stu_name, vector<vector<string>>&infos, int num)
{
	vector<string> tokens = split(line);
	for (size_t i = 0;i < ceil(tokens.size());i++) {
		if (tokens[i] == stu_no && i + 1 < tokens.size() && tokens[i + 1] == stu_name) {
			cout << "第[" << (i + 2) / 2 << "]项写了自己，后续内容忽略" << endl;
			return 1;
		}
		if (!(i % 2)) {
			if (i + 1 >= tokens.size()) {
				cout << "第[" << i / 2 << "]个学生后面的信息不全(只读到一项)，后续内容忽略" << endl;
				return 1;
			}
			if (tokens[i].size() != 7) {
				cout << "第" << (i + 2) / 2 << "位同学的学号[" << tokens[i] << "]不是7位，后续内容忽略" << endl;
				return 1;
			}
		}
		if (i % 2) {
			infos[num].push_back(tokens[i - 1] + ' ' + tokens[i]);
		}
	}
	return 0;
}
bool second_line_check(MYSQL_RES* stu_result, MYSQL_RES* hw_result, const string& file_root, const string cno) 
{
	MYSQL_ROW  stu_row, hw_row;
	/*unsigned long long hw_num = mysql_num_rows(hw_result), exclude_file = 0;
	unsigned long long min_exclude = hw_num;
	int max_len = hw_max_length(hw_result, 1);
	mysql_data_seek(hw_result, 0);
	
	unsigned long stu_num = static_cast<unsigned long>(mysql_num_rows(stu_result));
	hw_row = mysql_fetch_row(hw_result);*/
	
	hw_row = mysql_fetch_row(hw_result);
	unsigned long stu_num = static_cast<unsigned long>(mysql_num_rows(stu_result));
	char* filename = new char[strlen(hw_row[5]) + 1];
	strcpy(filename, hw_row[5]);
	string line;
	int max_len = info_max_length(stu_result);
	vector<int> if_valid(stu_num, 0);
	vector<vector<string>> infos(stu_num);
	vector<vector<string>> stus(stu_num, vector<string>(3));
	
	
	cout << "课号 : " << cno << " 学生数量 : " << stu_num << " 源文件名 : " << hw_row[5] <<endl;
	int i = 0;
	int setw_n = 2;
	int correct = 0, unsub = 0, gb_encode_error = 0, vs_encode_error = 0, anno_format_error = 0, not_anno = 0;

	mysql_data_seek(stu_result, 0);

	//单文件检查
	while ((stu_row = mysql_fetch_row(stu_result)) != NULL) {
		cout << setiosflags(ios::left) << setw(3) << ++i;
		cout << ": " << setw(max_len) << string(stu_row[2]) + "/" + string(replaceChar(stu_row[3])) << " : ";
		stus[i - 1][0] = string(stu_row[2]);
		stus[i - 1][1] = string(stu_row[3]);
		stus[i - 1][2] = string(stu_row[7]);
		cout << resetiosflags(ios::left);

		string filepath = file_root + "/" + stu_row[7] + "-" + stu_row[2] + "/" + filename;
		ifstream file(filepath, ios::in | ios::binary);
		/*if (!file.is_open()) {
			cout << filename << ":[--严重错误--] 不应该的文件打开失败." << endl;
			return false;
		}*/
		if (!file) {
			cout << "未提交" << endl;
			unsub++;
			continue;
		}
		else {
			while (1) {
				getline(file, line);
				if (!trim(line).empty()) {
					break;
				}
			}
			while (1) {
				getline(file, line);
				if (!trim(line).empty()) {
					break;
				}
			}
			line = trim(line);
			
			//int anno = 0;

			// 检查 DOS 格式
			file.clear();
			file.seekg(0, ios::beg);
			if (!isDosFormat(file)) {
				cout << "源文件格式不正确(VS无法识别)" << endl;
				vs_encode_error++;
				file.close();
				continue;
			}

			// 检查 GB 编码
			file.clear();
			file.seekg(0, ios::beg);
			if (!encode_check(file)) {
				cout << "源文件格式不正确(非GB编码)" << endl;
				gb_encode_error++;
				file.close();
				continue;
			}
			/*if (!anno_format(line)) {
				cout << "首行不是符合要求的格式 [" << line << "]" << endl;
				anno_format_error++;
				file.close();
				continue;
			}*/
			if (!is_annotation(line)) {
				cout << "次行不是注释" << endl;
				not_anno++;
				file.close();
				continue;
			}
			if (secondline_error_info(line, stu_row[2], stu_row[3], infos, i-1)) {
				correct++;
				if_valid[i - 1] = 1;
				continue;
			}
			cout << "正确" << endl;
			correct++;
			if_valid[i - 1] = 1;
		}
		file.close();
	}
	setw_n = 2;
	if (vs_encode_error)
		setw_n += 31;
	else if (gb_encode_error)
		setw_n += 29;
	else if (anno_format_error)
		setw_n += 25;
	else if (not_anno)
		setw_n += 15;
	else if (unsub)
		setw_n += 9;
	else if (correct)
		setw_n += 7;

	cout << endl;
	cout << setiosflags(ios::right);
	if (correct == stu_num) {
		cout << "全部通过" << correct << "/" << stu_num << "个学生，本次通过" << correct << "个" << endl;

	}
	else {
		cout << "检查通过" << correct << "/" << stu_num << "个学生，本次通过" << correct << "个" << endl;
	}
	cout << setw(setw_n + 7) << setfill('=') << "====" << endl;
	cout << setfill(' ');
	cout << "详细信息" << endl;
	cout << setw(setw_n + 7) << setfill('=') << "====" << endl;
	cout << setfill(' ');

	if (correct) {
		cout << setw(setw_n) << "正确 : ";
		cout << correct << endl;
	}
	if (unsub) {
		cout << setw(setw_n) << "未提交 : ";
		cout << unsub << endl;
	}
	if (vs_encode_error) {
		cout << setw(setw_n) << "源文件格式不正确(VS无法识别) : ";
		cout << vs_encode_error << endl;
	}
	if (gb_encode_error) {
		cout << setw(setw_n) << "源文件格式不正确(非GB编码) : ";
		cout << gb_encode_error << endl;
	}
	/*if (anno_format_error) {
		cout << setw(setw_n) << "首行多行注释格式不正确 : ";
		cout << anno_format_error << endl;
	}*/
	if (not_anno) {
		cout << setw(setw_n) << "次行不是注释 : ";
		cout << not_anno << endl;
	}
	/*if (not_threeitem) {
		cout << setw(setw_n) << "首行不是三项 : ";
		cout << not_threeitem << endl;;
	}*/
	/*if (first_line_error) {
		cout << setw(setw_n) << "首行检查出错 : ";
		cout << first_line_error << endl;;
	}*/
	cout << setw(setw_n + 7) << setfill('=') << "====" << endl;
	cout << setfill(' ');
	cout << endl;

	cout << resetiosflags(ios::right);

	//交叉检查
	cout << "交叉检查结果：" << endl;

	mysql_data_seek(stu_result, 0);
	size_t j = 0;
	for (size_t a = 0;a < stu_num;a++) {
		string current_stu_no = stus[a][0], current_stu_name = stus[a][1], current_stu_cno = stus[a][2];

		cout << setiosflags(ios::left) << setw(3) << j + 1;
		cout << ": " << current_stu_cno << "-" << current_stu_no << "-" << current_stu_name << endl;
		cout << resetiosflags(ios::left);

		if (!if_valid[j]) {
			j++;
			continue;
		}


		for (size_t k = 0; k < infos[j].size(); k++) {
			size_t space_pos = infos[j][k].find(' ');

			string other_stu_no = infos[j][k].substr(0, space_pos);
			string other_stu_name = infos[j][k].substr(space_pos + 1);

			bool found1 = false, found10 = true;

			int p = 0;
			for (size_t b = 0;b < stu_num;b++) {
				if (other_stu_no == stus[b][0] && other_stu_name == stus[b][1]) {
					found1 = true;
					break;
				}
				if (other_stu_no == stus[b][0] && other_stu_name != stus[b][1]) {
					cout << "\t" << other_stu_no << " " << other_stu_name << "\t对方姓名不正确" << endl;
					found1 = false;
					found10 = false;
					break;
				}
				/*if (other_stu_no != stus[b][0] && other_stu_name == stus[b][1]) {
					cout << "\t" << other_stu_no << " " << other_stu_name << "\t对方学号不正确" << endl;
					found1 = false;
					found10 = false;
					break;
				}*/
				p++;
			}
			if (!found1 && found10) {
				cout << "\t" << other_stu_no << " " << other_stu_name << "\t对方学号不存在" << endl;
				continue;
			}
			else if (!found1) {
				continue;
			}
			

			bool found2 = false;
			string no, name;
			for (size_t n = 0; n < infos[p].size(); n++) {
				size_t pos = infos[p][n].find(' ');
				if (pos == string::npos)
					continue;
				string no(infos[p][n].substr(0, pos)), name(infos[p][n].substr(pos + 1));

				if (current_stu_no == no && current_stu_name == name) {
					found2 = true;
					cout << "\t" << other_stu_no << " " << other_stu_name << endl;
					break;
				}
				if (current_stu_no == no && current_stu_name != name) {
					cout << "\t" << other_stu_no << " " << other_stu_name << "\t没写对你名字" << endl;
					found2 = true;
					break;
				}
				/*if (current_stu_no != no && current_stu_name == name) {
					cout << "\t" << other_stu_no << " " << other_stu_name << "\t没写对你学号" << endl;
					found2 = true;
					break;
				}*/
			}
			if (found2)
				continue;
			else {
				cout << "\t" << other_stu_no << " " << other_stu_name << "\t抛弃了你" << endl;
			}
		}

		j++;

	}

	delete[]filename;
	return 0;
}



int check(const int argc, const char* const* const argv, args_analyse_tools* args)
{
	string dbserver, dbuser, dbpasswd, dbname, file_root;

	if (args[ARGS_HELP].existed()) {
		usage(argv[0]);
		return 0;
	}
	if (args[ARGS_DEBUD].existed()) {

	}
	if (args[ARGS_DISPLAY].existed()) {

	}
	//参数检查
	if (!args[ARGS_ACTION].existed()) {
		cout << "参数[" << args[ARGS_ACTION].get_name() << "]必须指定." << endl;
		return -1;
	}
	if (!args[ARGS_CNO].existed()) {
		cout << "参数[" << args[ARGS_CNO].get_name() << "]必须指定." << endl;
		return -1;
	}
	if (!args[ARGS_STU].existed()) {
		cout << "参数[" << args[ARGS_STU].get_name() << "]必须指定." << endl;
		return -1;
	}
	if (!args[ARGS_FILE].existed()) {
		cout << "参数[" << args[ARGS_FILE].get_name() << "]必须指定." << endl;
		return -1;
	}
	//取值
	string action = args[ARGS_ACTION].get_string(), cno = args[ARGS_CNO].get_string(),
		   stu = args[ARGS_STU].get_string(), file = args[ARGS_FILE].get_string(),
		   cfgfile = args[ARGS_CFGFILE].get_string();

	int chapter = -1, week = -1;
	//if (file == string("all")) {
		if (args[ARGS_CAHPTER].existed()) {
			chapter = args[ARGS_CAHPTER].get_int();
		}
		if (ARGS_WEEK) {
			week = args[ARGS_WEEK].get_int();
		}
	//}
	if (args[ARGS_CFGFILE].existed()) {
		cfgfile = args[ARGS_CFGFILE].get_string();
	}
	config_file_tools sCfg(cfgfile, BREAK_CTYPE::Equal);
	if (sCfg.is_read_succeeded() == 0) {
		cout << "配置文件[" << cfgfile << "]读取不成功" << endl;
		return -1;
	}
	sCfg.item_get_string("[数据库]", "db_host", dbserver);
	sCfg.item_get_string("[数据库]", "db_username", dbuser);
	sCfg.item_get_string("[数据库]", "db_passwd", dbpasswd);
	sCfg.item_get_string("[数据库]", "db_name", dbname);
	sCfg.item_get_string("[文件目录]", "src_rootdir", file_root);
	

	MYSQL* mysql;
	MYSQL_RES* stu_result, *hw_result;
	//MYSQL_ROW  row;
	//MYSQL_FIELD* field;

	/* 初始化 mysql 变量，失败返回NULL */
	if ((mysql = mysql_init(NULL)) == NULL) {
		cout << "mysql_init failed" << endl;
		return -1;
	}

	/* 连接数据库，失败返回NULL
		1、mysqld没运行
		2、没有指定名称的数据库存在 */
	if (mysql_real_connect(mysql, dbserver.c_str(), dbuser.c_str(), dbpasswd.c_str(), dbname.c_str(), 0, NULL, 0) == NULL) {
		cout << "mysql_real_connect failed(" << mysql_error(mysql) << ")" << endl;
		return -1;
	}

	string query;
	/* 学生信息查询 */
	query = "select * from view_hwcheck_stulist where stu_cno in(" + cno + ")";
	if (stu == string("all")) {
		if (mysql_query(mysql, query.c_str())) {
			cout << "mysql_query failed(" << mysql_error(mysql) << ")" << endl;
			return -1;
		}
	}
	else {
		query += " and stu_no = \"" + stu + "\"";
		//cout << query.c_str();
		if (mysql_query(mysql, query.c_str())) {
			cout << "mysql_query failed(" << mysql_error(mysql) << ")" << endl;
			return -1;
		}
	}
	
	if ((stu_result = mysql_store_result(mysql)) == NULL) {
		cout << "mysql_store_result failed" << endl;
		return -1;
	}
	unsigned long long stu_num = mysql_num_rows(stu_result);

	/*while ((field = mysql_fetch_field(stu_result)) != NULL) {
		cout << field->name << endl;
	}*/
	/* 作业信息查询 */
	query = "select * from view_hwcheck_hwlist where hw_cno in(" + cno + ")";
	if (chapter != -1) {
		query += " and hw_chapter = \"" + to_string(chapter) + "\"";
	}
	if (week != -1) {
		query += " and hw_week = \"" + to_string(week) + "\"";
	}
	if (file != string("all")) {
		query += " and hw_filename = \"" + file + "\"";
	}
	if (mysql_query(mysql, query.c_str())) {
		cout << "mysql_query failed(" << mysql_error(mysql) << ")" << endl;
		return -1;
	}
	if ((hw_result = mysql_store_result(mysql)) == NULL) {
		cout << "mysql_store_result failed" << endl;
		return -1;
	}
	//
	// 
	
	//while ((row = mysql_fetch_row(stu_result)) != NULL) {
	//	cout << setiosflags(ios::left);           //输出左对齐
	//	cout << setw(3) << row[0];    //宽度12位，左对齐
	//	cout << setw(10) << row[1];     //    8
	//	cout << setw(8) << row[2];     //    4
	//	cout << setw(8) << row[3];     //    4，目前是字符串形式，也可以用atoi(row[3])输出int型的年龄
	//	cout << setw(8) << row[4];     //    4
	//	cout << setw(10) << row[5];     //    4，目前是字符串形式，也可以用atoi(row[3])输出int型的年龄
	//	cout << setw(5) << row[6];
	//	//cout << row[7];
	//	cout << endl;
	//}
	//while ((row = mysql_fetch_row(hw_result)) != NULL) {
	//	cout << setiosflags(ios::left);           //输出左对齐
	//	cout <<  setw(3) << row[0];    //宽度12位，左对齐
	//	cout <<  setw(10) << row[1];     //    8
	//	cout <<  setw(8) << row[2];     //    4
	//	cout <<  setw(8) << row[3];     //    4，目前是字符串形式，也可以用atoi(row[3])输出int型的年龄
	//	cout <<  setw(8) << row[4];     //    4
	//	cout << setw(10) << row[5];     //    4，目前是字符串形式，也可以用atoi(row[3])输出int型的年龄
	//	cout << setw(5) << row[6];
	//	//cout << row[7];
	//	cout << endl;
	//}
	//cout << endl;


	//检查
	if (action == string("base")) {
		base_check(stu_result, hw_result, file_root);
	}
	else if (action == string("firstline")) {
		first_line_check(stu_result, hw_result, file_root);
	}
	else if (action == string("secondline")) {
		second_line_check(stu_result, hw_result, file_root, cno);
	}
	//输出查询信息


	cout << endl;
	return 0;
	//int i = 0;
	//args_analyse_tools arg;
	//string arg_name;
	//while (!((arg_name = ((arg = args[i++]).get_name())).empty())) {
	//	if (!arg.existed()) {
	//		continue;
	//	}
	//	if (arg_name == string("--help")) {
	//		usage(argv[0]);
	//	}
	//	else if (arg_name == string("--debug")){
	//	}
	//	else if (arg_name == string("--action")) {
	//		string action = arg.get_string();
	//		if (action == string("base")) {

	//		}
	//		else if (action == string("firstline")) {

	//		}
	//		else if (action == string("secondline")) {

	//		}
	//	}
	//	else if (arg_name == string("--display")) {
	//	}
	//}
}