#ifndef __TOKENIZER_T_H__
#define __TOKENIZER_T_H__
#include <vector>
#include <string>
#include <iterator>
#include <stdio.h>
using namespace std;


class Tokenezer_t
{
	public:
		Tokenezer_t() :m_delimiter(" ;:,{}"), m_tokenList ("|") , m_specialList ("\r\a\b\f\n\t\v"){};
		~Tokenezer_t(){};
		const vector<string>& GetTokensList(const string& _string);		
	protected:		
	private:
	
		Tokenezer_t(const Tokenezer_t& _tokenizer);
		Tokenezer_t& operator=(const Tokenezer_t& _tokenizer);	
		
		void skipDelimiter();// ignore leading delimiters
   		bool isDelimiter(const char _c) const; // check if the current char is delimiter
		bool isToken(const char _c) const  ;
		bool isSpecial(const char _c) const ;
		
		vector<string> m_tokens;
		string m_buffer;// input string
		string m_token; // output string
		string m_delimiter;// delimiter string
		string::const_iterator m_currPos;
		string m_tokenList;
		string m_specialList;
		string NextToken();
};

#endif
