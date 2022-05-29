#ifndef TRAPEZOID_GLOBAL_H
#define TRAPEZOID_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(TRAPEZOID_LIBRARY)
#  define TRAPEZOID_EXPORT Q_DECL_EXPORT
#else
#  define TRAPEZOID_EXPORT Q_DECL_IMPORT
#endif

#endif // TRAPEZOID_GLOBAL_H
