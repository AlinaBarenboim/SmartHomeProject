#ifndef __READER_H__
#define __READER__H__
#include <cstring>
#include <string>
#include <fstream>
using namespace std;

class Reader
{
public:
	Reader():m_currLineNumber(0), m_fs(0) {};
	~Reader(){if (m_fs) delete m_fs;}
	inline int GetLineNumber()const;
	string GetNextLine();
	inline bool ismoreLines()const;
	void ProcessFile(const string& _fileName);
	inline void ZeroLineNum();

protected:		
private:

	Reader(const Reader& _read);
	Reader& operator=(const Reader& _read);
	int m_currLineNumber;
	ifstream* m_fs;		
};
#endif

inline void Reader:: ZeroLineNum()
{
	m_currLineNumber = 0;
}

inline int Reader:: GetLineNumber()const
{
	return m_currLineNumber;
}

inline bool Reader:: ismoreLines()const
{
	
	return (m_fs) ? !(m_fs->eof()) : false ;
}


