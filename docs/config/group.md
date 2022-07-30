---
sidebar_position: 3
---

# 自定义q群

进入config文件夹可以看到一个名为```group_settings.json```的配置文件, 模板如下
```json
{
    "0721" : {
        "keyword1" : {
            "ip" : "127.0.0.1",
            "port" : 27015,
            "rcon" : "password"
        },
        "keyword2" : {
            "ip" : "192.168.0.1",
            "port" : 27016
        },
        "admin" : [123456, 456789, 156]
    }
}
```

## 参数说明
- "0721" : 这是qq群号
- "keyword1" : 这是一个服务器的关键词, 别名
- "ip" : 关键词服务器的ip地址
- "port" : 关键词服务器的端口
- "rcon" : 关键词服务器的rcon密码, 可以不填
- "admin" : 有权在这个群进行远程操控的qq号数组, 用逗号分隔每一个qq号

你还可以设置多个qq群, 只要多写几个json对象就行了, 顶层key是qq号, 对象内部就是服务器关键词和admin对象.