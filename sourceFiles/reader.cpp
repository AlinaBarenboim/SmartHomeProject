#include "../hFiles/reader.h"
#include <cstring>
#include <iostream>
#include <stdio.h>
#include <fstream>
using namespace std;

string Reader:: GetNextLine()
{
	string line;
	if (!m_fs->bad() && !m_fs->fail())
	{
		if (!m_fs->eof())
		{
			getline(*m_fs, line);
			m_currLineNumber ++;
			return line;
		}
	}
	
	throw ("error read from file");   
}


void Reader::ProcessFile(const string& _fileName)
{
	if (m_fs)
	{
		delete m_fs;
	} 
	m_fs =  new ifstream (_fileName.c_str());
}

