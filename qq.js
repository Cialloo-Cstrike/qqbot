const { createClient } = require('oicq')
const Gamedig = require('gamedig');
const { exec } = require('node:child_process')
const fs = require('fs');
const Rcon = require('rcon');
const request = require('request');

const config_file = fs.readFileSync('config.json');
const config = JSON.parse(config_file);
const client = createClient(config.account)
const api_key = config.chatgpt.apikey;
const endpoint = 'https://api.openai.com/v1/engines/text-davinci-003/completions';

client.on("system.login.qrcode", function (e) {
    //扫码后按回车登录
    process.stdin.once("data", () => {
      this.login()
    })
}).login()
client.on("system.online", () => console.log("Logged in!"))

client.on("message.group", message => {
    if(message.group_id in config == false 
    && config.chatgpt.permit.includes(message.group_id) == false)
        return;

    let message_array = message.toString().split(" ")
    if(message_array[0] != ">" 
    && message_array[0] != "#"
    && message_array[0] != "!"
    && message_array[0] != "/")
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
    && message_array[1] in config[message.group_id]) { // 成员输出
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
    else if(message_array[0] == ">" 
    && message_array[1] in config[message.group_id]) { // 远程控制
        if(!config[message.group_id][message_array[1]].admin.includes(message.sender.user_id)) {
            message.reply("You are not admin.", true)
            return
        }
        let rcon_client = Rcon(config[message.group_id][message_array[1]].host,
            config[message.group_id][message_array[1]].port,
            config[message.group_id][message_array[1]].rcon)
        rcon_client.connect()
        rcon_client.on('auth', function() {
            let cmd = " "
            for(let i = 0; i < message_array.length; i++) {
                if(i + 3 > message_array.length) break
                else cmd += (message_array[i + 2] + " ")
            }
            console.log(cmd)
            rcon_client.send(cmd);
        }).on('response', function(str) {
            str += " "
            if(str.length < 5) return
            console.log("Response: " + str);
            message.reply(str, true)
        }).on('error', function(err) {
            err += " "
            console.log("Error: " + err);
            message.reply(err, true)
        }).on('end', function() {
            console.log("rcon connetction closed.");
            process.exit();
        });
    }
    else if(message_array[0] == "/") {
        let temp = message.toString()
        let prompt = ""
        for(let i = 2; i < temp.length; i++)
            prompt += temp[i]
        let payload = {
            'prompt': prompt,
            'max_tokens': 1024,
            'temperature': 0.9,
            'top_p': 0.9,
        };
        console.log(payload)
        request.post({url: endpoint, body: payload, json: true, headers: {Authorization: `Bearer ${api_key}`}}, (err, res, body) => {
            let temp = ""
            for(let i = 2; i < body.choices[0].text.length; i++)
                temp += body.choices[0].text[i]
            message.reply(temp, true)
        });
    }
})