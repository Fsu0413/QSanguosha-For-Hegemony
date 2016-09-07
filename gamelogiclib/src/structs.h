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

class Room;
class Player;
class Card;

struct DamageStruct
{

    DamageStruct();
//    DamageStruct(const Card *card, ServerPlayer *from, ServerPlayer *to, int damage = 1, Nature nature = Normal);
//    DamageStruct(const QString &reason, ServerPlayer *from, ServerPlayer *to, int damage = 1, Nature nature = Normal);

//    ServerPlayer *from;
//    ServerPlayer *to;
//    const Card *card;
//    int damage;
//    Nature nature;
//    bool chain;
//    bool transfer;
//    bool by_user;
//    QString reason;
//    QString transfer_reason;
//    bool prevented;

    QString getReason() const;
};

struct CardEffectStruct
{
    CardEffectStruct();

//    const Card *card;

//    ServerPlayer *from;
//    ServerPlayer *to;

//    bool multiple; // helper to judge whether the card has multiple targets
//    // does not make sense if the card inherits SkillCard
//    bool nullptrified;
};

struct SlashEffectStruct
{
    SlashEffectStruct();

//    int jink_num;

//    const Card *slash;
//    const Card *jink;

//    ServerPlayer *from;
//    ServerPlayer *to;

//    int drank;

//    DamageStruct::Nature nature;

//    bool nullptrified;
};

struct CardUseStruct
{

    CardUseStruct();
//    CardUseStruct(const Card *card, ServerPlayer *from, QList<ServerPlayer *> to, bool isOwnerUse = true);
//    CardUseStruct(const Card *card, ServerPlayer *from, ServerPlayer *target, bool isOwnerUse = true);
    bool isValid(const QString &pattern) const;
    void parse(const QString &str, Room *room);
    bool tryParse(const QVariant &usage, Room *room);

//    const Card *card;
//    ServerPlayer *from;
//    QList<ServerPlayer *> to;
//    bool m_isOwnerUse;
//    bool m_addHistory;
//    bool m_isHandcard;
//    QStringList nullptrified_list;
    QSgsEnum::CardUseReason m_reason;
};

struct SkillInvokeStruct
{
    // Skill, player, skillowner, target, card

};

class CardMovement
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

struct CardsMoveOneTimeStruct
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

struct CardsMoveStruct
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

struct DyingStruct
{
    DyingStruct();

//    ServerPlayer *who; // who is ask for help
//    DamageStruct *damage; // if it is nullptr that means the dying is caused by losing hp
};

struct DeathStruct
{
    DeathStruct();

//    ServerPlayer *who; // who is dead
//    DamageStruct *damage; // if it is nullptr that means the dying is caused by losing hp
};

struct RecoverStruct
{
    RecoverStruct();

//    int recover;
//    ServerPlayer *who;
//    const Card *card;
};

struct PindianStruct
{
    PindianStruct();
    bool isSuccess() const;

//    ServerPlayer *from;
//    ServerPlayer *to;
//    const Card *from_card;
//    const Card *to_card;
//    int from_number;
//    int to_number;
//    QString reason;
//    bool success;
};

struct JudgeStruct
{
    JudgeStruct();
    bool isGood() const;
    bool isBad() const;
    bool isEffected() const;
    void updateResult();

    bool isGood(const Card *card) const; // For AI

//    ServerPlayer *who;
//    const Card *card;
//    QString pattern;
//    bool good;
//    QString reason;
//    bool time_consuming;
//    bool negative;
//    bool play_animation;

//private:
//    enum TrialResult
//    {
//        TRIAL_RESULT_UNKNOWN,
//        TRIAL_RESULT_GOOD,
//        TRIAL_RESULT_BAD
//    } _m_result;
};

struct PhaseChangeStruct
{
    PhaseChangeStruct();
//    Player::Phase from;
//    Player::Phase to;
};

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

struct CardResponseStruct
{
    inline CardResponseStruct()
    {
//        m_card = nullptr;
//        m_who = nullptr;
//        m_isUse = false;
//        m_isRetrial = false;
    }

//    inline CardResponseStruct(const Card *card)
//    {
//        m_card = card;
//        m_who = nullptr;
//        m_isUse = false;
//        m_isRetrial = false;
//    }

//    inline CardResponseStruct(const Card *card, ServerPlayer *who)
//    {
//        m_card = card;
//        m_who = who;
//        m_isUse = false;
//        m_isRetrial = false;
//    }

//    inline CardResponseStruct(const Card *card, bool isUse)
//    {
//        m_card = card;
//        m_who = nullptr;
//        m_isUse = isUse;
//        m_isRetrial = false;
//    }

//    inline CardResponseStruct(const Card *card, ServerPlayer *who, bool isUse)
//    {
//        m_card = card;
//        m_who = who;
//        m_isUse = isUse;
//        m_isRetrial = false;
//    }

//    const Card *m_card;
//    ServerPlayer *m_who;
//    bool m_isUse;
//    bool m_isHandcard;
//    bool m_isRetrial;
};

struct PlayerNumStruct
{
    inline PlayerNumStruct()
    {
//        m_num = 0;
//        m_toCalculate = QString();
//        m_type = MaxCardsType::Max;
//        m_reason = QString();
    }

//    inline PlayerNumStruct(int num, const QString &toCalculate)
//    {
//        m_num = num;
//        m_toCalculate = toCalculate;
//        m_type = MaxCardsType::Max;
//        m_reason = QString();
//    }

//    inline PlayerNumStruct(int num, const QString &toCalculate, MaxCardsType::MaxCardsCount type)
//    {
//        m_num = num;
//        m_toCalculate = toCalculate;
//        m_type = type;
//        m_reason = QString();
//    }

//    inline PlayerNumStruct(int num, const QString &toCalculate, MaxCardsType::MaxCardsCount type, const QString &reason)
//    {
//        m_num = num;
//        m_toCalculate = toCalculate;
//        m_type = type;
//        m_reason = reason;
//    }

//    MaxCardsType::MaxCardsCount m_type;
//    int m_num;
//    QString m_toCalculate;
//    QString m_reason;
};



struct LogMessage
{
    LogMessage();
    QString toString() const;
    QVariant toVariant() const;

//    QString type;
//    ServerPlayer *from;
//    QList<ServerPlayer *> to;
//    QString card_str;
//    QString arg;
//    QString arg2;
};

struct AskForMoveCardsStruct
{
    AskForMoveCardsStruct();

//    QList<int> top;
//    QList<int> bottom;

//    bool is_success;
};

Q_DECLARE_METATYPE(DamageStruct)
Q_DECLARE_METATYPE(CardEffectStruct)
Q_DECLARE_METATYPE(SlashEffectStruct)
Q_DECLARE_METATYPE(CardUseStruct)
Q_DECLARE_METATYPE(CardsMoveStruct)
Q_DECLARE_METATYPE(CardsMoveOneTimeStruct)
Q_DECLARE_METATYPE(DyingStruct)
Q_DECLARE_METATYPE(DeathStruct)
Q_DECLARE_METATYPE(RecoverStruct)
Q_DECLARE_METATYPE(PhaseChangeStruct)
Q_DECLARE_METATYPE(CardResponseStruct)
Q_DECLARE_METATYPE(PlayerNumStruct)
//Q_DECLARE_METATYPE(Card *)
//Q_DECLARE_METATYPE(ServerPlayer *)
//Q_DECLARE_METATYPE(JudgeStruct *)
//Q_DECLARE_METATYPE(PindianStruct *)
Q_DECLARE_METATYPE(AskForMoveCardsStruct)
#endif

