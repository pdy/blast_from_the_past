/* ftp.cpp zawiera implementacje metod stanowiacych
 szkielet wlasciwej aplikacji podczas pisania GUI nastapia
                   tu nieznaczne zmiany                  */

/*Nag³óki*/
#include "ftp.h"
#include <winsock.h>
#include <fstream>
#include <stdio.h>
//#include <string>
//#include <vector>



//#include <windows.h>


Cftp::Cftp()
{
	ftpHandle=new FtpBuf;
	ftpHandle->bConnected=0;
	ftpHandle->nSock=0;
	ftpHandle->DataHandle.cMode='A';
	ftpHandle->DataHandle.nDataSock=0;
	memset(ftpHandle->cResponse,'\0', 256);

	init_Winsock();//icnicjalizacja winsock, konieczne dla windows
}
//*******
Cftp::~Cftp()
{
	delete ftpHandle;//zwalnianie dynamicznego zaczepu
}
//******
int Cftp::init_Winsock()
{
	
	WSADATA WsaData;

	/*if( !WSAStartup(0x0101,&WsaData) ) {
		SetConsoleTitle("ftp: Connection closed");
		return 1;
	}
	else {
		cout<<"Winsock cannot be started"<<"\n";
	 return 0;
	}*/

	if(WSAStartup(MAKEWORD(2,0), &WsaData) != 0)
	{
		puts("ERROR: WSAStartup");
		return 0;
	}
	else
	{
		SetConsoleTitle("ftp: Connection closed");
		return 1;
	}

}
//********
int Cftp::ServerConnect(char *csAdresIP, int nPort)
{
	int sockfd;
	sockfd=socket(PF_INET, SOCK_STREAM, 0);
	if(sockfd == -1)
	{
	perror("socket() error");
	return 0;
	}
    /*wypelniamy strukture polaczenia*/
	struct sockaddr_in server;
	memset(&server,0,sizeof(server));
	server.sin_family=AF_INET;
	server.sin_port=htons(nPort);
	server.sin_addr.s_addr=inet_addr(csAdresIP);

    //laczymy sie z serwem tworzam kontrolne polaczenie
	int nConnectCheck=connect(sockfd, (struct sockaddr *)&server, sizeof(struct sockaddr));
	if(nConnectCheck == -1)
	{
		perror("connect() error");
		return 0;
	}
	
	ftpHandle->nSock=sockfd;//ustawiamy wartosci naszego zaczepu serwera	
	ftpHandle->bConnected=1;
	
	
	/*odbiór odpowiedzi serwera, je¿eli w tym miejscu to pominê
	zdarza sie ¿e odbieram b³êdne komunikaty*/
	if(net_read(ftpHandle->nSock, ftpHandle->cResponse, sizeof(ftpHandle->cResponse))<=0)
	{
		perror("read");
		cout<<"\n"<<"Server do not respond or been closed"<<endl;
		return 0;
	}
	
	memset(ftpHandle->cResponse, '\0', sizeof(ftpHandle->cResponse));
	return 1;
}
//******
void Cftp::ServerDisconnect()
{
	if(ftpHandle->bConnected)
	{
		closesocket(ftpHandle->nSock);
		closesocket(ftpHandle->DataHandle.nDataSock);
		SetConsoleTitle("ftp: Connection closed");
		ftpHandle->bConnected=0;
		memset(ftpHandle->cResponse, '\0', sizeof(ftpHandle->cResponse));
	}
	else{
		cout<<"Server is not connect"<<endl;}
	
}

//**********
/*krotka ale uzyteczna metoda robiaca za nas
  wiele fajnych rzeczy :)                   */
int Cftp::SendCmd(char *csCmd, char cExpAns)
{
	if(!ftpHandle->bConnected)
	{
		cout<<"Server is not connected"<<endl;
		return 0;
	}
	memset(ftpHandle->cResponse,0,sizeof(ftpHandle->cResponse));
	char cCmdBuf[256];
	if(strlen(csCmd)>256 || strlen(csCmd)<=2)//prymitywne sprawdzanie poprawnosci argumentow
	{
		cout<<"Wrong command"<<endl;
		return 0;
	}
	//strcpy(cCmdBuf, csCmd);
	
	sprintf(cCmdBuf,"%s\r\n",csCmd);//przepisanie, powrot karetki i nowa linia
	if(net_send(ftpHandle->nSock, cCmdBuf, strlen(cCmdBuf))<=0)//wylanie komendy i sprawdzenie bledu funckji
	{
		perror("send");
		return 0;
	}
	char cBuf[512];
	int nRecSize=net_read(ftpHandle->nSock, cBuf, 512);
	if(nRecSize<=0)
	{
		perror("read");
		return 0;
	}
	
	for(int i=0;i<nRecSize;i++){ftpHandle->cResponse[i]=cBuf[i];}
	ftpHandle->cResponse[nRecSize+1]='~';//znacznik dla metody RemoteFileSize, TODO do poprawy
	//for(int i=0;i<nRecSize;i++){cout<<ftpHandle->cResponse[i];}
	
	//cout<<nRecSize;
	if(cExpAns!=ftpHandle->cResponse[0]){//sprawdzamy czy otrzymalismy spodziewana odpowiedz
		return 0;}
	//for(int i=0;i<strlen(ftpHandle->cResponse);i++){cout<<ftpHandle->cResponse[i];}
	//memset(ftpHandle->cResponse, 0, sizeof(ftpHandle->cResponse));
	return 1;
}
//*******
int Cftp::LogIn(char *csUser, char *csPass)
{
	
	if(!ftpHandle->bConnected)
	{
		cout<<"Server is not connect"<<endl;
		return 0;
	}
	
	
	string strUserCmd="USER ";//inicjalizujemy lancuchy dla komend
	string strPassCmd="PASS ";
	strUserCmd+=csUser;	
	strPassCmd+=csPass;

	
	if(!SendCmd((char*)strUserCmd.c_str(),'3'))
	{
		if(ftpHandle->cResponse[0]=='2'){//"jezeli serw nie potrzebuje hasla"
			return 1;}
		for(int i=0;i<strlen(ftpHandle->cResponse);i++){cout<<ftpHandle->cResponse[i];}
		cout<<"User login mismatch"<<endl;
		return 0;
	}	
	
	if(!SendCmd((char*)strPassCmd.c_str(),'2'))//jezeli serw potrzebuje hasla
	{
		cout<<"Password error"<<endl;
		return 0;
	}
	
	
	cout<<"\n";
	return 1;
}
//*******
int Cftp::CurrentDir()
{
	if(!ftpHandle->bConnected)
	{
		cout<<"Server is not connect"<<endl;
		return 0;
	}
	memset(ftpHandle->cResponse, '\0', sizeof(ftpHandle->cResponse));
	/*if(ftpHandle->DataHandle.nDataSock>0)
	{
		char* cBuf=new char[100];
		net_read(ftpHandle->nSock,cBuf,100);
		delete[]cBuf;
	}*/
	if(!SendCmd("PWD", '2')){//wysylamy komende
		return 0;}
	char *pResp=&ftpHandle->cResponse[5];
	//for(int i=0;i<strlen(ftpHandle->cResponse);i++){cout<<ftpHandle->cResponse[i];}
	cout<<"Dir: ";
	while(*pResp!='"'){//"dopoki wartosc jest rozna od "
		cout<<*pResp;
		++pResp;}
	//memset(ftpHandle->cResponse, 0, sizeof(ftpHandle->cResponse));
	cout<<endl;
	return 1;
}

//*******
int Cftp::OpenDataPort()
{
	if(!ftpHandle->bConnected)
	{
		cout<<"Server is not connect"<<endl;
		return 0;
	}
	int sockfd;
	if(!SendCmd("PASV",'2'))//pobieramy informacjê o wolnym adresie i porcie dla transmisji danych
	{
		for(int i=0;i<strlen(ftpHandle->cResponse);i++){cout<<ftpHandle->cResponse[i];}//wyswietlamy dokladny komunikat bledu
		return 0;
	}
	//for(int i=0;i<strlen(ftpHandle->cResponse);i++){cout<<ftpHandle->cResponse[i];}
	//cout<<endl;
	
	
	string strDataHost;// deklaracja lanucha
	int nDataPort;

	/* przeksztalcamy odpowiedz na uzyteczne dla nas lancuchy*/
	char* p = strchr((char*)ftpHandle->cResponse,'(');
	
        if(p)
        {
                ++p;
                for(int i = 0; *p; ++p)
                {
					if(*p != ','){
						strDataHost.push_back(*p);}

                    else{
						if(++i == 4){ ++p; break;}
						strDataHost.push_back('.');}                                               
                }
				
                int p1,p2;
                if(sscanf(p,"%i,%i",&p1,&p2) != 2){
                       cout<<"sscanf error";}
                        
                /* wyliczamy port */
                nDataPort = p1 * 256 + p2; 				
        }
		
	memset(ftpHandle->cResponse, 0 , 256);
	/*wype³niamy strukturê*/
	struct sockaddr_in sin;
	memset(&sin, 0, sizeof(sin));
	sin.sin_family=AF_INET;
	sin.sin_port=htons(nDataPort);
	sin.sin_addr.s_addr = inet_addr(strDataHost.c_str());

	sockfd=socket(PF_INET, SOCK_STREAM,0);

	/*³aczymy sie z portem danych, klient pracuje w trybie pasywnym*/
	if(connect(sockfd, (struct sockaddr *)&sin, sizeof(struct sockaddr)) < 0){
		perror("connect");
		return 0;}

	ftpHandle->DataHandle.nDataSock=sockfd;
	return 1;
}
//********
int Cftp::AcceptDataConnection()//metoda dla aktywnego klienta, narazie niepotrzebna
{                              
	if(!ftpHandle->bConnected)
	{
		cout<<"Server is not connect"<<endl;
		return 0;
	}
	struct sockaddr addr;
	int len=sizeof(addr);
	int sData=accept(ftpHandle->DataHandle.nDataSock, &addr, &len);
	if(sData == -1){
		perror("accept");
		return 0;}

	ftpHandle->DataHandle.nDataSock=sData;
	return 1;
}


//*******
int Cftp::FileList(int nType)
{
	if(ftpHandle->DataHandle.cMode=='A'){
		cout<<"Tran mode: ASCII"<<endl;}
	else{                                  
		cout<<"Tran. mode: BINARY"<<endl;}
	if(!CurrentDir()){
		cout<<"CurrentDir() error"<<endl;
		for(int i=0;i<strlen(ftpHandle->cResponse);i++){cout<<ftpHandle->cResponse[i];}
		return 0;}
	string strDir;
	char *pBuf=&ftpHandle->cResponse[5];//przypisanie wskaznikowi odpowiedniego adresu
	
	while(*pBuf!='"'){
		strDir.push_back(*pBuf);
		++pBuf;}
	string ListCmd;
	if(nType==SIMPLE){//jezeli chcemy wyswietlic liste bez szczegó³ów
		 ListCmd="NLST ";}
	else if(nType==DETAIL){//je¿eli chcemy wyswietlic liste ze szczegó³ami
		 ListCmd="LIST ";}
	else{
		cout<<"FileList() argument failed"<<endl;}
	
	ListCmd+=strDir;
	
	
	
	if(!OpenDataPort()){//otwieramy port danych by odebrac dane po naszej komendzie
		cout<<"OpenDataPort() error"<<endl;
		return 0;}
	
	if(!SendCmd((char*)ListCmd.c_str(), '1')){//wysylamy komende
		for(int i=0;i<strlen(ftpHandle->cResponse);i++){cout<<ftpHandle->cResponse[i];}
		return 0;}	
	//for(int i=0;i<strlen(ftpHandle->cResponse);i++){cout<<ftpHandle->cResponse[i];}

	int nData=ftpHandle->DataHandle.nDataSock;//przepisujemy wartosc deskryptora
	char cBuf[1024];
	
	int size=net_read(nData, cBuf, 256);//pobieramy nasza liste oraz zapisujemy dokladna
	if(size<0){                         //ilosc pobranych bajtow
		perror("recv");
		return 0;}
	DataTranReply(NO_PRINT);//odbieramy odpowiedz z kontrolnego polaczenia, wiele zlego sie dzialo gdy tej linijki tu nie bylo
	for(int i=0;i<size;i++){cout<<cBuf[i];}//wyswietlamy liste
	ftpHandle->DataHandle.nDataSock=0;//powinno chodzic bez tego
									  //TODO dowiedziec sie dlaczego serw chce nowego portu danych dla kolejenj operacji
	

	return 1;
}
//********
/*niektore serwy tego nie obsluguja ale 
  przewidzialem pozniej taka okolicznosc*/
int Cftp::RemoteFileSize(char *csPath)
{
	string strSizeCmd="SIZE ";
	strSizeCmd+=csPath;

	if(!SendCmd((char *)strSizeCmd.c_str(), '2')){
		for(int i=0;i<strlen(ftpHandle->cResponse);i++){cout<<ftpHandle->cResponse[i];}
		return -1;}
	string strFileSize;
	char *pBuf=&ftpHandle->cResponse[4];
	while(*pBuf!='~'){
		strFileSize.push_back(*pBuf);
		++pBuf;}
	//cout<<strFileSize;
	int nFileSize=atoi((char *)strFileSize.c_str());
	//cout<<nFileSize;
	return nFileSize;
}

//*********
int Cftp::PutFile(char *csSrcPath, char *csDestPath)
{
	int nData=ftpHandle->DataHandle.nDataSock;
	if(nData==0)//jezeli nie ma postawionego polaczenia danych stawiamy je
	{
		if(!OpenDataPort()){//sprawdzanie bledow ofcourse
			cout<<"OpenDataPort() error"<<endl;
			return 0;}
		nData=ftpHandle->DataHandle.nDataSock;
	}
	
	ifstream file;
	file.open(csSrcPath, ios::in | ios::binary | ios::ate);
	int nFileSize=file.tellg();
	char *cFileBuf=new char[nFileSize];
	file.seekg(0, ios::beg);
	file.read(cFileBuf, nFileSize);
	
	string strStorCmd="STOR";//inicjalizacja lancucha dla komendy wyslania danych
	strStorCmd+=csDestPath;
	if(!SendCmd((char *)strStorCmd.c_str(), '1')){//wysylamy komende ze chcemy zapisac plik
		for(int i=0;i<strlen(ftpHandle->cResponse);i++){cout<<ftpHandle->cResponse[i];}//wyswitlamy dokladna odpowiedz w przypadku bledu
		cout<<"Send store error"<<endl;
		return 0;}

	int nSend=net_send(nData, cFileBuf, nFileSize);//TODO pakietowanie
	if(nSend>0){                                    
		cout<<"Write succeded. Wrote: "<<nSend<<"bytes"<<endl;//wyswietlamy komunikat ile bajtow udalo nam sie zapisac
		return 1;}
	else{
		cout<<"Write failed"<<endl;//komunikat bledu
		return 0;}
	delete[]cFileBuf;//zwalniamy dynamiczna pamiec
	file.close();//zamykamy strumien
	ftpHandle->DataHandle.nDataSock=0;//powinno chodzic bez tej linijki ale nie chodzi,
	return 1;
}

//********
int Cftp::GetFile(char *csFileName)//wrr dodac parametr dla sciezki zapisu na HDD
{
	int nData=ftpHandle->DataHandle.nDataSock;
	if(nData==0)
	{
		if(!OpenDataPort()){
			cout<<"OpenDataPort() error"<<endl;
			return 0;}
		nData=ftpHandle->DataHandle.nDataSock;
	}
	int nFileSize=RemoteFileSize(csFileName);
	if(nFileSize==-1){//w przypadku gdyby serwer nie obs³ugiwa³ komendy SIZE badz mia³ jakis inny problem :)
		cout<<"Program can not get remote file size."<<"\n"<<"Local disk space given in this case is: 131072 bytes"<<endl;
		nFileSize=131072;}
	 
	string strRetrCmd="RETR";
	strRetrCmd+=csFileName;
	if(!SendCmd((char *)strRetrCmd.c_str(),'1')){
		for(int i=0;i<strlen(ftpHandle->cResponse);i++){cout<<ftpHandle->cResponse[i];}
		cout<<endl<<"Send RETR error"<<endl;
		return 0;}
	for(int i=0;i<strlen(ftpHandle->cResponse);i++){cout<<ftpHandle->cResponse[i];}
	char *cFileBuf=new char[nFileSize];
	int nRec=net_read(nData, cFileBuf, nFileSize);//TODO pakietowanie danych
	if(nRec<=0){
		//for(int i=0;i<1024;i++){cout<<cFileBuf[i];}
		DataTranReply(SHOW);
		cout<<"Data read error"<<endl;
		return 0;}
	else{
		DataTranReply(SHOW);
		cout<<"Get succeded. Got: "<<nRec<<"bytes"<<endl;}
	ofstream file;
	file.open(csFileName, ios::out | ios::binary);
	file.write(cFileBuf, nRec);
	file.close();
	delete[]cFileBuf;
	ftpHandle->DataHandle.nDataSock=0;//powinno chodzic bez tej linijki ale nie chodzi,
	return 1;
}
//********
int Cftp::DataTranType(char cType)
{
	string strTypeCmd="TYPE ";
	if(cType==ASCII){
		strTypeCmd.push_back('A');//komenda ustawiajace typ ASCII
		ftpHandle->DataHandle.cMode='A';}//ustawiamy odpowiednio dane dla uchwytu by wygodnie móc wyswietlac informacje
	else if(cType==BINARY){
		strTypeCmd.push_back('I');//komenda ustawiajaca typ IMAGE, czesto nazywana tez trybem binarnym
		ftpHandle->DataHandle.cMode='I';}
	else{
		cout<<"DataTranType() argument error"<<endl;
		return 0;}

	if(!SendCmd((char *)strTypeCmd.c_str(),'2')){//wysylamy
		for(int i=0;i<strlen(ftpHandle->cResponse);i++){cout<<ftpHandle->cResponse[i];}//pelna odpowiedz serwa jesli blad
		return 0;}
	for(int i=0;i<strlen(ftpHandle->cResponse);i++){cout<<ftpHandle->cResponse[i];}
	//memset(ftpHandle->cResponse, '\0', sizeof(ftpHandle->cResponse));
	return 1;
}


//********
/*laczymy i logujemy sie na serwer, wywolujemy tutaj dwie metody*/
   
int Cftp::ConnectInit(char *csAdres, int nPort, char *csUser, char *csPass)
{
	if(!ServerConnect(csAdres, nPort)){
		cout<<"Can not set control conection"<<endl;
		return 0;}
	if(!LogIn(csUser, csPass)){
		cout<<"Can not log in"<<endl;
		return 0;}
	SetConsoleTitle("ftp: Connection open");
	for(int i=0;i<strlen(ftpHandle->cResponse);i++){cout<<ftpHandle->cResponse[i];}
	memset(ftpHandle->cResponse, '\0', sizeof(ftpHandle->cResponse));
	return 1;
}
//********
int Cftp::Quit()
{
	if(ftpHandle->bConnected)
	{
		if(!SendCmd("QUIT",'2')){
			for(int i=0;i<sizeof(ftpHandle->cResponse);i++){cout<<ftpHandle->cResponse[i];}//komunikat bledu
			return 0;}
		ServerDisconnect();
		WSACleanup();//wrr dodaæ czyszczenie struktur do blokow if(blad)
	}
	return 1;
}
//********
int Cftp::ChangeDir(char *csPath)
{
	string strChCmd="CWD ";	//inicjalizujemy lancuch
	strChCmd+=csPath;//precyzujemy
	if(!SendCmd((char *)strChCmd.c_str(), '2')){//wysylamy
		return 0;}
	for(int i=0;i<strlen(ftpHandle->cResponse);i++){cout<<ftpHandle->cResponse[i];}
	memset(ftpHandle->cResponse, '\0', sizeof(ftpHandle->cResponse));
	//CurrentDir();
    return 1;
}
//********

int Cftp::CDup()
{
	if(!SendCmd("CDUP", '2')){
		return 0;}
	for(int i=0;i<strlen(ftpHandle->cResponse);i++){cout<<ftpHandle->cResponse[i];}
	//memset(ftpHandle->cResponse, '\0', sizeof(ftpHandle->cResponse));
	return 1;
}
//*********
int Cftp::RemDir(char *csPath)
{
	string strRdirCmd="RMD ";	
	strRdirCmd+=csPath;
	if(!SendCmd((char *)strRdirCmd.c_str(), '2')){
		for(int i=0;i<strlen(ftpHandle->cResponse);i++){cout<<ftpHandle->cResponse[i];}
		return 0;}
	for(int i=0;i<strlen(ftpHandle->cResponse);i++){cout<<ftpHandle->cResponse[i];}
	memset(ftpHandle->cResponse, '\0', sizeof(ftpHandle->cResponse));
	return 1;
}
//*********
int Cftp::MakeDir(char *csPath)
{
	string strMdirCmd="MKD ";	
	strMdirCmd+=csPath;

	if(!SendCmd((char *)strMdirCmd.c_str(), '2')){
		for(int i=0;i<strlen(ftpHandle->cResponse);i++){cout<<ftpHandle->cResponse[i];}
		return 0;}
	for(int i=0;i<strlen(ftpHandle->cResponse);i++){cout<<ftpHandle->cResponse[i];}
	memset(ftpHandle->cResponse, '\0', sizeof(ftpHandle->cResponse));
	return 1;
}
//******
int Cftp::DelFile(char *csPath)
{
	string strDelCmd="DELE ";
	strDelCmd+=csPath;

	if(!SendCmd((char *)strDelCmd.c_str(), '2')){
		for(int i=0;i<strlen(ftpHandle->cResponse);i++){cout<<ftpHandle->cResponse[i];}
		return 0;}
	for(int i=0;i<strlen(ftpHandle->cResponse);i++){cout<<ftpHandle->cResponse[i];}
	memset(ftpHandle->cResponse, '\0', sizeof(ftpHandle->cResponse));
	return 1;
}

//*******
int Cftp::FileRename(char *csPath, char *csNewName)
{
	string strRenFrom="RNFR ";//wskazujey ktory plik zmieniamy
	strRenFrom+=csPath;

	if(!SendCmd((char *)strRenFrom.c_str(), '3')){
		for(int i=0;i<strlen(ftpHandle->cResponse);i++){cout<<ftpHandle->cResponse[i];}
		return 0;}
	for(int i=0;i<strlen(ftpHandle->cResponse);i++){cout<<ftpHandle->cResponse[i];}
	string strRenTo="RNTO ";//i dopiero teraz zmieniamy
	strRenTo+=csNewName;

	if(!SendCmd((char *)strRenTo.c_str(), '2')){
		for(int i=0;i<strlen(ftpHandle->cResponse);i++){cout<<ftpHandle->cResponse[i];}
		return 0;}
	for(int i=0;i<strlen(ftpHandle->cResponse);i++){cout<<ftpHandle->cResponse[i];}
	memset(ftpHandle->cResponse, '\0', sizeof(ftpHandle->cResponse));
	
	return 1;
}

//******
int Cftp::DataTranReply(int nCmd)
{
	char cBuf[256];
	int nSize=net_read(ftpHandle->nSock,cBuf,256);
	if(nSize<0){
		return 0;}
	if(nCmd==SHOW)
	{
		for(int i=0;i<nSize;i++){
			cout<<cBuf[i];}
	}

	//cout<<endl;
	return 1;
}
