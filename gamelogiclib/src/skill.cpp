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
#include "roomobject.h"
#include "card.h"
#include "cardface.h"

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
    if ((!inherits("TriggerSkill") || inherits("EquipSkill")) && c) {
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

bool ViewAsSkill::isEnabledAtPlay(const Player *) const
{
    Q_D(const ViewAsSkill);
    return d->responsePattern.isEmpty();
}

bool ViewAsSkill::isEnabledAtResponse(const Player *, QSgsEnum::CardUseReason, const QString &pattern) const
{
    Q_D(const ViewAsSkill);
    if (!d->responsePattern.isEmpty()) {
        QRegularExpression regex(d->responsePattern);
        return regex.match(pattern).hasMatch();
    }

    return false;
}

bool ViewAsSkill::isEnabledAtNullification(const Player *) const
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

class SkillCardFace : public CardFace
{
    Q_OBJECT

public:
    SkillCardFace(ProactiveSkill *skill)
        : CardFace(QString())
    {
        setParent(skill);
    }

    QSgsEnum::CardType typeId() const final override
    {
        return QSgsEnum::CardType::Skill; // Warning: Special operations for UI and AI, possablly....
    }

    bool targetsFeasible(const QList<const Player *> &targets, const Player *self, QSgsEnum::CardUseReason reason, const QString &pattern) const final override
    {
        const ProactiveSkill *skill = qobject_cast<ProactiveSkill *>(parent());
        if (skill)
            return skill->playerFeasible(targets, self, reason, pattern);

        return false;
    }
    bool targetFilter(const QList<const Player *> &targets, const Player *toSelect, const Player *self, QSgsEnum::CardUseReason reason, const QString &pattern, int *maxVotes) const final override
    {
        const ProactiveSkill *skill = qobject_cast<ProactiveSkill *>(parent());
        if (skill)
            return skill->playerFilter(targets, toSelect, self, reason, pattern, maxVotes);

        return false;
    }

    bool isAvailable(const Player *player) const final override
    {
        const ProactiveSkill *skill = qobject_cast<ProactiveSkill *>(parent());
        if (skill)
            return skill->isAvailable(player, QSgsEnum::CardUseReason::Play, QString());

        return false;
    }
};

ProactiveSkill::ProactiveSkill(const QString &name, QSgsEnum::SkillFrequency frequency, QSgsEnum::SkillPlace place)
    : ViewAsSkill(name, frequency, place)
{
    new SkillCardFace(this);
}

bool ProactiveSkill::cardFilter(const QList<Card *> &, Card *, const Player *, QSgsEnum::CardUseReason, const QString &) const
{
    return false;
}

bool ProactiveSkill::cardFeasible(const QList<Card *> &, const Player *, QSgsEnum::CardUseReason, const QString &) const
{
    return true;
}

bool ProactiveSkill::playerFilter(const QList<const Player *> &selected, const Player *toSelect, const Player *player, QSgsEnum::CardUseReason, const QString &, int *) const
{
    return selected.isEmpty() && toSelect != player;
}

bool ProactiveSkill::playerFeasible(const QList<const Player *> &selected, const Player *, QSgsEnum::CardUseReason, const QString &) const
{
    return !selected.isEmpty();
}

void ProactiveSkill::cost(const SkillInvokeStruct &) const
{
    // no-op
}

bool ProactiveSkill::viewFilter(const QList<Card *> &selected, Card *to_select, const Player *player, QSgsEnum::CardUseReason reason, const QString &pattern) const
{
    return cardFilter(selected, to_select, player, reason, pattern);
}

Card *ProactiveSkill::viewAs(const QList<Card *> &cards, const Player *player, QSgsEnum::CardUseReason reason, const QString &pattern) const
{
    if (cardFeasible(cards, player, reason, pattern)) {
        Card *card = new Card(nullptr, findChild<SkillCardFace *>(), 0);
        card->addSubcards(cards);
        return card;
    }
    return nullptr;
}

bool BattleArraySkill::playerFilter(const QList<const Player *> &, const Player *, const Player *, QSgsEnum::CardUseReason, const QString &, int *) const
{
    return false;
}

bool BattleArraySkill::playerFeasible(const QList<const Player *> &, const Player *, QSgsEnum::CardUseReason, const QString &) const
{
    return true;
}

void BattleArraySkill::effect(const SkillInvokeStruct &invoke) const
{
    // @todo_Fs: SkillInvokeStruct and array summon
}

ZeroCardViewAsSkill::ZeroCardViewAsSkill(const QString &name, QSgsEnum::SkillFrequency frequency, QSgsEnum::SkillPlace place)
    : ViewAsSkill(name, frequency, place)
{

}

bool ZeroCardViewAsSkill::viewFilter(const QList<Card *> &, Card *, const Player *, QSgsEnum::CardUseReason , const QString &) const
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

bool TriggerSkill::cost(QSgsEnum::TriggerEvent triggerEvent, RoomObject *room, QSharedPointer<SkillTriggerStruct> invoke, Player *player, QVariant &data) const
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

QList<SkillTriggerStruct> MasochismSkill::triggerable(QSgsEnum::TriggerEvent triggerEvent, const RoomObject *room, const Player *player, const QVariant &data) const
{
    return triggerable(triggerEvent, room, player, data.value<DamageStruct>());
}

bool MasochismSkill::cost(QSgsEnum::TriggerEvent triggerEvent, RoomObject *room, QSharedPointer<SkillTriggerStruct> invoke, Player *player, QVariant &data) const
{
    DamageStruct d = data.value<DamageStruct>();
    bool r = cost(triggerEvent, room, invoke, player, d);
    data = QVariant::fromValue(d);
    return r;
}

bool MasochismSkill::effect(QSgsEnum::TriggerEvent triggerEvent, RoomObject *room, QSharedPointer<SkillTriggerStruct> invoke, Player *player, QVariant &data) const
{
    DamageStruct d = data.value<DamageStruct>();
    bool r = effect(triggerEvent, room, invoke, player, d);
    data = QVariant::fromValue(d);
    return r;
}

void MasochismSkill::record(QSgsEnum::TriggerEvent, RoomObject *, Player *, const DamageStruct &) const
{
    // Apperantly, this function should be a no-op.
}

bool MasochismSkill::cost(QSgsEnum::TriggerEvent triggerEvent, RoomObject *room, QSharedPointer<SkillTriggerStruct> invoke, Player *player, DamageStruct &) const
{
    // Apperantly, the function of TriggerSkill is a default realization. i.e. it can't be aware of data
    QVariant data;
    return TriggerSkill::cost(triggerEvent, room, invoke, player, data);
}

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


PhaseChangeSkill::PhaseChangeSkill(const QString &name, QSgsEnum::SkillFrequency frequency, QSgsEnum::SkillPlace place)
    : TriggerSkill(name, frequency, place)
{
    addTriggerEvent(QSgsEnum::TriggerEvent::EventPhaseStart);
}

DrawCardsSkill::DrawCardsSkill(const QString &name, QSgsEnum::SkillFrequency frequency, QSgsEnum::SkillPlace place)
    : TriggerSkill(name, frequency, place)
{
    addTriggerEvent(QSgsEnum::TriggerEvent::DrawNCards);
}

void DrawCardsSkill::record(QSgsEnum::TriggerEvent triggerEvent, RoomObject *room, Player *player, const QVariant &data) const
{
    record(triggerEvent, room, player, data.toInt());
}

QList<SkillTriggerStruct> DrawCardsSkill::triggerable(QSgsEnum::TriggerEvent triggerEvent, const RoomObject *room, const Player *player, const QVariant &data) const
{
    return triggerable(triggerEvent, room, player, data.toInt());
}

bool DrawCardsSkill::cost(QSgsEnum::TriggerEvent triggerEvent, RoomObject *room, QSharedPointer<SkillTriggerStruct> invoke, Player *player, QVariant &data) const
{
    int n = data.toInt();
    bool r = cost(triggerEvent, room, invoke, player, n);
    data = n;
    return r;
}

bool DrawCardsSkill::effect(QSgsEnum::TriggerEvent triggerEvent, RoomObject *room, QSharedPointer<SkillTriggerStruct> invoke, Player *player, QVariant &data) const
{
    int n = data.toInt();
    bool r = effect(triggerEvent, room, invoke, player, n);
    data = n;
    return r;
}

void DrawCardsSkill::record(QSgsEnum::TriggerEvent, RoomObject *, Player *, int) const
{
    // Apperantly, this function should be a no-op.
}

bool DrawCardsSkill::cost(QSgsEnum::TriggerEvent triggerEvent, RoomObject *room, QSharedPointer<SkillTriggerStruct> invoke, Player *player, int &) const
{
    // Apperantly, the function of TriggerSkill is a default realization. i.e. it can't be aware of data
    QVariant data;
    return TriggerSkill::cost(triggerEvent, room, invoke, player, data);
}

class FakeMoveSkillPrivate
{
public:
    QString origSkillName;
};

FakeMoveSkill::FakeMoveSkill(const QString &originalSkillName, QSgsEnum::SkillPlace place)
    : TriggerSkill(originalSkillName + QStringLiteral("-FakeMove"), QSgsEnum::SkillFrequency::Compulsory, place), d_ptr_fakeMoveSkill(new FakeMoveSkillPrivate)
{
    Q_D(FakeMoveSkill);
    d->origSkillName = originalSkillName;
    setVisible(false);
    setPriority(10);
    addTriggerEvent(QSgsEnum::TriggerEvent::BeforeCardsMove);
    addTriggerEvent(QSgsEnum::TriggerEvent::CardsMoveOneTime);
}

FakeMoveSkill::~FakeMoveSkill()
{
    Q_D(FakeMoveSkill);
    delete d;
}

QList<SkillTriggerStruct> FakeMoveSkill::triggerable(QSgsEnum::TriggerEvent, const RoomObject *room, const Player *, const QVariant &) const
{
    Q_D(const FakeMoveSkill);
    foreach (const Player *p, room->players()) {
        if (p->isAlive() && p->hasFlag(d->origSkillName + QStringLiteral("_InTempMoving")) && p->hasSkill(this, true))
            return QList<SkillTriggerStruct>(); // @Todo_Fs: return a meaningful SkillTriggerStruct
    }

    return QList<SkillTriggerStruct>();
}

bool FakeMoveSkill::cost(QSgsEnum::TriggerEvent, RoomObject *, QSharedPointer<SkillTriggerStruct>, Player *, QVariant &) const
{
    return true;
}

bool FakeMoveSkill::effect(QSgsEnum::TriggerEvent, RoomObject *, QSharedPointer<SkillTriggerStruct>, Player *, QVariant &) const
{
    return true;
}


EquipSkill::EquipSkill(const QString &name, QSgsEnum::SkillFrequency frequency)
    : TriggerSkill(name, frequency, QSgsEnum::SkillPlace::None)
{

}

WeaponSkill::WeaponSkill(const QString &name, QSgsEnum::SkillFrequency frequency)
    : EquipSkill(name, frequency)
{

}

ArmorSkill::ArmorSkill(const QString &name, QSgsEnum::SkillFrequency frequency)
    : EquipSkill(name, frequency)
{

}

TreasureSkill::TreasureSkill(const QString &name, QSgsEnum::SkillFrequency frequency)
    : EquipSkill(name, frequency)
{

}

ProhibitSkill::ProhibitSkill(const QString &name, QSgsEnum::SkillPlace place)
    : Skill(name, QSgsEnum::SkillFrequency::Compulsory, place)
{

}

DistanceSkill::DistanceSkill(const QString &name, QSgsEnum::SkillPlace place)
    : Skill(name, QSgsEnum::SkillFrequency::Compulsory, place)
{

}

MaxCardsSkill::MaxCardsSkill(const QString &name, QSgsEnum::SkillPlace place)
    : Skill(name, QSgsEnum::SkillFrequency::Compulsory, place)
{

}

int MaxCardsSkill::extra(const Player *) const
{
    return 0;
}

int MaxCardsSkill::fixed(const Player *) const
{
    return -1;
}

TargetModSkill::TargetModSkill(const QString &name, QSgsEnum::SkillPlace place)
    : Skill(name, QSgsEnum::SkillFrequency::Compulsory, place)
{

}

int TargetModSkill::residueNum(const Player *, Card *) const
{
    return 0;
}

int TargetModSkill::distanceLimit(const Player *, Card *) const
{
    return 0;
}

int TargetModSkill::extraTargetNum(const Player *, Card *) const
{
    return 0;
}

class SlashNoDistanceLimitSkillPrivate
{
public:
    QString origSkillName;
};

SlashNoDistanceLimitSkill::SlashNoDistanceLimitSkill(const QString &originalSkillName, QSgsEnum::SkillPlace place)
    : TargetModSkill(originalSkillName + QStringLiteral("-SlashNdl"), place), d_ptr_slashNoDistanceLimitSkill(new SlashNoDistanceLimitSkillPrivate)
{
    Q_D(SlashNoDistanceLimitSkill);
    d->origSkillName = originalSkillName;
    setVisible(false);
}

SlashNoDistanceLimitSkill::~SlashNoDistanceLimitSkill()
{
    Q_D(SlashNoDistanceLimitSkill);
    delete d;
}

int SlashNoDistanceLimitSkill::distanceLimit(const Player *, Card *card) const
{
    Q_D(const SlashNoDistanceLimitSkill);
    if (card->cardFace()->isKindOf("Slash") && card->skillName() == d->origSkillName)
        return 1000;

    return 0;
}

AttackRangeSkill::AttackRangeSkill(const QString &name, QSgsEnum::SkillPlace place)
    : Skill(name, QSgsEnum::SkillFrequency::Compulsory, place)
{

}

int AttackRangeSkill::extra(const Player *, bool) const
{
    return 0;
}

int AttackRangeSkill::fixed(const Player *, bool) const
{
    return -1;
}

#include "skill.moc"
