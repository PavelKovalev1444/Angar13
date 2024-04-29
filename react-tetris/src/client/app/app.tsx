import React from "react"
import { BrowserRouter, Route, Routes } from "react-router-dom";
import { Error404Page } from "../error/pages/Error404";

import './app.scss'
import { MainPage } from "../pages/MainPage";

export const App = () => {
    return (
        <BrowserRouter>
            <div className="container">
                <Routes>
                    <Route path="/" Component={MainPage} />
                    <Route path="*" Component={Error404Page}/>
                </Routes>
            </div>
        </BrowserRouter>
    );
};
