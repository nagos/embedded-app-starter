import { Injectable } from '@angular/core';
import { Subject } from 'rxjs';
import { WebsocketService, Message } from './websocket.service';
import { HttpClient } from '@angular/common/http';
import { Version, SettingsData } from './datatypes';
import { copyArray } from './tools';

@Injectable()
export class WsdataService {
    connectionStatus = this.wsService.connectionStatus;
    private newData = new Subject();

    public sidebarRoutes = [
        {label: 'Status', link: '/'},
        {label: 'Settings', link: '/settings'},
    ];
    public modelStr = 'Angular Template';

    private versionUrl = 'assets/version.json';
    public version = {
        frontend_version: ''
    };

    // хранение данных
    public settingsData: SettingsData = {
        value: 'test',
    };

    constructor(public wsService: WebsocketService, private http: HttpClient) {
        wsService.subscribe_new_connection(() => {
            this.show_version();
        });
        wsService.subscribe((msg) => this.message(msg));
    }

    public sendSettings(): void {
        this.send('set_settings', {
        });
    }

    /**
     * Обработка полученых сообщений от websocket
     * @param msg сообщение
     */
    message(msg: Message): void {
        switch (msg.type) {
            case 'settings': {
                this.newData.next();
                break;
            }
            default:
                break;
        }
    }

    private get_version() {
        return this.http.get(this.versionUrl);
    }

    private show_version() {
        this.get_version()
            .subscribe((data: Version) =>
                this.version.frontend_version = data.frontend_version
            );
    }

    public subscribeNewData(f: () => void): void {
        this.newData.subscribe(f);
    }

    /**
     * Отправить сообщение на сервер
     * @param type тип сообщения
     * @param data данные
     */
    private send(type: string, data: any): void {
        this.wsService.send_data(type, data);
    }

    public copySettings(): SettingsData {
        return copyArray(this.settingsData);
    }

    public readSettings(data: SettingsData) {
        this.settingsData = copyArray(data);
    }

}
