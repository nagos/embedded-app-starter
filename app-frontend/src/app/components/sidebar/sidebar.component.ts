import { Component, Input } from '@angular/core';
import { ActivatedRoute, Router } from '@angular/router';

@Component({
    selector: 'app-sidebar',
    templateUrl: './sidebar.component.html',
    styleUrls: ['./sidebar.component.less']
})
export class SidebarComponent {
    // Настройки sidebar
    @Input() data = [];
    @Input() modelStr = 'No Model';

    public isCollapsed = false;

    constructor(private route: ActivatedRoute) {
    }
}
