#-------------------------------------------------
#
# Project created by QtCreator 2013-05-12T21:34:51
#
#-------------------------------------------------

QT       += core gui

TARGET = Poker
TEMPLATE = app


SOURCES += main.cpp\
        MainApplication.cpp \
    CardView.cpp \
    UtpPoker.cpp \
    CardSet.cpp \
    Deck.cpp \
    GameLogic.cpp \
    ComputerPlayer.cpp

HEADERS  += MainApplication.h \
    CardView.h \
    Card.h \
    UtpPoker.h \
    CardSet.h \
    Deck.h \
    GameLogic.h \
    ComputerPlayer.h

FORMS    += mainapplication.ui

RESOURCES += \
    cards.qrc
