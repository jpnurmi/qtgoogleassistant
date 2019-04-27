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

#ifndef QGOOGLEASSISTANT_P_H
#define QGOOGLEASSISTANT_P_H

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

#include <QtCore/private/qobject_p.h>
#include <QtGoogleAssistant/qgoogleassistant.h>
#include <QtGoogleAssistant/qgoogleassistantrequest.h>

QT_BEGIN_NAMESPACE

class QGoogleAssistantChannel;

class QGoogleAssistantPrivate : public QObjectPrivate
{
    Q_DECLARE_PUBLIC(QGoogleAssistant)

public:
    static QGoogleAssistantPrivate *get(QGoogleAssistant *assistant)
    {
        return assistant->d_func();
    }

    QGoogleAssistantConfig createConfig() const;
    void postRequest(const QGoogleAssistantRequest &request);
    void receiveResponse(const QGoogleAssistantResponse &response);
    void finish(QGoogleAssistant::Status status, const QString &error);

    bool authenticated = false;
    QGoogleAssistant::Status status = QGoogleAssistant::Ok;
    QLocale locale = QLocale(QStringLiteral("en-US"));
    QString apiEndpoint = QStringLiteral("embeddedassistant.googleapis.com");
    QString deviceIdentifier = QStringLiteral("default");
    QString deviceModel = QStringLiteral("default");
    QString lastError;
    QString clientIdentifier;
    QString clientSecret;
    QString accessToken;
    QString refreshToken;
    QUrl authorizationUrl = QStringLiteral("https://accounts.google.com/o/oauth2/auth");
    QUrl accessTokenUrl = QStringLiteral("https://accounts.google.com/o/oauth2/token");
    QGoogleAssistantAudioInput *audioInput = nullptr;
    QGoogleAssistantAudioOutput *audioOutput = nullptr;
    QGoogleAssistantChannel *channel = nullptr;
};

QT_END_NAMESPACE

#endif // QGOOGLEASSISTANT_P_H
