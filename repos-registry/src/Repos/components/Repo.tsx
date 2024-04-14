import React from 'react';
import { Repository } from '../../store/actions/repos/types';
import { NavLink } from 'react-router-dom';

import './repo.scss'

type RepoProps = {
    repo: Repository
}

const Repo = ({repo}: RepoProps) => {
    
    const {name, stargazers_count, updated_at, html_url} = repo

    return (
        <div className="repo">
            <div className="repo-header">
                <div className="repo-header-name">
                    <NavLink to={`/repositories/${repo.owner.login}/${repo.name}`}>
                        {name}
                    </NavLink>
                </div>
                <div className="repo-header-stars">Количество звезд: {stargazers_count}</div>
            </div>
            <div className="repo-last-commit">Последний коммит: {updated_at}</div>
            <a href={html_url} className="repo-link">Ссылка на репозиторий: {html_url}</a>
        </div>
    );
};

export default Repo;