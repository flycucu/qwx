// Copyright (C) 2014 Leslie Zhai <xiang.zhai@i-soft.com.cn>

import QtQuick 2.2
import QtQuick.Controls 1.1
import cn.com.isoft.qwx 1.0

Item {
    id: chatView
    width: parent.width; height: parent.height

    property string uin
    property string sid
    property string skey
    property string fromUserName
    property string toUserName
    property string toNickName

    SendMsg {
        id: sendMsgObj
    }

    Image {
        id: backImage
        source: "../images/back.png"

        MouseArea {
            anchors.fill: parent
            onClicked: {
                navigatorStackView.pop()
            }
        }
    }

    ListModel {
        id: chatListModel

        ListElement { content: "" }
    }

    ListView {
        id: chatListView
        model: chatListModel
        width: parent.width; height: parent.height - backImage.height - 
        sendMsgTextField.height
        anchors.top: backImage.bottom
        delegate: Item {
            height: 60
            Text { text: content }
        }
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
            chatListModel.append({"content": sendMsgTextField.text})
            sendMsgTextField.text = ""
        }
    }
}
