import { TodoAction, TodoActionTypes } from '../../types/todo'
import { Dispatch } from 'react'
import axios from 'axios'


export const fetchTodos = (page: number = 1, limit: number = 10) => {
    return async (dispatch: Dispatch<TodoAction>) => {
        try{
            dispatch({type: TodoActionTypes.FETCH_TODOS})
            const response = await axios.get('https://jsonplaceholder.typicode.com/todos', {
                params: {_page: page, _limit: limit}
            })
            setTimeout(()=>{
                dispatch({
                    type: TodoActionTypes.FETCH_TODOS_SUCCESS,
                    payload: response.data
                })
            }, 2000)
        }catch(e){
            dispatch({
                type: TodoActionTypes.FETCH_TODOS_ERROR,
                payload: 'Произошла ошибка при загрузке списка дел'
            })
        }
    }
}

export function setTodoPage(page: number): TodoAction{
    return {type: TodoActionTypes.SET_TODO_PAGE, payload: page}
}