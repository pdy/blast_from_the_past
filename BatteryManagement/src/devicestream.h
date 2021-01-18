#ifndef DEVICESTREAM_H
#define DEVICESTREAM_H

#include <windows.h>
#include <QString>

class DeviceStream
{
public:
    DeviceStream();
    ~DeviceStream();

    bool Open();
    void Close();
    void SetStandardMessageLong(int messLong){standardMessageLong = messLong;}
    QString Read();
    bool Write(const char *mess);
    int PortNumber(){return portNumber;}
    QString PortNumberStr();
private:
    HANDLE portHandle;
    bool isOpen;
    int portNumber;
    COMMTIMEOUTS timeOut;
    int standardMessageLong;

    void SetTimeOut(const char *req);

    QString ConvertToString(int val);
    QString ConvertToString(unsigned long val);
    QString CurrentTime();
    void WriteToFile(QString value);

    int counter;


};

#endif // DEVICESTREAM_H
