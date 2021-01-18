#include "DllLoading.h"

using namespace std;

MbrolaDllLoading::MbrolaDllLoading()
{
	m_loadingState=LS_UNLOAD;
	m_lastLog="No action detected";


}
//======================================================
MbrolaDllLoading::~MbrolaDllLoading()
{


}

//======================================================


bool MbrolaDllLoading::load_MbrolaDLL()
{

        if (!(hinstDllMBR=LoadLibrary(L"mbrola.dll"))){
		return FALSE;}
	init_MBR			=(PROCIC) GetProcAddress(hinstDllMBR,"init_MBR");
	init_rename_MBR		=(PROCICCC) GetProcAddress(hinstDllMBR,"init_rename_MBR");
	write_MBR			=(PROCIC) GetProcAddress(hinstDllMBR,"write_MBR");
	flush_MBR			=(PROCIV) GetProcAddress(hinstDllMBR,"flush_MBR");
	read_MBR			=(PROCISI) GetProcAddress(hinstDllMBR,"read_MBR");
	readType_MBR		=(PROCIPVIAT) GetProcAddress(hinstDllMBR,"readtype_MBR");
	close_MBR			=(PROCVV) GetProcAddress(hinstDllMBR,"close_MBR");
	reset_MBR			=(PROCVV) GetProcAddress(hinstDllMBR,"reset_MBR");
	lastError_MBR		=(PROCIV) GetProcAddress(hinstDllMBR,"lastError_MBR");
	lastErrorStr_MBR	=(PROCVCI) GetProcAddress(hinstDllMBR,"lastErrorStr_MBR");
	setNoError_MBR		=(PROCVI) GetProcAddress(hinstDllMBR,"setNoError_MBR");
	getNoError_MBR		=(PROCIV) GetProcAddress(hinstDllMBR,"getNoError_MBR");
	setFreq_MBR			=(PROCVI) GetProcAddress(hinstDllMBR,"setFreq_MBR");
	getFreq_MBR			=(PROCIV) GetProcAddress(hinstDllMBR,"getFreq_MBR");
	setVolumeRatio_MBR	=(PROCVF) GetProcAddress(hinstDllMBR,"setVolumeRatio_MBR");
	getVolumeRatio_MBR	=(PROCFV) GetProcAddress(hinstDllMBR,"getVolumeRatio_MBR");
	getVersion_MBR		=(PROCVCI) GetProcAddress(hinstDllMBR,"getVersion_MBR");
	getDatabaseInfo_MBR	=(PROCICII) GetProcAddress(hinstDllMBR,"getDatabaseInfo_MBR");
	setParser_MBR		=(PROCPPAR) GetProcAddress(hinstDllMBR,"setParser_MBR");
	init_Phone			=(PROCPPHOCF) GetProcAddress(hinstDllMBR,"init_Phone");
	reset_Phone			=(PROCVPPHO) GetProcAddress(hinstDllMBR,"reset_Phone");
	close_Phone			=(PROCVPPHO) GetProcAddress(hinstDllMBR,"close_Phone");
	appendf0_Phone		=(PROCVPPHOFF) GetProcAddress(hinstDllMBR,"appendf0_Phone");

	if ((!init_MBR)
		|| (!init_rename_MBR)
		|| (!write_MBR)
		|| (!flush_MBR)
		|| (!read_MBR)
		|| (!readType_MBR)
		|| (!close_MBR)
		|| (!reset_MBR)
		|| (!lastError_MBR)
		|| (!lastErrorStr_MBR)
		|| (!setNoError_MBR)
		|| (!getNoError_MBR)
		|| (!setFreq_MBR)
		|| (!getFreq_MBR)
		|| (!setVolumeRatio_MBR)
		|| (!getVolumeRatio_MBR)
		|| (!getVersion_MBR)
		|| (!getDatabaseInfo_MBR)
		|| (!setParser_MBR)
		|| (!init_Phone)
		|| (!reset_Phone)
		|| (!close_Phone)
		|| (!appendf0_Phone))
	{
    	FreeLibrary (hinstDllMBR); 
		hinstDllMBR=NULL;
		return FALSE;
	}
	return TRUE;
}
//======================================================
void MbrolaDllLoading::unload_MbrollaDLL()
{
	if (hinstDllMBR)
	{
		FreeLibrary (hinstDllMBR);
		hinstDllMBR=NULL;
	}
}
//======================================================
bool MbrolaDllLoading::load_MbrolaPlayDLL()
{
	
        if (!(hMbrInst=LoadLibrary(L"mbrplay.dll"))){
		return FALSE;}
	
	MBR_Play=(LPLCDCD) GetProcAddress(hMbrInst,"_MBR_Play@16");
	MBR_Stop=(LPLV) GetProcAddress(hMbrInst,"_MBR_Stop@0");
	MBR_WaitForEnd=(LPLV) GetProcAddress(hMbrInst,"_MBR_WaitForEnd@0");
	MBR_SetPitchRatio=(LPLF) GetProcAddress(hMbrInst,"_MBR_SetPitchRatio@4");
	MBR_SetDurationRatio=(LPLF) GetProcAddress(hMbrInst,"_MBR_SetDurationRatio@4");
	MBR_SetVoiceFreq=(LPLL) GetProcAddress(hMbrInst,"_MBR_SetVoiceFreq@4");
	MBR_SetVolumeRatio=(LPLF) GetProcAddress(hMbrInst,"_MBR_SetVolumeRatio@4");
	MBR_GetPitchRatio=(LPFV) GetProcAddress(hMbrInst,"_MBR_GetPitchRatio@0");
	MBR_GetDurationRatio=(LPFV) GetProcAddress(hMbrInst,"_MBR_GetDurationRatio@0");
	MBR_GetVoiceFreq=(LPLV) GetProcAddress(hMbrInst,"_MBR_GetVoiceFreq@0");
	MBR_GetVolumeRatio=(LPFV) GetProcAddress(hMbrInst,"_MBR_GetVolumeRatio@0");
	MBR_SetNoError=(LPLB) GetProcAddress(hMbrInst,"_MBR_SetNoError@4");
	MBR_GetNoError=(LPBV) GetProcAddress(hMbrInst,"_MBR_GetNoError@0");
	MBR_SetDatabase=(LPLC) GetProcAddress(hMbrInst,"_MBR_SetDatabase@4");
	MBR_SetDatabaseEx=(LPLCCC) GetProcAddress(hMbrInst,"_MBR_SetDatabaseEx@12");
	MBR_GetDatabase=(LPLTD) GetProcAddress(hMbrInst,"_MBR_GetDatabase@8");
	MBR_IsPlaying=(LPBV) GetProcAddress(hMbrInst,"_MBR_IsPlaying@0");
	MBR_LastError=(LPLTD) GetProcAddress(hMbrInst,"_MBR_LastError@8");
	MBR_GetVersion=(LPVTD) GetProcAddress(hMbrInst,"_MBR_GetVersion@8");
	MBR_GetDefaultFreq=(LPLV) GetProcAddress(hMbrInst,"_MBR_GetDefaultFreq@0");
	MBR_GetDatabaseInfo=(LPLDTD) GetProcAddress(hMbrInst,"_MBR_GetDatabaseInfo@12");
	MBR_GetDatabaseAllInfo=(LPLTD) GetProcAddress(hMbrInst,"_MBR_GetDatabaseAllInfo@8");
	MBR_RegEnumDatabase=(LPLTD) GetProcAddress(hMbrInst,"_MBR_RegEnumDatabase@8");
	MBR_RegEnumDatabaseCallback=(LPLED) GetProcAddress(hMbrInst,"_MBR_RegEnumDatabaseCallback@8");
	MBR_RegGetDatabaseLabel=(LPLCTD) GetProcAddress(hMbrInst,"_MBR_RegGetDatabaseLabel@12");
	MBR_RegGetDatabasePath=(LPLCTD) GetProcAddress(hMbrInst,"_MBR_RegGetDatabasePath@12");
	MBR_RegGetDatabaseCount=(LPLV) GetProcAddress(hMbrInst,"_MBR_RegGetDatabaseCount@0");
	MBR_RegGetDefaultDatabase=(LPLTD) GetProcAddress(hMbrInst,"_MBR_RegGetDefaultDatabase@8");
	MBR_RegSetDefaultDatabase=(LPLC) GetProcAddress(hMbrInst,"_MBR_RegSetDefaultDatabase@4");
	MBR_RegisterDatabase=(LPBCCCBTD) GetProcAddress(hMbrInst,"_MBR_RegisterDatabase@24");
	MBR_UnregisterDatabase=(LPBCT) GetProcAddress(hMbrInst,"_MBR_UnregisterDatabase@4");
	MBR_UnregisterAll=(LPBV) GetProcAddress(hMbrInst,"_MBR_UnregisterAll@0");
	MBR_DatabaseExist=(LPBCT) GetProcAddress(hMbrInst,"_MBR_DatabaseExist@4");
	MBR_RegIdxGetDatabaseId=(LPBLTD) GetProcAddress(hMbrInst,"_MBR_RegIdxGetDatabaseId@12");
	MBR_RegIdxGetDatabasePath=(LPBLTD) GetProcAddress(hMbrInst,"_MBR_RegIdxGetDatabasePath@12");
	MBR_RegIdxGetDatabaseLabel=(LPBLTD) GetProcAddress(hMbrInst,"_MBR_RegIdxGetDatabaseLabel@12");
	MBR_RegIdxGetDatabaseIndex=(LPLC) GetProcAddress(hMbrInst,"_MBR_RegIdxGetDatabaseIndex@4");
	MBR_RegIdxGetDefaultDatabase=(LPLV) GetProcAddress(hMbrInst,"_MBR_RegIdxGetDefaultDatabase@0");
	MBR_StartControlPanel=(LPDWHW) GetProcAddress(hMbrInst,"_MBR_StartControlPanel@4");
	MBR_SetCallbackMsgBase=(LPLDW) GetProcAddress(hMbrInst,"_MBR_SetCallbackMsgBase@4");
	MBR_MBRUnload=(LPVV) GetProcAddress(hMbrInst,"_MBR_MBRUnload@0");\
	
	if((!MBR_Play)
      		|| (!MBR_Stop)
            || (!MBR_WaitForEnd)
            || (!MBR_SetPitchRatio)
            || (!MBR_SetDurationRatio)
            || (!MBR_SetVoiceFreq)
			|| (!MBR_SetVolumeRatio)
            || (!MBR_GetPitchRatio)
            || (!MBR_GetDurationRatio)
            || (!MBR_GetVoiceFreq)
			|| (!MBR_GetVolumeRatio)
			|| (!MBR_SetNoError)
			|| (!MBR_GetNoError)
			|| (!MBR_SetDatabase)
			|| (!MBR_SetDatabaseEx)
            || (!MBR_GetDatabase)
            || (!MBR_IsPlaying)
            || (!MBR_LastError)
            || (!MBR_GetVersion)
            || (!MBR_GetDefaultFreq)
            || (!MBR_GetDatabaseInfo)
            || (!MBR_GetDatabaseAllInfo)
            || (!MBR_RegEnumDatabase)
            || (!MBR_RegEnumDatabaseCallback)
            || (!MBR_RegGetDatabaseLabel)
            || (!MBR_RegGetDatabasePath)
            || (!MBR_RegGetDatabaseCount)
            || (!MBR_RegGetDefaultDatabase)
            || (!MBR_RegSetDefaultDatabase)
            || (!MBR_RegisterDatabase)
            || (!MBR_UnregisterDatabase)
            || (!MBR_UnregisterAll)
            || (!MBR_DatabaseExist)
            || (!MBR_RegIdxGetDatabaseId)
            || (!MBR_RegIdxGetDatabasePath)
            || (!MBR_RegIdxGetDatabaseLabel)
            || (!MBR_RegIdxGetDatabaseIndex)
            || (!MBR_RegIdxGetDefaultDatabase)
			|| (!MBR_StartControlPanel)
			|| (!MBR_SetCallbackMsgBase)
			|| (!MBR_MBRUnload))
		{
			free(hMbrInst);
			hinstDllMBR=NULL;
		    return FALSE;
		}

	return TRUE;
}
//======================================================
void MbrolaDllLoading::unload_MbrolaPlayDLL()
{
	if (hMbrInst)
	{
		MBR_MBRUnload();
	   	FreeLibrary(hMbrInst);
	}

}
//======================================================
bool MbrolaDllLoading::MbrStart()
{
	if(m_loadingState==LS_UNLOAD)
	{
		if(!load_MbrolaDLL())
		{
			m_lastLog="Can't load MbrolaDLL";
			m_loadingState=LS_ERROR;
			return FALSE;
		}
		
		//load_MbrolaPlayDLL();
		if(!load_MbrolaPlayDLL())
		{
			m_lastLog="Can't load MbrolaPlayDLL";
			m_loadingState=LS_ERROR;
			return FALSE;
		}
		
		int DatabaseLoadCheck=init_MBR("pl1");
		if (DatabaseLoadCheck!=0)
		{
			m_lastLog="Can't load Diphone base";
			m_loadingState=LS_ERROR;
			return FALSE;
		}
		m_loadingState=LS_LOAD;
		return TRUE;
	}
	m_lastLog="MBROLA already loaded";
	return TRUE;
	
}
//======================================================
bool MbrolaDllLoading::MbrClose()
{
	if(m_loadingState==LS_LOAD)
	{
//		flush_MBR();
		unload_MbrolaPlayDLL();
		unload_MbrollaDLL();
                m_loadingState=LS_UNLOAD;
		return 1;
	}
	m_lastLog="No need to unload MBROLA";
	return 0;
}



