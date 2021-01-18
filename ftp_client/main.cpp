/* Prosty interfejs dla testow */


#include "ftp.h"




int main(int argc, char *argv[])
{
	Cftp FtpClient;
	//kolejnosc argumentow: host-port-user-pass
	//argc jest o jeden wiekszy niz rzeczywista ilosc podanych argumentow
	if(argc==4)//jezeli uzytkownik nie poda portu DEFAULT_PORT=21
	{
		if(!FtpClient.ConnectInit(argv[1], DEFAULT_PORT, argv[2], argv[3]))
		{
			cin.sync();
			cin.get();
			return 0;
		}
	}
	else if(argc==5)//jezeli uzytkownik podaje pelen zestaw danych
	{
		int nPort=atoi(argv[2]);//zamiania c-stringa na integer
		if(!FtpClient.ConnectInit(argv[1], nPort, argv[2], argv[3]))
		{
			cin.sync();
			cin.get();
			return 0;
		}
	}
	else if(argc==3)//jezeli uzytkownik podaje host i uzytkowinka
	{
		if(!FtpClient.ConnectInit(argv[1], DEFAULT_PORT, argv[2], "none"))
		{
			cin.sync();
			cin.get();
			return 0;
		}
	}
	else if(argc==2)//jezeli uzytkownik podaje tylko host
	{
		if(!FtpClient.ConnectInit(argv[1], DEFAULT_PORT, "anonymous", "none"))
		{
			cin.sync();
			cin.get();
			return 0;
		}
	}
	else//jezeli uzytkownik mimo wszystko spieprzy sprawe :)
	{
		system("cls");//czyszczenie konsoli, windows only
		cout<<"Wrong args number.";
		cin.sync();
		cin.get();
		return 0;
	}
	
	

	for(;;)
	{
		system("cls");//windows only
		string strCmd;
		cout<<"Cmd: ";
		getline(cin,strCmd);//pobranie komendy
		if(strCmd=="cdir")
		{
			string strDir;
			cout<<"Dir: ";
			getline(cin,strDir);
			FtpClient.ChangeDir((char *)strDir.c_str());
		}
		else if(strCmd=="info")
		{
			FtpClient.FileList(SIMPLE);
			cin.sync();
			cin.get();
		}
		else if(strCmd=="cd")
		{
			FtpClient.CDup();
			cin.sync();
			cin.get();
		}
		else if(strCmd=="mkd")
		{
			string strPath;
			cout<<"Path: ";
			getline(cin,strPath);
			FtpClient.MakeDir((char *)strPath.c_str());
			cin.sync();
			cin.get();
		}
		else if(strCmd=="rmd")
		{
			string strPath;
			cout<<"Path: ";
			getline(cin,strPath);
			FtpClient.RemDir((char *)strPath.c_str());
			cin.sync();
			cin.get();
		}
		else if(strCmd=="del")
		{
			string strPath;
			cout<<"Path: ";
			getline(cin,strPath);
			FtpClient.DelFile((char *)strPath.c_str());
			cin.sync();
			cin.get();
		}
		else if(strCmd=="renfile")
		{
			string strPath;
			string strNewName;
			cout<<"Path: ";
			getline(cin,strPath);
			cout<<"New name: ";
			getline(cin,strNewName);
			FtpClient.FileRename((char *)strPath.c_str(),(char *)strNewName.c_str());
			cin.sync();
			cin.get();
		}
		else if(strCmd=="get")
		{
			string strFileName;
			cout<<"File: ";
			getline(cin, strFileName);
			FtpClient.GetFile((char *)strFileName.c_str());
			cin.sync();
			cin.get();
		}
		else if(strCmd=="put")
		{
			string strSrcPath;
			string strDestPath;
			cout<<"Source path: ";
			getline(cin, strSrcPath);
			cout<<"Dest path: ";
			getline(cin, strDestPath);
			FtpClient.PutFile((char *)strSrcPath.c_str(),(char *)strDestPath.c_str());
			cin.sync();
			cin.get();
		}
		else if(strCmd=="tran")
		{
			char cType;
			cout<<"Select tran. type: A-ASCII"<<"\n"
				<<"                   B-Binary"
				<<"\n"<<"Mode :";
			cin>>cType;
			if(cType=='A'){
				FtpClient.DataTranType(ASCII);}
			else if(cType=='B'){
				FtpClient.DataTranType(BINARY);}
				else{cout<<"TranType arg error";break;}
			cin.sync();
			cin.get();
			
		}
		else if(strCmd=="quit")
		{
			FtpClient.Quit();
			cin.sync();
			cin.get();
			break;//bye bye

		}
		else
		{
			cout<<"Wrong command";
			cin.sync();
			cin.get();
		}
	}


	
	//FtpClient.ConnectInit(LOCALHOST, DEFAULT_PORT, "kingc", "ka");
	//FtpClient.FileList(SIMPLE);
	//FtpClient.ChangeDir("virtual");
	//FtpClient.FileList(SIMPLE);
	//FtpClient.MakeDir("virtuall");
	//FtpClient.CDup();
	//FtpClient.DelFile("virtual");
	//FtpClient.FileRename("virtual","vertex");
	//FtpClient.FileList(DETAIL);
	//FtpClient.DataTranType(ASCII);
	//FtpClient.PutFile("example.jpg","przyklad.jpg");
	//FtpClient.CurrentDir();
	//FtpClient.OpenDataPort();
	//FtpClient.RemDir("virtual");
	//FtpClient.GetFile("przyklad.txt");
	//FtpClient.Quit();
	cin.sync();
	cin.get();
	return 0;
}

