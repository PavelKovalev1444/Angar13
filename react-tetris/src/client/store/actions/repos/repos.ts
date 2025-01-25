import axios from "axios"
import { Dispatch } from "redux"
import { setIsFetching, setRepos } from "../../reducers/reposReducer"
import { GetContributersResponse, GetReposResponse } from "./types"

export const getRepos = (searchQueries = "Q", currentPage: number, per_page: number) => {
    return async (dispatch: Dispatch) => {
        dispatch(setIsFetching(true))
        const response = await axios.get<GetReposResponse>("https://api.github.com/search/repositories", {
            params: {
                q: searchQueries || "Q" ,
                sort: "stars",
                page: currentPage,
                per_page
            }
        })
        dispatch(setRepos(response.data))
    }
}

export const getCurrentRepo = async (username: string, repoName: string, setRepo: (value: any) => void) => {
    const response = await axios.get(`https://api.github.com/repos/${username}/${repoName}`)
    setRepo(response.data)
 }
 
export const getContributors = async (username: string, repoName: string, setContributors: (value: any) => void) => {
    const response = await axios.get<GetContributersResponse[]>(`https://api.github.com/repos/${username}/${repoName}/contributors`, {
        params: {
            page: 1,
            per_page: 10
        }
    })
    setContributors(response.data)
}