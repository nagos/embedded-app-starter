import { Component, ViewChild } from '@angular/core';
import { WsdataService } from '../wsdata.service';

@Component({
    selector: 'app-settings',
    templateUrl: './settings.component.html',
})
export class SettingsComponent {

    public settingsData = this.wsData.copySettings();

    newdata(): void {
        this.settingsData = this.wsData.copySettings();
    }

    constructor(public wsData: WsdataService) {
        this.wsData.subscribeNewData(() => this.newdata());
    }
}
