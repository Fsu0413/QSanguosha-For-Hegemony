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
#include "cardface.h"
#include "general.h"

class Player : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString screenname READ screenName WRITE setScreenName)
    Q_PROPERTY(int m_hp READ hp WRITE setHp)
    Q_PROPERTY(int maxhp READ maxHp WRITE setMaxHp)
    Q_PROPERTY(QString m_kingdom READ kingdom WRITE setKingdom)
    Q_PROPERTY(bool wounded READ isWounded STORED false)
    Q_PROPERTY(QString m_role READ role WRITE setRole)
    Q_PROPERTY(QString m_general READ generalName WRITE setGeneralName)
    Q_PROPERTY(QString m_general2 READ general2Name WRITE setGeneral2Name)
    Q_PROPERTY(QString m_state READ state WRITE setState)
    Q_PROPERTY(int handcard_num READ handcardNum)
    Q_PROPERTY(int m_seat READ seat WRITE setSeat)
    Q_PROPERTY(QString m_phase READ phaseString WRITE setPhaseString)
    Q_PROPERTY(bool faceup READ faceUp WRITE setFaceUp)
    Q_PROPERTY(bool m_alive READ isAlive WRITE setAlive)
    Q_PROPERTY(QString m_flags READ flags WRITE setFlags)
    Q_PROPERTY(bool m_chained READ isChained WRITE setChained)
    Q_PROPERTY(bool m_removed READ isRemoved WRITE setRemoved)
    Q_PROPERTY(bool m_owner READ isOwner WRITE setOwner)
    Q_PROPERTY(bool m_roleShown READ hasShownRole WRITE setShownRole)

    Q_PROPERTY(bool kongcheng READ isKongcheng)
    Q_PROPERTY(bool nude READ isNude)
    Q_PROPERTY(bool all_nude READ isAllNude)

    Q_PROPERTY(QString m_actualGeneral1 READ actualGeneral1Name WRITE setActualGeneral1Name)
    Q_PROPERTY(QString m_actualGeneral2 READ actualGeneral2Name WRITE setActualGeneral2Name)
    Q_PROPERTY(bool m_general1Showed READ hasShownGeneral1 WRITE setGeneral1Showed)
    Q_PROPERTY(bool m_general2Showed READ hasShownGeneral2 WRITE setGeneral2Showed)

    Q_PROPERTY(QString m_next READ nextName WRITE setNext)

    Q_PROPERTY(bool m_scenarioRoleShown READ scenarioRoleShown WRITE setScenarioRoleShown)

    Q_PROPERTY(int head_skin_id READ getHeadSkinId WRITE setHeadSkinId)
    Q_PROPERTY(int deputy_skin_id READ getDeputySkinId WRITE setDeputySkinId)

    Q_ENUMS(Phase)
    Q_ENUMS(Place)
    Q_ENUMS(Role)

public:
    enum Phase
    {
        RoundStart, Start, Judge, Draw, Play, Discard, Finish, NotActive, PhaseNone
    };
    enum Place
    {
        PlaceHand, PlaceEquip, PlaceDelayedTrick, PlaceJudge,
        PlaceSpecial, DiscardPile, DrawPile, PlaceTable, PlaceUnknown,
        PlaceWuGu, DrawPileBottom
    };
    enum Relation
    {
        Friend, Enemy, Neutrality
    };
    enum Role
    {
        Lord, Loyalist, Rebel, Renegade
    };
    enum ArrayType
    {
        Siege,
        Formation
    };

    explicit Player(QObject *parent);

    void setScreenName(const QString &m_screenName);
    QString screenName() const;

    // property setters/getters
    int hp() const;
    void setHp(int hp);
    int maxHp() const;
    void setMaxHp(int maxHp);
    int lostHp() const;
    bool isWounded() const;
    General::Gender gender() const;
    virtual void setGender(General::Gender gender);
    bool isMale() const;
    bool isFemale() const;
    bool isNeuter() const;

    bool isOwner() const;
    void setOwner(bool owner);

    bool hasShownRole() const;
    void setShownRole(bool shown);

    void setDisableShow(const QString &m_flags, const QString &reason);
    void removeDisableShow(const QString &reason);
    QStringList disableShow(bool head) const;

    QString kingdom() const;
    void setKingdom(const QString &m_kingdom);

    void setRole(const QString &m_role);
    QString role() const;
    Role roleEnum() const;

    void setGeneral(const General *m_general);
    void setGeneralName(const QString &general_name);
    QString generalName() const;

    void setGeneral2Name(const QString &general_name);
    QString general2Name() const;
    const General *general2() const;

    QString footnoteName() const;

    void setState(const QString &state);
    QString state() const;

    int seat() const;
    void setSeat(int seat);
    bool isAdjacentTo(const Player *another) const;
    QString phaseString() const;
    void setPhaseString(const QString &phase_str);
    Phase phase() const;
    void setPhase(Phase m_phase);

    int attackRange(bool include_weapon = true) const;
    bool inMyAttackRange(const Player *other) const;

    bool isAlive() const;
    bool isDead() const;
    void setAlive(bool alive);

    QString flags() const;
    QStringList flagList() const;
    virtual void setFlags(const QString &flag);
    bool hasFlag(const QString &flag) const;
    void clearFlags();

    bool faceUp() const;
    void setFaceUp(bool faceUp);

    void setFixedDistance(const Player *player, int distance);
    int originalRightDistanceTo(const Player *other) const;
    int distanceTo(const Player *other, int distance_fix = 0) const;
    const General *avatarGeneral() const;
    const General *general() const;

    bool isLord() const;

    void acquireSkill(const QString &skill_name, bool head = true);
    void detachSkill(const QString &skill_name);
    void detachAllSkills();
    virtual void addSkill(const QString &skill_name, bool head_skill = true);
    virtual void loseSkill(const QString &skill_name);
    bool hasSkill(const QString &skill_name, bool include_lose = false) const;
    bool hasSkill(const Skill *skill, bool include_lose = false) const;
    bool hasSkills(const QString &skill_name, bool include_lose = false) const;
    bool hasInnateSkill(const QString &skill_name) const;
    bool hasLordSkill(const QString &skill_name, bool include_lose = false) const;

    void setEquip(Card *equip);
    void removeEquip(Card *equip);
    bool hasEquip(const Card *card) const;
    bool hasEquip() const;

    QList<const Card *> judgingArea() const;
    QList<int> judgingAreaID() const; //for marshal
    void addDelayedTrick(const Card *trick);
    void removeDelayedTrick(const Card *trick);
    bool containsTrick(const QString &trick_name) const;

    virtual int handcardNum() const = 0;
    virtual void removeCard(const Card *card, Place place) = 0;
    virtual void addCard(const Card *card, Place place) = 0;
    virtual QList<const Card *> handcards() const = 0;

    Card *weapon() const;
    Card *armor() const;
    Card *defensiveHorse() const;
    Card *offensiveHorse() const;
    Card *treasure() const;

    QList<const Card *> equips() const;
    const Card *equip(int index) const;

    bool hasWeapon(const QString &weapon_name) const;
    bool hasArmorEffect(const QString &armor_name) const;
    bool hasTreasure(const QString &treasure_name) const;

    bool isKongcheng() const;
    bool isNude() const;
    bool isAllNude() const;

    bool canDiscard(const Player *to, const QString &m_flags) const;
    bool canDiscard(const Player *to, int card_id) const;

    void addMark(const QString &mark, int add_num = 1);
    void removeMark(const QString &mark, int remove_num = 1);
    virtual void setMark(const QString &mark, int value);
    int mark(const QString &mark) const;

    void setChained(bool m_chained);
    bool isChained() const;
    bool canBeChainedBy(const Player *source = NULL) const;

    void setRemoved(bool m_removed);
    bool isRemoved() const;

    bool isDuanchang(const bool head = true) const;

    bool canSlash(const Player *other, const Card *slash, bool distance_limit = true,
        int rangefix = 0, const QList<const Player *> &others = QList<const Player *>()) const;
    bool canSlash(const Player *other, bool distance_limit = true,
        int rangefix = 0, const QList<const Player *> &others = QList<const Player *>()) const;
    int getCardCount(bool include_equip) const;

    QList<int> pile(const QString &pile_name) const;
    QStringList pileNames() const;
    QString pileName(int card_id) const;

    //Xusine:
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

    //Xusine:
    QStringList acquiredSkills(const QString &flags) const;

    QString skillDescription(bool inToolTip = true) const;
    QString headSkillDescription() const;
    QString deputySkillDescription() const;

    virtual bool isProhibited(const Player *to, const Card *card, const QList<const Player *> &others = QList<const Player *>()) const;
    bool canSlashWithoutCrossbow(const Card *slash = NULL) const;
    virtual bool isLastHandCard(const Card *card, bool contain = false) const = 0;

    inline bool isJilei(const Card *card) const
    {
        return isCardLimited(card, CardFace::MethodDiscard);
    }
    inline bool isLocked(const Card *card) const
    {
        return isCardLimited(card, CardFace::MethodUse);
    }

    void setCardLimitation(const QString &limit_list, const QString &pattern, bool single_turn = false);
    void removeCardLimitation(const QString &limit_list, const QString &pattern);
    void clearCardLimitation(bool single_turn = false);
    bool isCardLimited(const Card *card, CardFace::HandlingMethod method, bool isHandcard = false) const;

    // just for convenience
    void addQinggangTag(const Card *card);
    void removeQinggangTag(const Card *card);
    const Player *getLord(bool include_death = false) const; // a small function put here, simple but useful

    void copyFrom(Player *p);

    virtual QList<const Player *> getSiblings() const = 0;
    virtual QList<const Player *> getAliveSiblings() const = 0;

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
    void setActualGeneral1(const General *m_general);
    void setActualGeneral2(const General *m_general);
    void setActualGeneral1Name(const QString &name);
    void setActualGeneral2Name(const QString &name);
    bool hasShownGeneral1() const;
    bool hasShownGeneral2() const;
    void setGeneral1Showed(bool showed);
    void setGeneral2Showed(bool showed);
    bool hasShownOneGeneral() const;
    bool hasShownAllGenerals() const;
    void setSkillPreshowed(const QString &skill, bool preshowed = true);
    void setSkillsPreshowed(const QString &falgs = "hd", bool preshowed = true);
    bool hasPreshowedSkill(const QString &name) const;
    bool hasPreshowedSkill(const Skill *skill) const;
    bool isHidden(const bool &head_general) const;

    inline bool scenarioRoleShown() const
    {
        return m_scenarioRoleShown;
    }
    inline void setScenarioRoleShown(bool show)
    {
        m_scenarioRoleShown = show;
    }

    bool ownSkill(const QString &skill_name) const;
    bool ownSkill(const Skill *skill) const;
    bool isFriendWith(const Player *player) const;
    bool willBeFriendWith(const Player *player) const;

    void setNext(Player *m_next);
    void setNext(const QString &m_next);
    Player *next(bool ignoreRemoved = true) const;
    QString nextName() const;
    Player *last(bool ignoreRemoved = true) const;
    Player *nextAlive(int n = 1, bool ignoreRemoved = true) const;
    Player *lastAlive(int n = 1, bool ignoreRemoved = true) const;

    QList<const Player *> formation() const;

//    virtual void setHeadSkinId(int id);
//    int getHeadSkinId() const;

//    virtual void setDeputySkinId(int id);
//    int getDeputySkinId() const;

//    virtual QStringList getBigKingdoms(const QString &reason, MaxCardsType::MaxCardsCount type = MaxCardsType::Min) const = 0;

    QVariantMap tag;

protected:
    QMap<QString, int> m_marks;
    QMap<QString, QList<int> > m_piles;
    QMap<QString, QStringList> m_pileOpen;
    QSet<QString> m_headAcquiredSkills, m_deputyAcquiredSkills;
    QMap<QString, bool> m_headSkills;
    QMap<QString, bool> m_deputySkills;
    QSet<QString> m_flags;
    QHash<QString, int> m_history;

    const General *m_general, *m_general2;
    int m_headSkinId, m_deputySkinId;

private:
    QString m_screenName;
    bool m_owner;
    General::Gender m_gender;
    int m_hp, m_maxHp;
    QString m_kingdom;
    QString m_role;
    bool m_roleShown;
    QString m_state;
    int m_seat;
    bool m_alive;

    const General *m_actualGeneral1, *m_actualGeneral2;

    bool m_general1Showed, m_general2Showed;

    Phase m_phase;
    Card *m_weapon, *m_armor, *m_defensiveHorse, *m_offensiveHorse, *m_treasure;
    bool m_faceUp;
    bool m_chained;
    bool m_removed;
    QList<int> m_judgingArea;
    QHash<const Player *, int> m_fixedDistance;
    QString m_next;

    QMap<CardFace::HandlingMethod, QStringList> m_cardLimitation;

    QStringList m_disableShow;
    // head and/or deputy, reason
    // example: "hd,Blade"

    bool m_scenarioRoleShown;

signals:
    void general_changed();
    void general2_changed();
    void role_changed(const QString &new_role);
    void state_changed();
    void hp_changed();
    void kingdom_changed(const QString &new_kingdom);
    void phase_changed();
    void owner_changed(bool m_owner);
    void head_state_changed();
    void deputy_state_changed();
    void disable_show_changed();
    void removedChanged();
};

#endif

