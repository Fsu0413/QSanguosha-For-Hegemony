
#ifndef CARDFACE_H__
#define CARDFACE_H__

#include "libqsgsgamelogicglobal.h"

class Player;
class Card;
class Room;

class CardFace
{
public:
    enum HandlingMethod
    {
        NoMethod,
        Use,
        Response,
        Discard,
        Recast,
        Pindian
    };

    // card types
    enum CardType
    {
        Skill,
        Basic,
        Equip,
        Trick
    };

    // In fact there is no such grammar in C++, but I set it here.
    // Every subclass should own this function.
#if 0
    static virtual CardFace *instance() = 0;
#endif
    virtual ~CardFace();

    virtual bool willThrow() const;
    virtual bool hasPreAction() const;
    virtual HandlingMethod handlingMethod() const;

    virtual CardType typeId() const = 0;
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
    virtual const Card *validateInResponse(ServerPlayer *user) const;

    virtual void doPreAction(Room *room, const CardUseStruct &card_use) const;
    virtual void onUse(Room *room, const CardUseStruct &card_use) const;
    virtual void use(Room *room, ServerPlayer *source, QList<ServerPlayer *> &targets) const;
    virtual void onEffect(const CardEffectStruct &effect) const;
    virtual bool isCancelable(const CardEffectStruct &effect) const;

    virtual QStringList checkTargetModSkillShow(const CardUseStruct & /* use */) const;

    virtual void onNullified(ServerPlayer * /* target */) const;

protected:
    explicit CardFace(const QString &name);

    HandlingMethod m_handlingMethod;

    bool m_targetFixed;
    bool m_willThrow;
    bool m_hasPreact;

};

class DummyCardFace : public CardFace
{
    static DummyCardFace *instance();

    virtual CardType typeId() const final override;

private:
    static DummyCardFace *self;
    DummyCardFace();
};


#endif
