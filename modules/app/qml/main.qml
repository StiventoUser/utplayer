import QtQuick 2.11
import QtQuick.Window 2.11
import QtQuick.Controls 2.4
import QtQuick.Controls.Universal 2.3
import api.YtMethods 1.0

ApplicationWindow
{
    id: root

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

    YtWrapper
    {
        authUri: AuthUri
        clientId: ClientId
        clientSecret: ClientSecret
        redirectUri: RedirectUri
        tokenUri: TokenUri

        Component.onCompleted: {
            Authorize();
        }

        onAccessGranted: {
            root.title = "Granted"
        }
    }
}
