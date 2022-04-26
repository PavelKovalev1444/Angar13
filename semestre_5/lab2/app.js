let express = require("express");
let server = express();
server.use('/public', express.static('public'));
server.engine('pug', require('pug').__express);
server.set("view engine", "pug");
server.set("views",`./public/pug_files`);
server.use(express.json());
server.use(express.urlencoded())

let books_from_lib_json = require('./public/json/library');
let index_of_changing = 0;

server.get("/", (req, res) => {
    res.render("index",{
        value: 1
    });
});

server.get("/list", (req, res) => {
    res.render("list",{title: 'library', books: books_from_lib_json});
});

server.get("/deleteBook", (req, res) => {
    res.render("deleteBook",{title: 'library', books: books_from_lib_json});
});
/*change,lend,get book*/
server.post("/chg/:num", (req, res,next) => {
    let id = req.params.num;
    for(let i = 0; i < books_from_lib_json.length; i++){
        if(books_from_lib_json[i].id.toString() === id){
            index_of_changing = i;
        }
    }
    res.render("changeBook",{title: 'library', book: books_from_lib_json[index_of_changing]});
    //res.redirect('/list');
});

server.post("/lnd", (req, res,next) => {
    let data = req.body;
    for(let i = 0; i < books_from_lib_json.length; i++){
        if(books_from_lib_json[i].name === data.name_of_book && books_from_lib_json[i].author === data.name_of_author && books_from_lib_json[i].date_of_writing === data.date_of_writing){
            index_of_changing = i;
        }
    }
    books_from_lib_json[index_of_changing].person = data.name_of_reader;
    books_from_lib_json[index_of_changing].date_of_lending = data.date_of_lending;
    books_from_lib_json[index_of_changing].date_of_return = data.date_of_return;
    books_from_lib_json[index_of_changing].in_library = 'Нет в наличии';
    res.redirect('/list');
});

server.post("/take/:num", (req, res,next) => {
    let id=req.params.num;
    for(let i = 0; i < books_from_lib_json.length; i++){
        if(books_from_lib_json[i].id.toString() === id){
            index_of_changing = i;
        }
    }
    books_from_lib_json[index_of_changing].in_library = 'Есть в наличии';
    books_from_lib_json[index_of_changing].person = '-';
    books_from_lib_json[index_of_changing].date_of_lending = '-';
    books_from_lib_json[index_of_changing].date_of_return = '-';
    res.redirect('/list');
});

server.post('/addBook', (req, res)=>{
    let addForm = req.body;
    addForm['id'] = books_from_lib_json[books_from_lib_json.length-1].id + 1;
    addForm['person'] = '-';
    addForm['date_of_lending'] = '-';
    addForm['date_of_return'] = '-';
    addForm['in_library'] = 'Есть в наличии';
    books_from_lib_json.push(addForm);
    //res.render("list", {title: 'library', books: books_from_lib_json});
    res.redirect('/list');
});

server.post('/delBook', (req, res)=>{
    let delForm = req.body;
    for(let i = 0; i < books_from_lib_json.length; i++){
        if(books_from_lib_json[i].name === delForm.name.toString() && books_from_lib_json[i].author === delForm.author.toString()){
            books_from_lib_json.splice(i,1);
        }
    }
    //res.render("list", {title: 'library', books: books_from_lib_json});
    res.redirect('/list');
});

server.post('/changingInfo', (req, res)=>{
    let changeForm = req.body;
    if(changeForm.hasOwnProperty('name')) {
        if (changeForm.name !== '') {
            books_from_lib_json[index_of_changing].name = changeForm.name;
        }
    }
    if(changeForm.hasOwnProperty('author')) {
        if (changeForm.author !== '') {
            books_from_lib_json[index_of_changing].author = changeForm.author;
        }
    }
    if(changeForm.hasOwnProperty('date')) {
        if (changeForm.date !== '') {
            books_from_lib_json[index_of_changing].date_of_writing = changeForm.date;
        }
    }
    //res.render("list", {title: 'library', books: books_from_lib_json});
    res.redirect('/list');
});

/*ajax request*/
server.get('/filter/:num', (req, res, next)=>{
    let id = req.params.num;
    if(id === 'in_library'){
        let book_in_library_arr = [];
        for(let i = 0; i < books_from_lib_json.length; i++){
            if(books_from_lib_json[i].in_library !== 'Есть в наличии'){
                book_in_library_arr.push(books_from_lib_json[i])
            }
        }
        res.end(JSON.stringify(book_in_library_arr));
    }else if(id === 'without_filter'){
        res.end(JSON.stringify(books_from_lib_json));
    }else if(id === 'date_return'){
        let book_in_library_arr = [];
        let dateNow = new Date();
        for(let i = 0; i < books_from_lib_json.length; i++){
            if(books_from_lib_json[i].date_of_return !== '-') {
                //console.log(books_from_lib_json[i].date_of_return);
                let tmpDate = new Date(books_from_lib_json[i].date_of_return);
                //console.log("tmpDate.getTime() = ", tmpDate.getTime(), "dateNow.getTime() = ", dateNow.getTime());
                if (tmpDate.getTime() - dateNow.getTime() >= 0) {
                    book_in_library_arr.push(books_from_lib_json[i]);
                }
            }else{
                book_in_library_arr.push(books_from_lib_json[i]);
            }
        }
        res.end(JSON.stringify(book_in_library_arr));
    }
    next();
});

server.get("*", (req, res)=>{
    res.status(404);
    res.end("Page not found");
});

server.listen(3000);