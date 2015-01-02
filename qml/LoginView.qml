// Copyright (C) 2014 Leslie Zhai <xiang.zhai@i-soft.com.cn>

import QtQuick 2.2
import QtQuick.Controls 1.1
import cn.com.isoft.qwx 1.0

Item {
    id: loginView
    width: parent.width; height: parent.height

    property bool v2: false
    property string uuid
    property string tip: "1"
    property string uin
    property string sid
    property string skey
    property string ticket

    Text {
        id: titleText
        text: "微信"
        font.pixelSize: 22
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 42
    }

    Image {
        id: qrcodeImage
        source: "https://login.weixin.qq.com/qrcode/" + loginView.uuid + "?t=webwx"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: titleText.bottom
        anchors.topMargin: 31
    }

    Text {
        text: "请使用微信扫描二维码以登录"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: qrcodeImage.bottom
        anchors.topMargin: 38
    }

    Scan {
        id: scanObj
        onError: { console.log("ERROR:", strerror) }
        onScanedButWaitConfirm: {
            console.log("DEBUG: scanned but waiting for confirm...")
            loginView.tip = "0"
            statReportObj.firstRequestSuccess(loginView.uuid)
            statReportObj.secondRequestStart(loginView.uuid)
        }
        onScanedAndConfirmed: {
            console.log("DEBUG: confirmed!")
            scanTimer.stop()
            if (loginView.v2) {
                cookieObj.getV2(redirect_uri)
            } else {
                cookieObj.get(redirect_uri)
            }
        }
    }

    function scanQRcode() { scanObj.get(loginView.uuid, loginView.tip) }

    Timer {
        id: scanTimer
        interval: 3000; running: true; repeat: true; triggeredOnStart: true
        onTriggered: { scanQRcode() }
    }

    Cookie {
        id: cookieObj
        onInfoChanged: {
            loginView.uin = uin
            loginView.sid = sid
            loginView.ticket = ticket
            if (loginView.v2) {
                statReportObj.postV2(loginView.uuid)
                initObj.postV2(loginView.uin, loginView.sid, loginView.ticket)
            } else {
                statReportObj.post(loginView.uuid)
                initObj.post(loginView.uin, loginView.sid, loginView.ticket)
            }
        }
        onSwitchToV2: {
            rootWindowStackView.clear()
            rootWindowStackView.push({
                item: Qt.resolvedUrl("SplashView.qml"),
                properties: {v2: true}})
        }
    }

    StatReport {
        id: statReportObj
    }

    Init {
        id: initObj
        onSkeyChanged: {
            if (skey != "") { loginView.skey = skey }
            rootWindowStackView.clear()
            rootWindowStackView.push({
                item: Qt.resolvedUrl("NavigatorView.qml"),  
                properties: {v2: loginView.v2,
                             uin: loginView.uin,
                             sid: loginView.sid, 
                             skey: loginView.skey, 
                             deviceId: initObj.deviceId,
                             ticket: loginView.ticket, 
                             loginUserName: initObj.loginUserName, 
                             syncKey: syncKey, 
                             initObj: initObj}})
        }
    }
}
