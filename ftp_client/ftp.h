#ifndef _FTP_H
#define _FTP_H



/*Kilka makr*/

#define DEFAULT_PORT 21
#define LOCALHOST "127.0.0.1"//do testow

#define net_send(socket,buf,buflen) send(socket,buf,buflen,0)
#define net_read(socket,buf,buflen) recv(socket,buf,buflen,0)

#define SIMPLE 0
/* TODO
   wykonanie predyrektyw dostosowujac kod
        do kompilacji na Linux'ie       */

#define DETAIL 1

#define ASCII 'A'
#define BINARY 'I'

#define SHOW 0
#define NO_PRINT 1





#include <iostream>
#include <string>
using namespace std;

/*Cftp do klasa pelniaca role wlasciwego 'silnika' wykonawczego
          bedzie ona dziedziczona do klasy z GUI             */
class Cftp
{

private:
	struct FtpBuf//typ dla uchwytu ftp
	{
		bool bConnected;//flaga informuj¹ca czy jest postawione kontrolne po³aczenie
		char cResponse[256];//bufor odpowiedzi serwera
		int nSock;//gniazdo zwrócone przez ServerConnect
		struct DataBuf//podtyp dla uchwytu danych
		{
			int nDataSock;//deskryptor gniazda dla polaczen danych
			char cMode;//typ transmisji
		}DataHandle;//poduchwyt dla danych
	}*ftpHandle;

	int init_Winsock();//dla glupiego windowsa
	int SendCmd(char *cmd, char cExpAns);//metoda wysylajaca komendy kontrolne i sprawdzajaca odpowiedzi serwera
	int CurrentDir();//informuje o obecnej sciezce serwera
	int ServerConnect(char *csAdres, int nPort);//polaczenie kontrolne z serwerem
	int LogIn(char *csUser, char *csPass);//logowanie na serwer
	void ServerDisconnect();//zamkniecie gniazd-kontrolnego i danych
	int OpenDataPort();//otwarcie portu dla transmisji danych, TODO tryb aktywny
	int AcceptDataConnection();//narazie niepotrzebne dla naszego pasywnego polaczenia
	int DataTranReply(int nCmd);
	int RemoteFileSize(char *csPath);

public:	
	Cftp();
	~Cftp();
	int ConnectInit(char *csAdres, int nPort, char *csUser, char *csPass);//laczy i loguje sie na serw
	int ChangeDir(char *csPath);
	int CDup();
	int RemDir(char *csPath);
	int MakeDir(char *csPath);
	int DelFile(char *csPath);
	int FileRename(char *csPath, char *csNewName);
	int GetFile(char *FileName);//pobiera plik TODO pakietowanie danych
	int PutFile(char *csSrcPath, char *csDestPath);//wysy³anie danych TODO pakietowanie danych
	int FileList(int nType);//dostajemy spis plikow, obecna sciezke i w jakim trybie transmisji jestesmy
	int DataTranType(char cType);//ustawiamy sposob transmisji
	int Quit();
	
};

#endif