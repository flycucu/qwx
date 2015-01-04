// Copyright (C) 2014 - 2015 Leslie Zhai <xiang.zhai@i-soft.com.cn>

import QtQuick 2.2
import QtQuick.Controls 1.1
import cn.com.isoft.qwx 1.0

Item {
    id: contactListView
    width: parent.width; height: parent.height

    property bool v2: false
    property string uin
    property string sid
    property string skey
    property string deviceId
    property string ticket
    property string loginUserName
    property var syncKey

    Contact {
        id: contactObj
        onContactListChanged: {
            modContactListView.model = contactObj.contactList
        }
    }

    ListView {
        id: modContactListView
        anchors.fill: parent

        delegate: Item {
            width: parent.width; height: 60

            HeadImg {                                                              
                v2: contactListView.v2
                userName: modelData.userName                                       
                onFilePathChanged: {                                               
                    headImage.imageSource = filePath
                }                                                                  
            }                                                                      
                                                                                   
            CircleImage {
                id: headImage                                                      
                width: 42; height: 42                                              
                anchors.top: parent.top                                            
                anchors.topMargin: 8                                               
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
                            v2: contactListView.v2,
                            uin: contactListView.uin,                          
                            sid: contactListView.sid,                          
                            skey: contactListView.skey,
                            deviceId: contactListView.deviceId, 
                            ticket: contactListView.ticket,         
                            fromUserName: contactListView.loginUserName,       
                            toUserName: modelData.userName,                    
                            toNickName: modelData.nickName, 
                            syncKey: contactListView.syncKey}})                  
                }                                                              
            }
        }
    }
}
