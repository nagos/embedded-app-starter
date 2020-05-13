import { Component, AfterViewInit, ViewChild } from '@angular/core';
import { NgForm } from '@angular/forms';
import { WsdataService } from '../wsdata.service';

@Component({
    selector: 'app-main',
    templateUrl: './main.component.html',
})
export class MainComponent implements AfterViewInit {

    @ViewChild('settingsForm', {static: false}) settingsForm: NgForm;

    public settingsData = this.wsData.settingsData;
    public disabled = 0;
    public hidden = 0;

    newdata(): void {
        this.settingsData = this.wsData.copySettings();
    }

    constructor(public wsData: WsdataService) {
        this.wsData.subscribeNewData(() => this.newdata());
    }

    ngAfterViewInit() {
        this.newdata();
    }

    public sendForm() {
        this.wsData.readSettings(this.settingsData);
        this.wsData.sendSettings();
        this.settingsForm.form.markAsPristine();
    }

    public resetForm() {
        this.settingsForm.form.markAsPristine();
        this.newdata();
    }

}
