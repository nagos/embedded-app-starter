import { Component, Input, forwardRef, Output, EventEmitter } from '@angular/core';
import { ControlValueAccessor} from '@angular/forms';
import { NG_VALUE_ACCESSOR } from '@angular/forms';

@Component({
    selector: 'app-checkbox',
    templateUrl: './checkbox.component.html',
    providers: [
        {
          provide: NG_VALUE_ACCESSOR,
          useExisting: forwardRef(() => CheckboxComponent),
          multi: true
        }
    ],
    styleUrls: ['./checkbox.component.less']
})
export class CheckboxComponent implements ControlValueAccessor {
    public val: number;
    public isDisabled: boolean;

    @Input() title = '';
    @Input() name = '';

    onChange: any = () => {};
    onTouched: any = () => {};

    constructor() {
    }

    get value(): any {
        return this.val;
    }

    set value(val) {
        this.val = val;
    }

    writeValue(value): void {
        this.val = value;
    }

    // за изменением значения компонента следим через ngModelChange
    // (при возникновении ngModelChanged вызываем функцию changeValue, которая сделает значение числовым, если тип компонента number)
    changeValue(value): void {
        if (value) {
            this.val = 0;
        } else {
            this.val = 1;
        }
        this.onChange(this.val);
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
