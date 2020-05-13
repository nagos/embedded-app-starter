import { Component, AfterViewInit, ViewChild } from '@angular/core';
import { NgForm } from '@angular/forms';
import { WsdataService } from '../wsdata.service';

@Component({
    selector: 'app-settings',
    templateUrl: './settings.component.html',
})
export class SettingsComponent implements AfterViewInit {

    public settingsData = this.wsData.settingsData;

    newdata(): void {
        this.settingsData = this.wsData.copySettings();
    }

    constructor(public wsData: WsdataService) {
        this.wsData.subscribeNewData(() => this.newdata());
    }

    ngAfterViewInit() {
        this.newdata();
    }

    soloOnChange(value: {enable: number, input: number}) {
        this.wsData.sendSettings();
    }

    public presetChanged(preset: number) {
    }

}
