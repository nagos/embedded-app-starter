import { NgModule } from '@angular/core';
import { RouterModule, Routes } from '@angular/router';
import { MainComponent } from './views/main.component';
import { SettingsComponent } from './views/settings.component';

const routes: Routes = [
    { path: 'status', component: MainComponent },
    { path: 'settings', component: SettingsComponent },
    { path: '**', redirectTo: 'status', pathMatch: 'full'},
];

@NgModule({
    imports: [ RouterModule.forRoot(routes, { useHash: true }) ],
    exports: [ RouterModule ]
})
export class AppRoutingModule {}
