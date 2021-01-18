#include "SyntSettings.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include "filestream.h"
using namespace std;

SyntSettings::SyntSettings()
{
        InitCfg();
	m_lastLog="NO ERROR";
	m_syntSets["ERROR"]="NO ERROR";
        MbrStart();

}
//======================================================
SyntSettings::~SyntSettings()
{

        MbrClose();

}
//======================================================
void SyntSettings::InitCfg()
{
    if(m_configPath.length()>0){
        m_configPath.clear();
    }
    if(m_configName.length()>0){
        m_configName.clear();
    }
    FileStream stream;
    FileStream testFile;

    stream.Open("cfgpath",FileStream::READ);
    stream.StreamSeek(0,FileStream::END);
    int length=stream.StreamTell();
    stream.StreamSeek(0,FileStream::BEGIN);
    char *buffer=new char[length];
    stream.Read(buffer,length);
    stream.Close();

    for(int i=0;i<length;i++){
        m_configPath.push_back(buffer[i]);
    }

    if(testFile.Open(m_configPath.c_str(),FileStream::READ))
    {


        if(m_configPath.find('/')==string::npos && m_configPath.find('\\')==string::npos){
            m_configName=m_configPath;
        }
        else
        {
            string temp;
            string::reverse_iterator it=m_configPath.rbegin();

            while(*it!='/' && *it!='\\'){
                temp.push_back(*it);
                ++it;
            }
            it=temp.rbegin();

            while(it!=temp.rend()){
                m_configName.push_back(*it);
                ++it;
            }
        }
        testFile.Close();
    }
    else
    {
        m_configName="";
        m_configPath="";
    }


}

//======================================================
bool SyntSettings::SetConfigFile(char *cfgName)
{
        FileStream testFile;

        if(testFile.Open(cfgName,FileStream::READ))
        {
            FileStream stream;
            stream.Open("cfgpath",FileStream::WRITE);
            stream.Write(cfgName,strlen(cfgName));
            stream.Close();
            testFile.Close();
            InitCfg();
            return 1;
        }
        m_lastLog="File do not exist.";
        return 0;
}
//======================================================
SetsBuf SyntSettings::CurrentSetInfo()
{

	string ret=ImportSetsFromCfg();
        if(ret=="ERROR" || ret=="")
	{
		m_lastLog="Import sets error";
		m_syntSets["ERROR"]=m_lastLog;
	}
	
	return m_syntSets;
}
//======================================================
string SyntSettings::ImportSetsFromCfg()
{
        FileStream inFile;
	string retValue;
        InitCfg();

        if(!inFile.Open(m_configPath.c_str(),FileStream::READ))
	{
		m_lastLog="No config file in directory";
		retValue="ERROR";
                //inFile.Close();
		return retValue;
	}
        inFile.StreamSeek(0,FileStream::END);
        long fileSize=inFile.StreamTell();
        inFile.StreamSeek(0,FileStream::BEGIN);

        if(fileSize==0)
	{
		m_lastLog="Empty config file";
		retValue="ERROR";
                inFile.Close();
		return retValue;
	}

	char *buf=new char[fileSize];
        inFile.Read(buf,fileSize);
        inFile.Close();

	
	for(int i=0;i<fileSize;i++)
	{
		if(buf[i]=='\n' && buf[i-2]=='\n'){i++;}
		retValue.push_back(buf[i]);
		if(i>=fileSize){break;}
	}
	delete[] buf;
	string line;
	int j=0;
	for(;;)
	{
		for(;;)
		{
			if(retValue[j]=='\r' && retValue[j+1]=='\n')
			{
				j+=2;
				break;
			}
			else if(retValue[j]=='\n' || (retValue[j]=='\r' && retValue[j+1]!='\n'))
			{
				++j;
				break;
			}
			else if(j==retValue.length())
			{
				break;
			}
			else
			{
				line.push_back(retValue[j]);
			}
			++j;
		}
		if(line.length()!=0)
		{
			//cout<<line<<endl;
			LineParse(line);
		}	
		if(line[0]=='V'
			&& line[1]=='o'
			&& line[2]=='i')
		{
			line.clear();
			break;
		}
		line.clear();
	}

	/*map<string,string>::iterator it;	
	for(it=m_syntSets.begin();it!=m_syntSets.end();it++)
	{
		cout<<it->first<<" "<<it->second<<endl;
	}*/
	
	return retValue;

}
//======================================================
void SyntSettings::LineParse(string &line)
{
	string setName, setValue;
	
	int i=0;
	while(line[i]!=':')
	{
		setName.push_back(line[i]);
		++i;
	}
	i+=2;
	//cout<<line.length();
	while(i!=line.length())
	{
		setValue.push_back(line[i]);
		++i;
	}
	m_syntSets[setName]=setValue;
}
//======================================================
bool SyntSettings::ExportSetsToCfg(int consonantTime, int vowelTime,
							int freq, int percx,
							float duration, float pitch,
							float volume, int voiceFreq)
{
	ostringstream ossConsTime, ossVowelTime, ossFreq, ossPercX, ossDuration, ossPitch, 
					ossVolume, ossVoiceFreq;

	ossConsTime << consonantTime; 
	ossVowelTime << vowelTime;
	ossFreq << freq;
	ossPercX << percx;
	ossDuration << duration;
	ossPitch << pitch;
	ossVolume << volume;
	ossVoiceFreq << voiceFreq;

	string outBuf="Consonant Time: " + ossConsTime.str() + "\r\n" +
					"Vowel Time: " + ossVowelTime.str() + "\r\n" +
					"PercX: " + ossPercX.str() + "\r\n" +
					"Freq: " + ossFreq.str() + "\r\n" +
					"\r\n" +
					"Duration: " + ossDuration.str() + "\r\n" +
					"Pitch: " + ossPitch.str() + "\r\n" +
					"Volume: " + ossVolume.str() + "\r\n" + 
					"Voice Freq: " + ossVoiceFreq.str();
	
	
        FileStream outFile;


        if(!outFile.Open(m_configPath.c_str(),FileStream::WRITE))
	{
		m_lastLog="Error with cfg opening";
                //outFile.Close();
		return 0;
	}
        outFile.Write(outBuf.c_str(),outBuf.length());
        outFile.Close();
	
	return 1;
}
//======================================================
bool SyntSettings::SetToDefault()
{
        return ExportSetsToCfg(70,140,280,50,1.1,0.7,3,14000);
}

//======================================================
SetsBuf SyntSettings::LoadSets()
{
       // MbrStart();
	CurrentSetInfo();
	if(m_syntSets["ERROR"]!="NO ERROR")
	{
		m_syntSets["ERROR"]=m_lastLog;
		return m_syntSets;
	}
	float duration,pitch,volume;
	int voiceFreq, consTime,vowelTime,freq,percx;

	istringstream issConv(m_syntSets["Consonant Time"]);
	istringstream issVowel(m_syntSets["Vowel Time"]);
	istringstream issFreq(m_syntSets["Freq"]);
	istringstream issPercX(m_syntSets["PercX"]);
	istringstream issDuration(m_syntSets["Duration"]);
	istringstream issVol(m_syntSets["Volume"]);
	istringstream issPitch(m_syntSets["Pitch"]);
	istringstream issVoiceFreq(m_syntSets["Voice Freq"]);

	issConv >> consTime;
	issVowel >> vowelTime;
	issFreq >> freq;
	issPercX >> percx;
	issDuration >> duration;
	issVol >> volume;
	issPitch >> pitch;
	issVoiceFreq >> voiceFreq;
	
	LONG err=0;
    ostringstream ossErrCode;

	err=MBR_SetPitchRatio(pitch);
	if(err!=0)
	{
		ossErrCode << err;
		m_lastLog="SetPitch fail. Error code: " + ossErrCode.str();
		m_syntSets["ERROR"]=m_lastLog;
		return m_syntSets;
	}
	err=MBR_SetDurationRatio(duration);
	if(err!=0)
	{
		ossErrCode << err;
		m_lastLog="SetDuration fail. Error code: " + ossErrCode.str();
		m_syntSets["ERROR"]=m_lastLog;
		return m_syntSets;
	}

	err=MBR_SetVoiceFreq(voiceFreq);
	if(err!=0)
	{
		ossErrCode << err;
		m_lastLog="SetPitch fail. Error code: " + ossErrCode.str();
		m_syntSets["ERROR"]=m_lastLog;
		return m_syntSets;
	}

	err=MBR_SetVolumeRatio(volume);
	if(err!=0)
	{
		ossErrCode << err;
		m_lastLog="SetVolume fail. Error code: " + ossErrCode.str();
		m_syntSets["ERROR"]=m_lastLog;
		return m_syntSets;
	}
	err=MBR_SetNoError(1);
        //MbrClose();
	return m_syntSets;
}
