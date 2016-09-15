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

#ifndef _SKILL_H
#define _SKILL_H

#include "libqsgsgamelogicglobal.h"
#include "enumeration.h"
#include "structs.h"

class Card;
class RoomObject;
class Player;
class SkillPrivate;

class LIBQSGSGAMELOGIC_EXPORT Skill : public QObject
{
    Q_OBJECT

public:
    virtual ~Skill(); // = 0?

    bool isLordSkill() const;
    void setLordSkill(bool l);
    bool isAttachedSkill() const;
    void setAttachedSkill(bool a);
    bool isVisible() const;
    void setVisible(bool v);
    const QString &limitMark() const;
    void setLimitMark(const QString &lm);
    bool canPreshow() const;
    void setCanPreshow(bool c);

    QSgsEnum::SkillFrequency frequency() const;

    // Note: Both functions should return true for skills without a description of head skill or deputy skill
    bool isHeadSkill() const;
    bool isDeputySkill() const;

protected:
    explicit Skill(const QString &name, QSgsEnum::SkillFrequency frequency = QSgsEnum::SkillFrequency::NotFrequent, QSgsEnum::SkillPlace place = QSgsEnum::SkillPlace::Both);

    Q_DECLARE_PRIVATE(Skill)
    SkillPrivate *d_ptr;
};

class ViewAsSkillPrivate;

class LIBQSGSGAMELOGIC_EXPORT ViewAsSkill : public Skill
{
    Q_OBJECT

public:
    virtual ~ViewAsSkill() override;

    virtual bool viewFilter(const QList<Card *> &selected, Card *to_select, const Player *player, QSgsEnum::CardUseReason reason, const QString &pattern) const = 0;
    virtual Card *viewAs(const QList<Card *> &cards, const Player *player, QSgsEnum::CardUseReason reason, const QString &pattern) const = 0;

    bool isAvailable(const Player *invoker, QSgsEnum::CardUseReason reason, const QString &pattern) const;
    virtual bool isEnabledAtPlay(const Player *player) const;
    virtual bool isEnabledAtResponse(const Player *player, QSgsEnum::CardUseReason reason, const QString &pattern) const;
    virtual bool isEnabledAtNullification(const Player *player) const;

    bool isResponseOrUse() const;
    const QString &expandPile() const;

    const QString &responsePattern() const;
    void setResponsePattern(const QString &pattern);

protected:
    explicit ViewAsSkill(const QString &name, QSgsEnum::SkillFrequency frequency = QSgsEnum::SkillFrequency::NotFrequent, QSgsEnum::SkillPlace place = QSgsEnum::SkillPlace::Both);

    Q_DECLARE_PRIVATE_D(d_ptr_viewAsSkill, ViewAsSkill)
    ViewAsSkillPrivate *d_ptr_viewAsSkill;
};

// In this form ProactiveSkill generates a generic skill cardface
// One can override ViewAs which generates other cards
class LIBQSGSGAMELOGIC_EXPORT ProactiveSkill : public ViewAsSkill
{
    Q_OBJECT

public:
    // default is zero-card
    virtual bool cardFilter(const QList<Card *> &selected, Card *toSelect, const Player *player, QSgsEnum::CardUseReason reason, const QString &pattern) const;
    virtual bool cardFeasible(const QList<Card *> &selected, const Player *player, QSgsEnum::CardUseReason reason, const QString &pattern) const;

    // default is an other player
    virtual bool playerFilter(const QList<const Player *> &selected, const Player *toSelect, const Player *player, QSgsEnum::CardUseReason reason, const QString &pattern, int *maxVotes = nullptr) const;
    virtual bool playerFeasible(const QList<const Player *> &selected, const Player *player, QSgsEnum::CardUseReason reason, const QString &pattern) const;

    // default for cost is no-op
    virtual void cost(const SkillInvokeStruct &invoke) const;
    virtual void effect(const SkillInvokeStruct &invoke) const = 0;

protected:
    explicit ProactiveSkill(const QString &name, QSgsEnum::SkillFrequency frequency = QSgsEnum::SkillFrequency::NotFrequent, QSgsEnum::SkillPlace place = QSgsEnum::SkillPlace::Both);

    virtual bool viewFilter(const QList<Card *> &selected, Card *to_select, const Player *player, QSgsEnum::CardUseReason reason, const QString &pattern) const override;
    virtual Card *viewAs(const QList<Card *> &cards, const Player *player, QSgsEnum::CardUseReason reason, const QString &pattern) const override;
};

// Note: The effect of BattleArraySkill is designed in other skills, this skill only do summon friends
class LIBQSGSGAMELOGIC_EXPORT BattleArraySkill final : public ProactiveSkill
{
    Q_OBJECT

public:
    explicit BattleArraySkill(const QString &name, QSgsEnum::SkillPlace place = QSgsEnum::SkillPlace::Both);

    bool playerFilter(const QList<const Player *> &selected, const Player *toSelect, const Player *player, QSgsEnum::CardUseReason reason, const QString &pattern, int *maxVotes) const final override;
    bool playerFeasible(const QList<const Player *> &selected, const Player *player, QSgsEnum::CardUseReason reason, const QString &pattern) const final override;

    void effect(const SkillInvokeStruct &invoke) const final override;
};

class LIBQSGSGAMELOGIC_EXPORT ZeroCardViewAsSkill : public ViewAsSkill
{
    Q_OBJECT

public:
    bool viewFilter(const QList<Card *> &selected, Card *toSelect, const Player *player, QSgsEnum::CardUseReason reason, const QString &pattern) const final override;
    Card *viewAs(const QList<Card *> &cards, const Player *player, QSgsEnum::CardUseReason reason, const QString &pattern) const final override;

    virtual Card *viewAs(const Player *player, QSgsEnum::CardUseReason reason, const QString &pattern) const = 0;

protected:
    explicit ZeroCardViewAsSkill(const QString &name, QSgsEnum::SkillFrequency frequency = QSgsEnum::SkillFrequency::NotFrequent, QSgsEnum::SkillPlace place = QSgsEnum::SkillPlace::Both);
};

class OneCardViewAsSkillPrivate;

class LIBQSGSGAMELOGIC_EXPORT OneCardViewAsSkill : public ViewAsSkill
{
    Q_OBJECT

public:
    virtual ~OneCardViewAsSkill() override;

    bool viewFilter(const QList<Card *> &selected, Card *toSelect, const Player *player, QSgsEnum::CardUseReason reason, const QString &pattern) const final override;
    Card *viewAs(const QList<Card *> &cards, const Player *player, QSgsEnum::CardUseReason reason, const QString &pattern) const final override;

    virtual bool viewFilter(Card *card, const Player *player, QSgsEnum::CardUseReason reason, const QString &pattern) const;
    virtual Card *viewAs(Card *originalCard, const Player *player, QSgsEnum::CardUseReason reason, const QString &pattern) const = 0;

protected:
    explicit OneCardViewAsSkill(const QString &name, QSgsEnum::SkillFrequency frequency = QSgsEnum::SkillFrequency::NotFrequent, QSgsEnum::SkillPlace place = QSgsEnum::SkillPlace::Both);

    Q_DECLARE_PRIVATE_D(d_ptr_oneCardViewAsSkill, OneCardViewAsSkill)
    OneCardViewAsSkillPrivate *d_ptr_oneCardViewAsSkill;
};

class LIBQSGSGAMELOGIC_EXPORT CardTransformSkill : public Skill
{
    Q_OBJECT

public:
    CardTransformSkill(const QString &name, QSgsEnum::SkillPlace place = QSgsEnum::SkillPlace::Both); // frequency is limited to Compulsory

    virtual bool viewFilter(Card *to_select) const = 0;
    virtual Card *viewAs(Card *originalCard) const = 0;
};

class TriggerSkillPrivate;

class LIBQSGSGAMELOGIC_EXPORT TriggerSkill : public Skill
{
    Q_OBJECT

public:
    virtual ~TriggerSkill() override;
    const QList<QSgsEnum::TriggerEvent> &triggerEvents() const;
    void addTriggerEvent(QSgsEnum::TriggerEvent triggerEvent);

    int priority() const;
    void setPriority(int priority);

    bool isGlobal() const;
    void setGlobal(bool global);

    virtual void record(QSgsEnum::TriggerEvent triggerEvent, RoomObject *room, Player *player, const QVariant &data) const;
    virtual QList<SkillTriggerStruct> triggerable(QSgsEnum::TriggerEvent triggerEvent, const RoomObject *room, const Player *player, const QVariant &data) const = 0;
    virtual bool cost(QSgsEnum::TriggerEvent triggerEvent, RoomObject *room, QSharedPointer<SkillTriggerStruct> invoke, Player *player, QVariant &data) const;
    virtual bool effect(QSgsEnum::TriggerEvent triggerEvent, RoomObject *room, QSharedPointer<SkillTriggerStruct> invoke, Player *player, QVariant &data) const = 0;

protected:
    explicit TriggerSkill(const QString &name, QSgsEnum::SkillFrequency frequency = QSgsEnum::SkillFrequency::NotFrequent, QSgsEnum::SkillPlace place = QSgsEnum::SkillPlace::Both);

    Q_DECLARE_PRIVATE_D(d_ptr_triggerSkill, TriggerSkill)
    TriggerSkillPrivate *d_ptr_triggerSkill;
};

class Scenario;

//class ScenarioRule : public TriggerSkill
//{
//    Q_OBJECT

//public:
//    ScenarioRule(Scenario *scenario);

//    virtual int m_priority() const;
//    virtual bool triggerable(const Player *target) const;
//};

class LIBQSGSGAMELOGIC_EXPORT MasochismSkill : public TriggerSkill
{
    Q_OBJECT

public:
    void record(QSgsEnum::TriggerEvent triggerEvent, RoomObject *room, Player *player, const QVariant &data) const final override;
    QList<SkillTriggerStruct> triggerable(QSgsEnum::TriggerEvent triggerEvent, const RoomObject *room, const Player *player, const QVariant &data) const final override;
    bool cost(QSgsEnum::TriggerEvent triggerEvent, RoomObject *room, QSharedPointer<SkillTriggerStruct> invoke, Player *player, QVariant &data) const final override;
    bool effect(QSgsEnum::TriggerEvent triggerEvent, RoomObject *room, QSharedPointer<SkillTriggerStruct> invoke, Player *player, QVariant &data) const final override;

    virtual void record(QSgsEnum::TriggerEvent triggerEvent, RoomObject *room, Player *player, const DamageStruct &damage) const;
    virtual QList<SkillTriggerStruct> triggerable(QSgsEnum::TriggerEvent triggerEvent, const RoomObject *room, const Player *player, const DamageStruct &damage) const = 0;
    virtual bool cost(QSgsEnum::TriggerEvent triggerEvent, RoomObject *room, QSharedPointer<SkillTriggerStruct> invoke, Player *player, DamageStruct &damage) const;
    virtual bool effect(QSgsEnum::TriggerEvent triggerEvent, RoomObject *room, QSharedPointer<SkillTriggerStruct> invoke, Player *player, DamageStruct &damage) const = 0;

protected:
    explicit MasochismSkill(const QString &name, QSgsEnum::SkillFrequency frequency = QSgsEnum::SkillFrequency::NotFrequent, QSgsEnum::SkillPlace place = QSgsEnum::SkillPlace::Both);
};

class LIBQSGSGAMELOGIC_EXPORT PhaseChangeSkill : public TriggerSkill
{
    Q_OBJECT

public:
    explicit PhaseChangeSkill(const QString &name, QSgsEnum::SkillFrequency frequency = QSgsEnum::SkillFrequency::NotFrequent, QSgsEnum::SkillPlace place = QSgsEnum::SkillPlace::Both);
};

class LIBQSGSGAMELOGIC_EXPORT DrawCardsSkill : public TriggerSkill
{
    Q_OBJECT

public:
    void record(QSgsEnum::TriggerEvent triggerEvent, RoomObject *room, Player *player, const QVariant &data) const final override;
    QList<SkillTriggerStruct> triggerable(QSgsEnum::TriggerEvent triggerEvent, const RoomObject *room, const Player *player, const QVariant &data) const final override;
    bool cost(QSgsEnum::TriggerEvent triggerEvent, RoomObject *room, QSharedPointer<SkillTriggerStruct> invoke, Player *player, QVariant &data) const final override;
    bool effect(QSgsEnum::TriggerEvent triggerEvent, RoomObject *room, QSharedPointer<SkillTriggerStruct> invoke, Player *player, QVariant &data) const final override;

    virtual void record(QSgsEnum::TriggerEvent triggerEvent, RoomObject *room, Player *player, int n) const;
    virtual QList<SkillTriggerStruct> triggerable(QSgsEnum::TriggerEvent triggerEvent, const RoomObject *room, const Player *player, int n) const = 0;
    virtual bool cost(QSgsEnum::TriggerEvent triggerEvent, RoomObject *room, QSharedPointer<SkillTriggerStruct> invoke, Player *player, int &n) const;
    virtual bool effect(QSgsEnum::TriggerEvent triggerEvent, RoomObject *room, QSharedPointer<SkillTriggerStruct> invoke, Player *player, int &n) const = 0;

protected:
    explicit DrawCardsSkill(const QString &name, QSgsEnum::SkillFrequency frequency = QSgsEnum::SkillFrequency::NotFrequent, QSgsEnum::SkillPlace place = QSgsEnum::SkillPlace::Both);
};


// a nasty way for 'fake moves', usually used in the process of multi-card chosen. IT IS A FINAL CLASS NOW
class FakeMoveSkillPrivate;
class LIBQSGSGAMELOGIC_EXPORT FakeMoveSkill final : public TriggerSkill
{
    Q_OBJECT

public:
    explicit FakeMoveSkill(const QString &originalSkillName, QSgsEnum::SkillPlace place = QSgsEnum::SkillPlace::Both); // frequency is limited to Compulsory
    ~FakeMoveSkill() final override;

    QList<SkillTriggerStruct> triggerable(QSgsEnum::TriggerEvent triggerEvent, const RoomObject *room, const Player *player, const QVariant &data) const final override;
    bool cost(QSgsEnum::TriggerEvent triggerEvent, RoomObject *room, QSharedPointer<SkillTriggerStruct> invoke, Player *player, QVariant &data) const final override;
    bool effect(QSgsEnum::TriggerEvent triggerEvent, RoomObject *room, QSharedPointer<SkillTriggerStruct> invoke, Player *player, QVariant &data) const final override;

private:
    Q_DECLARE_PRIVATE_D(d_ptr_fakeMoveSkill, FakeMoveSkill)
    FakeMoveSkillPrivate *d_ptr_fakeMoveSkill;
};

class LIBQSGSGAMELOGIC_EXPORT EquipSkill : public TriggerSkill
{
    Q_OBJECT

protected:
    explicit EquipSkill(const QString &name, QSgsEnum::SkillFrequency frequency = QSgsEnum::SkillFrequency::NotFrequent);
};

class LIBQSGSGAMELOGIC_EXPORT WeaponSkill : public EquipSkill
{
    Q_OBJECT

protected:
    explicit WeaponSkill(const QString &name, QSgsEnum::SkillFrequency frequency = QSgsEnum::SkillFrequency::NotFrequent);
};

class LIBQSGSGAMELOGIC_EXPORT ArmorSkill : public EquipSkill
{
    Q_OBJECT

protected:
    explicit ArmorSkill(const QString &name, QSgsEnum::SkillFrequency frequency = QSgsEnum::SkillFrequency::NotFrequent);
};

class LIBQSGSGAMELOGIC_EXPORT TreasureSkill : public EquipSkill
{
    Q_OBJECT

protected:
    explicit TreasureSkill(const QString &name, QSgsEnum::SkillFrequency frequency = QSgsEnum::SkillFrequency::NotFrequent);
};

class LIBQSGSGAMELOGIC_EXPORT ProhibitSkill : public Skill
{
    Q_OBJECT

public:
    virtual bool isProhibited(const Player *from, const Player *to, Card *card) const = 0;

protected:
    explicit ProhibitSkill(const QString &name, QSgsEnum::SkillPlace place = QSgsEnum::SkillPlace::Both); // frequency is limited to Compulsory
};

class LIBQSGSGAMELOGIC_EXPORT DistanceSkill : public Skill
{
    Q_OBJECT

public:
    virtual int correct(const Player *from, const Player *to) const = 0;

protected:
    explicit DistanceSkill(const QString &name, QSgsEnum::SkillPlace place = QSgsEnum::SkillPlace::Both); // frequency is limited to Compulsory
};

class LIBQSGSGAMELOGIC_EXPORT MaxCardsSkill : public Skill
{
    Q_OBJECT

public:
    virtual int extra(const Player *target) const;
    virtual int fixed(const Player *target) const;

protected:
    explicit MaxCardsSkill(const QString &name, QSgsEnum::SkillPlace place = QSgsEnum::SkillPlace::Both); // frequency is limited to Compulsory
};

class LIBQSGSGAMELOGIC_EXPORT TargetModSkill : public Skill
{
    Q_OBJECT

public:
    virtual int residueNum(const Player *from, Card *card) const;
    virtual int distanceLimit(const Player *from, Card *card) const;
    virtual int extraTargetNum(const Player *from, Card *card) const;

protected:
    explicit TargetModSkill(const QString &name, QSgsEnum::SkillPlace place = QSgsEnum::SkillPlace::Both); // frequency is limited to Compulsory
};

class SlashNoDistanceLimitSkillPrivate;
class LIBQSGSGAMELOGIC_EXPORT SlashNoDistanceLimitSkill final : public TargetModSkill
{
    Q_OBJECT

public:
    explicit SlashNoDistanceLimitSkill(const QString &originalSkillName, QSgsEnum::SkillPlace place = QSgsEnum::SkillPlace::Both); // frequency is limited to Compulsory
    ~SlashNoDistanceLimitSkill() final override;

    int distanceLimit(const Player *from, Card *card) const final override;

private:
    Q_DECLARE_PRIVATE_D(d_ptr_slashNoDistanceLimitSkill, SlashNoDistanceLimitSkill)
    SlashNoDistanceLimitSkillPrivate *d_ptr_slashNoDistanceLimitSkill;
};

class LIBQSGSGAMELOGIC_EXPORT AttackRangeSkill : public Skill
{
    Q_OBJECT

public:
    virtual int extra(const Player *target, bool include_weapon = true) const;
    virtual int fixed(const Player *target, bool include_weapon = true) const;

protected:
    explicit AttackRangeSkill(const QString &name, QSgsEnum::SkillPlace place = QSgsEnum::SkillPlace::Both); // frequency is limited to Compulsory
};



#endif

