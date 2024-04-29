import {combineReducers} from "redux"
import {configureStore} from '@reduxjs/toolkit'
import reposReducer from "./reducers/reposReducer";

const rootReducer = combineReducers({
    repos: reposReducer,
})

const store = configureStore({
    reducer: rootReducer
})

export default store