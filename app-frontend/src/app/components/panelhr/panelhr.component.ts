import { Component, Input } from '@angular/core';

@Component({
    selector: 'app-panelhr',
    templateUrl: './panelhr.component.html',
    styleUrls: ['./panelhr.component.less']
})
export class PanelHrComponent {

    @Input() title = '';
    @Input() set nocase(value: boolean) {
        // защита от пустой строки
        this.isNocase = typeof value === 'boolean' ? value : true;
    }
    public isNocase = false;

    constructor() {
    }

}
