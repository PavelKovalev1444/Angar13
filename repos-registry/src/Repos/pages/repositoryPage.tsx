import React, {useState, useEffect} from 'react';
import {useNavigate, useParams} from "react-router-dom"
import { getContributors, getCurrentRepo } from '../../store/actions/repos/repos';
import { Repository } from '../../store/actions/repos/types';

import './repository.scss'

export const RepositoryPage = () => {
    const {username, reponame} = useParams()
    const navigate = useNavigate()
    const [repo, setRepo] = useState<Repository>({owner: {login: "", avatar_url: ""}, html_url: "", name: "", stargazers_count: 0, updated_at: ""})
    const [contributors, setContributors] = useState([])

    console.log('RepositoryPage')

    useEffect(()=>{
        getCurrentRepo(username || '', reponame || '', setRepo)
        getContributors(username || '', reponame || '', setContributors)
    }, [])

    const handleClick = () => {
        navigate(-1)
    }

    return (
        <div>
            <button onClick={handleClick} className="back-btn">BACK</button>
            <div className="card">
                <img src={repo.owner.avatar_url} alt=""/>
                <div className="name">{repo.name}</div>
                <div className="stars">{repo.stargazers_count}</div>
            </div>
            {contributors.map((c: any, index) =>
                <div key="index">{index+1}. {c.login}</div>
            )}
        </div>
    );
};
