import { Component, Input, forwardRef, Output, EventEmitter } from '@angular/core';
import { ControlValueAccessor} from '@angular/forms';
import { NG_VALUE_ACCESSOR } from '@angular/forms';

@Component({
    selector: 'app-inputfield',
    templateUrl: './inputfield.component.html',
    providers: [
        {
          provide: NG_VALUE_ACCESSOR,
          useExisting: forwardRef(() => InputfieldComponent),
          multi: true
        }
    ],
    styleUrls: ['./inputfield.component.less']
})
export class InputfieldComponent implements ControlValueAccessor {
    public val: any;
    public isDisabled: boolean;

    @Input() title = '';
    @Input() type = 'text';
    @Input() min = '';
    @Input() max = '';

    onChange: any = () => {};
    onTouched: any = () => {};

    constructor() {
    }

    get value() {
        if (this.type === 'number') {
            return +this.val;
        } else {
            return this.val;
        }
    }

    set value(val) {
        this.val = val;
    }

    writeValue(value) {
        this.val = value;
    }

    // за изменением значения компонента следим через ngModelChange
    // (при возникновении ngModelChanged вызываем функцию changeValue, которая сделает значение числовым, если тип компонента number)
    changeValue(value) {
        if (this.type === 'number') {
            this.onChange(+value);
        } else {
            this.onChange(value);
        }
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
