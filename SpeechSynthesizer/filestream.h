#ifndef FILESTREAM_H
#define FILESTREAM_H



#include <stdio.h>
#include <stdlib.h>
#include <fstream>
typedef unsigned long uLong; 

class FileStream
{
public:
	enum Mode
	{
		READ=0x1,
		WRITE=0x2,
		READ_WRITE=READ | WRITE,
	};

	enum Origin
	{
		BEGIN,
		END,
		CURRENT,
	};
	FileStream(const char *path, Mode mode);
	FileStream(void *extStream);
	FileStream();
	~FileStream();

	bool Open(const char *path, Mode mode);
	int Close();

	int KillExternalStream(void *stream);

	void Read(void *buf, int len);
	void Write(const void *buf,int size);
	long StreamSeek(uLong offset, Origin origin);
	long StreamTell();
	int StreamError();
	

	uLong ByteCount();
	
private:
	FILE *stream;
	uLong m_byteCount;
	

};
#endif//FILESTREAM_H