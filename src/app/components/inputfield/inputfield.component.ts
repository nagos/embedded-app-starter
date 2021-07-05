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
    @Input() set readonly(value: boolean) {
        this.isReadonly = typeof value === 'boolean' ? value : true;
    }
    get readonly(): boolean {
        return this.isReadonly;
    }

    public isReadonly = false;

    onChange: any = () => {};
    onTouched: any = () => {};

    constructor() {
    }

    get value(): any {
        if (this.type === 'number') {
            return +this.val;
        } else {
            return this.val;
        }
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
        if (this.type === 'number') {
            this.onChange(+value);
        } else {
            this.onChange(value);
        }
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
