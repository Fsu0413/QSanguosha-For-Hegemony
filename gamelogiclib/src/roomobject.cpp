#include "roomobject.h"

RoomRequestHandler::RoomRequestHandler(RoomRequestReceiver *receiver)
{
    m_receiver = receiver;
}

RoomRequestHandler::~RoomRequestHandler()
{

}

QJsonDocument RoomRequestHandler::requestReceiver(const QJsonDocument &request, int timeout)
{
    // emit a signal to RoomRequestReceiver, and wait for its callback
    m_receiver->doRequest(request);
    return m_receiver->waitForResult(timeout); // timeout????
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
    return d->cardPlaces.value(card, CardPlaceStruct{nullptr, QSgsEnum::CardPlace::PlaceUnknown});
}

RoomRequestHandler *RoomObject::requestHandler() const
{
    Q_D(const RoomObject);
    return d->handler;
}

void RoomObject::setRequestHandler(RoomRequestHandler *handler)
{
    Q_D(RoomObject);
    d->handler = handler;
}

bool RoomObject::activate(Player *player, CardUseStruct *&cardUse, SkillInvokeStruct *&skillInvoke)
{
    cardUse = nullptr;
    skillInvoke = nullptr;
    return false;
}

CardUseStruct RoomObject::askForUseCard(Player *player, const QString &pattern, const QString &prompt, const QString &reason, bool addHistory, const QJsonValue &data)
{
    return CardUseStruct();
}

CardUseStruct RoomObject::askForUseSlashTo(Player *from, const QList<Player *> &to, const QString &prompt, const QString &reason, bool addHistory, const QJsonValue &data)
{
    return CardUseStruct();
}

CardUseStruct RoomObject::askForUseSlashTo(Player *from, Player *to, const QString &prompt, const QString &reason, bool addHistory, const QJsonValue &data)
{
    return CardUseStruct();
}

Card *RoomObject::askForResponseCard(Player *player, const QString &pattern, const QString &prompt, const QString &reason, bool toTable, const QJsonValue &data)
{
    return nullptr;
}

Card *RoomObject::askForAg(Player *player, const QList<Card *> cards, const QString &reason, bool forced, const QJsonValue &data)
{
    return nullptr;
}

QList<RoomObject::CardDistributeStruct> RoomObject::askForDistribute(Player *player, const QList<Card *> cards, QSgsEnum::CardPlace fromPlace, bool forced, const QJsonValue &data)
{
    return QList<RoomObject::CardDistributeStruct>();
}

Card *RoomObject::askForDiscard(Player *player, const QString &pattern, const QString &prompt, const QString &reason, bool forced, const QJsonValue &data)
{
    return nullptr;
}

QList<Card *> RoomObject::askForDiscard(Player *player, int minNum, int maxNum, const QString &prompt, const QString &reason, bool forced, const QJsonValue &data)
{
    return QList<Card *>();
}

QList<Card *> RoomObject::askForSelectCard(Player *player, int minNum, int maxNum, const QString &prompt, QSgsEnum::CardHandlingMethod handlingMethod, const QString &expandPile, bool forced, const QJsonValue &data)
{
    return QList<Card *>();
}

QString RoomObject::askForChoice(Player *player, const QStringList &choices, const QString &reason, const QJsonValue &data)
{
    return QString();
}

QString RoomObject::askForChoice(Player *player, const QJsonDocument &choicesDocument, const QString &reason, const QJsonValue &data)
{
    return QString();
}

CardUseStruct RoomObject::askForNullification(const CardUseStruct &use, int targetNo)
{
    return CardUseStruct();
}

RoomObject::RearrangeCardStruct RoomObject::askForRearrangeCard(Player *from, const QList<Card *> cards, QSgsEnum::RearrangeCardDirection direction)
{
    return RearrangeCardStruct();
}

void RoomObject::askForTriggerOrder(...)
{

}

bool RoomObject::askForConfirm(Player *player, const QString &prompt, const QString &reason, const QJsonValue &data)
{
    return false;
}

QList<Card *> RoomObject::askForPindian(Player *from, Player *to, const QString &reason)
{
    return QList<Card *>();
}

const ProhibitSkill *RoomObject::isProhibited(const Player *from, const Player *to, const Card *card) const
{
    return nullptr;
}
