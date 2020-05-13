import { Component, AfterViewInit, ViewChild } from '@angular/core';
import { NgForm } from '@angular/forms';
import { WsdataService } from '../wsdata.service';

@Component({
    selector: 'app-main',
    templateUrl: './main.component.html',
})
export class MainComponent implements AfterViewInit {

    @ViewChild('statusForm', {static: false}) statusForm: NgForm;

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
