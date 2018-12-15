import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtCharts 2.2
import Qt.labs.calendar 1.0

Item {
    id: item1
    property alias chartView: chartView

    Connections {
        target: NetworkManager
        onValueUpdated: {
            y = y * 100
            series.append(x, y)
            if (x > xAxis.max) {
                xAxis.max = x
            }
            if (y > yAxis.max) {
                yAxis.max = y
            }
        }
    }

    ColumnLayout {
        id: columnLayout
        anchors.fill: parent

        RowLayout {
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: 10
            Text {
                id: text1
                color: "#d323c9"
                text: qsTr("High Chart")
                z: 1
                font.italic: true
                font.pointSize: 20
            }
        }
    }

    Item {
        id: item2
        x: 0
        y: 58
        width: parent.width
        height: parent.height
        anchors.top: parent.top
        anchors.topMargin: 53
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 27

        ChartView {
            id: chartView
            anchors.rightMargin: 114
            title: ""
            anchors.fill: parent
            theme: ChartView.ChartThemeLight
            ValueAxis {
                id: yAxis
                titleText: "High*100 "
                titleVisible: true
                gridVisible: true
                tickCount: 11
                min: 0
                max: 1000
            }
            DateTimeAxis {
                id: xAxis
                format: qsTr("yyyy-MM-dd")
                tickCount: 20
                visible: true
                labelsAngle: 90
                gridVisible: true
                min: "2018-07-19"
                max: "2018-12-10"
            }
            LineSeries {
                id: series
                axisX: xAxis
                axisY: yAxis
                name: "daily time series"
                visible: true
            }
        }
    }
}


/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
