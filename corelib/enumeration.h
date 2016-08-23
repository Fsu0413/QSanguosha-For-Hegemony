#ifndef ENUMERATION_H
#define ENUMERATION_H

namespace QSgsEnum{

enum class CardSuit {
    NoSuit = 0x0,
    Black = 0x100,
    Red = 0x200,
    Spade = Black + 1,
    Club = Black + 2,
    Heart = Red + 1,
    Diamond = Red + 2,
    Tbd = -1
};

enum class CardHandlingMethod
{
    NoMethod,
    Use,
    Response,
    Discard,
    Recast,
    Pindian
};

// card types
enum class CardType
{
    Skill,
    Basic,
    Equip,
    Trick
};

enum class GeneralGender
{
    Sexless, Male, Female, Neuter
};

enum class PackageType {
    GeneralPackage,
    CardPackage,
    OtherPackage
};

enum class PlayerPhase
{
    RoundStart, Start, Judge, Draw, Play, Discard, Finish, NotActive, PhaseNone
};

enum class PlayerPlace
{
    PlaceHand, PlaceEquip, PlaceDelayedTrick, PlaceJudge,
    PlaceSpecial, DiscardPile, DrawPile, PlaceTable, PlaceUnknown,
    PlaceWuGu, DrawPileBottom
};

enum class PlayerRelation
{
    Friend, Enemy, Neutrality
};

enum class PlayerRole
{
    Lord, Loyalist, Rebel, Renegade
};

enum class PlayersArrayType
{
    Siege,
    Formation
};

enum class GuanxingType
{
    GuanxingUpOnly = 1, GuanxingBothSides = 0, GuanxingDownOnly = -1
};

enum class SkillFrequency
{
    Frequent,
    NotFrequent,
    Compulsory,
    Limited,
    Wake
};

enum class DamageNature
{
    Normal, // normal slash, duel and most damage caused by skill
    Fire,  // fire slash, fire attack and few damage skill (Yeyan, etc)
    Thunder // lightning, thunder slash, and few damage skill (Leiji, etc)
};

enum class CardUseReason
{
    CARD_USE_REASON_UNKNOWN = 0x00,
    CARD_USE_REASON_PLAY = 0x01,
    CARD_USE_REASON_RESPONSE = 0x02,
    CARD_USE_REASON_RESPONSE_USE = 0x12
};

enum class TriggerEvent
{
    NonTrigger,

    GameStart,
    TurnStart,
    EventPhaseStart,
    EventPhaseProceeding,
    EventPhaseEnd,
    EventPhaseChanging,
    EventPhaseSkipping,

    ConfirmPlayerNum, // hongfa only

    DrawNCards,
    AfterDrawNCards,

    PreHpRecover,
    HpRecover,
    PreHpLost,
    HpChanged,
    MaxHpChanged,
    PostHpReduced,
    HpLost,

    EventLoseSkill,
    EventAcquireSkill,

    StartJudge,
    AskForRetrial,
    FinishRetrial,
    FinishJudge,

    PindianVerifying,
    Pindian,

    TurnedOver,
    ChainStateChanged,
    RemoveStateChanged,

    ConfirmDamage,    // confirm the damage's count and damage's nature
    Predamage,        // trigger the certain skill -- jueqing
    DamageForseen,    // the first event in a damage -- kuangfeng dawu
    DamageCaused,     // the moment for -- qianxi..
    DamageInflicted,  // the moment for -- tianxiang..
    PreDamageDone,    // before reducing Hp
    DamageDone,       // it's time to do the damage
    Damage,           // the moment for -- lieren..
    Damaged,          // the moment for -- yiji..
    DamageComplete,   // the moment for trigger iron chain

    Dying,
    QuitDying,
    AskForPeaches,
    AskForPeachesDone,
    Death,
    BuryVictim,
    BeforeGameOverJudge,
    GameOverJudge,
    GameFinished,

    SlashEffected,
    SlashProceed,
    SlashHit,
    SlashMissed,

    JinkEffect,

    CardAsked,
    CardResponded,
    BeforeCardsMove, // sometimes we need to record cards before the move
    CardsMoveOneTime,

    PreCardUsed,
    CardUsed,
    TargetChoosing, //distinguish "choose target" and "confirm target"
    TargetConfirming,
    TargetChosen,
    TargetConfirmed,
    CardEffect,
    CardEffected,
    CardEffectConfirmed, //after nullptrification
    PostCardEffected,
    CardFinished,
    TrickCardCanceling,

    ChoiceMade,

    StageChange, // For hulao pass only
    FetchDrawPileCard, // For miniscenarios only

    TurnBroken, // For the skill 'DanShou'. Do not use it to trigger events

    GeneralShown, // For Official Hegemony mode
    GeneralHidden, // For Official Hegemony mode
    GeneralRemoved, // For Official Hegemony mode

    DFDebut, // for Dragon Phoenix Debut

    NumOfEvents
};
enum class EquipLocation
{
    WeaponLocation,
    ArmorLocation,
    DefensiveHorseLocation,
    OffensiveHorseLocation,
    TreasureLocation
};
}


#endif // ENUMERATION_H
