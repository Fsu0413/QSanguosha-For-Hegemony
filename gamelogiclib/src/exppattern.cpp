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

#include "exppattern.h"
#include "player.h"
#include "card.h"
#include "cardface.h"

ExpPattern::ExpPattern(const QString &exp)
{
    this->exp = exp;
}

bool ExpPattern::match(const Player *player, const Card *card) const
{
    QStringList splited = exp.split(QStringLiteral("$"));
    foreach (const QString &oneExp, splited)
        if (this->matchOne(player, card, oneExp)) return true;

    return false;
}

const QString &ExpPattern::getPatternString() const
{
    return exp;
}

// '|' means 'and', '$' means 'or'.
// the expression splited by '|' has 3 parts,
// 1st part means the card name, and ',' means more than one options.
// 2nd patt means the card suit, and ',' means more than one options.
// 3rd part means the card number, and ',' means more than one options,
// the number uses '~' to make a scale for valid expressions
bool ExpPattern::matchOne(const Player *player, const Card *card, QString exp) const
{
    QStringList factors = exp.split(QStringLiteral("|"));

    bool checkpoint = false;
    QStringList card_types = factors.at(0).split(QStringLiteral(","));
    foreach (const QString &or_name, card_types) {
        checkpoint = false;
        QStringList orNameSplit = or_name.split(QStringLiteral("+"));
        foreach (const QString &_name, orNameSplit) {
            QString name = _name;
            if (name == QStringLiteral(".")) {
                checkpoint = true;
            } else {
                bool isInt = false;
                bool positive = true;
                if (name.startsWith(QStringLiteral("^"))) {
                    positive = false;
                    name = name.mid(1);
                }
                if (card->cardFace()->isKindOf(name.toUtf8().data()) || (QStringLiteral("%") + card->cardFace()->objectName() == name) || (card->effectiveId() == name.toInt(&isInt) && isInt))
                    checkpoint = positive;
                else
                    checkpoint = !positive;
            }
            if (!checkpoint)
                break;
        }
        if (checkpoint)
            break;
    }
    if (!checkpoint)
        return false;
    if (factors.size() < 2)
        return true;

    checkpoint = false;
    QStringList card_suits = factors.at(1).split(QStringLiteral(","));
    foreach (const QString &_suit, card_suits) {
        QString suit = _suit;
        if (suit == QStringLiteral(".")) {
            checkpoint = true;
            break;
        }
        bool positive = true;
        if (suit.startsWith(QStringLiteral("^"))) {
            positive = false;
            suit = suit.mid(1);
        }
        if (card->suitString() == suit || (card->isBlack() && suit == QStringLiteral("black")) || (card->isRed() && suit == QStringLiteral("red")))
            checkpoint = positive;
        else
            checkpoint = !positive;
        if (checkpoint)
            break;
    }
    if (!checkpoint)
        return false;
    if (factors.size() < 3)
        return true;

    checkpoint = false;
    QStringList card_numbers = factors.at(2).split(QStringLiteral(","));
    int cdn = card->number();

    foreach (const QString &number, card_numbers) {
        if (number == QStringLiteral(".")) {
            checkpoint = true;
            break;
        }

        bool isInt = false;
        if (number.contains(QStringLiteral("~"))) {
            QStringList params = number.split(QStringLiteral("~"));
            int from, to;
            if (!params.at(0).size())
                from = 1;
            else
                from = params.at(0).toInt();
            if (!params.at(1).size())
                to = 13;
            else
                to = params.at(1).toInt();

            if (from <= cdn && cdn <= to)
                checkpoint = true;
        } else if (number.toInt(&isInt) == cdn && isInt)
            checkpoint = true;
        else if ((number == QStringLiteral("A") && cdn == 1) || (number == QStringLiteral("J") && cdn == 11) || (number == QStringLiteral("Q") && cdn == 12) || (number == QStringLiteral("K") && cdn == 13))
            checkpoint = true;
        if (checkpoint)
            break;
    }
    if (!checkpoint)
        return false;
    if (factors.size() < 4)
        return true;

    checkpoint = false;
    QString place = factors.at(3);
    if (!player || place == QStringLiteral("."))
        checkpoint = true;
    if (!checkpoint) {
        QList<const Card *> cards;
        if (card->isVirtualCard())
            cards = card->subcards();
        else
            cards << card;
        if (!cards.isEmpty()) {
            foreach (const Card *card, cards) {
                checkpoint = false;
                QStringList placeSplit = place.split(QStringLiteral(","));
                foreach (const QString &_p, placeSplit) {
                    QString p = _p;
                    if (p == QStringLiteral("equipped") && player->hasEquip(card)) {
                        checkpoint = true;
                    } else if (p == QStringLiteral("hand") && card->effectiveId() >= 0) {
                        foreach (const Card *c, player->handcards()) {
                            if (c == card) {
                                checkpoint = true;
                                break;
                            }
                        }
                    } else {
                        if (p.startsWith(QStringLiteral("%"))) {
                            p = p.mid(1);
//                            foreach (const Player *pl, player->getAliveSiblings()) {
//                                if (!pl->pile(p).isEmpty() && pl->pile(p).contains(card)) {
//                                    checkpoint = true;
//                                    break;
//                                }
//                            }
                        } else if (!player->pile(p).isEmpty() && player->pile(p).contains(card)) {
                            checkpoint = true;
                        }
                    }
                    if (checkpoint)
                        break;
                }
                if (!checkpoint)
                    break;
            }
        }
    }
    return checkpoint;
}

