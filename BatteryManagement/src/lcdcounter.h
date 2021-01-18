#ifndef LCDCOUNTER_H
#define LCDCOUNTER_H

#include <QLCDNumber>

class QTimer;

class LcdCounter : public QLCDNumber
{
    Q_OBJECT
public:
    LcdCounter();
    void Start(int minutes,int seconds);
    void Stop();

private slots:
    void Update();
    void StopSlot();
signals:
    void Timeout();
private:
    QTimer *timer;
    QStringList minutes;
    QStringList seconds;

    QString value;
    QString previousValue;

    int lastMinIndex;
    int lastSecIndex;

    QString ConvertToString(int val);

};

#endif // LCDCOUNTER_H
