import React from "react";

export default class Login extends React.Component{

    get_users() {
        fetch('http://localhost:8080/sendBrokers')
            .then(response => response.json())
            .then(allUsers => {
                this.setState({brokerList: allUsers.filter((user) => user.broker_name!=='admin')})
            });
    }

    componentDidMount() {
        this.get_users();
    }

    constructor(){
        super();
        this.foo = this.foo.bind(this);
        this.state = {
            brokerList: null,
            username: ''
        };
    }

    foo(){
        if(this.state.username === 'admin'){
            window.location.href='/Admin';
        }else{
            for(let i = 0; i < this.state.brokerList.length; i++) {
                if(this.state.brokerList[i].broker_name === this.state.username) {
                    let counter = 0;
                    if (localStorage.hasOwnProperty("counter")) {
                        counter = parseInt(localStorage.getItem("counter"));
                    } else {
                        localStorage.setItem("counter", '0')
                    }
                    window.location.href = '/User/' + counter;
                    localStorage.setItem(String(counter), this.state.username);
                    counter += 1;
                    localStorage.setItem("counter", String(counter));
                }
            }
        }

    }

    render() {
        return(
            <div className="Login">
                <p>Имя пользователя:</p>
                <input value={this.state.username} onChange={(e) => this.setState({username: e.target.value})}/>
                <br/>
                <button id="a" onClick={()=>{this.foo()}}>Войти</button>
            </div>
        );
    }
}