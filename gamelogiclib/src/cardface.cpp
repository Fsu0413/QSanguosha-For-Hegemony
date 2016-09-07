
#include "cardface.h"

class CardFacePrivate
{
public:
    QSgsEnum::CardHandlingMethod handlingMethod;
    bool targetFixed;
    bool willThrow;
    bool hasPreact;

};


bool CardFace::willThrow() const
{
    Q_D(const CardFace);
    return d_ptr->willThrow;
}

bool CardFace::hasPreAction() const
{
    Q_D(const CardFace);
    return d_ptr->hasPreact;
}

QSgsEnum::CardHandlingMethod CardFace::handlingMethod() const
{
    Q_D(const CardFace);
    return d_ptr->handlingMethod;
}

bool CardFace::isNDTrick() const
{
    return false;
}

QString CardFace::package() const
{
    return "";
}

bool CardFace::targetFixed() const
{
    Q_D(const CardFace);
    return d_ptr->targetFixed;
}

bool CardFace::targetsFeasible(const QList<const Player *> &, const Player *) const
{
    return false;
}

bool CardFace::targetFilter(const QList<const Player *> &targets, const Player *to_select, const Player *Self) const
{
    return targets.length() == 0;
}

bool CardFace::targetFilter(const QList<const Player *> &targets, const Player *to_select, const Player *Self, int &maxVotes) const
{
    bool result = this->targetFilter(targets,to_select,Self);
    if (result)
        maxVotes == 1;
    else
        maxVotes == 0;
    return result;
}

bool CardFace::isAvailable(const Player *) const
{
    return true;
}

const CardFace *CardFace::validate(CardUseStruct &) const
{
    return this;
}

const CardFace *CardFace::validateInResponse(Player *) const
{
    return this;
}

void CardFace::doPreAction(Room *, const CardUseStruct &) const
{

}

void CardFace::onUse(Room *, const CardUseStruct &) const
{

}

void CardFace::use(Room *, Player *, QList<Player *> &) const
{

}

void CardFace::onEffect(const CardEffectStruct &) const
{

}

bool CardFace::isCancelable(const CardEffectStruct &) const
{
    return true;
}

QStringList CardFace::checkTargetModSkillShow(const CardUseStruct &) const
{
    return QStringList();
}

void CardFace::onNullified(Player *) const
{

}


bool CardFace::isKindOf(const char *cardType) const
{
//    Q_ASSERT(cardType);
//    return inherits(cardType);
    // @Todo: use a new mechanism to deal with this
    return false;
}

CardFace::CardFace(const QString &name, QSgsEnum::CardHandlingMethod handlingMethod, bool targetFixed, bool willThrow, bool hasPreact)
    :d_ptr(new CardFacePrivate)
{
    setObjectName(name);
    Q_D(CardFace);
    d_ptr->handlingMethod = handlingMethod;
    d_ptr->targetFixed = targetFixed;
    d_ptr->willThrow = willThrow;
    d_ptr->hasPreact = hasPreact;

}
