#include "filestream.h"


using namespace std;
//======================================================
FileStream::FileStream(const char *path, FileStream::Mode mode)
{
	
	switch(mode)
	{
	case READ:
		stream=fopen(path, "rb");
		break;
	case WRITE:
		stream=fopen(path, "wb");
		break;
	case READ_WRITE:
		stream=fopen(path, "r+b");
		break;
	}

}
//======================================================
FileStream::FileStream(void *extStream)
{
	stream=(FILE*)extStream;
}
//======================================================
FileStream::FileStream()
{
	//fclose(stream);
}
//======================================================
FileStream::~FileStream()
{
	//m_byteCount=0;
}
//======================================================
bool FileStream::Open(const char *path, FileStream::Mode mode)
{
	if(!path)
	{
		return 0;
	}

	

	switch(mode)
	{
	case READ:
		stream=fopen(path, "rb");
		break;
	case WRITE:
		stream=fopen(path, "wb");
		break;
	case READ_WRITE:
		stream=fopen(path, "r+b");
		break;
	}
	if(stream!=NULL)
	{
		return 1;
	}
	return 0;
}
//======================================================
int FileStream::Close()
{

	return fclose(stream);
}
//======================================================
int FileStream::KillExternalStream(void *stream)
{
	return fclose((FILE*)stream);
}
//======================================================
void FileStream::Read(void *buf, int len)
{
	m_byteCount=fread(buf,1,(size_t)len,stream);

}
//======================================================
void FileStream::Write(const void *buf,int size)
{
	m_byteCount=fwrite(buf, 1, (size_t)size, stream);
}
//======================================================
uLong FileStream::ByteCount()
{
	return m_byteCount;	
}
//======================================================
long FileStream::StreamSeek(uLong offset, FileStream::Origin origin)
{
	int fseek_origin;
	switch(origin)
	{
	case CURRENT:
		fseek_origin=SEEK_CUR;
		break;
	case BEGIN:
		fseek_origin=SEEK_SET;
		break;
	case END:
		fseek_origin=SEEK_END;
		break;
	default: return -1;
	}
	long ret = 0;
    if (fseek(stream, offset, fseek_origin) != 0)
	{
		ret = -1;
	}
 
	
    return ret;

}
//======================================================
long FileStream::StreamTell()
{
	long ret;
    ret = ftell(stream);
    return ret;
}
//======================================================
int FileStream::StreamError()
{
	return ferror(stream);
}


