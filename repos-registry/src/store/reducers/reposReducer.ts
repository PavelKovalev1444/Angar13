const enum ActionType {
    SET_REPOS = "SET_REPOS",
    SET_IS_FETCHING = "SET_IS_FETCHING",
    SET_CURRENT_PAGE = "SET_CURRENT_PAGE"
}

const defaultState = {
    items: [],
    isFetching: true,
    currentPage:1,
    perPage:10,
    totalCount:0
}


export default function reposReducer(state = defaultState, action: any) {
    switch (action.type) {
        case ActionType.SET_REPOS:
            return {
                ...state,
                items: action.payload.items,
                totalCount: action.payload.total_count,
                isFetching: false
            }
        case ActionType.SET_IS_FETCHING:
            return {
                ...state,
                isFetching: action.payload
            }
        case ActionType.SET_CURRENT_PAGE:
            return {
                ...state,
                currentPage: action.payload
            }
        default:
            return state
    }
}

export const setRepos = (repos: any) => ({type: ActionType.SET_REPOS, payload: repos})
export const setIsFetching = (isFetching: any) => ({type: ActionType.SET_IS_FETCHING, payload: isFetching})
export const setCurrentPage = (page: any) => ({type: ActionType.SET_CURRENT_PAGE, payload: page})