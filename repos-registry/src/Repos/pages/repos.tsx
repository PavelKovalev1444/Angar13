import React, { useEffect, useState } from "react"
import { useDispatch, useSelector } from "react-redux"
import { getRepos } from "../../store/actions/repos/repos"
import Repo from "../components/Repo"
import { Repository } from "../../store/actions/repos/types"
import { createPages } from "../utils/createPages"
import { setCurrentPage } from "../../store/reducers/reposReducer"

import './repos.scss'

export const ReposPage = () => {
    const dispatch: any = useDispatch()

    const repos: Repository[] = useSelector((state: any) => state.repos.items)
    const isFetching = useSelector((state: any) => state.repos.isFetching)

    const currentPage = useSelector((state: any) => state.repos.currentPage)
    const totalCount = useSelector((state: any) => state.repos.totalCount)
    const perPage = useSelector((state: any) => state.repos.perPage)
    const pagesCount = Math.ceil(totalCount / perPage)
    const pages: number[] = []
    createPages(pages, pagesCount, currentPage)

    const [searchValue, setSearchValue] = useState("")

    useEffect(()=>{
        dispatch(getRepos(searchValue, currentPage, perPage))
    }, [currentPage])

    const searchHandler = () => {
        dispatch(setCurrentPage(1))
        dispatch(getRepos(searchValue, currentPage, perPage))
    }
    
    return (
        <div>
            <div className="title">Список репозиториев</div>

            <div className="search">
                <input value={searchValue} onChange={(e) => setSearchValue(e.target.value)} type="text" placeholder="Repo name" className="search-input"/>
                <button onClick={()=> searchHandler()} className="search-btn">Search</button>
            </div>

            {
                isFetching ? (
                    <div className="fetching" />
                ) : (
                    repos.map(repo => <Repo key={repo.name} repo={repo}/>)
                )
            }

            <div className="pages">
                {pages.map((page, index) => <span
                    key={index}
                    className={currentPage == page ? "current-page" : "page"}
                    onClick={() => dispatch(setCurrentPage(page))}>{page}</span>)}
            </div>
        </div>
    )
}