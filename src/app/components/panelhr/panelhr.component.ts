import { Component, OnInit, Input } from '@angular/core';

@Component({
    selector: 'app-panelhr',
    templateUrl: './panelhr.component.html',
    styleUrls: ['./panelhr.component.less']
})
export class PanelHrComponent implements OnInit {

    @Input() title = '';

    constructor() {
    }

    ngOnInit() {
    }

}
