// Copyright (C) 2014 Leslie Zhai <xiang.zhai@i-soft.com.cn>

import QtQuick 2.2
import QtQuick.Controls 1.1
import cn.com.isoft.qwx 1.0

Item {
    id: wxView
    width: parent.width; height: parent.height

    property bool v2: false
    property string uin
    property string sid
    property string skey
    property string deviceId
    property string ticket
    property string loginUserName
    property var syncKey
    property var initObj

    GetMsg {
        id: wxGetMsgObj
        onNewMsg: {}
    }

    Timer {
        id: wxGetMsgTimer
        interval: 3000; running: true; repeat: true; triggeredOnStart: true
        onTriggered: {
            if (wxView.v2) {
                wxGetMsgObj.postV2(wxView.uin, wxView.sid, wxView.skey, wxView.syncKey)
            } else {
                wxGetMsgObj.post(wxView.uin, wxView.sid, wxView.skey, wxView.syncKey)
            }
        }
    }

    ListView {
        id: wxListView
        model: wxView.initObj.contactList
        anchors.fill: parent

        delegate: Item {
            width: parent.width; height: 60

            HeadImg {
                id: headImgObj
                v2: wxView.v2
                userName: modelData.userName
                onFilePathChanged: {
                    headImage.imageSource = headImgObj.filePath
                }
            }

            CircleImage {
                id: headImage
                width: 42; height: 42
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.leftMargin: 10
            }

            Text {
                text: modelData.nickName
                font.pixelSize: 13
                anchors.top: parent.top
                anchors.topMargin: 14
                anchors.left: headImage.right
                anchors.leftMargin: 11
            }

            Rectangle {
                width: parent.width; height: 1
                color: "#dadada"
            }

            MouseArea {                                                        
                anchors.fill: parent                                           
                onClicked: {                                                   
                    navigatorStackView.push({                                  
                        item: Qt.resolvedUrl("ChatView.qml"),                  
                        properties: {                                          
                            v2: wxView.v2,
                            uin: wxView.uin,
                            sid: wxView.sid,                                   
                            skey: wxView.skey,
                            deviceId: wxView.deviceId,      
                            ticket: wxView.ticket,                            
                            fromUserName: wxView.loginUserName,                 
                            toUserName: modelData.userName,                    
                            toNickName: modelData.nickName, 
                            syncKey: wxView.syncKey}})                  
                }                                                              
            }
        }
    }
}
