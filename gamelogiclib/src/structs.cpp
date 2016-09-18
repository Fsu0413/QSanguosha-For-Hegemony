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

#include "structs.h"
#include "player.h"
#include "card.h"
#include "roomobject.h"

bool CardsMoveStruct::tryParse(const QVariant &arg)
{
//    JsonArray args = arg.value<JsonArray>();
//    if (args.size() != 8) return false;

//    if ((!JsonUtils::isNumber(args[0]) && !args[0].canConvert<JsonArray>()) ||
//        !JsonUtils::isNumberArray(args, 1, 2) || !JsonUtils::isStringArray(args, 3, 6)) return false;

//    if (JsonUtils::isNumber(args[0])) {
//        int size = args[0].toInt();
//        for (int i = 0; i < size; i++)
//            card_ids.append(Card::S_UNKNOWN_CARD_ID);
//    } else if (!JsonUtils::tryParse(args[0], card_ids)) {
//        return false;
//    }

//    from_place = (Player::Place)args[1].toInt();
//    to_place = (Player::Place)args[2].toInt();
//    from_player_name = args[3].toString();
//    to_player_name = args[4].toString();
//    from_pile_name = args[5].toString();
//    to_pile_name = args[6].toString();
//    reason.tryParse(args[7]);
//    return true;
    return false;
}

QVariant CardsMoveStruct::toVariant() const
{
//    JsonArray arg;
//    if (open) {
//        arg << JsonUtils::toJsonArray(card_ids);
//    } else {
//        arg << card_ids.size();
//    }

//    arg << (int)from_place;
//    arg << (int)to_place;
//    arg << from_player_name;
//    arg << to_player_name;
//    arg << from_pile_name;
//    arg << to_pile_name;
//    arg << reason.toVariant();
//    return arg;
    return QVariant();
}

bool CardMovement::tryParse(const QVariant &arg)
{
//    JsonArray args = arg.value<JsonArray>();
//    if (args.size() != 5 || !args[0].canConvert<int>() || !JsonUtils::isStringArray(args, 1, 4))
//        return false;

//    m_reason = args[0].toInt();
//    m_playerId = args[1].toString();
//    m_skillName = args[2].toString();
//    m_eventName = args[3].toString();
//    m_targetId = args[4].toString();

//    return true;
    return false;
}

QVariant CardMovement::toVariant() const
{
//    JsonArray result;
//    result << m_reason;
//    result << m_playerId;
//    result << m_skillName;
//    result << m_eventName;
//    result << m_targetId;
//    return result;
    return QVariant();
}

LogMessage::LogMessage()
    //: from(nullptr)
{
}

QString LogMessage::toString() const
{
//    QStringList tos;
//    foreach (Player *player, to)
//        if (player != nullptr) tos << player->objectName();

//    return QString("%1:%2->%3:%4:%5:%6")
//        .arg(type)
//        .arg(from ? from->objectName() : "")
//        .arg(tos.join("+"))
//        .arg(card_str).arg(arg).arg(arg2);
    return QString();
}

QVariant LogMessage::toVariant() const
{
//    QStringList tos;
//    foreach (Player *player, to)
//        if (player != nullptr) tos << player->objectName();

//    QStringList log;
//    log << type << (from ? from->objectName() : "") << tos.join("+") << card_str << arg << arg2;
//    return JsonUtils::toJsonArray(log);
    return QVariant();
}

DamageStruct::DamageStruct()
    : from(nullptr), to(nullptr), card(nullptr), damage(1), nature(QSgsEnum::DamageNature::Normal), chain(false), transfer(false), byUser(true), reason(QString()), transferReason(QString()), prevented(false)
{
}

DamageStruct::DamageStruct(const Card *card, Player *from, Player *to, int damage, QSgsEnum::DamageNature nature)
    : chain(false), transfer(false), byUser(true), reason(QString()), transferReason(QString()), prevented(false)
{
    this->card = card;
    this->from = from;
    this->to = to;
    this->damage = damage;
    this->nature = nature;
}

DamageStruct::DamageStruct(const QString &reason, Player *from, Player *to, int damage, QSgsEnum::DamageNature nature)
    : card(nullptr), chain(false), transfer(false), byUser(true), transferReason(QString()), prevented(false)
{
    this->from = from;
    this->to = to;
    this->damage = damage;
    this->nature = nature;
    this->reason = reason;
}

QJsonValue DamageStruct::toJson() const
{
    QJsonValue v;
    if (to == nullptr || damage <= 0)
        return v;

    QJsonObject ob;
    ob.insert(QStringLiteral("structType"), QStringLiteral("DamageStruct"));

    if (from != nullptr)
        ob.insert(QStringLiteral("from"), from->objectName());
    else
        ob.insert(QStringLiteral("from"), QString());
    ob.insert(QStringLiteral("to"), to->objectName());
    if (card != nullptr)
        ob.insert(QStringLiteral("card"), card->id());
    else
        ob.insert(QStringLiteral("card"), 0);
    ob.insert(QStringLiteral("damage"), damage);
    ob.insert(QStringLiteral("nature"), static_cast<int>(nature));
    ob.insert(QStringLiteral("chain"), chain);
    ob.insert(QStringLiteral("transfer"), transfer);
    ob.insert(QStringLiteral("byUser"), byUser);
    ob.insert(QStringLiteral("reason"), reason);
    ob.insert(QStringLiteral("transferReason"), transferReason);
    ob.insert(QStringLiteral("prevented"), prevented);

    return ob;
}

DamageStruct DamageStruct::fromJson(const QJsonValue &value, RoomObject *room)
{
    DamageStruct r;
    if (!value.isObject() || room == nullptr)
        return r;

    QJsonObject ob = value.toObject();
    if (ob.value(QStringLiteral("structType")).toString() != QStringLiteral("DamageStruct"))
        return r;

    QString strTo = ob.value(QStringLiteral("to")).toString();
    if (strTo.isNull() || strTo.isEmpty())
        return r;

    int intDamage = ob.value(QStringLiteral("damage")).toInt();
    if (intDamage == 0)
        return r;

    QString strFrom = ob.value(QStringLiteral("from")).toString();
    if (!strFrom.isNull() && !strFrom.isEmpty())
        r.from = room->player(strFrom);

    r.to = room->player(strTo);

    int intCard = ob.value(QStringLiteral("card")).toInt();
    if (intCard != 0)
        r.card = room->card(intCard);

    r.damage = intDamage;
    r.nature = static_cast<QSgsEnum::DamageNature>(ob.value(QStringLiteral("nature")).toInt());
    r.chain = ob.value(QStringLiteral("chain")).toBool();
    r.transfer = ob.value(QStringLiteral("transfer")).toBool();
    r.byUser = ob.value(QStringLiteral("byUser")).toBool();
    r.reason = ob.value(QStringLiteral("reason")).toString();
    r.transferReason = ob.value(QStringLiteral("transferReason")).toString();
    r.prevented = ob.value(QStringLiteral("prevented")).toBool();

    return r;
}

CardEffectStruct::CardEffectStruct()
    : card(nullptr), from(nullptr), to(nullptr), multiple(false), nullptrified(false)
{
}

QJsonValue CardEffectStruct::toJson() const
{
    QJsonValue v;

    if (to == nullptr || card == nullptr || card->id() == 0)
        return v;

    QJsonObject ob;

    ob.insert(QStringLiteral("structType"), QStringLiteral("CardEffectStruct"));
    if (from != nullptr)
        ob.insert(QStringLiteral("from"), from->objectName());
    else
        ob.insert(QStringLiteral("from"), QString());

    ob.insert(QStringLiteral("to"), to->objectName());
    ob.insert(QStringLiteral("card"), card->id());
    ob.insert(QStringLiteral("multiple"), multiple);
    ob.insert(QStringLiteral("nullptrified"), nullptrified);

    return ob;
}

CardEffectStruct CardEffectStruct::fromJson(const QJsonValue &value, RoomObject *room)
{
    CardEffectStruct r;

    if (!value.isObject() || room == nullptr)
        return r;

    QJsonObject ob = value.toObject();
    if (ob.value(QStringLiteral("structType")).toString() != QStringLiteral("CardEffectStruct"))
        return r;

    QString strTo = ob.value(QStringLiteral("to")).toString();
    if (strTo.isNull() || strTo.isEmpty())
        return r;

    int intCard = ob.value(QStringLiteral("card")).toInt();
    if (intCard == 0)
        return r;

    r.card = room->card(intCard);
    r.to = room->player(strTo);
    r.multiple = ob.value(QStringLiteral("multiple")).toBool();
    r.nullptrified = ob.value(QStringLiteral("nullptrified")).toBool();

    QString strFrom = ob.value(QStringLiteral("from")).toString();
    if (!strFrom.isEmpty() && !strFrom.isNull())
        r.from = room->player(strFrom);

    return r;
}

SlashEffectStruct::SlashEffectStruct()
    : jinkNum(1), slash(nullptr), jink(nullptr), from(nullptr), to(nullptr), drank(0), nature(QSgsEnum::DamageNature::Normal), nullified(false)
{
}

QJsonValue SlashEffectStruct::toJson() const
{
    QJsonValue v;

    if (slash == nullptr || to == nullptr || slash->id() == 0)
        return v;

    QJsonObject ob;

    ob.insert(QStringLiteral("structType"), QStringLiteral("SlashEffectStruct"));
    ob.insert(QStringLiteral("jinkNum"), jinkNum);
    ob.insert(QStringLiteral("slash"), slash->id());
    ob.insert(QStringLiteral("to"), to->objectName());
    ob.insert(QStringLiteral("drank"), drank);
    ob.insert(QStringLiteral("nature"), static_cast<int>(nature));
    ob.insert(QStringLiteral("nullified"), nullified);

    if (jink != nullptr)
        ob.insert(QStringLiteral("jink"), jink->id());
    else
        ob.insert(QStringLiteral("jink"), 0);
    if (from != nullptr)
        ob.insert(QStringLiteral("from"), from->objectName());
    else
        ob.insert(QStringLiteral("from"), QString());

    return ob;
}

SlashEffectStruct SlashEffectStruct::fromJson(const QJsonValue &value, RoomObject *room)
{
    SlashEffectStruct r;

    if (!value.isObject() || room == nullptr)
        return r;

    QJsonObject ob = value.toObject();
    if (ob.value(QStringLiteral("structType")).toString() != QStringLiteral("SlashEffectStruct"))
        return r;

    QString strTo = ob.value(QStringLiteral("to")).toString();
    if (strTo.isEmpty() || strTo.isNull())
        return r;
    int intSlash = ob.value(QStringLiteral("slash")).toInt();
    if (intSlash == 0)
        return r;

    r.slash = room->card(intSlash);
    r.to = room->player(strTo);

    QString strFrom = ob.value(QStringLiteral("from")).toString();
    if (!strFrom.isNull() && !strFrom.isEmpty())
        r.from = room->player(strFrom);
    int intJink = ob.value(QStringLiteral("jink")).toInt();
    if (intJink != 0)
        r.jink = room->card(intJink);

    r.drank = ob.value(QStringLiteral("drank")).toInt();
    r.jinkNum = ob.value(QStringLiteral("jinkNum")).toInt();
    r.nullified = ob.value(QStringLiteral("nullified")).toBool();
    r.nature = static_cast<QSgsEnum::DamageNature>(ob.value(QStringLiteral("nature")).toInt());

    return r;
}

DeathStruct::DeathStruct()
    : who(nullptr), reason(QSgsEnum::DeathReason::SuddenDeath), murderer(nullptr), damage(DamageStruct())
{
}

QJsonValue DeathStruct::toJson() const
{
    QJsonValue v;

    if (who == nullptr)
        return v;

    QJsonObject ob;
    ob.insert(QStringLiteral("structType"), QStringLiteral("DeathStruct"));
    ob.insert(QStringLiteral("who"), who->objectName());
    ob.insert(QStringLiteral("reason"), static_cast<int>(reason));
    if (murderer != nullptr)
        ob.insert(QStringLiteral("murderer"), murderer->objectName());
    else
        ob.insert(QStringLiteral("murderer"), QString());

    ob.insert(QStringLiteral("damage"), damage.toJson());


    return ob;
}

DeathStruct DeathStruct::fromJson(const QJsonValue &value, RoomObject *room)
{
    DeathStruct r;

    if (!value.isObject() || room == nullptr)
        return r;

    QJsonObject ob = value.toObject();

    if (ob.value(QStringLiteral("structType")).toString() != QStringLiteral("DeathStruct"))
        return r;

    QString strWho = ob.value(QStringLiteral("who")).toString();
    if (strWho.isNull() || strWho.isEmpty())
        return r;
    else
        r.who = room->player(strWho);

    int intReason = ob.value(QStringLiteral("reason")).toInt(static_cast<int>(QSgsEnum::DeathReason::SuddenDeath));
    r.reason = static_cast<QSgsEnum::DeathReason>(intReason);

    QString strMurderer = ob.value(QStringLiteral("murderer")).toString();
    if (!strMurderer.isNull() && !strMurderer.isEmpty())
        r.murderer = room->player(strMurderer);

    r.damage = DamageStruct::fromJson(ob.value(QStringLiteral("damage")), room);

    return r;
}

RecoverStruct::RecoverStruct()
    : recover(1), who(nullptr), card(nullptr)
{
}

QJsonValue RecoverStruct::toJson() const
{
    QJsonValue v;
    QJsonObject ob;

    if (who == nullptr || recover <= 0)
        return v;

    ob.insert(QStringLiteral("structType"), QStringLiteral("RecoverStruct"));
    ob.insert(QStringLiteral("who"), who->objectName());
    ob.insert(QStringLiteral("recover"), recover);
    if (card != nullptr)
        ob.insert(QStringLiteral("card"), card->id());
    else
        ob.insert(QStringLiteral("card"), 0);

    return ob;

}

RecoverStruct RecoverStruct::fromJson(const QJsonValue &value, RoomObject *room)
{
    RecoverStruct r;

    if (!value.isObject())
        return r;

    QJsonObject ob = value.toObject();
    if (ob.value(QStringLiteral("structType")).toString() != QStringLiteral("RecoverStruct"))
        return r;

    QString strWho = ob.value(QStringLiteral("who")).toString();
    if (strWho.isNull() || strWho.isEmpty())
        return r;

    int intRecover = ob.value(QStringLiteral("recover")).toInt();
    if (intRecover == 0)
        return r;

    r.who = room->player(strWho);
    r.recover = intRecover;

    int intCard = ob.value(QStringLiteral("card")).toInt();
    if (intCard != 0)
        r.card = room->card(intCard);

    return r;
}

PindianStruct::PindianStruct()
  //  : from(nullptr), to(nullptr), from_card(nullptr), to_card(nullptr), success(false)
{
}

bool PindianStruct::isSuccess() const
{
    return false;
}

JudgeStruct::JudgeStruct()
//    : who(nullptr), card(nullptr), pattern("."), good(true), time_consuming(false),
//    negative(false), play_animation(true), _m_result(TRIAL_RESULT_UNKNOWN)
{
}

bool JudgeStruct::isEffected() const
{
 //   return negative ? isBad() : isGood();
    return false;
}

void JudgeStruct::updateResult()
{
//    bool effected = (good == ExpPattern(pattern).match(who, card));
//    if (effected)
//        _m_result = TRIAL_RESULT_GOOD;
//    else
//        _m_result = TRIAL_RESULT_BAD;
}

bool JudgeStruct::isGood() const
{
//    Q_ASSERT(_m_result != TRIAL_RESULT_UNKNOWN);
//    return _m_result == TRIAL_RESULT_GOOD;
    return false;
}

bool JudgeStruct::isBad() const
{
 //   return !isGood();
    return false;
}

bool JudgeStruct::isGood(const Card *card) const
{
//    Q_ASSERT(card);
//    return (good == ExpPattern(pattern).match(who, card));
    return false;
}

PhaseChangeStruct::PhaseChangeStruct()
//    : from(Player::NotActive), to(Player::NotActive)
{
}

CardUseStruct::CardUseStruct()
    : card(nullptr), from(nullptr), isOwnerUse(true), addHistory(true), nullifiedList(QStringList())
{
}

QJsonValue CardUseStruct::toJson() const
{
    QJsonValue v;
    QJsonObject ob;

    if (card == nullptr || card->id() == 0)
        return v;

    ob.insert(QStringLiteral("structType"), QStringLiteral("CardUseStruct"));

    QJsonArray playerArray;
    foreach (Player *p, to)
        playerArray.append(p->objectName());
    ob.insert(QStringLiteral("to"), playerArray);
    ob.insert(QStringLiteral("card"), card->id());
    ob.insert(QStringLiteral("isOwnerUse"), isOwnerUse);
    ob.insert(QStringLiteral("addHistory"), addHistory);
    ob.insert(QStringLiteral("isHandcard"), isHandcard);
    QJsonArray nullifiedArray;
    foreach (const QString &n, nullifiedList)
        nullifiedArray.append(n);
    ob.insert(QStringLiteral("nullifiedList"), nullifiedArray);
    ob.insert(QStringLiteral("reason"), static_cast<int>(reason));

    if (from != nullptr)
        ob.insert(QStringLiteral("from"), from->objectName());
    else
        ob.insert(QStringLiteral("from"), QString());

    return ob;
}

CardUseStruct CardUseStruct::fromJson(const QJsonValue &value, RoomObject *room)
{
    CardUseStruct r;

    if (!value.isObject())
        return r;

    QJsonObject ob = value.toObject();
    if (ob.value(QStringLiteral("structType")).toString() != QStringLiteral("CardUseStruct"))
        return r;

    int intCard = ob.value(QStringLiteral("card")).toInt();
    if (intCard == 0)
        return r;

    r.card = room->card(intCard);

    QJsonArray playerArray = ob.value(QStringLiteral("to")).toArray();
    foreach (const QVariant &p, playerArray.toVariantList())
        r.to.append(room->player(p.toString()));

    QString strFrom = ob.value(QStringLiteral("from")).toString();
    if (strFrom.isNull() || strFrom.isEmpty())
        r.from = nullptr;
    else
        r.from = room->player(strFrom);

    r.addHistory = ob.value(QStringLiteral("addHistory")).toBool();
    r.isOwnerUse = ob.value(QStringLiteral("isOwnerUse")).toBool();
    r.isHandcard = ob.value(QStringLiteral("isHandcard")).toBool();
    r.reason = static_cast<QSgsEnum::CardUseReason>(ob.value(QStringLiteral("reason")).toInt());

    QJsonArray nullifiedArray = ob.value(QStringLiteral("nullifiedList")).toArray();
    foreach (const QVariant &p, nullifiedArray.toVariantList())
        r.nullifiedList.append(p.toString());

    return r;

}

CardUseStruct::CardUseStruct(const Card *card, Player *from, QList<Player *> to, bool isOwnerUse)
{
    this->card = card;
    this->from = from;
    this->to = to;
    this->isOwnerUse = isOwnerUse;
    this->addHistory = true;
}

CardUseStruct::CardUseStruct(const Card *card, Player *from, Player *target, bool isOwnerUse)
{
    this->card = card;
    this->from = from;
    this->to << target;
    this->isOwnerUse = isOwnerUse;
    this->addHistory = true;
}

//bool CardUseStruct::isValid(const QString &pattern) const
//{
////    Q_UNUSED(pattern)
////        return card != nullptr;
//    /*if (card == nullptr) return false;
//    if (!card->getSkillName().isEmpty()) {
//    bool validSkill = false;
//    QString skillName = card->getSkillName();
//    QSet<const Skill *> skills = from->getVisibleSkills();
//    for (int i = 0; i < 4; i++) {
//    const EquipCard *equip = from->getEquip(i);
//    if (equip == nullptr) continue;
//    const Skill *skill = Sanguosha->getSkill(equip);
//    if (skill)
//    skills.insert(skill);
//    }
//    foreach (const Skill *skill, skills) {
//    if (skill->objectName() != skillName) continue;
//    const ViewAsSkill *vsSkill = ViewAsSkill::parseViewAsSkill(skill);
//    if (vsSkill) {
//    if (!vsSkill->isAvailable(from, m_reason, pattern))
//    return false;
//    else {
//    validSkill = true;
//    break;
//    }
//    } else if (skill->getFrequency() == Skill::Wake) {
//    bool valid = (from->getMark(skill->objectName()) > 0);
//    if (!valid)
//    return false;
//    else
//    validSkill = true;
//    } else
//    return false;
//    }
//    if (!validSkill) return false;
//    }
//    if (card->targetFixed())
//    return true;
//    else {
//    QList<const Player *> targets;
//    foreach (const Player *player, to)
//    targets.push_back(player);
//    return card->targetsFeasible(targets, from);
//    }*/
//    return false;
//}

//bool CardUseStruct::tryParse(const QVariant &usage, RoomObject *room)
//{
////    JsonArray use = usage.value<JsonArray>();
////    if (use.size() < 2 || !JsonUtils::isString(use[0]) || !use[1].canConvert<JsonArray>())
////        return false;

////    card = Card::Parse(use[0].toString());
////    JsonArray targets = use[1].value<JsonArray>();

////    foreach (const QVariant &target, targets) {
////        if (!JsonUtils::isString(target)) return false;
////        this->to << room->findChild<Player *>(target.toString());
////    }
////    return true;
//    return false;
//}

//void CardUseStruct::parse(const QString &str, RoomObject *room)
//{
////    QStringList words = str.split("->", QString::KeepEmptyParts);
////    Q_ASSERT(words.length() == 1 || words.length() == 2);

////    QString card_str = words.at(0);
////    QString target_str = ".";

////    if (words.length() == 2 && !words.at(1).isEmpty())
////        target_str = words.at(1);

////    card = Card::Parse(card_str);

////    if (target_str != ".") {
////        QStringList target_names = target_str.split("+");
////        foreach (const QString &target_name, target_names)
////            to << room->findChild<Player *>(target_name);
////    }
//}

AskForMoveCardsStruct::AskForMoveCardsStruct()
{
//    is_success = false;
//    top.clear();
//    bottom.clear();
}

SkillInvokeStruct::SkillInvokeStruct()
    : skill(nullptr), invoker(nullptr)
{
}

//QJsonValue SkillInvokeStruct::toJson() const
//{
//    return QJsonValue();
//}

//SkillInvokeStruct SkillInvokeStruct::fromJson(const QJsonValue &value)
//{
//    return SkillInvokeStruct();
//}

SkillTriggerStruct::SkillTriggerStruct()
    //:invoker(nullptr), owner(nullptr), preferredTarget(nullptr), skill(QString())
{

}

QJsonValue SkillTriggerStruct::toJson() const
{
    return QJsonValue();
}

SkillTriggerStruct SkillTriggerStruct::fromJson(const QJsonValue &value, RoomObject *room)
{
    return SkillTriggerStruct();
}

QJsonValue PindianStruct::toJson() const
{
    QJsonValue v;

    if (from == nullptr || to == nullptr || from_card == nullptr || to_card == nullptr ||
        from_card->id() == 0 || to_card->id() == 0)
        return v;

    QJsonObject ob;

    ob.insert(QStringLiteral("structType"), QStringLiteral("PindianStruct"));
    ob.insert(QStringLiteral("from"), from->objectName());
    ob.insert(QStringLiteral("to"), to->objectName());
    ob.insert(QStringLiteral("from_card"), from_card->id());
    ob.insert(QStringLiteral("to_card"), to_card->id());
    ob.insert(QStringLiteral("from_number"), from_number);
    ob.insert(QStringLiteral("to_number"), to_number);
    ob.insert(QStringLiteral("reason"), reason);
    ob.insert(QStringLiteral("success"), success);

    return ob;
}

PindianStruct PindianStruct::fromJson(const QJsonValue &value, RoomObject *room)
{
    PindianStruct r;

    if (!value.isObject())
        return r;

    QJsonObject ob = value.toObject();
    if (ob.value(QStringLiteral("structType")).toString() != QStringLiteral("PindianStruct"))
        return r;

    QString strFrom = ob.value(QStringLiteral("from")).toString();
    if (strFrom.isNull() || strFrom.isEmpty())
        return r;

    QString strTo = ob.value(QStringLiteral("to")).toString();
    if (strTo.isNull() || strTo.isEmpty())
        return r;

    int intFromCard = ob.value(QStringLiteral("from_card")).toInt();
    if (intFromCard == 0)
        return r;

    int intToCard = ob.value(QStringLiteral("to_card")).toInt();
    if (intToCard == 0)
        return r;

    r.from = room->player(strFrom);
    r.to = room->player(strTo);
    r.from_card = room->card(intFromCard);
    r.to_card = room->card(intToCard);
    r.from_number = ob.value(QStringLiteral("from_number")).toInt();
    r.to_number = ob.value(QStringLiteral("to_number")).toInt();
    r.reason = ob.value(QStringLiteral("reason")).toString();
    r.success = ob.value(QStringLiteral("success")).toBool();

    return r;
}

QJsonValue JudgeStruct::toJson() const
{
    QJsonValue v;

    if (who == nullptr || card == nullptr || card->id() == 0)
        return v;

    QJsonObject ob;

    ob.insert(QStringLiteral("structType"), QStringLiteral("JudgeStruct"));
    ob.insert(QStringLiteral("who"), who->objectName());
    ob.insert(QStringLiteral("card"), card->id());
    ob.insert(QStringLiteral("pattern"), pattern);
    ob.insert(QStringLiteral("good"), good);
    ob.insert(QStringLiteral("reason"), reason);
    ob.insert(QStringLiteral("time_consuming"), time_consuming);
    ob.insert(QStringLiteral("negative"), negative);
    ob.insert(QStringLiteral("play_animation"), play_animation);

    return ob;
}

JudgeStruct JudgeStruct::fromJson(const QJsonValue &value, RoomObject *room)
{
    JudgeStruct r;

    if (!value.isObject())
        return r;

    QJsonObject ob = value.toObject();
    if (ob.value(QStringLiteral("structType")).toString() != QStringLiteral("JudgeStruct"))
        return r;

    QString strWho = ob.value(QStringLiteral("who")).toString();
    if (strWho.isNull() || strWho.isEmpty())
        return r;

    int intCard = ob.value(QStringLiteral("card")).toInt();
    if (intCard == 0)
        return r;

    r.who = room->player(strWho);
    r.card = room->card(intCard);
    r.pattern = ob.value(QStringLiteral("pattern")).toString();
    r.good = ob.value(QStringLiteral("good")).toBool();
    r.reason = ob.value(QStringLiteral("reason")).toString();
    r.time_consuming = ob.value(QStringLiteral("time_consuming")).toBool();
    r.negative = ob.value(QStringLiteral("negative")).toBool();
    r.play_animation = ob.value(QStringLiteral("play_animation")).toBool();

    return r;
}

QJsonValue PhaseChangeStruct::toJson() const
{
    QJsonObject ob;

    ob.insert(QStringLiteral("structType"), QStringLiteral("PhaseChangeStruct"));
    ob.insert(QStringLiteral("from"), static_cast<int>(from));
    ob.insert(QStringLiteral("to"), static_cast<int>(to));

    return ob;
}

PhaseChangeStruct PhaseChangeStruct::fromJson(const QJsonValue &value, RoomObject *)
{
    PhaseChangeStruct r;

    if (!value.isObject())
        return r;

    QJsonObject ob = value.toObject();
    if (ob.value(QStringLiteral("structType")).toString() != QStringLiteral("PhaseChangeStruct"))
        return r;

    r.from = static_cast<QSgsEnum::PlayerPhase>(ob.value(QStringLiteral("from")).toInt());
    r.to = static_cast<QSgsEnum::PlayerPhase>(ob.value(QStringLiteral("to")).toInt());

    return r;
}

QJsonValue CardResponseStruct::toJson() const
{
    QJsonValue v;

    if (card == nullptr || who == nullptr || card->id() == 0)
        return v;

    QJsonObject ob;

    ob.insert(QStringLiteral("structType"), QStringLiteral("CardResponseStruct"));
    ob.insert(QStringLiteral("card"), card->id());
    ob.insert(QStringLiteral("who"), who->objectName());
    ob.insert(QStringLiteral("isUse"), isUse);
    ob.insert(QStringLiteral("isHandcard"), isHandcard);
    ob.insert(QStringLiteral("isRetrial"), isRetrial);

    return ob;
}

CardResponseStruct CardResponseStruct::fromJson(const QJsonValue &value, RoomObject *room)
{
    CardResponseStruct r;

    if (!value.isObject())
        return r;

    QJsonObject ob = value.toObject();
    if (ob.value(QStringLiteral("structType")).toString() != QStringLiteral("CardResponseStruct"))
        return r;

    QString strWho = ob.value(QStringLiteral("who")).toString();
    if (strWho.isNull() || strWho.isEmpty())
        return r;

    int intCard = ob.value(QStringLiteral("card")).toInt();
    if (intCard == 0)
        return r;

    r.who = room->player(strWho);
    r.card = room->card(intCard);
    r.isUse = ob.value(QStringLiteral("isUse")).toBool();
    r.isHandcard = ob.value(QStringLiteral("isHandcard")).toBool();
    r.isRetrial = ob.value(QStringLiteral("isRetrial")).toBool();

    return r;
}

QJsonValue LogMessage::toJson() const
{
    QJsonObject ob;

    ob.insert(QStringLiteral("structType"), QStringLiteral("LogMessage"));
    ob.insert(QStringLiteral("type"), type);
    ob.insert(QStringLiteral("card_str"), card_str);
    ob.insert(QStringLiteral("arg"), arg);
    ob.insert(QStringLiteral("arg2"), arg2);

    QJsonArray playerArray;
    foreach (Player *p, to)
        playerArray.append(p->objectName());

    ob.insert(QStringLiteral("to"), playerArray);

    if (from != nullptr)
        ob.insert(QStringLiteral("from"), from->objectName());
    else
        ob.insert(QStringLiteral("from"), QString());

    return ob;
}

LogMessage LogMessage::fromJson(const QJsonValue &value, RoomObject *room)
{
    LogMessage r;

    if (!value.isObject())
        return r;

    QJsonObject ob = value.toObject();
    if (ob.value(QStringLiteral("structType")).toString() != QStringLiteral("LogMessage"))
        return r;

    r.type = ob.value(QStringLiteral("type")).toString();
    r.card_str = ob.value(QStringLiteral("card_str")).toString();
    r.arg = ob.value(QStringLiteral("arg")).toString();
    r.arg2 = ob.value(QStringLiteral("arg2")).toString();

    QString strFrom = ob.value(QStringLiteral("from")).toString();
    if (!strFrom.isNull() && ! strFrom.isEmpty())
        r.from = room->player(strFrom);

    QJsonArray playerArray = ob.value(QStringLiteral("to")).toArray();
    foreach (const QVariant &p, playerArray.toVariantList())
        r.to.append(room->player(p.toString()));

    return r;
}
