// Copyright (C) 2014 Leslie Zhai <xiang.zhai@i-soft.com.cn>

import QtQuick 2.2
import QtQuick.Controls 1.1
import cn.com.isoft.qwx 1.0

Item {
    id: contactListView
    width: parent.width; height: parent.height

    property string uin
    property string sid
    property string skey
    property var initObj

    ModContact {
        id: modContactObj
        uin: contactListView.uin
        sid: contactListView.sid
        onModContactListChanged: {
            modContactListView.model = modContactObj.modContactList
        }
    }

    SendMsg {
        id: sendMsgObj
    }

    ListView {
        id: modContactListView
        anchors.fill: parent

        delegate: Item {
            height: 60

            HeadImg {                                                              
                id: headImgObj                                                     
                userName: modelData.userName                                       
                onFilePathChanged: {                                               
                    headImage.source = headImgObj.filePath                         
                }                                                                  
            }                                                                      
                                                                                   
            Image {                                                                
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

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        var component = Qt.createComponent("ChatView.qml")         
                        var chatView = component.createObject(                     
                            Qt.resolvedUrl("ChatView.qml"),                        
                            {"uin": contactListView.uin, 
                             "sid": contactListView.sid,
                             "skey": contactListView.skey,
                             "fromUserName": contactListView.initObj.loginUserName,
                             "toUserName": modelData.userName,
                             "toNickName": modelData.nickName})                    
                        chatView.show()
                    }
                }
            }
        }
    }
}
