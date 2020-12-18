#include "headers.h"
#include "pngStruct.h"
#include "readFile.h"

void readFile(char *file_name, struct Png *image){
	int x,y;
    	char header[8];

    	FILE *fp = fopen(file_name, "rb");
    	if (!fp){
        	printf("Sorry! Can't open this file for reading!\n");
        	exit(EXIT_SUCCESS);
    	}

    	fread(header, 1, 8, fp);
    	if(png_sig_cmp(header, 0, 8)){
    		printf("Sorry, you have incorrect file!\n");
	        exit(EXIT_SUCCESS); 
    	}

    	image->png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

    	if(!image->png_ptr){
        	printf("Sorry, read struct creating failed!\n");
		exit(EXIT_SUCCESS);
    	}

    	image->info_ptr = png_create_info_struct(image->png_ptr);
    	if(!image->info_ptr){
        	printf("Sorry, info struct creating failed!\n");
		exit(EXIT_SUCCESS);
    	}

    	if(setjmp(png_jmpbuf(image->png_ptr))){
        	printf("Sorry! There happened an error during trying to initialize image structure.\n");
		exit(EXIT_SUCCESS);
    	}

    	png_init_io(image->png_ptr, fp);
    	png_set_sig_bytes(image->png_ptr, 8);

    	png_read_info(image->png_ptr, image->info_ptr);

    	image->width = png_get_image_width(image->png_ptr, image->info_ptr);
    	image->height = png_get_image_height(image->png_ptr, image->info_ptr);
    	image->color_type = png_get_color_type(image->png_ptr, image->info_ptr);
    	image->bit_depth = png_get_bit_depth(image->png_ptr, image->info_ptr);

    	image->number_of_passes = png_set_interlace_handling(image->png_ptr);
    	png_read_update_info(image->png_ptr, image->info_ptr);

    	if (setjmp(png_jmpbuf(image->png_ptr))){
		printf("Sorry! There happened an error during reading image.\n");
		exit(EXIT_SUCCESS);
    	}

    	image->row_pointers = (png_bytep *) malloc(sizeof(png_bytep) * image->height);
    	for(y = 0; y < image->height; y++){
        	image->row_pointers[y] = (png_byte *) malloc(png_get_rowbytes(image->png_ptr, image->info_ptr));
	}
    	png_read_image(image->png_ptr, image->row_pointers);

    	fclose(fp);
}
