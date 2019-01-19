import QtQuick 2.0
import QtQuick.Controls 2.4
import QtQuick.Controls.Universal 2.3

Rectangle
{
    id: root

    width: 200
    height: 50

    color: Universal.background
    state: "Default"

    signal searchRequested(string text)

    Text
    {
        id: searchLabel
        anchors.fill: parent

        text: qsTr("Search")
        color: Universal.accent
        font.pointSize: 12
        horizontalAlignment: Qt.AlignRight
        verticalAlignment: Qt.AlignVCenter
    }

    Item
    {
        id: searchBox
        anchors.fill: parent

        TextField
        {
            id: searchText
            anchors.fill: parent

            onFocusChanged:
            {
                if (!focus)
                {
                    text = "";
                    root.state = "Default";
                }
            }

            Keys.onEscapePressed:
            {
                text = "";
                root.state = "Default";
            }

            onAccepted:
            {
                root.searchRequested(text)
                text = "";
                root.state = "Default";
            }
        }
    }

    MouseArea
    {
        id: mouseArea

        anchors.fill: parent

        onClicked:
        {
            root.state = root.state == "Default" ? "Active" : "Default"
        }
    }

    states: [
        State
        {
            name: "Default"

            PropertyChanges
            {
                target: searchLabel
                opacity: 1
            }

            PropertyChanges
            {
                target: searchBox
                opacity: 0
            }

            PropertyChanges
            {
                target: mouseArea
                visible: true
            }
        },
        State
        {
            name: "Active"

            PropertyChanges
            {
                target: searchLabel
                opacity: 0
            }

            PropertyChanges
            {
                target: searchBox
                opacity: 1
            }

            PropertyChanges
            {
                target: mouseArea
                visible: false
            }

            PropertyChanges
            {
                target: searchText
                focus: true
            }
        }
    ]

    transitions: [
        Transition
        {
            from: "Default"
            to: "Active"

            NumberAnimation
            {
                properties: "opacity"
                duration: 500
                easing.type: Easing.InOutQuad
            }
        },
        Transition
        {
            from: "Active"
            to: "Default"

            NumberAnimation
            {
                properties: "opacity"
                duration: 250
                easing.type: Easing.InOutQuad
            }
        }
    ]
}
