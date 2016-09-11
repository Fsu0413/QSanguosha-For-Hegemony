
#ifndef CARDFACE_H__
#define CARDFACE_H__

#include "libqsgsgamelogicglobal.h"
#include "enumeration.h"
#include "structs.h"

class Player;
class Card;

class CardFacePrivate;

class LIBQSGSGAMELOGIC_EXPORT CardFace : public QObject
{
    Q_OBJECT

public:

    // In fact there is no such grammar in C++, but I set it here.
    // Every subclass should own this function.
#if 0
    static virtual CardFace *instance() = 0;
#endif
    virtual ~CardFace();

    virtual bool willThrow() const;
    virtual bool hasPreAction() const;
    virtual QSgsEnum::CardHandlingMethod handlingMethod() const;


    virtual QSgsEnum::CardType typeId() const = 0;
    virtual bool isNDTrick() const;
    virtual QString package() const;

    // card target selection
    virtual bool targetFixed() const;
    virtual bool targetsFeasible(const QList<const Player *> &targets, const Player *self) const;
    // @todo: the following two functions should be merged into one.
    virtual bool targetFilter(const QList<const Player *> &targets, const Player *toSelect, const Player *self) const;
    virtual bool targetFilter(const QList<const Player *> &targets, const Player *toSelect, const Player *self, int &maxVotes) const;
    virtual bool isAvailable(const Player *player) const;

    virtual const CardFace *validate(CardUseStruct &cardUse) const;
    virtual const CardFace *validateInResponse(Player *user) const;

    virtual void doPreAction(RoomObject *room, const CardUseStruct &card_use) const;
    virtual void onUse(RoomObject *room, const CardUseStruct &card_use) const;
    virtual void use(RoomObject *room, Player *source, QList<Player *> &targets) const;
    virtual void onEffect(const CardEffectStruct &effect) const;
    virtual bool isCancelable(const CardEffectStruct &effect) const;

    virtual QStringList checkTargetModSkillShow(const CardUseStruct & /* use */) const;

    virtual void onNullified(Player *target) const;
    bool isKindOf(const char *cardType) const; // for YanXiao and LuaCard? Should we make Yanxiao as "move cards out of game"?


protected:
    explicit CardFace(const QString &name, QSgsEnum::CardHandlingMethod handlingMethod = QSgsEnum::CardHandlingMethod::Use, bool targetFixed = false, bool willThrow = false, bool hasPreact = false);

    Q_DECLARE_PRIVATE(CardFace)
    CardFacePrivate *d_ptr;
};

class DummyCardFace : public CardFace
{
    static DummyCardFace *instance();

    virtual QSgsEnum::CardType typeId() const final override;

private:
    static DummyCardFace *self;
    DummyCardFace();
};


#endif
