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
#include "player.h"

class Card;
class ServerPlayer;
class Room;

class Skill : public QObject
{
    Q_OBJECT

public:

    explicit Skill(const QString &name, QSgsEnum::SkillFrequency frequent = QSgsEnum::SkillFrequency::NotFrequent);
    bool isLordSkill() const;
    bool isAttachedLordSkill() const;
    QString description(bool inToolTip = true) const;
    QString notice(int index) const;
    bool isVisible() const;

//    virtual int getEffectIndex(const ServerPlayer *player, const Card *card) const;
//    virtual QDialog *getDialog() const;

//    virtual QString getGuhuoBox() const;

//    void initMediaSource();
//    void playAudioEffect(int index = -1) const;
    QSgsEnum::SkillFrequency frequency() const;
    QString limitMark() const;
//    QStringList getSources(const QString &general, const int skinId) const;
//    QStringList getSources() const;

    virtual bool canPreshow() const;
    virtual bool relateToPlace(bool head = true) const;

    //for LUA
    inline void setRelateToPlace(const char *rtp)
    {
        m_relateToPlace = rtp;
    }

protected:
    QSgsEnum::SkillFrequency m_frequency;
    QString m_limitMark;
    QString m_relateToPlace;
    bool m_attachedLordSkill;

private:
    bool m_lordSkill;
    //QStringList sources;
    //mutable QHash<const QString, QStringList> skinSourceHash;
};

class ViewAsSkill : public Skill
{
    Q_OBJECT

public:
    ViewAsSkill(const QString &name);

    virtual bool viewFilter(const QList<Card *> &selected, const Card *to_select) const = 0;
    virtual const Card *viewAs(const QList<Card *> &cards) const = 0;

    bool isAvailable(const Player *invoker, QSgsEnum::CardUseReason reason, const QString &pattern) const;
    virtual bool isEnabledAtPlay(const Player *player) const;
    virtual bool isEnabledAtResponse(const Player *player, const QString &pattern) const;
    virtual bool isEnabledAtNullification(const ServerPlayer *player) const;
    static const ViewAsSkill *parseViewAsSkill(const Skill *skill);

    inline bool isResponseOrUse() const
    {
        return m_responseOrUse;
    }
    inline QString expandPile() const
    {
        return m_expandPile;
    }

protected:
    QString m_responsePattern;
    bool m_responseOrUse;
    QString m_expandPile;
};

class ZeroCardViewAsSkill : public ViewAsSkill
{
    Q_OBJECT

public:
    ZeroCardViewAsSkill(const QString &name);

    virtual bool viewFilter(const QList<Card *> &selected, const Card *to_select) const;
    virtual const Card *viewAs(const QList<Card *> &cards) const;
    virtual const Card *viewAs() const = 0;
};

class OneCardViewAsSkill : public ViewAsSkill
{
    Q_OBJECT

public:
    OneCardViewAsSkill(const QString &name);

    virtual bool viewFilter(const QList<Card *> &selected, const Card *to_select) const;
    virtual const Card *viewAs(const QList<Card *> &cards) const;

    virtual bool viewFilter(const Card *to_select) const;
    virtual const Card *viewAs(const Card *originalCard) const = 0;

protected:
    QString m_filterPattern;
};

class FilterSkill : public OneCardViewAsSkill
{
    Q_OBJECT

public:
    FilterSkill(const QString &name);
};

typedef QMap<ServerPlayer *, QStringList> TriggerList;

class TriggerSkill : public Skill
{
    Q_OBJECT

public:
    TriggerSkill(const QString &name);
    const ViewAsSkill *viewAsSkill() const;
    QList<QSgsEnum::TriggerEvent> triggerEvents() const;

    virtual int priority() const;
    //virtual double getDynamicPriority(TriggerEvent e) const;
    //     double getCurrentPriority() const
    //     {
    //         return current_priority;
    //     }
    //     void setCurrentPriority(double p) const
    //     {
    //         current_priority = p;
    //     }

    void insertPriority(QSgsEnum::TriggerEvent e, double value);

    virtual bool triggerable(const ServerPlayer *target) const;

    virtual void record(QSgsEnum::TriggerEvent triggerEvent, Room *room, ServerPlayer *player, QVariant &data) const;

    virtual TriggerList triggerable(QSgsEnum::TriggerEvent triggerEvent, Room *room, ServerPlayer *player, QVariant &data) const;
    virtual QStringList triggerable(QSgsEnum::TriggerEvent triggerEvent, Room *room, ServerPlayer *player, QVariant &data, ServerPlayer* &ask_who) const;
    virtual bool cost(QSgsEnum::TriggerEvent triggerEvent, Room *room, ServerPlayer *player, QVariant &data, ServerPlayer *ask_who = nullptr) const;
    virtual bool effect(QSgsEnum::TriggerEvent triggerEvent, Room *room, ServerPlayer *player, QVariant &data, ServerPlayer *ask_who = nullptr) const;

    inline bool isGlobal() const
    {
        return m_global;
    }

    virtual ~TriggerSkill();

protected:
    const ViewAsSkill *m_viewAsSkill;
    QList<QSgsEnum::TriggerEvent> m_events;
    bool m_global;
    QHash<QSgsEnum::TriggerEvent, double> m_priority;

//private:
//    mutable double current_priority;
};

class Scenario;

//class ScenarioRule : public TriggerSkill
//{
//    Q_OBJECT

//public:
//    ScenarioRule(Scenario *scenario);

//    virtual int m_priority() const;
//    virtual bool triggerable(const ServerPlayer *target) const;
//};

class MasochismSkill : public TriggerSkill
{
    Q_OBJECT

public:
    MasochismSkill(const QString &name);

    virtual bool cost(QSgsEnum::TriggerEvent triggerEvent, Room *room, ServerPlayer *player, QVariant &data, ServerPlayer *ask_who = nullptr) const;
    virtual bool effect(QSgsEnum::TriggerEvent triggerEvent, Room *room, ServerPlayer *player, QVariant &data, ServerPlayer *ask_who = nullptr) const;
    virtual void onDamaged(ServerPlayer *target, const DamageStruct &damage) const = 0;
};

class PhaseChangeSkill : public TriggerSkill
{
    Q_OBJECT

public:
    PhaseChangeSkill(const QString &name);

    virtual bool effect(QSgsEnum::TriggerEvent triggerEvent, Room *room, ServerPlayer *player, QVariant &data, ServerPlayer *ask_who = nullptr) const;
    virtual bool onPhaseChange(ServerPlayer *target) const = 0;
};

class DrawCardsSkill : public TriggerSkill
{
    Q_OBJECT

public:
    DrawCardsSkill(const QString &name);

    virtual bool effect(QSgsEnum::TriggerEvent triggerEvent, Room *room, ServerPlayer *player, QVariant &data, ServerPlayer *ask_who = nullptr) const;
    virtual int getDrawNum(ServerPlayer *player, int n) const = 0;
};

class GameStartSkill : public TriggerSkill
{
    Q_OBJECT

public:
    GameStartSkill(const QString &name);

    virtual bool effect(QSgsEnum::TriggerEvent triggerEvent, Room *room, ServerPlayer *player, QVariant &data, ServerPlayer *ask_who = nullptr) const;
    virtual void onGameStart(ServerPlayer *player) const = 0;
};

class BattleArraySkill : public TriggerSkill
{
    Q_OBJECT

public:

    BattleArraySkill(const QString &name, const QSgsEnum::ArrayType type);
    virtual bool triggerable(const ServerPlayer *player) const;

    virtual void summonFriends(ServerPlayer *player) const;

    inline QSgsEnum::ArrayType getArrayType() const
    {
        return m_arrayType;
    }
private:
    QSgsEnum::ArrayType m_arrayType;
};

class ArraySummonSkill : public ZeroCardViewAsSkill
{
    Q_OBJECT

public:

    ArraySummonSkill(const QString &name);

    const Card *viewAs() const;
    virtual bool isEnabledAtPlay(const Player *player) const;
};

class ProhibitSkill : public Skill
{
    Q_OBJECT

public:
    ProhibitSkill(const QString &name);

    virtual bool isProhibited(const Player *from, const Player *to, const Card *card, const QList<const Player *> &others = QList<const Player *>()) const = 0;
};

class DistanceSkill : public Skill
{
    Q_OBJECT

public:
    DistanceSkill(const QString &name);

    virtual int getCorrect(const Player *from, const Player *to) const = 0;
};

class MaxCardsSkill : public Skill
{
    Q_OBJECT

public:
    MaxCardsSkill(const QString &name);

    virtual int getExtra(const ServerPlayer *target/*, MaxCardsType::MaxCardsCount type = MaxCardsType::Max*/) const;
    virtual int getFixed(const ServerPlayer *target/*, MaxCardsType::MaxCardsCount type = MaxCardsType::Max*/) const;
};

class TargetModSkill : public Skill
{
    Q_OBJECT

public:
    TargetModSkill(const QString &name);
    virtual QString pattern() const;

    virtual int residueNum(const Player *from, const Card *card) const;
    virtual int distanceLimit(const Player *from, const Card *card) const;
    virtual int extraTargetNum(const Player *from, const Card *card) const;

protected:
    QString m_pattern;
};

class SlashNoDistanceLimitSkill : public TargetModSkill
{
    Q_OBJECT

public:
    SlashNoDistanceLimitSkill(const QString &skill_name);

    virtual int distanceLimit(const Player *from, const Card *card) const;

protected:
    QString m_name;
};

class AttackRangeSkill : public Skill
{
    Q_OBJECT

public:
    AttackRangeSkill(const QString &name);

    virtual int extra(const Player *target, bool include_weapon) const;
    virtual int fixed(const Player *target, bool include_weapon) const;
};


// a nasty way for 'fake moves', usually used in the process of multi-card chosen
class FakeMoveSkill : public TriggerSkill
{
    Q_OBJECT

public:
    FakeMoveSkill(const QString &skillname);

    virtual int priority() const;
    virtual QStringList triggerable(QSgsEnum::TriggerEvent, Room *, ServerPlayer *target, QVariant &, ServerPlayer * &ask_who) const;
    virtual bool effect(QSgsEnum::TriggerEvent triggerEvent, Room *room, ServerPlayer *player, QVariant &data, ServerPlayer *ask_who = nullptr) const;

private:
    QString m_name;
};

class DetachEffectSkill : public TriggerSkill
{
    Q_OBJECT

public:
    DetachEffectSkill(const QString &skillname, const QString &pilename = QString());

    virtual QStringList triggerable(QSgsEnum::TriggerEvent triggerEvent, Room *room, ServerPlayer *player, QVariant &data, ServerPlayer * &ask_who) const;
    virtual bool effect(QSgsEnum::TriggerEvent triggerEvent, Room *room, ServerPlayer *player, QVariant &data, ServerPlayer *ask_who = nullptr) const;
    virtual void onSkillDetached(Room *room, ServerPlayer *player) const;

private:
    QString m_name, m_pileName;
};

class WeaponSkill : public TriggerSkill
{
    Q_OBJECT

public:
    WeaponSkill(const QString &name);

    virtual int priority() const;
    virtual bool triggerable(const ServerPlayer *target) const;
};

class ArmorSkill : public TriggerSkill
{
    Q_OBJECT

public:
    ArmorSkill(const QString &name);

    virtual int priority() const;
    virtual bool triggerable(const ServerPlayer *target) const;
};

class TreasureSkill : public TriggerSkill
{
    Q_OBJECT

public:
    TreasureSkill(const QString &name);

    virtual int priority() const;
    virtual bool triggerable(const ServerPlayer *target) const;
};

#endif

