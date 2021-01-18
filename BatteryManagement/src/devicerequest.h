#ifndef DEVICEREQUEST_H
#define DEVICEPREQUEST_H

#include <QString>

#define STANDARD_MESSAGE_LONG 15

class DeviceStream;

class DeviceRequest
{
public:
    DeviceRequest();
    ~DeviceRequest();

    bool ConfirmConnection();
    bool PrepareRequest(int cellNum,int delayValue);
    bool SendRequest();
    QString GetData();
    void CleanUp(){CloseDevice();}
    int PortNumber(){return portNumber.intPort;}
    QString PortNumberStr(){return portNumber.stringPort;}

private:
    bool OpenDevice();
    void CloseDevice();

    DeviceStream *stream;
    QString request;

    struct PORTNUM
    {
        int intPort;
        QString stringPort;
    }portNumber;

    QString ConvertToString(int val);
};

#endif // DEVICEREQUEST_H
