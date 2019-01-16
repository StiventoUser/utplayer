import QtQuick 2.0
import QtQuick.Controls.Universal 2.3

Rectangle
{
    TopBrowsePanel
    {
        id: topPanel

        anchors
        {
            left: parent.left
            top: parent.top
            right: parent.right
        }

        height: 80
    }

    LeftBrowsePanel
    {
        id: leftPanel

        anchors
        {
            left: parent.left
            top: topPanel.bottom
            bottom: parent.bottom
        }

        width: 200
    }

    VideosView
    {
        id: videosView

        anchors
        {
            left: leftPanel.right
            top: topPanel.bottom
            right: parent.right
            bottom: parent.bottom
        }
    }
}
