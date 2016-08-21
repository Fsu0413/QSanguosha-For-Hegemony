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
#include "settings.h"
#include "engine.h"
#include "player.h"
#include "room.h"
#include "client.h"
#include "standard.h"
#include "scenario.h"
#include "serverplayer.h"

#include <QFile>

Skill::Skill(const QString &name, Frequency frequency)
    : m_frequency(frequency), m_limitMark(QString()), m_relateToPlace(QString()), m_attachedLordSkill(false)
{
    static QChar lord_symbol('$');

    if (name.endsWith(lord_symbol)) {
        QString copy = name;
        copy.remove(lord_symbol);
        setObjectName(copy);
        m_lordSkill = true;
    } else {
        setObjectName(name);
        m_lordSkill = false;
    }
}

bool Skill::isLordSkill() const
{
    return m_lordSkill;
}

bool Skill::isAttachedLordSkill() const
{
    return m_attachedLordSkill;
}

QString Skill::description(bool inToolTip) const
{
    QString desc;
    if (!canPreshow())
        desc.prepend(QString("<font color=gray>(%1)</font><br/>").arg(tr("this skill cannot preshow")));

    QString skill_name = objectName();

    if (objectName().contains("_")) {
        skill_name = objectName().split("_").first();
    }

    QString des_src = Sanguosha->translate(":" + skill_name);
    if (des_src == ":" + skill_name)
        return desc;

    foreach (const QString &skill_type, Sanguosha->getSkillColorMap().keys()) {
        QString to_replace = Sanguosha->translate(skill_type);
        if (to_replace == skill_type) continue;
        QString color_str = Sanguosha->getSkillColor(skill_type).name();
        if (des_src.contains(to_replace))
            des_src.replace(to_replace, QString("<font color=%1><b>%2</b></font>").arg(color_str)
            .arg(to_replace));
    }

    for (int i = 0; i < 6; i++) {
        Card::Suit suit = (Card::Suit)i;
        QString str = Card::Suit2String(suit);
        QString to_replace = Sanguosha->translate(str);
        bool red = suit == Card::Heart
            || suit == Card::Diamond
            || suit == Card::NoSuitRed;
        if (to_replace == str) continue;
        if (des_src.contains(to_replace)) {
            if (red)
                des_src.replace(to_replace, QString("<font color=#FF0000>%1</font>").arg(Sanguosha->translate(str + "_char")));
            else
                des_src.replace(to_replace, QString("<font color=#000000><span style=background-color:white>%1</span></font>").arg(Sanguosha->translate(str + "_char")));
        }
    }

    desc.append(QString("<font color=%1>%2</font>").arg(inToolTip ? Config.SkillDescriptionInToolTipColor.name() : Config.SkillDescriptionInOverviewColor.name()).arg(des_src));
    return desc;
}

QString Skill::notice(int index) const
{
    if (index == -1)
        return Sanguosha->translate("~" + objectName());

    return Sanguosha->translate(QString("~%1%2").arg(objectName()).arg(index));
}

bool Skill::isVisible() const
{
    return !objectName().startsWith("#");
}

//int Skill::getEffectIndex(const ServerPlayer *, const Card *) const
//{
//    return -1;
//}

//void Skill::initMediaSource()
//{
//    sources.clear();
//    for (int i = 1;; ++i) {
//        QString effect_file = QString("audio/skill/%1%2.ogg").arg(objectName()).arg(QString::number(i));
//        if (QFile::exists(effect_file))
//            sources << effect_file;
//        else
//            break;
//    }

//    if (sources.isEmpty()) {
//        QString effect_file = QString("audio/skill/%1.ogg").arg(objectName());
//        if (QFile::exists(effect_file))
//            sources << effect_file;
//    }
//}

//void Skill::playAudioEffect(int index) const
//{
//    if (!sources.isEmpty()) {
//        if (index == -1)
//            index = qrand() % sources.length();
//        else
//            index--;

//        // check length
//        QString filename;
//        if (index >= 0 && index < sources.length())
//            filename = sources.at(index);
//        else if (index >= sources.length()) {
//            while (index >= sources.length())
//                index -= sources.length();
//            filename = sources.at(index);
//        } else
//            filename = sources.first();

//        Sanguosha->playAudioEffect(filename);
//    }
//}

Skill::Frequency Skill::frequency() const
{
    return m_frequency;
}

QString Skill::limitMark() const
{
    return m_limitMark;
}

//QStringList Skill::getSources(const QString &general, const int skinId) const
//{
//    if (skinId == 0)
//        return sources;

//    const QString key = QString("%1_%2")
//        .arg(QString::number(skinId))
//        .arg(general);

//    if (skinSourceHash.contains(key))
//        return skinSourceHash[key];

//    for (int i = 1;; ++i) {
//        QString effectFile = QString("hero-skin/%1/%2/%3%4.ogg")
//            .arg(general).arg(QString::number(skinId))
//            .arg(objectName()).arg(QString::number(i));
//        if (QFile::exists(effectFile))
//            skinSourceHash[key] << effectFile;
//        else
//            break;
//    }

//    if (skinSourceHash[key].isEmpty()) {
//        QString effectFile = QString("hero-skin/%1/%2/%3.ogg")
//            .arg(general).arg(QString::number(skinId)).arg(objectName());
//        if (QFile::exists(effectFile))
//            skinSourceHash[key] << effectFile;
//    }

//    return skinSourceHash[key].isEmpty() ? sources : skinSourceHash[key];
//}

//QStringList Skill::getSources() const
//{
//    return sources;
//}

//QDialog *Skill::getDialog() const
//{
//    return nullptr;
//}

//QString Skill::getGuhuoBox() const
//{
//    return "";
//}

bool Skill::canPreshow() const
{
    if (inherits("TriggerSkill")) {
        const TriggerSkill *triskill = qobject_cast<const TriggerSkill *>(this);
        return triskill->viewAsSkill() == nullptr;
    }

    return false;
}

bool Skill::relateToPlace(bool head) const
{
    if (head)
        return m_relateToPlace == "head";
    else
        return m_relateToPlace == "deputy";
    return false;
}

ViewAsSkill::ViewAsSkill(const QString &name)
    : Skill(name), m_responsePattern(QString()), m_responseOrUse(false), m_expandPile(QString())
{
}

bool ViewAsSkill::isAvailable(const Player *invoker, CardUseStruct::CardUseReason reason, const QString &pattern) const
{
    if (!inherits("TransferSkill") && !invoker->hasSkill(objectName())
        && !invoker->hasFlag(objectName())) { // For Shuangxiong
        return false;
    }
    switch (reason) {
        case CardUseStruct::CARD_USE_REASON_PLAY: return isEnabledAtPlay(invoker);
        case CardUseStruct::CARD_USE_REASON_RESPONSE:
        case CardUseStruct::CARD_USE_REASON_RESPONSE_USE: return isEnabledAtResponse(invoker, pattern);
        default:
            return false;
    }
}

bool ViewAsSkill::isEnabledAtPlay(const Player *) const
{
    return m_responsePattern.isEmpty();
}

bool ViewAsSkill::isEnabledAtResponse(const Player *, const QString &pattern) const
{
    if (!m_responsePattern.isEmpty())
        return pattern == m_responsePattern;
    return false;
}

bool ViewAsSkill::isEnabledAtnullptrification(const ServerPlayer *) const
{
    return false;
}

const ViewAsSkill *ViewAsSkill::parseViewAsSkill(const Skill *skill)
{
    if (skill == nullptr) return nullptr;
    if (skill->inherits("ViewAsSkill")) {
        const ViewAsSkill *view_as_skill = qobject_cast<const ViewAsSkill *>(skill);
        return view_as_skill;
    }
    if (skill->inherits("TriggerSkill")) {
        const TriggerSkill *trigger_skill = qobject_cast<const TriggerSkill *>(skill);
        Q_ASSERT(trigger_skill != nullptr);
        const ViewAsSkill *view_as_skill = trigger_skill->viewAsSkill();
        if (view_as_skill != nullptr) return view_as_skill;
    }
    return nullptr;
}

ZeroCardViewAsSkill::ZeroCardViewAsSkill(const QString &name)
    : ViewAsSkill(name)
{
}

const Card *ZeroCardViewAsSkill::viewAs(const QList<const Card *> &cards) const
{
    if (cards.isEmpty())
        return viewAs();
    else
        return nullptr;
}

bool ZeroCardViewAsSkill::viewFilter(const QList<const Card *> &, const Card *) const
{
    return false;
}

OneCardViewAsSkill::OneCardViewAsSkill(const QString &name)
    : ViewAsSkill(name), m_filterPattern(QString())
{
}

bool OneCardViewAsSkill::viewFilter(const QList<const Card *> &selected, const Card *to_select) const
{
    return selected.isEmpty() && !to_select->hasFlag("using") && viewFilter(to_select);
}

bool OneCardViewAsSkill::viewFilter(const Card *to_select) const
{
    if (!inherits("FilterSkill") && !m_filterPattern.isEmpty()) {
        QString pat = m_filterPattern;
        if (pat.endsWith("!")) {
            if (Self->isJilei(to_select)) return false;
            pat.chop(1);
        } else if (m_responseOrUse && pat.contains("hand")) {
            QStringList handlist;
            handlist.append("hand");
            foreach (const QString &pile, Self->getPileNames()) {
                if (pile.startsWith("&") || pile == "wooden_ox")
                    handlist.append(pile);
            }
            pat.replace("hand", handlist.join(","));
        }
        ExpPattern pattern(pat);
        return pattern.match(Self, to_select);
    }
    return false;
}

const Card *OneCardViewAsSkill::viewAs(const QList<const Card *> &cards) const
{
    if (cards.length() != 1)
        return nullptr;
    else
        return viewAs(cards.first());
}

FilterSkill::FilterSkill(const QString &name)
    : OneCardViewAsSkill(name)
{
    m_frequency = Compulsory;
}

TriggerSkill::TriggerSkill(const QString &name)
    : Skill(name), m_viewAsSkill(nullptr), m_global(false), current_priority(0.0)
{
    m_priority.clear();
}

const ViewAsSkill *TriggerSkill::viewAsSkill() const
{
    return m_viewAsSkill;
}

QList<TriggerEvent> TriggerSkill::triggerEvents() const
{
    return m_events;
}

int TriggerSkill::m_priority() const
{
    return 3;
}

double TriggerSkill::getDynamicPriority(TriggerEvent e) const
{
    if (m_priority.keys().contains(e))
        return m_priority.key(e);
    else
        return this->m_priority();
}

/*!
    You are expected to return a QMap<ServerPlayer *, QStringList> in TriggerSkill::triggerable.
    And the QStringList of QMap is expected to include some items as the examples below:
    \list 1
    \li Skill name, such as: "yiji", "fankui", etc.
    \li Skill name combines someone's object name who is the owner of the skill, such as: "sgs1'songwei", "sgs10'baonue", etc.
    \note must use a single quote mark to concatenate
    \li Skill name combines multitargets' object names.
    If you use this kind of type, it means the skill's trigger order of targets should be according to the order you write, such as: "tieqi->sgs4+sgs8+sgs1+sgs2"
    \note must use a "->" to concatenate skill name to targets and "+" to concatenate targets' object names
    \endlist
    */

TriggerList TriggerSkill::triggerable(TriggerEvent triggerEvent, Room *room, ServerPlayer *player, QVariant &data) const
{
    TriggerList skill_lists;
    if (objectName() == "game_rule") return skill_lists;
    ServerPlayer *ask_who = player;
    QStringList skill_list = triggerable(triggerEvent, room, player, data, ask_who);
    if (!skill_list.isEmpty())
        skill_lists.insert(ask_who, skill_list);
    return skill_lists;
}

bool TriggerSkill::triggerable(const ServerPlayer *target) const
{
    return target != nullptr && target->isAlive() && target->hasSkill(objectName());
}

void TriggerSkill::insertPriority(TriggerEvent e, double value)
{
    m_priority.insert(e, value);
}

void TriggerSkill::record(TriggerEvent, Room *, ServerPlayer *, QVariant &) const
{

}

QStringList TriggerSkill::triggerable(TriggerEvent, Room *, ServerPlayer *target, QVariant &, ServerPlayer* &) const
{
    if (triggerable(target))
        return QStringList(objectName());
    return QStringList();
}

bool TriggerSkill::cost(TriggerEvent, Room *, ServerPlayer *, QVariant &, ServerPlayer *) const
{
    return true;
}

bool TriggerSkill::effect(TriggerEvent, Room *, ServerPlayer *, QVariant &, ServerPlayer *) const
{
    return false;
}

TriggerSkill::~TriggerSkill()
{
    if (m_viewAsSkill && !m_viewAsSkill->inherits("LuaViewAsSkill"))
        delete m_viewAsSkill;
    m_events.clear();
}

ScenarioRule::ScenarioRule(Scenario *scenario)
    :TriggerSkill(scenario->objectName())
{
    setParent(scenario);
}

int ScenarioRule::m_priority() const
{
    return 0;
}

bool ScenarioRule::triggerable(const ServerPlayer *) const
{
    return true;
}

MasochismSkill::MasochismSkill(const QString &name)
    : TriggerSkill(name)
{
    m_events << Damaged;
}

bool MasochismSkill::cost(TriggerEvent triggerEvent, Room *room, ServerPlayer *player, QVariant &data, ServerPlayer *ask_who) const
{
    return TriggerSkill::cost(triggerEvent, room, player, data, ask_who);
}

bool MasochismSkill::effect(TriggerEvent, Room *, ServerPlayer *player, QVariant &data, ServerPlayer *) const
{
    DamageStruct damage = data.value<DamageStruct>();
    onDamaged(player, damage);

    return false;
}

PhaseChangeSkill::PhaseChangeSkill(const QString &name)
    : TriggerSkill(name)
{
    m_events << EventPhaseStart;
}

bool PhaseChangeSkill::effect(TriggerEvent, Room *, ServerPlayer *player, QVariant &, ServerPlayer *) const
{
    return onPhaseChange(player);
}

DrawCardsSkill::DrawCardsSkill(const QString &name)
    : TriggerSkill(name)
{
    m_events << DrawNCards;
}

bool DrawCardsSkill::effect(TriggerEvent, Room *, ServerPlayer *player, QVariant &data, ServerPlayer *) const
{
    int n = data.toInt();
    data = getDrawNum(player, n);
    return false;
}

GameStartSkill::GameStartSkill(const QString &name)
    : TriggerSkill(name)
{
    m_events << GameStart;
}

bool GameStartSkill::effect(TriggerEvent, Room *, ServerPlayer *player, QVariant &, ServerPlayer *) const
{
    onGameStart(player);
    return false;
}

BattleArraySkill::BattleArraySkill(const QString &name, const HegemonyMode::ArrayType type)
    : TriggerSkill(name), m_arrayType(type)
{
    if (!inherits("LuaBattleArraySkill")) //extremely dirty hack!!!
        m_viewAsSkill = new ArraySummonSkill(objectName());
}

bool BattleArraySkill::triggerable(const ServerPlayer *player) const
{
    return TriggerSkill::triggerable(player) && player->aliveCount() >= 4;
}

void BattleArraySkill::summonFriends(ServerPlayer *player) const
{
    player->summonFriends(m_arrayType);
}

ArraySummonSkill::ArraySummonSkill(const QString &name)
    : ZeroCardViewAsSkill(name)
{

}

const Card *ArraySummonSkill::viewAs() const
{
    QString name = objectName();
    name[0] = name[0].toUpper();
    name += "Summon";
    Card *card = Sanguosha->cloneSkillCard(name);
    card->setShowSkill(objectName());
    return card;
}

using namespace HegemonyMode;
bool ArraySummonSkill::isEnabledAtPlay(const Player *player) const
{
    if (player->getAliveSiblings().length() < 3) return false;
    if (player->hasFlag("Global_SummonFailed")) return false;
    const BattleArraySkill *skill = qobject_cast<const BattleArraySkill *>(Sanguosha->getTriggerSkill(objectName()));
    if (skill) {
        ArrayType type = skill->getArrayType();
        switch (type) {
            case Siege: {
                if (player->willBeFriendWith(player->nextAlive())
                    && player->willBeFriendWith(player->lastAlive()))
                    return false;
                if (!player->willBeFriendWith(player->nextAlive())) {
                    if (!player->nextAlive(2)->hasShownOneGeneral() && player->nextAlive()->hasShownOneGeneral())
                        return true;
                }
                if (!player->willBeFriendWith(player->lastAlive()))
                    return !player->lastAlive(2)->hasShownOneGeneral() && player->lastAlive()->hasShownOneGeneral();
                break;
            }
            case Formation: {
                int n = player->aliveCount(false);
                int asked = n;
                for (int i = 1; i < n; ++i) {
                    Player *target = player->nextAlive(i);
                    if (player->isFriendWith(target))
                        continue;
                    else if (!target->hasShownOneGeneral())
                        return true;
                    else {
                        asked = i;
                        break;
                    }
                }
                n -= asked;
                for (int i = 1; i < n; ++i) {
                    Player *target = player->lastAlive(i);
                    if (player->isFriendWith(target))
                        continue;
                    else return !target->hasShownOneGeneral();
                }
                break;
            }
        }
    }
    return false;
}

int MaxCardsSkill::getExtra(const ServerPlayer *, MaxCardsType::MaxCardsCount) const
{
    return 0;
}

int MaxCardsSkill::getFixed(const ServerPlayer *, MaxCardsType::MaxCardsCount) const
{
    return -1;
}

ProhibitSkill::ProhibitSkill(const QString &name)
    : Skill(name, Skill::Compulsory)
{
}

DistanceSkill::DistanceSkill(const QString &name)
    : Skill(name, Skill::Compulsory)
{
}

MaxCardsSkill::MaxCardsSkill(const QString &name)
    : Skill(name, Skill::Compulsory)
{
}

TargetModSkill::TargetModSkill(const QString &name)
    : Skill(name, Skill::Compulsory)
{
    pattern = "Slash";
}

QString TargetModSkill::pattern() const
{
    return pattern;
}

int TargetModSkill::residueNum(const Player *, const Card *) const
{
    return 0;
}

int TargetModSkill::distanceLimit(const Player *, const Card *) const
{
    return 0;
}

int TargetModSkill::extraTargetNum(const Player *, const Card *) const
{
    return 0;
}

SlashNoDistanceLimitSkill::SlashNoDistanceLimitSkill(const QString &skill_name)
    : TargetModSkill(QString("#%1-slash-ndl").arg(skill_name)), name(skill_name)
{
}

int SlashNoDistanceLimitSkill::distanceLimit(const Player *from, const Card *card) const
{
    if (from->hasSkill(name) && card->getSkillName() == name)
        return 1000;
    else
        return 0;
}

QString SlashNoDistanceLimitSkill::getName() const
{
    return name;
}

void SlashNoDistanceLimitSkill::setName(const QString &value)
{
    name = value;
}

AttackRangeSkill::AttackRangeSkill(const QString &name) : Skill(name, Skill::Compulsory)
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

FakeMoveSkill::FakeMoveSkill(const QString &name)
    : TriggerSkill(QString("#%1-fake-move").arg(name)), name(name)
{
    m_events << BeforeCardsMove << CardsMoveOneTime;
}

int FakeMoveSkill::m_priority() const
{
    return 10;
}

QStringList FakeMoveSkill::triggerable(TriggerEvent, Room *, ServerPlayer *target, QVariant &, ServerPlayer * &) const
{
    return (target != nullptr) ? QStringList(objectName()) : QStringList();
}

bool FakeMoveSkill::effect(TriggerEvent, Room *room, ServerPlayer *, QVariant &, ServerPlayer *) const
{
    QString flag = QString("%1_InTempMoving").arg(name);

    foreach(ServerPlayer *p, room->getAllPlayers())
        if (p->hasFlag(flag)) return true;

    return false;
}

DetachEffectSkill::DetachEffectSkill(const QString &skillname, const QString &pilename)
    : TriggerSkill(QString("#%1-clear").arg(skillname)), name(skillname), pile_name(pilename)
{
    m_events << EventLoseSkill;
}

QStringList DetachEffectSkill::triggerable(TriggerEvent, Room *, ServerPlayer *target, QVariant &data, ServerPlayer * &) const
{
    if (target && data.toString() == name)
        return QStringList(objectName());
    return QStringList();
}

bool DetachEffectSkill::effect(TriggerEvent, Room *room, ServerPlayer *player, QVariant &, ServerPlayer *) const
{
    if (!pile_name.isEmpty())
        player->clearOnePrivatePile(pile_name);
    else
        onSkillDetached(room, player);

    return false;
}

void DetachEffectSkill::onSkillDetached(Room *, ServerPlayer *) const
{
}

WeaponSkill::WeaponSkill(const QString &name)
    : TriggerSkill(name)
{
}

int WeaponSkill::m_priority() const
{
    return 2;
}

bool WeaponSkill::triggerable(const ServerPlayer *target) const
{
    if (target == nullptr) return false;
    if (target->getMark("Equips_nullptrified_to_Yourself") > 0) return false;
    return target->hasWeapon(objectName());
}

ArmorSkill::ArmorSkill(const QString &name)
    : TriggerSkill(name)
{
}

int ArmorSkill::m_priority() const
{
    return 2;
}

bool ArmorSkill::triggerable(const ServerPlayer *target) const
{
    if (target == nullptr)
        return false;
    return target->hasArmorEffect(objectName());
}

TreasureSkill::TreasureSkill(const QString &name)
    : TriggerSkill(name)
{
}

int TreasureSkill::m_priority() const
{
    return 2;
}

bool TreasureSkill::triggerable(const ServerPlayer *target) const
{
    if (target == nullptr)
        return false;
    return target->hasTreasure(objectName());
}
