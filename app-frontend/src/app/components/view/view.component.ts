import { Component, OnInit, Input } from '@angular/core';

@Component({
    selector: 'app-view',
    templateUrl: './view.component.html',
    styleUrls: ['./view.component.less']
})
export class ViewComponent {
    // Настройки sidebar
    @Input() data = [];
    @Input() modelStr = 'No Model';
}
