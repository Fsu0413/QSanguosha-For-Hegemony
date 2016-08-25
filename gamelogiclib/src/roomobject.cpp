#include "roomobject.h"

class RoomObjectPrivate
{
public:
    QList<Card *> availableCards;
    QList<Player *> players;

    QString currentCardUsePattern;
    QSgsEnum::CardUseReason currentCardUseReason;

    QList<Card *> drawPile;
    QList<Card *> discardPile;
    QList<Card *> proceedingArea;

    QHash<Card *, CardPlaceStruct> cardPlaces;
};

RoomObject::RoomObject(QObject *parent)
    : QObject(parent), d_ptr(new RoomObjectPrivate)
{

}

RoomObject::~RoomObject()
{
    delete d_ptr;
}

void RoomObject::addRealCard(Card *card)
{

}

void RoomObject::addRealCards(QList<Card *> cards)
{

}

void RoomObject::addVirtualCard(Card *card)
{

}

const QList<Card *> &RoomObject::cards() const
{
    Q_D(const RoomObject);
    return d->availableCards;
}

const QList<Player *> &RoomObject::players() const
{
    Q_D(const RoomObject);
    return d->players;
}

const QString &RoomObject::currentCardUsePattern() const
{
    Q_D(const RoomObject);
    return d->currentCardUsePattern;
}

QSgsEnum::CardUseReason RoomObject::currentCardUseReason() const
{
    Q_D(const RoomObject);
    return d->currentCardUseReason;
}

QList<Card *> &RoomObject::drawPile()
{
    Q_D(RoomObject);
    return d->drawPile;
}

const QList<Card *> &RoomObject::drawPile() const
{
    Q_D(const RoomObject);
    return d->drawPile;
}

const QList<Card *> &RoomObject::discardPile() const
{
    Q_D(const RoomObject);
    return d->discardPile;
}

const RoomObject::CardPlaceStruct &RoomObject::cardPlace(Card *card) const
{
    Q_D(const RoomObject);
    return d->cardPlaces.value(card, CardPlaceStruct{nullptr, QSgsEnum::PlayerPlace::PlaceUnknown});
}
