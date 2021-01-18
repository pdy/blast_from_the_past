#ifndef MBROLADLLLOADING_H
#define MBROLADLLLOADING_H


#include <windows.h>
#include <string>
#include "mbrola.h"
#include "mbrplaydyn.h"

class MbrolaDllLoading
{
public:
	
	enum LoadingState
	{
		LS_LOAD,
		LS_UNLOAD,
		LS_ERROR
	};

	MbrolaDllLoading();
	~MbrolaDllLoading();
	
	bool MbrStart();
	bool MbrClose();

	std::string GetLastLoadLog(){return m_lastLog;}
	LoadingState GetDllState(){return m_loadingState;}
	
protected:
	
	//za³adowanie funckji mbrplay.dll
	bool load_MbrolaPlayDLL();
	void unload_MbrolaPlayDLL();

	//za³adowanie funckji mbrola.dll
	bool load_MbrolaDLL();
	void unload_MbrollaDLL();


	//funkcje mbrola.dll
	HINSTANCE	hinstDllMBR;
	PROCIC		init_MBR;
	PROCICCC	init_rename_MBR;
	PROCIC		write_MBR;
	PROCIV		flush_MBR;
	PROCISI		read_MBR;
	PROCIPVIAT	readType_MBR;
	PROCVV		close_MBR;
	PROCVV		reset_MBR;
	PROCIV		lastError_MBR;
	PROCVCI		lastErrorStr_MBR;
	PROCVI		setNoError_MBR;
	PROCIV		getNoError_MBR;
	PROCVI		setFreq_MBR;
	PROCIV		getFreq_MBR;
	PROCVF		setVolumeRatio_MBR;
	PROCFV		getVolumeRatio_MBR;
	PROCVCI		getVersion_MBR;
	PROCICII	getDatabaseInfo_MBR;
	PROCPPAR	setParser_MBR;
	PROCPPHOCF	init_Phone;
	PROCVPPHO	reset_Phone;
	PROCVPPHO	close_Phone;
	PROCVPPHOFF	appendf0_Phone;
	
	//funckje mbrplay.dll
	HINSTANCE hMbrInst;
	LPLCDCD MBR_Play;
	LPLV MBR_Stop;
	LPLV MBR_WaitForEnd;
	LPLF MBR_SetPitchRatio;
	LPLF MBR_SetDurationRatio;
	LPLL MBR_SetVoiceFreq;
	LPLF MBR_SetVolumeRatio;
	LPFV MBR_GetPitchRatio;
	LPFV MBR_GetDurationRatio;
	LPLV MBR_GetVoiceFreq;
	LPFV MBR_GetVolumeRatio;
	LPLB MBR_SetNoError;
	LPBV MBR_GetNoError;
	LPLC MBR_SetDatabase;
	LPLCCC MBR_SetDatabaseEx;
	LPLTD MBR_GetDatabase;
	LPBV MBR_IsPlaying;
	LPLTD MBR_LastError;
	LPVTD	MBR_GetVersion;
	LPLV MBR_GetDefaultFreq;
	LPLDTD MBR_GetDatabaseInfo;
	LPLTD MBR_GetDatabaseAllInfo;
	LPLTD MBR_RegEnumDatabase;
	LPLED MBR_RegEnumDatabaseCallback;
	LPLCTD MBR_RegGetDatabaseLabel;
	LPLCTD MBR_RegGetDatabasePath;
	LPLV MBR_RegGetDatabaseCount;
	LPLTD MBR_RegGetDefaultDatabase;
	LPLC MBR_RegSetDefaultDatabase;
	LPBCCCBTD MBR_RegisterDatabase;
	LPBCT MBR_UnregisterDatabase;
	LPBV MBR_UnregisterAll;
	LPBCT MBR_DatabaseExist;
	LPBLTD MBR_RegIdxGetDatabaseId;
	LPBLTD MBR_RegIdxGetDatabasePath;
	LPBLTD MBR_RegIdxGetDatabaseLabel;
	LPLC MBR_RegIdxGetDatabaseIndex;
	LPLV MBR_RegIdxGetDefaultDatabase;
	LPDWHW MBR_StartControlPanel;
	LPLDW MBR_SetCallbackMsgBase;
	LPVV MBR_MBRUnload;

private:
	std::string m_lastLog;
        LoadingState m_loadingState;
	
	
};



#endif//MBROLADLLLOADING
