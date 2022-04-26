export class ShareClass{

  share_id: number;
  emitent_name: string;
  share_price: number;
  distribution: string;
  max_change: number;
  amount: number;

  constructor(share_id: number, emitent_name: string, share_price: number, distribution: string, max_change: number, amount: number) {
    this.share_id = share_id;
    this.emitent_name = emitent_name;
    this.share_price = share_price;
    this.distribution = distribution;
    this.max_change = max_change;
    this.amount = amount;
  }
}
