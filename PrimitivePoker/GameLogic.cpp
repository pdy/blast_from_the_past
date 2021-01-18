#include "GameLogic.h"
#include "Card.h"
#include "CardSet.h"
#include "Deck.h"
#include "UtpPoker.h"
#include "ComputerPlayer.h"

GameLogic::GameLogic(QObject *parent) :
    QObject(parent)
{
    _deck = new Deck();

    _flipsideSet = new CardSet(*new Card(),*new Card(),*new Card(),*new Card(),*new Card());
    _computerPlayer = new ComputerPlayer();

    _humanSet = 0;
    _computerSet = 0;
}
//===================================================
GameLogic::~GameLogic()
{
    if(_deck)
    {
        delete _deck;
        _deck = 0;
    }

    if(_flipsideSet)
    {
        QVector<const Card*> vec = _flipsideSet->GetCardsVector();
        for(int i=0; i<vec.size();++i)
        {
            const Card *card = vec.at(i);
            if(card)
            {
                delete card;
                card = 0;
            }
        }
        delete _flipsideSet;
        _flipsideSet = 0;
    }

    if(_computerPlayer)
    {
        delete _computerPlayer;
        _computerPlayer = 0;
    }

    DisposeSets();
}
//==================================================
void GameLogic::DisposeSets()
{
    if(_humanSet)
    {
        delete _humanSet;
        _humanSet = 0;
    }

    if(_computerSet)
    {
        delete _computerSet;
        _computerSet = 0;
    }
}

//==================================================
void GameLogic::Start()
{
    //DisposeSets();
    QPair<CardSet*,CardSet*> sets = _deck->Distribute();

    _humanSet = sets.first; // przypisujemy ta wartosc tylko po to zeby zwolnic obiekt, obiekty zwrocone przez Deck::Distribute() nie sa zwalnianie w Deck
    _computerSet = sets.second;


    QPair<unsigned short,CardSet*> computerActionResult = _computerPlayer->ExchangeCards(*_computerSet,*_deck);
    unsigned short howManyCardsComputerExchanged = computerActionResult.first;
    if(howManyCardsComputerExchanged != 0)
    {
        delete _computerSet;
        _computerSet = 0;
        _computerSet = computerActionResult.second;
    }

    emit WhenGameStarts(*_humanSet,*_flipsideSet);
    emit NumberOfCardsExchangedByComputer(howManyCardsComputerExchanged);
}
//==================================================
void GameLogic::GiveMeCards(unsigned short cardsCount)
{
    QVector<const Card*> cards = _deck->GetCards(cardsCount);
    emit CardsRequested(cards);
}
//===================================================
void GameLogic::Finish(const CardSet &humanSet)
{
    bool equal = humanSet == (*_computerSet);
    bool humanWon = false;
    if(!equal){
        humanWon = humanSet > (*_computerSet);
    }

    QString msg;
    if(!equal && humanWon){
        msg = "Wygrales";
    }
    else if(!equal && !humanWon){
        msg = "Przegrales";
    }
    else{
        msg = "Remis";
    }
    emit GameFinished(*_computerSet,msg);
    DisposeSets();
}
