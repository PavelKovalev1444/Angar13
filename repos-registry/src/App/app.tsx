import React from "react"
import { BrowserRouter, Route, Routes } from "react-router-dom";
import { ReposPage } from "../Repos/pages/repos";
import { RepositoryPage } from "../Repos/pages/repositoryPage";
import { MainPage } from "../Main/pages";
import { Error404Page } from "../Error/pages/Error404";

import './app.scss'

export const App = () => {
    return (
        <BrowserRouter>
            <div className="container">
                <Routes>
                    <Route path="/" Component={MainPage} />
                    <Route path="/repositories" Component={ReposPage}/>
                    <Route path="/repositories/:username/:reponame" Component={RepositoryPage} />    
                    <Route path="*" Component={Error404Page}/>
                </Routes>
            </div>
        </BrowserRouter>
    );
};
