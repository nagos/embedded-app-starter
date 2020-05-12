import { Component, Input, forwardRef, Output, EventEmitter } from '@angular/core';
import { ControlValueAccessor} from '@angular/forms';
import { NG_VALUE_ACCESSOR } from '@angular/forms';

@Component({
    selector: 'app-selectfield',
    templateUrl: './selectfield.component.html',
    providers: [
        {
          provide: NG_VALUE_ACCESSOR,
          useExisting: forwardRef(() => SelectfieldComponent),
          multi: true
        }
    ],
    styleUrls: ['./selectfield.component.less']
})
export class SelectfieldComponent implements ControlValueAccessor {
    public val: any;
    public isDisabled: boolean;

    @Input() title = '';

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
