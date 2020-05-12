import { Component, Input, Output, EventEmitter } from '@angular/core';

@Component({
    selector: 'app-setcancelbutton',
    templateUrl: './setcancelbutton.component.html',
    styleUrls: ['./setcancelbutton.component.less']
})

export class SetCancelButtonComponent {
    @Input() disabled = false;
    @Output() apply = new EventEmitter<{}>();
    @Output() cancel = new EventEmitter<{}>();

    public dataApply() {
        this.apply.emit();
    }

    public dataCancel() {
        this.cancel.emit();
    }
}
