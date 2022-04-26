export class BrokerClass{

  broker_name: string;
  broker_money: number;
  broker_id: number;

  constructor(name: string, money: number, id: number) {
    this.broker_name = name;
    this.broker_money = money;
    this.broker_id = id;
  }
}
