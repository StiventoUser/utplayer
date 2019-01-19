import QtQuick 2.0
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3
import QtQuick.Controls.Universal 2.3
import QtGraphicalEffects 1.0

Rectangle
{
    id: root

    color: Universal.background

    ColumnLayout
    {
        anchors.fill: parent
        spacing: 0

        property int buttonHeight: 50

        UserButton
        {
            Layout.fillWidth: true
            Layout.preferredHeight: width * 0.5
        }

        Button
        {
            text: qsTr("Recommendations")
            Layout.fillWidth: true
            Layout.preferredHeight: parent.buttonHeight
            Universal.foreground: Universal.accent
        }

        Button
        {
            text: qsTr("Subscriptions")
            Layout.fillWidth: true
            Layout.preferredHeight: parent.buttonHeight
            Universal.foreground: Universal.accent
        }

        Button
        {
            text: qsTr("Channels")
            Layout.fillWidth: true
            Layout.preferredHeight: parent.buttonHeight
            Universal.foreground: Universal.accent
        }

        Button
        {
            text: qsTr("Watch later")
            Layout.fillWidth: true
            Layout.preferredHeight: parent.buttonHeight
            Universal.foreground: Universal.accent
        }

        Button
        {
            text: qsTr("Playlists")
            Layout.fillWidth: true
            Layout.preferredHeight: parent.buttonHeight
            Universal.foreground: Universal.accent
        }

        Button
        {
            text: qsTr("Liked")
            Layout.fillWidth: true
            Layout.preferredHeight: parent.buttonHeight
            Universal.foreground: Universal.accent
        }

        Button
        {
            text: qsTr("History")
            Layout.fillWidth: true
            Layout.preferredHeight: parent.buttonHeight
            Universal.foreground: Universal.accent
        }

        Item
        {
            Layout.fillHeight: true
        }
    }
}
