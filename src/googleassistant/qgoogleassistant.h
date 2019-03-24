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

#ifndef QGOOGLEASSISTANT_H
#define QGOOGLEASSISTANT_H

#include <QtCore/qlocale.h>
#include <QtCore/qobject.h>
#include <QtCore/qstring.h>
#include <QtGoogleAssistant/qtgoogleassistantglobal.h>

QT_BEGIN_NAMESPACE

class QGoogleAssistantAuth;
class QGoogleAssistantRequest;
class QGoogleAssistantResponse;
class QGoogleAssistantPrivate;
class QGoogleAssistantAudioInput;
class QGoogleAssistantAudioOutput;

class Q_GOOGLEASSISTANT_EXPORT QGoogleAssistant : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QGoogleAssistantAuth *auth READ auth CONSTANT)
    Q_PROPERTY(QGoogleAssistantAudioInput *audioInput READ audioInput CONSTANT)
    Q_PROPERTY(QGoogleAssistantAudioOutput *audioOutput READ audioOutput CONSTANT)
    Q_PROPERTY(QLocale locale READ locale WRITE setLocale NOTIFY localeChanged)
    Q_PROPERTY(QString apiEndpoint READ apiEndpoint WRITE setApiEndpoint NOTIFY apiEndpointChanged)
    Q_PROPERTY(QString deviceIdentifier READ deviceIdentifier WRITE setDeviceIdentifier NOTIFY deviceIdentifierChanged)
    Q_PROPERTY(QString deviceModel READ deviceModel WRITE setDeviceModel NOTIFY deviceModelChanged)
    Q_PROPERTY(Status status READ status NOTIFY statusChanged)
    Q_PROPERTY(QString lastError READ lastError NOTIFY lastErrorChanged)

public:
    explicit QGoogleAssistant(QObject *parent = nullptr);
    ~QGoogleAssistant();

    QGoogleAssistantAuth *auth() const;
    QGoogleAssistantAudioInput *audioInput() const;
    QGoogleAssistantAudioOutput *audioOutput() const;

    QLocale locale() const;
    void setLocale(const QLocale &locale);

    QString apiEndpoint() const;
    void setApiEndpoint(const QString &apiEndpoint);

    QString deviceIdentifier() const;
    void setDeviceIdentifier(const QString &identifier);

    QString deviceModel() const;
    void setDeviceModel(const QString &model);

    enum Status {
        Ok = 0,
        Cancelled = 1,
        Unknown = 2,
        InvalidArgument = 3,
        DeadlineExceeded = 4,
        NotFound = 5,
        AlreadyExists = 6,
        PermissionDenied = 7,
        Unauthenticated = 16,
        ResourceExhausted = 8,
        FailedPrecondition = 9,
        Aborted = 10,
        OutOfRange = 11,
        Unimplemented = 12,
        Internal = 13,
        Unavailable = 14,
        DataLoss = 15
    };
    Q_ENUM(Status)

    Status status() const;
    QString lastError() const;

public Q_SLOTS:
    void textRequest(const QString &text);
    void audioRequest(const QByteArray &audio);
    void request(const QGoogleAssistantRequest &request);

Q_SIGNALS:
    void response(const QGoogleAssistantResponse &response);
    void finished(Status status);
    void statusChanged(Status status);
    void lastErrorChanged(const QString &error);
    void localeChanged(const QLocale &locale);
    void apiEndpointChanged(const QString &apiEndpoint);
    void deviceIdentifierChanged(const QString &deviceIdentifier);
    void deviceModelChanged(const QString &deviceModel);

private:
    Q_DISABLE_COPY(QGoogleAssistant)
    Q_DECLARE_PRIVATE(QGoogleAssistant)
};

QT_END_NAMESPACE

#endif // QGOOGLEASSISTANT_H
