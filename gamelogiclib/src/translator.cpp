#include "translator.h"

// TBD for further design

class Translator final : public QTranslator
{
    Q_OBJECT

public:

    QString translate(const char *context, const char *sourceText, const char *disambiguation, int n) const final override
    {
        return QString();
    }
    bool isEmpty() const final override
    {
        return false;
    }
};

namespace
{

void initTranslator()
{
    // dummy
}

}

namespace QSgsTranslator
{


void loadTranslationOfPackage(const QString &packageName)
{
    // TBD
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

#include "translator.moc"
