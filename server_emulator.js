// Node.js WebSocket server script
const rand_value = Math.floor(Math.random()*1000);
const http = require('http');
const WebSocketServer = require('websocket').server;
const server = http.createServer();
server.listen(9898);
const wsServer = new WebSocketServer({
    httpServer: server
});
wsServer.on('request', function (request) {
    const connection = request.accept(null, request.origin);
    connection.on('message', function (message) {
        const msg = JSON.parse(message.utf8Data);
        console.log('Received Message:', msg.type);
        if(msg.type=='keepalive') {
            connection.send(JSON.stringify({
                type: "keepalive", data: {}
            }));
        } else {
            console.log(msg);
        }
    });
    connection.on('close', function (reasonCode, description) {
        console.log('Client has disconnected.');
    });
    connection.send(JSON.stringify({
        type: "settings", data: {
            value: 'New Value',
            valueint: 1,
            valueselect: 1,
            valuebutton: 0,
            timeZone: 'Europe/Moscow',
            rand_value: rand_value,
        }
    }));
});
