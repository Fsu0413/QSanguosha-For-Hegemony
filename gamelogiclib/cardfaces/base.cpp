#include "base.h"
#include "skill.h"

BasicCard::BasicCard(const QString &name) : CardFace(name)
{
    m_handlingMethod = QSgsEnum::CardHandlingMethod::Use;
}

QString BasicCard::type() const
{
    return "basic";
}

QSgsEnum::CardType BasicCard::typeId() const
{
    return QSgsEnum::CardType::Basic;
}

TrickCard::TrickCard(const QString &name)
    : CardFace(name),m_cancelable(true)
{
    m_handlingMethod = QSgsEnum::CardHandlingMethod::Use;
}

void TrickCard::setCancelable(bool cancelable)
{
    m_cancelable = cancelable;
}

QString TrickCard::type() const
{
    return "trick";
}

QSgsEnum::CardType TrickCard::typeId() const
{
    return QSgsEnum::CardType::Trick;
}

bool TrickCard::isCancelable(const CardEffectStruct &effect) const
{
    Q_UNUSED(effect);
    return m_cancelable;
}


DelayedTrick::DelayedTrick(const QString &name, bool movable) : TrickCard(name),m_movable(movable)
{
    judge.negative = true;
}

void DelayedTrick::onNullified(ServerPlayer *target) const
{
    Room *room = target->getRoom();
    RoomThread *thread = room->getThread();
    if (m_movable) {
        QList<ServerPlayer *> players;
        QList<ServerPlayer *> count_players = room->getPlayers();
        ServerPlayer *starter = target;
        int index = count_players.indexOf(starter);
        for (int i = index + 1; i < count_players.length(); i++) {
            if (count_players[i]->isAlive())
                players << count_players[i];
        }

        for (int i = 0; i <= index; i++) {
            if (count_players[i]->isAlive())
                players << count_players[i];
        }

        ServerPlayer *p = NULL;

        foreach (ServerPlayer *player, players) {
            if (player->containsTrick(objectName()))
                continue;

            const ProhibitSkill *skill = room->isProhibited(target, player, this);
            if (skill) {
                LogMessage log;
                log.type = "#SkillAvoid";
                log.from = player;
                log.arg = skill->objectName();
                log.arg2 = objectName();
                room->sendLog(log);

                room->broadcastSkillInvoke(skill->objectName(), player);
                continue;
            }

            CardMoveReason reason(CardMoveReason::S_REASON_TRANSFER, target->objectName(), QString(), this->getSkillName(), QString());
            room->moveCardTo(this, target, player, QSgsEnum::PlayerPlace::Judge, reason, true);

            if (target == player) break;

            CardUseStruct use(this, NULL, player);
            QVariant data = QVariant::fromValue(use);
            thread->trigger(QSgsEnum::TriggerEvent::TargetConfirming, room, player, data);
            CardUseStruct new_use = data.value<CardUseStruct>();
            if (new_use.to.isEmpty()) {
                p = player;
                break;
            }

            foreach(ServerPlayer *p, room->getAllPlayers())
                thread->trigger(QSgsEnum::TriggerEvent::TargetChosen, room, p, data);
            foreach(ServerPlayer *p, room->getAllPlayers())
                thread->trigger(QSgsEnum::TriggerEvent::TargetConfirmed, room, p, data);
            break;
        }
        if (p)
            onNullified(p);
    } else {
        CardMoveReason reason(CardMoveReason::S_REASON_NATURAL_ENTER, target->objectName());
        room->throwCard(this, reason, NULL);
    }
}

void DelayedTrick::onUse(Room *room, const CardUseStruct &card_use) const
{
    CardUseStruct use = card_use;
    //WrappedCard *wrapped = Sanguosha->getWrappedCard(this->getEffectiveId());
    //use.card = wrapped;

    LogMessage log;
    log.from = use.from;
    log.to = use.to;
    log.type = "#UseCard";
    log.card_str = toString();
    room->sendLog(log);

    QVariant data = QVariant::fromValue(use);
    RoomThread *thread = room->getThread();
    thread->trigger(QSgsEnum::TriggerEvent::PreCardUsed, room, use.from, data);

    CardMoveReason reason(CardMoveReason::S_REASON_USE, use.from->objectName(), use.to.first()->objectName(), getSkillName(), QString());
    room->moveCardTo(this, use.from, use.to.first(), QSgsEnum::PlayerPlace::Judge, reason, true);

    QString skill_name = wrapped->showSkill();
    if (!skill_name.isNull() && use.from->ownSkill(skill_name) && !use.from->hasShownSkill(skill_name))
        use.from->showGeneral(use.from->inHeadSkills(skill_name));

    thread->trigger(QSgsEnum::TriggerEvent::CardUsed, room, use.from, data);
    thread->trigger(QSgsEnum::TriggerEvent::CardFinished, room, use.from, data);
}

void DelayedTrick::use(Room *room, ServerPlayer *source, QList<ServerPlayer *> &targets) const
{
    QStringList nullified_list = room->getTag("CardUseNullifiedList").toStringList();
    bool all_nullified = nullified_list.contains("_ALL_TARGETS");
    if (all_nullified || targets.isEmpty()) {
        if (movable) {
            onNullified(source);
            if (room->getCardOwner(getEffectiveId()) != source) return;
        }
        CardMoveReason reason(CardMoveReason::S_REASON_USE, source->objectName(), QString(), this->getSkillName(), QString());
        room->moveCardTo(this, NULL, QSgsEnum::PlayerPlace::DiscardPile, reason, true);
    }
}

QString DelayedTrick::subtype() const
{
    return "delayed_trick";
}

void DelayedTrick::onEffect(const CardEffectStruct &effect) const
{
    Room *room = effect.to->getRoom();

    CardMoveReason reason(CardMoveReason::S_REASON_USE, effect.to->objectName(), getSkillName(), QString());
    room->moveCardTo(this, NULL, QSgsEnum::PlayerPlace::ProceedingArea, reason, true);

    LogMessage log;
    log.from = effect.to;
    log.type = "#DelayedTrick";
    log.arg = effect.card->objectName();
    room->sendLog(log);

    JudgeStruct judge_struct = judge;
    judge_struct.who = effect.to;
    room->judge(judge_struct);

    if (judge_struct.isBad()) {
        takeEffect(effect.to);
        if (room->getCardOwner(getEffectiveId()) == NULL) {
            CardMoveReason reason(CardMoveReason::S_REASON_NATURAL_ENTER, QString());
            room->throwCard(this, reason, NULL);
        }
    } else if (m_movable) {
        onNullified(effect.to);
    } else {
        if (room->getCardOwner(getEffectiveId()) == NULL) {
            CardMoveReason reason(CardMoveReason::S_REASON_NATURAL_ENTER, QString());
            room->throwCard(this, reason, NULL);
        }
    }
}


QString InstanceTrick::subtype() const
{
    return "ND_trick";
}

EquipCard::EquipCard(const QString &name) : CardFace(name)
{
    m_handlingMethod = QSgsEnum::CardHandlingMethod::Use;
}

QString EquipCard::type() const
{
    return "equip";
}

QSgsEnum::CardType EquipCard::typeId() const
{
    return QSgsEnum::CardType::Equip;
}

bool EquipCard::isAvailable(const Player *player) const
{
    return !player->isProhibited(player, this) && CardFace::isAvailable(player);
}

void EquipCard::onUse(Room *room, const CardUseStruct &card_use) const
{
    CardUseStruct use = card_use;

     ServerPlayer *player = use.from;
     if (use.to.isEmpty())
         use.to << player;

     QVariant data = QVariant::fromValue(use);
     RoomThread *thread = room->getThread();
     thread->trigger(QSgsEnum::TriggerEvent::PreCardUsed, room, player, data);
     thread->trigger(QSgsEnum::TriggerEvent::CardUsed, room, player, data);
     thread->trigger(QSgsEnum::TriggerEvent::CardFinished, room, player, data);
}

void EquipCard::use(Room *room, ServerPlayer *source, QList<ServerPlayer *> &targets) const
{
    if (targets.isEmpty()) {
        CardMoveReason reason(CardMoveReason::S_REASON_USE, source->objectName(), QString(), this->getSkillName(), QString());
        room->moveCardTo(this, room->getCardOwner(getEffectiveId()), NULL, QSgsEnum::PlayerPlace::DiscardPile, reason, true);
    }
    int equipped_id = Card::S_UNKNOWN_CARD_ID;
    ServerPlayer *target = targets.first();
    if (target->getEquip(location()))
        equipped_id = target->getEquip(location())->getEffectiveId();

    QList<CardsMoveStruct> exchangeMove;
    CardsMoveStruct move1(getEffectiveId(), target, QSgsEnum::PlayerPlace::Equip,
        CardMoveReason(CardMoveReason::S_REASON_USE, target->objectName()));
    exchangeMove.push_back(move1);
    if (equipped_id != Card::S_UNKNOWN_CARD_ID) {
        CardsMoveStruct move2(equipped_id, target, QSgsEnum::PlayerPlace::ProceedingArea,
            CardMoveReason(CardMoveReason::S_REASON_CHANGE_EQUIP, target->objectName()));
        exchangeMove.push_back(move2);
    }
    room->moveCardsAtomic(exchangeMove, true);

    LogMessage log;
    log.from = target;
    log.type = "$Install";
    log.card_str = QString::number(getEffectiveId());
    room->sendLog(log);

    if (equipped_id != Card::S_UNKNOWN_CARD_ID) {
        if (room->getCardPlace(equipped_id) == QSgsEnum::PlayerPlace::ProceedingArea) {
            CardsMoveStruct move3(equipped_id, NULL, QSgsEnum::PlayerPlace::DiscardPile,
                CardMoveReason(CardMoveReason::S_REASON_CHANGE_EQUIP, target->objectName()));
            room->moveCardsAtomic(move3, true);
        }
    }
}

void EquipCard::onInstall(ServerPlayer *player) const
{
    Room *room = player->getRoom();

    const Skill *skill = Sanguosha->getSkill(this);
    if (skill) {
        if (skill->inherits("ViewAsSkill")) {
            room->attachSkillToPlayer(player, this->objectName());
        } else if (skill->inherits("TriggerSkill")) {
            const TriggerSkill *trigger_skill = qobject_cast<const TriggerSkill *>(skill);
            room->getThread()->addTriggerSkill(trigger_skill);
            if (trigger_skill->getViewAsSkill())
                room->attachSkillToPlayer(player, this->objectName());
        }
    }
}

void EquipCard::onUninstall(ServerPlayer *player) const
{
    Room *room = player->getRoom();
    const Skill *skill = Sanguosha->getSkill(this);
    if (skill) {
        if (skill->inherits("ViewAsSkill")) {
            room->detachSkillFromPlayer(player, this->objectName(), true);
        } else if (skill->inherits("TriggerSkill")) {
            const TriggerSkill *trigger_skill = qobject_cast<const TriggerSkill *>(skill);
            if (trigger_skill->getViewAsSkill())
                room->detachSkillFromPlayer(player, this->objectName(), true);
        }
    }
}


Weapon::Weapon(const QString &name, int range)
    :EquipCard(name), m_range(range)
{

}

int Weapon::range() const
{
    return m_range;
}

QString Weapon::subtype() const
{
    return "weapon";
}

QSgsEnum::EquipLocation Weapon::location() const
{
    return QSgsEnum::EquipLocation::WeaponLocation;
}

QString Weapon::commonEffectName() const
{
    return "weapon";
}


Armor::Armor(const QString &name) : EquipCard(name)
{
}

QString Armor::subtype() const
{
    return "armor";
}

QSgsEnum::EquipLocation Armor::location() const
{
    return QSgsEnum::EquipLocation::ArmorLocation;
}

QString Armor::commonEffectName() const
{
    return "armor";
}

Horse::Horse(const QString &name, int correct)
    :EquipCard(name), m_correct(correct)
{

}

int Horse::correctNum() const
{
    return m_correct;
}

QString Horse::commonEffectName() const
{
    return "horse";
}

OffensiveHorse::OffensiveHorse(const QString &name, int correct, bool is_transferable)
    :Horse(name,correct)
{
    Q_UNUSED(is_transferable)
}

QString OffensiveHorse::subtype() const
{
    return "offensive_horse";
}

DefensiveHorse::DefensiveHorse(const QString &name, int correct)
    :Horse(name,correct)
{

}

QString DefensiveHorse::subtype() const
{
    return "defensive_horse";
}

Treasure::Treasure(const QString &name) : EquipCard(name)
{
}

QString Treasure::subtype() const
{
    return "treasure";
}

QSgsEnum::EquipLocation Treasure::location() const
{
    return QSgsEnum::EquipLocation::TreasureLocation;
}

QString Treasure::commonEffectName() const
{
    return "treasure";
}
