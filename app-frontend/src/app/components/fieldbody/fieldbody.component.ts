import { Component, Input } from '@angular/core';

@Component({
    selector: 'app-fieldbody',
    templateUrl: './fieldbody.component.html',
    styleUrls: ['./fieldbody.component.less']
})
export class FieldBodyComponent {

    @Input() title = '';
    public labelClass = 'col-xl-5 col-lg-4 col-md-12';
    public inputClass = 'col-xl-7 col-lg-8 col-md-12';
    public inputClassNoLabel = 'col-xl-12 col-lg-12 col-md-12 text-center';
    @Input() set nocase(value: boolean) {
        // защита от пустой строки
        this.isNocase = typeof value === 'boolean' ? value : true;
    }
    @Input() set nolabel(value: boolean) {
        // защита от пустой строки
        this.isNoLabel = typeof value === 'boolean' ? value : true;
    }
    public isNocase = false;
    public isNoLabel = false;

    constructor() {
    }
}
