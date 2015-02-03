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

网页版本的微信只能聊天，官方虽然没有提供协议，[狼夜] (http://www.langyeweb.com/Program/70.html) 分析了早期的（V1版本）协议，基于此就可以开动了 ;)

