qwx
----

WeChat Qt frontend based on [webwx protocol] (https://github.com/xiangzhai/qwx/blob/master/doc/protocol.md) 
微信Qt前端，使用[网页微信协议] (https://github.com/xiangzhai/qwx/blob/master/doc/protocol.md)

***images and protocol Copyright (C) by [Tencent] (http://weixin.qq.com/)*** 
***图片、协议版权归[腾讯] (http://weixin.qq.com/) 所有！***


## Dependences 依赖

Qt5(>=5.2) qml, quick, network and xml 

## Rock for wayland 

[QtWayland 5.4 with QtCompositor] (https://github.com/papyros/papyros-shell#dependencies)


## Build && Install 编译、运行

```
qmake QWX_DEBUG=ON
make
./qwx
```


## i18n

```
lupdate qml/*.qml -ts translations/qwx_zh_CN.ts
lrelease translations/qwx_zh_CN.ts
```


## Skeleton 重度开发状态下的原型骨架截图

![ScreenShot](https://raw.github.com/xiangzhai/qwx/master/doc/splash.png)

![ScreenShot](https://raw.github.com/xiangzhai/qwx/master/doc/login.png)

![ScreenShot](https://raw.github.com/xiangzhai/qwx/master/doc/qwx-snapshot1.png)

![ScreenShot](https://raw.github.com/xiangzhai/qwx/master/doc/qwx-snapshot2.png)

![ScreenShot](https://raw.github.com/xiangzhai/qwx/master/doc/qwx-snapshot3.png)

![ScreenShot](https://raw.github.com/xiangzhai/qwx/master/doc/wayland-screenshot.png)

![ScreenShot](https://raw.github.com/xiangzhai/qwx/master/doc/chat.png)

![ScreenShot](https://raw.github.com/xiangzhai/qwx/master/doc/init-contact.png)

![ScreenShot](https://raw.github.com/xiangzhai/qwx/master/doc/modcontact.png)

![ScreenShot](https://raw.github.com/xiangzhai/qwx/master/doc/qrcode-card.png)

![ScreenShot](https://raw.github.com/xiangzhai/qwx/master/doc/notify-send.png)


## 聊天机器人

在聊天时，输入“小逗比出来”即可唤出聊天机器人，若实在受不了小逗比，输入“小逗比退下”
即可退出聊天机器人。


## 自动回复

在聊天时，输入“away”即可进入自动回复状态，输入“back”即可退出自动回复状态。
