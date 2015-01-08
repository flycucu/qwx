// Copyright (C) 2014 Leslie Zhai <xiang.zhai@i-soft.com.cn>

import QtQuick 2.2
import QtQuick.Controls 1.1
import cn.com.isoft.qwx 1.0

Rectangle {
    id: splashView
    width: parent.width; height: parent.height
    color: "#010510"

    property bool v2: false

    QwxUUID {
        id: uuidObj
        onError: {
            console.log("ERROR: 获取UUID失败!")
        }
        onUuidChanged: {
            rootWindowStackView.clear()                                            
            rootWindowStackView.push({                                             
                item: Qt.resolvedUrl("LoginView.qml"),                         
                properties: {uuid: uuid, v2: splashView.v2}})
        }
    }

    Image {
        source: "../images/splash.jpg"
        width: parent.width; height: parent.height
    }
}
