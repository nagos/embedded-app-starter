import { NgModule } from '@angular/core';
import { RouterModule, Routes } from '@angular/router';
import { MainComponent } from './views/main.component';
import { SettingsComponent } from './views/settings.component';

const routes: Routes = [
    { path: '', component: MainComponent },
    { path: 'settings', component: SettingsComponent },
    { path: '**', component: MainComponent },
];

@NgModule({
    imports: [ RouterModule.forRoot(routes, { useHash: true }) ],
    exports: [ RouterModule ]
})
export class AppRoutingModule {}
