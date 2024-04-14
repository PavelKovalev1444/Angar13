type Owner = {
    login: string
    avatar_url: string
}

export type Repository = {
    name: string
    stargazers_count: number
    updated_at: string
    html_url: string
    owner: Owner
}

export type GetReposResponse = {
    items: Repository[]
}

export type GetContributersResponse = {
    id: number,
    login: string,    
    node_id: string,
    avatar_url: string,
    gravatar_id: string,
    url: string,
    html_url: string,
    followers_url: string,
    following_url: string,
    gists_url: string,
    starred_url: string,
    subscriptions_url: string,
    organizations_url: string,
    repos_url: string,
    events_url: string,
    received_events_url: string,
    type: string,
    site_admin: boolean,
    contributions: number
}
