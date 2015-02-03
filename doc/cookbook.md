烹饪微信Qt前端
----------------

Copyright (C) 2015 Leslie Zhai <xiang.zhai@i-soft.com.cn>

## 怎么想到要开发微信Qt前端？

这要从2014年CSDN举办的OSTC说起，在大会上遇到了很多Linux粉丝：大爷@sonald、
嘎@aphroiai、右二@towonzhou，我们彼此加了微信，但是Android手机上的默认输入法
不好用，打字速度很着急，明显跟不上聊天进度，就萌发了开发Linux微信Qt前端的想法，
可以在电脑上用键盘输入。

## 可行性分析

Android版本的微信虽然full feature，但是其协议是不开放的，没有完整的文档，也没有
封装好的库，@cjacker 的[apkutil] (https://github.com/xiangzhai/apkutil) 可以
反向微信apk，但是mod后（比如，删除了#朋友圈#）的apk无法登录，或者登录后就被block。

网页版本的微信只能聊天，官方虽然也没有提供协议，[狼夜] (http://www.langyeweb.com/Program/70.html) 却分析了早期的（V1版本）协议，基于此就可以开动了 ;)

## 预研

看[网页版本的微信协议] (https://github.com/xiangzhai/qwx/blob/master/doc/protocol.md)
之前，先要知道HTTP GET和HTTP POST是什么。

### HTTP GET

比如，在Chromium浏览器输入[网址URL] (https://login.weixin.qq.com/jslogin?appid=wx782c26e4c19acffb&redirect_uri=https%3A%2F%2Fwx.qq.com%2Fcgi-bin%2Fmmwebwx-bin%2Fwebwxnewloginpage&fun=new&lang=zh_CN&_=1388994062250) 然后浏览器呈现响应的内容，比如：
```
window.QRLogin.code = 200; window.QRLogin.uuid = "9da5658a689a4f";
```

比如，在终端下用curl做HTTP GET：
```
curl https://login.weixin.qq.com/jslogin?appid=wx782c26e4c19acffb&redirect_uri=https%3A%2F%2Fwx.qq.com%2Fcgi-bin%2Fmmwebwx-bin%2Fwebwxnewloginpage&fun=new&lang=zh_CN&_=1388994062250
```

然后在终端下也会打印类似的响应内容。

### HTTP POST

比如，使用Google搜索qwx就是HTTP POST，不同的是，网页微信的HTTP POST的Header
内容类型是application/json

## 设计

微信Qt前端就是实现HTTP GET/POST，抽象出两个基类[HttpGet] (https://github.com/xiangzhai/qwx/blob/master/src/httpget.h) 
和[HttpPost] (https://github.com/xiangzhai/qwx/blob/master/src/httppost.h)


