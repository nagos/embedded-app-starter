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

    public dataApply(): void {
        this.apply.emit();
    }

    public dataCancel(): void {
        this.cancel.emit();
    }
}
