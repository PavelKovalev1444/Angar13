function showModal(){
    document.getElementsByClassName('settings-modal')[0].style.display = 'flex';
}

function closeModal(){
    document.getElementsByClassName('settings-modal')[0].style.display = 'none';
}

window.addEventListener('click', function (e) {
	if(e.target == document.querySelector('.settings-modal')) {
        document.getElementsByClassName('settings-modal')[0].style.display = 'none';
	}	
})

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