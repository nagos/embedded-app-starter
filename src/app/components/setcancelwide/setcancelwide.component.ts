import { Component, Input, Output, EventEmitter } from '@angular/core';

@Component({
    selector: 'app-setcancelwide',
    templateUrl: './setcancelwide.component.html',
    styleUrls: ['./setcancelwide.component.less']
})

export class SetCancelWideComponent {
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
