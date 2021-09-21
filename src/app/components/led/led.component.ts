import { Component, Input, forwardRef, Output, EventEmitter } from '@angular/core';
import { ControlValueAccessor} from '@angular/forms';
import { NG_VALUE_ACCESSOR } from '@angular/forms';

@Component({
    selector: 'app-led',
    templateUrl: './led.component.html',
    providers: [
        {
          provide: NG_VALUE_ACCESSOR,
          useExisting: forwardRef(() => LedComponent),
          multi: true
        }
    ],
    styleUrls: ['./led.component.less']
})
export class LedComponent implements ControlValueAccessor {
    public val: number;
    public isDisabled: boolean;

    @Input() title = '';

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

    changeValue(value): void {
        this.onChange(value);
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
