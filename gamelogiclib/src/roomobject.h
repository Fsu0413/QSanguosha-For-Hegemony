#ifndef ROOMOBJECT_H
#define ROOMOBJECT_H

#include "libqsgsgamelogicglobal.h"
#include "structs.h"

class Player;
class Card;

class RoomRequestReceiver
{
    // DO NOT INHERIT QObject HERE!!!
    // It is intended to be inherited by Socket/UI/AI, and wait for their reply
    // Because all these components needs to inherit QObject, so this class should not inherit QObject
public:
    virtual ~RoomRequestReceiver();

    virtual bool doRequest(const QJsonDocument &request) = 0; // REMEMBER TO CLEAR m_result!!!
    virtual const QJsonDocument &waitForResult(int timeout);

protected:
    RoomRequestReceiver();
    virtual void resultReceived(const QJsonDocument &result); // This function is meant to be called in the slot when the receiver received the result

    QJsonDocument m_result;

    QWaitCondition m_cond;
    QMutex m_mutex;

private:
    Q_DISABLE_COPY(RoomRequestReceiver)
};

class RoomObject;

class RoomRequestHandler final
{
    // There should be no class inherits RoomRequestHandler
public:
    RoomRequestHandler(RoomRequestReceiver *receiver);
    ~RoomRequestHandler();

    QJsonDocument requestReceiver(const QJsonDocument &request, int timeout);

    RoomRequestReceiver *receiver() const;

private:
    RoomRequestReceiver *m_receiver;
    Q_DISABLE_COPY(RoomRequestHandler)
};

class RoomObjectPrivate;

class RoomObject : public QObject
{
    Q_OBJECT

public:
    explicit RoomObject(QObject *parent = 0);
    /*virtual*/ ~RoomObject(); // if this class is meant to be a virtual class, make sure this destructor is virtual

    struct CardPlaceStruct
    {
        Player *player;
        QSgsEnum::PlayerPlace place;
    };

    void addRealCard(Card *card);
    void addRealCards(QList<Card *> cards);
    void addVirtualCard(Card *card);

    const QList<Card *> &cards() const;
    const QList<Player *> &players() const;

    const QString &currentCardUsePattern() const;
    QSgsEnum::CardUseReason currentCardUseReason() const;

    QList<Card *> &drawPile();
    const QList<Card *> &drawPile() const;

    const QList<Card *> &discardPile() const;

    const CardPlaceStruct &cardPlace(Card *card) const; // using the const functions of the QHash to get the place of a card

    // set the handler of the following interactive methods
    RoomRequestHandler *requestHandler() const;
    void setRequestHandler(RoomRequestHandler *handler);
    // Interactive Methods: Note these functions does not do the actual operations, it is caller's responsibility to do the things
    // calls when this player is in the free time of Play Phase
    CardUseStruct &&activate(Player *player);
    // ask a player to use a card according to the pattern
    CardUseStruct &&askForUseCard(Player *player, const QString &pattern, const QString &prompt, const QString &reason = QString(), bool addHistory = true, const QJsonValue &data = QJsonValue());
    // a wrapper to askForUseCard which aims at using Slash(Strike) to a certain target
    // note that one can add more additional targets in the returned CardUseStruct
    CardUseStruct &&askForUseSlashTo(Player *from, const QList<Player *> &to, const QString &prompt, const QString &reason = QString(), bool addHistory = true, const QJsonValue &data = QJsonValue());
    CardUseStruct &&askForUseSlashTo(Player *from, Player *to, const QString &prompt, const QString &reason = QString(), bool addHistory = true, const QJsonValue &data = QJsonValue());
    // ask a player to take out a card according to the pattern
    Card *askForResponseCard(Player *player, const QString &pattern, const QString &prompt, const QString &reason = QString(), bool toTable = false, const QJsonValue &data = QJsonValue());
    // ask a player to choose a card in an AG container
    Card *askForAg(Player *player, const QList<Card *> cards, const QString &reason = QString(), bool forced = false, const QJsonValue &data = QJsonValue());
    struct CardDistributeStruct
    {
        Card *card;
        Player *player;
    };
    // ask a player to distribute cards. Note that fromPlace can either be PlaceHand/PlaceEquip or PlaceTable/PlaceWugu, in the condition of PlaceTable/PlaceWugu you should call fillAg first and call clearAg afterwards
    QList<CardDistributeStruct> &&askForDistribute(Player *player, const QList<Card *> cards, QSgsEnum::PlayerPlace fromPlace, bool forced = false, const QJsonValue &data = QJsonValue());
    // ask a player to discard. Note this pattern needs to be discussed, probably it will be a QStringList
    Card *askForDiscard(Player *player, const QString &pattern, const QString &prompt, const QString &reason = QString(), bool forced = false, const QJsonValue &data = QJsonValue());
    // ask a player to discard multi cards
    QList<Card *> &&askForDiscard(Player *player, int minNum, int maxNum, const QString &prompt, const QString &reason = QString(), bool forced = false, const QJsonValue &data = QJsonValue());
    // ask a player to select some cards to do something
    QList<Card *> &&askForSelectCard(Player *player, int minNum, int maxNum, const QString &prompt, QSgsEnum::CardHandlingMethod handlingMethod = QSgsEnum::CardHandlingMethod::NoMethod, const QString &expandPile = QString(), bool forced = false, const QJsonValue &data = QJsonValue());
    // ask a player to make a choice
    const QString &askForChoice(Player *player, const QStringList &choices, const QString &reason = QString(), const QJsonValue &data = QJsonValue());
    // advanced use of askForChoice
    const QString &askForChoice(Player *player, const QJsonDocument &choicesDocument, const QString &reason = QString(), const QJsonValue &data = QJsonValue());
    // ask players to use Nullification, a targetNo of -1 stands for Nullification to Nullification
    CardUseStruct &&askForNullification(const CardUseStruct &use, int targetNo = 0);
    // ask a player to choose a card of others
    Card *askForChooseCard(Player *from, Player *to, const QString &reason = QString(), QString &&flags = QStringLiteral("hej"), bool handcardVisible = false, QSgsEnum::CardHandlingMethod handlingMethod = QSgsEnum::CardHandlingMethod::NoMethod, const QList<Card *> &disabled = QList<Card *>(), const QJsonValue &data = QJsonValue());
    struct RearrangeCardStruct
    {
        QList<Card *> up;
        QList<Card *> bottom;
    };
    // ask a player to rearrange a set of cards
    RearrangeCardStruct &&askForRearrangeCard(Player *from, const QList<Card *> cards, QSgsEnum::RearrangeCardDirection direction);
    // ask a player to select trigger order of a set of skills
    void askForTriggerOrder(...); // TBD
    // ask a player to confirm something. askForConfirm(a, b, c, d) == askForSkillInvoke(a, c, b, d)
    bool askForConfirm(Player *player, const QString &prompt, const QString &reason, const QJsonValue &data = QJsonValue());
    // ask a player to pindian to an other player, note that the obsolete "Card1" parameter is removed
    QList<Card *> &&askForPindian(Player *from, Player *to, const QString &reason);


protected:
    Q_DECLARE_PRIVATE(RoomObject)
    RoomObjectPrivate *d_ptr;
};

#endif // ROOMOBJECT_H
