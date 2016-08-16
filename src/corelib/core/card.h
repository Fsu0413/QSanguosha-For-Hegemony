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

#include <QObject>
#include <QMap>
#include <QIcon>

class Room;
class Player;
class ServerPlayer;
class Client;
class ClientPlayer;
class CardItem;

struct CardEffectStruct;
struct CardUseStruct;



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

    Q_ENUMS(Suit)
    Q_ENUMS(CardType)
    Q_ENUMS(HandlingMethod)

public:
    // enumeration type
    enum class Suit {
        NoSuit = 0x0,
        Black = 0x100,
        Red = 0x200,
        Spade = Black + 1,
        Club = Black + 2,
        Heart = Red + 1,
        Diamond = Red + 2,
        Tbd = -1
    };

    enum Color
    {
        Red, Black, Colorless
    };
    enum HandlingMethod
    {
        MethodNone, MethodUse, MethodResponse, MethodDiscard, MethodRecast, MethodPindian
    };

    static const Suit AllSuits[4];

    // card types
    enum CardType
    {
        TypeSkill, TypeBasic, TypeTrick, TypeEquip
    };

    // constructor
    Card(Suit suit, int number, bool target_fixed = false);

    // property getters/setters
    QString suitString() const;
    bool isRed() const;
    bool isBlack() const;
    int id() const;
    virtual void setId(int id);
    int effectiveId() const;

    int number() const;
    virtual void setNumber(int number);
    QString numberString() const;

    Suit suit() const;
    virtual void setSuit(Suit suit);

    bool sameColorWith(const Card *other) const;
    Color color() const;
    QString fullName(bool include_suit = false) const;
    QString logName() const;
    QString name() const;
    QString skillName(bool removePrefix = true) const;
    virtual void setSkillName(const QString &skill_name);
    QString description(bool inToolTip = true) const;

    virtual bool isMute() const;
    virtual bool willThrow() const;
    virtual bool canRecast() const;
    virtual bool hasPreAction() const;
    virtual Card::HandlingMethod handlingMethod() const;
    void canRecast(bool can);

    virtual void setFlags(const QString &flag) const;
    inline virtual void setFlags(const QStringList &fs)
    {
        m_flags = fs;
    }
    bool hasFlag(const QString &flag) const;
    virtual void clearFlags() const;

    virtual QString package() const;
    inline virtual QString className() const;
    virtual bool isVirtualCard() const;
    virtual bool isEquipped() const;
    virtual QString commonEffectName() const;
    virtual bool match(const QString &pattern) const;

    virtual void addSubcard(int card_id);
    virtual void addSubcard(const Card *card);
    virtual QList<int> subcards() const;
    virtual void clearSubcards();
    virtual QString subcardString() const;
    virtual void addSubcards(const QList<const Card *> &cards);
    virtual void addSubcards(const QList<int> &subcards_list);
    virtual int subcardsLength() const;

    virtual QString type() const = 0;
    virtual QString subtype() const = 0;
    virtual CardType typeId() const = 0;
    virtual bool isNDTrick() const;

    // card target selection
    virtual bool targetFixed() const;
    virtual bool targetsFeasible(const QList<const Player *> &targets, const Player *Self) const;
    // @todo: the following two functions should be merged into one.
    virtual bool targetFilter(const QList<const Player *> &targets, const Player *to_select, const Player *Self) const;
    virtual bool targetFilter(const QList<const Player *> &targets, const Player *to_select, const Player *Self,
        int &maxVotes) const;
    virtual bool isAvailable(const Player *player) const;

    inline virtual const Card *realCard() const
    {
        return this;
    }
    virtual const Card *validate(CardUseStruct &cardUse) const;
    virtual const Card *validateInResponse(ServerPlayer *user) const;

    virtual void doPreAction(Room *room, const CardUseStruct &card_use) const;
    virtual void onUse(Room *room, const CardUseStruct &card_use) const;
    virtual void use(Room *room, ServerPlayer *source, QList<ServerPlayer *> &targets) const;
    virtual void onEffect(const CardEffectStruct &effect) const;
    virtual bool isCancelable(const CardEffectStruct &effect) const;

    inline virtual QStringList checkTargetModSkillShow(const CardUseStruct & /* use */) const
    {
        return QStringList();
    }

    virtual QString showSkill() const;
    virtual void setShowSkill(const QString &skill_name);

    inline virtual bool isKindOf(const char *cardType) const
    {
        Q_ASSERT(cardType); return inherits(cardType);
    }
    inline virtual QStringList flags() const
    {
        return m_flags;
    }

    inline virtual bool isModified() const
    {
        return false;
    }
    inline virtual void onNullified(ServerPlayer * /* target */) const
    {
        return;
    }

    // static functions
    static bool CompareByNumber(const Card *a, const Card *b);
    static bool CompareBySuit(const Card *a, const Card *b);
    static bool CompareByType(const Card *a, const Card *b);
    static Card *Clone(const Card *card);
    static QString Suit2String(Suit suit);
    static const int S_UNKNOWN_CARD_ID;

    static const Card *Parse(const QString &str);
    virtual QString toString(bool hidden = false) const;

    virtual QString effectName() const;

    virtual bool isTransferable() const;
    virtual void setTransferable(const bool transferbale);

protected:
    QList<int> m_subcards;
    bool m_targetixed;
    bool m_mute;
    bool m_willThrow;
    bool m_hasPreact;
    bool m_canRecast;
    bool m_transferable;
    Suit m_suit;
    int m_number;
    int m_id;
    QString m_skillName;
    Card::HandlingMethod m_handlingMethod;

    QString m_showSkill;

    mutable QStringList m_flags;
};

typedef QList<const Card *> CardList;

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

