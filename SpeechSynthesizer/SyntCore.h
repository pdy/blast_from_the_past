#ifndef SYNTCORE_H
#define SYNTCORE_H


//#include "DllLoading.h"
#include <string>
#include <vector>
#include <algorithm>
//#include "SyntSettings.h"
#include "WordsExt.h"

typedef std::vector<std::string> SyntBuf;


class SyntCore : public MbrolaDllLoading
{
public:
	SyntCore();
	~SyntCore();

        void SayIt(const char *sentence);
        void Stop();
        void Pause();
        bool Paused(){return pause;}
        bool Stopted(){return stop;}
        bool TextEnded(){return pauseBuff.lastSentWasSaid;}
	std::string GetLastCoreLog(){return m_lastLog;}

        SyntSettings Settings;
        WordsExt extWordsHandle;
	
private:
        SyntBuf FillSyntBuf(std::string &sentence);
        SyntBuf ProcessSyntBuf(SyntBuf &inSyntBuf);
        std::string PhoneticRules(std::string &word);
	std::string TextToSampa(std::string &input);//zamieniamy zwykly tekst na transkrypcje SAMPA
	std::string ToLower(std::string &sentence);//zamieniamy wielkie litery na male
        bool PhonemesSet(SetsBuf &settings, std::string &sampaSentence);//ustawiamy czasy z configa
        std::string TextPrepare(const char *text);

	SyntBuf WordsIsolate(std::string &sentence);//zwraca wektor stringow zawierajacy w komorkach slowa z podanego zdania
	std::string SpellWord(std::string &word);//zwraca lancuch slowa bedacy fonetycznym odpowiednikiem literowania
	bool HasOnlyConsonants(std::string &word);//zwraca true jesli w lancuchu sa same samogloski
        bool IsVowel(char letter);
        bool HasOnlyNumbers(std::string &word);
        std::string SayNumber(std::string &number);

        bool stop;
        bool pause;
        bool lastSentenceBegin;
        struct PauseHandler
        {
            int begIndex;
            SyntBuf syntContent;
            bool lastSentWasSaid;
        }pauseBuff;



	std::string m_lastLog;
	
}static Synth;




#endif // SYNTCORE_H
