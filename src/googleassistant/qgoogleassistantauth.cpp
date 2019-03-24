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

#include "qgoogleassistantauth.h"

#include <QtCore/qloggingcategory.h>
#include <QtCore/private/qobject_p.h>
#include <QtNetwork/qnetworkreply.h>
#include <QtNetworkAuth/qoauth2authorizationcodeflow.h>
#include <QtNetworkAuth/qoauthhttpserverreplyhandler.h>

QT_BEGIN_NAMESPACE

Q_LOGGING_CATEGORY(lcAuth, "qt.googleassistant.auth")

static QString authErrorToString(QAbstractOAuth::Error error)
{
    switch (error) {
    case QAbstractOAuth::Error::NoError:
        return QGoogleAssistantAuth::tr("No error.");
    case QAbstractOAuth::Error::NetworkError:
        return QGoogleAssistantAuth::tr("Failed to connect to the server.");
    case QAbstractOAuth::Error::ServerError:
        return QGoogleAssistantAuth::tr("The server answered the request with an error.");
    case QAbstractOAuth::Error::OAuthTokenNotFoundError:
        return QGoogleAssistantAuth::tr("The server's response to a token request provided no token identifier.");
    case QAbstractOAuth::Error::OAuthTokenSecretNotFoundError:
        return QGoogleAssistantAuth::tr("The server's response to a token request provided no token secret.");
    case QAbstractOAuth::Error::OAuthCallbackNotVerified:
        return QGoogleAssistantAuth::tr("The authorization server has not verified the supplied callback URI in the request.");
    default:
        return QGoogleAssistantAuth::tr("Unknown error.");
    }
}

class QGoogleAssistantAuthPrivate : public QObjectPrivate
{
public:
    bool authenticated = false;
    QString clientIdentifier;
    QString clientSecret;
    QString accessToken;
    QString refreshToken;
    QUrl authorizationUrl = QStringLiteral("https://accounts.google.com/o/oauth2/auth");
    QUrl accessTokenUrl = QStringLiteral("https://accounts.google.com/o/oauth2/token");
};

class QGoogleAssistantAuthReplyHandler : public QOAuthHttpServerReplyHandler
{
    Q_OBJECT

public:
    explicit QGoogleAssistantAuthReplyHandler(QObject *parent = nullptr)
        : QOAuthHttpServerReplyHandler(parent) { }

signals:
    void replyError(QNetworkReply::NetworkError error, const QString &errorString);

protected:
    void networkReplyFinished(QNetworkReply *reply) override
    {
        if (reply->error() != QNetworkReply::NoError) {
            emit replyError(reply->error(), reply->errorString());
            return;
        }
        QOAuthHttpServerReplyHandler::networkReplyFinished(reply);
    }
};

QGoogleAssistantAuth::QGoogleAssistantAuth(QObject *parent)
    : QObject(*(new QGoogleAssistantAuthPrivate), parent)
{
}

bool QGoogleAssistantAuth::isAuthenticated() const
{
    Q_D(const QGoogleAssistantAuth);
    return d->authenticated;
}

QString QGoogleAssistantAuth::clientIdentifier() const
{
    Q_D(const QGoogleAssistantAuth);
    return d->clientIdentifier;
}

void QGoogleAssistantAuth::setClientIdentifier(const QString &clientIdentifier)
{
    Q_D(QGoogleAssistantAuth);
    if (d->clientIdentifier == clientIdentifier)
        return;

    d->clientIdentifier = clientIdentifier;
    emit clientIdentifierChanged(clientIdentifier);
}

QString QGoogleAssistantAuth::clientSecret() const
{
    Q_D(const QGoogleAssistantAuth);
    return d->clientSecret;
}

void QGoogleAssistantAuth::setClientSecret(const QString &clientSecret)
{
    Q_D(QGoogleAssistantAuth);
    if (d->clientSecret == clientSecret)
        return;

    d->clientSecret = clientSecret;
    emit clientSecretChanged(clientSecret);
}

QString QGoogleAssistantAuth::accessToken() const
{
    Q_D(const QGoogleAssistantAuth);
    return d->accessToken;
}

void QGoogleAssistantAuth::setAccessToken(const QString &accessToken)
{
    Q_D(QGoogleAssistantAuth);
    if (d->accessToken == accessToken)
        return;

    d->accessToken = accessToken;
    emit accessTokenChanged(accessToken);
}

QString QGoogleAssistantAuth::refreshToken() const
{
    Q_D(const QGoogleAssistantAuth);
    return d->refreshToken;
}

void QGoogleAssistantAuth::setRefreshToken(const QString &refreshToken)
{
    Q_D(QGoogleAssistantAuth);
    if (d->refreshToken == refreshToken)
        return;

    d->refreshToken = refreshToken;
    emit refreshTokenChanged(refreshToken);
}

QUrl QGoogleAssistantAuth::accessTokenUrl() const
{
    Q_D(const QGoogleAssistantAuth);
    return d->accessTokenUrl;
}

void QGoogleAssistantAuth::setAccessTokenUrl(const QUrl &accessTokenUrl)
{
    Q_D(QGoogleAssistantAuth);
    if (d->accessTokenUrl == accessTokenUrl)
        return;

    d->accessTokenUrl = accessTokenUrl;
    emit accessTokenUrlChanged(accessTokenUrl);
}

QJsonObject QGoogleAssistantAuth::credentials() const
{
    Q_D(const QGoogleAssistantAuth);
    QJsonObject json;
    json[QStringLiteral("client_id")] = d->clientIdentifier;
    json[QStringLiteral("client_secret")] = d->clientSecret;
    json[QStringLiteral("refresh_token")] = d->refreshToken;
    json[QStringLiteral("type")] = QStringLiteral("authorized_user");
    return json;
}

QUrl QGoogleAssistantAuth::authorizationUrl() const
{
    Q_D(const QGoogleAssistantAuth);
    return d->authorizationUrl;
}

void QGoogleAssistantAuth::setAuthorizationUrl(const QUrl &authorizationUrl)
{
    Q_D(QGoogleAssistantAuth);
    if (d->authorizationUrl == authorizationUrl)
        return;

    d->authorizationUrl = authorizationUrl;
    emit authorizationUrlChanged(authorizationUrl);
}

void QGoogleAssistantAuth::authenticate()
{
    Q_D(QGoogleAssistantAuth);
    QOAuth2AuthorizationCodeFlow *flow = new QOAuth2AuthorizationCodeFlow(this);
    flow->setScope(QString::fromLocal8Bit(QUrl::toPercentEncoding(QStringLiteral("https://www.googleapis.com/auth/assistant-sdk-prototype"))));
    flow->setClientIdentifier(d->clientIdentifier);
    flow->setClientIdentifierSharedKey(d->clientSecret);
    flow->setRefreshToken(d->refreshToken);
    flow->setAccessTokenUrl(d->accessTokenUrl);
    flow->setAuthorizationUrl(d->authorizationUrl);

    flow->setModifyParametersFunction([&](QAbstractOAuth::Stage stage, QVariantMap *parameters) {
        if (stage == QAbstractOAuth::Stage::RefreshingAccessToken) {
            parameters->insert(QStringLiteral("client_id"), QUrl::toPercentEncoding(d->clientIdentifier));
            if (!d->clientSecret.isEmpty())
                parameters->insert(QStringLiteral("client_secret"), d->clientSecret);
        }
    });

    QObject::connect(flow, &QOAuth2AuthorizationCodeFlow::authorizeWithBrowser, this, &QGoogleAssistantAuth::authorizeWithBrowser);
    QObject::connect(flow, &QAbstractOAuth::granted, [=]() {
        qCDebug(lcAuth) << "granted" << flow->token();
        QString refreshToken = flow->refreshToken();
        if (!refreshToken.isEmpty())
            setRefreshToken(refreshToken);
        flow->deleteLater();
        d->authenticated = true;
        emit authenticated();
    });
    QObject::connect(flow, &QAbstractOAuth::requestFailed, [=](QAbstractOAuth::Error error) {
        QString errorString = authErrorToString(error);
        qCWarning(lcAuth) << "request error" << errorString;
        emit errorOccurred(errorString);
    });

    QGoogleAssistantAuthReplyHandler *replyHandler = new QGoogleAssistantAuthReplyHandler(flow);
    flow->setReplyHandler(replyHandler);
    connect(replyHandler, &QGoogleAssistantAuthReplyHandler::replyError, [=](QNetworkReply::NetworkError, const QString &errorString) {
        qCWarning(lcAuth) << "reply error" << errorString;
        emit errorOccurred(errorString);
    });

    if (d->refreshToken.isEmpty()) {
        qCDebug(lcAuth) << "grant";
        flow->grant();
    } else {
        qCDebug(lcAuth) << "refresh" << d->refreshToken;
        flow->refreshAccessToken();
    }
}

QT_END_NAMESPACE

#include "qgoogleassistantauth.moc"
