---
sidebar_position: 2
---

# 配置config.json

config.json的模板
```json
{
    "hostname": "127.0.0.1",
    "port": 80,
    "qqnumber": 1234,
    "verifykey": "key"
}
```

1. 进入config
```
cd config
```
2. 修改config.json
```
vim config.json
```

参数解释
- hostname: mirai-console的ip地址
- port: mirai机器人的
- qqnumber: 机器人的qq号
- verifykey: 进行验证的key, 要和mirai-console那个配置一样