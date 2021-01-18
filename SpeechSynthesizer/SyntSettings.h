#ifndef SYNTSETTINGS_H
#define SYNTSETTINGS_H

#include "DllLoading.h"
#include <map>

typedef std::map<std::string,std::string> SetsBuf;

class SyntSettings : public MbrolaDllLoading
{
public:
	SyntSettings();
	~SyntSettings();
	
	bool SetConfigFile(char *cfgName);
	SetsBuf LoadSets();
	bool SetToDefault();
	SetsBuf CurrentSetInfo();
	std::string ImportSetsFromCfg();
	bool ExportSetsToCfg(int consonantTime, int vowelTime,
							int freq, int percx,
							float duration, float pitch,
							float volume, int voiceFreq);

	std::string GetSetLastLog(){return m_lastLog;}
        std::string GetActConfigName(){return m_configName;}
        std::string GetActConfigPath(){return m_configPath;}

private:
        void InitCfg();
	void LineParse(std::string &line);
	SetsBuf m_syntSets;
	bool m_alreadyImport;
	std::string m_lastLog;
	std::string m_configName;
        std::string m_configPath;
};




#endif //SYNTSETTINGS_H
