// Copyright (C) 2014 Leslie Zhai <xiang.zhai@i-soft.com.cn>

import QtQuick 2.2
import QtQuick.Window 2.1
import QtQuick.Controls 1.1
import cn.com.isoft.qwx 1.0

Window {
    id: chatView
    width: 500; height: 300
    title: chatView.toNickName

    property string uin
    property string sid
    property string skey
    property string fromUserName
    property string toUserName
    property string toNickName

    SendMsg {
        id: sendMsgObj
    }

    TextField {
        id: sendMsgTextField
        width: parent.width - sendButton.width
        anchors.bottom: parent.bottom
    }

    Button {
        id: sendButton
        text: "发送"
        anchors.top: sendMsgTextField.top
        anchors.right: parent.right
        onClicked: {
            sendMsgObj.post(chatView.uin, 
                            chatView.sid, 
                            chatView.skey, 
                            chatView.fromUserName, 
                            chatView.toUserName, 
                            sendMsgTextField.text)
        }
    }
}
