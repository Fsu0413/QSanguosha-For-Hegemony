#ifndef ROOMOBJECT_H
#define ROOMOBJECT_H

#include <QObject>
#include <QList>
#include <QHash>

class RoomObject : public QObject
{
    Q_OBJECT


public:
    explicit RoomObject(QObject *parent = 0);

    struct CardPlaceStruct
    {
        Player *player;
        Player::Place place;
    };

    void addRealCard(Card *card);
    void addRealCards(QList<Card *> cards);
    void addVirtualCard(Card *card);

    const QList<Card *> &cards() const; // return m_availableCards;
    const QList<Player *> &players() const; // return m_players;

    const QString &currentCardUsePattern() const; // return m_currentCardUsePattern;
    CardUseStruct::CardUseReason currentCardUseReason() const; // return m_currentCardUseReason;

    QList<Card *> &drawPile();
    const QList<Card *> &drawPile() const;

    const QList<Card *> &discardPile() const;

    const CardPlaceStruct &cardPlace(Card *card) const; // using the const functions of the QHash to get the place of a card

protected:
    QList<Card *> m_availableCards;
    QList<Player *> m_players;

    QString m_currentCardUsePattern;
    CardUseStruct::CardUseReason m_currentCardUseReason;

    QList<Card *> m_drawPile;
    QList<Card *> m_discardPile;
    QList<Card *> m_proceedingArea;

    QHash<Card *, CardPlaceStruct> m_cardPlaces;

};

#endif // ROOMOBJECT_H
