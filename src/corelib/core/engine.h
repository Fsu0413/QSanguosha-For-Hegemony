/********************************************************************
    Copyright (c) 2013-2015 - Mogara

    This file is part of QSanguosha-Hegemony.

    This game is free software; you can redistribute it and/or
    modify it under the terms of the GNU General Public License as
    published by the Free Software Foundation; either version 3.0
    of the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    General Public License for more details.

    See the LICENSE file for more details.

    Mogara
    *********************************************************************/

#ifndef _ENGINE_H
#define _ENGINE_H

#include <QObject>
#include <QVersionNumber>

struct lua_State;

class QSgsEngine : public QObject
{
    Q_OBJECT

public:
    QSgsEngine();
    ~QSgsEngine();

    void addTranslationEntry(const char *key, const char *value);
    QString translate(const QString &toTranslate) const;
    QString translate(const QString &toTranslate, const QString &defaultValue) const;
    lua_State *getLuaState() const;

    int getMiniSceneCounts();

    void addPackage(Package *package);
    void addBanPackage(const QString &package_name);
    QList<const Package *> getPackages() const;

    QStringList getBanPackages() const;
    Card *cloneCard(const Card *card) const;
    Card *cloneCard(const QString &name, Card::Suit suit = Card::SuitToBeDecided, int number = -1, const QStringList &flags = QStringList()) const;
    SkillCard *cloneSkillCard(const QString &name) const;

    QVersionNumber getVersionNumber() const;
    QString getVersion() const;
    QString getVersionName() const;
    QString getMODName() const;
    QStringList getExtensions() const;
    QStringList getKingdoms() const;
    QColor getKingdomColor(const QString &kingdom) const;
    QMap<QString, QColor> getSkillColorMap() const;
    QColor getSkillColor(const QString &skill_type) const;
    QStringList getChattingEasyTexts() const;
    QString getSetupString() const;

    QMap<QString, QString> getAvailableModes() const;
    QString getModeName(const QString &mode) const;
    int getPlayerCount(const QString &mode) const;
    QString getRoles(const QString &mode) const;
    QStringList getRoleList(const QString &mode) const;

    const CardPattern *getPattern(const QString &name) const;
    bool matchExpPattern(const QString &pattern, const Player *player, const Card *card) const;
    Card::HandlingMethod getCardHandlingMethod(const QString &method_name) const;
    QList<const Skill *> getRelatedSkills(const QString &skill_name) const;
    const Skill *getMainSkill(const QString &skill_name) const;

    QStringList getModScenarioNames() const;
    void addScenario(Scenario *scenario);
    const Scenario *getScenario(const QString &name) const;
    void addPackage(const QString &name);

    const General *getGeneral(const QString &name) const;
    int getGeneralCount(bool include_banned = false) const;
    const Skill *getSkill(const QString &skill_name) const;
    const Skill *getSkill(const EquipCard *card) const;
    QStringList getSkillNames() const;
    const TriggerSkill *getTriggerSkill(const QString &skill_name) const;
    const ViewAsSkill *getViewAsSkill(const QString &skill_name) const;
    QList<const DistanceSkill *> getDistanceSkills() const;
    QList<const MaxCardsSkill *> getMaxCardsSkills() const;
    QList<const TargetModSkill *> getTargetModSkills() const;
    QList<const TriggerSkill *> getGlobalTriggerSkills() const;
    QList<const AttackRangeSkill *> getAttackRangeSkills() const;
    void addSkills(const QList<const Skill *> &skills);

    int getCardCount() const;
    const Card *getEngineCard(int cardId) const;
    // @todo: consider making this const Card *
    Card *getCard(int cardId);
    WrappedCard *getWrappedCard(int cardId);

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
    QStringList getRandomGenerals(int count, const QSet<QString> &ban_set = QSet<QString>()) const;
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
    QList<int> getRandomCards() const;
    QString getRandomGeneralName() const;
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
    QStringList getLimitedGeneralNames() const;
    QStringList getGeneralNames() const;
    QList<const General *> getGeneralList() const;

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
    QHash<QString, QString> m_className2objectName;
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

    QList<const Package *> m_packages;
    QList<Card *> m_cards;
    QStringList m_lordList;
    QSet<QString> m_banPackage;
    QHash<QString, Scenario *> m_scenarios;
    QHash<QString, Scenario *> m_miniScenes;
    Scenario *m_customScene;

    lua_State *m_lua;

   // QHash<QString, QString> luaBasicCard_className2objectName;
    QHash<QString, const LuaBasicCard *> m_luaBasicCards;
   // QHash<QString, QString> luaTrickCard_className2objectName;
    QHash<QString, const LuaTrickCard *> m_luaTrickCards;
   // QHash<QString, QString> luaWeapon_className2objectName;
    QHash<QString, const LuaWeapon*> m_luaWeapons;
   // QHash<QString, QString> luaArmor_className2objectName;
    QHash<QString, const LuaArmor *> m_luaArmors;
    //QHash<QString, QString> luaTreasure_className2objectName;
    QHash<QString, const LuaTreasure *> m_luaTreasures;

    QMultiMap<QString, QString> m_spConvertPairs;


//#if 1

//public:

//    void registerRoom(QObject *room);
//    void unregisterRoom();
//    QObject *currentRoomObject();
//    Room *currentRoom();
//    RoomState *currentRoomState();

//private:

    // todo: delete me after the code has completely finished

    //QMutex m_mutex;
    //QHash<QThread *, QObject *> m_rooms;

    //TransferSkill *transfer;
//#endif
};

static inline QVariant GetConfigFromLuaState(lua_State *L, const char *key)
{
    return GetValueFromLuaState(L, "config", key);
}

extern QSgsEngine *Sanguosha;

#endif
