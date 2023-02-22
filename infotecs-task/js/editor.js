/*
@brief Добавление слушателя для формы.
@detail Добавление слушателя отправки формы для окна редактирования записи таблицы.
*/
document.getElementsByClassName('editor-form')[0].addEventListener('submit', changeTableRow)

/*
@brief Закрытие окна редактирования записи таблицы.
@detailed Данная функция выставляет свойство display в none у окна редактирования записи таблицы.
*/
function closeEditor(){
    document.getElementsByClassName('editor-wrapper')[0].style.display = 'none'
}

/*
@brief Показ окна редактирования записи таблицы.
@detailed Данная функция показывает окно редактирования записи таблицы и заполняет значения input'ов значениями из этой записи.
@param index индекс строки таблицы, которая будет отредактирована.
*/
function showEditor(index){
    let curRecord = data[(page-1)*LIMIT + index]
    indexOfChanging = index
    document.getElementsByClassName('form-input')[0].value = curRecord.name.firstName
    document.getElementsByClassName('form-input')[1].value = curRecord.name.lastName
    document.getElementsByClassName('form-textarea')[0].value = curRecord.about
    document.getElementsByClassName('form-input')[2].value = curRecord.eyeColor
    document.getElementsByClassName('editor-wrapper')[0].style.display = 'block'
}

/*
@brief Изменение записи таблицы.
@detailed Данная функция обрабатывает отправку формы окна редактировани записи таблицы. Функция позволяет не перезагружать страницу при отправке формы, получает значения.
из input'ов формы и закрывает окно редактирования записи таблицы. После этого функция обновляет как значения строки таблице, так и соответствующую запись в изначальных данных, 
чтобы не потерять изменения при сортировке.
@param e событие отправки формы.
*/
function changeTableRow(e){
    e.preventDefault()
    let firstName = e.srcElement[0].value
    let lastName = e.srcElement[1].value
    let about = e.srcElement[2].value
    let eyeColor = e.srcElement[3].value
    closeEditor()
    data[(page - 1)*LIMIT + indexOfChanging].name.firstName = firstName
    data[(page - 1)*LIMIT + indexOfChanging].name.lastName = lastName
    data[(page - 1)*LIMIT + indexOfChanging].about = about
    data[(page - 1)*LIMIT + indexOfChanging].eyeColor = eyeColor
    updateInitialData(data[(page - 1)*LIMIT + indexOfChanging].id, { 
        name: {
            firstName: firstName,
            lastName:lastName
        },
        about: about,
        eyeColor: eyeColor
    })
    updateRow(indexOfChanging, { 
        name: {
            firstName: firstName,
            lastName:lastName
        },
        about: about,
        eyeColor: eyeColor
    })
}

/*
@brief Изменение изначальных данных.
@detailed Данная функция изменяет изначальные данные после редактирования записи таблицы. Функция ищет в изначальных данных запись с таким же id, 
какой ей передали и если находит, заменяет значения полей.
@param oldRecordId id записи, которую нужно изменить.
@param newRecord объект, содержащий новые данные, которыми необходимо обновить соответствующую запись в таблице.
*/
function updateInitialData(oldRecordId, newRecord){
    for(let i = 0; i < INITIALDATA.length; i++){
        if(INITIALDATA[i].id === oldRecordId){
            INITIALDATA[i].name.firstName = newRecord.name.firstName
            INITIALDATA[i].name.lastName = newRecord.name.lastName
            INITIALDATA[i].about = newRecord.about
            INITIALDATA[i].eyeColor = newRecord.eyeColor
            break;
        }
    }
}

/*
@brief Обновление значений в строке таблицы.
@detailed Данная функция обновляет значения в строке таблицы после того, как пользователь отредактировал соответствующую строку в окне редактирования. 
Функция напрямую меняет значения соответствующих DOM элементов.
@param index индекс строки, которую нужно обновить.
@param newRecord объект, содержащий новые данные, которыми необходимо обновить соответствующую запись в таблице.
*/
function updateRow(index, newRecord){
    document.getElementById('td-fn-' + index + '-0').innerHTML = newRecord.name.firstName
    document.getElementById('td-ln-' + index + '-1').innerHTML = newRecord.name.lastName
    document.getElementById('td-ab-' + index + '-2').innerHTML = `<div class='td-ab'>${newRecord.about}</div>`
    if(isColor(newRecord.eyeColor)){
        document.getElementById('td-cl-' + index + '-3').innerHTML = `<div style='background-color: ${newRecord.eyeColor}; width: 40px; height: 20px;'></div>`
    }else{
        document.getElementById('td-cl-' + index + '-3').innerHTML = `<div>${newRecord.eyeColor}</div>`
    }    
}