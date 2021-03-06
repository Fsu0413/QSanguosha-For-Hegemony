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

#ifndef _STRUCTS_H
#define _STRUCTS_H

#include "libqsgsgamelogicglobal.h"
#include "enumeration.h"

class Player;
class Card;
class Skill;
class RoomObject;

struct LIBQSGSGAMELOGIC_EXPORT DamageStruct
{

    DamageStruct();
    DamageStruct(const Card *card, Player *from, Player *to, int damage = 1, QSgsEnum::DamageNature nature = QSgsEnum::DamageNature::Normal);
    DamageStruct(const QString &reason, Player *from, Player *to, int damage = 1, QSgsEnum::DamageNature nature = QSgsEnum::DamageNature::Normal);

    Player *from;
    Player *to;
    const Card *card;
    int damage;
    QSgsEnum::DamageNature nature;
    bool chain;
    bool transfer;
    bool byUser;
    QString reason;
    QString transferReason;
    bool prevented;

    QJsonValue toJson() const;

    static DamageStruct fromJson(const QJsonValue &value, RoomObject *room);

};

struct LIBQSGSGAMELOGIC_EXPORT CardEffectStruct
{
    CardEffectStruct();

    const Card *card;

    Player *from;
    Player *to;

    bool multiple; // helper to judge whether the card has multiple targets
    // does not make sense if the card inherits SkillCard
    bool nullptrified;

    QJsonValue toJson() const;

    static CardEffectStruct fromJson(const QJsonValue &value, RoomObject *room);
};

struct LIBQSGSGAMELOGIC_EXPORT SlashEffectStruct
{
    SlashEffectStruct();

    int jinkNum;

    const Card *slash;
    const Card *jink;

    Player *from;
    Player *to;

    int drank;

    QSgsEnum::DamageNature nature;

    bool nullified;

    QJsonValue toJson() const;

    static SlashEffectStruct fromJson(const QJsonValue &value, RoomObject *room);
};

struct LIBQSGSGAMELOGIC_EXPORT CardUseStruct
{
    CardUseStruct();

    const Card *card;
    Player *from;
    QList<Player *> to;
    bool isOwnerUse;
    bool addHistory;
    bool isHandcard;
    QStringList nullifiedList;
    QSgsEnum::CardUseReason reason;

    QJsonValue toJson() const;

    static CardUseStruct fromJson(const QJsonValue &value, RoomObject *room);
};

// To: Slob, Xusine, Lights, DJ
// PLEASE DO NOT MODIFY SkillInvokeStruct AND SkillTriggerStruct
// reserved for proactive skill and trigger order
// the homework of dev QQ qun does not include these 2 struct
// @todo_Fs: create a way to access these struct
struct LIBQSGSGAMELOGIC_EXPORT SkillInvokeStruct
{
    // Skill, player, target, card
    // use to describe ProactiveSkill

    SkillInvokeStruct();

    const Skill *skill;
    Player *invoker;
    QList<Player *> targets;
    QList<Card *> cards;

//    QJsonValue toJson() const;

//    static SkillInvokeStruct fromJson(const QJsonValue &value);

};

struct LIBQSGSGAMELOGIC_EXPORT SkillTriggerStruct
{
    // Skill, player, skillowner, and other sth.
    // like SkillInvokeDetail in TouhouSatsu, but we use a more suitable name here


    SkillTriggerStruct();

//    QString skill; // the skill
//    Player *owner; // skill owner. 2 structs with the same skill and skill owner are treated as of a same skill.
//    Player *invoker; // skill invoker. When invoking skill, we sort firstly according to the priority, then the seat of invoker, at last weather it is a skill of an equip.
//    QList<Player *> targets; // skill targets.
//    bool isCompulsory; // judge the skill is compulsory or not. It is set in the skill's triggerable
//    bool triggered; // judge whether the skill is triggered
//    Player *preferredTarget; // the preferred target of a certain skill
//    QVariantMap tag; // used to add a tag to the struct. useful for skills like Tieqi and Liegong to save a QVariantList for assisting to assign targets

    QJsonValue toJson() const;

    static SkillTriggerStruct fromJson(const QJsonValue &value, RoomObject *room);
};

class LIBQSGSGAMELOGIC_EXPORT CardMovement
{
public:
    QSgsEnum::CardMoveReason m_reason;
//    QString m_playerId; // the cause (not the source) of the movement, such as "lusu" when "dimeng", or "zhanghe" when "qiaobian"
//    QString m_targetId; // To keep this structure lightweight, currently this is only used for UI purpose.
//    // It will be set to empty if multiple targets are involved. NEVER use it for trigger condition
//    // judgement!!! It will not accurately reflect the real reason.
//    QString m_skillName; // skill that triggers movement of the cards, such as "longdang", "dimeng"
//    QString m_eventName; // additional arg such as "lebusishu" on top of "S_REASON_JUDGE"
//    inline CardMovement()
//    {
//        m_reason = S_REASON_UNKNOWN;
//    }
//    inline CardMovement(int moveReason, QString playerId)
//    {
//        m_reason = moveReason;
//        m_playerId = playerId;
//    }

//    inline CardMovement(int moveReason, QString playerId, QString skillName, QString eventName)
//    {
//        m_reason = moveReason;
//        m_playerId = playerId;
//        m_skillName = skillName;
//        m_eventName = eventName;
//    }

//    inline CardMovement(int moveReason, QString playerId, QString targetId, QString skillName, QString eventName)
//    {
//        m_reason = moveReason;
//        m_playerId = playerId;
//        m_targetId = targetId;
//        m_skillName = skillName;
//        m_eventName = eventName;
//    }

    bool tryParse(const QVariant &);
    QVariant toVariant() const;


};

struct LIBQSGSGAMELOGIC_EXPORT CardsMoveOneTimeStruct
{
//    QList<int> card_ids;
//    QList<Player::Place> from_places;
//    Player::Place to_place;
//    CardMoveReason reason;
//    Player *from, *to;
//    QStringList from_pile_names;
//    QString to_pile_name;

//    QList<Player::Place> origin_from_places;
//    Player::Place origin_to_place;
//    Player *origin_from, *origin_to;
//    QStringList origin_from_pile_names;
//    QString origin_to_pile_name; //for case of the movement transitted

//    QList<bool> open; // helper to prevent sending card_id to unrelevant clients
//    bool is_last_handcard;
};

struct LIBQSGSGAMELOGIC_EXPORT CardsMoveStruct
{
    inline CardsMoveStruct()
    {
//        from_place = Player::PlaceUnknown;
//        to_place = Player::PlaceUnknown;
//        from = nullptr;
//        to = nullptr;
//        is_last_handcard = false;
    }

//    inline CardsMoveStruct(const QList<int> &ids, Player *from, Player *to, Player::Place from_place,
//        Player::Place to_place, CardMoveReason reason)
//    {
//        this->card_ids = ids;
//        this->from_place = from_place;
//        this->to_place = to_place;
//        this->from = from;
//        this->to = to;
//        this->reason = reason;
//        this->is_last_handcard = false;
//        if (from) this->from_player_name = from->objectName();
//        if (to) this->to_player_name = to->objectName();
//    }

//    inline CardsMoveStruct(const QList<int> &ids, Player *to, Player::Place to_place, CardMoveReason reason)
//    {
//        this->card_ids = ids;
//        this->from_place = Player::PlaceUnknown;
//        this->to_place = to_place;
//        this->from = nullptr;
//        this->to = to;
//        this->reason = reason;
//        this->is_last_handcard = false;
//        if (to) this->to_player_name = to->objectName();
//    }

//    inline CardsMoveStruct(int id, Player *from, Player *to, Player::Place from_place,
//        Player::Place to_place, CardMoveReason reason)
//    {
//        this->card_ids << id;
//        this->from_place = from_place;
//        this->to_place = to_place;
//        this->from = from;
//        this->to = to;
//        this->reason = reason;
//        this->is_last_handcard = false;
//        if (from) this->from_player_name = from->objectName();
//        if (to) this->to_player_name = to->objectName();
//    }

//    inline CardsMoveStruct(int id, Player *to, Player::Place to_place, CardMoveReason reason)
//    {
//        this->card_ids << id;
//        this->from_place = Player::PlaceUnknown;
//        this->to_place = to_place;
//        this->from = nullptr;
//        this->to = to;
//        this->reason = reason;
//        this->is_last_handcard = false;
//        if (to) this->to_player_name = to->objectName();
//    }

    inline bool operator == (const CardsMoveStruct &other) const
    {
//        return from == other.from && from_place == other.from_place
//            && from_pile_name == other.from_pile_name && from_player_name == other.from_player_name;
        return false;
    }

    inline bool operator < (const CardsMoveStruct &other) const
    {
//        return from < other.from || from_place < other.from_place
//            || from_pile_name < other.from_pile_name || from_player_name < other.from_player_name;
        return false;
    }

//    QList<int> card_ids;
//    Player::Place from_place, to_place;
//    QString from_player_name, to_player_name;
//    QString from_pile_name, to_pile_name;
//    Player *from, *to;
//    CardMoveReason reason;
//    bool open; // helper to prevent sending card_id to unrelevant clients
//    bool is_last_handcard;

//    Player::Place origin_from_place, origin_to_place;
//    Player *origin_from, *origin_to;
//    QString origin_from_pile_name, origin_to_pile_name; //for case of the movement transitted

    bool tryParse(const QVariant &arg);
    QVariant toVariant() const;
    inline bool isRelevant(const Player *player)
    {
        //return player != nullptr && (from == player || (to == player && to_place != Player::PlaceSpecial));
        return false;
    }
};

struct LIBQSGSGAMELOGIC_EXPORT DeathStruct
{
    DeathStruct();

    Player *who; // who is dead
    QSgsEnum::DeathReason reason;
    Player *murderer;
    DamageStruct damage;

    QJsonValue toJson() const;

    static DeathStruct fromJson(const QJsonValue &value, RoomObject *room);
};

struct LIBQSGSGAMELOGIC_EXPORT RecoverStruct
{
    RecoverStruct();

    int recover;
    Player *who;
    const Card *card;

    QJsonValue toJson() const;

    static RecoverStruct fromJson(const QJsonValue &value, RoomObject *room);
};

struct LIBQSGSGAMELOGIC_EXPORT PindianStruct
{
    PindianStruct();
    bool isSuccess(bool from = true) const;

    Player *from;
    Player *to;
    const Card *from_card;
    const Card *to_card;
    int from_number;
    int to_number;
    QString reason;

    QJsonValue toJson() const;
    static PindianStruct fromJson(const QJsonValue &value, RoomObject *room);
};

struct LIBQSGSGAMELOGIC_EXPORT JudgeStruct
{
    JudgeStruct();
    bool match() const;

    Player *who;
    const Card *card;
    QString pattern;
    QString reason;

    QJsonValue toJson() const;
    static JudgeStruct fromJson(const QJsonValue &value, RoomObject *room);
};

struct LIBQSGSGAMELOGIC_EXPORT PhaseChangeStruct
{
    PhaseChangeStruct();
    QSgsEnum::PlayerPhase from;
    QSgsEnum::PlayerPhase to;

    QJsonValue toJson() const;
    static PhaseChangeStruct fromJson(const QJsonValue &value, RoomObject *room);
};

// @todo: Move it to Player?
struct PhaseStruct
{
    inline PhaseStruct()
    {
//        phase = Player::PhaseNone;
//        finished = false;
    }

//    Player::Phase phase;
//    bool finished;
};

struct LIBQSGSGAMELOGIC_EXPORT CardResponseStruct
{
    CardResponseStruct();

    const Card *card;
    Player *who;
    bool isUse;
    bool isHandcard;
    bool isRetrial;

    QJsonValue toJson() const;
    static CardResponseStruct fromJson(const QJsonValue &value, RoomObject *room);
};

struct LIBQSGSGAMELOGIC_EXPORT LogMessage
{
    LogMessage();

    QString type;
    Player *from;
    QList<Player *> to;
    QString card_str;
    QString arg;
    QString arg2;

    QJsonValue toJson() const;
    static LogMessage fromJson(const QJsonValue &value, RoomObject *room);
};


Q_DECLARE_METATYPE(DamageStruct)
Q_DECLARE_METATYPE(CardEffectStruct)
Q_DECLARE_METATYPE(SlashEffectStruct)
Q_DECLARE_METATYPE(CardUseStruct)
Q_DECLARE_METATYPE(CardsMoveStruct)
Q_DECLARE_METATYPE(CardsMoveOneTimeStruct)
Q_DECLARE_METATYPE(DeathStruct)
Q_DECLARE_METATYPE(RecoverStruct)
Q_DECLARE_METATYPE(PhaseChangeStruct)
Q_DECLARE_METATYPE(CardResponseStruct)
//Q_DECLARE_METATYPE(PlayerNumStruct)
//Q_DECLARE_METATYPE(Card *)
//Q_DECLARE_METATYPE(Player *)
//Q_DECLARE_METATYPE(JudgeStruct *)
//Q_DECLARE_METATYPE(PindianStruct *)
#endif

