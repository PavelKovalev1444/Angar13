import { NgModule } from '@angular/core';
import { RouterModule, Routes } from '@angular/router';
import { StartPageComponent } from "./ts_components/startPage.component";
import { BrokerListComponent } from "./ts_components/brokerList.component";
import {SharesListComponent} from "./ts_components/sharesList.component";
import {SettingsComponent} from "./ts_components/settings.component";

const routes: Routes = [
  {path:'',component: StartPageComponent},
  {path:'brokerList', component: BrokerListComponent},
  {path:'sharesList', component: SharesListComponent},
  {path:'settings', component: SettingsComponent}
];

@NgModule({
  imports: [RouterModule.forRoot(routes)],
  exports: [RouterModule]
})
export class AppRoutingModule { }
