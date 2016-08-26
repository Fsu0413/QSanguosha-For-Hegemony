#include "roomobject.h"

RoomRequestHandler::RoomRequestHandler(RoomRequestReceiver *receiver)
{
    m_receiver = receiver;
}

RoomRequestHandler::~RoomRequestHandler()
{

}

QJsonDocument RoomRequestHandler::requestReceiver(const QJsonDocument &request)
{
    // emit a signal to RoomRequestReceiver, and wait for its callback
    m_receiver->doRequest(request);
    return m_receiver->waitForResult(0); // timeout????
}

RoomRequestReceiver *RoomRequestHandler::receiver() const
{
    return m_receiver;
}

class RoomObjectPrivate
{
public:
    QList<Card *> availableCards;
    QList<Player *> players;

    QList<Card *> virtualCards;

    QString currentCardUsePattern;
    QSgsEnum::CardUseReason currentCardUseReason;

    QList<Card *> drawPile;
    QList<Card *> discardPile;
    QList<Card *> proceedingArea;

    QHash<Card *, RoomObject::CardPlaceStruct> cardPlaces;

    RoomRequestHandler *handler;
};

RoomObject::RoomObject(QObject *parent)
    : QObject(parent), d_ptr(new RoomObjectPrivate)
{
    Q_D(RoomObject);
    d->currentCardUseReason = QSgsEnum::CardUseReason::Unknown;
    d->handler = nullptr;
}

RoomObject::~RoomObject()
{
    delete d_ptr;
}

void RoomObject::addRealCard(Card *card)
{
    Q_D(RoomObject);
    d->availableCards << card;
}

void RoomObject::addRealCards(QList<Card *> cards)
{
    Q_D(RoomObject);
    d->availableCards << cards;
}

void RoomObject::addVirtualCard(Card *card)
{
    Q_D(RoomObject);
    d->virtualCards << card;
    // card->setParent(this);
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

RoomRequestHandler *RoomObject::requestHandler() const
{
    Q_D(const RoomObject);

}

CardUseStruct &&RoomObject::activate(Player *player)
{

}

CardUseStruct &&RoomObject::askForUseCard(Player *player, const QString &pattern, const QString &prompt, const QString &reason, bool addHistory, const QJsonDocument &data)
{

}

CardUseStruct &&RoomObject::askForUseSlashTo(Player *from, const QList<Player *> &to, const QString &prompt, const QString &reason, bool addHistory, const QJsonDocument &data)
{

}

CardUseStruct &&RoomObject::askForUseSlashTo(Player *from, Player *to, const QString &prompt, const QString &reason, bool addHistory, const QJsonDocument &data)
{

}

Card *RoomObject::askForResponseCard(Player *player, const QString &pattern, const QString &prompt, const QString &reason, bool toTable, const QJsonDocument &data)
{

}

Card *RoomObject::askForAg(Player *player, const QList<Card *> cards, const QString &reason, bool forced, const QJsonDocument &data)
{

}

QList<RoomObject::CardDistributeStruct> &&RoomObject::askForDistribute(Player *player, const QList<Card *> cards, QSgsEnum::PlayerPlace fromPlace, bool forced, const QJsonDocument &data)
{

}

Card *RoomObject::askForDiscard(Player *player, const QString &pattern, const QString &prompt, const QString &reason, bool forced, const QJsonDocument &data)
{

}

QList<Card *> &&RoomObject::askForDiscard(Player *player, int minNum, int maxNum, const QString &prompt, const QString &reason, bool forced, const QJsonDocument &data)
{

}

QList<Card *> &&RoomObject::askForSelectCard(Player *player, int minNum, int maxNum, const QString &prompt, QSgsEnum::CardHandlingMethod handlingMethod, const QString &expandPile, bool forced, const QJsonDocument &data)
{

}

const QString &RoomObject::askForChoice(Player *player, const QStringList &choices, const QString &reason, const QJsonDocument &data)
{

}

const QString &RoomObject::askForChoice(Player *player, const QJsonDocument &choicesDocument, const QString &reason, const QJsonDocument &data)
{

}

CardUseStruct &&RoomObject::askForNullification(const CardUseStruct &use, int targetNo)
{

}

RoomObject::RearrangeCardStruct &&RoomObject::askForRearrangeCard(Player *from, const QList<Card *> cards, QSgsEnum::RearrangeCardDirection direction)
{

}

void RoomObject::askForTriggerOrder(...)
{

}

bool RoomObject::askForConfirm(Player *player, const QString &prompt, const QString &reason, const QJsonDocument &data)
{

}

QList<Card *> &&RoomObject::askForPindian(Player *from, Player *to, const QString &reason)
{

}