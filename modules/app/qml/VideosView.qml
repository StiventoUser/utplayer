import QtQuick 2.0
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3
import QtQuick.Controls.Universal 2.3

import api.GApiMethods 1.0
import api.GApiMethods.Commands 1.0

Rectangle {
	id: root

	property var commandExecutor: null

	color: Universal.background

	function loadVideos() {
		commandExecutor.execute(getMostPopularCommand);
	}

	Component.onCompleted: {
		view.model = getMostPopularCommand.getModel();
		loadVideos();
	}

	GetMostPopular {
		id: getMostPopularCommand

		onCommandReadResponse: {
			var yPos = view.contentY;
			var yVel = view.verticalVelocity;
			var pageModel = getMostPopularCommand.getPageModel();
			view.model.appendModel(pageModel);

			if (view.model.rowCount() > 0) {
				var firstItem = pageModel.getItemMapByIndex(0);
				view.imageWidth = firstItem.thumbnailMediumWidth;
				view.imageHeight = firstItem.thumbnailMediumHeight;	
			}

			view.contentY = yPos;
			view.updateSizes();
		}
	}

	GridView {
		id: view
		anchors.fill: parent

		clip: true

		property real imageWidth: 0
		property real imageHeight: 0
		property real additionalHeight: 60
		property real spacing: 10

		Component.onCompleted: {
			updateSizes();
		}	

		onImageWidthChanged: {
			updateSizes();
		}

		onWidthChanged: {
			updateSizes();
		}

		onContentYChanged: {
			if (visibleArea.yPosition + visibleArea.heightRatio > 0.9) {
				loadVideos();
			}
		}

		function updateSizes() {
			var freeSpace = width % imageWidth;
			var itemsPerRow = Math.floor(width / imageWidth);
			// Subtract extra pixel to remove GridView random items jumping.
			cellWidth = imageWidth + freeSpace / itemsPerRow - 1;
			cellHeight = imageHeight * (cellWidth / imageWidth) + additionalHeight;
		}

		ScrollBar.vertical: ScrollBar {
		}

		delegate: Rectangle {
			width: view.cellWidth
			height: view.cellHeight

			color: Universal.background

			VideoRectangleDelegate {
				anchors.fill: parent
				//anchors.centerIn: parent
				//width: parent.width - view.spacing * 2
				//height: parent.height - view.spacing * 2
			}
		}
	}
}
