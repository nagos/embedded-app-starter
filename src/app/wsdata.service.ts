import { Injectable } from '@angular/core';
import { Subject } from 'rxjs';
import { WebsocketService, Message } from './websocket.service';
import { HttpClient } from '@angular/common/http';
import { Title } from '@angular/platform-browser';
import { Version, SettingsData } from './datatypes';
import { copyArray } from './tools';

@Injectable()
export class WsdataService {
    private wsService = new WebsocketService();
    connectionStatus = this.wsService.connectionStatus;
    private newData = new Subject();

    public sidebarRoutes = [
        {label: 'Status', link: '/status'},
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
        valueint: 0,
        valueselect: 0,
        valuebutton: 0,
        valuecheckbox: 0,
        timeZone: 'Europe/Moscow',
    };

    constructor(private http: HttpClient, private titleService: Title) {
        this.show_version();
        this.wsService.subscribe((msg) => this.message(msg));
        this.titleService.setTitle(this.modelStr);
    }

    public sendSettings(): void {
        this.send('set_settings', this.settingsData);
    }

    /**
     * Обработка полученых сообщений от websocket
     * @param msg сообщение
     */
    message(msg: Message): void {
        switch (msg.type) {
            case 'settings': {
                Object.assign(this.settingsData, msg.data);
                this.newData.next();
                break;
            }
            default:
                break;
        }
    }

    private get_version(): any {
        return this.http.get(this.versionUrl);
    }

    private show_version(): void {
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

    public readSettings(data: SettingsData): void {
        this.settingsData = copyArray(data);
    }

}
