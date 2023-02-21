let page = 1
const limit = 10
let data = JSON.parse(JSON.stringify(initialData))
const maxPages = Math.ceil(data.length/limit)
let sortFirstNameType = 0
let sortLastNameType = 0
let sortAboutType = 0
let sortEyeType = 0
let indexOfChanging = -1

let firstNameSortImgTag = `<img src='./icons/NoSort.png'>`
let lastNameSortImgTag = `<img src='./icons/NoSort.png'>`
let aboutSortImgTag = `<img src='./icons/NoSort.png'>`
let eyeColorSortImgTag = `<img src='./icons/NoSort.png'>`

let firstNameCol = true
let lastNameCol = true
let aboutCol = true
let eyeColorCol = true

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
        firstNameSortImgTag = `<img src='./icons/SortAsc.png'>`
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
        firstNameSortImgTag = `<img src='./icons/SortDesc.png'>`
        createTable(firstNameSortImgTag, lastNameSortImgTag, aboutSortImgTag, eyeColorSortImgTag)
    }else{
        sortFirstNameType = 0
        data = JSON.parse(JSON.stringify(initialData))
        firstNameSortImgTag = `<img src='./icons/NoSort.png'>`
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
        lastNameSortImgTag = `<img src='./icons/SortAsc.png'>`
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
        lastNameSortImgTag = `<img src='./icons/SortDesc.png'>`
        createTable(firstNameSortImgTag, lastNameSortImgTag, aboutSortImgTag, eyeColorSortImgTag)
    }else{
        sortLastNameType = 0
        data = JSON.parse(JSON.stringify(initialData))
        lastNameSortImgTag = `<img src='./icons/NoSort.png'>`
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
        aboutSortImgTag = `<img src='./icons/SortAsc.png'>`
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
        aboutSortImgTag = `<img src='./icons/SortDesc.png'>`
        createTable(firstNameSortImgTag, lastNameSortImgTag, aboutSortImgTag, eyeColorSortImgTag)
    }else{
        sortAboutType = 0
        data = JSON.parse(JSON.stringify(initialData))
        aboutSortImgTag = `<img src='./icons/NoSort.png'>`
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
        eyeColorSortImgTag = `<img src='./icons/SortAsc.png'>`
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
        eyeColorSortImgTag = `<img src='./icons/SortDesc.png'>`
        createTable(firstNameSortImgTag, lastNameSortImgTag, aboutSortImgTag, eyeColorSortImgTag)
    }else{
        sortEyeType = 0
        data = JSON.parse(JSON.stringify(initialData))
        eyeColorSortImgTag = `<img src='./icons/NoSort.png'>`
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
    let header = ''
    if(firstNameCol || lastNameCol || aboutCol || eyeColorCol){
        header = `<table id="table"><thead id="table-header"><tr>`
    }
    if(firstNameCol){
        header += `<th onclick='sortFirstNameColumn()'>
                        <div class='th-div-wrapper'>
                            Имя
                            ${firstNameSortImgTag}
                        </div>
                    </th>`
    }
    if(lastNameCol){
        header += `<th onclick='sortLastNameColumn()'>
                        <div class='th-div-wrapper'>
                            Фамилия
                            ${lastNameSortImgTag}
                        </div>    
                    </th>`
    }
    if(aboutCol){
        header += `<th onclick='sortAboutColumn()'>
                    <div class='th-div-wrapper'>
                        Описание
                        ${aboutSortImgTag}
                    </div>
                </th>`
    }
    if(eyeColorCol){
        header += `<th onclick='sortEyeColorColumn()'>
                    <div class='th-div-wrapper'>
                        Цвет глаз
                        ${eyeColorSortImgTag}
                    </div>
                </th>`
    }
    if(firstNameCol || lastNameCol || aboutCol || eyeColorCol){
        header += `</tr></thead>`
    }
    return header
}

function makeTableBody(){
    let table = ''
    let i = 0
    let data = getData()

    if(firstNameCol || lastNameCol || aboutCol || eyeColorCol){
        table += `<tbody>`
        data.forEach(element => {
            table += `<tr id='tr-${i}' onclick='showEditor(${i})'>`
            if(firstNameCol){
                table += `<td id='td-fn-${i}'>`
                table += element.name.firstName
                table += '</td>'
            }
            if(lastNameCol){
                table += `<td id='td-ln-${i}'>`
                table += element.name.lastName
                table += '</td>'
            }
            if(aboutCol){
                table +=  `<td id='td-ab-${i}' >`
                table += `<div class='td-ab'>`
                table += element.about
                table += `</div>`
                table += '</td>'
            }
            if(eyeColorCol){
                table +=  `<td id='td-cl-${i}'>`
                table += `<div style='background-color: ${element.eyeColor}; padding: 25% 25%;'>`
                table += `<div>`
                table += '</td>'
            }
            table += '</tr>'
            
            i++
        });
        table += '</tbody>'
        table += '</table>'
    }
    return table
}

function makeButtons(){
    if(page === 1 && (firstNameCol || lastNameCol || aboutCol || eyeColorCol)){
        return `<div id="page">
                    ${page}
                </div>
                <button class="button" type="button" onclick="nextPage()">
                    Вперед
                </button>`
    }else if(page === maxPages){
        return `<button class="button" type="button" onclick="prevPage()">
                    Назад
                </button>
                <div id="page">
                    ${page}
                </div>`
    }else{
        return `<button class="button" type="button" onclick="prevPage()">
                    Назад
                </button>
                <div id="page">
                    ${page}
                </div>
                <button class="button" type="button" onclick="nextPage()">
                    Вперед
                </button>`
    }
}

function closeEditor(){
    document.getElementsByClassName('editor-wrapper')[0].style.display = 'none'
}

function showEditor(index){
    curRecord = data[(page-1)*limit + index]
    indexOfChanging = index
    document.getElementsByClassName('form-input')[0].value = curRecord.name.firstName
    document.getElementsByClassName('form-input')[1].value = curRecord.name.lastName
    document.getElementsByClassName('form-textarea')[0].value = curRecord.about
    document.getElementsByClassName('form-input')[2].value = curRecord.eyeColor
    document.getElementsByClassName('editor-wrapper')[0].style.display = 'block'
}

function changeTableRow(e){
    e.preventDefault()
    let firstName = e.srcElement[0].value
    let lastName = e.srcElement[1].value
    let about = e.srcElement[2].value
    let eyeColor = e.srcElement[3].value
    closeEditor()
    data[(page - 1)*limit + indexOfChanging].name.firstName = firstName
    data[(page - 1)*limit + indexOfChanging].name.lastName = lastName
    data[(page - 1)*limit + indexOfChanging].about = about
    data[(page - 1)*limit + indexOfChanging].eyeColor = eyeColor
    updateInitialData(data[(page - 1)*limit + indexOfChanging].id, { 
        name: {
            firstName: firstName,
            lastName:lastName
        },
        about: about,
        eyeColor: eyeColor
    })
    createTable(firstNameSortImgTag, lastNameSortImgTag, aboutSortImgTag, eyeColorSortImgTag)
}

function updateInitialData(oldRecordId, newRecord){
    for(let i = 0; i < initialData.length; i++){
        if(initialData[i].id === oldRecordId){
            initialData[i].name.firstName = newRecord.name.firstName
            initialData[i].name.lastName = newRecord.name.lastName
            initialData[i].about = newRecord.about
            initialData[i].eyeColor = newRecord.eyeColor
            break;
        }
    }
}

function createTable(firstNameSortImgTag, lastNameSortImgTag, aboutSortImgTag, eyeColorSortImgTag){
    let table = ''
    table += createTableHeader(firstNameSortImgTag, lastNameSortImgTag, aboutSortImgTag, eyeColorSortImgTag)
    table += makeTableBody()
    document.getElementById('table-wrapper').innerHTML = table
    document.getElementById('buttons-wrapper').innerHTML = makeButtons()
}

document.getElementsByClassName('editor-form')[0].addEventListener('submit', changeTableRow)

createTable(firstNameSortImgTag, lastNameSortImgTag, aboutSortImgTag, eyeColorSortImgTag)