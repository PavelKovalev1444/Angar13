let page = 1
const limit = 10
let data = JSON.parse(JSON.stringify(initialData))
const maxPages = Math.ceil(data.length/limit)
let sortFirstNameType = 0
let sortLastNameType = 0
let sortAboutType = 0
let sortEyeType = 0

let firstNameSortImgTag = `<img src='No-sorting.png'>`
let lastNameSortImgTag = `<img src='No-sorting.png'>`
let aboutSortImgTag = `<img src='No-sorting.png'>`
let eyeColorSortImgTag = `<img src='No-sorting.png'>`

function sortFirstNameColumn(){
    if(sortFirstNameType === 0){
        sortFirstNameType = 1
        data.sort((a, b)=>{
            if(a.name.firstName < b.name.firstName){
                return -1
            }else if(a.name.firstName === b.name.firstName){
                return 0
            }else{
                return 1
            }
        })
        firstNameSortImgTag = `<img src='Sort-Alpha-Asc-16.png'>`
        createTable(firstNameSortImgTag, lastNameSortImgTag, aboutSortImgTag, eyeColorSortImgTag)
    }else if(sortFirstNameType === 1){
        sortFirstNameType = -1
        data.sort((a, b)=>{
            if(a.name.firstName < b.name.firstName){
                return 1
            }else if(a.name.firstName === b.name.firstName){
                return 0
            }else{
                return -1
            }
        })
        firstNameSortImgTag = `<img src='Sort-Alpha-Desc-16.png'>`
        createTable(firstNameSortImgTag, lastNameSortImgTag, aboutSortImgTag, eyeColorSortImgTag)
    }else{
        sortFirstNameType = 0
        data = JSON.parse(JSON.stringify(initialData))
        firstNameSortImgTag = `<img src='No-sorting.png'>`
        createTable(firstNameSortImgTag, lastNameSortImgTag, aboutSortImgTag, eyeColorSortImgTag)
    }
}

function sortLastNameColumn(){
    if(sortLastNameType === 0){
        sortLastNameType = 1
        data.sort((a, b)=>{
            if(a.name.lastName < b.name.lastName){
                return -1
            }else if(a.name.lastName === b.name.lastName){
                return 0
            }else{
                return 1
            }
        })
        lastNameSortImgTag = `<img src='Sort-Alpha-Asc-16.png'>`
        createTable(firstNameSortImgTag, lastNameSortImgTag, aboutSortImgTag, eyeColorSortImgTag)
    }else if(sortLastNameType === 1){
        sortLastNameType = -1
        data.sort((a, b)=>{
            if(a.name.lastName < b.name.lastName){
                return 1
            }else if(a.name.lastName === b.name.lastName){
                return 0
            }else{
                return -1
            }
        })
        lastNameSortImgTag = `<img src='Sort-Alpha-Desc-16.png'>`
        createTable(firstNameSortImgTag, lastNameSortImgTag, aboutSortImgTag, eyeColorSortImgTag)
    }else{
        sortLastNameType = 0
        data = JSON.parse(JSON.stringify(initialData))
        lastNameSortImgTag = `<img src='No-sorting.png'>`
        createTable(firstNameSortImgTag, lastNameSortImgTag, aboutSortImgTag, eyeColorSortImgTag)
    }
}

function sortAboutColumn(){
    if(sortAboutType === 0){
        sortAboutType = 1
        data.sort((a, b)=>{
            if(a.about < b.about){
                return -1
            }else if(a.about === b.about){
                return 0
            }else{
                return 1
            }
        })
        aboutSortImgTag = `<img src='Sort-Alpha-Asc-16.png'>`
        createTable(firstNameSortImgTag, lastNameSortImgTag, aboutSortImgTag, eyeColorSortImgTag)
    }else if(sortAboutType === 1){
        sortAboutType = -1
        data.sort((a, b)=>{
            if(a.about < b.about){
                return 1
            }else if(a.about === b.about){
                return 0
            }else{
                return -1
            }
        })
        aboutSortImgTag = `<img src='Sort-Alpha-Desc-16.png'>`
        createTable(firstNameSortImgTag, lastNameSortImgTag, aboutSortImgTag, eyeColorSortImgTag)
    }else{
        sortAboutType = 0
        data = JSON.parse(JSON.stringify(initialData))
        aboutSortImgTag = `<img src='No-sorting.png'>`
        createTable(firstNameSortImgTag, lastNameSortImgTag, aboutSortImgTag, eyeColorSortImgTag)
    }
}

function sortEyeColorColumn(){
    if(sortEyeType === 0){
        sortEyeType = 1
        data.sort((a, b)=>{
            if(a.eyeColor < b.eyeColor){
                return -1
            }else if(a.eyeColor === b.eyeColor){
                return 0
            }else{
                return 1
            }
        })
        eyeColorSortImgTag = `<img src='Sort-Alpha-Asc-16.png'>`
        createTable(firstNameSortImgTag, lastNameSortImgTag, aboutSortImgTag, eyeColorSortImgTag)
    }else if(sortEyeType === 1){
        sortEyeType = -1
        data.sort((a, b)=>{
            if(a.eyeColor < b.eyeColor){
                return 1
            }else if(a.eyeColor === b.eyeColor){
                return 0
            }else{
                return -1
            }
        })
        eyeColorSortImgTag = `<img src='Sort-Alpha-Desc-16.png'>`
        createTable(firstNameSortImgTag, lastNameSortImgTag, aboutSortImgTag, eyeColorSortImgTag)
    }else{
        sortEyeType = 0
        data = JSON.parse(JSON.stringify(initialData))
        eyeColorSortImgTag = `<img src='No-sorting.png'>`
        createTable(firstNameSortImgTag, lastNameSortImgTag, aboutSortImgTag, eyeColorSortImgTag)
    }
}

function prevPage(){
    if(page > 1){
        page -= 1
        createTable(firstNameSortImgTag, lastNameSortImgTag, aboutSortImgTag, eyeColorSortImgTag)
    }
}

function nextPage(){
    if(page < maxPages){
        page += 1
        createTable(firstNameSortImgTag, lastNameSortImgTag, aboutSortImgTag, eyeColorSortImgTag)
    }
}

function getData(){
    let res = []
    for(let i = 0; i < limit; i++){
        res.push(data[(page - 1)*limit + i])
    }
    return res
}

function createTableHeader(firstNameSortImgTag, lastNameSortImgTag, aboutSortImgTag, eyeColorSortImgTag){
    return `<thead id="table-header">
        <tr>
            <th onclick='sortFirstNameColumn()'>
                <div class='th-div-wrapper'>
                    Имя
                    ${firstNameSortImgTag}
                </div>
            </th>
            <th onclick='sortLastNameColumn()'>
                <div class='th-div-wrapper'>
                    Фамилия
                    ${lastNameSortImgTag}
                </div>    
            </th>
            <th onclick='sortAboutColumn()'>
                <div class='th-div-wrapper'>
                    Описание
                    ${aboutSortImgTag}
                </div>
            </th>
            <th onclick='sortEyeColorColumn()'>
                <div class='th-div-wrapper'>
                    Цвет глаз
                    ${eyeColorSortImgTag}
                </div>
            </th>
        </tr>
    </thead>`
}

function makeTableBody(){
    let table = '<tbody>'
    let i = 0
    let data = getData()

    data.forEach(element => {
        table += `<tr id='tr-${i}'>`
        
        table += `<td id='td-fn-${i}'>`
        table += element.name.firstName
        table += '</td>'

        table += `<td id='td-ln-${i}'>`
        table += element.name.lastName
        table += '</td>'

        table +=  `<td id='td-ab-${i}' >`
        table += `<div class='td-ab'>`
        table += element.about
        table += `</div>`
        table += '</td>'

        table +=  `<td id='td-cl-${i}'>`
        table += `<div style='background-color: ${element.eyeColor}; padding: 25% 25%;'>`
        table += `<div>`
        table += '</td>'

        table += '</tr>'
        
        i++
    });
    table += '</tbody>'
    return table
}

function createTable(firstNameSortImgTag, lastNameSortImgTag, aboutSortImgTag, eyeColorSortImgTag){
    let table = '<table id="table">'
    table += createTableHeader(firstNameSortImgTag, lastNameSortImgTag, aboutSortImgTag, eyeColorSortImgTag)
    table += makeTableBody()
    table += '</table>'
    document.getElementById('table-wrapper').innerHTML = table
    document.getElementById('page').innerHTML = '' + page
}

createTable(firstNameSortImgTag, lastNameSortImgTag, aboutSortImgTag, eyeColorSortImgTag)