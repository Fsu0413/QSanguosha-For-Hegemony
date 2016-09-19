
#include "cardface.h"

class CardFacePrivate
{
public:
    QSgsEnum::CardHandlingMethod handlingMethod;
    bool willThrow;
    bool hasPreact;

};

CardFace::CardFace(const QString &name, QSgsEnum::CardHandlingMethod handlingMethod, bool willThrow, bool hasPreact)
    : d_ptr(new CardFacePrivate)
{
    setObjectName(name);
    Q_D(CardFace);
    d->handlingMethod = handlingMethod;
    d->willThrow = willThrow;
    d->hasPreact = hasPreact;

}

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

bool CardFace::targetsFeasible(const QList<const Player *> &targets, const Player *, QSgsEnum::CardUseReason, const QString &) const
{
    return !targets.isEmpty();
}

bool CardFace::targetFilter(const QList<const Player *> &targets, const Player *toSelect, const Player *self, QSgsEnum::CardUseReason, const QString &, int *maxVotes) const
{
    int maxVotes_ = 0;
    if (maxVotes == nullptr)
        maxVotes = &maxVotes_;

    bool result = targets.isEmpty() && toSelect != self;
    if (result)
        *maxVotes = 1;
    else
        *maxVotes = 0;
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
    return inherits(cardType);
}

