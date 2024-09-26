import React, {useState} from 'react';
import io from "socket.io-client";
import Modal from "react-bootstrap/Modal";

let socket = io('http://localhost:3030', {transports: ['websocket'], withCredentials: true});

function CreateModalBuy(id) {
    if(id === undefined){
        id = 0;
    }
    const [show, setShow] = useState(false);
    const handleClose = () => setShow(false);
    const handleShow = () => setShow(true);
    return(
        <div className="Modal">
            <header className="Modal-header">
                <button
                    type="button"
                    className="btn btn-success"
                    disabled={tmpState.state.buttonState}
                    onClick={handleShow}
                >
                    Купить
                </button>
            </header>
            <Modal show={show} onHide={handleClose} aria-labelledby="contained-modal-title-vcenter" size='sm' centered>
                <Modal.Header>
                    <Modal.Title>Купить акции</Modal.Title>
                </Modal.Header>
                <Modal.Body>
                    <input value={tmpState.state.buyAmount}
                           onChange={(e) => {tmpState.setState({buyAmount: e.target.value})}}/>
                </Modal.Body>
                <Modal.Footer>
                    <button className="btn btn-outline-danger" onClick={handleClose}>
                        Закрыть
                    </button>
                    <button className="btn btn-outline-primary" onClick={()=>{
                        if(!isNaN(tmpState.state.sellAmount)) {
                            if (parseInt(tmpState.state.sellAmount) >= 0) {
                                let sumOfShares = 0;
                                let flag = false;
                                //count sum shares
                                for (let i = 0; i < tmpState.state.sharesList.length; i++) {
                                    if (tmpState.state.sharesList[i].emitent_name === id.shname) {
                                        if(tmpState.state.sharesList[i].amount >= parseInt(tmpState.state.buyAmount)) {
                                            flag = true;
                                            sumOfShares = parseInt(tmpState.state.buyAmount) * parseInt(tmpState.state.sharesList[i].share_price);
                                        }
                                    }
                                }
                                //if can buy shares - subtract shares from sharelist
                                if(flag) {
                                    if (parseInt(tmpState.state.user.broker_money) >= sumOfShares) {
                                        for (let i = 0; i < tmpState.state.sharesList.length; i++) {
                                            if (tmpState.state.sharesList[i].emitent_name === id.shname) {
                                                tmpState.state.sharesList[i].amount = parseInt(tmpState.state.sharesList[i].amount) - parseInt(tmpState.state.buyAmount);
                                            }
                                        }
                                        tmpState.state.user.broker_money = parseInt(tmpState.state.user.broker_money) - sumOfShares;
                                        for(let i = 0; i < tmpState.state.user.shares.length; i++){
                                            if(tmpState.state.user.shares[i].name === id.shname){
                                                tmpState.state.user.shares[i].amount = parseInt(tmpState.state.user.shares[i].amount) + parseInt(tmpState.state.buyAmount);
                                            }
                                        }
                                        socket.emit('buyShareEvent', {
                                            brokersList: tmpState.state.users,
                                            sharesList: tmpState.state.sharesList
                                        });
                                    }
                                }
                            }
                        }
                        /*
                        if(!isNaN(tmpState.state.sellAmount)) {
                            if (parseInt(tmpState.state.sellAmount) >= 0) {
                                let sumOfShares = 0;
                                for (let i = 0; i < tmpState.state.sharesList.length; i++) {
                                    if (tmpState.state.sharesList[i].emitent_name === id.shname) {
                                        sumOfShares = tmpState.state.buyAmount * tmpState.state.sharesList[i].share_price;
                                        if (tmpState.state.user.broker_money >= sumOfShares) {
                                            tmpState.state.user.broker_money -= sumOfShares;
                                            for (let j = 0; j < tmpState.state.users.length; j++) {
                                                if (tmpState.state.users[j].broker_name === tmpState.state.user.broker_name) {
                                                    tmpState.state.users[j].broker_money = tmpState.state.user.broker_money;
                                                    for (let a = 0; a < tmpState.state.users[j].shares.length; a++) {
                                                        if (tmpState.state.users[j].shares[a].name === id.shname) {
                                                            tmpState.state.users[j].shares[a].amount = parseInt(parseInt(tmpState.state.users[j].shares[a].amount) + parseInt(tmpState.state.buyAmount));
                                                        }
                                                    }

                                                }
                                            }
                                            tmpState.state.sharesList[i].amount = parseInt(parseInt(tmpState.state.sharesList[i].amount) - parseInt(tmpState.state.buyAmount));
                                        }
                                    }
                                }
                                //console.log('buyShares');
                                socket.emit('buyShareEvent', {
                                    brokersList: tmpState.state.users,
                                    sharesList: tmpState.state.sharesList
                                });
                            }
                        }
                         */
                        tmpState.state.buyAmount = 0;
                        handleClose();
                    }}>
                        Принять
                    </button>
                </Modal.Footer>
            </Modal>
        </div>
    )
}

function CreateModalSell(id) {
    if(id === undefined){
        id = 0;
    }
    const [show, setShow] = useState(false);
    const handleClose = () => setShow(false);
    const handleShow = () => setShow(true);
    return(
        <div className="Modal">
            <header className="Modal-header">
                <button
                    type="button"
                    className="btn btn-danger"
                    disabled={tmpState.state.buttonState}
                    onClick={handleShow}
                >Продать
                </button>
            </header>
            <Modal show={show} onHide={handleClose} aria-labelledby="contained-modal-title-vcenter" size='sm' centered>
                <Modal.Header>
                    <Modal.Title>Продать акции</Modal.Title>
                </Modal.Header>
                <Modal.Body>
                    <input value={tmpState.state.sellAmount}
                           onChange={(e) => tmpState.setState({sellAmount: e.target.value})}/>
                </Modal.Body>
                <Modal.Footer>
                    <button className="btn btn-outline-danger" onClick={handleClose}>
                        Закрыть
                    </button>
                    <button className="btn btn-outline-primary" onClick={()=>{
                        if(!isNaN(tmpState.state.sellAmount)) {
                            if (parseInt(tmpState.state.sellAmount) >= 0) {
                                let sumOfShares = 0;
                                let flag = false;
                                //subtract shares from broker
                                for (let i = 0; i < tmpState.state.user.shares.length; i++) {
                                    if (tmpState.state.user.shares[i].name === id.shname) {
                                        if (tmpState.state.user.shares[i].amount >= parseInt(tmpState.state.sellAmount)) {
                                            tmpState.state.user.shares[i].amount = parseInt(tmpState.state.user.shares[i].amount) - parseInt(tmpState.state.sellAmount);
                                            flag = true;
                                        }
                                    }
                                }
                                //add shares to sharelist
                                if (flag) {
                                    for (let i = 0; i < tmpState.state.sharesList.length; i++) {
                                        if (tmpState.state.sharesList[i].emitent_name === id.shname) {
                                            tmpState.state.sharesList[i].amount = parseInt(tmpState.state.sharesList[i].amount) + parseInt(tmpState.state.sellAmount);
                                            sumOfShares = parseInt(tmpState.state.sellAmount) * parseInt(tmpState.state.sharesList[i].share_price);
                                        }
                                    }
                                    tmpState.state.user.broker_money = parseInt(tmpState.state.user.broker_money) + parseInt(sumOfShares);
                                }
                                //change info in users
                                if (flag) {
                                    for (let i = 0; i < tmpState.state.users.length; i++) {
                                        if (tmpState.state.users[i].broker_name === tmpState.state.user.broker_name) {
                                            tmpState.state.users[i].broker_money = tmpState.state.user.broker_money;
                                            tmpState.state.users[i].shares = tmpState.state.user.shares;
                                        }
                                    }
                                }
                                if (flag) {
                                    socket.emit('buyShareEvent', {
                                        brokersList: tmpState.state.users,
                                        sharesList: tmpState.state.sharesList
                                    });
                                }
                            }
                        }
                        tmpState.state.sellAmount = 0;
                        handleClose();
                    }}>
                        Принять
                    </button>
                </Modal.Footer>
            </Modal>
        </div>
    )
}

let tmpState = {};

export default class User extends React.Component{
    clientId = window.location.href.slice(27);

    constructor(){
        super();
        this.state={
            buyAmount: 0,
            sellAmount:0,
            user:{
                broker_id: 0,
                broker_name: '',
                broker_money: null,
                shares: []
            },
            users: [],
            sharesList: [],
            buttonState: true,
            message: ''
        }
        this.getUserInfo = this.getUserInfo.bind(this);
        this.getUsers = this.getUsers.bind(this);
        this.getShares = this.getShares.bind(this);
    }

    componentDidMount() {
        this.getUserInfo();
        this.getUsers();
        this.getShares();

        socket.on('buyShareEvent', (data)=>{
            this.setState({users: data.users, sharesList: data.shares});
            tmpState.state.users = data.users;
            tmpState.state.shareList = data.shares;
        });

        socket.on('startTrade', ()=>{
            this.setState({buttonState: false, message: 'Торги начались!'});
            tmpState.buttonState = false;
            tmpState.message = 'Торги начались!';
        });

        socket.on('endTrade', ()=>{
            this.setState({buttonState: true, message: 'Торги окончились!'});
            tmpState.buttonState = true;
            tmpState.message = 'Торги окончились!';
        });

        socket.on('updatePrices', (data)=>{
            this.setState({sharesList: data});
            tmpState.state.sharesList = data;
        });
    }

    getUserInfo() {
        fetch('http://localhost:8080/getUser/' + localStorage.getItem(this.clientId))
            .then(response => response.json())
            .then(data => {
                this.setState(
                    {user: data}
                );
            });
    }

    getUsers(){
        fetch('http://localhost:8080/getUsers')
            .then(response => response.json())
            .then(data => {
                this.setState(
                    {users: data}
                );
            });
    }

    getShares(){
        fetch('http://localhost:8080/getShares')
            .then(response => response.json())
            .then(allShares => {
                this.setState(
                    {sharesList: allShares.filter((share) => share.share_id !== -1)}
                );
            });
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
                        <td>
                            <CreateModalBuy id={index + 'buyBtn'} shname={share.emitent_name}/>
                        </td>
                    </tr>
                )
            }
        )
    }

    makeUsersSharesTable(sh){
        if(sh === null){
            return null;
        }
        return this.state.user.shares.map(
            (share, index) => {
                return (
                    <tr key={index}>
                        <td id={index+ 'td0'}>{share.name}</td>
                        <td id={index+ 'td1'}>{share.amount}</td>
                        <td id={index+ 'td2'}>
                            <CreateModalSell id={index + 'sellBtn'} shname={share.name} />
                        </td>
                    </tr>
                )
            }
        )
    }

    makeMoney(mn){
        if(mn === null){
            return null
        }else{
            return this.state.user.broker_money;
        }
    }

    render() {
        tmpState = this;
        return (
            <div className="User">
                <p/> Welcome, {this.state.user.broker_name}
                <p/> Money: {this.makeMoney(this.state.user.broker_money)}
                <p/> {tmpState.state.message}
                <div className="shares">
                    <p>Акции:</p>
                    <table>
                        <thead>
                            <tr>
                                <th>Акция</th>
                                <th>Цена одной акции</th>
                                <th>Количество акций</th>
                                <th>Действие</th>
                            </tr>
                        </thead>
                        <tbody>
                            {this.makeSharesTable(this.state.sharesList)}
                        </tbody>
                    </table>
                </div>
                <div className="userShares">
                    <p>Акции пользователя:</p>
                    <table>
                        <thead>
                        <tr>
                            <th>Акция</th>
                            <th>Количество акций</th>
                            <th>Действие</th>
                        </tr>
                        </thead>
                        <tbody>
                            {this.makeUsersSharesTable(this.state.user.shares)}
                        </tbody>
                    </table>
                </div>
            </div>
        );
    }

}
