import { Component, OnInit } from '@angular/core';
import { WsdataService } from './../../wsdata.service';

@Component({
    selector: 'app-connection',
    templateUrl: './connection.component.html',
    styleUrls: ['./connection.component.less']
})
export class ConnectionComponent implements OnInit {
    connectionStatus: any;
    connectionDialog = false;

    constructor(private wsdataService: WsdataService) {
        this.connectionStatus = wsdataService.connectionStatus;
    }

    ngOnInit() {
    }

}
