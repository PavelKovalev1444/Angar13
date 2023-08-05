import React from "react"
import {App} from './App/app';
import './index.scss'

import {render} from 'react-dom';
import { Provider } from "react-redux";

import store from "./store"

render(
    <Provider store={store}>
        <App />
    </Provider>,
    document.getElementById('root')
)