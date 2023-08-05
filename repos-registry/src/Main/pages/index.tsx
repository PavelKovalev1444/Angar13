import React from "react"
import { NavLink } from "react-router-dom"

export const MainPage = () => {
    
    return (
        <div>
            <NavLink to={`repositories`}>Репозитории</NavLink>
        </div>
    )
}