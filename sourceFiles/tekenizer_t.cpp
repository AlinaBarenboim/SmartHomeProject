#include "../hFiles/tokenizer_t.h"
#include <string>
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iterator>
using namespace std;


bool Tokenezer_t:: isDelimiter(const char _c) const                          
{
	return (m_delimiter.find(_c) != string::npos);
}

bool Tokenezer_t:: isToken(const char _c) const                          
{
	return (m_tokenList.find(_c) != string::npos);
}

bool Tokenezer_t:: isSpecial(const char _c) const                          
{
	return (m_specialList.find(_c) != string::npos);
}


void Tokenezer_t::skipDelimiter()
{
	while(m_currPos!= m_buffer.end() && isDelimiter(*m_currPos) && !isToken(*m_currPos))
	++m_currPos;
}

string Tokenezer_t::NextToken()
{
	string token;

	if (!(m_buffer.size()))
	{
		return "";
	}

	skipDelimiter();
	
	if (isToken(*m_currPos))
	{
		token+= *m_currPos;
		++m_currPos;
		return token;
	}

	while(m_currPos != m_buffer.end() && !isDelimiter(*m_currPos) && !isToken(*m_currPos))
	{
		if (!isSpecial(*m_currPos))

		{
		       token += *m_currPos;
		}

		++m_currPos;
	}
	return token;
}


const vector<string>& Tokenezer_t::GetTokensList(const string& _string)
{
	m_tokens.clear();
	string token;
	m_buffer = _string;
	m_currPos = m_buffer.begin();

	while(( token = NextToken()) != "")
	{
		m_tokens.push_back(token);
	}

	return m_tokens;
}


