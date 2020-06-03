import { Injectable } from '@angular/core';
import { Subject } from 'rxjs';
import { timer } from 'rxjs';
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
    private newConnectionSubject = new Subject();
    private dataIn = new Subject<Message>();
    public dataOut = new Subject<Message>();

    constructor() {
        this.url = environment.dev_ip;
        // таймер повторного подключения
        this.connect();
        timer(1000, 1000)
            .subscribe(() => {
                switch (this.ws.readyState) {
                    case WebSocket.CLOSED:
                        this.connectionStatus.value = false;
                        if (this.lastConnectAttempt + this.reconnectTimeout < this.get_time()) {
                            this.connect();
                        }
                        break;
                    case WebSocket.OPEN:
                        if (this.lastDataTime + this.dataTimeout < this.get_time()) {
                            this.ws.close();
                            this.connect();
                            this.connectionStatus.value = false;
                        } else {
                            this.connectionStatus.value = true;
                        }
                        this.connectionStatus.first = true;
                        break;
                    default:
                        break;
                }
            });
        // таймер keepalive
        timer(10000, 10000)
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

    public connect() {
        this.ws = new WebSocket(this.url);
        this.ws.onmessage = (ev) => {
            this.dataIn.next(JSON.parse(ev.data));
            this.lastDataTime = this.get_time();
        };
        this.ws.onopen = () => this.new_connection();
        this.lastConnectAttempt = this.get_time();
        this.lastDataTime = this.get_time();
    }

    private new_connection() {
        this.newConnectionSubject.next();
        console.log('Successfully connected: ' + this.url);
    }

    /**
     * Подписаться на получение сообщений
     * @param f callback
     * @param t this
     */
    public subscribe(f: (object) => void): void {
        this.dataIn.subscribe(f);
    }

    public subscribe_new_connection(f: () => void): void {
        this.newConnectionSubject.subscribe(value => f());
    }
}
