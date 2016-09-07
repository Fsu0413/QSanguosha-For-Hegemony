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

#include "card.h"
#include "structs.h"
#include "lua-wrapper.h"
#include "roomobject.h"


class CardPrivate
{
public:
    RoomObject *roomObject;
    const CardFace *cardFace;
    QList<Card *> subcards;
    bool mute;
    bool canRecast;
    bool transferable;
    QSgsEnum::CardSuit suit;
    int number;
    int id;
    QString skillName;
    QString showSkill;
    QStringList flags;
};

const int Card::S_UNKNOWN_CARD_ID = -1;

const QSgsEnum::CardSuit Card::AllSuits[4] = {
    QSgsEnum::CardSuit::Spade,
    QSgsEnum::CardSuit::Club,
    QSgsEnum::CardSuit::Heart,
    QSgsEnum::CardSuit::Diamond
};

Card::Card(RoomObject *roomObject, const CardFace *cardFace, QSgsEnum::CardSuit suit, int number, bool canRecast, bool transferable, int id)
    : QObject(roomObject), d_ptr(new CardPrivate)
{
    Q_D(Card);
    d->roomObject = roomObject;
    d->cardFace = cardFace;
    d->suit = suit;
    d->number = number;
    d->canRecast = canRecast;
    d->transferable = transferable;
    d->id = id;

    d->mute = false;
}

Card::~Card()
{
    Q_D(Card);
    delete d;
}

QString Card::suitString() const
{
    return Suit2String(suit());
}

QString Card::Suit2String(QSgsEnum::CardSuit suit)
{
    switch (suit) {
        case QSgsEnum::CardSuit::Spade: return QStringLiteral("spade");
        case QSgsEnum::CardSuit::Heart: return QStringLiteral("heart");
        case QSgsEnum::CardSuit::Club: return QStringLiteral("club");
        case QSgsEnum::CardSuit::Diamond: return QStringLiteral("diamond");
        case QSgsEnum::CardSuit::Black: return QStringLiteral("no_suit_black");
        case QSgsEnum::CardSuit::Red: return QStringLiteral("no_suit_red");
        default: return QStringLiteral("no_suit");
    }
}

bool Card::isRed() const
{
    return color() == QSgsEnum::CardSuit::Red;
}

bool Card::isBlack() const
{
    return color() == QSgsEnum::CardSuit::Black;
}

int Card::id() const
{
    Q_D(const Card);
    return d->id;
}

void Card::setId(int id)
{
    Q_D(Card);
    d->id = id;
}

int Card::effectiveId() const
{
    Q_D(const Card);
    if (isVirtualCard()) {
        if (d->subcards.isEmpty())
            return -1;
        else
            return d->subcards.first()->id();
    } else
        return d->id;
}

int Card::number() const
{
    Q_D(const Card);
    // note: distinguish "No number" and "Number TBD"
    if (d->number >= 0)
        return d->number;

    if (isVirtualCard()) {
        // Virtual cards must be created in a certain RoomObject
        Q_ASSERT(d->roomObject != nullptr);
        if (subcardsLength() == 0)
            return 0;
        else {
            int num = 0;
            foreach (Card *c, d->subcards)
                num += c->number();
            return num;
        }
    } else
        return d->number;
}

void Card::setNumber(int number)
{
    Q_D(Card);
    d->number = number;
}

QString Card::numberString() const
{
    int n = number();
    if (isVirtualCard()) {
        if (subcardsLength() == 0 || subcardsLength() >= 2)
            n = 0;
    }
    if (n == 10)
        return QStringLiteral("10");
    else {
        static const char *numberString = "-A23456789-JQK";
        return QString(numberString[n]);
    }
}

QSgsEnum::CardSuit Card::suit() const
{
    Q_D(const Card);
    // I don't know what problem this copuling in V2 and Hegemony solves, so we remove it for know.
    if (d->suit != QSgsEnum::CardSuit::Tbd)
        return d->suit;
    if (isVirtualCard()) {
        // Virtual cards must be created in a certain RoomObject
        Q_ASSERT(d->roomObject != nullptr);
        if (subcardsLength() == 0)
            return QSgsEnum::CardSuit::NoSuit;
        else if (subcardsLength() == 1)
            return d->subcards.first()->suit();
        else {
            QSgsEnum::CardSuit color = QSgsEnum::CardSuit::NoSuit;
            foreach (Card *c, d->subcards) {
                QSgsEnum::CardSuit color2 = c->color();
                if (color == QSgsEnum::CardSuit::NoSuit)
                    color = color2;
                else if (color != color2)
                    return QSgsEnum::CardSuit::NoSuit;
            }
            return (color == QSgsEnum::CardSuit::Red) ? QSgsEnum::CardSuit::Red : QSgsEnum::CardSuit::Black;
        }
    } else
        return d->suit;
}

void Card::setSuit(QSgsEnum::CardSuit suit)
{
    Q_D(Card);
    d->suit = suit;
}

bool Card::sameColorWith(const Card *other) const
{
    return color() == other->color();
}

QSgsEnum::CardSuit Card::color() const
{
    switch (suit()) {
        case QSgsEnum::CardSuit::Spade:
        case QSgsEnum::CardSuit::Club:
        case QSgsEnum::CardSuit::Black:
            return QSgsEnum::CardSuit::Black;
        case QSgsEnum::CardSuit::Heart:
        case QSgsEnum::CardSuit::Diamond:
        case QSgsEnum::CardSuit::Red:
            return QSgsEnum::CardSuit::Red;
        default:
            return QSgsEnum::CardSuit::NoSuit;
    }
}

bool Card::isEquipped() const
{
    // ClientPlayer? NO!!!
    //return Self->hasEquip(this);
    Q_D(const Card);
    RoomObject::CardPlaceStruct str = d->roomObject->cardPlace(this);
    return str.place == QSgsEnum::CardPlace::Equip;
}

bool Card::match(const QString &pattern) const
{
    QStringList patterns = pattern.split("+");
    foreach (const QString &ptn, patterns) {
        if (objectName() == ptn /*|| type() == ptn || subtype() == ptn*/)
            return true;
    }
    return false;
}

QString Card::fullName(bool includeSuit) const
{
    QString n = name();
    if (includeSuit) {
        QString suitName = suitString();
        return QStringLiteral("%1%2 %3").arg(suitName).arg(numberString()).arg(n);
    } else
        return QStringLiteral("%1 %2").arg(numberString()).arg(n);
}

QString Card::logName() const
{
    QString suitChar;
    QString numberStr;

    switch (suit()) {
        case QSgsEnum::CardSuit::Spade:
        case QSgsEnum::CardSuit::Heart:
        case QSgsEnum::CardSuit::Club:
        case QSgsEnum::CardSuit::Diamond: {
            suitChar = QStringLiteral("<img src='image/system/log/%1.png' height = 12/>").arg(suitString());
            break;
        }
        case QSgsEnum::CardSuit::Red: {
            suitChar = tr("NoSuitRed");
            break;
        }
        case QSgsEnum::CardSuit::Black: {
            suitChar = tr("NoSuitBlack");
            break;
        }
        case QSgsEnum::CardSuit::NoSuit: {
            suitChar = tr("NoSuit");
            break;
        }
        default:
            break;
    }
    Q_D(const Card);
    if (d->number > 0 && d->number <= 13)
        numberStr = numberString();

    return QStringLiteral("%1[%2%3]").arg(name()).arg(suitChar).arg(numberStr);
}

QString Card::name() const
{
    // @Todo_Fs: translation
    // return Sanguosha->translate(objectName());
    return objectName();
}

const QString &Card::skillName() const
{
    Q_D(const Card);
    return d->skillName;
}

void Card::setSkillName(const QString &name)
{
    Q_D(Card);
    d->skillName = name;
}

QString Card::description(bool yellow) const
{
    return QString();
//    QString desc = Sanguosha->translate(":" + objectName());
//    if (desc == ":" + objectName())
//        return desc;
//    foreach (const QString &skill_type, Sanguosha->skillColorMap().keys()) {
//        QString to_replace = Sanguosha->translate(skill_type);
//        if (to_replace == skill_type) continue;
//        QString color_str = Sanguosha->skillColor(skill_type).name();
//        if (desc.contains(to_replace))
//            desc.replace(to_replace, QString("<font color=%1><b>%2</b></font>").arg(color_str)
//            .arg(to_replace));
//    }

//    for (int i = 0; i < 6; i++) {
//        QSgsEnum::CardSuit suit = (QSgsEnum::CardSuit)i;
//        QString str = Card::Suit2String(suit);
//        QString to_replace = Sanguosha->translate(str);
//        bool red = isRed();
//        if (to_replace == str) continue;
//        if (desc.contains(to_replace)) {
//            if (red)
//                desc.replace(to_replace, QString("<font color=#FF0000>%1</font>").arg(Sanguosha->translate(str + "_char")));
//            else
//                desc.replace(to_replace, QString("<font color=#000000><span style=background-color:white>%1</span></font>").arg(Sanguosha->translate(str + "_char")));
//        }
//    }

//    desc.replace("\n", "<br/>");
//    if (isTransferable()) {
//        desc += "<br/><br/>";
//        desc += tr("This card is transferable.");
//    }
//    return tr("<font color=%1><b>[%2]</b> %3</font>").arg(yellow ? "#FFFF33" : "#FF0080").arg(name()).arg(desc);
}



QString Card::effectName() const
{
    return QString();
//    QString name = objectName();
//    for (int i = 0; i < name.length(); i++) {
//        QChar ch = name[i];
//        if (ch.isUpper()) {
//            name[i] = ch.toLower();
//            if (i != 0)
//                name.insert(i, "_");
//            break;
//        }
//    }
//    return name;
}

bool Card::isTransferable() const
{
    Q_D(const Card);
    return d->transferable;
}

void Card::setTransferable(bool transferbale)
{
    Q_D(Card);
    d->transferable = transferbale;
}

QString Card::subcardString() const
{
    Q_D(const Card);
    if (d->subcards.isEmpty())
        return QStringLiteral(".");

    QStringList str;
    foreach (Card *subcard, d->subcards)
        str << QString::number(subcard->id());

    return str.join("+");
}

void Card::addSubcards(const QList<Card *> &cards)
{
    Q_D(Card);
    d->subcards << cards;
}

void Card::addSubcards(const QList<int> &subcardsList)
{
    Q_D(Card);
    Q_ASSERT(d->roomObject != nullptr);

    foreach (int i, subcardsList) {
        Card *c = d->roomObject->card(i);
        if (c == nullptr)
            continue;
        Q_ASSERT(c->id() == i);
        d->subcards << c;
    }
}

int Card::subcardsLength() const
{
    Q_D(const Card);
    return d->subcards.length();
}

bool Card::isVirtualCard() const
{
    // note that a virtual card must be attached to a certain roomObject
    Q_D(const Card);
    return d->roomObject != nullptr && d->id < 0;
}
#if 0
bool Card::targetFixed() const
{
    return m_targetFixed;
}

bool Card::targetsFeasible(const QList<const Player *> &targets, const Player *) const
{
    if (target_fixed)
        return true;
    else
        return !targets.isEmpty();
}

bool Card::targetFilter(const QList<const Player *> &targets, const Player *to_select, const Player *Self) const
{
    return targets.isEmpty() && to_select != Self;
}

bool Card::targetFilter(const QList<const Player *> &targets, const Player *to_select, const Player *Self, int &maxVotes) const
{
    bool canSelect = targetFilter(targets, to_select, Self);
    maxVotes = canSelect ? 1 : 0;
    return canSelect;
}

void Card::doPreAction(Room *, const CardUseStruct &) const
{
}

void Card::onUse(Room *room, const CardUseStruct &use) const
{
//    CardUseStruct card_use = use;
//    ServerPlayer *player = card_use.from;

//    room->sortByActionOrder(card_use.to);

//    bool hidden = (card_use.card->getTypeId() == TypeSkill && !card_use.card->willThrow());
//    LogMessage log;
//    log.from = player;
//    if (!card_use.card->targetFixed() || card_use.to.length() > 1 || !card_use.to.contains(card_use.from))
//        log.to = card_use.to;
//    log.type = "#UseCard";
//    log.card_str = card_use.card->toString(hidden);
//    room->sendLog(log);

//    if (card_use.card->isKindOf("Collateral")) { // put it here for I don't wanna repeat these codes in Card::onUse
//        ServerPlayer *victim = card_use.to.first()->tag["collateralVictim"].value<ServerPlayer *>();
//        if (victim) {
//            LogMessage log;
//            log.type = "#CollateralSlash";
//            log.from = card_use.from;
//            log.to << victim;
//            room->sendLog(log);
//            room->doAnimate(QSanProtocol::S_ANIMATE_INDICATE, card_use.to.first()->objectName(), victim->objectName());
//        }
//    }

//    QList<int> used_cards;
//    QList<CardsMoveStruct> moves;
//    if (card_use.card->isVirtualCard())
//        used_cards.append(card_use.card->getSubcards());
//    else
//        used_cards << card_use.card->getEffectiveId();

//    QVariant data = QVariant::fromValue(card_use);
//    RoomThread *thread = room->getThread();
//    Q_ASSERT(thread != nullptr);
//    thread->trigger(PreCardUsed, room, player, data);
//    card_use = data.value<CardUseStruct>();

//    if (card_use.card->getTypeId() != TypeSkill) {
//        CardMoveReason reason(CardMoveReason::S_REASON_USE, player->objectName(), QString(), card_use.card->getSkillName(), QString());
//        if (card_use.to.size() == 1)
//            reason.m_targetId = card_use.to.first()->objectName();
//        foreach (int id, used_cards) {
//            CardsMoveStruct move(id, nullptr, Player::PlaceTable, reason);
//            moves.append(move);
//        }
//        room->moveCardsAtomic(moves, true);
//        // show general
//        QString skill_name = card_use.card->showSkill();
//        if (!skill_name.isNull() && card_use.from->ownSkill(skill_name) && !card_use.from->hasShownSkill(skill_name))
//            card_use.from->showGeneral(card_use.from->inHeadSkills(skill_name));
//    } else {
//        const SkillCard *skill_card = qobject_cast<const SkillCard *>(card_use.card);
//        if (skill_card)
//            skill_card->extraCost(room, card_use);

//        // show general
//        QString skill_name = card_use.card->showSkill();
//        if (!skill_name.isNull() && card_use.from->ownSkill(skill_name) && !card_use.from->hasShownSkill(skill_name))
//            card_use.from->showGeneral(card_use.from->inHeadSkills(skill_name));

//        if (card_use.card->willThrow()) {
//            QList<int> table_cardids = room->getCardIdsOnTable(card_use.card);
//            if (!table_cardids.isEmpty()) {
//                DummyCard dummy(table_cardids);
//                CardMoveReason reason(CardMoveReason::S_REASON_THROW, player->objectName(), QString(), card_use.card->getSkillName(), QString());
//                room->moveCardTo(&dummy, player, nullptr, Player::DiscardPile, reason, true);
//            }
//        }
//    }

//    thread->trigger(CardUsed, room, player, data);
//    thread->trigger(CardFinished, room, player, data);
}

void Card::use(Room *room, ServerPlayer *source, QList<ServerPlayer *> &targets) const
{
//    QStringList nullified_list = room->getTag("CardUseNullifiedList").toStringList();
//    bool all_nullified = nullified_list.contains("_ALL_TARGETS");
//    foreach (ServerPlayer *target, targets) {
//        CardEffectStruct effect;
//        effect.card = this;
//        effect.from = source;
//        effect.to = target;
//        effect.multiple = (targets.length() > 1);
//        effect.nullified = (all_nullified || nullified_list.contains(target->objectName()));

//        QVariantList players;
//        for (int i = targets.indexOf(target); i < targets.length(); i++) {
//            if (!nullified_list.contains(targets.at(i)->objectName()) && !all_nullified)
//                players.append(QVariant::fromValue(targets.at(i)));
//        }
//        room->setTag("targets" + this->toString(), QVariant::fromValue(players));

//        room->cardEffect(effect);
//    }

//    room->removeTag("targets" + this->toString());

//    QList<int> table_cardids = room->getCardIdsOnTable(this);
//    if (!table_cardids.isEmpty()) {
//        DummyCard dummy(table_cardids);
//        CardMoveReason reason(CardMoveReason::S_REASON_USE, source->objectName(), QString(), this->getSkillName(), QString());
//        if (targets.size() == 1) reason.m_targetId = targets.first()->objectName();
//        room->moveCardTo(&dummy, source, nullptr, Player::DiscardPile, reason, true);
//    }
}

void Card::onEffect(const CardEffectStruct &) const
{
}

bool Card::isCancelable(const CardEffectStruct &) const
{
    return false;
}

QStringList Card::checkTargetModSkillShow(const CardUseStruct &) const
{
    return QStringList();
}

void Card::onNullified(ServerPlayer *) const
{
    return;
}
bool Card::isAvailable(const Player *player) const
{
    return !player->isCardLimited(this, m_handlingMethod)
        || (m_canRecast && !player->isCardLimited(this, Card::MethodRecast));
}

const Card *Card::validate(CardUseStruct &) const
{
    return this;
}

const Card *Card::validateInResponse(ServerPlayer *) const
{
    return this;
}
bool Card::willThrow() const
{
    return m_willThrow;
}
bool Card::hasPreAction() const
{
    return m_hasPreact;
}

Card::HandlingMethod Card::handlingMethod() const
{
    return m_handlingMethod;
}

#endif

const QString &Card::showSkill() const
{
    Q_D(const Card);
    return d->showSkill;
}

void Card::setShowSkill(const QString &skillName)
{
    Q_D(Card);
    d->showSkill = skillName;
}

const QStringList &Card::flags() const
{
    Q_D(const Card);
    return d->flags;
}

void Card::addSubcard(int cardId)
{
    if (cardId < 0)
        qWarning("%s", qPrintable(tr("Subcard must not be virtual card!")));
    else {
        Q_D(Card);
        Q_ASSERT(d->roomObject != nullptr);
        Card *c = d->roomObject->card(cardId);
        if (c == nullptr)
            return;
        d->subcards << c;
    }
}

void Card::addSubcard(Card *card)
{
    if (!card->isVirtualCard())
        addSubcard(card->id());
    else
        addSubcards(card->subcards());
}

const QList<Card *> &Card::subcards() const
{
    Q_D(const Card);
    return d->subcards;
}

void Card::clearSubcards()
{
    Q_D(Card);
    d->subcards.clear();
}

bool Card::mute() const
{
    Q_D(const Card);
    return d->mute;
}

bool Card::canRecast() const
{
    Q_D(const Card);
    return d->canRecast;
}

void Card::setCanRecast(bool can)
{
    Q_D(Card);
    d->canRecast = can;
}

void Card::setFlag(const QString &flag)
{
    static char symbol_c = '-';

    Q_D(Card);
    if (flag.isEmpty())
        return;
    else if (flag == QStringLiteral("."))
        d->flags.clear();
    else if (flag.startsWith(symbol_c)) {
        QString copy = flag;
        copy.remove(0, 1); // only remove the first "-", but not all "-"s
        d->flags.removeOne(copy);
    } else if (!d->flags.contains(flag))
        d->flags << flag;
}

void Card::setFlags(const QStringList &fs)
{
    // Grasp the grass!!
    // m_flags = fs;

    foreach (const QString &s, fs)
        setFlag(s);
}

bool Card::hasFlag(const QString &flag) const
{
    Q_D(const Card);
    return d->flags.contains(flag);
}

void Card::clearFlags()
{
    Q_D(Card);
    d->flags.clear();
}
#if 0
// ---------   Skill card     ------------------

SkillCard::SkillCard() : Card(NoSuit, 0)
{
}

void SkillCard::setUserString(const QString &userString)
{
    this->m_userString = userString;
}

QString SkillCard::userString() const
{
    return m_userString;
}

QString SkillCard::type() const
{
    return "skill_card";
}

QString SkillCard::subtype() const
{
    return "skill_card";
}

Card::CardType SkillCard::typeId() const
{
    return Card::TypeSkill;
}

QString SkillCard::toString(bool hidden) const
{
    QString str;
    if (!hidden)
        str = QString("@%1[%2:%3]=%4&%5")
        .arg(metaObject()->className()).arg(suitString())
        .arg(numberString()).arg(subcardString()).arg(m_showSkill);
    else
        str = QString("@%1[no_suit:-]=.&%2").arg(metaObject()->className()).arg(m_showSkill);

    if (!m_userString.isEmpty())
        return QString("%1:%2").arg(str).arg(m_userString);
    else
        return str;
}

void SkillCard::extraCost(Room *room, const CardUseStruct &card_use) const
{
    if (card_use.card->willThrow()) {
        CardMoveReason reason(CardMoveReason::S_REASON_THROW, card_use.from->objectName(), QString(), card_use.card->skillName(), QString());
        room->moveCardTo(this, card_use.from, nullptr, Player::PlaceTable, reason, true);
    }
}

// ---------- Dummy card      -------------------

DummyCard::DummyCard() : SkillCard()
{
    target_fixed = true;
    m_handlingMethod = Card::MethodNone;
    setObjectName("dummy");
}

DummyCard::DummyCard(const QList<int> &subcards) : SkillCard()
{
    target_fixed = true;
    m_handlingMethod = Card::MethodNone;
    setObjectName("dummy");
    foreach(int id, subcards)
        this->m_subcards.append(id);
}

QString DummyCard::type() const
{
    return "dummy_card";
}

QString DummyCard::subtype() const
{
    return "dummy_card";
}

QString DummyCard::toString(bool hidden) const
{
    Q_UNUSED(hidden)
        return "$" + subcardString();
}

ArraySummonCard::ArraySummonCard(const QString &name)
    : SkillCard()
{
    setObjectName(name);
    m_skillName = name;
    m_mute = true;
    target_fixed = true;
    m_handlingMethod = Card::MethodNone;
}

const Card *ArraySummonCard::validate(CardUseStruct &card_use) const
{
    const BattleArraySkill *skill = qobject_cast<const BattleArraySkill *>(Sanguosha->triggerSkill(objectName()));
    if (skill) {
        card_use.from->showGeneral(card_use.from->inHeadSkills(skill));
        skill->summonFriends(card_use.from);
    }
    return nullptr;
}

TransferCard::TransferCard()
{
    m_willThrow = false;
    m_mute = true;
}

bool TransferCard::targetFilter(const QList<const Player *> &targets, const Player *to_select, const Player *Self) const
{
    if (!targets.isEmpty())
        return false;
    if (!Self->hasShownOneGeneral())
        return !to_select->hasShownOneGeneral();
    return !to_select->hasShownOneGeneral() || !to_select->isFriendWith(Self);
}

void TransferCard::onEffect(const CardEffectStruct &effect) const
{
    bool draw = effect.to->hasShownOneGeneral();
    CardMoveReason reason(CardMoveReason::S_REASON_GIVE, effect.from->objectName(), effect.to->objectName(), "transfer", QString());
    effect.to->getRoom()->obtainCard(effect.to, this, reason);
    if (draw)
        effect.from->drawCards(1, "transfer");
}
#endif
