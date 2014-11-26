// Copyright (C) 2014 Leslie Zhai <xiang.zhai@i-soft.com.cn>

import QtQuick 2.2
import QtQuick.Controls 1.1
import cn.com.isoft.qwx 1.0

Item {
    id: wxView
    width: parent.width; height: parent.height

    property string uin
    property string sid
    property string skey
    property var initObj

    SendMsg {
        id: sendMsgObj
    }

    ListView {
        id: wxListView
        model: initObj.contactList
        anchors.fill: parent

        delegate: Item {
            height: 30
            
            /* FIXME: ./src/modcontact.cpp it ONLY works in web browser ...
            Image {
                source: modelData.HeadImgUrl
            }
            */

            Text {
                text: modelData.nickName

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        console.log("DEBUG: only for test sending msg")
                        // TODO: it needs to get current login user account ;)
                        sendMsgObj.post(wxView.uin, 
                                        wxView.sid, 
                                        wxView.skey, 
                                        wxView.initObj.loginUserName, 
                                        modelData.userName, 
                                        "您好 " + modelData.nickName + " 消息来自qwx https://github.com/xiangzhai/qwx 欢迎一起来鼓捣 ^_^")
                    }
                }
            }
        }
    }
}
