#ifndef ROOMOBJECT_H
#define ROOMOBJECT_H

#include "libqsgsgamelogicglobal.h"

class Player;
class Card;


class RoomRequestReceiver
{
    // DO NOT INHERIT QObject HERE!!!
    // It is intended to be inherited by Socket/UI/AI, and wait for their reply
    // Because all these components needs to inherit QObject, so this class should not inherit QObject
public:
    virtual ~RoomRequestReceiver();

    virtual bool doRequest(const QVariant &request) = 0; // REMEMBER TO CLEAR m_result!!!
    virtual QVariant waitForResult(int timeout);

protected:
    RoomRequestReceiver();
    virtual void resultReceived(const QVariant &result);

    QVariant m_result;

    QWaitCondition m_cond;
    QMutex m_mutex;

private:
    Q_DISABLE_COPY(RoomRequestReceiver)
};

class RoomObject;

class RoomRequestHandler final
{
    // There should be no class inherits RoomRequestHandler
    friend class RoomObject;

public:
    RoomRequestHandler(RoomRequestReceiver *receiver);
    ~RoomRequestHandler();

    QVariant requestReceiver(const QVariant &request);

    RoomRequestReceiver *receiver() const;

private:
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

protected:
    Q_DECLARE_PRIVATE(RoomObject)
    RoomObjectPrivate *d_ptr;
};

#endif // ROOMOBJECT_H
