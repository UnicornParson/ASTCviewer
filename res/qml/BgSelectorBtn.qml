import QtQuick 2.0
import QtQuick.Controls 2.12
import BGType 1.0

Button {
    id: root
    background: Rectangle {color: "transparent"}
    property int type: BGType.BGType_white


    Rectangle {
        anchors.fill: parent
        radius: width/2
        color: (type === BGType.BGType_black) ? "black" : "white"
        visible: (type === BGType.BGType_black) || (type === BGType.BGType_white)
    }

    Rectangle {
        anchors.fill: parent
        visible: (type === BGType.BGType_transparent)
        radius: width/2
        Image {
            anchors.fill: parent
            id: transparentIcon

            source: "qrc:/img/res/transparentBtn.png"

        }
    }

    Rectangle {
        anchors.fill: parent
        visible: type === BGType.BGType_gradient
        radius: width/2
        gradient: Gradient {
            GradientStop { position: 0.0; color: "red" }
            GradientStop { position: 0.5; color: "yellow" }
            GradientStop { position: 1.0; color: "green" }
        }
    }

    MouseArea {
        anchors.fill: parent
        onClicked: {
            if(fvsource)
            {
                fvsource.setBackgroundType(type)
            }
        }
    }
}
