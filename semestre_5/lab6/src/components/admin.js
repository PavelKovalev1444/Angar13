import React from 'react';
import io from "socket.io-client";

let socket = io('http://localhost:3030', {transports: ['websocket'], withCredentials: true});

export default class Admin extends React.Component{

    merge_users() {
        fetch('http://localhost:8080/sendBrokers')
            .then(response => response.json())
            .then(allUsers => {
                this.setState({brokerList: allUsers.filter((user) => user.broker_name!=='admin')})
            });
        fetch('http://localhost:8080/sendShares')
            .then(response => response.json())
            .then(allShares => {
                this.setState({sharesList: allShares.filter((share) => share.share_id !== -1)})
            });
    }

    componentDidMount() {
        this.merge_users();

        socket.on('buyShareEvent', (data)=>{
            this.setState({brokerList: data.users, sharesList: data.shares});
            //window.location.reload();
        });

        socket.on('updatePrices', (data)=>{
            this.setState({sharesList: data});
        });
    }

    constructor() {
        super();

        this.merge_users = this.merge_users.bind(this);
        this.startTrade = this.startTrade.bind(this);

        this.state = {
            brokerList: null,
            sharesList: null,
            distribution: 'uniform',
        };
    }

    makeBrokersTable(br){
        if(br === null){
            return null;
        }
        let table = [];
        let shareL = '';

        for(let i = 0; i < this.state.brokerList.length; i++){
            console.log('broker: ', this.state.brokerList[i]);
            for(let j = 0; j < this.state.brokerList[i].shares.length; j++){
                shareL += this.state.brokerList[i].shares[j].name + ': ' + this.state.brokerList[i].shares[j].amount +'\n';
            }
            table.push(
                <tr key={i}>
                    <td>{this.state.brokerList[i].broker_name}</td>
                    <td>{this.state.brokerList[i].broker_money}</td>
                    <td>{shareL}</td>
                </tr>
            );
            shareL = '';
        }
        return table;

        /*
        return this.state.brokerList.map(
            (broker, index) => {
                return (
                    <tr key={index}>
                        <td>{broker.broker_name}</td>
                        <td>{broker.broker_money}</td>
                        <td>{broker.shares[0].name}</td>
                    </tr>
                )
            }
        )*/
    }

    makeSharesTable(sh){
        if(sh === null){
            return null;
        }
        return this.state.sharesList.map(
            (share, index) => {
                return (
                    <tr key={index}>
                        <td>{share.emitent_name}</td>
                        <td>{share.share_price}</td>
                        <td>{share.amount}</td>
                    </tr>
                )
            }
        )
    }

    startTrade(event){
        event.preventDefault();
        console.log('startTrading');
        //localStorage.setItem('trade', '1');
        socket.emit("startTrade", this.state.distribution);
    }

    endTrade(event){
        event.preventDefault();
        console.log('endTrading');
        //localStorage.setItem('trade', '0');
        socket.emit("endTrade", this.state.distribution);
    }

    render(){
        return (
            <div className="Admin">
                <p/> Admin
                <br/>
                <form onSubmit={this.startTrade}>
                    <button type="submit" className="btn btn-outline-primary" onClick={(e)=>{this.startTrade(e)}}>Начать торги</button>
                </form>
                <form onSubmit={this.endTrade}>
                    <button type="submit" className="btn btn-outline-primary" onClick={(e)=>{this.endTrade(e)}}>Окончить торги</button>
                </form>
                <div>
                    <p>
                        <select size="1" multiple name="Law" required
                                onChange={(e) => this.setState({distribution: e.target.value})}>
                            <option value="uniform">Равномерный</option>
                            <option value="normal">Нормальный</option>
                        </select>
                    </p>
                </div>
                <div className="brokers">
                    <p>Брокеры:</p>
                    <table>
                        <thead>
                            <tr>
                                <th>Брокер</th>
                                <th>Средства брокера</th>
                                <th>Акции брокера</th>
                            </tr>
                        </thead>
                        <tbody>
                            {this.makeBrokersTable(this.state.brokerList)}
                        </tbody>
                    </table>
                </div>

                <div className="stocks">
                    <p>Акции:</p>
                    <table>
                        <thead>
                            <tr>
                                <th>Акция</th>
                                <th>Цена одной акции</th>
                                <th>Количество акций</th>
                            </tr>
                        </thead>
                        <tbody>
                            {this.makeSharesTable(this.state.sharesList)}
                        </tbody>
                    </table>
                </div>
            </div>
        );
    }
}
