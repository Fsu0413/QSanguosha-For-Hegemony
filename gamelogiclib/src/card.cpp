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
//#include "settings.h"
//#include "engine.h"
#include "structs.h"
#include "lua-wrapper.h"

const int Card::S_UNKNOWN_CARD_ID = -1;

const QSgsEnum::CardSuit Card::AllSuits[4] = {
    QSgsEnum::CardSuit::Spade,
    QSgsEnum::CardSuit::Club,
    QSgsEnum::CardSuit::Heart,
    QSgsEnum::CardSuit::Diamond
};

Card::Card(const QString &cardFaceName, QSgsEnum::CardSuit suit, int number, int id)
    : m_mute(false),
    m_canRecast(false), m_transferable(false),
    m_suit(suit), m_number(number), m_id(-1)
{

}

QString Card::suitString() const
{
    return Suit2String(suit());
}

QString Card::Suit2String(QSgsEnum::CardSuit suit)
{
    switch (suit) {
        case QSgsEnum::CardSuit::Spade: return "spade";
        case QSgsEnum::CardSuit::Heart: return "heart";
        case QSgsEnum::CardSuit::Club: return "club";
        case QSgsEnum::CardSuit::Diamond: return "diamond";
        case QSgsEnum::CardSuit::Black: return "no_suit_black";
        case QSgsEnum::CardSuit::Red: return "no_suit_red";
        default: return "no_suit";
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
    return m_id;
}

void Card::setId(int id)
{
    this->m_id = id;
}

int Card::effectiveId() const
{
    if (isVirtualCard()) {
        if (m_subcards.isEmpty())
            return -1;
        else
            return m_subcards.first();
    } else
        return m_id;
}

int Card::number() const
{
    if (m_number > 0) return m_number;
    if (isVirtualCard()) {
        if (subcardsLength() == 0)
            return 0;
        else {
            int num = 0;
            foreach (int id, m_subcards)
                num += Sanguosha->card(id)->number();
            return num;
        }
    } else
        return m_number;
}

void Card::setNumber(int number)
{
    this->m_number = number;
}

QString Card::numberString() const
{
    int n = number();
    if (isVirtualCard()) {
        if (subcardsLength() == 0 || subcardsLength() >= 2)
            n = 0;
    }
    if (n == 10)
        return "10";
    else {
        static const char *number_string = "-A23456789-JQK";
        return QString(number_string[n]);
    }
}

QSgsEnum::CardSuit Card::suit() const
{
    if (m_suit != QSgsEnum::CardSuit::NoSuit && m_suit != QSgsEnum::CardSuit::Tbd)
        return m_suit;
    if (isVirtualCard()) {
        if (subcardsLength() == 0)
            return QSgsEnum::CardSuit::NoSuit;
        else if (subcardsLength() == 1)
            return Sanguosha->card(m_subcards.first())->suit();
        else {
            QSgsEnum::CardSuit color = QSgsEnum::CardSuit::NoSuit;
            foreach (int id, m_subcards) {
                QSgsEnum::CardSuit color2 = Sanguosha->card(id)->color();
                if (color == QSgsEnum::CardSuit::NoSuit)
                    color = color2;
                else if (color != color2)
                    return QSgsEnum::CardSuit::NoSuit;
            }
            return (color == QSgsEnum::CardSuit::Red) ? QSgsEnum::CardSuit::Red : QSgsEnum::CardSuit::Black;
        }
    } else
        return m_suit;
}

void Card::setSuit(QSgsEnum::CardSuit suit)
{
    this->m_suit = suit;
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
    return Self->hasEquip(this);
}

bool Card::match(const QString &pattern) const
{
    QStringList patterns = pattern.split("+");
    foreach (const QString &ptn, patterns) {
        if (objectName() == ptn || type() == ptn /*|| subtype() == ptn*/)
            return true;
    }
    return false;
}

bool Card::CompareByNumber(const Card *a, const Card *b)
{
    static QSgsEnum::CardSuit new_suits[] = {QSgsEnum::CardSuit::Spade, QSgsEnum::CardSuit::Heart, QSgsEnum::CardSuit::Club,
                                             QSgsEnum::CardSuit::Diamond, QSgsEnum::CardSuit::Black, QSgsEnum::CardSuit::Red, QSgsEnum::CardSuit::NoSuit};
    QSgsEnum::CardSuit suit1 = new_suits[a->suit()];
    QSgsEnum::CardSuit suit2 = new_suits[b->suit()];

    if (a->m_number != b->m_number)
        return a->m_number < b->m_number;
    else
        return suit1 < suit2;
}

bool Card::CompareBySuit(const Card *a, const Card *b)
{
    static QSgsEnum::CardSuit new_suits[] = {QSgsEnum::CardSuit::Spade, QSgsEnum::CardSuit::Heart, QSgsEnum::CardSuit::Club,
                                             QSgsEnum::CardSuit::Diamond, QSgsEnum::CardSuit::Black, QSgsEnum::CardSuit::Red, QSgsEnum::CardSuit::NoSuit};
    QSgsEnum::CardSuit suit1 = new_suits[a->suit()];
    QSgsEnum::CardSuit suit2 = new_suits[b->suit()];

    if (suit1 != suit2)
        return suit1 < suit2;
    else
        return a->m_number < b->m_number;
}

//bool Card::isNDTrick() const
//{
//    return typeId() == TypeTrick && !isKindOf("DelayedTrick");
//}

//QString Card::package() const
//{
//    if (parent())
//        return parent()->objectName();
//    else
//        return QString();
//}

QString Card::fullName(bool include_suit) const
{
    QString name = name();
    if (include_suit) {
        QString suit_name = Sanguosha->translate(suitString());
        return QString("%1%2 %3").arg(suit_name).arg(numberString()).arg(name);
    } else
        return QString("%1 %2").arg(numberString()).arg(name);
}

QString Card::logName() const
{
    QString suit_char;
    QString number_string;

    switch (suit()) {
        case Spade:
        case Heart:
        case Club:
        case Diamond: {
            suit_char = QString("<img src='image/system/log/%1.png' height = 12/>").arg(suitString());
            break;
        }
        case NoSuitRed: {
            suit_char = tr("NoSuitRed");
            break;
        }
        case NoSuitBlack: {
            suit_char = tr("NoSuitBlack");
            break;
        }
        case NoSuit: {
            suit_char = tr("NoSuit");
            break;
        }
        default:
            break;
    }

    if (m_number > 0 && m_number <= 13)
        number_string = numberString();

    return QString("%1[%2%3]").arg(name()).arg(suit_char).arg(number_string);
}

QString Card::name() const
{
    return Sanguosha->translate(objectName());
}

QString Card::skillName(bool removePrefix) const
{
    if (m_skillName.startsWith("_") && removePrefix)
        return m_skillName.mid(1);
    else
        return m_skillName;
}

void Card::setSkillName(const QString &name)
{
    this->m_skillName = name;
}

QString Card::description(bool yellow) const
{
    QString desc = Sanguosha->translate(":" + objectName());
    if (desc == ":" + objectName())
        return desc;
    foreach (const QString &skill_type, Sanguosha->skillColorMap().keys()) {
        QString to_replace = Sanguosha->translate(skill_type);
        if (to_replace == skill_type) continue;
        QString color_str = Sanguosha->skillColor(skill_type).name();
        if (desc.contains(to_replace))
            desc.replace(to_replace, QString("<font color=%1><b>%2</b></font>").arg(color_str)
            .arg(to_replace));
    }

    for (int i = 0; i < 6; i++) {
        QSgsEnum::CardSuit suit = (Card::Suit)i;
        QString str = Card::Suit2String(suit);
        QString to_replace = Sanguosha->translate(str);
        bool red = isRed();
        if (to_replace == str) continue;
        if (desc.contains(to_replace)) {
            if (red)
                desc.replace(to_replace, QString("<font color=#FF0000>%1</font>").arg(Sanguosha->translate(str + "_char")));
            else
                desc.replace(to_replace, QString("<font color=#000000><span style=background-color:white>%1</span></font>").arg(Sanguosha->translate(str + "_char")));
        }
    }

    desc.replace("\n", "<br/>");
    if (isTransferable()) {
        desc += "<br/><br/>";
        desc += tr("This card is transferable.");
    }
    return tr("<font color=%1><b>[%2]</b> %3</font>").arg(yellow ? "#FFFF33" : "#FF0080").arg(name()).arg(desc);
}

QString Card::toString(bool hidden) const
{
    Q_UNUSED(hidden);
    if (!isVirtualCard())
        return QString::number(m_id);
    else
        return QString("%1:%2[%3:%4]=%5&%6")
        .arg(objectName()).arg(m_skillName)
        .arg(suitString()).arg(numberString()).arg(subcardString())
        .arg(m_showSkill);
}

QString Card::effectName() const
{
    QString name = objectName();
    for (int i = 0; i < name.length(); i++) {
        QChar ch = name[i];
        if (ch.isUpper()) {
            name[i] = ch.toLower();
            if (i != 0)
                name.insert(i, "_");
            break;
        }
    }
    return name;
}

bool Card::isTransferable() const
{
    return m_transferable;
}

void Card::setTransferable(bool transferbale)
{
    this->m_transferable = transferbale;
}

QString Card::subcardString() const
{
    if (m_subcards.isEmpty())
        return ".";

    QStringList str;
    foreach (int subcard, m_subcards)
        str << QString::number(subcard);

    return str.join("+");
}

void Card::addSubcards(const QList<const Card *> &cards)
{
    foreach (const Card *card, cards)
        m_subcards.append(card->id());
}

void Card::addSubcards(const QList<int> &subcards_list)
{
    m_subcards.append(subcards_list);
}

int Card::subcardsLength() const
{
    return m_subcards.length();
}

bool Card::isVirtualCard() const
{
    return m_id < 0;
}

//@to_do(Xusine): move this function to the logic core.

//const Card *Card::Parse(const QString &str)
//{
//    static QMap<QString, Card::Suit> suit_map;
//    if (suit_map.isEmpty()) {
//        suit_map.insert("spade", Card::Spade);
//        suit_map.insert("club", Card::Club);
//        suit_map.insert("heart", Card::Heart);
//        suit_map.insert("diamond", Card::Diamond);
//        suit_map.insert("no_suit_red", Card::NoSuitRed);
//        suit_map.insert("no_suit_black", Card::NoSuitBlack);
//        suit_map.insert("no_suit", Card::NoSuit);
//    }

//    if (str.startsWith(QChar('@'))) {
//        // skill card
//        QRegExp pattern1("@(\\w+)=([^:]+)&(.*)(:.+)?");
//        QRegExp pattern2("@(\\w+)=([^:]+)(:.+)?");
//        QRegExp ex_pattern("@(\\w*)\\[(\\w+):(.+)\\]=([^:]+)&(.*)(:.+)?");

//        QStringList texts;
//        QString card_name, card_suit, card_number;
//        QStringList subcard_ids;
//        QString subcard_str;
//        QString show_skill;
//        QString user_string;

//        if (pattern1.exactMatch(str)) {
//            texts = pattern1.capturedTexts();
//            card_name = texts.at(1);
//            subcard_str = texts.at(2);
//            show_skill = texts.at(3);
//            user_string = texts.at(4);
//        } else if (pattern2.exactMatch(str)) {
//            texts = pattern2.capturedTexts();
//            card_name = texts.at(1);
//            subcard_str = texts.at(2);
//            user_string = texts.at(3);
//        } else if (ex_pattern.exactMatch(str)) {
//            texts = ex_pattern.capturedTexts();
//            card_name = texts.at(1);
//            card_suit = texts.at(2);
//            card_number = texts.at(3);
//            subcard_str = texts.at(4);
//            show_skill = texts.at(5);
//            user_string = texts.at(6);
//        } else
//            return nullptr;

//        if (subcard_str != ".")
//            subcard_ids = subcard_str.split("+");

//        SkillCard *card = Sanguosha->cloneSkillCard(card_name);

//        if (card == nullptr)
//            return nullptr;

//        card->addSubcards(StringList2IntList(subcard_ids));

//        // skill name
//        // @todo: This is extremely dirty and would cause endless troubles.
//        QString skillName = card->skillName();
//        if (skillName.isNull()) {
//            skillName = card_name.remove("Card").toLower();
//            card->setSkillName(skillName);
//        }
//        if (!card_suit.isEmpty())
//            card->setSuit(suit_map.value(card_suit, Card::NoSuit));

//        if (!card_number.isEmpty()) {
//            int number = 0;
//            if (card_number == "A")
//                number = 1;
//            else if (card_number == "J")
//                number = 11;
//            else if (card_number == "Q")
//                number = 12;
//            else if (card_number == "K")
//                number = 13;
//            else
//                number = card_number.toInt();

//            card->setNumber(number);
//        }

//        if (!show_skill.isEmpty())
//            card->setShowSkill(show_skill);
//        /*
//                else if (!skillName.isEmpty())
//                card->setShowSkill(skillName);
//                */  // The deletion of this code is extremely dangerous, for all the card in server is created in this way.
//        // I(Fs) deleted this in 2015/4/21, for it causes a bug that one cannot use the skill card as the cost.

//        if (!user_string.isEmpty()) {
//            user_string.remove(0, 1);
//            card->setUserString(user_string);
//        }
//        card->deleteLater();
//        return card;
//    } else if (str.startsWith(QChar('$'))) {
//        QString copy = str;
//        copy.remove(QChar('$'));
//        QStringList card_strs = copy.split("+");
//        DummyCard *dummy = new DummyCard(StringList2IntList(card_strs));
//        dummy->deleteLater();
//        return dummy;
//    } else if (str.startsWith(QChar('#'))) {
//        LuaSkillCard *new_card = LuaSkillCard::Parse(str);
//        new_card->deleteLater();
//        return new_card;
//    } else if (str.contains(QChar('='))) {
//        QRegExp pattern("(\\w+):(\\w*)\\[(\\w+):(.+)\\]=(.+)&(.*)");
//        if (!pattern.exactMatch(str))
//            return nullptr;

//        QStringList texts = pattern.capturedTexts();
//        QString card_name = texts.at(1);
//        QString m_skillName = texts.at(2);
//        QString suit_string = texts.at(3);
//        QString number_string = texts.at(4);
//        QString subcard_str = texts.at(5);
//        QString show_skill = texts.at(6);
//        QStringList subcard_ids;
//        if (subcard_str != ".")
//            subcard_ids = subcard_str.split("+");

//        Suit suit = Card::NoSuit;
//        DummyCard *dummy = new DummyCard(StringList2IntList(subcard_ids));
//        if (suit_string == "to_be_decided")
//            suit = dummy->suit();
//        else
//            suit = suit_map.value(suit_string, Card::NoSuit);
//        dummy->deleteLater();

//        int number = 0;
//        if (number_string == "A")
//            number = 1;
//        else if (number_string == "J")
//            number = 11;
//        else if (number_string == "Q")
//            number = 12;
//        else if (number_string == "K")
//            number = 13;
//        else
//            number = number_string.toInt();

//        Card *card = Sanguosha->cloneCard(card_name, suit, number);
//        if (card == nullptr)
//            return nullptr;

//        card->addSubcards(StringList2IntList(subcard_ids));
//        card->setSkillName(m_skillName);
//        card->setShowSkill(show_skill);
//        card->deleteLater();
//        return card;
//    } else {
//        bool ok;
//        int card_id = str.toInt(&ok);
//        if (ok)
//            return Sanguosha->card(card_id)->realCard();
//        else
//            return nullptr;
//    }
//}

Card *Card::Clone(const Card *card)
{
    Card::Suit suit = card->suit();
    int number = card->number();

    QObject *card_obj = nullptr;
    if (card->isKindOf("LuaBasicCard")) {
        const LuaBasicCard *lcard = qobject_cast<const LuaBasicCard *>(card);
        Q_ASSERT(lcard != nullptr);
        card_obj = lcard->clone();
    } else if (card->isKindOf("LuaTrickCard")) {
        const LuaTrickCard *lcard = qobject_cast<const LuaTrickCard *>(card);
        Q_ASSERT(lcard != nullptr);
        card_obj = lcard->clone();
    } else if (card->isKindOf("LuaWeapon")) {
        const LuaWeapon *lcard = qobject_cast<const LuaWeapon *>(card);
        Q_ASSERT(lcard != nullptr);
        card_obj = lcard->clone();
    } else if (card->isKindOf("LuaArmor")) {
        const LuaArmor *lcard = qobject_cast<const LuaArmor *>(card);
        Q_ASSERT(lcard != nullptr);
        card_obj = lcard->clone();
    } else if (card->isKindOf("LuaTreasure")) {
        const LuaTreasure *lcard = qobject_cast<const LuaTreasure *>(card);
        Q_ASSERT(lcard != nullptr);
        card_obj = lcard->clone();
    } else {
        const QMetaObject *meta = card->metaObject();
        card_obj = meta->newInstance(Q_ARG(Card::Suit, suit), Q_ARG(int, number));
    }
    if (card_obj) {
        Card *new_card = qobject_cast<Card *>(card_obj);
        new_card->setId(card->id());
        new_card->setObjectName(card->objectName());
        new_card->addSubcard(card->id());
        new_card->setTransferable(card->isTransferable());
        return new_card;
    } else
        return nullptr;
}

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

QString Card::showSkill() const
{
    return m_showSkill;
}

void Card::setShowSkill(const QString &skill_name)
{
    m_showSkill = skill_name;
}

bool Card::isKindOf(const char *cardType) const
{
    Q_ASSERT(cardType); return inherits(cardType);
}

QStringList Card::flags() const
{
    return m_flags;
}

bool Card::isModified() const
{
    return false;
}

void Card::onNullified(ServerPlayer *) const
{
    return;
}

void Card::addSubcard(int card_id)
{
    if (card_id < 0)
        qWarning("%s", qPrintable(tr("Subcard must not be virtual card!")));
    else
        m_subcards << card_id;
}

void Card::addSubcard(const Card *card)
{
    //addSubcard(card->getEffectiveId());
    if (!card->isVirtualCard())
        addSubcard(card->id());
    else
        addSubcards(card->subcards());
}

QList<int> Card::subcards() const
{
    return m_subcards;
}

void Card::clearSubcards()
{
    m_subcards.clear();
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

bool Card::isMute() const
{
    return m_mute;
}

bool Card::willThrow() const
{
    return m_willThrow;
}

bool Card::canRecast() const
{
    return m_canRecast;
}

bool Card::hasPreAction() const
{
    return m_hasPreact;
}

Card::HandlingMethod Card::handlingMethod() const
{
    return m_handlingMethod;
}

void Card::setCanRecast(bool can)
{
    m_canRecast = can;
}

void Card::setFlags(const QString &flag) const
{
    static char symbol_c = '-';

    if (flag.isEmpty())
        return;
    else if (flag == ".")
        m_flags.clear();
    else if (flag.startsWith(symbol_c)) {
        QString copy = flag;
        copy.remove(symbol_c);
        m_flags.removeOne(copy);
    } else if (!m_flags.contains(flag))
        m_flags << flag;
}

void Card::setFlags(const QStringList &fs)
{
    m_flags = fs;
}

bool Card::hasFlag(const QString &flag) const
{
    return m_flags.contains(flag);
}

void Card::clearFlags() const
{
    m_flags.clear();
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
