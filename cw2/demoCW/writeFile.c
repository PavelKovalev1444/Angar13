#include "headers.h"
#include "pngStruct.h"
#include "writeFile.h"

void writeFile(char *file_name, struct Png *image){
    	int x,y;
    	FILE *fp = fopen(file_name, "wb");
    	if(!fp){
        	printf("Sorry, can't open file for writing! Check your input!\n");
		exit(EXIT_SUCCESS);
    	}
    	image->png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

    	if(!image->png_ptr){
        	printf("Sorry! Write struct creating is failed!\n");
		exit(EXIT_SUCCESS);
    	}

	image->info_ptr = png_create_info_struct(image->png_ptr);
    	if (!image->info_ptr){
        	printf("Sorry! Info struct creating is failed!\n");
		exit(EXIT_SUCCESS);
    	}

    	if (setjmp(png_jmpbuf(image->png_ptr))){
		printf("Sorry! Error during initalization image struct.\n");        
		exit(EXIT_SUCCESS);
    	}

    	png_init_io(image->png_ptr, fp);

    	if (setjmp(png_jmpbuf(image->png_ptr))){
		printf("Sorry! There happened an error during writing header.\n ");
		exit(EXIT_SUCCESS);
    	}

    	png_set_IHDR(image->png_ptr, image->info_ptr, image->width, image->height, image->bit_depth, image->color_type, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

    	png_write_info(image->png_ptr, image->info_ptr);

    	if (setjmp(png_jmpbuf(image->png_ptr))){
		printf("Sorry! There happened an error during writing bytes.\n ");
		exit(EXIT_SUCCESS);
    	}

    	png_write_image(image->png_ptr, image->row_pointers);

    	if (setjmp(png_jmpbuf(image->png_ptr))){
		printf("Sorry! There happened an error during end of writing.\n ");
		exit(EXIT_SUCCESS);
    	}

    	png_write_end(image->png_ptr, NULL);

    	for (y = 0; y < image->height; y++){
        	free(image->row_pointers[y]);
	}
    	free(image->row_pointers);

    	fclose(fp);
}
