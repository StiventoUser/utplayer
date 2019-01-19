import QtQuick 2.11
import QtQuick.Window 2.11
import QtQuick.Controls 2.4
import QtQuick.Controls.Universal 2.3

ApplicationWindow
{
    visible: true
    width: 1280
    height: 960
    title: qsTr("UT Player")

    Universal.theme: Universal.Dark
    Universal.accent: Universal.Red

    BrowseView
    {
        anchors.fill: parent
    }
}
