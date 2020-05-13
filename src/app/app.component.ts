import { Component } from '@angular/core';
import { WsdataService } from './wsdata.service';

@Component({
    selector: 'app-root',
    templateUrl: './app.component.html',
})
export class AppComponent {
    constructor(private wsData: WsdataService) {
    }

}
