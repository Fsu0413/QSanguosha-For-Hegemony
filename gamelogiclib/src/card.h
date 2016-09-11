/********************************************************************
    Copyright (c) 2013-2015 - Mogara

    This file is part of QSanguosha-Hegemony.

    This game is free software; you can redistribute it and/or
    modify it under the terms of the GNU General Public License as
    published by the Free Software Foundation; either version 3.0
    of the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    General Public License for more details.

    See the LICENSE file for more details.

    Mogara
    *********************************************************************/

#ifndef _CARD_H
#define _CARD_H

#include "libqsgsgamelogicglobal.h"
#include "enumeration.h"

class CardPrivate;
class CardFace;
class RoomObject;

// Make Card a final class, we subclass a class called CardFace to make card functional
class LIBQSGSGAMELOGIC_EXPORT Card final: public QObject
{
    Q_OBJECT

public:
    static const QSgsEnum::CardSuit AllSuits[4];

    // note that if this card is created in QSgsLogicCore, the roomObject variable should be nullptr
    // virtual cards should always have their corresponding roomObject
    Card(RoomObject *roomObject, const CardFace *cardFace, QSgsEnum::CardSuit suit = QSgsEnum::CardSuit::Tbd, int number = -1, bool canRecast = false, bool transferable = false, int id = -1);
    // This dtor is not virtual!!!!
    ~Card();

    int id() const;
    void setId(int id);
    int effectiveId() const;

    QString suitString() const;
    QSgsEnum::CardSuit suit() const;
    void setSuit(QSgsEnum::CardSuit suit);

    bool isRed() const;
    bool isBlack() const;
    QSgsEnum::CardSuit color() const;
    bool sameColorWith(const Card *other) const;

    int number() const;
    void setNumber(int number);
    QString numberString() const;

    QString fullName(bool includeSuit = false) const;
    QString logName() const;
    QString name() const;
    QString description(bool inToolTip = true) const;

    const QString &skillName() const;
    void setSkillName(const QString &skill_name);
    QString effectName() const;
    QString commonEffectName() const;

    bool mute() const;

    bool canRecast() const;
    void setCanRecast(bool can);

    bool isTransferable() const;
    void setTransferable(bool transferbale);

    void setFlag(const QString &flag);
    void setFlags(const QStringList &fs);
    bool hasFlag(const QString &flag) const;
    void clearFlags();

    bool isVirtualCard() const;
    bool isEquipped() const;
    bool match(const QString &pattern) const;

    void addSubcard(int cardId);
    void addSubcard(Card *card);
    QList<const Card *> subcards() const;
    const QList<Card *> &subcards();
    void clearSubcards();
    QString subcardString() const;
    void addSubcards(const QList<Card *> &cards);
    void addSubcards(const QList<int> &subcardsList);
    int subcardsLength() const;

    const QString &showSkill() const;
    void setShowSkill(const QString &skillName);

    const QStringList &flags() const;

    const QString &cardFaceName() const;

    // static functions
    static QString Suit2String(QSgsEnum::CardSuit suit);
    static const int S_UNKNOWN_CARD_ID;


private:
    Q_DECLARE_PRIVATE(Card)
    CardPrivate *d_ptr;
};

#if 0
class SkillCard : public Card
{
    Q_OBJECT

public:
    SkillCard();
    void setUserString(const QString &userString);
    QString userString() const;

    virtual QString subtype() const;
    virtual QString type() const;
    virtual CardType typeId() const;
    virtual QString toString(bool hidden = false) const;

    virtual void extraCost(RoomObject *room, const CardUseStruct &card_use) const;

protected:
    QString m_userString;
};

class ArraySummonCard : public SkillCard
{
    Q_OBJECT

public:
    Q_INVOKABLE ArraySummonCard(const QString &name);

    const Card *validate(CardUseStruct &card_use) const;
};

class TransferCard : public SkillCard
{
    Q_OBJECT

public:
    Q_INVOKABLE TransferCard();

    virtual bool targetFilter(const QList<const Player *> &targets, const Player *to_select, const Player *Self) const;
    virtual void onEffect(const CardEffectStruct &effect) const;
};

class DummyCard : public SkillCard
{
    Q_OBJECT

public:
    DummyCard();
    DummyCard(const QList<int> &m_subcards);

    virtual QString subtype() const;
    virtual QString type() const;
    virtual QString toString(bool hidden = false) const;
};
#endif
#endif

