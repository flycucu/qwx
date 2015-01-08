// Copyright (C) 2014 - 2015 Leslie Zhai <xiang.zhai@i-soft.com.cn>

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

    ListModel {                                                                    
        id: wxListModel                                                          
        Component.onCompleted: {                                                   
            wxListModel.remove(0)                                          
        }                                                                          
                                                                                   
        ListElement { mUserName: ""; mNickName: "" } 
    }

    Component.onCompleted: {
        for (var i = 0; i < wxView.initObj.contactList.length; i++) {
            wxListModel.append({"mUserName": wxView.initObj.contactList[i].userName, 
                                "mNickName": wxView.initObj.contactList[i].nickName}) 
        }
    }

    Contact {                                                                      
        id: contactObj                                                             
        Component.onCompleted: {                                                   
            if (wxView.v2) {                                              
                contactObj.postV2()                                                
            } else {                                                               
                contactObj.post()                                                  
            }                                                                      
        }                                                                          
    }

    GetMsg {
        id: getMsgObj
        onNewMsg: {
            var isExist = false
            for (var i = 0; i < wxListModel.count; i++) {
                var userName = wxListModel.get(i).mUserName
                if (userName == fromUserName || 
                    userName == toUserName) {
                    isExist = true
                    break
                }
            }

            if (isExist == false) {
                if (wxView.loginUserName == fromUserName) {
                    wxListModel.insert(0, {"mUserName": toUserName, 
                            "mNickName": contactObj.getNickName(toUserName)})
                } else {
                    wxListModel.insert(0, {"mUserName": fromUserName, 
                            "mNickName": contactObj.getNickName(fromUserName)})
                }
            }
        }
    }

    Timer {                                                                        
        id: getMsgTimer                                                            
        interval: 1000; running: true; repeat: true; triggeredOnStart: true        
        onTriggered: {                                                             
            if (wxView.v2) {                                                     
                getMsgObj.postV2(wxView.uin, wxView.sid, wxView.skey, wxView.syncKey)
            } else {                                                               
                getMsgObj.post(wxView.uin, wxView.sid, wxView.skey, wxView.syncKey)
            }                                                                      
        }                                                                          
    }

    ListView {
        id: wxListView
        model: wxListModel
        anchors.fill: parent

        delegate: Item {
            width: parent.width; height: 60

            HeadImg {
                id: headImgObj
                v2: wxView.v2
                userName: mUserName
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
                text: mNickName
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
                            toUserName: mUserName,                    
                            toNickName: mNickName, 
                            syncKey: wxView.syncKey}})                  
                }                                                              
            }
        }
    }
}
