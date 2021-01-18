#include "SyntCore.h"
//#include <iostream>
#include <locale>
#include "FileStream.h"

using namespace std;


SyntCore::SyntCore()
{
       stop=0;
       pause=0;
       lastSentenceBegin=0;
       pauseBuff.syntContent.push_back("NO CONTENT");
       pauseBuff.lastSentWasSaid=0;
       MbrStart();
}
//======================================================
SyntCore::~SyntCore()
{
        MbrClose();
}
//======================================================
void SyntCore::SayIt(const char *sentence)
{


        stop=0;
        pause=0;
        pauseBuff.lastSentWasSaid=0;
        string input=TextPrepare(sentence);
        if(input.length()==0)
        {
            pauseBuff.lastSentWasSaid=1;
            //lastSentenceBegin=0;
            return;
        }
        SetsBuf settings=Settings.LoadSets();
	
        SyntBuf syntBuffer=FillSyntBuf(input);
	syntBuffer=ProcessSyntBuf(syntBuffer);
        string singleSentence;
	int err;
	for(size_t i=0;i<syntBuffer.size();i++)
	{
                if(i==syntBuffer.size()-1)
                {
                    lastSentenceBegin=1;
                }
                singleSentence=TextToSampa(syntBuffer[i]);
                if(PhonemesSet(settings,singleSentence))
		{
                        if(stop){
                            break;
                        }
                        if(pause)
                        {
                            pauseBuff.begIndex=i;
                            pauseBuff.syntContent=syntBuffer;
                            break;
                        }
                        if(lastSentenceBegin==0)
                        {
                            err=MBR_Play((LPCTSTR)singleSentence.c_str(),MBR_WAIT,NULL,NULL);
                        }
                        else
                        {
                            err=MBR_Play((LPCTSTR)singleSentence.c_str(),MBR_SENTENCE,NULL,NULL);
                            pauseBuff.lastSentWasSaid=1;
                            lastSentenceBegin=0;
                        }

		}
	}

}

//======================================================
void SyntCore::Stop()
{

    if(MBR_IsPlaying())
    {
        stop=1;
        MBR_Stop();
        flush_MBR();
    }
}
//======================================================
void SyntCore::Pause()
{
    if(MBR_IsPlaying())
    {
        pause=1;
    }
    else if(pause)
    {
        pause=0;
    }

    if(!pause && pauseBuff.syntContent[0]!="NO CONTENT")
    {
        string sentence;

         if(pauseBuff.lastSentWasSaid==0)
         {
             for(int i=pauseBuff.begIndex;i<pauseBuff.syntContent.size();i++)
             {
                 sentence.append(pauseBuff.syntContent[i]);
             }
             SayIt(sentence.c_str());
            /* if(sentence==pauseBuff.lastSentence){
                 pauseBuff.lastSentWasSaid=1;
             }*/
         }
    }

}

//======================================================
string SyntCore::TextToSampa(string &input)
{
	string retString;
	string inString=input;
	
        string rawChars="¹æêh³ñœówyŸ¿";// chars need to convert
        string sampaCode[]={"o~","ts'","e~","x","w","n'","s'","u","v","I","z'","Z"};

        string simpleChars="aeoiujpbtgfmlk";//we dont't need to convert them
        string specChars="cdnrsz.!?";//chars which need special action
	
	bool nextIt=0;
	int moveIndex=0;
	for(size_t i=0;i<inString.length();i++)
	{
		i+=moveIndex;
		moveIndex=0;
		nextIt=0;
                for(int j=0;j<rawChars.length();j++)
		{
			if(inString[i]==rawChars[j])
			{
				retString.append(sampaCode[j]);
				nextIt=1;
			}
		}
		
		if(nextIt==0)
		{
                        for(int j=0;j<simpleChars.length();j++)
			{
				if(inString[i]==simpleChars[j])
				{
					retString.push_back(simpleChars[j]);
					nextIt=1;
				}
			}
		}

		if(nextIt==0)
		{
                        for(int j=0;j<specChars.length();j++)
			{
				if(inString[i]==specChars[j])
				{

					if(inString[i]=='c')
					{
						switch(inString[i+1])
						{
						case 'z':
							retString.append("tS");
							++moveIndex;
							break;
						case 'h':
							retString.push_back('x');
							++moveIndex;
							break;
						case 'i':
							retString.append("ts'");
							//++moveIndex;
							break;
						default:
							retString.append("ts");
							break;
						}
					}
					else if(inString[i]=='d')
					{
						switch(inString[i+1])
						{
						case 'z':
							if(inString[i+2]=='i')
							{
								retString.append("dz'");
                                                                ++moveIndex;
							}
							else
							{
								retString.append("dz");
                                                                ++moveIndex;
							}

							break;
						case 'Ÿ':
							retString.append("dz'");
							++moveIndex;
							break;
						case '¿':
							retString.append("dZ");
							++moveIndex;
							break;
						default:
							retString.push_back('d');
							break;
						}
					}
					else if(inString[i]=='n')
					{
						switch(inString[i+1])
						{
						case 'k':
							retString.push_back('N');
                                                        //++moveIndex;
							break;
						case 'i':
							retString.append("n'");
							break;
						default:
							retString.push_back('n');
							break;
						}
					}
					else if(inString[i]=='r')
					{
						switch(inString[i+1])
						{
						case 'z':
							retString.push_back('Z');
							++moveIndex;
							break;
						default:
							retString.push_back('r');
							break;
						}
					}
					else if(inString[i]=='s')
					{
						switch(inString[i+1])
						{
						case 'i':
							retString.append("s'");
							break;
						case 'z':
                                                        if(inString[i-1]=='t'){                                                         
                                                            retString.append("_S");
                                                        }
                                                        else{
                                                            retString.push_back('S');
                                                        }
                                                        ++moveIndex;
							break;
						default:
							retString.push_back('s');
							break;
						}
					}
                                        else if(inString[i]=='z')
                                        {
                                            if(inString[i+1]=='i'){
                                                retString.append("z'");
                                                ++moveIndex;
                                            }
                                            else{
                                                retString.push_back('z');
                                            }
                                        }
                                        else if(inString[i]=='.'
                                                || inString[i]=='!'
                                                || inString[i]=='?')
                                        {
                                            retString.push_back('_');
                                        }
				}
			}
		}
	}				
	return retString;
}
//======================================================
bool SyntCore::PhonemesSet(SetsBuf &settings, string &sentence)
{
	

	if(settings["ERROR"]!="NO ERROR")
	{
		m_lastLog="Sets loading error\n" + settings["ERROR"];
		return 0;
	}
	string vowelSet=settings["Vowel Time"] + " "  + settings["PercX"] + " " + settings["Freq"] + "\n";
	string consSet=settings["Consonant Time"] + " "  + settings["PercX"] + " " + settings["Freq"] + "\n";
	string temp=sentence;
	sentence.clear();

	char vowels[]="aeiIou";
	bool isVowel=0;
	int moveIndex=0;
	for(size_t i=0;i<temp.length();i++)
	{
		i+=moveIndex;
		moveIndex=0;
		isVowel=0;
		for(int j=0;j<6;j++)
		{
			if(temp[i]==vowels[j] && temp[i+1]!='~')
			{
				sentence.push_back(vowels[j]);
				sentence.push_back(' ');
				sentence.append(vowelSet);
				isVowel=1;
			}
			else if(temp[i]==vowels[j] && temp[i+1]=='~')
			{
				sentence.push_back(vowels[j]);
				sentence.append("~ ");
				sentence.append(vowelSet);
				isVowel=1;
				++moveIndex;
                                if(i==temp.length()-1)
                                {
                                    sentence.append("\0 ");
                                    sentence.append(vowelSet);
                                }
			}
		}
		if(isVowel==0)
		{
			if(temp[i]=='t')
			{
				switch(temp[i+1])
				{
				case 'S':

					sentence.append("tS ");
					sentence.append(consSet);
					++moveIndex;
					break;
				case 's':
					if(temp[i+2]=='\'')
					{
						sentence.append("ts' ");
						sentence.append(consSet);
						moveIndex+=2;                                             
					}
					else
					{
						sentence.append("ts ");
						sentence.append(consSet);
						++moveIndex;
					}
					break;
				default:
					sentence.append("t ");
					sentence.append(consSet);
					break;
				}
			}
			else if(temp[i]=='d')
			{
                                if(temp[i+1] == 'z' && temp[i+2]=='\'')
				{
					sentence.append("dz' ");
					sentence.append(consSet);
					moveIndex+=2;                                       
				}
				else if((temp[i+1] == 'z' || temp[i+1] == 'Z') && temp[i+2] != '\'')
				{
					sentence.push_back('d');
					sentence.push_back(temp[i+1]);
					sentence.push_back(' ');
					sentence.append(consSet);
					++moveIndex;
				}
				else
				{
					sentence.append("d ");
					sentence.append(consSet);
				}
			}
			else if(temp[i]=='n')
			{
				if(temp[i+1]=='\'')
				{
					sentence.append("n' ");
					sentence.append(consSet);
					++moveIndex;

				}
				else
				{
					sentence.append("n ");
					sentence.append(consSet);
				}
			}
			else if(temp[i]=='s')
			{
				if(temp[i+1]=='\'')
				{
					sentence.append("s' ");
					sentence.append(consSet);
                                        ++moveIndex;

				}
				else
				{
					sentence.append("s ");
					sentence.append(consSet);
				}
			}
                        else if(temp[i]=='z')
                        {
                                if(temp[i+1]=='\'')
                                {
                                        sentence.append("z' ");
                                        sentence.append(consSet);
                                        ++moveIndex;
                                }
                                else
                                {
                                        sentence.append("z ");
                                        sentence.append(consSet);
                                }
                        }
			else if(temp[i]=='_')
			{
				sentence.append("_ 10 0 0\n");
			}
			else
			{
				sentence.push_back(temp[i]);
				sentence.push_back(' ');
				sentence.append(consSet);
			}
		}
	}

	return 1;
}
//======================================================
bool SyntCore::HasOnlyConsonants(string &word)
{
        string consonants="bcædfghjklmnñprsœtwzŸ¿";
        vector<bool> checkVector;
        //checkVector.reserve(word.length()-1);
        for(int i=0;i<word.length();i++)
        {
            for(int j=0;j<consonants.length();j++)
            {
                if(word[i]==consonants[j]){
                   checkVector.push_back(1);
                   break;
                }
                else if(word[i]!=consonants[j] && j==consonants.length()-1){
                    checkVector.push_back(0);
                }
            }
        }
        int counter=std::count(checkVector.begin(),checkVector.end(),1);
        if(counter==word.length()){
            return 1;
        }
        else{
            return 0;
        }
}
//======================================================
bool SyntCore::IsVowel(char letter)
{
    char *vowels="a¹eêiuóyo";
    for(int i=0;i<9;i++){
        if(letter==vowels[i]){
            return 1;
        }
    }
    return 0;
}
//======================================================
bool SyntCore::HasOnlyNumbers(std::string &word)
{
    string numbers="0123456789";
    vector<bool> checkVector;
    //checkVector.reserve(word.length()-1);
    for(int i=0;i<word.length();i++)
    {
        for(int j=0;j<numbers.length();j++)
        {
            if(word[i]==numbers[j]){
               checkVector.push_back(1);
               break;
            }
            else if(word[i]!=numbers[j] && j==numbers.length()-1){
                checkVector.push_back(0);
            }
        }
    }
    int counter=std::count(checkVector.begin(),checkVector.end(),1);
    if(counter==word.length()){
        return 1;
    }
    else{
        return 0;
    }
}
//======================================================
string SyntCore::SayNumber(std::string &number)
{
    string retSentence;
    char *numbers="0123456789";
    string numberWord[]={"zero","jeden","dwa","trzy","cztery","piêæ","szeœæ","siedem","osiem","dziewiêæ"};
    for(int i=0;i<number.length();i++)
    {
        for(int j=0;j<10;j++)
        {
            if(number[i]==numbers[j])
            {
                retSentence.append(numberWord[j]);
                retSentence.push_back(' ');
                break;
            }
        }
    }
    return retSentence;
}

//======================================================
string SyntCore::ToLower(string &sentence)
{
	string temp=sentence;
	string retString;
	char *uperChars="¥ÆÊ£ÑŒÓ¯";
	char *lowerChars="¹æê³ñœóŸ¿";
	locale loc;
	for (size_t i=0; i<temp.length(); ++i)
	{
		bool nextIt=0;
		for(int j=0;j<9;++j)
		{
			if(temp[i]==uperChars[j])
			{
				retString.push_back(lowerChars[j]);
				nextIt=1;
				break;
			}
		}
		if(nextIt){continue;}
		retString.push_back(tolower(temp[i],loc));
	}
	return retString;
}

//======================================================
SyntBuf SyntCore::FillSyntBuf(std::string &sentence)
{
	SyntBuf retBuf;
	long end=sentence.length()-1;

	if(sentence[end]!='.'
		&&sentence[end]!='?'
		&&sentence[end]!='!')
	{
		sentence.push_back('.');
	}

	if(sentence.find('.')!=string::npos
		|| sentence.find('?')!=string::npos
		|| sentence.find('!')!=string::npos)
	{

		size_t j=0;
		string temp;
		while(j!=sentence.length())
		{
			while(sentence[j]!='.'
				&&sentence[j]!='?'
				&&sentence[j]!='!')
			{
				temp.push_back(sentence[j]);
				++j;
			}
			retBuf.push_back(temp);
			temp.clear();
			++j;
			if(sentence[j]==' '){++j;}

		}
	}
	return retBuf;
}
//======================================================
SyntBuf SyntCore::WordsIsolate(std::string &sentence)
{
	SyntBuf retBuf;
	string temp;
	
	int i=0;
	size_t sentenceEnd=sentence.size()-1;
	int wordsCount=0;

	for(;;)
	{

		while(sentence[i]!=' ' && i!=sentenceEnd)
		{
			temp.push_back(sentence[i]);
			++i;
		}
		++wordsCount;
		retBuf.push_back(temp);
		temp.clear();
		if(i==sentenceEnd)
		{
			--wordsCount;
			retBuf[wordsCount].push_back(sentence[sentenceEnd]);
			break;
		}
		++i;

	}
	return retBuf;

}
//======================================================
string SyntCore::SpellWord(string &word)
{
	string retString;

	for(size_t i=0;i<word.length();i++)
	{	
		if(word[i]=='b')
		{
			retString.append("be");
			continue;
		}
		else if(word[i]=='c')
		{
			retString.append("ce");
			continue;
		}
		else if(word[i]=='d')
		{
			retString.append("de");
			continue;
		}
		else if(word[i]=='f')
		{
			retString.append("ef");
			continue;
		}
		else if(word[i]=='g')
		{
			retString.append("gie");
			continue;
		}
		else if(word[i]=='h')
		{
			retString.append("ha");
			continue;
		}
		else if(word[i]=='j')
		{
			retString.append("jot");
			continue;
		}
		else if(word[i]=='k')
		{
			retString.append("ka");
			continue;
		}
		else if(word[i]=='l')
		{
			retString.append("el");
			continue;
		}
		else if(word[i]=='m')
		{
			retString.append("em");
			continue;
		}
		else if(word[i]=='n')
		{
			retString.append("en");
			continue;
		}
		else if(word[i]=='p')
		{
			retString.append("pe");
			continue;
		}
		else if(word[i]=='r')
		{
			retString.append("er");
			continue;
		}
		else if(word[i]=='s')
		{
			retString.append("es");
			continue;
		}
		else if(word[i]=='t')
		{
			retString.append("te");
			continue;
		}
		else if(word[i]=='w')
		{
                    if((word.length()-1)==0)
                    {
                       retString.append("ww");
                       continue;
                    }
                    else
                    {
                       retString.append("wu");
                       continue;
                    }
		}
                else if(word[i]=='z')
		{

                    if((word.length()-1)==0)
                    {
                       retString.push_back('z');
                       continue;
                    }
                    else
                    {
                       retString.append("zet");
                       continue;
                    }
		}
		else if(word[i]=='Ÿ')
		{
			retString.append("ziet");
			continue;
		}
		else if(word[i]=='¿')
		{
			retString.append("¿et");
			continue;
		}
		else if(word[i]=='x')
		{
			retString.append("iks");
			continue;
		}
		else
		{
			retString.push_back(word[i]);
			if(word[i]!='.' && word[i]!=','
				&& word[i]!='?' && word[i]!='!')
			{
				retString.push_back(word[i]);
			}
		}
	}

	return retString;
	
}
//======================================================
SyntBuf SyntCore::ProcessSyntBuf(SyntBuf &inSyntBuf)
{
	SyntBuf retSyntBuf;
	SyntBuf sentenceWords;	
	for(size_t i=0;i<inSyntBuf.size();i++)
	{
		string temp;
                //inSyntBuf[i]=ToLower(inSyntBuf[i]);
		sentenceWords=WordsIsolate(inSyntBuf[i]);
		
		bool lastWord=0;
		for(size_t j=0;j<sentenceWords.size();j++)
		{
                        if(j==(sentenceWords.size()-1)){
                            lastWord=1;
                        }
                        extWordsHandle.ExtWordsChange(sentenceWords[j]);
                        if(HasOnlyConsonants(sentenceWords[j]))
			{
                                sentenceWords[j]=SpellWord(sentenceWords[j]);
                        }
                        if(HasOnlyNumbers(sentenceWords[j]))
                        {
                            sentenceWords[j]=SayNumber(sentenceWords[j]);
                        }
                        sentenceWords[j]=PhoneticRules(sentenceWords[j]);
			temp.append(sentenceWords[j]);
			if(lastWord)
			{
				temp.push_back('.');
			}
			else
			{
				temp.push_back(' ');
			}
			
		}
		retSyntBuf.push_back(temp);
	}
	return retSyntBuf;
}
//=========================================================
string SyntCore::PhoneticRules(string &word)
{
        string sounds;
	size_t wordEnd=word.length()-1;
	
	bool hasSpecChr=0;
	char chr;
	if(word[wordEnd]==',' || word[wordEnd]=='!' || word[wordEnd]=='?' || word[wordEnd]=='.')
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
		wordEnd=word.length()-1;
	}

	int addIt=0;
	for(size_t i=0;i<word.length();i++)
	{
		i+=addIt;
		addIt=0;

		if(word[i]=='r')
		{
			if(i!=0 && word[i+1]=='z' && 
                                ((word[i-1]=='p' || word[i-1]=='t' || word[i-1]=='k' || word[i-1]=='h') || //trzeba, przygoda, krzew
				  ((word[i-1]=='a' || word[i-1]=='e') && (i+1)==wordEnd))) //murarz, tynkarz, malarz, ¿olnierz, kolnierz
			{
                                sounds.append("sz");
				++addIt;
			}
			else
			{
				sounds.push_back('r');
			}
		}
		else if(word[i]=='w')
		{
			if((i!=0 && 
				(word[i-1]=='s' || word[i+1]=='s'
                                || word[i-1]=='œ' || word[i+1]=='œ'
				|| word[i-1]=='t' || word[i+1]=='t'//swoj, twoj, cwaniak, kwiat itp.
				|| word[i-1]=='c' || word[i+1]=='c'//wsiowy,wtorek,wczoraj,wkurzony, powtórzony itp
                                || word[i-1]=='æ' || word[i+1]=='æ'
                                || word[i-1]=='k' || word[i+1]=='k'
                                || (word[i-1]=='z' && word[i-2]=='s')))
                                || (i==wordEnd && IsVowel(word[i-1])))
			{
				sounds.push_back('f');
				//++addIt;
			}
			else
			{
				sounds.push_back('w');
			}	
		}
                else if(i==wordEnd && IsVowel(word[i-1]) && word[i-1]!='i')
                {
                    string bdg="bdg";
                    string ptk="ptk";
                    bool changed=0;
                    for(int j=0;j<3;j++)
                    {
                        if(word[i]==bdg[j]){
                            sounds.push_back(ptk[j]);
                            changed=1;
                            break;
                        }                                              
                    }
                    if(!changed){
                        sounds.push_back(word[i]);
                    }
                }
		else
		{
                        string softEnableCons="nscz";
                        string softExchangeCons="ñœæŸ";
                        bool wasSoft=0;
                        for(int j=0;j<softEnableCons.length()-1;j++)
                        {
                            if(word[i]==softEnableCons[j]
                               && word[i+1]=='i'
                               && IsVowel(word[i+2]))
                            {
                                sounds.push_back(softExchangeCons[j]);
                                wasSoft=1;
                                ++addIt;
                                break;
                            }                        
                        }
                        if(word[i]=='d' && i!=wordEnd)
                        {
                            if(word[i+1]=='z' && word[i+2]=='i')
                            {
                                sounds.append("dŸ");
                                ++addIt;
                                if(IsVowel(word[i+3])){
                                    ++addIt;
                                }
                                wasSoft=1;
                            }
                        }
                        else if(word[i]=='d' && i==wordEnd)
                        {
                            if(IsVowel(word[i-1])){
                                sounds.push_back('t');
                            }
                            else{
                                sounds.push_back('d');
                            }
                        }
                        if(!wasSoft){
                            if(word[i]=='i' && i!=wordEnd)
                            {
                                string tmp;
                                tmp.push_back(word[i-1]);
                                if(tmp!="z" && HasOnlyConsonants(tmp) && IsVowel(word[i+1])){
                                    sounds.push_back('j');
                                }
                                else{
                                    sounds.push_back('i');
                                }
                            }
                            /*else if(word[i]=='i' && i==wordEnd && word[i-1]=='c'){
                                sounds.append("i");
                            }*/
                            else{                              
                                    sounds.push_back(word[i]);                               
                            }
                        }
		}

		if((i+addIt)==wordEnd){break;}
	}
	
	if(hasSpecChr)
	{
		sounds.push_back(chr);
	}
	return sounds;
}
//=========================================================
string SyntCore::TextPrepare(const char *text)
{
    string input=text;
    string retString="";
    string markers=".!?";

    input=ToLower(input);

    string::iterator it=input.end()-1;
    string itChar;
    itChar.push_back(*it);

    if(!IsVowel(*it) && !HasOnlyConsonants(itChar) && !HasOnlyNumbers(itChar))
    {
        while(!IsVowel(*it) && !HasOnlyConsonants(itChar) &&!HasOnlyNumbers(itChar))
        {
            if(it==input.begin()){
                break;
            }
            --it;
            itChar.clear();
            itChar.push_back(*it);
        }
        if(it!=input.begin())
        {
            string temp;
            string::iterator itBeg=input.begin();
            while(itBeg!=(it+1))
            {
                temp.push_back(*itBeg);
                ++itBeg;
            }
            input.clear();
            input=temp;
        }
        else{
            return retString;
        }
    }

    itChar.clear();
    it=input.begin();
    itChar.push_back(*it);

    if(!IsVowel(*it) && !HasOnlyConsonants(itChar) && !HasOnlyNumbers(itChar))
    {
        while(!IsVowel(*it) && !HasOnlyConsonants(itChar) &&!HasOnlyNumbers(itChar))
        {
            if(it==input.end()){
                break;
            }
            ++it;
            itChar.clear();
            itChar.push_back(*it);
        }
        if(it!=input.end())
        {
            string temp;
            while(it!=input.end())
            {
                temp.push_back(*it);
                ++it;
            }
            input.clear();
            input=temp;
        }
        else{
            return retString;
        }
    }



    for(size_t i=0;i<input.length();i++)
    {
        for(size_t j=0;j<markers.length();j++)
        {
            if(input[i]==markers[j])
            {
                for(size_t it=0;it<markers.length();it++)
                {
                    if(input[i+1]==markers[it])
                    {
                        while(input[i+1]=='.' || input[i+1]=='!' || input[i+1]=='?'){
                            ++i;
                        }
                        break;
                    }
                }
             }         
         }
        retString.push_back(input[i]);
    }

    input.clear();
    input=retString;
    retString.clear();

    for(int i=0;i<input.length();i++)
    {
        string mark;
        mark.push_back(input[i+1]);
        if(input[i]==' ' &&
           !IsVowel(input[i+1]) && !HasOnlyConsonants(mark) && !HasOnlyNumbers(mark))
        {
            ++i;
            mark.clear();
            mark.push_back(input[i]);
            while(!IsVowel(input[i]) && !HasOnlyConsonants(mark) && !HasOnlyNumbers(mark) && input[i]!=' ')
            {
                ++i;
                mark.clear();
                mark.push_back(input[i]);
            }
        }
        retString.push_back(input[i]);
    }


    return retString;
}


