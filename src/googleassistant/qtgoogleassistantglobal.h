/****************************************************************************
**
** Copyright (C) 2019 J-P Nurmi <jpnurmi@gmail.com>
**
** This file is part of QtGoogleAssistant.
**
** QtGoogleAssistant is free software: you can redistribute it and/or modify
** it under the terms of the GNU Lesser General Public License as published
** by the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** QtGoogleAssistant is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU Lesser General Public License for more details.
**
** You should have received a copy of the GNU Lesser General Public License
** along with QtGoogleAssistant. If not, see <https://www.gnu.org/licenses/>.
**
****************************************************************************/

#ifndef QTGOOGLEASSISTANTGLOBAL_H
#define QTGOOGLEASSISTANTGLOBAL_H

#include <QtCore/qglobal.h>

#ifndef Q_GOOGLEASSISTANT_EXPORT
#  ifndef QT_STATIC
#    if defined(QT_BUILD_GOOGLEASSISTANT_LIB)
#      define Q_GOOGLEASSISTANT_EXPORT Q_DECL_EXPORT
#    else
#      define Q_GOOGLEASSISTANT_EXPORT Q_DECL_IMPORT
#    endif
#  else
#    define Q_GOOGLEASSISTANT_EXPORT
#  endif
#endif

#endif // QTGOOGLEASSISTANTGLOBAL_H
