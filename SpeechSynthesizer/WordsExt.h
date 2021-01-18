#ifndef WORDSEXT_H
#define WORDSEXT_H

#include "SyntSettings.h"

class WordsExt
{
public:
	WordsExt();
	~WordsExt();

	SetsBuf GetBase();
	void ExtWordsChange(std::string &word);
	bool AddRecord(std::string &baseWord, std::string &pronunciation);
private:

	bool loaded;
	SetsBuf m_content;
};
#endif//WORDSEXT_H
