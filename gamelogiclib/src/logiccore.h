#ifndef LOGICCORE_H__
#define LOGICCORE_H__

#include "libqsgsgamelogicglobal.h"

class Card;
class CardFace;
class QSgsPackage;
class Skill;
class General;
class Player;

class GameLogicCorePrivate;

class LIBQSGSGAMELOGIC_EXPORT GameLogicCore final : public QObject
{
    Q_OBJECT
    
public:
    static GameLogicCore *instance();
    ~GameLogicCore();
    
    void addPackage(QSgsPackage *package);
    QList<const QSgsPackage *> packages() const;

    const General *general(const QString &name) const;
    QList<const General *> generals() const;
    QStringList generalNames() const;

    const Skill *skill(const QString &name) const;
    QStringList skillNames() const;
    const Skill *mainSkill(const Skill *subSkill) const;
    QList<const Skill *> relatedSkills(const Skill *mainSkill) const;

    const QList<Card *> &cards() const;


    const CardFace *cardFace(const QString &name) const;
    QStringList cardFaceNames() const;
    QList<const CardFace *> cardFaces() const;


private:
    GameLogicCore();

    Q_DECLARE_PRIVATE(GameLogicCore)
    GameLogicCorePrivate *d_ptr;
};

#endif
