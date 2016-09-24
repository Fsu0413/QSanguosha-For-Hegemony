#ifndef QSGSTRANSLATOR_H
#define QSGSTRANSLATOR_H

#include "libqsgsgamelogicglobal.h"

#if 0
class _EXPORT QSgsTranslator
#endif

namespace QSgsTranslator
{

void loadTranslationOfPackage(const QString &packageName);

// Card description
QString PackageName(const char *package);
QString GeneralName(const char *general);
QString GeneralDescription(const char *general);
QString CardName(const char *cardface);
QString CardDescription(const char *cardface);
QString SkillName(const char *skill);
QString SkillDescription(const char *skill);

// Player property
QString Role(const char *role);
QString Kingdom(const char *kingdom);
QString Gender(const char *gender);

// Game process
QString MarkName(const char *mark);
QString Log(const char *logType);
QString Prompt(const char *prompt);
QString Choice(const char *choice);

}

#endif // QSGSTRANSLATOR_H
