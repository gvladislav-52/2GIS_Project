import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts

ApplicationWindow {
    visible: true
    width: 600
    height: 300
    title: "Histogram"

    Histogram
    {
        width: parent.width *0.7
        height: parent.height
    }
}
