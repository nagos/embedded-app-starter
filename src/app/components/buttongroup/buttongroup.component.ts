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

    constructor() {
    }

    get value() {
        return +this.val;
    }

    set value(val) {
        this.val = val;
    }

    writeValue(value) {
        this.val = +value;
    }

    changeValue(value) {
        this.value = value;
        this.onChange(+value);
    }

    registerOnChange(fn) {
        this.onChange = fn;
    }

    registerOnTouched(fn) {
        this.onTouched = fn;
    }

    setDisabledState(isDisabled: boolean) {
        this.isDisabled = isDisabled;
    }

}
