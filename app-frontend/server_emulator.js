const WebSocket = require('ws')
const fs = require('fs');
const path = require('path');
let watchFiles = [];

function send_file(fname) {
    fs.readFile(fname, 'utf8' , (err, data) => {
        const msgType = path.basename(fname, ".json");
        const msgData = JSON.parse(data);
        wsServer.clients.forEach(function(client) {
            client.send(JSON.stringify({
                type: msgType,
                data: msgData,
            }));
         });
    });
}

function watchFile(fname) {
    fs.watchFile(fname, {interval: 1000}, () => {
        send_file(fname);
    });
}

fs.readdirSync('./server_emulator/').forEach(file => {
    watchFiles.push('./server_emulator/' + file);
});

const wsServer = new WebSocket.Server({ port: 9898 },()=>{
    console.log('server started')
});

wsServer.on('connection', (ws) => {
    ws.on('message', function (message) {
        const msg = JSON.parse(message);
        if(msg.type=='keepalive') {
            ws.send(JSON.stringify({
                type: "keepalive", data: {}
            }));
        } else {
            console.log(msg);
        }
    });
    watchFiles.forEach((fname) => {
        send_file(fname);
    })

});

watchFiles.forEach((fname) => {
    watchFile(fname);
});
