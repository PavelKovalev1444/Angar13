/*
@brief Сортировка таблицы по столбцу "Имя"
@detailed Данная функция проверяет, как именно отсортирована таблица на текущий момент по столбцу "Имя":
в алфавитном порядке, в обратном алфавитном порядке или не отсортирована. Если таблица не отсортирована по столбцу "Имя", то она сортируется
в алфавитном порядке по этому столбцу; если таблица отсортирована в алфавитном порядке, то сортируется в обратном порядке, если отсортирована в обратном порядке - 
таблица возвращается в неотсортированное состояние.
*/
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
        // Копирование массива неотсортированных данных
        data = [...INITIALDATA]
        firstNameSortImgTag = `<img src='./icons/NoSort.png'>`
        createTable(firstNameSortImgTag, lastNameSortImgTag, aboutSortImgTag, eyeColorSortImgTag)
    }
}

/*
@brief Сортировка таблицы по столбцу "Фамилия"
@detailed Данная функция проверяет, как именно отсортирована таблица на текущий момент по столбцу "Фамилия":
в алфавитном порядке, в обратном алфавитном порядке или не отсортирована. Если таблица не отсортирована по столбцу "Фамилия", то она сортируется
в алфавитном порядке по этому столбцу; если таблица отсортирована в алфавитном порядке, то сортируется в обратном порядке, если отсортирована в обратном порядке - 
таблица возвращается в неотсортированное состояние.
*/
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
        // Копирование массива неотсортированных данных
        data = [...INITIALDATA]
        lastNameSortImgTag = `<img src='./icons/NoSort.png'>`
        createTable(firstNameSortImgTag, lastNameSortImgTag, aboutSortImgTag, eyeColorSortImgTag)
    }
}

/*
@brief Сортировка таблицы по столбцу "Описание"
@detailed Данная функция проверяет, как именно отсортирована таблица на текущий момент по столбцу "Описание":
в алфавитном порядке, в обратном алфавитном порядке или не отсортирована. Если таблица не отсортирована по столбцу "Фамилия", то она сортируется
в алфавитном порядке по этому столбцу; если таблица отсортирована в алфавитном порядке, то сортируется в обратном порядке, если отсортирована в обратном порядке - 
таблица возвращается в неотсортированное состояние.
*/
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
        // Копирование массива неотсортированных данных
        data = [...INITIALDATA]
        aboutSortImgTag = `<img src='./icons/NoSort.png'>`
        createTable(firstNameSortImgTag, lastNameSortImgTag, aboutSortImgTag, eyeColorSortImgTag)
    }
}

/*
@brief Сортировка таблицы по столбцу "Цвет глаз"
@detailed Данная функция проверяет, как именно отсортирована таблица на текущий момент по столбцу "Цвет глаз":
в алфавитном порядке, в обратном алфавитном порядке или не отсортирована. Если таблица не отсортирована по столбцу "Цвет глаз", то она сортируется
в алфавитном порядке по этому столбцу; если таблица отсортирована в алфавитном порядке, то сортируется в обратном порядке, если отсортирована в обратном порядке - 
таблица возвращается в неотсортированное состояние.
*/
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
        // Копирование массива неотсортированных данных
        data = [...INITIALDATA]
        eyeColorSortImgTag = `<img src='./icons/NoSort.png'>`
        createTable(firstNameSortImgTag, lastNameSortImgTag, aboutSortImgTag, eyeColorSortImgTag)
    }
}