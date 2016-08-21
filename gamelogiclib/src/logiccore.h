#ifndef LOGICCORE_H__
#define LOGICCORE_H__

#include "libqsgsgamelogicglobal.h"

#include "card.h"
class QSgsPackage;
class Skill;
class General;


class GameLogicCore: public QObject
{
    Q_OBJECT
    
public:
    
    void addPackage(QSgsPackage *package);
    void addBanPackage(const QString &package_name);
    QList<const QSgsPackage *> packages() const;
    
    int miniSceneCounts();
    QStringList banPackages() const;
    Card *cloneCard(const Card *card) const;
    Card *cloneCard(const QString &name, Card::Suit suit = Card::Tbd, int number = -1, const QStringList &flags = QStringList()) const;
    // SkillCard *cloneSkillCard(const QString &name) const;
    QStringList extensions() const;
    QStringList kingdoms() const;
    QColor kingdomColor(const QString &kingdom) const;
    QMap<QString, QColor> skillColorMap() const;
    QColor skillColor(const QString &skill_type) const;
    QStringList chattingEasyTexts() const;
    QString setupString() const;

    QMap<QString, QString> availableModes() const;
    QString modeName(const QString &mode) const;
    int playerCount(const QString &mode) const;
    QString roles(const QString &mode) const;
    QStringList roleList(const QString &mode) const;

    const CardPattern *pattern(const QString &name) const;
    bool matchExpPattern(const QString &pattern, const Player *player, const Card *card) const;
    QList<const Skill *> relatedSkills(const QString &skill_name) const;
    const Skill *mainSkill(const QString &skill_name) const;

    QStringList modScenarioNames() const;
    void addScenario(Scenario *scenario);
    const Scenario *scenario(const QString &name) const;
    void addPackage(const QString &name);

    const General *general(const QString &name) const;
    int generalCount(bool include_banned = false) const;
    const Skill *skill(const QString &skill_name) const;
    const Skill *skill(const EquipCard *card) const;
    QStringList skillNames() const;
    const TriggerSkill *triggerSkill(const QString &skill_name) const;
    const ViewAsSkill *viewAsSkill(const QString &skill_name) const;
    QList<const DistanceSkill *> distanceSkills() const;
    QList<const MaxCardsSkill *> maxCardsSkills() const;
    QList<const TargetModSkill *> targetModSkills() const;
    QList<const TriggerSkill *> globalTriggerSkills() const;
    QList<const AttackRangeSkill *> attackRangeSkills() const;
    void addSkills(const QList<const Skill *> &skills);

    int cardCount() const;
    //const Card *getEngineCard(int cardId) const;
    // @todo: consider making this const Card *
    Card *card(int cardId);
    //************************************
    // Method:    getRandomGenerals
    // FullName:  Engine::getRandomGenerals
    // Access:    public
    // Returns:   QT_NAMESPACE::QStringList
    // Qualifier: const
    // Parameter: int count
    // Parameter: const QSet<QString> & ban_set
    // Description: Get [count] available generals and no one is in [ban_set].
    //
    // Last Updated By Yanguam Siliagim
    // To use a proper way to convert generals and cards
    //
    // Mogara
    // March 17 2014
    //************************************
    QStringList randomGenerals(int count, const QSet<QString> &ban_set = QSet<QString>()) const;
    //************************************
    // Method:    getRandomCards
    // FullName:  Engine::getRandomCards
    // Access:    public
    // Returns:   QList<int>
    // Qualifier: const
    // Description: Get IDs of all the available cards.
    //
    // Last Updated By Yanguam Siliagim
    // To use a proper way to convert generals and cards
    //
    // Mogara
    // March 17 2014
    //************************************
    QList<int> randomCards() const;
    QString randomGeneralName() const;
    //************************************
    // Method:    getLimitedGeneralNames
    // FullName:  Engine::getLimitedGeneralNames
    // Access:    public
    // Returns:   QT_NAMESPACE::QStringList
    // Qualifier: const
    // Description: It was designed to get the list of all available generals.
    //
    // Last Updated By Yanguam Siliagim
    // To use a proper way to convert generals and cards
    //
    // Mogara
    // March 17 2014
    //************************************
    QStringList limitedGeneralNames() const;
    QStringList generalNames() const;
    QList<const General *> generalList() const;

//    void playSystemAudioEffect(const QString &name) const;
//    void playAudioEffect(const QString &filename) const;
//    void playSkillAudioEffect(const QString &skill_name, int index) const;

    const ProhibitSkill *isProhibited(const Player *from, const Player *to, const Card *card, const QList<const Player *> &others = QList<const Player *>()) const;
    int correctDistance(const Player *from, const Player *to) const;
    int correctMaxCards(const ServerPlayer *target, bool fixed = false, MaxCardsType::MaxCardsCount type = MaxCardsType::Max) const;
    int correctCardTarget(const TargetModSkill::ModType type, const Player *from, const Card *card) const;
    int correctAttackRange(const Player *target, bool include_weapon = true, bool fixed = false) const;

//    QString getCurrentCardUsePattern();
//    CardUseStruct::CardUseReason getCurrentCardUseReason();

    bool isGeneralHidden(const QString &general_name) const;

    //TransferSkill *getTransfer() const;

private:
    void _loadMiniScenarios();
    void _loadModScenarios();

    QHash<QString, QString> m_translations;
    QList<const General *> m_generalList;
    QHash<QString, const General *> m_generalHash;
    QHash<QString, const QMetaObject *> m_metaobjects;
    //QHash<QString, QString> m_className2objectName;
    QHash<QString, const Skill *> m_skills;
    QMap<QString, QString> m_modes;
    QMultiMap<QString, QString> m_relatedSkills;
    mutable QMap<QString, const CardPattern *> m_patterns;
    mutable QList<ExpPattern *> m_enginePatterns;

    // special skills
    QList<const ProhibitSkill *> m_prohibitSkills;
    QList<const DistanceSkill *> m_distanceSkills;
    QList<const MaxCardsSkill *> m_maxcardsSkills;
    QList<const TargetModSkill *> m_targetmodSkills;
    QList<const AttackRangeSkill *> m_attackrangeSkills;
    QList<const TriggerSkill *> m_globalTriggerSkills;

    QList<const QSgsPackage *> m_packages;
    QList<Card *> m_cards;
    QStringList m_lordList;
    QSet<QString> m_banPackage;
    QHash<QString, Scenario *> m_scenarios;
    QHash<QString, Scenario *> m_miniScenes;
    Scenario *m_customScene;

//    QHash<QString, QString> luaBasicCard_className2objectName;
//    QHash<QString, const LuaBasicCard *> m_luaBasicCards;
//    QHash<QString, QString> luaTrickCard_className2objectName;
//    QHash<QString, const LuaTrickCard *> m_luaTrickCards;
//    QHash<QString, QString> luaWeapon_className2objectName;
//    QHash<QString, const LuaWeapon*> m_luaWeapons;
//    QHash<QString, QString> luaArmor_className2objectName;
//    QHash<QString, const LuaArmor *> m_luaArmors;
//    QHash<QString, QString> luaTreasure_className2objectName;
//    QHash<QString, const LuaTreasure *> m_luaTreasures;

    QMultiMap<QString, QString> m_spConvertPairs;

}

#endif
