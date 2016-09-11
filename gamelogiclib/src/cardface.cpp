
#include "cardface.h"

class CardFacePrivate
{
public:
    QSgsEnum::CardHandlingMethod handlingMethod;
    bool targetFixed;
    bool willThrow;
    bool hasPreact;

};


CardFace::~CardFace()
{
    Q_D(CardFace);
    delete d;
}

bool CardFace::willThrow() const
{
    Q_D(const CardFace);
    return d->willThrow;
}

bool CardFace::hasPreAction() const
{
    Q_D(const CardFace);
    return d->hasPreact;
}

QSgsEnum::CardHandlingMethod CardFace::handlingMethod() const
{
    Q_D(const CardFace);
    return d->handlingMethod;
}

bool CardFace::isNDTrick() const
{
    return false;
}

QString CardFace::package() const
{
    return QString();
}

bool CardFace::targetFixed() const
{
    Q_D(const CardFace);
    return d->targetFixed;
}

bool CardFace::targetsFeasible(const QList<const Player *> &targets, const Player *self) const
{
    return false;
}

bool CardFace::targetFilter(const QList<const Player *> &targets, const Player *toSelect, const Player *self) const
{
    return targets.length() == 0;
}

bool CardFace::targetFilter(const QList<const Player *> &targets, const Player *toSelect, const Player *self, int &maxVotes) const
{
    bool result = this->targetFilter(targets, toSelect, self);
    if (result)
        maxVotes = 1;
    else
        maxVotes = 0;
    return result;
}

bool CardFace::isAvailable(const Player *player) const
{
    return true;
}

const CardFace *CardFace::validate(CardUseStruct &use) const
{
    return this;
}

const CardFace *CardFace::validateInResponse(Player *user) const
{
    return this;
}

void CardFace::doPreAction(RoomObject *room, const CardUseStruct &use) const
{

}

void CardFace::onUse(RoomObject *room, const CardUseStruct &use) const
{

}

void CardFace::use(RoomObject *room, Player *source, QList<Player *> &targets) const
{

}

void CardFace::onEffect(const CardEffectStruct &effect) const
{

}

bool CardFace::isCancelable(const CardEffectStruct &effect) const
{
    return true;
}

QStringList CardFace::checkTargetModSkillShow(const CardUseStruct &effect) const
{
    return QStringList();
}

void CardFace::onNullified(Player *target) const
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
    d->handlingMethod = handlingMethod;
    d->targetFixed = targetFixed;
    d->willThrow = willThrow;
    d->hasPreact = hasPreact;

}
