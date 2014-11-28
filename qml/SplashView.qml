// Copyright (C) 2014 Leslie Zhai <xiang.zhai@i-soft.com.cn>

import QtQuick 2.2
import QtQuick.Controls 1.1
import cn.com.isoft.qwx 1.0

Rectangle {
    id: loginView
    width: parent.width; height: parent.height
    color: "#010510"

    UUID {
        id: uuidObj
        onError: {
            console.log("ERROR: 获取UUID失败!")
        }
        onUuidChanged: {
            rootWindowStackView.clear()                                            
            rootWindowStackView.push({                                             
                item: Qt.resolvedUrl("LoginView.qml"),                         
                properties: {uuid: uuid}})
        }
    }

    Image {
        source: "../images/splash.jpg"
        width: parent.width; height: parent.height
    }
}
