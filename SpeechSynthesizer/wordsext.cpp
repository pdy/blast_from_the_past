//=========================================================
//=                                                       =
//=Implementacja klasy handlujacej baze skrótów, ich      =
//=rozwiniêæ oraz wyrazy ktore wymawiamy i piszemy inaczej=
//=                                                       =
//=========================================================

#include "WordsExt.h"
#include "filestream.h"


using namespace std;

WordsExt::WordsExt()
{
        loaded=0;
        m_content["ERROR"]="NO ERROR";
}
//======================================================
WordsExt::~WordsExt()
{
}
//======================================================
SetsBuf WordsExt::GetBase()
{
        if(loaded)
        {
                return m_content;
        }

        SetsBuf retBuf;
        FileStream stream;

        if(!stream.Open("wordtoword.we",FileStream::READ))
        {
                retBuf["ERROR"]="ERROR opening *.we file";
                return retBuf;
        }
        stream.StreamSeek(0,FileStream::END);
        long fileSize=stream.StreamTell();
        stream.StreamSeek(0,FileStream::BEGIN);
        char *baseContent=new char[fileSize];
        stream.Read(baseContent,fileSize);
        stream.Close();

        string initialism,meaning;
        int i=0;

        while(i!=fileSize)
        {
                if(baseContent[i]=='\r' || baseContent[i]=='\n')
                {
                        ++i;
                        continue;
                }
                while(baseContent[i]!=':')
                {
                        initialism.push_back(baseContent[i]);
                        ++i;
                }
                ++i;
                while(baseContent[i]!='\r' && baseContent[i]!='\n')
                {
                        meaning.push_back(baseContent[i]);
                        ++i;
                }
                ++i;
                retBuf[initialism]=meaning;
                initialism.clear();
                meaning.clear();
        }
        m_content=retBuf;
        loaded=1;
        return retBuf;
}
//======================================================
bool WordsExt::AddRecord(std::string &baseWord, std::string &finalWord)
{

        string newRecord;
        newRecord.append(baseWord);
        newRecord.push_back(':');
        newRecord.append(finalWord);
        newRecord.append("\r\n");

        FileStream stream;
        if(!stream.Open("wordtoword.we",FileStream::READ_WRITE))
        {
                return 0;
        }
        stream.StreamSeek(0,FileStream::END);
        int i=0;
        char chr[1];
        stream.Read(chr,1);
        while(chr[0]=='\n' || chr[0]=='\r')
        {

                stream.StreamSeek(i,FileStream::END);
                stream.Read(chr,1);
                ++i;
        }
        stream.StreamSeek(i,FileStream::END);
        stream.Write(newRecord.c_str(),(newRecord.length()-1));
        stream.Close();
        return 1;

}
//======================================================
void WordsExt::ExtWordsChange(std::string &word)
{
        GetBase();
        SetsBuf::iterator baseContIt=m_content.begin();
        bool hasSpecChr=0;
        char chr;
        size_t wordEnd=word.length()-1;

        if(word[wordEnd]==',' || word[wordEnd]=='!' || word[wordEnd]=='?')
        {
                string temp=word;
                chr=word[wordEnd];
                word.clear();
                int i=0;
                while(temp[i]!=chr)
                {
                        word.push_back(temp[i]);
                        ++i;
                }
                hasSpecChr=1;
        }

        for(baseContIt;baseContIt!=m_content.end();baseContIt++)
        {
                if(word==baseContIt->first)
                {
                        word.clear();
                        word=baseContIt->second;
                        break;
                }
        }
        if(hasSpecChr)
        {
                word.push_back(chr);
        }

}
