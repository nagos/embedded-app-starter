import { Component, Input, HostBinding } from '@angular/core';

@Component({
    selector: 'app-panel',
    templateUrl: './panel.component.html',
    styleUrls: ['./panel.component.less']
})
export class PanelComponent {

    @Input() title = '';
    // назначить классы родительскому компоненту
    @HostBinding('class') classList = 'col-xl-6 col-lg-12 mb-2';
    @Input() set nocase(value: boolean) {
        // защита от пустой строки
        this.isNocase = typeof value === 'boolean' ? value : true;
    }
    // количество панелей в ряд
    @Input() set stack(value: number) {
        if (value == 1) {
            this.classList = 'col-xl-12 col-lg-12 mb-2';
        } else if (value == 2) {
            this.classList = 'col-xl-6 col-lg-12 mb-2';
        } else if (value == 3) {
            this.classList = 'col-xl-4 col-lg-12 mb-2';
        }
    }
    public isNocase = false;

    constructor() {
    }
}
