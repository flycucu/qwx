// Copyright (C) 2014 Leslie Zhai <xiang.zhai@i-soft.com.cn>

import QtQuick 2.2
import QtQuick.Controls 1.1
import QtQuick.Window 2.1

ApplicationWindow {
    id: rootWindow
    width: 320; height: 544

    StackView {
        id: rootWindowStackView
        anchors.fill: parent
        initialItem: SplashView {}
    }
}
