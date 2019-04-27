import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2
import QtGoogleAssistant 1.0
import Qt.labs.settings 1.0

ApplicationWindow {
    id: window
    width: 640
    height: 480
    visible: true
    title: "maiAssistant"

    readonly property string prefix: "\u203a"

    Settings {
        id: settings
        property string refreshToken: assistant.refreshToken
    }

    GoogleAssistant {
        id: assistant

        audioInput.enabled: button.pressed

        refreshToken: settings.refreshToken
        clientIdentifier: "139782839008-p92a7t3bfia2c2bhudbc08batphlg1et.apps.googleusercontent.com"
        clientSecret: "mDT2imOGRTaAJyuussj5QbPP" // not really a secret
        onAuthorizeWithBrowser: Qt.openUrlExternally(url)

        onResponse: {
            for (var i = 0; i < response.speechResultCount; ++i) {
                var result = response.speechResult(i)
                if (result.stability === 1.0)
                    addEntry(qsTr("%1 \"%2\"").arg(prefix).arg(result.transcript))
            }
            if (response.hasDialogStateOut)
                addEntry(response.dialogStateOut.supplementalDisplayText)
        }

        Component.onCompleted: authenticate()
    }

    function addEntry(entry) {
        listModel.append({text: entry})
        ++listView.currentIndex
    }

    ListView {
        id: listView
        spacing: 10
        anchors.fill: parent
        highlightRangeMode: ListView.ApplyRange
        model: ListModel { id: listModel }
        delegate: Label {
            padding: 10
            text: model.text
            width: parent.width
            wrapMode: Label.Wrap
        }
        ScrollIndicator.vertical: ScrollIndicator{ }
    }

    footer: RowLayout {
        TextField {
            id: textField
            focus: true
            placeholderText: qsTr("...")
            background.width: textField.width
            onAccepted: {
                addEntry(qsTr("%1 %2").arg(prefix).arg(textField.text))
                assistant.textRequest(text)
                textField.clear()
            }
            Layout.margins: 6
            Layout.fillWidth: true
            Material.accent: Material.Blue
        }
        RoundButton {
            id: button
            Layout.margins: 3
            focusPolicy: Qt.TabFocus
            Material.background: Material.Red
        }
    }
}
