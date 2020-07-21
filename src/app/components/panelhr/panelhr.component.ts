import { Component, Input } from '@angular/core';

@Component({
    selector: 'app-panelhr',
    templateUrl: './panelhr.component.html',
    styleUrls: ['./panelhr.component.less']
})
export class PanelHrComponent {

    @Input() title = '';

    constructor() {
    }

}
