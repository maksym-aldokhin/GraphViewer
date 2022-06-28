import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts 1.15
import Palette 1.0

import "../qmlSimple"

Window {
	id: root

	width: 640
	height: 480

	visible: true
	title: qsTr("Graphics")

	Rectangle {
		id: mainSpace
		anchors.fill: parent

		color: Palette.color1()

		RowLayout {
			anchors {
				fill: parent
				rightMargin: 4
				leftMargin: 4
				topMargin: 4
				bottomMargin: 4
			}

			spacing: 6

			GraphicLegend {
				Layout.minimumWidth: 200
				Layout.fillHeight: true

				model: GraphicModel
			}

			Graphic {
				Layout.fillWidth: true
				Layout.fillHeight: true

				model: GraphicModel
			}
		}
	}
}
