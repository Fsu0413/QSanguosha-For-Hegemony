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

class Player;
class Card;

class CardPattern
{
public:
    virtual bool match(const Player *player, const Card *card) const = 0;
    virtual bool willThrow() const
    {
        return true;
    }
    virtual QString patternString() const
    {
        return QString();
    }

    virtual ~CardPattern()
    {
    }
};

class Card : public QObject
{
    Q_OBJECT

public:


    static const QSgsEnum::CardSuit AllSuits[4];

    // constructor
    explicit Card(const QString &cardFaceName, QSgsEnum::CardSuit suit = QSgsEnum::CardSuit::Tbd, int number = -1, int id = -1);

    // property getters/setters
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

    QString fullName(bool include_suit = false) const;
    QString logName() const;
    QString name() const;
    QString description(bool inToolTip = true) const;

    QString skillName(bool removePrefix = true) const;
    void setSkillName(const QString &skill_name);
    QString effectName() const;
    QString commonEffectName() const;

    bool isMute() const;

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

    void addSubcard(int card_id);
    void addSubcard(const Card *card);
    QList<int> subcards() const;
    void clearSubcards();
    QString subcardString() const;
    void addSubcards(const QList<const Card *> &cards);
    void addSubcards(const QList<int> &subcards_list);
    int subcardsLength() const;

    QString showSkill() const;
    void setShowSkill(const QString &skill_name);

    bool isKindOf(const char *cardType) const;
    QStringList flags() const;

    bool isModified() const;

    const QString &cardFaceName() const;

    // static functions
    static QString Suit2String(QSgsEnum::CardSuit suit);
    static const int S_UNKNOWN_CARD_ID;


private:
    QString m_cardFaceName;
    QList<int> m_subcards;
    bool m_mute;
    bool m_canRecast;
    bool m_transferable;
    QSgsEnum::CardSuit m_suit;
    int m_number;
    int m_id;
    QString m_skillName;

    QString m_showSkill;

    QStringList m_flags;
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

    virtual void extraCost(Room *room, const CardUseStruct &card_use) const;

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

