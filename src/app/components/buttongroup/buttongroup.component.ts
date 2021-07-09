import { Component, Input, forwardRef, Output, EventEmitter } from '@angular/core';
import { ControlValueAccessor} from '@angular/forms';
import { NG_VALUE_ACCESSOR } from '@angular/forms';

@Component({
    selector: 'app-buttongroup',
    templateUrl: './buttongroup.component.html',
    providers: [
        {
            provide: NG_VALUE_ACCESSOR,
            useExisting: forwardRef(() => ButtonGroupComponent),
            multi: true
        }
    ],
    styleUrls: ['./buttongroup.component.less']
})
export class ButtonGroupComponent implements ControlValueAccessor {
    public val: any;
    public isDisabled: boolean;

    @Input() title = '';
    @Input() buttons = [];

    onChange: any = () => {};
    onTouched: any = () => {};

    @Input() set nocase(value: boolean) {
        // защита от пустой строки
        this.isNocase = typeof value === 'boolean' ? value : true;
    }
    public isNocase = false;

    constructor() {
    }

    get value(): number {
        return +this.val;
    }

    set value(val) {
        this.val = val;
    }

    writeValue(value: number): void {
        this.val = +value;
    }

    changeValue(value): void {
        this.value = value;
        this.onChange(+value);
    }

    registerOnChange(fn): void {
        this.onChange = fn;
    }

    registerOnTouched(fn): void {
        this.onTouched = fn;
    }

    setDisabledState(isDisabled: boolean): void {
        this.isDisabled = isDisabled;
    }
}
