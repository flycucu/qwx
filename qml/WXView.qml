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
    property string ticket
    property string loginUserName
    property var syncKey
    property var initObj

    ListView {
        id: wxListView
        model: wxView.initObj.contactList
        anchors.fill: parent

        delegate: Item {
            width: parent.width; height: 60

            HeadImg {
                id: headImgObj
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
                            uin: wxView.uin,                                   
                            sid: wxView.sid,                                   
                            skey: wxView.skey,      
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
