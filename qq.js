const { createClient } = require('oicq')
const Gamedig = require('gamedig');
const { exec } = require('node:child_process')
const fs = require('fs');

let config_file = fs.readFileSync('config.json');
let config = JSON.parse(config_file);
const client = createClient(config.account)

client.on("system.login.qrcode", function (e) {
    //扫码后按回车登录
    process.stdin.once("data", () => {
      this.login()
    })
}).login()
client.on("system.online", () => console.log("Logged in!"))

client.on("message.group", message => {
    if(message.group_id in config == false)
        return;

    let message_array = message.toString().split(" ")
    if(message_array[0] != ">" 
    && message_array[0] != "#"
    && message_array[0] != "!")
        return;

    if(message_array[0] == "#" 
    && message_array[1] in config[message.group_id]) { // 简易输出
        console.log("npx gamedig --type css " 
        + config[message.group_id][message_array[1]].host 
        + ":" + config[message.group_id][message_array[1]].port)
        exec("npx gamedig --type css " 
        + config[message.group_id][message_array[1]].host 
        + ":" + config[message.group_id][message_array[1]].port, 
        (err, result) => {
            if (err) {
                console.error("could not execute command: ", err)
                message.reply("Error.", true)
                return
            }

            let a2s_result = JSON.parse(result);
            if("error" in a2s_result) {
                message.reply("Error in a2s query.", true)
                return
            }
            else {
                message.reply("地图: " + a2s_result.map + "\n" + "人数: " + a2s_result.raw.numplayers, true)
            }
        })
    }
    else if(message_array[0] == "!" 
    && message_array[1] in config[message.group_id]) { // 简易输出
        console.log("npx gamedig --type css " 
        + config[message.group_id][message_array[1]].host 
        + ":" + config[message.group_id][message_array[1]].port)
        exec("npx gamedig --type css " 
        + config[message.group_id][message_array[1]].host 
        + ":" + config[message.group_id][message_array[1]].port, 
        (err, result) => {
            if (err) {
                console.error("could not execute command: ", err)
                message.reply("Error.", true)
                return
            }

            let a2s_result = JSON.parse(result);
            if("error" in a2s_result) {
                message.reply("Error in a2s query.", true)
                return
            }
            else {
                let members = ""
                for(i in a2s_result.players) {
                    members += a2s_result.players[i].name+ "\n"
                }
                message.reply("服务器: " + a2s_result.name + "\n" 
                + "地图: " + a2s_result.map + "\n" 
                + "IP: " + a2s_result.connect + "\n" 
                + "人数: " + a2s_result.raw.numplayers + "\n" 
                + "==========\n" 
                + members 
                + "==========", true)
            }
        })
    }
})