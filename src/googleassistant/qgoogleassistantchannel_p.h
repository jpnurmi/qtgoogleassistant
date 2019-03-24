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

#ifndef QGOOGLEASSISTANTCHANNEL_P_H
#define QGOOGLEASSISTANTCHANNEL_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include <QtCore/qobject.h>
#include <QtGoogleAssistant/qgoogleassistant.h>

QT_BEGIN_NAMESPACE

class QGoogleAssistantRequest;
class QGoogleAssistantResponse;
class QGoogleAssistantChannelPrivate;

class QGoogleAssistantChannel : public QObject
{
    Q_OBJECT

public:
    explicit QGoogleAssistantChannel(QGoogleAssistant *parent);

public Q_SLOTS:
    void request(const QGoogleAssistantRequest &request);
    void beginBatch();
    void endBatch();

Q_SIGNALS:
    void response(const QGoogleAssistantResponse &response);
    void finished(QGoogleAssistant::Status status, const QString &errorString);

private:
    Q_DISABLE_COPY(QGoogleAssistantChannel)
    Q_DECLARE_PRIVATE(QGoogleAssistantChannel)
};

QT_END_NAMESPACE

#endif // QGOOGLEASSISTANTCHANNEL_P_H
