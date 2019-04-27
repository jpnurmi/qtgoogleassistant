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

/*
This file contains source code that was copied from, or is inspired by,
the Google Assistant C++ SDK (https://github.com/googlesamples/assistant-sdk-cpp)

Copyright 2017 Google Inc.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    https://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#include "qgoogleassistant.h"
#include "qgoogleassistant_p.h"
#include "qgoogleassistantaudioinput.h"
#include "qgoogleassistantaudiooutput.h"
#include "qgoogleassistantchannel_p.h"
#include "qgoogleassistantrequest.h"
#include "qgoogleassistantresponse.h"

#include <QtCore/qloggingcategory.h>
#include <QtCore/qthread.h>
#include <QtCore/private/qobject_p.h>
#include <QtNetwork/qnetworkreply.h>
#include <QtNetworkAuth/qoauth2authorizationcodeflow.h>
#include <QtNetworkAuth/qoauthhttpserverreplyhandler.h>

QT_BEGIN_NAMESPACE

Q_LOGGING_CATEGORY(lcAuth, "qt.googleassistant.auth")

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

QGoogleAssistantConfig QGoogleAssistantPrivate::createConfig() const
{
    QGoogleAssistantDeviceConfig deviceConfig;
    deviceConfig.setDeviceId(deviceIdentifier);
    deviceConfig.setDeviceModelId(deviceModel);

    QGoogleAssistantDialogStateIn dialogStateIn;
    dialogStateIn.setLanguageCode(locale.name());

    QGoogleAssistantAudioInConfig audioInConfig;
    audioInConfig.setSampleRateHertz(audioInput->format().sampleRate());
    audioInConfig.setEncoding(QGoogleAssistantAudioInConfig::Linear16);
    QGoogleAssistantAudioOutConfig audioOutConfig;
    audioOutConfig.setSampleRateHertz(audioOutput->format().sampleRate());
    audioOutConfig.setEncoding(QGoogleAssistantAudioOutConfig::Linear16);

    QGoogleAssistantConfig config;
    config.setDeviceConfig(deviceConfig);
    config.setDialogStateIn(dialogStateIn);
    config.setAudioInConfig(audioInConfig);
    config.setAudioOutConfig(audioOutConfig);
    return config;
}

void QGoogleAssistantPrivate::postRequest(const QGoogleAssistantRequest &request)
{
    QMetaObject::invokeMethod(channel, "request", Qt::QueuedConnection, Q_ARG(QGoogleAssistantRequest, request));
}

void QGoogleAssistantPrivate::receiveResponse(const QGoogleAssistantResponse &response)
{
    Q_Q(QGoogleAssistant);
    if (audioInput->isActive() && (response.hasAudioOut() || response.endOfUtterance()))
        audioInput->disable();
    if (response.hasAudioOut())
        audioOutput->output(response.audioOut().audioData());
    emit q->response(response);
}

void QGoogleAssistantPrivate::finish(QGoogleAssistant::Status newStatus, const QString &newError)
{
    Q_Q(QGoogleAssistant);
    bool statusChange = status != newStatus;
    bool errorChange = lastError != newError;

    status = newStatus;
    lastError = newError;

    if (statusChange)
        emit q->statusChanged(newStatus);
    if (errorChange)
        emit q->lastErrorChanged(newError);
    emit q->finished(newStatus);
}

QGoogleAssistant::QGoogleAssistant(QObject *parent)
    : QObject(*(new QGoogleAssistantPrivate), parent)
{
    Q_D(QGoogleAssistant);
    d->audioInput = new QGoogleAssistantAudioInput(this);
    d->audioOutput = new QGoogleAssistantAudioOutput(this);

    connect(d->audioInput, &QGoogleAssistantAudioInput::input, this, &QGoogleAssistant::audioRequest);

    d->channel = new QGoogleAssistantChannel(this);
    connect(d->audioInput, &QGoogleAssistantAudioInput::begin, d->channel, &QGoogleAssistantChannel::beginBatch, Qt::QueuedConnection);
    connect(d->audioInput, &QGoogleAssistantAudioInput::end, d->channel, &QGoogleAssistantChannel::endBatch, Qt::QueuedConnection);
    QObjectPrivate::connect(d->channel, &QGoogleAssistantChannel::finished, d, &QGoogleAssistantPrivate::finish, Qt::QueuedConnection);
    QObjectPrivate::connect(d->channel, &QGoogleAssistantChannel::response, d, &QGoogleAssistantPrivate::receiveResponse, Qt::QueuedConnection);

    QThread *thread = new QThread(this);
    d->channel->moveToThread(thread);
    thread->start();

    qRegisterMetaType<QGoogleAssistantAudioInConfig>();
    qRegisterMetaType<QGoogleAssistantAudioOutConfig>();
    qRegisterMetaType<QGoogleAssistantScreenOutConfig>();
    qRegisterMetaType<QGoogleAssistantDeviceLocation>();
    qRegisterMetaType<QGoogleAssistantDialogStateIn>();
    qRegisterMetaType<QGoogleAssistantDeviceConfig>();
    qRegisterMetaType<QGoogleAssistantDebugConfig>();
    qRegisterMetaType<QGoogleAssistantConfig>();
    qRegisterMetaType<QGoogleAssistantRequest>();

    qRegisterMetaType<QGoogleAssistantAudioOut>();
    qRegisterMetaType<QGoogleAssistantDebugInfo>();
    qRegisterMetaType<QGoogleAssistantDeviceAction>();
    qRegisterMetaType<QGoogleAssistantDialogStateOut>();
    qRegisterMetaType<QGoogleAssistantScreenOut>();
    qRegisterMetaType<QGoogleAssistantSpeechRecognitionResult>();
    qRegisterMetaType<QGoogleAssistantResponse>();
}

QGoogleAssistant::~QGoogleAssistant()
{
    Q_D(QGoogleAssistant);
    if (d->channel) {
        QThread *thread = d->channel->thread();
        thread->quit();
        thread->wait(2000);
        delete d->channel;
    }
}

QGoogleAssistantAudioInput *QGoogleAssistant::audioInput() const
{
    Q_D(const QGoogleAssistant);
    return d->audioInput;
}

QGoogleAssistantAudioOutput *QGoogleAssistant::audioOutput() const
{
    Q_D(const QGoogleAssistant);
    return d->audioOutput;
}

QLocale QGoogleAssistant::locale() const
{
    Q_D(const QGoogleAssistant);
    return d->locale;
}

void QGoogleAssistant::setLocale(const QLocale &locale)
{
    Q_D(QGoogleAssistant);
    if (d->locale == locale)
        return;

    d->locale = locale;
    emit localeChanged(locale);
}

QString QGoogleAssistant::apiEndpoint() const
{
    Q_D(const QGoogleAssistant);
    return d->apiEndpoint;
}

void QGoogleAssistant::setApiEndpoint(const QString &apiEndpoint)
{
    Q_D(QGoogleAssistant);
    if (d->apiEndpoint == apiEndpoint)
        return;

    d->apiEndpoint = apiEndpoint;
    emit apiEndpointChanged(apiEndpoint);
}

QString QGoogleAssistant::deviceIdentifier() const
{
    Q_D(const QGoogleAssistant);
    return d->deviceIdentifier;
}

void QGoogleAssistant::setDeviceIdentifier(const QString &deviceIdentifier)
{
    Q_D(QGoogleAssistant);
    if (d->deviceIdentifier == deviceIdentifier)
        return;

    d->deviceIdentifier = deviceIdentifier;
    emit deviceIdentifierChanged(deviceIdentifier);
}

QString QGoogleAssistant::deviceModel() const
{
    Q_D(const QGoogleAssistant);
    return d->deviceModel;
}

void QGoogleAssistant::setDeviceModel(const QString &deviceModel)
{
    Q_D(QGoogleAssistant);
    if (d->deviceModel == deviceModel)
        return;

    d->deviceModel = deviceModel;
    emit deviceModelChanged(deviceModel);
}

QString QGoogleAssistant::clientIdentifier() const
{
    Q_D(const QGoogleAssistant);
    return d->clientIdentifier;
}

void QGoogleAssistant::setClientIdentifier(const QString &clientIdentifier)
{
    Q_D(QGoogleAssistant);
    if (d->clientIdentifier == clientIdentifier)
        return;

    d->clientIdentifier = clientIdentifier;
    emit clientIdentifierChanged(clientIdentifier);
}

QString QGoogleAssistant::clientSecret() const
{
    Q_D(const QGoogleAssistant);
    return d->clientSecret;
}

void QGoogleAssistant::setClientSecret(const QString &clientSecret)
{
    Q_D(QGoogleAssistant);
    if (d->clientSecret == clientSecret)
        return;

    d->clientSecret = clientSecret;
    emit clientSecretChanged(clientSecret);
}

QString QGoogleAssistant::accessToken() const
{
    Q_D(const QGoogleAssistant);
    return d->accessToken;
}

void QGoogleAssistant::setAccessToken(const QString &accessToken)
{
    Q_D(QGoogleAssistant);
    if (d->accessToken == accessToken)
        return;

    d->accessToken = accessToken;
    emit accessTokenChanged(accessToken);
}

QString QGoogleAssistant::refreshToken() const
{
    Q_D(const QGoogleAssistant);
    return d->refreshToken;
}

void QGoogleAssistant::setRefreshToken(const QString &refreshToken)
{
    Q_D(QGoogleAssistant);
    if (d->refreshToken == refreshToken)
        return;

    d->refreshToken = refreshToken;
    emit refreshTokenChanged(refreshToken);
}

QUrl QGoogleAssistant::accessTokenUrl() const
{
    Q_D(const QGoogleAssistant);
    return d->accessTokenUrl;
}

void QGoogleAssistant::setAccessTokenUrl(const QUrl &accessTokenUrl)
{
    Q_D(QGoogleAssistant);
    if (d->accessTokenUrl == accessTokenUrl)
        return;

    d->accessTokenUrl = accessTokenUrl;
    emit accessTokenUrlChanged(accessTokenUrl);
}

QUrl QGoogleAssistant::authorizationUrl() const
{
    Q_D(const QGoogleAssistant);
    return d->authorizationUrl;
}

void QGoogleAssistant::setAuthorizationUrl(const QUrl &authorizationUrl)
{
    Q_D(QGoogleAssistant);
    if (d->authorizationUrl == authorizationUrl)
        return;

    d->authorizationUrl = authorizationUrl;
    emit authorizationUrlChanged(authorizationUrl);
}

QJsonObject QGoogleAssistant::credentials() const
{
    Q_D(const QGoogleAssistant);
    QJsonObject json;
    json[QStringLiteral("client_id")] = d->clientIdentifier;
    json[QStringLiteral("client_secret")] = d->clientSecret;
    json[QStringLiteral("refresh_token")] = d->refreshToken;
    json[QStringLiteral("type")] = QStringLiteral("authorized_user");
    return json;
}

bool QGoogleAssistant::isAuthenticated() const
{
    Q_D(const QGoogleAssistant);
    return d->authenticated;
}

QGoogleAssistant::Status QGoogleAssistant::status() const
{
    Q_D(const QGoogleAssistant);
    return d->status;
}

QString QGoogleAssistant::lastError() const
{
    Q_D(const QGoogleAssistant);
    return d->lastError;
}

static QString authErrorToString(QAbstractOAuth::Error error)
{
    switch (error) {
    case QAbstractOAuth::Error::NoError:
        return QGoogleAssistant::tr("No error.");
    case QAbstractOAuth::Error::NetworkError:
        return QGoogleAssistant::tr("Failed to connect to the server.");
    case QAbstractOAuth::Error::ServerError:
        return QGoogleAssistant::tr("The server answered the request with an error.");
    case QAbstractOAuth::Error::OAuthTokenNotFoundError:
        return QGoogleAssistant::tr("The server's response to a token request provided no token identifier.");
    case QAbstractOAuth::Error::OAuthTokenSecretNotFoundError:
        return QGoogleAssistant::tr("The server's response to a token request provided no token secret.");
    case QAbstractOAuth::Error::OAuthCallbackNotVerified:
        return QGoogleAssistant::tr("The authorization server has not verified the supplied callback URI in the request.");
    default:
        return QGoogleAssistant::tr("Unknown error.");
    }
}

void QGoogleAssistant::authenticate()
{
    Q_D(QGoogleAssistant);
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

    QObject::connect(flow, &QOAuth2AuthorizationCodeFlow::authorizeWithBrowser, this, &QGoogleAssistant::authorizeWithBrowser);
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

void QGoogleAssistant::textRequest(const QString &text)
{
    Q_D(QGoogleAssistant);
    QGoogleAssistantConfig config = d->createConfig();
    config.setTextQuery(text);
    QGoogleAssistantRequest request;
    request.setConfig(config);
    d->postRequest(request);
}

void QGoogleAssistant::audioRequest(const QByteArray &audio)
{
    Q_D(QGoogleAssistant);
    QGoogleAssistantRequest request;
    request.setAudioIn(audio);
    d->postRequest(request);
}

void QGoogleAssistant::request(const QGoogleAssistantRequest &request)
{
    Q_D(QGoogleAssistant);
    d->postRequest(request);
}

QT_END_NAMESPACE

#include "qgoogleassistant.moc"
