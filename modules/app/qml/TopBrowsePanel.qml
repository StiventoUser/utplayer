import QtQuick 2.0
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3
import QtQuick.Controls.Universal 2.3

Rectangle {
	color: Universal.background

	RowLayout {
		anchors.fill: parent

		Item {
			width: 20
		}

		Button {
			text: "Home"
			Layout.preferredHeight: parent.height * 0.5
		}

		Item {
			// spacer item
			Layout.fillWidth: true
			Layout.fillHeight: true
		}

		SearchFieldItem {
			Layout.preferredWidth: 250
			Layout.preferredHeight: parent.height * 0.5
		}

		Item {
			width: 20
		}
	}
}
