import QtQuick 2.11
import QtQuick.Window 2.11
import QtQuick.Controls 2.4
import QtQuick.Controls.Universal 2.3

import api.GApiMethods 1.0

ApplicationWindow {
	id: root

	visible: true
	width: 1280
	height: 960
	title: qsTr("UT Player")

	Universal.theme: Universal.Dark
	Universal.accent: Universal.Red

	BrowseView {
		id: view
		anchors.fill: parent

		commandExecutor: executor
	}

	GApiWrapper {
		id: apiWrapper

		accessData: AccessData

		Component.onCompleted: {

			//authorize();
		}

		onAccessGranted: {
			root.title = "Granted"
		}
	}

	UserProfile {
		id: userProfile
	}

	GApiCommandExecutor {
		id: executor

		apiWrapper: apiWrapper
		userProfile: userProfile
	}
}
