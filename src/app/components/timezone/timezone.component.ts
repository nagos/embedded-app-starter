import { Component, Input, forwardRef, Output, EventEmitter } from '@angular/core';
import { ControlValueAccessor} from '@angular/forms';
import { NG_VALUE_ACCESSOR } from '@angular/forms';
import {tzlist} from './tzlist';

@Component({
    selector: 'app-timezone',
    templateUrl: './timezone.component.html',
    styleUrls: ['./timezone.component.less'],
    providers: [
        {
          provide: NG_VALUE_ACCESSOR,
          useExisting: forwardRef(() => TimezoneComponent),
          multi: true
        }
    ],
})
export class TimezoneComponent implements ControlValueAccessor {
    public val: string;
    public val2: string;
    public isDisabled: boolean;
    public tzlist = tzlist;

    @Input() title = '';

    onChange: any = () => {};
    onTouched: any = () => {};

    constructor() {
        this.val = Object.keys(tzlist)[0];
        this.val2 = tzlist[this.val][0];
    }

    get value(): string {
        return this.val + '/' + this.val2;
    }

    set value(val: string) {
        this.val = val;
    }

    writeValue(value: string) {
        if (typeof(value) !== 'string') {
            return;
        }
        const valueSplit = value.split('/');
        this.val = valueSplit[0];
        if (valueSplit.length === 2) {
            this.val2 = valueSplit[1];
        } else {
            this.val2 = valueSplit[1] + '/' + valueSplit[2];
        }
    }

    changeValue() {
        this.onChange(this.val + '/' + this.val2);
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

    chaneRegion() {
        this.val2 = tzlist[this.val][0];
        this.changeValue();
    }
}
