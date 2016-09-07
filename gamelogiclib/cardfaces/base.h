#ifndef BASE_H
#define BASE_H

#include "libqsgsgamelogicglobal.h"
#include "cardface.h"
#include "structs.h"

class BasicCard : public CardFace
{


public:
    BasicCard(const QString &name);
    QString type() const;
    QSgsEnum::CardType typeId() const;
};

class TrickCard : public CardFace
{


public:
    TrickCard(const QString &name);
    void setCancelable(bool cancelable);

    QString type() const;
    QSgsEnum::CardType typeId() const;
    bool isCancelable(const CardEffectStruct &effect) const;

private:
    bool m_cancelable;
};

class InstanceTrick : public TrickCard
{

public:
    InstanceTrick(const QString &name) :TrickCard(name){

    }
    QString subtype() const;
};

class DelayedTrick : public TrickCard
{


public:
    DelayedTrick(const QString &name, bool movable = false);

    void onNullified(Player *target) const;

    void onUse(Room *room, const CardUseStruct &card_use) const;
    void use(Room *room, Player *source, QList<Player *> &targets) const;
    QString subtype() const;
    void onEffect(const CardEffectStruct &effect) const;
    virtual void takeEffect(Player *target) const = 0;

protected:
    JudgeStruct m_judge;

private:
    bool m_movable;
};

class EquipCard : public CardFace
{


public:

    EquipCard(const QString &name);

    QString type() const;
    QSgsEnum::CardType typeId() const;

    bool isAvailable(const Player *player) const;
    void onUse(Room *room, const CardUseStruct &card_use) const;
    void use(Room *room, Player *source, QList<Player *> &targets) const;

    void onInstall(Player *player) const;
    void onUninstall(Player *player) const;

    virtual QSgsEnum::EquipLocation location() const = 0;
};

class Weapon : public EquipCard
{


public:
    Weapon(const QString &name, int range);
    int range() const;

    QString subtype() const;

    QSgsEnum::EquipLocation location() const;
    QString commonEffectName() const;

protected:
    int m_range;
};

class Armor : public EquipCard
{


public:
    Armor(const QString &name);
    QString subtype() const;

    QSgsEnum::EquipLocation location() const;
    QString commonEffectName() const;
};

class Horse : public EquipCard
{


public:
    Horse(const QString &name, int correct);
    int correctNum() const;

    QSgsEnum::EquipLocation location() const;
    /*void onInstall(Player *player) const;
    void onUninstall(Player *player) const;*/

    QString commonEffectName() const;

private:
    int m_correct;
};

class OffensiveHorse : public Horse
{


public:
    Q_INVOKABLE OffensiveHorse(const QString &name, int correct = -1, bool is_transferable = false);
    QString subtype() const;
};

class DefensiveHorse : public Horse
{


public:
    Q_INVOKABLE DefensiveHorse(const QString &name, int correct = +1);
    QString subtype() const;
};

class Treasure : public EquipCard
{


public:
    Treasure(const QString &name);
    QString subtype() const;

    QSgsEnum::EquipLocation location() const;

    QString commonEffectName() const;
};

#endif // BASE_H
