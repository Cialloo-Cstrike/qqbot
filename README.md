## 支持的功能
- 远程给起源引擎服务器发送指令
- 远程查询起源引擎服务器状态
- OpenAI

---
## 使用方式
需要在电脑上安装nodejs运行, 下载地址 https://nodejs.org/  
下载解压代码后先在代码路径下执行`npm install`指令  
使用前先修改config.json, 这里已经有一个写好了的模板
```json
{
    "account" : 123,
    "1234" : {
        "surf" : {
            "host" : "127.0.0.1",
            "port" : 27015,
            "rcon" : "password",
            "admin" : [123, 456, 789]
        },
        "msr" : {
            "host" : "127.0.0.1",
            "port" : 27017,
            "rcon" : "password",
            "admin" : [123, 456, 789]
        }
    },
    "chatgpt" : {
        "apikey" : "apikey",
        "permit" : [123, 456, 789]
    }
}
```
- 第一项```account```就是填你的qq号
- 第二项```1234```改成自己的群号
- ```chatgpt```项里的```apikey```换上你自己注册openai时候拿到的apikey
- ```permit```里就填可以用openai的群的群号, 用逗号隔开
- 群号下可以写很多个关键字, 比如```surf```和`msr`都是触发qq机器人回复的关键词
- `host`填服务器ip
- `port`填服务器端口
- `rcon`填服务器rcon密码
- `admin`填可以执行远程控制的qq号, 用逗号隔开
- 按照json格式可以多设置关键词和群号.

修改完`config.json`以后就可以通过在代码路径下执行```node qq.js```命令来启动机器人, 第一次启动要扫码登陆, 确认登陆后记得按一下回车键.

发送指令格式(以config.json为例):
- `# surf`仅回复127.0.0.1:27015服务器的地图和人数
- `! surf`回复127.0.0.1:27015服务器的大部分可读信息和玩家
- `> surf echo hello world!`像127.0.0.1:27015服务器发送`echo hello world!`指令
- `/ 你知道2+5等于几？`向openai对话, 对话内容最前面要有`/`和**一个空格**