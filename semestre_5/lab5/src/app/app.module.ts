import { NgModule } from '@angular/core';
import { BrowserModule } from '@angular/platform-browser';
import { AppRoutingModule } from "./approut.module";
import { AppComponent } from './ts_components/app.component';
import { StartPageComponent } from "./ts_components/startPage.component";
import { BrokerListComponent } from "./ts_components/brokerList.component";
import { SharesListComponent } from "./ts_components/sharesList.component";
import { SettingsComponent } from "./ts_components/settings.component";
import { FormsModule } from "@angular/forms";
import {HttpClientModule} from "@angular/common/http";

@NgModule({
  declarations: [
    AppComponent,
    StartPageComponent,
    BrokerListComponent,
    SharesListComponent,
    SettingsComponent
  ],
  imports: [
    BrowserModule,
    AppRoutingModule,
    FormsModule,
    HttpClientModule
  ],
  providers: [],
  bootstrap: [AppComponent]
})

export class AppModule { }
