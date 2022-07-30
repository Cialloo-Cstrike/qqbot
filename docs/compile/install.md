---
sidebar_position: 1
---

# 安装依赖

> 此次更新的2.0版本依然是只支持Linux系统, 此教程也是在Linux系统下的编译教程, 我的系统是```wsl ubuntu20.04```.
如果不想编译直接使用请看配置教程.

## 1. 装编译环境
输入以下指令安装好```g++```和```gcc```编译器还有一些工具
```
sudo apt-get install build-essential
sudo apt-get install git
sudo apt-get install zip
```
## 2. 下载并导入一些C++库
编译这个机器人还要装一些开源库
- [httplib](https://github.com/yhirose/cpp-httplib)
- [boost](https://www.boost.org/)
- [json](https://github.com/nlohmann/json)

除了以上三个比较大的库, 这个仓库还装了```SourceRCON```和```libssq```, 比较轻量, 所以我直接放进来了, 不需要再手动安装