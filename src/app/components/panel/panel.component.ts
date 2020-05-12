import { Component, OnInit, Input, HostBinding } from '@angular/core';

@Component({
    selector: 'app-panel',
    templateUrl: './panel.component.html',
    styleUrls: ['./panel.component.less']
})
export class PanelComponent implements OnInit {

    @Input() title = '';
    @HostBinding('class') classList = 'col-xl-5 col-lg-8 col-md-10 col-sm-12 col-xs-12 mb-2';

    constructor() {
    }

    ngOnInit() {
    }

}
