const gulp = require('gulp');
const less = require('gulp-less');
const babel = require('gulp-babel');
const del = require('del');


gulp.task('delete_js', function(){
    return del('./public/js/*.js');
});

gulp.task('compile_js', function(){
    return gulp.src('./public/babel_js/*.js')
        .pipe(babel())
        .pipe(gulp.dest('./public/js/'))
});

gulp.task('delete_css', function(){
    return del('./public/stylesheets/*.css');
});

gulp.task('compile_less', function(){
    return gulp.src('./public/less/*.less')
        .pipe(less())
        .pipe(gulp.dest('./public/stylesheets/'))
});

gulp.task("default",gulp.parallel((gulp.series('delete_js', 'compile_js')),(gulp.series('delete_css', 'compile_less'))));