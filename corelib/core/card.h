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

#include "libqsgscoreglobal.h"



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

class CardFace;

class Card : public QObject
{
    Q_OBJECT


public:
    // enumeration type
    enum Suit {
        NoSuit = 0x0,
        Black = 0x100,
        Red = 0x200,
        Spade = Black + 1,
        Club = Black + 2,
        Heart = Red + 1,
        Diamond = Red + 2,
        Tbd = -1
    };
    Q_ENUM(Suit)
    static const Suit AllSuits[4];

    // constructor
    explicit Card(const QString &cardFaceName, Suit suit = Card::Tbd, int number = -1, int id = -1);
    explicit Card(const CardFace *cardFace, Suit suit = Card::Tbd, int number = -1, int id = -1);

    // property getters/setters
    int id() const;
    void setId(int id);
    int effectiveId() const;

    QString suitString() const;
    Suit suit() const;
    void setSuit(Suit suit);

    bool isRed() const;
    bool isBlack() const;
    Suit color() const;
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
    bool hasFlag(const QString &flag);
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
    const CardFace *cardFace() const;

    // static functions
    static bool CompareByNumber(const Card *a, const Card *b);
    static bool CompareBySuit(const Card *a, const Card *b);
    static Card *Clone(const Card *card);
    static QString Suit2String(Suit suit);
    static const int S_UNKNOWN_CARD_ID;


private:
    QString m_cardFaceName;
    QList<int> m_subcards;
    bool m_mute;
    bool m_canRecast;
    bool m_transferable;
    Suit m_suit;
    int m_number;
    int m_id;
    QString m_skillName;

    QString m_showSkill;

    QStringList m_flags;
};

class CardFace
{
public:
    enum HandlingMethod
    {
        NoMethod,
        Use,
        Response,
        Discard,
        Recast,
        Pindian
    };
    Q_ENUM(HandlingMethod)

    // card types
    enum CardType
    {
        Skill,
        Basic,
        Equip,
        Trick
    };
    Q_ENUM(CardType)


    // In fact there is no such grammar in C++, but I set it here.
    // Every subclass should own this function.
#if 0
    static virtual CardFace *instance() = 0;
#endif
    virtual ~CardFace();

    virtual bool willThrow() const;
    virtual bool hasPreAction() const;
    virtual HandlingMethod handlingMethod() const;

    virtual CardType typeId() const = 0;
    virtual bool isNDTrick() const;
    virtual QString package() const;

    // card target selection
    virtual bool targetFixed() const;
    virtual bool targetsFeasible(const QList<const Player *> &targets, const Player *Self) const;
    // @todo: the following two functions should be merged into one.
    virtual bool targetFilter(const QList<const Player *> &targets, const Player *to_select, const Player *Self) const;
    virtual bool targetFilter(const QList<const Player *> &targets, const Player *to_select, const Player *Self, int &maxVotes) const;
    virtual bool isAvailable(const Player *player) const;

    virtual const Card *validate(CardUseStruct &cardUse) const;
    virtual const Card *validateInResponse(ServerPlayer *user) const;

    virtual void doPreAction(Room *room, const CardUseStruct &card_use) const;
    virtual void onUse(Room *room, const CardUseStruct &card_use) const;
    virtual void use(Room *room, ServerPlayer *source, QList<ServerPlayer *> &targets) const;
    virtual void onEffect(const CardEffectStruct &effect) const;
    virtual bool isCancelable(const CardEffectStruct &effect) const;

    virtual QStringList checkTargetModSkillShow(const CardUseStruct & /* use */) const;

    virtual void onNullified(ServerPlayer * /* target */) const;

protected:
    explicit CardFace(const QString &name);

    HandlingMethod m_handlingMethod;

    bool m_targetFixed;
    bool m_willThrow;
    bool m_hasPreact;

};

class DummyCardFace : public CardFace
{
    static DummyCardFace *instance();

    virtual CardType typeId() const final override;

private:
    static DummyCardFace *self;
    DummyCardFace();
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

