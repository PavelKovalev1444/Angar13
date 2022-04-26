export class SettingsClass{

  time_start: string;
  time_end: string;
  intervalCounter: number;

  constructor(time_start: string, time_end: string, intervalCounter: number) {
    this.time_start = time_start;
    this.time_end = time_end;
    this.intervalCounter = intervalCounter;
  }
}
