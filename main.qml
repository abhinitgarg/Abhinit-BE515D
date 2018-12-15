import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtCharts 2.2

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Abhinit Garg")

    SwipeView {
        id: swipeView
        anchors.fill: parent
        currentIndex: tabBar.currentIndex

        Page2
        {

               }


        Page3
        {

               }


    }

    footer: TabBar {
        id: tabBar
        currentIndex: swipeView.currentIndex

        TabButton {
            text: qsTr("Volume chart")
        }
        TabButton {
            text: qsTr("close chart")
        }
    }
}
