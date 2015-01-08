// Copyright (C) 2014 - 2015 Leslie Zhai <xiang.zhai@i-soft.com.cn>

import QtQuick 2.2
import QtQuick.Controls 1.1
import cn.com.isoft.qwx 1.0

Rectangle {
    id: splashView
    width: parent.width; height: parent.height
    color: "#010510"

    QwxUUID {
        id: uuidObj
        onError: {
            console.log("ERROR: fail to get UUID!")
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
