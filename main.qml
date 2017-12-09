import QtQuick 2.3
import QtQuick.Window 2.2
import QtWebEngine 1.5

Window {
    visible: true
    width: 1024
    height: 768
    title: qsTr("QtPlex")

    WebEngineView {
        anchors.fill: parent
        url: "http://192.168.1.100:32400/web"
    }
}
