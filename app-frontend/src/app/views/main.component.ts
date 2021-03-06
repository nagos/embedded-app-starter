import { Component, ViewChild } from '@angular/core';
import { NgForm } from '@angular/forms';
import { WsdataService } from '../wsdata.service';

@Component({
    selector: 'app-main',
    templateUrl: './main.component.html',
})
export class MainComponent {

    @ViewChild('settingsForm', {static: false}) settingsForm: NgForm;

    public settingsData = this.wsData.copySettings();
    public disabled = 0;
    public hidden = 0;

    newdata(): void {
        this.settingsData = this.wsData.copySettings();
    }

    constructor(public wsData: WsdataService) {
        this.wsData.subscribeNewData(() => this.newdata());
    }

    public sendForm(): void {
        this.wsData.readSettings(this.settingsData);
        this.wsData.sendSettings();
        this.settingsForm.form.markAsPristine();
    }

    public resetForm(): void {
        this.settingsForm.form.markAsPristine();
        this.newdata();
    }

    public modalOk(): void {
        console.log('Modal OK');
    }

    public modalCancel(): void {
        console.log('Modal Cancel');
    }

    public setButton(): void {
        console.log("Button");
    }

}
