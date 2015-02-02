// Copyright (C) 2014 - 2015 Leslie Zhai <xiang.zhai@i-soft.com.cn>

import QtQuick 2.2
import "global.js" as Global 

Item { 
    Image {                                                                        
        id: qrcodeImage 
        source: "http://qr.liantu.com/api.php?text=" + Global.loginNickName + "&logo=https://open.weixin.qq.com/zh_CN/htmledition/res/assets/res-design-download/icon64_wx_logo.png" 
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent
        anchors.topMargin: 31
    }
}
