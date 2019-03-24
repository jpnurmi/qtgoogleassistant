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

#ifndef QGOOGLEASSISTANTAUDIO_H
#define QGOOGLEASSISTANTAUDIO_H

#include <QtMultimedia/qaudioformat.h>
#include <QtGoogleAssistant/qtgoogleassistantglobal.h>

QT_BEGIN_NAMESPACE

class Q_GOOGLEASSISTANT_EXPORT QGoogleAssistantAudio
{
public:
    static QAudioFormat defaultFormat();
};

QT_END_NAMESPACE

#endif // QGOOGLEASSISTANTAUDIO_H
