#ifndef ROOMOBJECT_H
#define ROOMOBJECT_H

#include "libqsgsgamelogicglobal.h"
#include "enumeration.h"
#include "structs.h"

class Player;
class Card;
class ProhibitSkill;

class LIBQSGSGAMELOGIC_EXPORT RoomRequestReceiver
{
    // DO NOT INHERIT QObject HERE!!!
    // It is intended to be inherited by Socket/UI/AI, and wait for their reply
    // Because all these components needs to inherit QObject, if this class inherits QObject, that will cause troubles in multi-inheriting
    // THIS SHOULD BE ON A DIFFERENT THREAD THAN RoomRequestHandler!!!
public:
    virtual ~RoomRequestReceiver();

    virtual bool doRequest(const QJsonDocument &request) = 0; // REMEMBER TO CLEAR m_result!!!
    virtual const QJsonDocument &waitForResult(int timeout);

protected:
    RoomRequestReceiver();
    virtual void resultReceived(const QJsonDocument &result); // This function is meant to be called in the slot when the receiver received the result

    // should we use D-pointer to handle this? Seems it is not worthy.
    QJsonDocument m_result;

    QWaitCondition m_cond;
    QMutex m_mutex;

private:
    Q_DISABLE_COPY(RoomRequestReceiver)
};

class LIBQSGSGAMELOGIC_EXPORT RoomRequestHandler final
{
    // There should be no class inherits RoomRequestHandler
    // This instance of this class should be on the same thread of RoomObject
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

class LIBQSGSGAMELOGIC_EXPORT RoomObject : public QObject
{
    Q_OBJECT

public:
    explicit RoomObject(QObject *parent = 0);
    /*virtual*/ ~RoomObject(); // if this class is meant to be a virtual class, make sure this destructor is virtual

    struct CardPlaceStruct
    {
        Player *player;
        QSgsEnum::CardPlace place;
    };

    void addRealCard(Card *card);
    void addRealCards(QList<Card *> cards);
    void addVirtualCard(Card *card);

    const QList<Card *> &cards();
    QList<const Card *> cards() const;
    Card *card(int id) const;
    const QList<Player *> &players();
    QList<const Player *> players() const;

    const QString &currentCardUsePattern() const;
    QSgsEnum::CardUseReason currentCardUseReason() const;

    QList<Card *> &drawPile();
    QList<const Card *> drawPile() const;

    const QList<Card *> &discardPile();
    QList<const Card *> discardPile() const;

    const CardPlaceStruct &cardPlace(const Card *card) const; // using the const functions of the QHash to get the place of a card

    // set the handler of the following interactive methods. Note that RoomObject takes the ownership of the handler, DO NOT DELETE IT AFTER YOU SET IT!!
    RoomRequestHandler *requestHandler() const;
    bool setRequestHandler(RoomRequestHandler *handler);
    // Interactive Methods: Note these functions does not do the actual operations, it is caller's responsibility to do the things
    // calls when this player is in the free time of Play Phase, note that in this phase this player can use a card, or invoke a skill
    // for return value: true means one of the 2 pointer contains value, else means both of them are nullptr
    // cardUse and skillInvoke must be nullptr when entering this function
    // you should manually delete the structs when you don't use it
    bool activate(Player *player, CardUseStruct *&cardUse, SkillInvokeStruct *&skillInvoke);
    // ask a player to use a card according to the pattern
    CardUseStruct askForUseCard(Player *player, const QString &pattern, const QString &prompt, const QString &reason = QString(), bool addHistory = true, const QJsonValue &data = QJsonValue());
    // a wrapper to askForUseCard which aims at using Slash(Strike) to a certain target
    // note that one can add more additional targets in the returned CardUseStruct
    // This function will rename to askForUseStrikeTo if we decided to use offical translations in card/general names, etc.
    CardUseStruct askForUseSlashTo(Player *from, const QList<Player *> &to, const QString &prompt, const QString &reason = QString(), bool addHistory = true, const QJsonValue &data = QJsonValue());
    CardUseStruct askForUseSlashTo(Player *from, Player *to, const QString &prompt, const QString &reason = QString(), bool addHistory = true, const QJsonValue &data = QJsonValue());
    // ask a player to take out a card according to the pattern
    Card *askForResponseCard(Player *player, const QString &pattern, const QString &prompt, const QString &reason = QString(), bool toTable = false, const QJsonValue &data = QJsonValue());
    // ask a player to choose a card in an AG container
    // There should be a better name for this function.....askForSelectCard has already replaced askForExchange, so....
    // If we still use the meaning of "Wugufengdeng", this function will rename to askForBh
    Card *askForAg(Player *player, const QList<Card *> cards, const QString &reason = QString(), bool forced = false, const QJsonValue &data = QJsonValue());
    struct CardDistributeStruct
    {
        Card *card;
        Player *player;
    };
    // ask a player to distribute cards. Note that fromPlace can either be PlaceHand/PlaceEquip or PlaceTable/PlaceWugu, in the condition of PlaceTable/PlaceWugu you should call fillAg first and call clearAg afterwards
    QList<CardDistributeStruct> askForDistribute(Player *player, const QList<Card *> cards, QSgsEnum::CardPlace fromPlace, bool forced = false, const QJsonValue &data = QJsonValue());
    // ask a player to discard. Note this pattern needs to be discussed, probably it will be a QStringList
    Card *askForDiscard(Player *player, const QString &pattern, const QString &prompt, const QString &reason = QString(), bool forced = false, const QJsonValue &data = QJsonValue());
    // ask a player to discard multi cards
    QList<Card *> askForDiscard(Player *player, int minNum, int maxNum, const QString &prompt, const QString &reason = QString(), bool forced = false, const QJsonValue &data = QJsonValue());
    // ask a player to select some cards to do something
    QList<Card *> askForSelectCard(Player *player, int minNum, int maxNum, const QString &prompt, QSgsEnum::CardHandlingMethod handlingMethod = QSgsEnum::CardHandlingMethod::NoMethod, const QString &expandPile = QString(), bool forced = false, const QJsonValue &data = QJsonValue());
    // ask a player to make a choice
    QString askForChoice(Player *player, const QStringList &choices, const QString &reason = QString(), const QJsonValue &data = QJsonValue());
    // advanced use of askForChoice
    QString askForChoice(Player *player, const QJsonDocument &choicesDocument, const QString &reason = QString(), const QJsonValue &data = QJsonValue());
    // ask players to use Nullification, a targetNo of -1 stands for Nullification to Nullification
    // This function will rename to askForWard if we decided to use offical translations in card/general names, etc.
    CardUseStruct askForNullification(const CardUseStruct &use, int targetNo = 0);
    // ask a player to choose a card of others
    Card *askForChooseCard(Player *from, Player *to, const QString &reason = QString(), QString &&flags = QStringLiteral("hej"), bool handcardVisible = false, QSgsEnum::CardHandlingMethod handlingMethod = QSgsEnum::CardHandlingMethod::NoMethod, const QList<Card *> &disabled = QList<Card *>(), const QJsonValue &data = QJsonValue());
    struct RearrangeCardStruct
    {
        QList<Card *> up;
        QList<Card *> bottom;
    };
    // ask a player to rearrange a set of cards, just like guanxing
    RearrangeCardStruct askForRearrangeCard(Player *from, const QList<Card *> cards, QSgsEnum::RearrangeCardDirection direction);
    // ask a player to select the order of triggering from a set of skills
    void askForTriggerOrder(...); // TBD
    // ask a player to confirm something. askForConfirm(a, b, c, d) == askForSkillInvoke(a, c, b, d)
    bool askForConfirm(Player *player, const QString &prompt, const QString &reason, const QJsonValue &data = QJsonValue());
    // ask a player to pindian to an other player, note that the obsolete "Card1" parameter is removed
    QList<Card *> askForPindian(Player *from, Player *to, const QString &reason);


    // functions to get the correction between players
    const ProhibitSkill *isProhibited(const Player *from, const Player *to, const Card *card) const;
    int correctDistance(const Player *from, const Player *to) const;
    int correctMaxCards(const Player *target, bool fixed = false) const;
    int correctCardTarget(const QSgsEnum::ModType type, const Player *from, Card *card) const;
    int correctAttackRange(const Player *target, bool include_weapon = true, bool fixed = false) const;

    // if this class is meant to be a virtual class, make sure RoomObjectPrivate *d_ptr and Q_DECLARE_PRIVATE are protected
private:
    Q_DECLARE_PRIVATE(RoomObject)
    RoomObjectPrivate *d_ptr;
};

#endif // ROOMOBJECT_H
