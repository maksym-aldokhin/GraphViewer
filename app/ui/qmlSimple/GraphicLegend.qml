import QtQuick 2.0
import QtQuick.Layouts 1.15

Item {
	property alias model: listGraphics.model

	ListView {
		id: listGraphics

		anchors.fill: parent

		width: 200

		spacing: 6

		delegate: GraphicNode {
			width: listGraphics.width

			garphicName: name
			garphicDescription: description
			lastValue: lastValueY

			onVisibleStateChanged: {
				visibleGraphic = visibleState
			}
		}
	}

}
