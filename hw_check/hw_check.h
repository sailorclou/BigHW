/* 2351044 ������ ������ */
#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <iomanip>
#include <cstring>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <sstream>
#include <iterator>
#include "../include_mariadb_x86/mysql/mysql.h"  
#include "../include/class_aat.h"
#include "../include/class_cft.h"
using namespace std;



enum OPT_ARGS {
	ARGS_HELP = 0,
	ARGS_DEBUD,
	ARGS_ACTION,
	ARGS_CNO,
	ARGS_STU,
	ARGS_FILE,
	ARGS_CAHPTER,
	ARGS_WEEK,
	ARGS_DISPLAY,
	ARGS_CFGFILE,
	ARGS_MAX	//���ڿ���enum���޵����ֵ�������� if (enum_value < ARGS_MAX) ����ʱʹ��
};

const string Action_Name[] = { "base","firstline","secondline","" }; //Ҳ���Ը�����Ҫ������ͷ�ļ����Ա㹲�� 
const string Opt_Args[] = { "--help", "--debug", "--action", "--cno", "--stu", "--file", "--chapter", "--week", "--display", "--cfgfile", ""};

static void usage(const char* const full_procname)
{
	const char* procname = strrchr(full_procname, '\\');
	if (procname == NULL)
		procname = full_procname;

	const int wkey = 7 + strlen(procname) + 1;
	const int wopt = 7 + strlen(procname) + 4;
	cout << endl;

	cout << "Usage: " << procname << " ��ѡ��/��ѡ��" << endl;
	cout << endl;
	cout << setw(wkey) << ' ' << "��ѡ�ָ������" << endl;
	cout << setw(wopt) << ' ' << "--action opname : ֧�ֵ�opname����" << endl;
	cout << setw(wopt) << ' ' << "\t base              : �������(�ļ��Ƿ��ύ���Ƿ񱻸Ķ��������Ƿ���ȷ)" << endl;
	cout << setw(wopt) << ' ' << "\t firstline         : ���м�飨��Դ�����ļ���Ҫ��" << endl;
	cout << setw(wopt) << ' ' << "\t secondline        : ���м�飨������Դ�����ļ���Ҫ��" << endl;

	cout << setw(wkey) << ' ' << "��ѡ�ָ���κ�" << endl;
	cout << setw(wopt) << ' ' << "--cno course_no     : �κ�" << endl;

	cout << setw(wkey) << ' ' << "��ѡ�ָ��ѧ��" << endl;
	cout << setw(wopt) << ' ' << "--stu no/all        : ָ������/ȫ��(7λ����Ϊѧ��,allΪȫ��)" << endl;

	cout << setw(wkey) << ' ' << "��ѡ�ָ���ļ�" << endl;
	cout << setw(wopt) << ' ' << "--file filename/all : �����ļ���/ȫ��(allΪȫ��,����Ϊ�����ļ���)" << endl;

	cout << setw(wkey) << ' ' << "��ѡ�" << endl;
	cout << setw(wopt) << ' ' << "--chapter n         : ��--file�Ļ������ٽ����½ڵ�ɸѡ(��/-1��ȫ���½�,����--week����)" << endl;
	cout << setw(wopt) << ' ' << "--week n            : ��--file�Ļ������ٽ����ܴε�ɸѡ(��/-1��ȫ���ܴ�,����--chapter����)" << endl;
	cout << setw(wopt) << ' ' << "--display xxxxx     : ÿλ0/1�ֱ��ʾ������Ϣ/δ�ύ��Ϣ/������Ϣ/������Ϣ/���ش�����Ϣ" << endl;
	cout << setw(wopt) << ' ' << "--cfgfile filename  : ָ�������ļ���(ȱʡ:hw_check.conf)" << endl;
	cout << endl;

	const char* DEMO_CNO = "10108001";
	const char* DEMO_SRC_FNAME = "12-b1.cpp";
	const char* DEMO_STUNO = "2359999";

	cout << "e.g.   " << procname << " --action base --cno " << DEMO_CNO << " --stu all --file all             : ���" << DEMO_CNO << "����ѧ����������ҵ�Ļ�����Ϣ" << endl;
	cout << "       " << procname << " --action base --cno " << DEMO_CNO << " --stu all --file all --chapter 4 : ���" << DEMO_CNO << "����ѧ���ĵ�4����ҵ�Ļ�����Ϣ" << endl;
	cout << "       " << procname << " --action base --cno " << DEMO_CNO << " --stu all --file all --week 6    : ���" << DEMO_CNO << "����ѧ���ĵ�6����ҵ�Ļ�����Ϣ" << endl;
	cout << "       " << procname << " --action base --cno " << DEMO_CNO << " --stu " << DEMO_STUNO << " --file all         : ���" << DEMO_CNO << "��" << DEMO_STUNO << "ѧ����������ҵ�Ļ�����Ϣ" << endl;
	cout << "       " << procname << " --action base --cno " << DEMO_CNO << " --stu " << DEMO_STUNO << " --file " << DEMO_SRC_FNAME << "   : ���" << DEMO_CNO << "��" << DEMO_STUNO << "ѧ����" << DEMO_SRC_FNAME << "��ҵ�Ļ�����Ϣ" << endl;
	cout << endl;

	cout << "       " << procname << " --action firstline --cno " << DEMO_CNO << " --stu all --file all             : ���" << DEMO_CNO << "����ѧ����������ҵ��������Ϣ" << endl;
	cout << "       " << procname << " --action firstline --cno " << DEMO_CNO << " --stu all --file all --chapter 4 : ���" << DEMO_CNO << "����ѧ���ĵ�4����ҵ��������Ϣ" << endl;
	cout << "       " << procname << " --action firstline --cno " << DEMO_CNO << " --stu all --file all --week 6    : ���" << DEMO_CNO << "����ѧ���ĵ�6����ҵ��������Ϣ" << endl;
	cout << "       " << procname << " --action firstline --cno " << DEMO_CNO << " --stu " << DEMO_STUNO << " --file all         : ���" << DEMO_CNO << "��" << DEMO_STUNO << "ѧ����������ҵ��������Ϣ" << endl;
	cout << "       " << procname << " --action firstline --cno " << DEMO_CNO << " --stu " << DEMO_STUNO << " --file " << DEMO_SRC_FNAME << "   : ���" << DEMO_CNO << "��" << DEMO_STUNO << "ѧ����" << DEMO_SRC_FNAME << "��ҵ��������Ϣ" << endl;
	cout << endl;

	cout << "       " << procname << " --action secondline --cno " << DEMO_CNO << " --stu all --file " << DEMO_SRC_FNAME << " : ���" << DEMO_CNO << "������ѧ����" << DEMO_SRC_FNAME << "��ҵ�Ĵ�����Ϣ" << endl;
	cout << endl;

	cout << "       " << procname << " --cfgfile E:\\test\\my.conf --action base --cno " << DEMO_CNO << " --stu all --file all : ���" << DEMO_CNO << "����ѧ����������ҵ�Ļ�����Ϣ(ָ�������ļ�)" << endl;
	cout << endl;


	cout << endl;
}
int check(const int argc, const char* const* const argv, args_analyse_tools* args);
