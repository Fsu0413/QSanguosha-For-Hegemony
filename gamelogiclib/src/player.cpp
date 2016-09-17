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

#include "player.h"
#include <QSgsCore/QSgsEngine>

class PlayerPrivate
{
public:
    QMap<QString, int> marks;
    QMap<QString, QList<int> > piles;
    QMap<QString, QStringList> pileOpen;
    QSet<QString> headAcquiredSkills;
    QSet<QString> deputyAcquiredSkills;
    QMap<QString, bool> headSkills;
    QMap<QString, bool> deputySkills;
    QSet<QString> flags;
    QHash<QString, int> history;

    QStringList delayedEffects;

    const General *general;
    const General *general2;

    QString screenName;
    bool owner;
    QSgsEnum::GeneralGender gender;
    int hp;
    int maxHp;
    QString kingdom;
    QString role;
    bool roleShown;
    QString state;
    int seat;
    bool alive;

    const General *actualGeneral1;
    const General *actualGeneral2;

    bool general1Showed;
    bool general2Showed;

    QSgsEnum::PlayerPhase phase;
    Card *weapon;
    Card *armor;
    Card *defensiveHorse;
    Card *offensiveHorse;
    Card *treasure;
    bool faceUp;
    bool chained;
    bool removed;
    QList<int> judgingArea;
    QHash<const Player *, int> fixedDistance;
    QString next;

    QMap<QSgsEnum::CardHandlingMethod, QStringList> cardLimitation;

    // head and/or deputy, reason
    // example: "hd,Blade"
    QStringList disableShow;

    bool scenarioRoleShown;
};

Player::Player(QObject *parent)
    : QObject(parent), d_ptr(new PlayerPrivate)
{
    Q_D(Player);
    d->general = d->general2 = d->actualGeneral1 = d->actualGeneral2 = nullptr;
    d->owner = d->roleShown = d->alive = d->general1Showed = d->general2Showed = d->faceUp = d->chained = d->removed = d->scenarioRoleShown = false;
    d->gender = QSgsEnum::GeneralGender::Neuter;
    d->hp = d->maxHp = d->seat = 0;
    d->phase = QSgsEnum::PlayerPhase::NoPhase;
    d->weapon = d->armor = d->defensiveHorse = d->offensiveHorse = d->treasure = nullptr;
}

Player::~Player()
{
    Q_D(Player);
    delete d;
}

int Player::hp() const
{
    Q_D(const Player);
    return d->hp;
}

void Player::setHp(int hp)
{
    Q_D(Player);
    d->hp = hp;
}

int Player::maxHp() const
{
    Q_D(const Player);
    return d->maxHp;
}

void Player::setMaxHp(int maxHp)
{
    Q_D(Player);
    d->maxHp = maxHp;
}

int Player::lostHp() const
{
    Q_D(const Player);
    return d->maxHp - d->hp;
}

bool Player::isWounded() const
{
    Q_D(const Player);
    return d->maxHp != d->hp;
}

QSgsEnum::GeneralGender Player::gender() const
{
    Q_D(const Player);
    return d->gender;
}

void Player::setGender(QSgsEnum::GeneralGender gender)
{
    Q_D(Player);
    d->gender = gender;
}

bool Player::isMale() const
{
    Q_D(const Player);
    return d->gender == QSgsEnum::GeneralGender::Male || d->gender == QSgsEnum::GeneralGender::Neuter;
}

bool Player::isFemale() const
{
    Q_D(const Player);
    return d->gender == QSgsEnum::GeneralGender::Female || d->gender == QSgsEnum::GeneralGender::Neuter;
}

bool Player::isNeuter() const
{
    Q_D(const Player);
    return d->gender == QSgsEnum::GeneralGender::Neuter;
}

void Player::setDisableShow(const QString &flags, const QString &reason)
{
    if (flags != QStringLiteral("h") || flags != QStringLiteral("d") || flags != QStringLiteral("hd"))
        return;

    removeDisableShow(reason);
    QString s = QStringLiteral("%1,%2").arg(flags).arg(reason);
    Q_D(Player);
    d->disableShow << s;
}

void Player::removeDisableShow(const QString &reason)
{
    Q_D(Player);
    foreach (const QString &s, d->disableShow) {
        QString r = s.split(QStringLiteral(",")).last();
        if (r == reason)
            d->disableShow.removeAll(s);
    }
}

bool Player::disableShow(bool head, QStringList *reasons) const
{
    QStringList reasons_;
    if (reasons == nullptr)
        reasons = &reasons_;
    else
        reasons->clear();

    Q_D(const Player);
    foreach (const QString &s, d->disableShow) {
        QStringList l = s.split(QStringLiteral(","));
        if (head && l.first().contains(QStringLiteral("h")))
            *reasons << l.last();
        else if (!head && l.first().contains(QStringLiteral("d")))
            *reasons << l.last();
    }

    return !reasons->isEmpty();
}

const QString &Player::kingdom() const
{
    Q_D(const Player);
    return d->kingdom;
}

void Player::setKingdom(const QString &kingdom)
{
    Q_D(Player);
    d->kingdom = kingdom;
}

void Player::setGeneral(const General *general)
{
    Q_D(Player);
    d->general = general;
}

void Player::setGeneralName(const QString &general_name)
{

}

const QString &Player::generalName() const
{
    return QString();
}

void Player::setGeneral2Name(const QString &general_name)
{

}

const QString &Player::general2Name() const
{
    return QString();
}

const General *Player::general2() const
{
    Q_D(const Player);
    return d->general2;
}

void Player::setState(const QString &state)
{
    Q_D(Player);
    d->state = state;
}

const QString &Player::state() const
{
    Q_D(const Player);
    return d->state;
}

int Player::seat() const
{
    Q_D(const Player);
    return d->seat;
}

void Player::setSeat(int seat)
{
    Q_D(Player);
    d->seat = seat;
}

bool Player::isAdjacentTo(const Player *another) const
{
    return false;
}

QString Player::phaseString() const
{
    return QString();
}

void Player::setPhaseString(const QString &phase_str)
{

}

QSgsEnum::PlayerPhase Player::phase() const
{
    Q_D(const Player);
    return d->phase;
}

void Player::setPhase(QSgsEnum::PlayerPhase phase)
{
    Q_D(Player);
    d->phase = phase;
}

int Player::attackRange(bool include_weapon) const
{
    return 0;
}

bool Player::inMyAttackRange(const Player *other) const
{
    return false;
}

bool Player::isAlive() const
{
    Q_D(const Player);
    return d->alive;
}

bool Player::isDead() const
{
    Q_D(const Player);
    return !d->alive;
}

void Player::setAlive(bool alive)
{
    Q_D(Player);
    d->alive = alive;
}

QString Player::flags() const
{
    return QString();
}

QStringList Player::flagList() const
{
    return QStringList();
}

void Player::setFlag(const QString &flag)
{

}

bool Player::hasFlag(const QString &flag) const
{
    return false;
}

void Player::clearFlags()
{

}

bool Player::faceUp() const
{
    Q_D(const Player);
    return d->faceUp;
}

void Player::setFaceUp(bool faceUp)
{
    Q_D(Player);
    d->faceUp = faceUp;
}

void Player::setFixedDistance(const Player *player, int distance)
{

}

int Player::originalRightDistanceTo(const Player *other) const
{
    return 0;
}

int Player::distanceTo(const Player *other, int distance_fix) const
{
    return 0;
}

bool Player::isLord() const
{
    return false;
}

void Player::acquireSkill(const QString &skill_name, bool head)
{

}

void Player::detachSkill(const QString &skill_name)
{

}

void Player::detachAllSkills()
{

}

void Player::addSkill(const QString &skill_name, bool head_skill)
{

}

void Player::loseSkill(const QString &skill_name)
{

}

bool Player::hasSkill(const QString &skill_name, bool include_lose) const
{
    return false;
}

bool Player::hasSkill(const Skill *skill, bool include_lose) const
{
    return false;
}

bool Player::hasSkills(const QString &skill_name, bool include_lose) const
{
    return false;
}

bool Player::hasInnateSkill(const QString &skill_name) const
{
    return false;
}

bool Player::hasLordSkill(const QString &skill_name, bool include_lose) const
{
    return false;
}

bool Player::hasDelayedEffect(const QString &effectName) const
{
    Q_D(const Player);
    return d->delayedEffects.contains(effectName);
}

void Player::setDelayedEffect(const QString &effectName)
{
    Q_D(Player);
    if (effectName.startsWith(QStringLiteral("-"))) {
        QString removed = effectName.mid(1);
        d->delayedEffects.removeAll(removed);
    } else
        d->delayedEffects << effectName;
}

bool Player::hasEquip(Card *card) const
{
    return false;
}

bool Player::hasEquip() const
{
    return false;
}

QList<const Card *> Player::judgingArea() const
{
    return QList<const Card *>();
}

const QList<Card *> &Player::judgingArea()
{
    return QList<Card *>();
}

QList<int> Player::judgingAreaID() const
{
    Q_D(const Player);
    return d->judgingArea;
}

void Player::addDelayedTrick(Card *trick)
{

}

void Player::removeDelayedTrick(Card *trick)
{

}

bool Player::containsTrick(const QString &trick_name) const
{
    return false;
}

int Player::handcardNum() const
{
    return false;
}

void Player::removeCard(Card *card, QSgsEnum::CardPlace place)
{

}

void Player::addCard(Card *card, QSgsEnum::CardPlace place)
{

}

QList<const Card *> Player::handcards() const
{
    return QList<const Card *>();
}

const QList<Card *> &Player::handcards()
{
    return QList<Card *>();
}

Card *Player::weapon() const
{
    Q_D(const Player);
    return d->weapon;
}

Card *Player::armor() const
{
    Q_D(const Player);
    return d->armor;
}

Card *Player::defensiveHorse() const
{
    Q_D(const Player);
    return d->defensiveHorse;
}

Card *Player::offensiveHorse() const
{
    Q_D(const Player);
    return d->offensiveHorse;
}

Card *Player::treasure() const
{
    Q_D(const Player);
    return d->treasure;
}

QList<const Card *> Player::equips() const
{
    return QList<const Card *>();
}

const QList<Card *> &Player::equips()
{
    return QList<Card *>();
}

Card *Player::equip(int index) const
{
    return nullptr;
}

bool Player::hasWeapon(const QString &weapon_name) const
{
    return false;
}

bool Player::hasArmor(const QString &armor_name) const
{
    return false;
}

bool Player::hasTreasure(const QString &treasure_name) const
{
    return false;
}

bool Player::isKongcheng() const
{
    return false;
}

bool Player::isNude() const
{
    return false;
}

bool Player::isAllNude() const
{
    return false;
}

bool Player::canDiscard(const Player *to, const QString &flags) const
{
    return false;
}

bool Player::canDiscard(const Player *to, int card_id) const
{
    return false;
}

void Player::addMark(const QString &mark, int add_num)
{

}

void Player::removeMark(const QString &mark, int remove_num)
{

}

void Player::setMark(const QString &mark, int value)
{

}

int Player::mark(const QString &mark) const
{
    return 0;
}

void Player::setChained(bool chained)
{
    Q_D(Player);
    d->chained = chained;
}

bool Player::isChained() const
{
    Q_D(const Player);
    return d->chained;
}

bool Player::canBeChainedBy(const Player *source) const
{
    return false;
}

void Player::setRemoved(bool removed)
{
    Q_D(Player);
    d->removed = removed;
}

bool Player::isRemoved() const
{
    Q_D(const Player);
    return d->removed;
}

bool Player::isDuanchang(const bool head) const
{
    return false;
}

bool Player::canSlash(const Player *other, Card *slash, bool distance_limit, int rangefix) const
{
    return false;
}

bool Player::canSlash(const Player *other, bool distance_limit, int rangefix) const
{
    return false;
}

int Player::getCardCount(bool include_equip) const
{
    return 0;
}

QList<int> Player::pile(const QString &pile_name) const
{
    return QList<int>();
}

QStringList Player::pileNames() const
{
    return QStringList();
}

QString Player::pileName(int card_id) const
{
    return QString();
}

QList<int> Player::handPile() const
{
    return QList<int>();
}

QStringList Player::handPileList(bool view_as_skill) const
{
    return QStringList();
}

bool Player::pileOpen(const QString &pile_name, const QString &player) const
{
    return false;
}

void Player::setPileOpen(const QString &pile_name, const QString &player)
{

}

void Player::addHistory(const QString &name, int times)
{

}

void Player::clearHistory(const QString &name)
{

}

bool Player::hasUsed(const QString &card_class) const
{
    return false;
}

int Player::usedTimes(const QString &card_class) const
{
    return 0;
}

int Player::slashCount() const
{
    return 0;
}

bool Player::hasEquipSkill(const QString &skill_name) const
{
    return false;
}

QSet<const TriggerSkill *> Player::triggerSkills() const
{
    return QSet<const TriggerSkill *>();
}

QSet<const Skill *> Player::skills(bool include_equip, bool visible_only) const
{
    return QSet<const Skill *>();
}

QList<const Skill *> Player::skillList(bool include_equip, bool visible_only) const
{
    return QList<const Skill *>();
}

QList<const Skill *> Player::headSkillList(bool visible_only) const
{
    return QList<const Skill *>();
}

QList<const Skill *> Player::deputySkillList(bool visible_only) const
{
    return QList<const Skill *>();
}

QSet<const Skill *> Player::visibleSkills(bool include_equip) const
{
    return QSet<const Skill *>();
}

QList<const Skill *> Player::visibleSkillList(bool include_equip) const
{
    return QList<const Skill *>();
}

QSet<QString> Player::acquiredSkills() const
{
    return QSet<QString>();
}

QStringList Player::acquiredSkills(const QString &flags) const
{
    return QStringList();
}

bool Player::isProhibited(const Player *to, Card *card) const
{
    return false;
}

bool Player::canSlashWithoutCrossbow(Card *slash) const
{
    return false;
}

bool Player::isLastHandCard(Card *card, bool contain) const
{
    return false;
}

void Player::setCardLimitation(const QString &limit_list, const QString &pattern, bool single_turn)
{

}

void Player::removeCardLimitation(const QString &limit_list, const QString &pattern)
{

}

void Player::clearCardLimitation(bool single_turn)
{

}

bool Player::isCardLimited(Card *card, QSgsEnum::CardHandlingMethod method, bool isHandcard) const
{
    return false;
}

void Player::addQinggangTag(Card *card)
{

}

void Player::removeQinggangTag(Card *card)
{

}

const Player *Player::getLord(bool include_death) const
{
    return nullptr;
}

void Player::copyFrom(Player *p)
{

}

QList<const Player *> Player::siblings() const
{
    return QList<const Player *>();
}

const QList<Player *> &Player::siblings()
{
    return QList<Player *>();
}

QList<const Player *> Player::aliveSiblings() const
{
    return QList<const Player *>();
}

const QList<Player *> &Player::aliveSiblings()
{
    return QList<Player *>();
}

bool Player::hasShownSkill(const Skill *skill) const
{
    return false;
}

bool Player::hasShownSkill(const QString &skill_name) const
{
    return false;
}

bool Player::hasShownSkills(const QString &skill_names) const
{
    return false;
}

void Player::preshowSkill(const QString &skill_name)
{

}

bool Player::inHeadSkills(const QString &skill_name) const
{
    return false;
}

bool Player::inHeadSkills(const Skill *skill) const
{
    return false;
}

bool Player::inDeputySkills(const QString &skill_name) const
{
    return false;
}

bool Player::inDeputySkills(const Skill *skill) const
{
    return false;
}

const General *Player::actualGeneral1() const
{
    Q_D(const Player);
    return d->actualGeneral1;
}

const General *Player::actualGeneral2() const
{
    Q_D(const Player);
    return d->actualGeneral2;
}

QString Player::actualGeneral1Name() const
{
    return QString();
}

QString Player::actualGeneral2Name() const
{
    return QString();
}

void Player::setActualGeneral1(const General *general)
{
    Q_D(Player);
    d->actualGeneral1 = general;
}

void Player::setActualGeneral2(const General *general)
{
    Q_D(Player);
    d->actualGeneral2 = general;
}

void Player::setActualGeneral1Name(const QString &name)
{

}

void Player::setActualGeneral2Name(const QString &name)
{

}

bool Player::hasShownGeneral1() const
{
    return false;
}

bool Player::hasShownGeneral2() const
{
    return false;
}

void Player::setGeneral1Showed(bool showed)
{

}

void Player::setGeneral2Showed(bool showed)
{

}

bool Player::hasShownOneGeneral() const
{
    return false;
}

bool Player::hasShownAllGenerals() const
{
    return false;
}

void Player::setSkillPreshowed(const QString &skill, bool preshowed)
{

}

void Player::setSkillsPreshowed(const QString &flags, bool preshowed)
{

}

bool Player::hasPreshowedSkill(const QString &name) const
{
    return false;
}

bool Player::hasPreshowedSkill(const Skill *skill) const
{
    return false;
}

bool Player::isHidden(const bool &head_general) const
{
    return false;
}

bool Player::ownSkill(const QString &skill_name) const
{
    return false;
}

bool Player::ownSkill(const Skill *skill) const
{
    return false;
}

bool Player::isFriendWith(const Player *player) const
{
    return false;
}

bool Player::willBeFriendWith(const Player *player) const
{
    return false;
}

void Player::setNext(Player *next)
{

}

void Player::setNext(const QString &next)
{

}

Player *Player::next(bool ignoreRemoved) const
{
    return nullptr;
}

QString Player::nextName() const
{
    return QString();
}

Player *Player::last(bool ignoreRemoved) const
{
    return nullptr;
}

Player *Player::nextAlive(int n, bool ignoreRemoved) const
{
    return nullptr;
}

Player *Player::lastAlive(int n, bool ignoreRemoved) const
{
    return nullptr;
}

QList<const Player *> Player::formation() const
{
    return QList<const Player *>();
}

const QList<Player *> &Player::formation()
{
    return QList<Player *>();
}

//#include "client.h"
//#include "standard-basics.h"
//#include "settings.h"

//Player::Player(QObject *parent)
//    : QObject(parent), m_general(nullptr), m_general2(nullptr),
//    m_headSkinId(0), m_deputySkinId(0), m_owner(false),
//    m_gender(QSgsEnum::GeneralGender::Sexless), m_hp(-1), m_maxHp(-1),
//    m_roleShown(false), m_state("online"), m_seat(0), m_alive(true),
//    m_actualGeneral1(nullptr), m_actualGeneral2(nullptr),
//    m_general1Showed(false), m_general2Showed(false),
//    m_phase(QSgsEnum::PlayerPhase::NotActive),
//    m_weapon(nullptr), m_armor(nullptr), m_defensiveHorse(nullptr), m_offensiveHorse(nullptr), m_treasure(nullptr),
//    m_faceUp(true), m_chained(false), m_removed(false), m_scenarioRoleShown(false)
//{
//}

//void Player::setScreenName(const QString &screen_name)
//{
//    this->m_screenName = screen_name;
//}

//QString Player::screenName() const
//{
//    return m_screenName;
//}

//bool Player::isOwner() const
//{
//    return m_owner;
//}

//void Player::setOwner(bool owner)
//{
//    if (this->m_owner != owner) {
//        this->m_owner = owner;
//        emit owner_changed(owner);
//    }
//}

//bool Player::hasShownRole() const
//{
//    return m_roleShown;
//}

//void Player::setShownRole(bool shown)
//{
//    this->m_roleShown = shown;
//}

//void Player::setHp(int hp)
//{
//    if (this->m_hp != hp) {
//        this->m_hp = hp;
//        emit hp_changed();
//    }
//}

//int Player::hp() const
//{
//    return m_hp;
//}

//int Player::maxHp() const
//{
//    return m_maxHp;
//}

//void Player::setMaxHp(int maxHp)
//{
//    if (this->m_maxHp == maxHp)
//        return;
//    this->m_maxHp = maxHp;
//    if (m_hp > maxHp)
//        m_hp = maxHp;
//    emit hp_changed();
//}

//int Player::lostHp() const
//{
//    return m_maxHp - qMax(m_hp, 0);
//}

//bool Player::isWounded() const
//{
//    if (m_hp < 0)
//        return true;
//    else
//        return m_hp < m_maxHp;
//}

//QSgsEnum::GeneralGender Player::gender() const
//{
//    return m_gender;
//}

//void Player::setGender(QSgsEnum::GeneralGender gender)
//{
//    m_gender = gender;
//}

//bool Player::isMale() const
//{
//    return m_gender == QSgsEnum::GeneralGender::Male;
//}

//bool Player::isFemale() const
//{
//    return m_gender == QSgsEnum::GeneralGender::Female;
//}

//bool Player::isNeuter() const
//{
//    return m_gender == QSgsEnum::GeneralGender::Neuter;
//}

//int Player::seat() const
//{
//    return m_seat;
//}

//void Player::setSeat(int seat)
//{
//    this->m_seat = seat;
//}

//void Player::setDisableShow(const QString &flags, const QString &reason)
//{
//    if (flags.contains('h')) {
//        if (disableShow(true).contains(reason))
//            return;
//    }
//    if (flags.contains('d')) {
//        if (disableShow(false).contains(reason))
//            return;
//    }

//    QString dis_str = flags + ',' + reason;
//    m_disableShow << dis_str;
//    emit disable_show_changed();
//}

//void Player::removeDisableShow(const QString &reason)
//{
//    QStringList remove_list;
//    foreach (const QString &dis_str, m_disableShow) {
//        QString dis_reason = dis_str.split(',').at(1);
//        if (dis_reason == reason)
//            remove_list << dis_str;
//    }

//    if (remove_list.isEmpty()) return;

//    foreach (const QString &to_remove, remove_list)
//        m_disableShow.removeOne(to_remove);

//    emit disable_show_changed();
//}

//QStringList Player::disableShow(bool head) const
//{
//    QChar head_flag = 'h';
//    if (!head)
//        head_flag = 'd';

//    QStringList r;
//    foreach (const QString &dis_str, m_disableShow) {
//        QStringList dis_list = dis_str.split(',');
//        if (dis_list.at(0).contains(head_flag))
//            r << dis_list.at(1);
//    }

//    return r;
//}


//bool Player::isAdjacentTo(const Player *another) const
//{
//    return nextAlive() == another
//        || another->nextAlive() == this;
//}

//bool Player::isAlive() const
//{
//    return m_alive;
//}

//bool Player::isDead() const
//{
//    return !m_alive;
//}

//void Player::setAlive(bool alive)
//{
//    this->m_alive = alive;
//}

//QString Player::flags() const
//{
//    return QStringList(m_flags.toList()).join("|");
//}

//QStringList Player::flagList() const
//{
//    return QStringList(m_flags.toList());
//}

//void Player::setFlags(const QString &flag)
//{
//    if (flag == ".") {
//        clearFlags();
//        return;
//    }
//    static QChar unset_symbol('-');
//    if (flag.startsWith(unset_symbol)) {
//        QString copy = flag;
//        copy.remove(unset_symbol);
//        m_flags.remove(copy);
//    } else {
//        m_flags.insert(flag);
//    }
//}

//bool Player::hasFlag(const QString &flag) const
//{
//    return m_flags.contains(flag);
//}

//void Player::clearFlags()
//{
//    m_flags.clear();
//}

//int Player::attackRange(bool include_weapon) const
//{
//    if (hasFlag("InfinityAttackRange") || mark("InfinityAttackRange") > 0)
//        return 1000;

//    include_weapon = include_weapon && m_weapon != nullptr;

//    int fixeddis = Sanguosha->correctAttackRange(this, include_weapon, true);
//    if (fixeddis > 0)
//        return fixeddis;

//    int original_range = 1, weapon_range = 0;

//    if (include_weapon) {
//        const Weapon *card = qobject_cast<const Weapon *>(m_weapon->getRealCard());
//        Q_ASSERT(card);
//        weapon_range = card->getRange();
//    }

//    int real_range = qMax(original_range, weapon_range) + Sanguosha->correctAttackRange(this, include_weapon, false);

//    if (real_range < 0)
//        real_range = 0;

//    return real_range;
//}

//bool Player::inMyAttackRange(const Player *other) const
//{
//    if (distanceTo(other) == -1)
//        return false;
//    QStringList in_attack_range_players = property("in_my_attack_range").toString().split("+");
//    if (in_attack_range_players.contains(other->objectName())) // for DIY Skills
//        return true;
//    return distanceTo(other) <= attackRange();
//}

//void Player::setFixedDistance(const Player *player, int distance)
//{
//    if (distance == -1)
//        m_fixedDistance.remove(player);
//    else
//        m_fixedDistance.insert(player, distance);
//}

//int Player::originalRightDistanceTo(const Player *other) const
//{
//    int right = 0;
//    Player *next_p = parent()->findChild<Player *>(objectName());
//    while (next_p != other) {
//        next_p = next_p->nextAlive();
//        right++;
//    }
//    return right;
//}

//int Player::distanceTo(const Player *other, int distance_fix) const
//{
//    if (this == other || isDead() || other->isDead())
//        return 0;

//    if (isRemoved() || other->isRemoved())
//        return -1;

//    if (m_fixedDistance.contains(other))
//        return m_fixedDistance.value(other);

//    int right = originalRightDistanceTo(other);
//    int left = aliveCount(false) - right;
//    int distance = qMin(left, right);

//    distance += Sanguosha->correctDistance(this, other);
//    distance += distance_fix;

//    // keep the distance >=1
//    if (distance < 1)
//        distance = 1;

//    return distance;
//}

//void Player::setGeneral(const General *new_general)
//{
//    if (this->m_general != new_general) {
//        this->m_general = new_general;

//        if (new_general && m_kingdom.isEmpty())
//            setKingdom(new_general->getKingdom());

//        emit general_changed();
//    }
//}

//void Player::setGeneralName(const QString &general_name)
//{
//    const General *new_general = Sanguosha->getGeneral(general_name);
//    Q_ASSERT(general_name.isnullptr() || general_name.isEmpty() || new_general != nullptr);
//    setGeneral(new_general);
//}

//QString Player::generalName() const
//{
//    if (m_general)
//        return m_general->objectName();
//    else
//        return QString();
//}

//void Player::setGeneral2Name(const QString &general_name)
//{
//    const General *new_general = Sanguosha->getGeneral(general_name);
//    if (m_general2 != new_general) {
//        m_general2 = new_general;

//        emit general2_changed();
//    }
//}

//QString Player::general2Name() const
//{
//    if (m_general2)
//        return m_general2->objectName();
//    else
//        return QString();
//}

//const General *Player::general2() const
//{
//    return m_general2;
//}

//QString Player::footnoteName() const
//{
//    if (m_general && m_general->objectName() != "anjiang" && !m_general->objectName().contains("sujiang"))
//        return m_general->objectName();
//    else if (m_general2 && m_general2->objectName() != "anjiang" && !m_general2->objectName().contains("sujiang"))
//        return m_general2->objectName();
//    else if (property("UI_Seat").toInt())
//        //return Sanguosha->translate(QString("SEAT(%1)").arg(QString::number(property("UI_Seat").toInt())));
//        return QString();
//    else
//        return QString();
//}

//QString Player::state() const
//{
//    return m_state;
//}

//void Player::setState(const QString &state)
//{
//    if (this->m_state != state) {
//        this->m_state = state;
//        emit state_changed();
//    }
//}

//void Player::setRole(const QString &role)
//{
//    if (role.isEmpty()) return;
//    if (this->m_role != role) {
//        this->m_role = role;
//        emit role_changed(role);
//        if (role == "careerist")
//            emit kingdom_changed("careerist");
//        else
//            emit kingdom_changed(HegemonyMode::GetMappedKingdom(role));
//    }
//}

//QString Player::role() const
//{
//    return m_role;
//}

//Player::Role Player::roleEnum() const
//{
//    static QMap<QString, Role> role_map;
//    if (role_map.isEmpty()) {
//        role_map.insert("lord", Lord);
//        role_map.insert("loyalist", Loyalist);
//        role_map.insert("rebel", Rebel);
//        role_map.insert("renegade", Renegade);
//    }

//    return role_map.value(m_role);
//}

//const General *Player::avatarGeneral() const
//{
//    if (m_general)
//        return m_general;

//    QString general_name = property("avatar").toString();
//    if (general_name.isEmpty())
//        return nullptr;
//    return Sanguosha->getGeneral(general_name);
//}

//const General *Player::general() const
//{
//    return m_general;
//}

//bool Player::isLord() const
//{
//    return getLord() == this;
//}

//bool Player::hasSkill(const QString &skill_name, bool include_lose) const
//{
//    const TriggerSkill *trigger = Sanguosha->getTriggerSkill(skill_name);
//    if (trigger && trigger->isGlobal()) return true;

//    const Skill *skill = Sanguosha->getSkill(skill_name);
//    if (skill == nullptr)
//        return false;

//    if (!skill->isVisible()) {
//        const Skill *main_skill = Sanguosha->getMainSkill(skill_name);
//        if (main_skill != nullptr)
//            return hasSkill(main_skill);
//    }

//    if (!include_lose && !hasEquipSkill(skill_name) && !acquiredSkills().contains(skill_name) && ownSkill(skill_name) && !hasShownSkill(skill_name) && !disableShow(inHeadSkills(skill_name)).isEmpty())
//        return false;
//    QStringList InvalidSkill = property("invalid_skill_has").toString().split("+");
//    if (InvalidSkill.contains(skill_name))
//        return false;

//    return m_headSkills.value(skill_name, false)
//        || m_deputySkills.value(skill_name, false)
//        || m_headAcquiredSkills.contains(skill_name)
//        || m_deputyAcquiredSkills.contains(skill_name);
//}

//bool Player::hasSkill(const Skill *skill, bool include_lose) const
//{
//    return hasSkill(skill->objectName(), include_lose);
//}

//bool Player::hasSkills(const QString &skill_name, bool include_lose) const
//{
//    foreach (const QString &skill, skill_name.split("|")) {
//        bool checkpoint = true;
//        foreach (const QString &sk, skill.split("+")) {
//            if (!hasSkill(sk, include_lose)) {
//                checkpoint = false;
//                break;
//            }
//        }
//        if (checkpoint) return true;
//    }
//    return false;
//}

//bool Player::hasInnateSkill(const QString &skill_name) const
//{
//    if (m_general && m_general->hasSkill(skill_name))
//        return true;

//    if (m_general2 && m_general2->hasSkill(skill_name))
//        return true;

//    return false;
//}

//bool Player::hasLordSkill(const QString &skill_name, bool include_lose) const
//{
//    const Skill *skill = Sanguosha->getSkill(skill_name);

//    return skill && skill->isLordSkill() && isLord() && hasSkill(skill_name, include_lose);
//}

//void Player::acquireSkill(const QString &skill_name, bool head)
//{
//    QSet<QString> &skills = head ? m_headAcquiredSkills : m_deputyAcquiredSkills;
//    skills.insert(skill_name);
//}

//void Player::detachSkill(const QString &skill_name)
//{
//    m_headAcquiredSkills.remove(skill_name);
//    m_deputyAcquiredSkills.remove(skill_name);
//}

//void Player::detachAllSkills()
//{
//    m_headAcquiredSkills.clear();
//    m_deputyAcquiredSkills.clear();
//}

//void Player::addSkill(const QString &skill_name, bool head_skill)
//{
//    const Skill *skill = Sanguosha->getSkill(skill_name);
//    Q_ASSERT(skill);
//    if (head_skill)
//        m_headSkills[skill_name] = !skill->canPreshow() || m_general1Showed;
//    else
//        m_deputySkills[skill_name] = !skill->canPreshow() || m_general2Showed;
//}

//void Player::loseSkill(const QString &skill_name)
//{
//    m_headSkills.remove(skill_name);
//    m_deputySkills.remove(skill_name);
//}

//QString Player::phaseString() const
//{
//    switch (m_phase) {
//        case RoundStart: return "round_start";
//        case Start: return "start";
//        case Judge: return "judge";
//        case Draw: return "draw";
//        case Play: return "play";
//        case Discard: return "discard";
//        case Finish: return "finish";
//        case NotActive:
//        default:
//            return "not_active";
//    }
//}

//void Player::setPhaseString(const QString &phase_str)
//{
//    static QMap<QString, Phase> phase_map;
//    if (phase_map.isEmpty()) {
//        phase_map.insert("round_start", RoundStart);
//        phase_map.insert("start", Start);
//        phase_map.insert("judge", Judge);
//        phase_map.insert("draw", Draw);
//        phase_map.insert("play", Play);
//        phase_map.insert("discard", Discard);
//        phase_map.insert("finish", Finish);
//        phase_map.insert("not_active", NotActive);
//    }

//    setPhase(phase_map.value(phase_str, NotActive));
//}

//void Player::setEquip(Card *equip)
//{
//    const EquipCard *card = qobject_cast<const EquipCard *>(equip->getRealCard());
//    Q_ASSERT(card != nullptr);
//    switch (card->location()) {
//        case EquipCard::WeaponLocation: m_weapon = equip; break;
//        case EquipCard::ArmorLocation: m_armor = equip; break;
//        case EquipCard::DefensiveHorseLocation: m_defensiveHorse = equip; break;
//        case EquipCard::OffensiveHorseLocation: m_offensiveHorse = equip; break;
//        case EquipCard::TreasureLocation: m_treasure = equip; break;
//    }
//}

//void Player::removeEquip(Card *equip)
//{
//    const EquipCard *card = qobject_cast<const EquipCard *>(Sanguosha->getEngineCard(equip->getId()));
//    Q_ASSERT(card != nullptr);
//    switch (card->location()) {
//        case EquipCard::WeaponLocation: m_weapon = nullptr; break;
//        case EquipCard::ArmorLocation: m_armor = nullptr; break;
//        case EquipCard::DefensiveHorseLocation: m_defensiveHorse = nullptr; break;
//        case EquipCard::OffensiveHorseLocation: m_offensiveHorse = nullptr; break;
//        case EquipCard::TreasureLocation: m_treasure = nullptr; break;
//    }
//}

//bool Player::hasEquip(Card *card) const
//{
//    Q_ASSERT(card != nullptr);
//    int weapon_id = -1, armor_id = -1, def_id = -1, off_id = -1, tr_id = -1;
//    if (m_weapon) weapon_id = m_weapon->getEffectiveId();
//    if (m_armor) armor_id = m_armor->getEffectiveId();
//    if (m_defensiveHorse) def_id = m_defensiveHorse->getEffectiveId();
//    if (m_offensiveHorse) off_id = m_offensiveHorse->getEffectiveId();
//    if (m_treasure) tr_id = m_treasure->getEffectiveId();
//    QList<int> ids;
//    if (card->isVirtualCard())
//        ids << card->getSubcards();
//    else
//        ids << card->getId();
//    if (ids.isEmpty()) return false;
//    foreach (int id, ids) {
//        if (id != weapon_id && id != armor_id && id != def_id && id != off_id && id != tr_id)
//            return false;
//    }
//    return true;
//}

//bool Player::hasEquip() const
//{
//    return m_weapon != nullptr || m_armor != nullptr || m_defensiveHorse != nullptr || m_offensiveHorse != nullptr || m_treasure != nullptr;
//}

//Card *Player::weapon() const
//{
//    return m_weapon;
//}

//Card *Player::armor() const
//{
//    return m_armor;
//}

//Card *Player::defensiveHorse() const
//{
//    return m_defensiveHorse;
//}

//Card *Player::offensiveHorse() const
//{
//    return m_offensiveHorse;
//}

//Card *Player::treasure() const
//{
//    return m_treasure;
//}

//QList<Card *> Player::equips() const
//{
//    QList<Card *> equips;
//    if (m_weapon)
//        equips << m_weapon;
//    if (m_armor)
//        equips << m_armor;
//    if (m_defensiveHorse)
//        equips << m_defensiveHorse;
//    if (m_offensiveHorse)
//        equips << m_offensiveHorse;
//    if (m_treasure)
//        equips << m_treasure;

//    return equips;
//}

//Card *Player::equip(int index) const
//{
//    Card *equip;
//    switch (index) {
//        case 0: equip = m_weapon; break;
//        case 1: equip = m_armor; break;
//        case 2: equip = m_defensiveHorse; break;
//        case 3: equip = m_offensiveHorse; break;
//        case 4: equip = m_treasure; break;
//        default:
//            return nullptr;
//    }
//    if (equip != nullptr)
//        return qobject_cast<const EquipCard *>(equip->getRealCard());

//    return nullptr;
//}

//bool Player::hasWeapon(const QString &weapon_name) const
//{
//    if (!m_weapon || mark("Equips_nullptrified_to_Yourself") > 0) return false;
//    if (m_weapon->objectName() == weapon_name || m_weapon->isKindOf(weapon_name.toStdString().c_str())) return true;
//    Card *real_weapon = Sanguosha->getEngineCard(m_weapon->getEffectiveId());
//    return real_weapon->objectName() == weapon_name || real_weapon->isKindOf(weapon_name.toStdString().c_str());
//}

//bool Player::hasArmorEffect(const QString &armor_name) const
//{
//    if (!tag["Qinggang"].toStringList().isEmpty() || mark("Armor_nullptrified") > 0
//        || mark("Equips_nullptrified_to_Yourself") > 0)
//        return false;
//    if (armor_name == "bazhen")
//        return m_armor == nullptr && m_alive && (hasSkill("bazhen") || hasSkill("linglong"));
//    else {
//        if (!m_armor) return false;
//        if (m_armor->objectName() == armor_name || m_armor->isKindOf(armor_name.toStdString().c_str())) return true;
//        Card *real_armor = Sanguosha->getEngineCard(m_armor->getEffectiveId());
//        return real_armor->objectName() == armor_name || real_armor->isKindOf(armor_name.toStdString().c_str());
//    }
//    return false;
//}

//bool Player::hasTreasure(const QString &treasure_name) const
//{
//    if (!m_treasure || mark("Equips_nullptrified_to_Yourself") > 0) return false;
//    if (m_treasure->objectName() == treasure_name || m_treasure->isKindOf(treasure_name.toStdString().c_str())) return true;
//    Card *real_treasure = Sanguosha->getEngineCard(m_treasure->getEffectiveId());
//    return real_treasure->objectName() == treasure_name || real_treasure->isKindOf(treasure_name.toStdString().c_str());
//}

//QList<Card *> Player::judgingArea() const
//{
//    QList<Card *>cards;
//    foreach(int card_id, m_judgingArea)
//        cards.append(Sanguosha->getCard(card_id));
//    return cards;
//}

//QList<int> Player::judgingAreaID() const
//{ //for marshal
//    return m_judgingArea;
//}

//Player::Phase Player::phase() const
//{
//    return m_phase;
//}

//void Player::setPhase(Phase phase)
//{
//    this->m_phase = phase;
//    emit phase_changed();
//}

//bool Player::faceUp() const
//{
//    return m_faceUp;
//}

//void Player::setFaceUp(bool face_up)
//{
//    if (this->m_faceUp != face_up) {
//        this->m_faceUp = face_up;
//        emit state_changed();
//    }
//}

//QString Player::kingdom() const
//{
//    if (m_kingdom.isEmpty() && m_general)
//        return m_general->getKingdom();
//    else
//        return m_kingdom;
//}

//void Player::setKingdom(const QString &kingdom)
//{
//    if (this->m_kingdom != kingdom) {
//        this->m_kingdom = kingdom;
//        if (m_role == "careerist") return;
//        emit kingdom_changed(kingdom);
//    }
//}

//bool Player::isKongcheng() const
//{
//    return handcardNum() == 0;
//}

//bool Player::isNude() const
//{
//    return isKongcheng() && !hasEquip();
//}

//bool Player::isAllNude() const
//{
//    return isNude() && m_judgingArea.isEmpty();
//}

//bool Player::canDiscard(const Player *to, const QString &flags) const
//{
//    static QChar handcard_flag('h');
//    static QChar equip_flag('e');
//    static QChar judging_flag('j');

//    if (flags.contains(handcard_flag) && !to->isKongcheng()) return true;
//    if (flags.contains(judging_flag) && !to->judgingArea().isEmpty()) return true;
//    if (flags.contains(equip_flag) && to->hasEquip()) return true;
//    return false;
//}

//bool Player::canDiscard(const Player *to, int card_id) const
//{
//    if (this == to) {
//        if (isJilei(Sanguosha->getCard(card_id)))
//            return false;
//    }
//    return true;
//}

//void Player::addDelayedTrick(Card *trick)
//{
//    m_judgingArea << trick->getId();
//}

//void Player::removeDelayedTrick(Card *trick)
//{
//    int index = m_judgingArea.indexOf(trick->getId());
//    if (index >= 0)
//        m_judgingArea.removeAt(index);
//}

//bool Player::containsTrick(const QString &trick_name) const
//{
//    foreach (int trick_id, m_judgingArea) {
//        Card *trick = Sanguosha->getCard(trick_id);
//        if (trick->objectName() == trick_name)
//            return true;
//    }
//    return false;
//}

//bool Player::isChained() const
//{
//    return m_chained;
//}

//void Player::setChained(bool chained)
//{
//    if (this->m_chained != chained) {
//        Sanguosha->playSystemAudioEffect("chained");
//        this->m_chained = chained;
//        emit state_changed();
//    }
//}

//bool Player::canBeChainedBy(const Player *_source) const
//{
//    const Player *source = _source ? _source : this;
//    if (isChained()) {
//        return true;
//    } else {
//        if (hasArmorEffect("IronArmor")) {
//            QStringList big_kingdoms = source->getBigKingdoms("IronArmor", MaxCardsType::Normal);
//            if (!big_kingdoms.isEmpty()) {
//                QString kingdom;
//                if (!hasShownOneGeneral())
//                    return false;
//                if (role() == "careerist")
//                    kingdom = objectName();
//                else
//                    kingdom = kingdom();
//                if (!big_kingdoms.contains(kingdom))
//                    return false;
//            }
//        }
//        return true;
//    }
//}

//bool Player::isRemoved() const
//{
//    return m_removed;
//}

//void Player::setRemoved(bool removed)
//{
//    if (this->m_removed != removed) {
//        this->m_removed = removed;
//        emit removedChanged();
//    }
//}

//bool Player::isDuanchang(const bool head) const
//{
//    if (head && property("Duanchang").toString().split(",").contains("head"))
//        return true;
//    else if (!head && property("Duanchang").toString().split(",").contains("deputy"))
//        return true;
//    else
//        return false;
//}

//void Player::addMark(const QString &mark, int add_num)
//{
//    int value = m_marks.value(mark, 0);
//    value += add_num;
//    setMark(mark, value);
//}

//void Player::removeMark(const QString &mark, int remove_num)
//{
//    int value = m_marks.value(mark, 0);
//    value -= remove_num;
//    value = qMax(0, value);
//    setMark(mark, value);
//}

//void Player::setMark(const QString &mark, int value)
//{
//    if (m_marks[mark] != value)
//        m_marks[mark] = value;
//}

//int Player::mark(const QString &mark) const
//{
//    return m_marks.value(mark, 0);
//}

//bool Player::canSlash(const Player *other, Card *slash, bool distance_limit,
//    int rangefix, const QList<const Player *> &others) const
//{
//    if (other == this || !other->isAlive())
//        return false;

//    Slash *newslash = new Slash(Card::NoSuit, 0);
//    newslash->deleteLater();

//    if (isProhibited(other, slash == nullptr ? newslash : slash, others))
//        return false;

//    int distance = distanceTo(other, rangefix);
//    if (distance == -1)
//        return false;

//    if (distance_limit)
//        return distance <= attackRange() + Sanguosha->correctCardTarget(TargetModSkill::DistanceLimit, this, slash == nullptr ? newslash : slash);
//    else
//        return true;
//}

//bool Player::canSlash(const Player *other, bool distance_limit, int rangefix, const QList<const Player *> &others) const
//{
//    return canSlash(other, nullptr, distance_limit, rangefix, others);
//}

//int Player::getCardCount(bool include_equip) const
//{
//    int count = handcardNum();
//    if (include_equip) {
//        if (m_weapon != nullptr) count++;
//        if (m_armor != nullptr) count++;
//        if (m_defensiveHorse != nullptr) count++;
//        if (m_offensiveHorse != nullptr) count++;
//        if (m_treasure != nullptr) count++;
//    }
//    return count;
//}

//QList<int> Player::getPile(const QString &pile_name) const
//{
//    return m_piles[pile_name];
//}

//QStringList Player::pileNames() const
//{
//    QStringList names;
//    foreach(const QString &pile_name, m_piles.keys())
//        names.append(pile_name);
//    return names;
//}

//QString Player::pileName(int card_id) const
//{
//    foreach (const QString &pile_name, m_piles.keys()) {
//        QList<int> pile = m_piles[pile_name];
//        if (pile.contains(card_id))
//            return pile_name;
//    }

//    return QString();
//}

//QList<int> Player::handPile() const
//{
//    QList<int> result;
//    foreach (const QString &pile, handPileList(false)) {
//        foreach(int id, getPile(pile))
//            result.append(id);
//    }
//    return result;
//}

//QStringList Player::handPileList(bool view_as_skill) const
//{
//    QStringList handlist;
//    if (view_as_skill)
//        handlist.append("hand");
//    foreach (const QString &pile, this->pileNames()) {
//        if (pile.startsWith("&") || pile == "wooden_ox" || pile.startsWith("^"))
//            handlist.append(pile);
//    }
//    return handlist;
//}

//bool Player::pileOpen(const QString &pile_name, const QString &player) const
//{
//    return m_pileOpen[pile_name].contains(player);
//}

//void Player::setPileOpen(const QString &pile_name, const QString &player)
//{
//    if (m_pileOpen[pile_name].contains(player)) return;
//    m_pileOpen[pile_name].append(player);
//}

//void Player::addHistory(const QString &name, int times)
//{
//    m_history[name] += times;
//}

//int Player::slashCount() const
//{
//    return m_history.value("Slash", 0)
//        + m_history.value("ThunderSlash", 0)
//        + m_history.value("FireSlash", 0);
//}

//void Player::clearHistory(const QString &name)
//{
//    if (name.isEmpty())
//        m_history.clear();
//    else
//        m_history.remove(name);
//}

//bool Player::hasUsed(const QString &card_class) const
//{
//    return m_history.value(card_class, 0) > 0;
//}

//int Player::usedTimes(const QString &card_class) const
//{
//    return m_history.value(card_class, 0);
//}

//bool Player::hasEquipSkill(const QString &skill_name) const
//{
//    if (m_weapon) {
//        const Weapon *weaponc = qobject_cast<const Weapon *>(m_weapon->getRealCard());
//        if (Sanguosha->getSkill(weaponc) && Sanguosha->getSkill(weaponc)->objectName() == skill_name)
//            return true;
//    }
//    if (m_armor) {
//        const Armor *armorc = qobject_cast<const Armor *>(m_armor->getRealCard());
//        if (Sanguosha->getSkill(armorc) && Sanguosha->getSkill(armorc)->objectName() == skill_name)
//            return true;
//    }
//    if (m_treasure) {
//        const Treasure *treasurec = qobject_cast<const Treasure *>(m_treasure->getRealCard());
//        if (Sanguosha->getSkill(treasurec) && Sanguosha->getSkill(treasurec)->objectName() == skill_name)
//            return true;
//    }
//    return false;
//}

//QSet<const TriggerSkill *> Player::triggerSkills() const
//{
//    QSet<const TriggerSkill *> skillList;
//    const QList<QString> skills = m_headSkills.keys() + m_deputySkills.keys() + m_headAcquiredSkills.toList() + m_deputyAcquiredSkills.toList();

//    foreach (const QString &skill_name, skills) {
//        const TriggerSkill *skill = Sanguosha->getTriggerSkill(skill_name);
//        if (skill && !hasEquipSkill(skill->objectName()))
//            skillList << skill;
//    }

//    return skillList;
//}

//QSet<const Skill *> Player::skills(bool include_equip, bool visible_only) const
//{
//    return skillList(include_equip, visible_only).toSet();
//}

//QList<const Skill *> Player::skillList(bool include_equip, bool visible_only) const
//{
//    QList<const Skill *> skillList;
//    const QList<QString> skills = m_headSkills.keys() + m_deputySkills.keys() + m_headAcquiredSkills.toList() + m_deputyAcquiredSkills.toList();

//    foreach (const QString &skill_name, skills) {
//        const Skill *skill = Sanguosha->getSkill(skill_name);
//        if (skill != nullptr) {
//            if ((include_equip || !hasEquipSkill(skill->objectName())) && (!visible_only || skill->isVisible()))
//                skillList << skill;
//            if (skill->isVisible() && !visible_only) {
//                QList<const Skill *> related_skill = Sanguosha->getRelatedSkills(skill->objectName());
//                foreach (const Skill *s, related_skill) {
//                    if (!skillList.contains(s) && !s->isVisible())
//                        skillList << s;
//                }
//            }
//        }
//    }

//    return skillList;
//}

//QList<const Skill *> Player::headSkillList(bool visible_only) const
//{
//    QList<const Skill *> skillList;

//    foreach (const QString &skill_name, m_headSkills.keys()) {
//        const Skill *skill = Sanguosha->getSkill(skill_name);
//        if (skill
//            && (!hasEquipSkill(skill->objectName()))
//            && (!visible_only || skill->isVisible()))
//            skillList << skill;
//    }

//    return skillList;
//}

//QList<const Skill *> Player::deputySkillList(bool visible_only) const
//{
//    QList<const Skill *> skillList;

//    foreach (const QString &skill_name, m_deputySkills.keys()) {
//        const Skill *skill = Sanguosha->getSkill(skill_name);
//        if (skill
//            && (!hasEquipSkill(skill->objectName()))
//            && (!visible_only || skill->isVisible()))
//            skillList << skill;
//    }

//    return skillList;
//}

//QSet<const Skill *> Player::visibleSkills(bool include_equip) const
//{
//    return visibleSkillList(include_equip).toSet();
//}

//QList<const Skill *> Player::visibleSkillList(bool include_equip) const
//{
//    return skillList(include_equip, true);
//}

//QSet<QString> Player::acquiredSkills() const
//{
//    return m_headAcquiredSkills + m_deputyAcquiredSkills;
//}

//QStringList Player::acquiredSkills(const QString &flags) const
//{
//    if (flags == "all")
//        return acquiredSkills().toList();
//    if (flags == "head")
//        return m_headAcquiredSkills.toList();
//    if (flags == "deputy")
//        return m_deputyAcquiredSkills.toList();
//    return QStringList();
//}

//QString Player::skillDescription(bool inToolTip) const
//{
//    QString description = QString();
//    QString color = inToolTip ? Config.SkillDescriptionInToolTipColor.name() : Config.SkillDescriptionInOverviewColor.name();

//    foreach (const Skill *skill, visibleSkillList()) {
//        QString skill_name = Sanguosha->translate(skill->objectName());
//        QString desc = skill->getDescription(inToolTip);
//        desc.replace("\n", "<br/>");
//        description.append(QString("<font color=%1><b>%2</b>:</font> %3 <br/> <br/>").arg(color).arg(skill_name).arg(desc));
//    }

//    if (description.isEmpty()) description = tr("<font color=%1>No skills</font>").arg(color);
//    return description;
//}

//QString Player::headSkillDescription() const
//{
//    QString description = QString();

//    foreach (const Skill *skill, visibleSkillList()) {
//        if (!inHeadSkills(skill->objectName())) continue;
//        QString skill_name = Sanguosha->translate(skill->objectName());
//        QString desc = skill->getDescription();
//        desc.replace("\n", "<br/>");
//        description.append(QString("<font color=%1><b>%2</b>:</font> %3 <br/> <br/>").arg(Config.SkillDescriptionInToolTipColor.name()).arg(skill_name).arg(desc));
//    }
//    return description;
//}

//QString Player::deputySkillDescription() const
//{
//    QString description = QString();
//    foreach (const Skill *skill, visibleSkillList()) {
//        if (inHeadSkills(skill->objectName())) continue;
//        QString skill_name = Sanguosha->translate(skill->objectName());
//        QString desc = skill->getDescription();
//        desc.replace("\n", "<br/>");
//        description.append(QString("<font color=%1><b>%2</b>:</font> %3 <br/> <br/>").arg(Config.SkillDescriptionInToolTipColor.name()).arg(skill_name).arg(desc));
//    }
//    return description;
//}


//bool Player::isProhibited(const Player *to, Card *card, const QList<const Player *> &others) const
//{
//    return Sanguosha->isProhibited(this, to, card, others);
//}

//bool Player::canSlashWithoutCrossbow(Card *slash) const
//{
//    Slash *newslash = new Slash(Card::NoSuit, 0);
//    newslash->deleteLater();
//#define THIS_SLASH (slash == nullptr ? newslash : slash)
//    int slash_count = slashCount();
//    int valid_slash_count = 1;
//    valid_slash_count += Sanguosha->correctCardTarget(TargetModSkill::Residue, this, THIS_SLASH);
//    return slash_count < valid_slash_count;
//#undef THIS_SLASH
//}

//void Player::setCardLimitation(const QString &limit_list, const QString &pattern, bool single_turn)
//{
//    QStringList limit_type = limit_list.split(",");
//    QString _pattern = pattern;
//    if (!pattern.endsWith("$1") && !pattern.endsWith("$0")) {
//        QString symb = single_turn ? "$1" : "$0";
//        _pattern = _pattern + symb;
//    }
//    foreach (const QString &limit, limit_type) {
//        Card::HandlingMethod method = Sanguosha->getCardHandlingMethod(limit);
//        m_cardLimitation[method] << _pattern;
//    }
//}

//void Player::removeCardLimitation(const QString &limit_list, const QString &pattern)
//{
//    QStringList limit_type = limit_list.split(",");
//    QString _pattern = pattern;
//    if (!_pattern.endsWith("$1") && !_pattern.endsWith("$0"))
//        _pattern = _pattern + "$0";
//    foreach (const QString &limit, limit_type) {
//        Card::HandlingMethod method = Sanguosha->getCardHandlingMethod(limit);
//        m_cardLimitation[method].removeOne(_pattern);
//    }
//}

//void Player::clearCardLimitation(bool single_turn)
//{
//    QList<Card::HandlingMethod> limit_type;
//    limit_type << Card::MethodUse << Card::MethodResponse << Card::MethodDiscard
//        << Card::MethodRecast << Card::MethodPindian;
//    foreach (const Card::HandlingMethod &method, limit_type) {
//        QStringList limit_patterns = m_cardLimitation[method];
//        foreach (const QString &pattern, limit_patterns) {
//            if (!single_turn || pattern.endsWith("$1"))
//                m_cardLimitation[method].removeAll(pattern);
//        }
//    }
//}

//bool Player::isCardLimited(Card *card, Card::HandlingMethod method, bool isHandcard) const
//{
//    if (method == Card::MethodNone)
//        return false;
//    if (card->getTypeId() == Card::TypeSkill && method == card->getHandlingMethod()) {
//        foreach (int card_id, card->getSubcards()) {
//            Card *c = Sanguosha->getCard(card_id);
//            foreach (const QString &pattern, m_cardLimitation[method]) {
//                QString _pattern = pattern.split("$").first();
//                if (isHandcard)
//                    _pattern.replace("hand", ".");
//                ExpPattern p(_pattern);
//                if (p.match(this, c)) return true;
//            }
//        }
//    } else {
//        foreach (const QString &pattern, m_cardLimitation[method]) {
//            QString _pattern = pattern.split("$").first();
//            if (isHandcard)
//                _pattern.replace("hand", ".");
//            ExpPattern p(_pattern);
//            if (p.match(this, card)) return true;
//        }
//    }

//    return false;
//}

//void Player::addQinggangTag(Card *card)
//{
//    QStringList qinggang = this->tag["Qinggang"].toStringList();
//    QString card_string = card->toString();
//    if (!qinggang.contains(card_string))
//        qinggang << card_string;
//    this->tag["Qinggang"] = QVariant::fromValue(qinggang);
//}

//void Player::removeQinggangTag(Card *card)
//{
//    QStringList qinggang = this->tag["Qinggang"].toStringList();
//    if (!qinggang.isEmpty()) {
//        qinggang.removeOne(card->toString());
//        this->tag["Qinggang"] = qinggang;
//    }
//}

//const Player *Player::getLord(bool include_death) const
//{
//    if (actualGeneral1() && actualGeneral1()->isLord())
//        return this;
//    QList<const Player *> sib = include_death ? getSiblings() : getAliveSiblings();
//    sib << this;
//    foreach (const Player *p, sib) {
//        if (p->general() && p->general()->isLord() && p->kingdom() == m_kingdom)
//            return p;
//    }

//    return nullptr;
//}

//void Player::copyFrom(Player *p)
//{
//    Player *b = this;
//    Player *a = p;

//    b->m_marks = QMap<QString, int>(a->m_marks);
//    b->m_piles = QMap<QString, QList<int> >(a->m_piles);
//    b->m_headAcquiredSkills = QSet<QString>(a->m_headAcquiredSkills);
//    b->m_deputyAcquiredSkills = QSet<QString>(a->m_deputyAcquiredSkills);
//    b->m_flags = QSet<QString>(a->m_flags);
//    b->m_history = QHash<QString, int>(a->m_history);
//    b->m_gender = a->m_gender;

//    b->m_hp = a->m_hp;
//    b->m_maxHp = a->m_maxHp;
//    b->m_kingdom = a->m_kingdom;
//    b->m_role = a->m_role;
//    b->m_seat = a->m_seat;
//    b->m_alive = a->m_alive;

//    b->m_phase = a->m_phase;
//    b->m_weapon = a->m_weapon;
//    b->m_armor = a->m_armor;
//    b->m_defensiveHorse = a->m_defensiveHorse;
//    b->m_offensiveHorse = a->m_offensiveHorse;
//    b->m_treasure = a->m_treasure;
//    b->m_faceUp = a->m_faceUp;
//    b->m_chained = a->m_chained;
//    b->m_judgingArea = QList<int>(a->m_judgingArea);
//    b->m_fixedDistance = QHash<const Player *, int>(a->m_fixedDistance);
//    b->m_cardLimitation = QMap<Card::HandlingMethod, QStringList>(a->m_cardLimitation);

//    b->tag = QVariantMap(a->tag);
//}

//QList<const Player *> Player::getSiblings() const
//{
//    QList<const Player *> siblings;
//    if (parent()) {
//        siblings = parent()->findChildren<const Player *>();
//        siblings.removeOne(this);
//    }
//    return siblings;
//}

//QList<const Player *> Player::getAliveSiblings() const
//{
//    QList<const Player *> siblings = getSiblings();
//    foreach (const Player *p, siblings) {
//        if (!p->isAlive())
//            siblings.removeOne(p);
//    }
//    return siblings;
//}

//bool Player::hasShownSkill(const Skill *skill) const
//{
//    if (skill == nullptr)
//        return false;
//    QStringList InvalidSkill = property("invalid_skill_shown").toString().split("+");
//    if (InvalidSkill.contains(skill->objectName())) return false;

//    if (m_headAcquiredSkills.contains(skill->objectName()) || m_deputyAcquiredSkills.contains(skill->objectName()))
//        return true;

//    if (skill->inherits("ArmorSkill") || skill->inherits("WeaponSkill") || skill->inherits("TreasureSkill"))
//        return true;

//    if (skill->inherits("TriggerSkill")) {
//        const TriggerSkill *tr_skill = qobject_cast<const TriggerSkill *>(skill);
//        if (tr_skill && tr_skill->isGlobal())
//            return true;
//    }

//    if (!skill->isVisible()) {
//        const Skill *main_skill = Sanguosha->getMainSkill(skill->objectName());
//        if (main_skill != nullptr)
//            return hasShownSkill(main_skill);
//        else
//            return false;
//    }

//    if (m_general1Showed && m_headSkills.contains(skill->objectName()))
//        return true;
//    else if (m_general2Showed && m_deputySkills.contains(skill->objectName()))
//        return true;
//    return false;
//}

//bool Player::hasShownSkill(const QString &skill_name) const
//{
//    const Skill *skill = Sanguosha->getSkill(skill_name);
//    if (skill == nullptr) {
//        QObject *roomObject = Sanguosha->currentRoomObject();
//        if (roomObject != nullptr && roomObject->inherits("RoomObject")) {
//            RoomObject *room = Sanguosha->currentRoom();
//            room->output("no such skill " + skill_name);
//            qWarning("%s", QString("no such skill " + skill_name).toStdString().c_str());
//        }
//        return false;
//    }
//    return hasShownSkill(skill);
//}

//bool Player::hasShownSkills(const QString &skill_name) const
//{
//    foreach (const QString &skill, skill_name.split("|")) {
//        bool checkpoint = true;
//        foreach (const QString &sk, skill.split("+")) {
//            if (!hasShownSkill(sk)) {
//                checkpoint = false;
//                break;
//            }
//        }
//        if (checkpoint) return true;
//    }
//    return false;
//}

//void Player::preshowSkill(const QString &skill_name)
//{
//    if (hasShownSkill(skill_name))
//        return;

//    if (m_headSkills.contains(skill_name))
//        m_headSkills[skill_name] = !m_headSkills.value(skill_name);
//    if (m_deputySkills.contains(skill_name))
//        m_deputySkills[skill_name] = !m_deputySkills.value(skill_name);
//}

//bool Player::inHeadSkills(const QString &skill_name) const
//{
//    return m_headSkills.contains(skill_name) || m_headAcquiredSkills.contains(skill_name);
//}

//bool Player::inHeadSkills(const Skill *skill) const
//{
//    if (skill == nullptr)
//        return false;

//    return inHeadSkills(skill->objectName());
//}

//bool Player::inDeputySkills(const QString &skill_name) const
//{
//    return m_deputySkills.contains(skill_name) || m_deputyAcquiredSkills.contains(skill_name);
//}

//bool Player::inDeputySkills(const Skill *skill) const
//{
//    if (skill == nullptr)
//        return false;

//    return inDeputySkills(skill->objectName());
//}

//const General *Player::actualGeneral1() const
//{
//    return m_actualGeneral1;
//}

//const General *Player::actualGeneral2() const
//{
//    return m_actualGeneral2;
//}

//QString Player::actualGeneral1Name() const
//{
//    if (m_actualGeneral1)
//        return m_actualGeneral1->objectName();
//    else
//        return QString();
//}

//QString Player::actualGeneral2Name() const
//{
//    if (m_actualGeneral2)
//        return m_actualGeneral2->objectName();
//    else
//        return QString();
//}

//void Player::setActualGeneral1(const General *general)
//{
//    m_actualGeneral1 = general;
//}

//void Player::setActualGeneral2(const General *general)
//{
//    m_actualGeneral2 = general;
//}

//void Player::setActualGeneral1Name(const QString &name)
//{
//    const General *general = Sanguosha->getGeneral(name);
//    Q_ASSERT(!(name.isnullptr() || name.isEmpty() || general == nullptr));
//    setActualGeneral1(general);
//}

//void Player::setActualGeneral2Name(const QString &name)
//{
//    const General *general = Sanguosha->getGeneral(name);
//    Q_ASSERT(!(name.isnullptr() || name.isEmpty() || general == nullptr));
//    setActualGeneral2(general);
//}

//bool Player::hasShownGeneral1() const
//{
//    return m_general1Showed;
//}

//bool Player::hasShownGeneral2() const
//{
//    return m_general2Showed;
//}

//bool Player::hasShownOneGeneral() const
//{
//    return m_scenarioRoleShown || m_general1Showed || (m_general2 && m_general2Showed);
//}

//bool Player::hasShownAllGenerals() const
//{
//    return m_general1Showed && (!m_general2 || m_general2Showed);
//}

//void Player::setGeneral1Showed(bool showed)
//{
//    this->m_general1Showed = showed;
//    emit head_state_changed();
//}

//void Player::setGeneral2Showed(bool showed)
//{
//    this->m_general2Showed = showed;
//    emit deputy_state_changed();
//}

//void Player::setSkillPreshowed(const QString &skill, bool preshowed)
//{
//    if (m_headSkills.contains(skill))
//        m_headSkills[skill] = preshowed;
//    else if (m_deputySkills.contains(skill))
//        m_deputySkills[skill] = preshowed;
//}

//void Player::setSkillsPreshowed(const QString &flags, bool preshowed)
//{
//    if (flags.contains("h")) {
//        foreach (const QString &skill, m_headSkills.keys()) {
//            if (!Sanguosha->getSkill(skill)->canPreshow()) continue;
//            m_headSkills[skill] = preshowed;
//        }
//    }
//    if (flags.contains("d")) {
//        foreach (const QString &skill, m_deputySkills.keys()) {
//            if (!Sanguosha->getSkill(skill)->canPreshow()) continue;
//            m_deputySkills[skill] = preshowed;
//        }
//    }
//}

//bool Player::hasPreshowedSkill(const QString &name) const
//{
//    return m_headSkills.value(name, false) || m_deputySkills.value(name, false);
//}

//bool Player::hasPreshowedSkill(const Skill *skill) const
//{
//    return hasPreshowedSkill(skill->objectName());
//}

//bool Player::isHidden(const bool &head_general) const
//{
//    if (head_general ? m_general1Showed : m_general2Showed) return false;
//    const QList<const Skill *> skills = head_general ? headSkillList() : deputySkillList();
//    int count = 0;
//    foreach (const Skill *skill, skills) {
//        if (skill->canPreshow() && hasPreshowedSkill(skill->objectName()))
//            return false;
//        else if (!skill->canPreshow())
//            ++count;
//    }
//    return count != skills.length();
//}

//bool Player::ownSkill(const QString &skill_name) const
//{
//    return m_headSkills.contains(skill_name) || m_deputySkills.contains(skill_name);
//}

//bool Player::ownSkill(const Skill *skill) const
//{
//    return ownSkill(skill->objectName());
//}

//bool Player::isFriendWith(const Player *player) const
//{
//    Q_ASSERT(player);
//    if (player == nullptr)
//        return false;
//    if (!hasShownOneGeneral() || !player->hasShownOneGeneral())
//        return false;

//    if (this == player)
//        return true;

//    if (m_role == "careerist" || player->m_role == "careerist")
//        return false;

//    return m_kingdom == player->m_kingdom;
//}

//bool Player::willBeFriendWith(const Player *player) const
//{
//    if (this == player)
//        return true;
//    if (isFriendWith(player))
//        return true;
//    if (player == nullptr)
//        return false;
//    if (!player->hasShownOneGeneral())
//        return false;
//    if (!hasShownOneGeneral()) {
//        QString kingdom = actualGeneral1()->getKingdom();
//        int i = 1;
//        bool has_lord = isAlive() && isLord();

//        if (!has_lord) {
//            foreach (const Player *p, getSiblings()) {
//                if (p->kingdom() == kingdom) {
//                    if (p->isAlive() && p->isLord()) {
//                        has_lord = true;
//                        break;
//                    }
//                    if (p->hasShownOneGeneral() && p->role() != "careerist")
//                        ++i;
//                }
//            }
//        }

//        if (!has_lord && i > (parent()->findChildren<const Player *>().length() / 2))
//            return false;
//        else if (kingdom == player->kingdom())
//            return true;
//    }
//    return false;
//}

//void Player::setNext(Player *next)
//{
//    this->m_next = next->objectName();
//}

//void Player::setNext(const QString &next)
//{
//    this->m_next = next;
//}

//Player *Player::next(bool ignoreRemoved) const
//{
//    Player *next_p = parent()->findChild<Player *>(m_next);
//    if (ignoreRemoved && next_p->isRemoved())
//        return next_p->next(ignoreRemoved);
//    return next_p;
//}

//QString Player::nextName() const
//{
//    return m_next;
//}

//Player *Player::last(bool ignoreRemoved) const
//{
//    foreach (Player *p, parent()->findChildren<Player *>()) {
//        if (p->next(ignoreRemoved) == this)
//            return p;
//    }
//    return nullptr;
//}

//Player *Player::nextAlive(int n, bool ignoreRemoved) const
//{
//    bool hasAlive = (aliveCount(!ignoreRemoved) > 0);
//    Player *next = parent()->findChild<Player *>(objectName());
//    if (!hasAlive) return next;
//    for (int i = 0; i < n; ++i) {
//        do next = next->next(ignoreRemoved);
//        while (next->isDead());
//    }
//    return next;
//}

//Player *Player::lastAlive(int n, bool ignoreRemoved) const
//{
//    return nextAlive(aliveCount(!ignoreRemoved) - n, ignoreRemoved);
//}

//QList<const Player *> Player::formation() const
//{
//    QList<const Player *> teammates;
//    teammates << this;
//    int n = aliveCount(false);
//    int num = n;
//    for (int i = 1; i < n; ++i) {
//        Player *target = nextAlive(i);
//        if (isFriendWith(target))
//            teammates << target;
//        else {
//            num = i;
//            break;
//        }
//    }

//    n -= num;
//    for (int i = 1; i < n; ++i) {
//        Player *target = lastAlive(i);
//        if (isFriendWith(target))
//            teammates << target;
//        else break;
//    }

//    return teammates;
//}

//void Player::setHeadSkinId(int id)
//{
//    m_headSkinId = id;
//}

//int Player::getHeadSkinId() const
//{
//    return m_headSkinId;
//}

//void Player::setDeputySkinId(int id)
//{
//    m_deputySkinId = id;
//}

//int Player::getDeputySkinId() const
//{
//    return m_deputySkinId;
//}
