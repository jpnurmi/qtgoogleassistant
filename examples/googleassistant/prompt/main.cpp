/****************************************************************************
**
** Copyright (C) 2019 J-P Nurmi <jpnurmi@gmail.com>
**
** This file is part of QtGoogleAssistant examples.
**
** Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**
** 1. Redistributions of source code must retain the above copyright notice,
**    this list of conditions and the following disclaimer.
**
** 2. Redistributions in binary form must reproduce the above copyright
**    notice, this list of conditions and the following disclaimer in the
**    documentation and/or other materials provided with the distribution.
**
** 3. Neither the name of the copyright holder nor the names of its
**    contributors may be used to endorse or promote products derived from
**    this software without specific prior written permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
** IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
** THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
** PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
** CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
** EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
** PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
** PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
** LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
** NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
** SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**
****************************************************************************/

#include <QtGoogleAssistant>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QTextStream qin(stdin);
    QTextStream qout(stdout);

    QGoogleAssistant assistant;
    assistant.setClientIdentifier("139782839008-p92a7t3bfia2c2bhudbc08batphlg1et.apps.googleusercontent.com");
    assistant.setClientSecret("mDT2imOGRTaAJyuussj5QbPP"); // not really a secret

    QObject::connect(&assistant, &QGoogleAssistant::authorizeWithBrowser, &QDesktopServices::openUrl);

    QObject::connect(&assistant, &QGoogleAssistant::errorOccurred, [&](const QString &errorString) {
        qout << "ERROR:" << errorString << endl;
        app.quit();
    });

    QObject::connect(&assistant, &QGoogleAssistant::response, [&](const QGoogleAssistantResponse &response) {
        QString supplementalDisplayText = response.dialogStateOut().supplementalDisplayText();
        if (!supplementalDisplayText.isEmpty())
            qout << supplementalDisplayText << endl;
    });

    QSocketNotifier notifier(fileno(stdin), QSocketNotifier::Read);
    QObject::connect(&notifier, &QSocketNotifier::activated, [&]() {
        QString line;
        if (!qin.readLineInto(&line) || line.isEmpty()) {
            app.quit();
        } else {
            notifier.setEnabled(false);
            assistant.textRequest(line);
        }
    });

    QObject::connect(&assistant, &QGoogleAssistant::finished, [&]() {
        qout << "> " << flush;
        notifier.setEnabled(true);
    });

    QObject::connect(&assistant, &QGoogleAssistant::authenticated, [&]() {
        qout << "> " << flush;
        notifier.setEnabled(true);
    });

    assistant.authenticate();
    return app.exec();
}
