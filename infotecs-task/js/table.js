/*
@brief Переход на предыдущую страницу.
@detail В случае, если текущая страница не первая, функция запускает отрисовку таблицы для предыдущих 10 записей из массива данных.
*/
function prevPage(){
    if(page > 1){
        page -= 1
        createTable(firstNameSortImgTag, lastNameSortImgTag, aboutSortImgTag, eyeColorSortImgTag)
    }
}

/*
@brief Переход на следующую страницу.
@detail В случае, если текущая страница не последняя, функция запускает отрисовку таблицы для следующих 10 записей из массива данных.
*/
function nextPage(){
    if(page < MAXPAGES){
        page += 1
        createTable(firstNameSortImgTag, lastNameSortImgTag, aboutSortImgTag, eyeColorSortImgTag)
    }
}

/*
@brief Отбор записей для таблицы.
@detail Функция отбирает LIMIT (задано как 10) записей из таблицы с учетом страницы, на которой находится пользователь.
@return res список записей.
*/
function getData(){
    let res = []
    for(let i = 0; i < LIMIT; i++){
        res.push(data[(page - 1)*LIMIT + i])
    }
    return res
}

/*
@brief Создание заголовка таблицы.
@detail Функция формирует строку, представляющую собой заголовок таблицы, без учета скрытых столбцов.
@param firstNameSortImgTag строка, содержащая тег изображения типа текущей сортировки столбца "Имя".
@param lastNameSortImgTag строка, содержащая тег изображения типа текущей сортировки столбца "Фамилия".
@param aboutSortImgTag строка, содержащая тег изображения типа текущей сортировки столбца "Описание".
@param eyeColorSortImgTag строка, содержащая тег изображения типа текущей сортировки столбца "Цвет глаз".
@return header строка, представляющая собой теги заголовка таблицы.
*/
function makeTableHeader(firstNameSortImgTag, lastNameSortImgTag, aboutSortImgTag, eyeColorSortImgTag){
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
/*
@brief Проверка того, является ли строка корректным CSS-цветом.
@detail Функция создает переменную s равную свойству style объекта типа Option(), после чего присваивает свойству color значение параметра strcolor. 
Далее происходят два сравнения: значения свойства color и переданного параметра, а также того, подходит ли переданный параметр под регулярное выражение, 
которое определяет цвета в 16-ичном формате.
В случае, если хоть одна из проверок корректна - переданная строка является валидным CSS цветом.
@param strColor строка, которую надо проверить на то, является ли она валидным CSS цветом.
@return true/false да или нет, в зависимости от того, является ли строка валидным CSS цветом или нет.
*/
function isColor(strColor){
    let s = new Option().style;
    s.color = strColor;
    let check1 = s.color == strColor;
    let check2 = /^#[0-9A-F]{6}$/i.test(strColor);
    if(check1 == true || check2 == true){
        return true;
    } else{
        return false;
    }
}

/*
@brief Создание тела таблицы.
@detail Функция формирует строку, представляющую собой тело таблицы, без учета скрытых столбцов. При создании строки table, происходит проверка 
флажков, отвечающих за показ/скрытие соответствующих столбцов. Если хоть один флажок истинный (хоть один столбец должен быть показан), будет сформирована строка,
содержащая html-разметку таблицы.
@return table строка, представляющая собой теги тела таблицы.
*/
function makeTableBody(){
    let table = ''
    let i = 0
    let data = getData()

    if(firstNameCol || lastNameCol || aboutCol || eyeColorCol){
        table += `<tbody>`
        data.forEach(element => {
            table += `<tr id='tr-${i}' onclick='showEditor(${i})'>`
            if(firstNameCol){
                table += `<td id='td-fn-${i}-0'>`
                table += element.name.firstName
                table += '</td>'
            }
            if(lastNameCol){
                table += `<td id='td-ln-${i}-1'>`
                table += element.name.lastName
                table += '</td>'
            }
            if(aboutCol){
                table +=  `<td id='td-ab-${i}-2'>`
                table += `<div class='td-ab'>`
                table += element.about
                table += `</div>`
                table += '</td>'
            }
            if(eyeColorCol){
                table +=  `<td id='td-cl-${i}-3'>`
                if(isColor(element.eyeColor)){
                    table += `<div style='background-color: ${element.eyeColor}; width: 40px; height: 20px;'>`
                }else{
                    table += `<div>${element.eyeColor}`
                }
                table += `</div>`
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

/*
@brief Создание панели пагинации под таблицец.
@detail Функция формирует строку, представляющую собой несколько тегов - панель пагинации под таблицей. В случае, если пользователь находится на первой странице, 
кнопки перехода на предыдущую страницу не будет. В случае, если пользователь дошел до последней траницы, кнопки перехода на последнюю страницу не будет. 
Между кнопками располагается номер страницы, обернутый в div. Также, панели пагинации не будет, если пользователь не выбрал ни одного столбца для отображения.
@return table строка, представляющая собой теги тела таблицы.
*/
function makeButtons(){
    if(page === 1 && (firstNameCol || lastNameCol || aboutCol || eyeColorCol)){
        return `<div id="page">
                    ${page}
                </div>
                <button class="button" type="button" onclick="nextPage()">
                    Вперед
                </button>`
    }else if(page === MAXPAGES && (firstNameCol || lastNameCol || aboutCol || eyeColorCol)){
        return `<button class="button" type="button" onclick="prevPage()">
                    Назад
                </button>
                <div id="page">
                    ${page}
                </div>`
    }else if(firstNameCol || lastNameCol || aboutCol || eyeColorCol){
        return `<button class="button" type="button" onclick="prevPage()">
                    Назад
                </button>
                <div id="page">
                    ${page}
                </div>
                <button class="button" type="button" onclick="nextPage()">
                    Вперед
                </button>`
    }else{
        return ''
    }
}

/*
@brief Создание таблицы.
@detail Функция создает строку, представляющую собой таблицу, сначала вызывая функцию для создания заголовка, далее вызывая функцию создания тела таблицы, 
после чего прикрепляет полученную строку в HTML разметку. После прикрепления таблицы, функция создает и прикрепляет панель пагинации в соответствующую HTML разметку.
@param firstNameSortImgTag строка, содержащая тег изображения типа текущей сортировки столбца "Имя".
@param lastNameSortImgTag строка, содержащая тег изображения типа текущей сортировки столбца "Фамилия".
@param aboutSortImgTag строка, содержащая тег изображения типа текущей сортировки столбца "Описание".
@param eyeColorSortImgTag строка, содержащая тег изображения типа текущей сортировки столбца "Цвет глаз".
*/
function createTable(firstNameSortImgTag, lastNameSortImgTag, aboutSortImgTag, eyeColorSortImgTag){
    let table = ''
    table += makeTableHeader(firstNameSortImgTag, lastNameSortImgTag, aboutSortImgTag, eyeColorSortImgTag)
    table += makeTableBody()
    document.getElementById('table-wrapper').innerHTML = table
    document.getElementById('buttons-wrapper').innerHTML = makeButtons()
}

/*
Вызов функции создания таблицы. Необходим, чтобы после загрузки страницы сразу была отображена таблица.
*/
createTable(firstNameSortImgTag, lastNameSortImgTag, aboutSortImgTag, eyeColorSortImgTag)