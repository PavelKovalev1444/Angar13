/*
@brief Функция показа модального окна с выбором столбцов для отображения.
@detailed Данная функция устанавливает свойство display в значение flex у модального окна, предоставляющего выбор столбцов для отображения. 
Также функция создает слушателя события нажатия кнопки мыши для глобального объекта window, 
чтобы можно было скрывать модальное окно при клике на область вне окна.
*/
function showModal(){
    window.addEventListener('click',  (e) => {
        if(e.target == document.querySelector('.settings-modal')) {
            document.getElementsByClassName('settings-modal')[0].style.display = 'none';
        }	
    })
    document.getElementsByClassName('settings-modal')[0].style.display = 'flex';
}

/*
@brief Функция закрытия модального окна с выбором столбцов для отображения.
@detailed Данная функция устанавливает свойство display в значение none у модального окна, предоставляющего выбор столбцов для отображения. Функция также убирает 
слушателя события нажатия кнопки мыши для глобального объекта window.
*/
function closeModal(){
    window.removeEventListener('click',  (e) => {
        if(e.target == document.querySelector('.settings-modal')) {
            document.getElementsByClassName('settings-modal')[0].style.display = 'none';
        }	
    })
    document.getElementsByClassName('settings-modal')[0].style.display = 'none';
}

/*
@brief Функция обработки нажатия на input типа checkbox.
@detailed Данная функция обрабатывает нажатие на input типа checkbox, который отвечает за отображение/сокрытие столбца таблицы. Т.к. всего возможных значений 2 - показывать или не показывать, 
то при каждом нажатии на input, соответствующий ему флажок меняет свое значение с true на false или наоборот. После того, как нажатие на input обработано, запускается отрисовка таблицы.
@param checkBoxName имя input'а типа checkbox, который был нажат.
*/
function columnVisibilityHandler(checkboxName){
    if(checkboxName === 'firstName'){
        firstNameCol = !firstNameCol
    }
    if(checkboxName === 'lastName'){
        lastNameCol = !lastNameCol
    }
    if(checkboxName === 'about'){
        aboutCol = !aboutCol
    }
    if(checkboxName === 'eyeColor'){
        eyeColorCol = !eyeColorCol
    }
    createTable(firstNameSortImgTag, lastNameSortImgTag, aboutSortImgTag, eyeColorSortImgTag)
}