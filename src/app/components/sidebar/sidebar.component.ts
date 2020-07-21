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

    private routeToIndex(route): number {
        for (const [i, v] of this.data.entries()) {
            if (v.link === route) {
                return i;
            }
            for (const q in v.alias) {
                if (v.alias[q] === route) {
                    return i;
                }
            }
        }
        return 0;
    }

    public getIndex(): number {
        return this.routeToIndex(this.route.snapshot.pathFromRoot.map(o => o.url[0]).join('/'));
    }

    constructor(private route: ActivatedRoute) {
    }
}
