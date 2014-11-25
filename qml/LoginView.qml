// Copyright (C) 2014 Leslie Zhai <xiang.zhai@i-soft.com.cn>

import QtQuick 2.2
import QtQuick.Controls 1.1
import cn.com.isoft.qwx 1.0

Item {
    id: loginView
    width: parent.width; height: parent.height

    property string uuid: ""
    property string tip: "1"

    UUID {
        id: uuidObj
        onError: {
            console.log("ERROR: fail to get uuid!")
        }
        onUuidChanged: {
            loginView.uuid = uuid
            qrcodeImage.source = "https://login.weixin.qq.com/qrcode/" + uuid + "?t=webwx"
            qrcodeImage.visible = true                     
            scanQRcode()
            scanTimer.start()
        }
    }

    Image {
        id: qrcodeImage
        visible: false
    }

    Scan {
        id: scanObj
        onError: {
            console.log("ERROR:", strerror)
        }
        onScanedButWaitConfirm: {
            console.log("DEBUG: scaned but waitting for confirm ...")
            loginView.tip = "0"
            statReportObj.firstRequestSuccess(loginView.uuid)
            statReportObj.secondRequestStart(loginView.uuid)
        }
        onScanedAndConfirmed: {
            console.log("DEBUG: confirmed")
            scanTimer.stop()
            cookieObj.get(redirect_uri)
        }
    }

    function scanQRcode() { scanObj.get(loginView.uuid, loginView.tip) }

    Timer {
        id: scanTimer
        interval: 16000; running: false; repeat: true
        onTriggered: { scanQRcode() }
    }

    Cookie {
        id: cookieObj
        onInfoChanged: {
            statReportObj.post(loginView.uuid)
            initObj.post(uin, sid)
            modContactObj.post(uin, sid)
            contactObj.post()
            //-----------------------------------------------------------------
            // TODO: only for test
            headImgObj.get("sirtoozee")
            statusNotifyObj.post(uin, sid, "sirtoozee")
            //-----------------------------------------------------------------
            stackView.clear()
            stackView.push({item: Qt.resolvedUrl("ContactListView.qml"), 
                            properties: {modContactObj: modContactObj, 
                                         uin: uin, sid: sid, skey: skey}})
        }
    }

    StatReport {
        id: statReportObj
    }

    Init {
        id: initObj
    }

    ModContact {
        id: modContactObj
    }

    Contact {
        id: contactObj
    }

    HeadImg {
        id: headImgObj
    }

    StatusNotify {
        id: statusNotifyObj
    }
}
