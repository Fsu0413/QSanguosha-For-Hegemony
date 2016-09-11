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

#include "skill.h"
#include "player.h"
#include "scenario.h"

#include "card.h"

class SkillPrivate
{
public:
    QSgsEnum::SkillFrequency frequency;
    QSgsEnum::SkillPlace relateToPlace;
    QString limitMark;
    bool attachedSkill;
    bool lordSkill;
    bool visible;
    bool canPreshow;
};

Skill::Skill(const QString &name, QSgsEnum::SkillFrequency frequency, QSgsEnum::SkillPlace place)
    : d_ptr(new SkillPrivate)
{
    setObjectName(name);
    Q_D(Skill);
    d->frequency = frequency;
    d->relateToPlace = place;
    d->attachedSkill = d->lordSkill = d->canPreshow = false;
    d->visible = true;
}

Skill::~Skill()
{
    Q_D(Skill);
    delete d;
}

bool Skill::isLordSkill() const
{
    Q_D(const Skill);
    return d->lordSkill;
}

void Skill::setLordSkill(bool l)
{
    Q_D(Skill);
    if (d->attachedSkill && l) {
        qWarning() << objectName() << QStringLiteral("is already an attached skill, It should not be set to LordSkill");
        Q_ASSERT_X(false, __FILE__ QT_STRINGIFY(__LINE__), "INVALID LORDSKILL SET");
    }
    d->lordSkill = l;
}

bool Skill::isAttachedSkill() const
{
    Q_D(const Skill);
    return d->attachedSkill;
}

void Skill::setAttachedSkill(bool a)
{
    Q_D(Skill);
    if (d->lordSkill && a) {
        qWarning() << objectName() << QStringLiteral("is already a lord skill, It should not be set to AttachedSkill");
        Q_ASSERT_X(false, __FILE__ QT_STRINGIFY(__LINE__), "INVALID ATTACHEDSKILL SET");
    }
    d->attachedSkill = a;
}

bool Skill::isVisible() const
{
    Q_D(const Skill);
    return d->visible;
}

void Skill::setVisible(bool v)
{
    Q_D(Skill);
    if (inherits("ViewAsSkill") && !v) {
        qWarning() << objectName() << QStringLiteral("is a ViewAsSkill. It shouldn't be invisible.");
        Q_ASSERT_X(false, __FILE__ QT_STRINGIFY(__LINE__), "INVALID VISIBILITY SET");
    }
    d->visible = v;
}

const QString &Skill::limitMark() const
{
    Q_D(const Skill);
    return d->limitMark;
}

void Skill::setLimitMark(const QString &lm)
{
    Q_D(Skill);
    if (d->frequency != QSgsEnum::SkillFrequency::Limited && !lm.isEmpty()) {
        qWarning() << objectName() << QStringLiteral("is not a limited skill, It should not set limit mark");
        Q_ASSERT_X(false, __FILE__ QT_STRINGIFY(__LINE__), "INVALID LIMITMARK SET");
    }
    d->limitMark = lm;
}

QSgsEnum::SkillFrequency Skill::frequency() const
{
    Q_D(const Skill);
    return d->frequency;
}

bool Skill::isHeadSkill() const
{
    Q_D(const Skill);
    return d->relateToPlace == QSgsEnum::SkillPlace::Head || d->relateToPlace == QSgsEnum::SkillPlace::Both;
}

bool Skill::isDeputySkill() const
{
    Q_D(const Skill);
    return d->relateToPlace == QSgsEnum::SkillPlace::Deputy || d->relateToPlace == QSgsEnum::SkillPlace::Both;
}

bool Skill::canPreshow() const
{
    Q_D(const Skill);
    return d->canPreshow;
}

void Skill::setCanPreshow(bool c)
{
    Q_D(Skill);
    if ((!inherits("TriggerSkill") || inherits("EquipSkill") && c)) {
        qWarning() << objectName() << QStringLiteral("is not a TriggerSkill or is an EquipSkill. It should not be able to preshow");
        Q_ASSERT_X(false, __FILE__ QT_STRINGIFY(__LINE__), "INVALID CANPRESHOW SET");
    }
    d->canPreshow = c;
}

class ViewAsSkillPrivate
{
public:
    QString responsePattern;
    bool responseOrUse;
    QString expandPile;
};

ViewAsSkill::ViewAsSkill(const QString &name, QSgsEnum::SkillFrequency frequency, QSgsEnum::SkillPlace place)
    : Skill(name, frequency, place), d_ptr_viewAsSkill(new ViewAsSkillPrivate)
{
    Q_D(ViewAsSkill);
    d->responseOrUse = false;
}

ViewAsSkill::~ViewAsSkill()
{
    Q_D(ViewAsSkill);
    delete d;
}

bool ViewAsSkill::isAvailable(const Player *invoker, QSgsEnum::CardUseReason reason, const QString &pattern) const
{
    // Make sure TransferSkill is invoked properly
    if (objectName() != QStringLiteral("transfer")) {
        // Make sure skill that was temporily invoked and skill that has delayed effect can be invoked properly
        if (!invoker->hasFlag(QStringLiteral("TempInvoke_") + objectName()) && !invoker->hasSkill(objectName()) && !invoker->hasDelayedEffect(objectName()))
            return false;
    }

    switch (reason) {
    case QSgsEnum::CardUseReason::Play:
        return isEnabledAtPlay(invoker);
    case QSgsEnum::CardUseReason::Response:
    case QSgsEnum::CardUseReason::ResponseUse:
        return isEnabledAtResponse(invoker, reason, pattern);
    default:
        return false;
    }

    return false;
}

bool ViewAsSkill::isEnabledAtPlay(const Player *player) const
{
    Q_D(const ViewAsSkill);
    return d->responsePattern.isEmpty();
}

bool ViewAsSkill::isEnabledAtResponse(const Player *player, QSgsEnum::CardUseReason reason, const QString &pattern) const
{
    Q_D(const ViewAsSkill);
    if (!d->responsePattern.isEmpty()) {
        QRegularExpression regex(d->responsePattern);
        return regex.match(pattern).hasMatch();
    }

    return false;
}

bool ViewAsSkill::isEnabledAtNullification(const Player *player) const
{
    return false;
}

bool ViewAsSkill::isResponseOrUse() const
{
    Q_D(const ViewAsSkill);
    return d->responseOrUse;
}

const QString &ViewAsSkill::expandPile() const
{
    Q_D(const ViewAsSkill);
    return d->expandPile;
}

const QString &ViewAsSkill::responsePattern() const
{
    Q_D(const ViewAsSkill);
    return d->responsePattern;
}

void ViewAsSkill::setResponsePattern(const QString &pattern)
{
    QString p = pattern;
    if (!pattern.isEmpty()) {
        if (!p.startsWith(QStringLiteral("^")))
            p.prepend(QStringLiteral("^"));

        if (!p.endsWith(QStringLiteral("$")))
            p.append(QStringLiteral("$"));
    }

    QRegularExpression re(p);
    if (!re.isValid()) {
        qWarning() << QStringLiteral("Regular Expression") << p << QStringLiteral("is invalid.");
        qWarning() << re.errorString();
        Q_ASSERT_X(false, __FILE__ QT_STRINGIFY(__LINE__), "INVALID REGEXP SET");
        p.clear();
    }

    Q_D(ViewAsSkill);
    d->responsePattern = p;
}


ZeroCardViewAsSkill::ZeroCardViewAsSkill(const QString &name, QSgsEnum::SkillFrequency frequency, QSgsEnum::SkillPlace place)
    : ViewAsSkill(name, frequency, place)
{

}

bool ZeroCardViewAsSkill::viewFilter(const QList<Card *> &selected, Card *toSelect, const Player *player, QSgsEnum::CardUseReason reason, const QString &pattern) const
{
    return false;
}

Card *ZeroCardViewAsSkill::viewAs(const QList<Card *> &cards, const Player *player, QSgsEnum::CardUseReason reason, const QString &pattern) const
{
    if (cards.isEmpty())
        return viewAs(player, reason, pattern);

    return nullptr;
}

class OneCardViewAsSkillPrivate
{
public:
    QString filterPattern;
};

OneCardViewAsSkill::OneCardViewAsSkill(const QString &name, QSgsEnum::SkillFrequency frequency, QSgsEnum::SkillPlace place)
    : ViewAsSkill(name, frequency, place), d_ptr_oneCardViewAsSkill(new OneCardViewAsSkillPrivate)
{

}

OneCardViewAsSkill::~OneCardViewAsSkill()
{
    Q_D(OneCardViewAsSkill);
    delete d;
}

bool OneCardViewAsSkill::viewFilter(const QList<Card *> &selected, Card *toSelect, const Player *player, QSgsEnum::CardUseReason reason, const QString &pattern) const
{
    return selected.isEmpty() && !toSelect->hasFlag(QStringLiteral("using")) && viewFilter(toSelect, player, reason, pattern);
}

Card *OneCardViewAsSkill::viewAs(const QList<Card *> &cards, const Player *player, QSgsEnum::CardUseReason reason, const QString &pattern) const
{
    if (cards.length() != 1)
        return nullptr;

    return viewAs(cards.first(), player, reason, pattern);
}

bool OneCardViewAsSkill::viewFilter(Card *card, const Player *player, QSgsEnum::CardUseReason reason, const QString &pattern) const
{
    // @todo: exppattern
    return false;
}

CardTransformSkill::CardTransformSkill(const QString &name, QSgsEnum::SkillPlace place)
    : Skill(name, QSgsEnum::SkillFrequency::Compulsory, place)
{

}

class TriggerSkillPrivate
{
public:
    QList<QSgsEnum::TriggerEvent> events;
    bool global;
    int priority;
};

TriggerSkill::TriggerSkill(const QString &name, QSgsEnum::SkillFrequency frequency, QSgsEnum::SkillPlace place)
    : Skill(name, frequency, place), d_ptr_triggerSkill(new TriggerSkillPrivate)
{
    Q_D(TriggerSkill);
    d->global = false;
    d->priority = 3;
}

TriggerSkill::~TriggerSkill()
{
    Q_D(TriggerSkill);
    delete d;
}

const QList<QSgsEnum::TriggerEvent> &TriggerSkill::triggerEvents() const
{
    Q_D(const TriggerSkill);
    return d->events;
}

void TriggerSkill::addTriggerEvent(QSgsEnum::TriggerEvent triggerEvent)
{
    Q_D(TriggerSkill);
    d->events << triggerEvent;
}

int TriggerSkill::priority() const
{
    Q_D(const TriggerSkill);
    return d->priority;
}

void TriggerSkill::setPriority(int priority)
{
    Q_D(TriggerSkill);
    d->priority = priority;
}

bool TriggerSkill::isGlobal() const
{
    Q_D(const TriggerSkill);
    return d->global;
}

void TriggerSkill::setGlobal(bool global)
{
    Q_D(TriggerSkill);
    d->global = global;
}

void TriggerSkill::record(QSgsEnum::TriggerEvent, RoomObject *, Player *, const QVariant &) const
{
    // Apperantly, this function should be a no-op.
}

bool TriggerSkill::cost(QSgsEnum::TriggerEvent triggerEvent, RoomObject *room, QSharedPointer<SkillInvokeStruct> invoke, Player *player, QVariant &data) const
{
    // if compulsory then return true
    // else askForConfirm
    return false;
}


MasochismSkill::MasochismSkill(const QString &name, QSgsEnum::SkillFrequency frequency, QSgsEnum::SkillPlace place)
    : TriggerSkill(name, frequency, place)
{
    addTriggerEvent(QSgsEnum::TriggerEvent::Damaged);
}

void MasochismSkill::record(QSgsEnum::TriggerEvent triggerEvent, RoomObject *room, Player *player, const QVariant &data) const
{
    record(triggerEvent, room, player, data.value<DamageStruct>());
}

QList<SkillInvokeStruct> MasochismSkill::triggerable(QSgsEnum::TriggerEvent triggerEvent, const RoomObject *room, const Player *player, const QVariant &data) const
{
    return triggerable(triggerEvent, room, player, data.value<DamageStruct>());
}

bool MasochismSkill::cost(QSgsEnum::TriggerEvent triggerEvent, RoomObject *room, QSharedPointer<SkillInvokeStruct> invoke, Player *player, QVariant &data) const
{
    DamageStruct d = data.value<DamageStruct>();
    bool c = cost(triggerEvent, room, invoke, player, d);
    data = QVariant::fromValue(d);
    return c;
}

bool MasochismSkill::effect(QSgsEnum::TriggerEvent triggerEvent, RoomObject *room, QSharedPointer<SkillInvokeStruct> invoke, Player *player, QVariant &data) const
{
    DamageStruct d = data.value<DamageStruct>();
    bool e = effect(triggerEvent, room, invoke, player, d);
    data = QVariant::fromValue(d);
    return e;
}

void MasochismSkill::record(QSgsEnum::TriggerEvent, RoomObject *, Player *, const DamageStruct &) const
{
    // Apperantly, this function should be a no-op.
}

bool MasochismSkill::cost(QSgsEnum::TriggerEvent triggerEvent, RoomObject *room, QSharedPointer<SkillInvokeStruct> invoke, Player *player, DamageStruct &damage) const
{
    // Apperantly, the function of TriggerSkill is a default realization. i.e. it can't be aware of data
    QVariant data;
    return TriggerSkill::cost(triggerEvent, room, invoke, player, data);
}

//TriggerSkill::~TriggerSkill()
//{

//}


//OneCardViewAsSkill::OneCardViewAsSkill(const QString &name)
//    : ViewAsSkill(name), m_filterPattern(QString())
//{
//}

//bool OneCardViewAsSkill::viewFilter(const QList<Card *> &selected, const Card *to_select) const
//{
//    return selected.isEmpty() && !to_select->hasFlag("using") && viewFilter(to_select);
//}

//bool OneCardViewAsSkill::viewFilter(const Card *to_select) const
//{
//    if (!inherits("FilterSkill") && !m_filterPattern.isEmpty()) {
//        QString pat = m_filterPattern;
//        if (pat.endsWith("!")) {
//            if (Self->isJilei(to_select)) return false;
//            pat.chop(1);
//        } else if (m_responseOrUse && pat.contains("hand")) {
//            QStringList handlist;
//            handlist.append("hand");
//            foreach (const QString &pile, Self->getPileNames()) {
//                if (pile.startsWith("&") || pile == "wooden_ox")
//                    handlist.append(pile);
//            }
//            pat.replace("hand", handlist.join(","));
//        }
//        ExpPattern pattern(pat);
//        return pattern.match(Self, to_select);
//    }
//    return false;
//}

//const Card *OneCardViewAsSkill::viewAs(const QList<Card *> &cards) const
//{
//    if (cards.length() != 1)
//        return nullptr;
//    else
//        return viewAs(cards.first());
//}

//FilterSkill::FilterSkill(const QString &name)
//    : OneCardViewAsSkill(name)
//{
//    m_frequency = Compulsory;
//}

//TriggerSkill::TriggerSkill(const QString &name)
//    : Skill(name), m_viewAsSkill(nullptr), m_global(false), current_priority(0.0)
//{
//    m_priority.clear();
//}

//const ViewAsSkill *TriggerSkill::viewAsSkill() const
//{
//    return m_viewAsSkill;
//}

//QList<TriggerEvent> TriggerSkill::triggerEvents() const
//{
//    return m_events;
//}

//int TriggerSkill::m_priority() const
//{
//    return 3;
//}

//double TriggerSkill::getDynamicPriority(TriggerEvent e) const
//{
//    if (m_priority.keys().contains(e))
//        return m_priority.key(e);
//    else
//        return this->m_priority();
//}

///*!
//    You are expected to return a QMap<ServerPlayer *, QStringList> in TriggerSkill::triggerable.
//    And the QStringList of QMap is expected to include some items as the examples below:
//    \list 1
//    \li Skill name, such as: "yiji", "fankui", etc.
//    \li Skill name combines someone's object name who is the owner of the skill, such as: "sgs1'songwei", "sgs10'baonue", etc.
//    \note must use a single quote mark to concatenate
//    \li Skill name combines multitargets' object names.
//    If you use this kind of type, it means the skill's trigger order of targets should be according to the order you write, such as: "tieqi->sgs4+sgs8+sgs1+sgs2"
//    \note must use a "->" to concatenate skill name to targets and "+" to concatenate targets' object names
//    \endlist
//    */

//QMap<Player *, QStringList> TriggerSkill::triggerable(TriggerEvent triggerEvent, RoomObject *room, ServerPlayer *player, QVariant &data) const
//{
//    QMap<Player *, QStringList> skill_lists;
//    if (objectName() == "game_rule") return skill_lists;
//    ServerPlayer *ask_who = player;
//    QStringList skill_list = triggerable(triggerEvent, room, player, data, ask_who);
//    if (!skill_list.isEmpty())
//        skill_lists.insert(ask_who, skill_list);
//    return skill_lists;
//}

//bool TriggerSkill::triggerable(const ServerPlayer *target) const
//{
//    return target != nullptr && target->isAlive() && target->hasSkill(objectName());
//}

//void TriggerSkill::insertPriority(TriggerEvent e, double value)
//{
//    m_priority.insert(e, value);
//}

//void TriggerSkill::record(TriggerEvent, RoomObject *, ServerPlayer *, QVariant &) const
//{

//}

//QStringList TriggerSkill::triggerable(TriggerEvent, RoomObject *, ServerPlayer *target, QVariant &, ServerPlayer* &) const
//{
//    if (triggerable(target))
//        return QStringList(objectName());
//    return QStringList();
//}

//bool TriggerSkill::cost(TriggerEvent, RoomObject *, ServerPlayer *, QVariant &, ServerPlayer *) const
//{
//    return true;
//}

//bool TriggerSkill::effect(TriggerEvent, RoomObject *, ServerPlayer *, QVariant &, ServerPlayer *) const
//{
//    return false;
//}

//TriggerSkill::~TriggerSkill()
//{
//    if (m_viewAsSkill && !m_viewAsSkill->inherits("LuaViewAsSkill"))
//        delete m_viewAsSkill;
//    m_events.clear();
//}

//ScenarioRule::ScenarioRule(Scenario *scenario)
//    :TriggerSkill(scenario->objectName())
//{
//    setParent(scenario);
//}

//int ScenarioRule::m_priority() const
//{
//    return 0;
//}

//bool ScenarioRule::triggerable(const ServerPlayer *) const
//{
//    return true;
//}

//MasochismSkill::MasochismSkill(const QString &name)
//    : TriggerSkill(name)
//{
//    m_events << Damaged;
//}

//bool MasochismSkill::cost(TriggerEvent triggerEvent, RoomObject *room, ServerPlayer *player, QVariant &data, ServerPlayer *ask_who) const
//{
//    return TriggerSkill::cost(triggerEvent, room, player, data, ask_who);
//}

//bool MasochismSkill::effect(TriggerEvent, RoomObject *, ServerPlayer *player, QVariant &data, ServerPlayer *) const
//{
//    DamageStruct damage = data.value<DamageStruct>();
//    onDamaged(player, damage);

//    return false;
//}

//PhaseChangeSkill::PhaseChangeSkill(const QString &name)
//    : TriggerSkill(name)
//{
//    m_events << EventPhaseStart;
//}

//bool PhaseChangeSkill::effect(TriggerEvent, RoomObject *, ServerPlayer *player, QVariant &, ServerPlayer *) const
//{
//    return onPhaseChange(player);
//}

//DrawCardsSkill::DrawCardsSkill(const QString &name)
//    : TriggerSkill(name)
//{
//    m_events << DrawNCards;
//}

//bool DrawCardsSkill::effect(TriggerEvent, RoomObject *, ServerPlayer *player, QVariant &data, ServerPlayer *) const
//{
//    int n = data.toInt();
//    data = getDrawNum(player, n);
//    return false;
//}

//GameStartSkill::GameStartSkill(const QString &name)
//    : TriggerSkill(name)
//{
//    m_events << GameStart;
//}

//bool GameStartSkill::effect(TriggerEvent, RoomObject *, ServerPlayer *player, QVariant &, ServerPlayer *) const
//{
//    onGameStart(player);
//    return false;
//}

//BattleArraySkill::BattleArraySkill(const QString &name, const QSgsEnum::ArrayType type)
//    : TriggerSkill(name), m_arrayType(type)
//{
//    if (!inherits("LuaBattleArraySkill")) //extremely dirty hack!!!
//        m_viewAsSkill = new ArraySummonSkill(objectName());
//}

//bool BattleArraySkill::triggerable(const ServerPlayer *player) const
//{
//    return TriggerSkill::triggerable(player) && player->aliveCount() >= 4;
//}

//void BattleArraySkill::summonFriends(ServerPlayer *player) const
//{
//    player->summonFriends(m_arrayType);
//}

//ArraySummonSkill::ArraySummonSkill(const QString &name)
//    : ZeroCardViewAsSkill(name)
//{

//}

//const Card *ArraySummonSkill::viewAs() const
//{
//    QString name = objectName();
//    name[0] = name[0].toUpper();
//    name += "Summon";
//    Card *card = Sanguosha->cloneSkillCard(name);
//    card->setShowSkill(objectName());
//    return card;
//}

//using namespace HegemonyMode;
//bool ArraySummonSkill::isEnabledAtPlay(const Player *player) const
//{
//    if (player->getAliveSiblings().length() < 3) return false;
//    if (player->hasFlag("Global_SummonFailed")) return false;
//    const BattleArraySkill *skill = qobject_cast<const BattleArraySkill *>(Sanguosha->getTriggerSkill(objectName()));
//    if (skill) {
//        ArrayType type = skill->getArrayType();
//        switch (type) {
//            case Siege: {
//                if (player->willBeFriendWith(player->nextAlive())
//                    && player->willBeFriendWith(player->lastAlive()))
//                    return false;
//                if (!player->willBeFriendWith(player->nextAlive())) {
//                    if (!player->nextAlive(2)->hasShownOneGeneral() && player->nextAlive()->hasShownOneGeneral())
//                        return true;
//                }
//                if (!player->willBeFriendWith(player->lastAlive()))
//                    return !player->lastAlive(2)->hasShownOneGeneral() && player->lastAlive()->hasShownOneGeneral();
//                break;
//            }
//            case Formation: {
//                int n = player->aliveCount(false);
//                int asked = n;
//                for (int i = 1; i < n; ++i) {
//                    Player *target = player->nextAlive(i);
//                    if (player->isFriendWith(target))
//                        continue;
//                    else if (!target->hasShownOneGeneral())
//                        return true;
//                    else {
//                        asked = i;
//                        break;
//                    }
//                }
//                n -= asked;
//                for (int i = 1; i < n; ++i) {
//                    Player *target = player->lastAlive(i);
//                    if (player->isFriendWith(target))
//                        continue;
//                    else return !target->hasShownOneGeneral();
//                }
//                break;
//            }
//        }
//    }
//    return false;
//}

//int MaxCardsSkill::getExtra(const ServerPlayer *) const
//{
//    return 0;
//}

//int MaxCardsSkill::getFixed(const ServerPlayer *) const
//{
//    return -1;
//}

//ProhibitSkill::ProhibitSkill(const QString &name)
//    : Skill(name, Skill::Compulsory)
//{
//}

//DistanceSkill::DistanceSkill(const QString &name)
//    : Skill(name, Skill::Compulsory)
//{
//}

//MaxCardsSkill::MaxCardsSkill(const QString &name)
//    : Skill(name, Skill::Compulsory)
//{
//}

//TargetModSkill::TargetModSkill(const QString &name)
//    : Skill(name, Skill::Compulsory)
//{
//    pattern = "Slash";
//}

//QString TargetModSkill::pattern() const
//{
//    return pattern;
//}

//int TargetModSkill::residueNum(const Player *, Card *) const
//{
//    return 0;
//}

//int TargetModSkill::distanceLimit(const Player *, Card *) const
//{
//    return 0;
//}

//int TargetModSkill::extraTargetNum(const Player *, Card *) const
//{
//    return 0;
//}

//SlashNoDistanceLimitSkill::SlashNoDistanceLimitSkill(const QString &skill_name)
//    : TargetModSkill(QString("#%1-slash-ndl").arg(skill_name)), name(skill_name)
//{
//}

//int SlashNoDistanceLimitSkill::distanceLimit(const Player *from, const Card *card) const
//{
//    if (from->hasSkill(name) && card->getSkillName() == name)
//        return 1000;
//    else
//        return 0;
//}

//QString SlashNoDistanceLimitSkill::getName() const
//{
//    return name;
//}

//void SlashNoDistanceLimitSkill::setName(const QString &value)
//{
//    name = value;
//}

//AttackRangeSkill::AttackRangeSkill(const QString &name) : Skill(name, Skill::Compulsory)
//{

//}

//int AttackRangeSkill::extra(const Player *, bool) const
//{
//    return 0;
//}

//int AttackRangeSkill::fixed(const Player *, bool) const
//{
//    return -1;
//}

//FakeMoveSkill::FakeMoveSkill(const QString &name)
//    : TriggerSkill(QString("#%1-fake-move").arg(name)), name(name)
//{
//    m_events << BeforeCardsMove << CardsMoveOneTime;
//}

//int FakeMoveSkill::m_priority() const
//{
//    return 10;
//}

//QStringList FakeMoveSkill::triggerable(TriggerEvent, RoomObject *, ServerPlayer *target, QVariant &, ServerPlayer * &) const
//{
//    return (target != nullptr) ? QStringList(objectName()) : QStringList();
//}

//bool FakeMoveSkill::effect(TriggerEvent, RoomObject *room, ServerPlayer *, QVariant &, ServerPlayer *) const
//{
//    QString flag = QString("%1_InTempMoving").arg(name);

//    foreach(ServerPlayer *p, room->getAllPlayers())
//        if (p->hasFlag(flag)) return true;

//    return false;
//}

//DetachEffectSkill::DetachEffectSkill(const QString &skillname, const QString &pilename)
//    : TriggerSkill(QString("#%1-clear").arg(skillname)), name(skillname), pile_name(pilename)
//{
//    m_events << EventLoseSkill;
//}

//QStringList DetachEffectSkill::triggerable(TriggerEvent, RoomObject *, ServerPlayer *target, QVariant &data, ServerPlayer * &) const
//{
//    if (target && data.toString() == name)
//        return QStringList(objectName());
//    return QStringList();
//}

//bool DetachEffectSkill::effect(TriggerEvent, RoomObject *room, ServerPlayer *player, QVariant &, ServerPlayer *) const
//{
//    if (!pile_name.isEmpty())
//        player->clearOnePrivatePile(pile_name);
//    else
//        onSkillDetached(room, player);

//    return false;
//}

//void DetachEffectSkill::onSkillDetached(RoomObject *, ServerPlayer *) const
//{
//}

//WeaponSkill::WeaponSkill(const QString &name)
//    : TriggerSkill(name)
//{
//}

//int WeaponSkill::m_priority() const
//{
//    return 2;
//}

//bool WeaponSkill::triggerable(const ServerPlayer *target) const
//{
//    if (target == nullptr) return false;
//    if (target->getMark("Equips_nullptrified_to_Yourself") > 0) return false;
//    return target->hasWeapon(objectName());
//}

//ArmorSkill::ArmorSkill(const QString &name)
//    : TriggerSkill(name)
//{
//}

//int ArmorSkill::m_priority() const
//{
//    return 2;
//}

//bool ArmorSkill::triggerable(const ServerPlayer *target) const
//{
//    if (target == nullptr)
//        return false;
//    return target->hasArmorEffect(objectName());
//}

//TreasureSkill::TreasureSkill(const QString &name)
//    : TriggerSkill(name)
//{
//}

//int TreasureSkill::m_priority() const
//{
//    return 2;
//}

//bool TreasureSkill::triggerable(const ServerPlayer *target) const
//{
//    if (target == nullptr)
//        return false;
//    return target->hasTreasure(objectName());
//}
