import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import BGType 1.0

Item
{
    id: root

    QtObject {
        id: internal
        property color panelColorStart: "#253536"
        property color panelColorStop: "#000"
        property int imgHeight: 0
        property var source: (fvsource) ? null: fvsource
        onSourceChanged: {
            console.warn("source changed", source)
        }
    }

    Item {
        id: bgComponent

        visible: !!internal.source
        anchors.fill: root

        Rectangle
        {
            id: bgSolid
            anchors.fill: parent
            color: (!!internal.source && internal.source.backgroundType === BGType.BGType_black) ? "black" : "white"
            visible: !!internal.source && internal.source.backgroundTypeSolid
        }

        Image {
            id: bgImage
            source: (!!internal.source && internal.source.backgroundType === BGType.BGType_transparent) ?
                        "qrc:/img/res/transparent.png" : "qrc:/img/res/gradient.jpg"
            anchors.fill: parent
            visible: !!internal.source && internal.source.backgroundTypeImage
        }
    }

    Rectangle {
        id: topPanel

        anchors {
            left: root.left
            right: root.right
            top: root.top
        }
        gradient: Gradient {
            GradientStop { position: 0.0; color: internal.panelColorStart }
            GradientStop { position: 0.8; color: internal.panelColorStart }
            GradientStop { position: 1.0; color: internal.panelColorStop }
        }
        height: 32

        RowLayout {
            id: bgIconsLayout
            anchors {
                top: parent.top
                bottom: parent.bottom
                horizontalCenter: parent.horizontalCenter
            }
            height: 14

            BgSelectorBtn {
                type: BGType.BGType_white
                Layout.alignment: Qt.AlignVCenter
                height: 16
                width: 16
            }
            BgSelectorBtn {
                type: BGType.BGType_black
                Layout.alignment: Qt.AlignVCenter
                height: 16
                width: 16
            }
            BgSelectorBtn {
                type: BGType.BGType_transparent
                Layout.alignment: Qt.AlignVCenter
                height: 16
                width: 16
            }
            BgSelectorBtn {
                type: BGType.BGType_gradient
                Layout.alignment: Qt.AlignVCenter
                height: 16
                width: 16
            }
        }
    }



    Image {
        id: contentImage
        source: (!!internal.source && internal.source.currentPath !== "") ? ("file:///" + internal.source.currentPath) : "qrc:/img/res/clicktoopen.png"
        visible: !!internal.source
        anchors {
            horizontalCenter: root.horizontalCenter
            top: topPanel.bottom
            bottom: bottomPanel.top
        }
        fillMode: Image.PreserveAspectFit
    }

    Rectangle {
        id: border

        property int borderWidth: 2

        anchors.centerIn: contentImage
        color: "transparent"
        width: Math.min(contentImage.sourceSize.width, contentImage.width) + borderWidth * 2
        height: Math.min(contentImage.sourceSize.height, contentImage.height)  + borderWidth * 2
        border.color: (!!internal.source && internal.source.backgroundType === BGType.BGType_black) ? "white" : "black"
        border.width: borderWidth
        visible: (!!fvsource && fvsource.currentPath)
        opacity: 0.5
    }

    Rectangle {
        id: bottomPanel

        anchors {
            left: root.left
            right: root.right
            bottom: root.bottom
        }
        gradient: Gradient {
            GradientStop { position: 0.0; color: internal.panelColorStop }
            GradientStop { position: 0.1; color: internal.panelColorStop }
            GradientStop { position: 1.0; color: internal.panelColorStart }
        }
        height: 24

        MouseArea
        {
            id: burgerBtn
            anchors {
                left: parent.left
                verticalCenter: parent.verticalCenter
                leftMargin: 16
            }
            Image
            {
                id: burgerBtnImg
                anchors.fill: parent
                source: "qrc:/img/res/open.png"
            }

            width: 16
            height: 16
            onEntered: {burgerBtnImg.source = "qrc:/img/res/open2.png"}
            onExited: {burgerBtnImg.source = "qrc:/img/res/open.png"}
            onReleased: {fvsource.fileDialogRequested()}
        }

        Text {
            id: imageInfo

            property string message: internal.source.currentPath + " size: " + contentImage.sourceSize
            anchors {
                centerIn: parent
            }
            color: "white"
            text: (!!fvsource && fvsource.currentPath) ? message : "<--- click open button"
        }
    }
    MouseArea
    {
        anchors {
            left: root.left
            right: root.right
            top: topPanel.bottom
            bottom: bottomPanel.top
        }
        onReleased: {
            if(fvsource)
            {
                fvsource.fileDialogRequested()
            }
        }
    }
    Component.onCompleted: {
        console.debug("root completed", fvsource.currentPath);
        fvsource.folderContent()
        internal.source = fvsource
    }
}
