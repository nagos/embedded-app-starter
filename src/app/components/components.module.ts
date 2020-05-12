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
import { FieldBodyComponent } from './fieldbody/fieldbody.component';

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
        FieldBodyComponent,
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
        FieldBodyComponent,
        AppRoutingModule,
    ]
  })
export class MyAddonModule {}
