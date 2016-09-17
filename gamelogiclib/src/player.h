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

#ifndef _PLAYER_H
#define _PLAYER_H

#include "libqsgsgamelogicglobal.h"
#include "enumeration.h"

class General;
class Card;
class Skill;
class TriggerSkill;
class PlayerPrivate;

class LIBQSGSGAMELOGIC_EXPORT Player final : public QObject
{
    Q_OBJECT

public:
    explicit Player(QObject *parent);
    ~Player();

    // property setters/getters
    int hp() const;
    void setHp(int hp);
    int maxHp() const;
    void setMaxHp(int maxHp);
    int lostHp() const;
    bool isWounded() const;
    QSgsEnum::GeneralGender gender() const;
    void setGender(QSgsEnum::GeneralGender gender);
    bool isMale() const;
    bool isFemale() const;
    bool isNeuter() const;

    void setDisableShow(const QString &flags, const QString &reason);
    void removeDisableShow(const QString &reason);
    bool disableShow(bool head, QStringList *reasons = nullptr) const;

    const QString &kingdom() const;
    void setKingdom(const QString &kingdom);
    void setGeneral(const General *general);
    void setGeneralName(const QString &general_name);
    const QString &generalName() const;

    void setGeneral2Name(const QString &general_name);
    const QString &general2Name() const;
    const General *general2() const;

    void setState(const QString &state);
    const QString &state() const;

    int seat() const;
    void setSeat(int seat);
    bool isAdjacentTo(const Player *another) const;
    QString phaseString() const;
    void setPhaseString(const QString &phase_str);
    QSgsEnum::PlayerPhase phase() const;
    void setPhase(QSgsEnum::PlayerPhase phase);

    int attackRange(bool include_weapon = true) const;
    bool inMyAttackRange(const Player *other) const;

    bool isAlive() const;
    bool isDead() const;
    void setAlive(bool alive);

    QString flags() const;
    QStringList flagList() const;
    void setFlag(const QString &flag);
    bool hasFlag(const QString &flag) const;
    void clearFlags();

    bool faceUp() const;
    void setFaceUp(bool faceUp);

    inline bool superposed() const { return faceUp(); }
    void setSuperposed(bool superposed) { setFaceUp(superposed); }

    void setFixedDistance(const Player *player, int distance);
    int originalRightDistanceTo(const Player *other) const;
    int distanceTo(const Player *other, int distance_fix = 0) const;

    bool isLord() const;

    void acquireSkill(const QString &skill_name, bool head = true);
    void detachSkill(const QString &skill_name);
    void detachAllSkills();
    void addSkill(const QString &skill_name, bool head_skill = true);
    void loseSkill(const QString &skill_name);
    bool hasSkill(const QString &skill_name, bool include_lose = false) const;
    bool hasSkill(const Skill *skill, bool include_lose = false) const;
    bool hasSkills(const QString &skill_name, bool include_lose = false) const;
    bool hasInnateSkill(const QString &skill_name) const;
    bool hasLordSkill(const QString &skill_name, bool include_lose = false) const;

    bool hasDelayedEffect(const QString &effectName) const;
    void setDelayedEffect(const QString &effectName);

    bool hasEquip(Card *card) const;
    bool hasEquip() const;

    QList<const Card *> judgingArea() const;
    const QList<Card *> &judgingArea();
    QList<int> judgingAreaID() const;
    void addDelayedTrick(Card *trick);
    void removeDelayedTrick(Card *trick);
    bool containsTrick(const QString &trick_name) const;

    int handcardNum() const;
    void removeCard(Card *card, QSgsEnum::CardPlace place);
    void addCard(Card *card, QSgsEnum::CardPlace place);
    QList<const Card *> handcards() const;
    const QList<Card *> &handcards();

    Card *weapon() const;
    Card *armor() const;
    Card *defensiveHorse() const;
    Card *offensiveHorse() const;
    Card *treasure() const;

    QList<const Card *> equips() const;
    const QList<Card *> &equips();
    Card *equip(int index) const;

    bool hasWeapon(const QString &weapon_name) const;
    bool hasArmor(const QString &armor_name) const;
    bool hasTreasure(const QString &treasure_name) const;

    bool isKongcheng() const;
    bool isNude() const;
    bool isAllNude() const;

    bool canDiscard(const Player *to, const QString &flags) const;
    bool canDiscard(const Player *to, int card_id) const;

    void addMark(const QString &mark, int add_num = 1);
    void removeMark(const QString &mark, int remove_num = 1);
    void setMark(const QString &mark, int value);
    int mark(const QString &mark) const;

    void setChained(bool chained);
    bool isChained() const;
    bool canBeChainedBy(const Player *source = nullptr) const;

    void setRemoved(bool removed);
    bool isRemoved() const;

    bool isDuanchang(const bool head = true) const;

    bool canSlash(const Player *other, Card *slash, bool distance_limit = true, int rangefix = 0) const;
    bool canSlash(const Player *other, bool distance_limit = true, int rangefix = 0) const;
    int getCardCount(bool include_equip) const;

    QList<int> pile(const QString &pile_name) const;
    QStringList pileNames() const;
    QString pileName(int card_id) const;

    QList<int> handPile() const;
    QStringList handPileList(bool view_as_skill = true) const;

    bool pileOpen(const QString &pile_name, const QString &player) const;
    void setPileOpen(const QString &pile_name, const QString &player);

    void addHistory(const QString &name, int times = 1);
    void clearHistory(const QString &name = QString());
    bool hasUsed(const QString &card_class) const;
    int usedTimes(const QString &card_class) const;
    int slashCount() const;

    bool hasEquipSkill(const QString &skill_name) const;
    QSet<const TriggerSkill *> triggerSkills() const;
    QSet<const Skill *> skills(bool include_equip = false, bool visible_only = true) const;
    QList<const Skill *> skillList(bool include_equip = false, bool visible_only = true) const;
    QList<const Skill *> headSkillList(bool visible_only = true) const;
    QList<const Skill *> deputySkillList(bool visible_only = true) const;
    QSet<const Skill *> visibleSkills(bool include_equip = false) const;
    QList<const Skill *> visibleSkillList(bool include_equip = false) const;
    QSet<QString> acquiredSkills() const;

    QStringList acquiredSkills(const QString &flags) const;

    bool isProhibited(const Player *to, Card *card) const;
    bool canSlashWithoutCrossbow(Card *slash = nullptr) const;
    bool isLastHandCard(Card *card, bool contain = false) const;

    inline bool isJilei(Card *card) const
    {
        return isCardLimited(card, QSgsEnum::CardHandlingMethod::Discard);
    }
    inline bool isLocked(Card *card) const
    {
        return isCardLimited(card, QSgsEnum::CardHandlingMethod::Use);
    }

    void setCardLimitation(const QString &limit_list, const QString &pattern, bool single_turn = false);
    void removeCardLimitation(const QString &limit_list, const QString &pattern);
    void clearCardLimitation(bool single_turn = false);
    bool isCardLimited(Card *card, QSgsEnum::CardHandlingMethod method, bool isHandcard = false) const;

    // just for convenience
    void addQinggangTag(Card *card);
    void removeQinggangTag(Card *card);
    const Player *getLord(bool include_death = false) const; // a small function put here, simple but useful

    void copyFrom(Player *p);

    QList<const Player *> siblings() const;
    const QList<Player *> &siblings();
    QList<const Player *> aliveSiblings() const;
    const QList<Player *> &aliveSiblings();

    bool hasShownSkill(const Skill *skill) const;
    bool hasShownSkill(const QString &skill_name) const;
    bool hasShownSkills(const QString &skill_names) const;
    void preshowSkill(const QString &skill_name);
    bool inHeadSkills(const QString &skill_name) const;
    bool inHeadSkills(const Skill *skill) const;
    bool inDeputySkills(const QString &skill_name) const;
    bool inDeputySkills(const Skill *skill) const;
    const General *actualGeneral1() const;
    const General *actualGeneral2() const;
    QString actualGeneral1Name() const;
    QString actualGeneral2Name() const;
    void setActualGeneral1(const General *general);
    void setActualGeneral2(const General *general);
    void setActualGeneral1Name(const QString &name);
    void setActualGeneral2Name(const QString &name);
    bool hasShownGeneral1() const;
    bool hasShownGeneral2() const;
    void setGeneral1Showed(bool showed);
    void setGeneral2Showed(bool showed);
    bool hasShownOneGeneral() const;
    bool hasShownAllGenerals() const;
    void setSkillPreshowed(const QString &skill, bool preshowed = true);
    void setSkillsPreshowed(const QString &flags = QStringLiteral("hd"), bool preshowed = true);
    bool hasPreshowedSkill(const QString &name) const;
    bool hasPreshowedSkill(const Skill *skill) const;
    bool isHidden(const bool &head_general) const;

    bool ownSkill(const QString &skill_name) const;
    bool ownSkill(const Skill *skill) const;
    bool isFriendWith(const Player *player) const;
    bool willBeFriendWith(const Player *player) const;

    void setNext(Player *next);
    void setNext(const QString &next);
    Player *next(bool ignoreRemoved = true) const;
    QString nextName() const;
    Player *last(bool ignoreRemoved = true) const;
    Player *nextAlive(int n = 1, bool ignoreRemoved = true) const;
    Player *lastAlive(int n = 1, bool ignoreRemoved = true) const;

    QList<const Player *> formation() const;
    const QList<Player *> &formation();

    QVariantMap tag;

protected:
    Q_DECLARE_PRIVATE(Player)
    PlayerPrivate *d_ptr;
};

#endif

