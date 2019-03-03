import QtQuick 2.0
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3
import QtQuick.Controls.Universal 2.3
import "../js/time.js" as Time

Rectangle {
	id: root

	color: Universal.background

	ColumnLayout {
		anchors.fill: parent

		Image {
			id: thumbnail

			//Layout.fillWidth: true
			//Layout.fillHeight: true

			Layout.minimumWidth: view.cellWidth
			Layout.minimumHeight: view.cellHeight - view.additionalHeight

			source: model.thumbnailMediumUrl
			fillMode: Image.PreserveAspectFit 

			Item {
				anchors.fill: parent

				Rectangle {
					anchors {
						right: parent.right
						bottom: parent.bottom
					}

					color: "black"

					width: timeText.contentWidth
					height: timeText.contentHeight

					Text {
						id: timeText
						anchors.centerIn: parent

						color: Universal.foreground
						font.pointSize: 11

						text: Time.generateReadableDuration(model.videoDuration)
					}
				}
			}
		}

		Text {
			Layout.fillWidth: true
			Layout.minimumHeight: view.additionalHeight / 3

			text: model.videoTitle
			color: Universal.foreground
			font.pointSize: 11

			horizontalAlignment: Text.AlignLeft
			verticalAlignment: Text.AlignVCenter
			wrapMode: Text.Wrap
		}

		Text {
			Layout.fillWidth: true
			Layout.minimumHeight: view.additionalHeight / 3

			text: model.channelTitle
			color: Universal.foreground
			font.pointSize: 10

			horizontalAlignment: Text.AlignLeft
			verticalAlignment: Text.AlignVCenter
			wrapMode: Text.Wrap
		}

		Rectangle {
			Layout.fillWidth: true
			Layout.minimumHeight: view.additionalHeight / 3

			color: Universal.background

			Item
			{
				anchors {
					horizontalCenter: parent.horizontalCenter
					top: parent.top
					bottom: parent.bottom
				}
				
				width: parent.width * 0.95
			
				Text {
					anchors
					{
						top: parent.top
						bottom: parent.bottom
						left: parent.left
					}

					width: parent.width * 0.5

					text: model.viewCount
					color: Universal.foreground
					font.pointSize: 10

					horizontalAlignment: Text.AlignLeft
					verticalAlignment: Text.AlignVCenter
					wrapMode: Text.Wrap
				}

				Text {
					anchors
					{
						top: parent.top
						right: parent.right
						bottom: parent.bottom
					}

					width: parent.width * 0.5

					text: Time.timeDifference(new Date(), new Date(model.publishedAt))
					color: Universal.foreground
					font.pointSize: 10

					horizontalAlignment: Text.AlignRight
					verticalAlignment: Text.AlignVCenter
					wrapMode: Text.Wrap
				}
			}
		}
	}
}
