#ifndef ENUMERATION_H
#define ENUMERATION_H

// NO INCLUDES HERE!!!!

#if 0
// for header generation
class _EXPORT QSgsEnum
#endif

namespace QSgsEnum
{

enum class CardSuit
{
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
    Get,
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
    Sexless,
    Male,
    Female,
    Neuter
};

enum class PackageType
{
    General,
    Card,
    Other
};

enum class PlayerPhase
{
    RoundStart,
    Start,
    Judge,
    Draw,
    Play,
    Discard,
    Finish,
    NotActive,
    NoPhase
};

enum class CardPlace
{
    Hand,
    Equip,
    Judge,
    JudgeCard,
    OutOfGame,
    DiscardPile,
    DrawPile,
    ProceedingArea,
    PlaceUnknown,
    AgContainer,
    DrawPileBottom
};

enum class PlayerRelation
{
    Friend, Enemy, Neutrality
};

enum class PlayerRole
{
    Lord,
    Loyalist,
    Rebel,
    Renegade
};

enum class ArrayType
{
    Siege,
    Formation
};

enum class RearrangeCardDirection
{
    UpOnly = 1,
    BothSides = 0,
    DownOnly = -1
};

enum class SkillFrequency
{
    Frequent,
    NotFrequent,
    Compulsory,
    Limited,
    Wake
};

enum class SkillPlace
{
    None = 0, // Used for acquire-only and equipment skills
    Head = 1,
    Deputy = 2,
    Both = 3
};

enum class DamageNature
{
    Normal, // normal slash, duel and most damage caused by skill
    Fire,  // fire slash, fire attack and few damage skill (Yeyan, etc)
    Thunder // lightning, thunder slash, and few damage skill (Leiji, etc)
};

enum class CardUseReason
{
    Unknown = 0x00,
    Play = 0x01,
    Response = 0x02,
    ResponseUse = 0x12
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
    Weapon,
    Armor,
    DefensiveHorse,
    OffensiveHorse,
    Treasure
};


enum class ModType
{
    Residue,
    DistanceLimit,
    ExtraTarget
};

enum class CardMoveReason
{
    Unknown = 0x00,

    Use = 0x01,
    LetUse = 0x11,              // use a card when self is not current

    Response = 0x02,
    Retrial = 0x12,

    Discard = 0x03,
    RuleDiscard = 0x13,         // discard at one's Player::Discard for gamerule
    Throw = 0x23,               // gamerule(dying or punish) as the cost of some skills
    Dismantle = 0x33,           // one throw card of another

    Recast = 0x04,              // ironchain etc.

    Pindian = 0x05,

    Draw = 0x06,

    GotCard = 0x07,
    Give = 0x17,                // from one hand to another hand
    Extraction = 0x27,          // from another's place to one's hand
    GotBack = 0x37,             // from placetable to hand
    Recycle = 0x47,             // from discardpile to hand
    Rob = 0x57,                 // got a definite card from other's hand
    PreviewGive = 0x67,         // give cards after previewing, i.e. Yiji & Miji

    Show = 0x08,
    TurnOver = 0x18,            // show n cards from drawpile
    Judge = 0x28,               // show a card from drawpile for judge
    Preview = 0x38,             // Not done yet, plan for view some cards for self only(guanxing yiji miji)
    Demonstrate = 0x48,         // show a card which copy one to move to table

    Transfer = 0x09,
    Swap = 0x19,                // exchange card for two players
    Override = 0x29,            // exchange cards from cards in game
    ExchangeFromPile = 0x39,    // exchange cards from cards moved out of game (for qixing only)

    Put = 0x0A,
    NaturalEnter = 0x1A,        // a card with no-owner move into discardpile  e.g. delayed trick enters discardpile
    RemoveFromPile = 0x2A,      // cards moved out of game go back into discardpile
    JudgeDone = 0x3A,           // judge card move into discardpile
    ChangeEquip = 0x4A,         // replace existed equip

    BasicReasonMask = 0x0F
};

enum class DeathReason
{
    Murder = 1,                 // killed by others
    Suiside,                    // killed by himself
    Contingency,                // damaged by no source
    HpLostTo0,
    MaxHpLostTo0,
    SuddenDeath                 // as the name tells. seems like only god_guanyu can cause this type of death...
};

}


#endif // ENUMERATION_H
