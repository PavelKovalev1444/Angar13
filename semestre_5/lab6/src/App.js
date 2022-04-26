import React from 'react';
import {BrowserRouter as Router, Routes, Route} from "react-router-dom";
import Login from "./components/login";
import Admin from "./components/admin";
import User from "./components/user";
import HW from "./components/helloworld";
import './App.css';

class App extends React.Component{

  render() {
    return (
        <div className='App'>
          <Router>
            <div>
              <Routes>
                <Route path="/" element={<Login/>}/>
                <Route path="/user/:num" element={<User/>}/>
                <Route path="/admin" element={<Admin/>}/>
                <Route path="/hw" element={<HW/>}/>
              </Routes>
            </div>
          </Router>
        </div>
    );
  }

}

export default App;
