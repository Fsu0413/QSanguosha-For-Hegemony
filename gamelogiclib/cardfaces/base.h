#ifndef BASE_H
#define BASE_H

#include "libqsgsgamelogicglobal.h"
#include "cardface.h"
#include "structs.h"

class BasicCard : public CardFace
{
    Q_OBJECT

public:
    BasicCard(const QString &name) : CardFace(name)
    {
        m_handlingMethod = QSgsEnum::CardHandlingMethod::Use;
    }
    virtual QString type() const;
    virtual QSgsEnum::CardType typeId() const;
};

class TrickCard : public CardFace
{
    Q_OBJECT

public:
    TrickCard(const QString &name);
    void setCancelable(bool cancelable);

    virtual QString type() const;
    virtual QSgsEnum::CardType typeId() const;
    virtual bool isCancelable(const CardEffectStruct &effect) const;

private:
    bool m_cancelable;
};

class InstanceTrick : public TrickCard
{
    Q_OBJECT
public:
    InstanceTrick(const QString &name) :TrickCard(name){

    }
    virtual QString subtype() const;
};

class DelayedTrick : public TrickCard
{
    Q_OBJECT

public:
    DelayedTrick(const QString &name, bool movable = false) : TrickCard(name),m_movable(movable){
        judge.negative = true;
    }

    virtual void onNullified(ServerPlayer *target) const;

    virtual void onUse(Room *room, const CardUseStruct &card_use) const;
    virtual void use(Room *room, ServerPlayer *source, QList<ServerPlayer *> &targets) const;
    virtual QString subtype() const;
    virtual void onEffect(const CardEffectStruct &effect) const;
    virtual void takeEffect(ServerPlayer *target) const = 0;

protected:
    JudgeStruct m_judge;

private:
    bool m_movable;
};

class EquipCard : public CardFace
{
    Q_OBJECT

public:

    EquipCard(const QString &name) : CardFace(name)
    {
        m_handlingMethod = QSgsEnum::CardHandlingMethod::Use;
    }

    virtual QString type() const;
    virtual QSgsEnum::CardType typeId() const;

    virtual bool isAvailable(const Player *player) const;
    virtual void onUse(Room *room, const CardUseStruct &card_use) const;
    virtual void use(Room *room, ServerPlayer *source, QList<ServerPlayer *> &targets) const;

    virtual void onInstall(ServerPlayer *player) const;
    virtual void onUninstall(ServerPlayer *player) const;

    virtual QSgsEnum::EquipLocation location() const = 0;
};

class Weapon : public EquipCard
{
    Q_OBJECT

public:
    Weapon(const QString &name, int range);
    int range() const;

    virtual QString subtype() const;

    virtual QSgsEnum::EquipLocation location() const;
    virtual QString commonEffectName() const;

protected:
    int m_range;
};

class Armor : public EquipCard
{
    Q_OBJECT

public:
    Armor(const QString &name) : EquipCard(name)
    {
    }
    virtual QString subtype() const;

    virtual QSgsEnum::EquipLocation location() const;
    virtual QString commonEffectName() const;
};

class Horse : public EquipCard
{
    Q_OBJECT

public:
    Horse(const QString &name, int correct);
    int correctNum() const;

    virtual QSgsEnum::EquipLocation location() const;
    /*virtual void onInstall(ServerPlayer *player) const;
    virtual void onUninstall(ServerPlayer *player) const;*/

    virtual QString commonEffectName() const;

private:
    int m_correct;
};

class OffensiveHorse : public Horse
{
    Q_OBJECT

public:
    Q_INVOKABLE OffensiveHorse(const QString &name, int correct = -1, bool is_transferable = false);
    virtual QString subtype() const;
};

class DefensiveHorse : public Horse
{
    Q_OBJECT

public:
    Q_INVOKABLE DefensiveHorse(const QString &name, int correct = +1);
    virtual QString subtype() const;
};

class Treasure : public EquipCard
{
    Q_OBJECT

public:
    Treasure(const QString &name) : EquipCard(name)
    {
    }
    virtual QString subtype() const;

    virtual QSgsEnum::EquipLocation location() const;

    virtual QString commonEffectName() const;
};

#endif // BASE_H
