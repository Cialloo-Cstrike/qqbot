---
sidebar_position: 3
---

# 指令

**这个教程以上一篇的```group_settings.json```为例**

你首先要进入q群号为0721的qq群

1. keyword1  
这个指令可以看起源引擎服务器的127.0.0.1:27015服务器信息, 示例输出如下
```
❀Cialloo❀ | BhopTimer[100tick] Current: *T2*
地图: bhop_psykeeysss
玩家人数: 3
玩家列表
==============
!replay
Main Normal - 1:51.603
GODbose
==============
```
2. \> keyword1 status  
这个指令可以远程发送status指令到服务器127.0.0.1:27015并返回输出信息, 只有在"admin"设置过的qq号才能用这个指令  
指令格式: 第一个字符必须是```>```, 然后一个空格, 然后输入要发送指令的对应服务器的关键词```keyword1```, 再输入一个空格,后面就可以输入你想要输入的服务器指令, 比如```changelevel```, ```sm plugins list```之类的