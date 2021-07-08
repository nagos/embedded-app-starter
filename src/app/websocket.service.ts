import { Injectable } from '@angular/core';
import { Subject } from 'rxjs';
import { interval } from 'rxjs';
import { environment } from '../environments/environment';

export interface Message {
    type: string;
    data: any;
}

@Injectable()
export class WebsocketService {
    // Таймауты
    reconnectTimeout = 10;
    dataTimeout = 20;

    ws: WebSocket;
    url: string;
    lastConnectAttempt: number;
    lastDataTime: number;
    // состояние подключения
    connectionStatus = {
        value: false,
        first: false,
    };
    private dataIn = new Subject<Message>();
    public dataOut = new Subject<Message>();

    constructor() {
        this.url = environment.dev_ip;
        // таймер повторного подключения
        this.connect();
        interval(1000)
            .subscribe(() => {
                switch (this.ws.readyState) {
                    case WebSocket.CLOSED:
                        if (this.lastConnectAttempt + this.reconnectTimeout < this.get_time()) {
                            this.connect();
                        }
                        break;
                    case WebSocket.OPEN:
                        if (this.lastDataTime + this.dataTimeout < this.get_time()) {
                            this.ws.close();
                            this.connect();
                            this.connectionStatus.value = false;
                        }
                        break;
                    default:
                        break;
                }
            });
        // таймер keepalive
        interval(10000)
        .subscribe(() => {
            if (this.ws.readyState === WebSocket.OPEN) {
                this.send_data('keepalive', {});
            }
        });
        this.dataOut.subscribe((msg) => this.ws.send(JSON.stringify(msg)));
    }

    public send_data(type: string, data: any): void {
        this.dataOut.next({type, data});
    }

    /**
     * Получить теущее время в секундах
     */
    private get_time(): number {
        return new Date().getTime() / 1000;
    }

    public connect(): void {
        this.ws = new WebSocket(this.url);
        this.ws.onmessage = (ev) => {
            this.dataIn.next(JSON.parse(ev.data));
            this.lastDataTime = this.get_time();
        };
        this.ws.onopen = () => {
            console.log('Successfully connected: ' + this.url);
            this.connectionStatus.first = true;
            this.connectionStatus.value = true;
        };
        this.ws.onclose = () => {
            console.log('Disconnected');
            this.connectionStatus.value = false;
        };
        this.lastConnectAttempt = this.get_time();
        this.lastDataTime = this.get_time();
    }

    /**
     * Подписаться на получение сообщений
     * @param f callback
     */
    public subscribe(f: (object) => void): void {
        this.dataIn.subscribe(f);
    }
}
