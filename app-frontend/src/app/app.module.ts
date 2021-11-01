import { BrowserModule } from '@angular/platform-browser';
import { NgModule } from '@angular/core';
import { FormsModule } from '@angular/forms';

import { AppComponent } from './app.component';
import { WsdataService } from './wsdata.service';
import { MainComponent } from './views/main.component';
import { SettingsComponent } from './views/settings.component';

import { HttpClientModule } from '@angular/common/http';
import { MyAddonModule } from './components/components.module';

import { library, dom } from '@fortawesome/fontawesome-svg-core';
import { faTimesCircle, faCogs, faAngleDoubleDown} from '@fortawesome/free-solid-svg-icons';
import { faBars } from '@fortawesome/free-solid-svg-icons';

@NgModule({
    declarations: [
        AppComponent,
        MainComponent,
        SettingsComponent,
    ],
    imports: [
        BrowserModule,
        FormsModule,
        HttpClientModule,
        MyAddonModule,
    ],
    providers: [
        WsdataService
    ],
    bootstrap: [AppComponent]
})
export class AppModule { }

library.add(faTimesCircle, faCogs, faAngleDoubleDown);
library.add(faBars);
dom.watch();
