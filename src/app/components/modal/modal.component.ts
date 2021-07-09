import { Component, Input, Output, EventEmitter } from '@angular/core';

@Component({
    selector: 'app-modal',
    templateUrl: './modal.component.html',
    styleUrls: ['./modal.component.less']
})
export class ModalComponent {

    @Input() title = '';
    @Input() name = '';
    @Input() button = '';
    @Input() hideCancel = false;
    // выход событий из компонента
    @Output() ok = new EventEmitter();
    @Output() cancel = new EventEmitter();
    public labelClass = 'col-xl-5 col-lg-4 col-md-12';
    public inputClass = 'col-xl-7 col-lg-8 col-md-12';

    constructor() {
    }

    public clickOk(): void {
        this.ok.emit();
    }
    public clickCancel(): void {
        this.cancel.emit();
    }
}
