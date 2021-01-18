#include "Card.h"
#include "CardSet.h"

CardSet::CardSet(const Card &card1, const Card &card2, const Card &card3, const Card &card4, const Card &card5)
{
    _cardSet.push_back(&card1);
    _cardSet.push_back(&card2);
    _cardSet.push_back(&card3);
    _cardSet.push_back(&card4);
    _cardSet.push_back(&card5);

    _fiveCards.card1 = &card1;
    _fiveCards.card2 = &card2;
    _fiveCards.card3 = &card3;
    _fiveCards.card4 = &card4;
    _fiveCards.card5 = &card5;

    CountFigures();
    _allSameColor = CheckIfAllCardsAreSameColor();
    ComputeCardSystemAndSystemPoints();
}
//==================================================
bool CardSet::CheckIfAllCardsAreSameColor()
{
    unsigned short heartsCount = CountColor(UtpPoker::SPADES);
    unsigned short diamondsCount = CountColor(UtpPoker::DIAMONDS);
    unsigned short spadesCount = CountColor(UtpPoker::SPADES);
    unsigned short clubsCount = CountColor(UtpPoker::CLUBS);

    return (heartsCount == 5 || diamondsCount == 5 || spadesCount == 5 || clubsCount == 5);
}
//==================================================
unsigned short CardSet::CountColor(UtpPoker::CardColor color)
{
    unsigned short ret = 0;
    for(int i=0;i<_cardSet.size();++i)
    {
        const Card &card = *_cardSet.at(i);
        if(card.GetCardColor() == color){
            ++ret;
        }
    }
    return ret;
}
//==================================================
void CardSet::CountFigures()
{
    _figuresCount[UtpPoker::NINE] = 0;
    _figuresCount[UtpPoker::TEN] = 0;
    _figuresCount[UtpPoker::JACK] = 0;
    _figuresCount[UtpPoker::QUEEN] = 0;
    _figuresCount[UtpPoker::KING] = 0;
    _figuresCount[UtpPoker::ACE] = 0;

    QList<UtpPoker::Figure> figures = UtpPoker::FiguresList();
    QList<UtpPoker::Figure>::iterator it = figures.begin();

    for(;it != figures.end();++it)
    {
        UtpPoker::Figure currFigure = *it;
        for(int i=0;i<_cardSet.size();++i)
        {
            const Card &card = *_cardSet.at(i);
            if(card.GetFigure() == currFigure){
                _figuresCount[currFigure] += 1;
            }
        }
    }
}
//==================================================
void CardSet::ComputeCardSystemAndSystemPoints()
{
    _cardSystem = UtpPoker::HIGH_CARD;

    _pointsComputeHelper.fig1 = UtpPoker::FLIPSIDE;
    _pointsComputeHelper.fig2 = UtpPoker::FLIPSIDE;

    if(_allSameColor)
    {
        if(IsBigStraight()){
            _cardSystem = UtpPoker::ROYAL_FLUSH;
        }
        else if(IsSmallStraight()){
            _cardSystem = UtpPoker::STRAIGHT_FLUSH;
        }
        else{
            _cardSystem = UtpPoker::FLUSH;
        }
        _pointsOfSystem = GetSumOfAllCards();
    }
    else
    {
        if(IsFourOfKind())
        {
            _cardSystem = UtpPoker::FOUR_OF_KIND;
            _pointsOfSystem = _pointsComputeHelper.fig2 * 4;
        }
        else if(IsFull())
        {
            _cardSystem = UtpPoker::FULL;
            _pointsOfSystem = _pointsComputeHelper.fig1 * 2 + _pointsComputeHelper.fig2 * 3;
        }
        else if(IsThreeOfKind())
        {
            _cardSystem = UtpPoker::THREE_OF_KIND;
            _pointsOfSystem = _pointsComputeHelper.fig2 * 3;
        }
        else if(IsTwoPair())
        {
            _cardSystem = UtpPoker::TWO_PAIRS;
            _pointsOfSystem = _pointsComputeHelper.fig1 * 2 + _pointsComputeHelper.fig2 * 2;
        }
        else if(IsPair())
        {
            _cardSystem = UtpPoker::PAIR;
            _pointsOfSystem = _pointsComputeHelper.fig1 * 2;
        }
        else if(IsSmallStraight())
        {
            _cardSystem = UtpPoker::STRAIGHT_SMALL;
            _pointsOfSystem = GetSumOfAllCards();
        }
        else if(IsBigStraight())
        {
            _cardSystem = UtpPoker::STRAIGHT_BIG;
            _pointsOfSystem = GetSumOfAllCards();
        }

    }

    if(_cardSystem == UtpPoker::HIGH_CARD){
        _pointsOfSystem = GetSumOfAllCards();
    }
}
//===============================
bool CardSet::IsSmallStraight()
{
    return (_figuresCount[UtpPoker::NINE] == 1
            && _figuresCount[UtpPoker::TEN] == 1
            && _figuresCount[UtpPoker::JACK] == 1
            && _figuresCount[UtpPoker::QUEEN] == 1
            && _figuresCount[UtpPoker::KING] == 1);
}
//===============================
bool CardSet::IsBigStraight()
{
    return (_figuresCount[UtpPoker::TEN] == 1
            && _figuresCount[UtpPoker::JACK] == 1
            && _figuresCount[UtpPoker::QUEEN] == 1
            && _figuresCount[UtpPoker::KING] == 1
            && _figuresCount[UtpPoker::ACE] == 1);
}
//===============================
bool CardSet::IsPair()
{
    int count = 0;

    if(_figuresCount[UtpPoker::NINE] == 2)
    {
        count +=1;
        _pointsComputeHelper.fig1 = UtpPoker::NINE;
    }
    if(_figuresCount[UtpPoker::TEN] == 2)
    {
        count +=1;
        _pointsComputeHelper.fig1 = UtpPoker::TEN;
    }
    if(_figuresCount[UtpPoker::JACK] == 2)
    {
        count +=1;
        _pointsComputeHelper.fig1 = UtpPoker::JACK;
    }
    if(_figuresCount[UtpPoker::QUEEN] == 2)
    {
        count +=1;
        _pointsComputeHelper.fig1 = UtpPoker::QUEEN;
    }
    if(_figuresCount[UtpPoker::KING] == 2)
    {
        count +=1;
        _pointsComputeHelper.fig1 = UtpPoker::KING;
    }
    if(_figuresCount[UtpPoker::ACE] == 2)
    {
        count +=1;
        _pointsComputeHelper.fig1 = UtpPoker::ACE;
    }

    return (count == 1);
}
//===============================
bool CardSet::IsTwoPair()
{
    int count = 0;

    if(_figuresCount[UtpPoker::NINE] == 2)
    {
        count +=1;
        if(_pointsComputeHelper.fig1 == UtpPoker::FLIPSIDE){
            _pointsComputeHelper.fig1 = UtpPoker::NINE;
        }
        else{
            _pointsComputeHelper.fig2 = UtpPoker::NINE;
        }
    }
    if(_figuresCount[UtpPoker::TEN] == 2)
    {
        count +=1;
        if(_pointsComputeHelper.fig1 == UtpPoker::FLIPSIDE){
            _pointsComputeHelper.fig1 = UtpPoker::TEN;
        }
        else{
            _pointsComputeHelper.fig2 = UtpPoker::TEN;
        }
    }
    if(_figuresCount[UtpPoker::JACK] == 2)
    {
        count +=1;
        if(_pointsComputeHelper.fig1 == UtpPoker::FLIPSIDE){
            _pointsComputeHelper.fig1 = UtpPoker::JACK;
        }
        else{
            _pointsComputeHelper.fig2 = UtpPoker::JACK;
        }
    }
    if(_figuresCount[UtpPoker::QUEEN] == 2)
    {
        count +=1;
        if(_pointsComputeHelper.fig1 == UtpPoker::FLIPSIDE){
            _pointsComputeHelper.fig1 = UtpPoker::JACK;
        }
        else{
            _pointsComputeHelper.fig2 = UtpPoker::JACK;
        }
    }
    if(_figuresCount[UtpPoker::KING] == 2)
    {
        count +=1;
        if(_pointsComputeHelper.fig1 == UtpPoker::FLIPSIDE){
            _pointsComputeHelper.fig1 = UtpPoker::KING;
        }
        else{
            _pointsComputeHelper.fig2 = UtpPoker::KING;
        }
    }
    if(_figuresCount[UtpPoker::ACE] == 2)
    {
        count +=1;
        if(_pointsComputeHelper.fig1 == UtpPoker::FLIPSIDE){
            _pointsComputeHelper.fig1 = UtpPoker::ACE;
        }
        else{
            _pointsComputeHelper.fig2 = UtpPoker::ACE;
        }
    }

    return (count == 2);
}
//===============================
bool CardSet::IsThreeOfKind()
{
    bool ret = false;
    if(_figuresCount[UtpPoker::NINE] == 3)
    {
        ret = true;
        _pointsComputeHelper.fig2 = UtpPoker::NINE;
    }
    else if(_figuresCount[UtpPoker::TEN] == 3)
    {
        ret = true;
        _pointsComputeHelper.fig2 = UtpPoker::TEN;
    }
    else if(_figuresCount[UtpPoker::JACK] == 3)
    {
        ret = true;
        _pointsComputeHelper.fig2 = UtpPoker::JACK;
    }
    else if(_figuresCount[UtpPoker::QUEEN] == 3)
    {
        ret = true;
        _pointsComputeHelper.fig2 = UtpPoker::QUEEN;
    }
    else if(_figuresCount[UtpPoker::KING] == 3)
    {
        ret = true;
        _pointsComputeHelper.fig2 = UtpPoker::KING;
    }
    else if(_figuresCount[UtpPoker::ACE] == 3)
    {
        ret = true;
        _pointsComputeHelper.fig2 = UtpPoker::ACE;
    }
    return ret;
}
//===============================
bool CardSet::IsFull()
{
    return (IsPair() && IsThreeOfKind());
}
//===============================
bool CardSet::IsFourOfKind()
{
    bool ret = false;
    if(_figuresCount[UtpPoker::NINE] == 4)
    {
        ret = true;
        _pointsComputeHelper.fig2 = UtpPoker::NINE;
    }
    else if(_figuresCount[UtpPoker::TEN] == 4)
    {
        ret = true;
        _pointsComputeHelper.fig2 = UtpPoker::TEN;
    }
    else if(_figuresCount[UtpPoker::JACK] == 4)
    {
        ret = true;
        _pointsComputeHelper.fig2 = UtpPoker::JACK;
    }
    else if(_figuresCount[UtpPoker::QUEEN] == 4)
    {
        ret = true;
        _pointsComputeHelper.fig2 = UtpPoker::QUEEN;
    }
    else if(_figuresCount[UtpPoker::KING] == 4)
    {
        ret = true;
        _pointsComputeHelper.fig2 = UtpPoker::KING;
    }
    else if(_figuresCount[UtpPoker::ACE] == 4)
    {
        ret = true;
        _pointsComputeHelper.fig2 = UtpPoker::ACE;
    }
    return ret;
}
//==================================================
bool CardSet::operator >(const CardSet &cardSet) const
{
    if(GetCardSystem() == cardSet.GetCardSystem()){
        return GetPointsOfSystem() > cardSet.GetPointsOfSystem();
    }
    return (GetCardSystem() > cardSet.GetCardSystem());
}
//==================================================
bool CardSet::operator <(const CardSet &cardSet) const
{
    if(GetCardSystem() == cardSet.GetCardSystem()){
        return GetPointsOfSystem() < cardSet.GetPointsOfSystem();
    }
    return (GetCardSystem() < cardSet.GetCardSystem());
}
//==================================================
bool CardSet::operator ==(const CardSet &cardSet) const
{
    return (GetCardSystem() == cardSet.GetCardSystem() && GetPointsOfSystem() == cardSet.GetPointsOfSystem());
}
//==================================================
int CardSet::GetSumOfAllCards()
{
    return (_fiveCards.card1->GetFigure() +
            _fiveCards.card2->GetFigure() +
            _fiveCards.card3->GetFigure() +
            _fiveCards.card4->GetFigure() +
            _fiveCards.card5->GetFigure());
}
