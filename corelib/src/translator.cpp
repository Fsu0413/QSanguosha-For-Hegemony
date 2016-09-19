#include "translator.h"



namespace QSgsTranslator
{


void initTranslator()
{

}

#define FUNCFORTRANSLATE(a) \
    QString a(const char *a ## Str) { \
        return qApp->translate(#a, a ## Str, nullptr, 0); \
    }

FUNCFORTRANSLATE(PackageName)
FUNCFORTRANSLATE(GeneralName)
FUNCFORTRANSLATE(GeneralDescription)
FUNCFORTRANSLATE(CardName)
FUNCFORTRANSLATE(CardDescription)
FUNCFORTRANSLATE(SkillName)
FUNCFORTRANSLATE(SkillDescription)
FUNCFORTRANSLATE(Role)
FUNCFORTRANSLATE(Kingdom)
FUNCFORTRANSLATE(Gender)
FUNCFORTRANSLATE(MarkName)
FUNCFORTRANSLATE(Log)
FUNCFORTRANSLATE(Prompt)
FUNCFORTRANSLATE(Choice)

#undef FUNCFORTRANSLATE

}
