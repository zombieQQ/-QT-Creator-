#pragma once

#include <QtCore/qglobal.h>

#ifdef MODULELINKER_LIB
# define MODULELINKER_EXPORT Q_DECL_EXPORT
#else
# define MODULELINKER_EXPORT Q_DECL_IMPORT
#endif
