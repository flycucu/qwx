// Copyright (C) 2014 - 2015 Leslie Zhai <xiang.zhai@i-soft.com.cn>

import QtQuick 2.2
import QtQuick.Controls 1.1
import cn.com.isoft.qwx 1.0
import "global.js" as Global

Item {
    id: contactListView
    width: parent.width; height: parent.height

    function contactRefresh() 
    {
        if (Global.v2)
            contactObj.postV2();
        else
            contactObj.post();
    }

    Contact {
        id: contactObj
        Component.onCompleted: {
            contactRefresh();
        }
        onContactListChanged: {
            modContactListView.model = contactObj.contactList;
        }
    }

    ListView {
        id: modContactListView
        anchors.fill: parent
        delegate: Item {
            width: parent.width; height: 60

            HeadImg {                                                              
                v2: Global.v2
                userName: modelData.userName
                headImgUrl: modelData.headImgUrl
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
                    if (modelData.userName == "groupsend") {
                        navigatorStackView.push({
                            item: Qt.resolvedUrl("ChatView.qml"),
                            properties: {
                                fromUserName: Global.loginUserName,
                                toUserList: contactObj.contactList,
                                toNickName: "群发"
                            }
                        });
                    } else {
                        navigatorStackView.push({                                  
                            item: Qt.resolvedUrl("ChatView.qml"),
                            properties: {
                                fromUserName: Global.loginUserName,
                                toUserName: modelData.userName,
                                toNickName: modelData.nickName 
                            }
                        });
                    }
                }                                                              
            }
        }
    }
}
