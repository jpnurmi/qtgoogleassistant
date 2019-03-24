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

#ifndef QGOOGLEASSISTANTAUTH_H
#define QGOOGLEASSISTANTAUTH_H

#include <QtCore/qobject.h>
#include <QtCore/qurl.h>
#include <QtGoogleAssistant/qtgoogleassistantglobal.h>
#include <QtCore/qjsonobject.h>

QT_BEGIN_NAMESPACE

class QGoogleAssistantAuthPrivate;

class Q_GOOGLEASSISTANT_EXPORT QGoogleAssistantAuth : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool authenticated READ isAuthenticated NOTIFY authenticatedChanged)
    Q_PROPERTY(QString clientIdentifier READ clientIdentifier WRITE setClientIdentifier NOTIFY clientIdentifierChanged)
    Q_PROPERTY(QString clientSecret READ clientSecret WRITE setClientSecret NOTIFY clientSecretChanged)
    Q_PROPERTY(QString accessToken READ accessToken WRITE setAccessToken NOTIFY accessTokenChanged)
    Q_PROPERTY(QString refreshToken READ refreshToken WRITE setRefreshToken NOTIFY refreshTokenChanged)
    Q_PROPERTY(QUrl authorizationUrl READ authorizationUrl WRITE setAuthorizationUrl NOTIFY authorizationUrlChanged)
    Q_PROPERTY(QUrl accessTokenUrl READ accessTokenUrl WRITE setAccessTokenUrl NOTIFY accessTokenUrlChanged)

public:
    explicit QGoogleAssistantAuth(QObject *parent = nullptr);

    bool isAuthenticated() const;

    QString clientIdentifier() const;
    void setClientIdentifier(const QString &clientIdentifier);

    QString clientSecret() const;
    void setClientSecret(const QString &clientSecret);

    QString accessToken() const;
    void setAccessToken(const QString &accessToken);

    QString refreshToken() const;
    void setRefreshToken(const QString &refreshToken);

    QUrl authorizationUrl() const;
    void setAuthorizationUrl(const QUrl &authorizationUrl);

    QUrl accessTokenUrl() const;
    void setAccessTokenUrl(const QUrl &accessTokenUrl);

    QJsonObject credentials() const;

public Q_SLOTS:
    void authenticate();

Q_SIGNALS:
    void authenticated();
    void authenticatedChanged(bool authenticated);
    void errorOccurred(const QString &errorString);
    void clientIdentifierChanged(const QString &clientIdentifier);
    void clientSecretChanged(const QString &clientSecret);
    void accessTokenChanged(const QString &accessToken);
    void refreshTokenChanged(const QString &refreshToken);
    void authorizationUrlChanged(const QUrl &authorizationUrl);
    void accessTokenUrlChanged(const QUrl &accessTokenUrl);
    void authorizeWithBrowser(const QUrl &url);

private:
    Q_DISABLE_COPY(QGoogleAssistantAuth)
    Q_DECLARE_PRIVATE(QGoogleAssistantAuth)
};

QT_END_NAMESPACE

#endif // QGOOGLEASSISTANTAUTH_P_H
