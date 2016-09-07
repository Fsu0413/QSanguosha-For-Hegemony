
#ifndef CARDFACE_H__
#define CARDFACE_H__

#include "libqsgsgamelogicglobal.h"
#include "enumeration.h"
#include "structs.h"

class Player;
class Card;
class Room;

class CardFacePrivate;

class CardFace : public QObject
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
    virtual bool targetsFeasible(const QList<const Player *> &targets, const Player *Self) const;
    // @todo: the following two functions should be merged into one.
    virtual bool targetFilter(const QList<const Player *> &targets, const Player *to_select, const Player *Self) const;
    virtual bool targetFilter(const QList<const Player *> &targets, const Player *to_select, const Player *Self, int &maxVotes) const;
    virtual bool isAvailable(const Player *player) const;

    virtual const Card *validate(CardUseStruct &cardUse) const;
    virtual const Card *validateInResponse(Player *user) const;

    virtual void doPreAction(Room *room, const CardUseStruct &card_use) const;
    virtual void onUse(Room *room, const CardUseStruct &card_use) const;
    virtual void use(Room *room, Player *source, QList<Player *> &targets) const;
    virtual void onEffect(const CardEffectStruct &effect) const;
    virtual bool isCancelable(const CardEffectStruct &effect) const;

    virtual QStringList checkTargetModSkillShow(const CardUseStruct & /* use */) const;

    virtual void onNullified(Player *target) const;
    bool isKindOf(const char *cardType) const; // for YanXiao and LuaCard? Should we make Yanxiao as "move cards out of game"?


protected:
    explicit CardFace(const QString &name, QSgsEnum::CardHandlingMethod handlingMethod = QSgsEnum::CardHandlingMethod::Use, bool targetFixed = false, bool willThrow = false, bool hasPreact = false);

private:
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
