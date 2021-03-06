import { NgModule } from '@angular/core';
import { FormsModule } from '@angular/forms';
import { InputfieldComponent } from './inputfield/inputfield.component';
import { SelectfieldComponent } from './selectfield/selectfield.component';
import { PanelComponent } from './panel/panel.component';
import { CommonModule } from '@angular/common';
import { SidebarComponent } from './sidebar/sidebar.component';
import { AppRoutingModule } from '../app-routing.module';
import { ViewComponent } from './view/view.component';
import { ConnectionComponent } from './connection/connection.component';
import { ButtonGroupComponent } from './buttongroup/buttongroup.component';
import { TimezoneComponent } from './timezone/timezone.component';
import { PanelHrComponent } from './panelhr/panelhr.component';
import { SetCancelButtonComponent } from './setcancelbutton/setcancelbutton.component';
import { SetCancelWideComponent } from './setcancelwide/setcancelwide.component';
import { FieldBodyComponent } from './fieldbody/fieldbody.component';
import { CheckboxComponent } from './checkbox/checkbox.component';
import { ModalComponent } from './modal/modal.component';
import { LedComponent } from './led/led.component';

@NgModule({
    declarations: [
        InputfieldComponent,
        SelectfieldComponent,
        PanelComponent,
        SidebarComponent,
        ViewComponent,
        ConnectionComponent,
        ButtonGroupComponent,
        TimezoneComponent,
        PanelHrComponent,
        SetCancelButtonComponent,
        SetCancelWideComponent,
        FieldBodyComponent,
        CheckboxComponent,
        ModalComponent,
        LedComponent,
    ],
    imports: [
        FormsModule,
        CommonModule,
        AppRoutingModule,
    ],
    exports: [
        InputfieldComponent,
        SelectfieldComponent,
        PanelComponent,
        SidebarComponent,
        ViewComponent,
        ConnectionComponent,
        ButtonGroupComponent,
        TimezoneComponent,
        PanelHrComponent,
        SetCancelButtonComponent,
        SetCancelWideComponent,
        FieldBodyComponent,
        CheckboxComponent,
        ModalComponent,
        LedComponent,
        AppRoutingModule,
    ]
  })
export class MyAddonModule {}
