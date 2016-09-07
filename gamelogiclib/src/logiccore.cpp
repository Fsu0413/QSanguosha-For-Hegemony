
#include "logiccore.h"

//GameLogicCore *GameLogicCore::instance()
//{
//    static GameLogicCore core;
//    return &core;
//}

//GameLogicCore::GameLogicCore()
//{
//    QStringList stringlist_sp_convert = GetConfigFromLuaState(lua, "convert_pairs").toStringList();
//    foreach (const QString &cv_pair, stringlist_sp_convert) {
//        QStringList pairs = cv_pair.split("->");
//        QStringList cv_to = pairs.at(1).split("|");
//        foreach(const QString &to, cv_to)
//            sp_convert_pairs.insertMulti(pairs.at(0), to);
//    }

//    QStringList package_names = GetConfigFromLuaState(lua, "package_names").toStringList();
//    foreach(const QString &name, package_names)
//        addPackage(name);

//    _loadMiniScenarios();
//    _loadModScenarios();
//    m_customScene = new CustomScenario();

//    DoLuaScript(lua, "lua/sanguosha.lua");

//    // available game modes
//    modes["02p"] = tr("2 players");
//    modes["03p"] = tr("3 players");
//    modes["04p"] = tr("4 players");
//    modes["05p"] = tr("5 players");
//    modes["06p"] = tr("6 players");
//    modes["07p"] = tr("7 players");
//    modes["08p"] = tr("8 players");
//    modes["09p"] = tr("9 players");
//    modes["10p"] = tr("10 players");

//}

//int GameLogicCore::miniSceneCounts()
//{
//    return m_miniScenes.size();
//}

//void GameLogicCore::_loadMiniScenarios()
//{
//    static bool loaded = false;
//    if (loaded) return;
//    int i = 1;
//    while (true) {
//        if (!QFile::exists(QString("etc/customScenes/%1.txt").arg(QString::number(i))))
//            break;

//        QString sceneKey = QString(MiniScene::S_KEY_MINISCENE).arg(QString::number(i));
//        m_miniScenes[sceneKey] = new LoadedScenario(QString::number(i));
//        i++;
//    }
//    loaded = true;
//}

//void GameLogicCore::_loadModScenarios()
//{
//    //wait for a new scenario
//    addScenario(new JiangeDefenseScenario());
//}

//void GameLogicCore::addPackage(const QString &name)
//{
//    QSgsPackage *pack = PackageAdder::packages()[name];
//    if (pack)
//        addPackage(pack);
//    else
//        qWarning("Package %s cannot be loaded!", qPrintable(name));
//}

//QStringList GameLogicCore::modScenarioNames() const
//{
//    return m_scenarios.keys();
//}

//void GameLogicCore::addScenario(Scenario *scenario)
//{
//    QString key = scenario->objectName();
//    if (m_scenarios.contains(key))
//        return;

//    m_scenarios[key] = scenario;
//    addPackage(scenario);
//}

//const Scenario *GameLogicCore::scenario(const QString &name) const
//{
//    if (m_scenarios.contains(name))
//        return m_scenarios[name];
//    else if (m_miniScenes.contains(name))
//        return m_miniScenes[name];
//    else if (name == "custom_scenario")
//        return m_customScene;
//    else
//        return nullptr;
//}

//void GameLogicCore::addSkills(const QList<const Skill *> &all_skills)
//{
//    foreach (const Skill *skill, all_skills) {
//        if (!skill) {
//            qWarning(tr("The engine tries to add an invalid skill"));
//            continue;
//        }
//        if (skills.contains(skill->objectName()))
//            qWarning(tr("Duplicated skill : %1").arg(skill->objectName()));

//        skills.insert(skill->objectName(), skill);

//        if (skill->inherits("ProhibitSkill"))
//            prohibit_skills << qobject_cast<const ProhibitSkill *>(skill);
//        else if (skill->inherits("DistanceSkill"))
//            distance_skills << qobject_cast<const DistanceSkill *>(skill);
//        else if (skill->inherits("MaxCardsSkill"))
//            maxcards_skills << qobject_cast<const MaxCardsSkill *>(skill);
//        else if (skill->inherits("TargetModSkill"))
//            targetmod_skills << qobject_cast<const TargetModSkill *>(skill);
//        else if (skill->inherits("AttackRangeSkill"))
//            attackrange_skills << qobject_cast<const AttackRangeSkill *>(skill);
//        else if (skill->inherits("TriggerSkill")) {
//            const TriggerSkill *trigger_skill = qobject_cast<const TriggerSkill *>(skill);
//            if (trigger_skill && trigger_skill->isGlobal())
//                global_trigger_skills << trigger_skill;
//        }
//    }
//}

//QList<const DistanceSkill *> GameLogicCore::distanceSkills() const
//{
//    return distance_skills;
//}

//QList<const MaxCardsSkill *> GameLogicCore::maxCardsSkills() const
//{
//    return maxcards_skills;
//}

//QList<const TargetModSkill *> GameLogicCore::targetModSkills() const
//{
//    return targetmod_skills;
//}

//QList<const AttackRangeSkill *> GameLogicCore::attackRangeSkills() const
//{
//    return attackrange_skills;
//}

//QList<const TriggerSkill *> GameLogicCore::globalTriggerSkills() const
//{
//    return global_trigger_skills;
//}

//void GameLogicCore::addPackage(QSgsPackage *package)
//{
//    foreach (const QSgsPackage *p, packages) {
//        if (p->objectName() == package->objectName())
//            return;
//    }

//    packages << package;
//    package->setParent(this);
//    sp_convert_pairs.unite(package->getConvertPairs());
//    patterns.unite(package->getPatterns());
//    related_skills.unite(package->getRelatedSkills());

//    package->registerCards();
//    foreach (Card *card, package->cards()) {
//        card->setId(cards.length());
//        m_cards << card;
//    }
    
//////        if (card->isKindOf("LuaBasicCard")) {
//////            const LuaBasicCard *lcard = qobject_cast<const LuaBasicCard *>(card);
//////            Q_ASSERT(lcard != nullptr);
//////            //luaBasicCard_className2objectName.insert(lcard->getClassName(), lcard->objectName());
//////            if (!luaBasicCards.contains(lcard->getClassName()))
//////                luaBasicCards.insert(lcard->getClassName(), lcard->clone());
//////        } else if (card->isKindOf("LuaTrickCard")) {
//////            const LuaTrickCard *lcard = qobject_cast<const LuaTrickCard *>(card);
//////            Q_ASSERT(lcard != nullptr);
//////            //luaTrickCard_className2objectName.insert(lcard->getClassName(), lcard->objectName());
//////            if (!luaTrickCards.contains(lcard->getClassName()))
//////                luaTrickCards.insert(lcard->getClassName(), lcard->clone());
//////        } else if (card->isKindOf("LuaWeapon")) {
//////            const LuaWeapon *lcard = qobject_cast<const LuaWeapon *>(card);
//////            Q_ASSERT(lcard != nullptr);
//////            //luaWeapon_className2objectName.insert(lcard->getClassName(), lcard->objectName());
//////            if (!luaWeapons.contains(lcard->getClassName()))
//////                luaWeapons.insert(lcard->getClassName(), lcard->clone());
//////        } else if (card->isKindOf("LuaArmor")) {
//////            const LuaArmor *lcard = qobject_cast<const LuaArmor *>(card);
//////            Q_ASSERT(lcard != nullptr);
//////            //luaArmor_className2objectName.insert(lcard->getClassName(), lcard->objectName());
//////            if (!luaArmors.contains(lcard->getClassName()))
//////                luaArmors.insert(lcard->getClassName(), lcard->clone());
//////        } else if (card->isKindOf("LuaTreasure")) {
//////            const LuaTreasure *lcard = qobject_cast<const LuaTreasure *>(card);
//////            Q_ASSERT(lcard != nullptr);
//////            //luaTreasure_className2objectName.insert(lcard->getClassName(), lcard->objectName());
//////            if (!luaTreasures.contains(lcard->getClassName()))
//////                luaTreasures.insert(lcard->getClassName(), lcard->clone());
//////        } else {
////            QString class_name = card->metaObject()->className();
////            metaobjects.insert(class_name, card->metaObject());
////            className2objectName.insert(class_name, card->objectName());
////        }
////    }

//    addSkills(package->getSkills());

//    QList<General *> all_generals = package->findChildren<General *>();
//    foreach (General *general, all_generals) {
//        addSkills(general->findChildren<const Skill *>());
//        foreach (const QString &skill_name, general->extraSkillSet()) {
//            if (skill_name.startsWith("#")) continue;
//            foreach(const Skill *related, relatedSkills(skill_name))
//                general->addSkill(related->objectName());
//        }
//        generalList << general;
//        generalHash.insert(general->objectName(), general);
//        if (isGeneralHidden(general->objectName())) continue;
//        if (general->isLord()) lord_list << general->objectName();
//    }

//    QList<const QMetaObject *> metas = package->getMetaObjects();
//    foreach(const QMetaObject *meta, metas)
//        metaobjects.insert(meta->className(), meta);
//}

//void GameLogicCore::addBanPackage(const QString &package_name)
//{
//    ban_package.insert(package_name);
//}

//QList<const QSgsPackage *> GameLogicCore::packages() const
//{
//    return packages;
//}

//QStringList GameLogicCore::banPackages() const
//{
//    if (qApp->arguments().contains("-server"))
//        return Config.BanPackages;
//    else
//        return ban_package.toList();
//}


//const CardPattern *GameLogicCore::pattern(const QString &name) const
//{
//    const CardPattern *ptn = patterns.value(name, nullptr);
//    if (ptn) return ptn;

//    ExpPattern *expptn = new ExpPattern(name);
//    enginePatterns << expptn;
//    patterns.insert(name, expptn);

//    return expptn;
//}

//bool GameLogicCore::matchExpPattern(const QString &pattern, const Player *player, const Card *card) const
//{
//    ExpPattern p(pattern);
//    return p.match(player, card);
//}

//Card::HandlingMethod GameLogicCore::cardHandlingMethod(const QString &method_name) const
//{
//    if (method_name == "use")
//        return Card::MethodUse;
//    else if (method_name == "response")
//        return Card::MethodResponse;
//    else if (method_name == "discard")
//        return Card::MethodDiscard;
//    else if (method_name == "recast")
//        return Card::MethodRecast;
//    else if (method_name == "pindian")
//        return Card::MethodPindian;
//    else if (method_name == "none")
//        return Card::MethodNone;
//    else {
//        Q_ASSERT(false);
//        return Card::MethodNone;
//    }
//}

//QList<const Skill *> GameLogicCore::relatedSkills(const QString &skill_name) const
//{
//    QList<const Skill *> skills;
//    foreach(const QString &name, related_skills.values(skill_name))
//        skills << skill(name);

//    return skills;
//}

//const Skill *GameLogicCore::mainSkill(const QString &skill_name) const
//{
//    const Skill *skill = skill(skill_name);
//    if (!skill || skill->isVisible() || related_skills.contains(skill_name)) return skill;
//    foreach (const QString &key, related_skills.keys()) {
//        foreach(const QString &name, related_skills.values(key))
//            if (name == skill_name) return skill(key);
//    }
//    return skill;
//}

//const General *GameLogicCore::general(const QString &name) const
//{
//    if (generalHash.contains(name))
//        return generalHash.value(name);
//    else
//        return nullptr;
//}

//int GameLogicCore::generalCount(bool include_banned) const
//{
//    if (include_banned)
//        return generalList.size();

//    int total = generalList.size();
//    foreach (const General *general, generalList) {
//        if (banPackages().contains(general->package()))
//            total--;
//    }

//    return total;
//}

//const Skill *GameLogicCore::skill(const QString &skill_name) const
//{

//}

////void GameLogicCore::registerRoom(QObject *room)
////{
////    m_mutex.lock();
////    m_rooms[QThread::currentThread()] = room;
////    m_mutex.unlock();
////}

////void GameLogicCore::unregisterRoom()
////{
////    m_mutex.lock();
////    m_rooms.remove(QThread::currentThread());
////    m_mutex.unlock();
////}

////QObject *GameLogicCore::currentRoomObject()
////{
////    QObject *room = nullptr;
////    m_mutex.lock();
////    room = m_rooms[QThread::currentThread()];
////    Q_ASSERT(room);
////    m_mutex.unlock();
////    return room;
////}

////Room *GameLogicCore::currentRoom()
////{
////    QObject *roomObject = currentRoomObject();
////    Room *room = qobject_cast<Room *>(roomObject);
////    Q_ASSERT(room != nullptr);
////    return room;
////}

////RoomState *GameLogicCore::currentRoomState()
////{
////    QObject *roomObject = currentRoomObject();
////    Room *room = qobject_cast<Room *>(roomObject);
////    if (room != nullptr) {
////        return room->getRoomState();
////    } else {
////        Client *client = qobject_cast<Client *>(roomObject);
////        Q_ASSERT(client != nullptr);
////        return client->getRoomState();
////    }
////}

////QString GameLogicCore::getCurrentCardUsePattern()
////{
////    return currentRoomState()->getCurrentCardUsePattern();
////}

////CardUseStruct::CardUseReason GameLogicCore::getCurrentCardUseReason()
////{
////    return currentRoomState()->getCurrentCardUseReason();
////}

//bool GameLogicCore::isGeneralHidden(const QString &general_name) const
//{
//    const General *general = general(general_name);
//    if (!general) return false;
//    if (!general->isHidden())
//        return Config.ExtraHiddenGenerals.contains(general_name);
//    else
//        return !Config.RemovedHiddenGenerals.contains(general_name);
//}

//TransferSkill *GameLogicCore::getTransfer() const
//{
//   // return transfer;
//    return nullptr;
//}

//Card *GameLogicCore::wrappedCard(int cardId)
//{
//    Card *card = card(cardId);
//    Card *wrappedCard = qobject_cast<Card *>(card);
//    Q_ASSERT(wrappedCard != nullptr && wrappedCard->id() == cardId);
//    return wrappedCard;
//}

//Card *GameLogicCore::card(int cardId)
//{
////    Card *card = nullptr;
////    if (cardId < 0 || cardId >= m_cards.length())
////        return nullptr;
////    //QObject *room = currentRoomObject();
////   // Q_ASSERT(room);
////    //Room *serverRoom = qobject_cast<Room *>(room);
////   // if (serverRoom != nullptr) {
////       // card = serverRoom->getCard(cardId);
////   // } else {
////        Client *clientRoom = qobject_cast<Client *>(room);
////        Q_ASSERT(clientRoom != nullptr);
////        card = clientRoom->getCard(cardId);
////   // }
////    Q_ASSERT(card);
////    return card;
//    if (cardId == Card::S_UNKNOWN_CARD_ID)
//        return nullptr;
//    else if (cardId < 0 || cardId >= m_cards.length()) {
//        Q_ASSERT(false);
//        return nullptr;
//    } else {
//        Q_ASSERT(m_cards[cardId] != nullptr);
//        return m_cards[cardId];
//    }
//}

////const Card *GameLogicCore::getEngineCard(int cardId) const
////{
////    if (cardId == Card::S_UNKNOWN_CARD_ID)
////        return nullptr;
////    else if (cardId < 0 || cardId >= m_cards.length()) {
////        Q_ASSERT(false);
////        return nullptr;
////    } else {
////        Q_ASSERT(m_cards[cardId] != nullptr);
////        return m_cards[cardId];
////    }
////}

//Card *GameLogicCore::cloneCard(const Card *card) const
//{
//    Q_ASSERT(card->metaObject() != nullptr);
//    QString name = card->metaObject()->className();
//    Card *result = cloneCard(name, card->suit(), card->number(), card->flags());
//    if (result == nullptr)
//        return nullptr;
//    result->setId(card->effectiveId());
//    result->setSkillName(card->skillName(false));
//    result->setObjectName(card->objectName());
//    return result;
//}

//Card *GameLogicCore::cloneCard(const QString &name, Card::Suit suit, int number, const QStringList &flags) const
//{
//    Card *card = nullptr;
////    if (luaBasicCard_className2objectName.contains(name)) {
////        const LuaBasicCard *lcard = luaBasicCards.value(name, nullptr);
////        if (!lcard) return nullptr;
////        card = lcard->clone(suit, number);
////    } else if (luaBasicCard_className2objectName.values().contains(name)) {
////        QString class_name = luaBasicCard_className2objectName.key(name, name);
////        const LuaBasicCard *lcard = luaBasicCards.value(class_name, nullptr);
////        if (!lcard) return nullptr;
////        card = lcard->clone(suit, number);
////    } else if (luaTrickCard_className2objectName.contains(name)) {
////        const LuaTrickCard *lcard = luaTrickCards.value(name, nullptr);
////        if (!lcard) return nullptr;
////        card = lcard->clone(suit, number);
////    } else if (luaTrickCard_className2objectName.values().contains(name)) {
////        QString class_name = luaTrickCard_className2objectName.key(name, name);
////        const LuaTrickCard *lcard = luaTrickCards.value(class_name, nullptr);
////        if (!lcard) return nullptr;
////        card = lcard->clone(suit, number);
////    } else if (luaWeapon_className2objectName.contains(name)) {
////        const LuaWeapon *lcard = luaWeapons.value(name, nullptr);
////        if (!lcard) return nullptr;
////        card = lcard->clone(suit, number);
////    } else if (luaWeapon_className2objectName.values().contains(name)) {
////        QString class_name = luaWeapon_className2objectName.key(name, name);
////        const LuaWeapon *lcard = luaWeapons.value(class_name, nullptr);
////        if (!lcard) return nullptr;
////        card = lcard->clone(suit, number);
////    } else if (luaArmor_className2objectName.contains(name)) {
////        const LuaArmor *lcard = luaArmors.value(name, nullptr);
////        if (!lcard) return nullptr;
////        card = lcard->clone(suit, number);
////    } else if (luaArmor_className2objectName.values().contains(name)) {
////        QString class_name = luaArmor_className2objectName.key(name, name);
////        const LuaArmor *lcard = luaArmors.value(class_name, nullptr);
////        if (!lcard) return nullptr;
////        card = lcard->clone(suit, number);
////    } else if (luaTreasure_className2objectName.contains(name)) {
////        const LuaTreasure *lcard = luaTreasures.value(name, nullptr);
////        if (!lcard) return nullptr;
////        card = lcard->clone(suit, number);
////    } else if (luaTreasure_className2objectName.values().contains(name)) {
////        QString class_name = luaTreasure_className2objectName.key(name, name);
////        const LuaTreasure *lcard = luaTreasures.value(class_name, nullptr);
////        if (!lcard) return nullptr;
////        card = lcard->clone(suit, number);
////    } else {
//        const QMetaObject *meta = metaobjects.value(name, nullptr);
//        if (meta == nullptr)
//            meta = metaobjects.value(className2objectName.key(name, QString()), nullptr);
//        if (meta) {
//            QObject *card_obj = meta->newInstance(Q_ARG(Card::Suit, suit), Q_ARG(int, number));
//            card_obj->setObjectName(className2objectName.value(name, name));
//            card = qobject_cast<Card *>(card_obj);
//        }
////    }
//    if (!card) return nullptr;
//    card->clearFlags();
//    if (!flags.isEmpty()) {
//        foreach(const QString &flag, flags)
//            card->setFlags(flag);
//    }
//    return card;
//}

//SkillCard *GameLogicCore::cloneSkillCard(const QString &name) const
//{
//    const QMetaObject *meta = m_metaobjects.value(name, nullptr);
//    if (meta) {
//        QObject *card_obj = meta->newInstance();
//        SkillCard *card = qobject_cast<SkillCard *>(card_obj);
//        return card;
//    } else {
//        return nullptr;
//    }
//}


//QStringList GameLogicCore::extensions() const
//{
//    QStringList extensions;
//    foreach (const QSgsPackage *package, m_packages) {
//        if (package->inherits("Scenario"))
//            continue;

//        extensions << package->objectName();
//    }
//    return extensions;
//}

//QStringList GameLogicCore::kingdoms() const
//{
//    static QStringList kingdoms;
//    if (kingdoms.isEmpty())
//        kingdoms = GetConfigFromLuaState(lua, "kingdoms").toStringList();

//    return kingdoms;
//}

//QColor GameLogicCore::kingdomColor(const QString &kingdom) const
//{
//    static QMap<QString, QColor> color_map;
//    if (color_map.isEmpty()) {
//        QVariantMap map = GetValueFromLuaState(lua, "config", "kingdom_colors").toMap();
//        QMapIterator<QString, QVariant> itor(map);
//        while (itor.hasNext()) {
//            itor.next();
//            QColor color(itor.value().toString());
//            if (!color.isValid()) {
//                qWarning("Invalid color for kingdom %s", qPrintable(itor.key()));
//                color = QColor(128, 128, 128);
//            }
//            color_map[itor.key()] = color;
//        }

//        Q_ASSERT(!color_map.isEmpty());
//    }

//    return color_map.value(kingdom);
//}

//QMap<QString, QColor> GameLogicCore::skillColorMap() const
//{
//    static QMap<QString, QColor> color_map;
//    if (color_map.isEmpty()) {
//        QVariantMap map = GetValueFromLuaState(lua, "config", "skill_colors").toMap();
//        QMapIterator<QString, QVariant> itor(map);
//        while (itor.hasNext()) {
//            itor.next();
//            QColor color(itor.value().toString());
//            if (!color.isValid()) {
//                qWarning("Invalid color for skill %s", qPrintable(itor.key()));
//                color = QColor(128, 128, 128);
//            }
//            color_map[itor.key()] = color;
//        }

//        Q_ASSERT(!color_map.isEmpty());
//    }

//    return color_map;
//}

//QColor GameLogicCore::skillColor(const QString &skill_type) const
//{
//    return GameLogicCore::skillColorMap().value(skill_type);
//}

//QStringList GameLogicCore::chattingEasyTexts() const
//{
//    static QStringList easy_texts;
//    if (easy_texts.isEmpty())
//        easy_texts = GetConfigFromLuaState(lua, "easy_text").toStringList();

//    return easy_texts;
//}

//QString GameLogicCore::setupString() const
//{
//    int timeout = Config.OperationNoLimit ? 0 : Config.OperationTimeout;
//    QString flags;
//    if (Config.RandomSeat)
//        flags.append("R");
//    if (Config.EnableCheat)
//        flags.append("C");
//    if (Config.EnableCheat && Config.FreeChoose)
//        flags.append("F");
//    if (Config.ForbidAddingRobot)
//        flags.append("A");
//    if (Config.DisableChat)
//        flags.append("M");
//    if (Config.RewardTheFirstShowingPlayer)
//        flags.append("S");

//    QString server_name = Config.ServerName;
//    QStringList setup_items;
//    setup_items << server_name
//        << Config.GameMode
//        << QString::number(timeout)
//        << QString::number(Config.NullificationCountDown)
//        << Sanguosha->banPackages().join("+")
//        << flags;

//    return setup_items.join(":");
//}

//QMap<QString, QString> GameLogicCore::availableModes() const
//{
//    return m_modes;
//}

//QString GameLogicCore::modeName(const QString &mode) const
//{
//    if (m_modes.contains(mode))
//        return m_modes.value(mode);
//    else
//        return tr("%1 [Scenario mode]").arg(translate(mode));
//}

//int GameLogicCore::playerCount(const QString &mode) const
//{
//    if (m_modes.contains(mode)) {
//        QRegExp rx("(\\d+)");
//        int index = rx.indexIn(mode);
//        if (index != -1)
//            return rx.capturedTexts().first().toInt();
//    } else {
//        // scenario mode
//        const Scenario *scenario = scenario(mode);
//        Q_ASSERT(scenario);
//        return scenario->playerCount();
//    }

//    return -1;
//}

//QString GameLogicCore::roles(const QString &mode) const
//{
//    int n = playerCount(mode);

//    if (modes.contains(mode)) {
//        static const char *table[] = {
//            "",
//            "",

//            "ZN", // 2
//            "ZNN", // 3
//            "ZNNN", // 4
//            "ZNNNN", // 5
//            "ZNNNNN", // 6
//            "ZNNNNNN", // 7
//            "ZNNNNNNN", // 8
//            "ZNNNNNNNN", // 9
//            "ZNNNNNNNNN" // 10
//        };

//        QString rolechar = table[n];

//        return rolechar;
//    } else {
//        const Scenario *scenario = scenario(mode);
//        if (scenario)
//            return scenario->getRoles();
//    }
//    return QString();
//}

//QStringList GameLogicCore::roleList(const QString &mode) const
//{
//    QString roles = roles(mode);

//    QStringList role_list;
//    for (int i = 0; roles[i] != '\0'; i++) {
//        QString role;
//        switch (roles[i].toLatin1()) {
//            case 'Z': role = "lord"; break;
//            case 'C': role = "loyalist"; break;
//            case 'N': role = "renegade"; break;
//            case 'F': role = "rebel"; break;
//        }
//        role_list << role;
//    }

//    return role_list;
//}

//int GameLogicCore::cardCount() const
//{
//    return cards.length();
//}

//QStringList GameLogicCore::generalNames() const
//{
//    QStringList generalNames;
//    foreach (const General *general, m_generalList)
//        generalNames << general->objectName();
//    return generalNames;
//}

//QList<const General *> GameLogicCore::generalList() const
//{
//    return m_generalList;
//}

//QStringList GameLogicCore::limitedGeneralNames() const
//{
//    //for later use
//    QStringList general_names = generalNames();
//    QStringList general_names_copy = general_names;

//    foreach (const QString &name, general_names_copy) {
//        if (isGeneralHidden(name) || banPackages().contains(general(name)->package()))
//            general_names.removeOne(name);
//    }

//    QStringList banned_generals = Config.value("Banlist/Generals", "").toStringList();
//    foreach (const QString &banned, banned_generals)
//        general_names.removeOne(banned);

//    return general_names;
//}

//QStringList GameLogicCore::randomGenerals(int count, const QSet<QString> &ban_set) const
//{
//    QStringList all_generals = limitedGeneralNames();
//    QSet<QString> general_set = all_generals.toSet();

//    count = qMin(count, all_generals.count());
//    Q_ASSERT(all_generals.count() >= count);

//    all_generals = general_set.subtract(ban_set).toList();

//    // shuffle them
//    qShuffle(all_generals);

//    QStringList general_list = all_generals.mid(0, count);
//    Q_ASSERT(general_list.count() == count);

//    return general_list;
//}

//QList<int> GameLogicCore::randomCards() const
//{
//    QList<int> list;
//    foreach (Card *card, cards) {
//        card->clearFlags();

//        if (!banPackages().contains(card->package()))
//            list << card->id();
//    }

//    QStringList card_conversions = Config.value("CardConversions").toStringList();

//    if (card_conversions.contains("DragonPhoenix"))
//        list.removeOne(55);
//    else
//        list.removeOne(108);

//    if (card_conversions.contains("PeaceSpell"))
//        list.removeOne(157);
//    else
//        list.removeOne(109);

//    qShuffle(list);

//    return list;
//}

//QString GameLogicCore::randomGeneralName() const
//{
//    const General *general = generalList.at(qrand() % generalList.size());
//    while (general->kingdom() == "programmer")
//        general = generalList.at(qrand() % generalList.size());
//    return general->objectName();
//}

//void GameLogicCore::playSystemAudioEffect(const QString &name) const
//{
//    playAudioEffect(QString("audio/system/%1.ogg").arg(name));
//}

//void GameLogicCore::playAudioEffect(const QString &filename) const
//{
//#ifdef AUDIO_SUPPORT
//    if (!Config.EnableEffects)
//        return;
//    if (filename.isNull())
//        return;

//    Audio::play(filename);
//#endif
//}

////void GameLogicCore::playSkillAudioEffect(const QString &skill_name, int index) const
////{
////    const Skill *skill = m_skills.value(skill_name, nullptr);
////    if (skill)
////        skill->playAudioEffect(index);
////}

////const Skill *GameLogicCore::getSkill(const QString &skill_name) const
////{
////    return m_skills.value(skill_name, nullptr);
////}

//const Skill *GameLogicCore::skill(const EquipCard *equip) const
//{
//    const Skill *skill;
//    if (equip == nullptr)
//        skill = nullptr;
//    else
//        skill = Sanguosha->skill(equip->objectName());

//    return skill;
//}

//QStringList GameLogicCore::skillNames() const
//{
//    return m_skills.keys();
//}

//const TriggerSkill *GameLogicCore::triggerSkill(const QString &skill_name) const
//{
//    const Skill *skill = skill(skill_name);
//    if (skill)
//        return qobject_cast<const TriggerSkill *>(skill);
//    else
//        return nullptr;
//}

//const ViewAsSkill *GameLogicCore::viewAsSkill(const QString &skill_name) const
//{
//    const Skill *skill = skill(skill_name);
//    if (skill == nullptr)
//        return nullptr;

//    if (skill->inherits("ViewAsSkill"))
//        return qobject_cast<const ViewAsSkill *>(skill);
//    else if (skill->inherits("TriggerSkill")) {
//        const TriggerSkill *trigger_skill = qobject_cast<const TriggerSkill *>(skill);
//        return trigger_skill->viewAsSkill();
//    } else
//        return nullptr;
//}

//const ProhibitSkill *GameLogicCore::isProhibited(const Player *from, const Player *to, const Card *card, const QList<const Player *> &others) const
//{
//    foreach (const ProhibitSkill *skill, m_prohibitSkills) {
//        if (skill->isProhibited(from, to, card, others))
//            return skill;
//    }

//    return nullptr;
//}

//int GameLogicCore::correctDistance(const Player *from, const Player *to) const
//{
//    int correct = 0;

//    foreach (const DistanceSkill *skill, m_distanceSkills)
//        correct += skill->getCorrect(from, to);

//    return correct;
//}

//int GameLogicCore::correctMaxCards(const ServerPlayer *target, bool fixed, MaxCardsType::MaxCardsCount type) const
//{
//    int extra = 0;

//    foreach (const MaxCardsSkill *skill, m_maxcardsSkills) {
//        if (fixed) {
//            int f = skill->getFixed(target, type);
//            if (f > extra)
//                extra = f;
//        } else {
//            extra += skill->getExtra(target, type);
//        }
//    }

//    return extra;
//}

//int GameLogicCore::correctCardTarget(const TargetModSkill::ModType type, const Player *from, const Card *card) const
//{
//    int x = 0;

//    if (type == TargetModSkill::Residue) {
//        foreach (const TargetModSkill *skill, m_targetmodSkills) {
//            ExpPattern p(skill->pattern());
//            if (p.match(from, card)) {
//                int residue = skill->residueNum(from, card);
//                if (residue >= 998) return residue;
//                x += residue;
//            }
//        }
//    } else if (type == TargetModSkill::DistanceLimit) {
//        foreach (const TargetModSkill *skill, m_targetmodSkills) {
//            ExpPattern p(skill->pattern());
//            if (p.match(from, card)) {
//                int distance_limit = skill->distanceLimit(from, card);
//                if (distance_limit >= 998) return distance_limit;
//                x += distance_limit;
//            }
//        }
//    } else if (type == TargetModSkill::ExtraTarget) {
//        foreach (const TargetModSkill *skill, m_targetmodSkills) {
//            ExpPattern p(skill->pattern());
//            if (p.match(from, card)) {
//                x += skill->extraTargetNum(from, card);
//            }
//        }
//    }

//    return x;
//}


//int GameLogicCore::correctAttackRange(const Player *target, bool include_weapon, bool fixed) const
//{
//    int extra = 0;

//    foreach (const AttackRangeSkill *skill, m_attackrangeSkills) {
//        if (fixed) {
//            int f = skill->fixed(target, include_weapon);
//            if (f > extra)
//                extra = f;
//        } else {
//            extra += skill->extra(target, include_weapon);
//        }
//    }

//    return extra;
//}


