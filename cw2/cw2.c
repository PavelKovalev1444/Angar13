#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

#define PNG_DEBUG 3
#include <png.h>

struct Png{
    int width, height;
    png_byte color_type;
    png_byte bit_depth;

    png_structp png_ptr;
    png_infop info_ptr;
    int number_of_passes;
    png_bytep *row_pointers;
};





void read_png_file(char *file_name, struct Png *image);/*reading*/


void write_png_file(char *file_name, struct Png *image);/*writing*/


void rectangle(struct Png* image, int x0, int y0, int x1, int y1, int width, int col1, int col2, int col3, int bol, int bolCol1, int bolCol2, int bolCol3);/*draw rectangle*/


void frame(struct Png* image, int choice, int width, int col1, int col2, int col3);


void rotation(struct Png* image, int x0, int y0, int x1, int y1, int angle);/*part rotation*/


void rotationSquare90Deg(struct Png* image, int x0, int y0, int x1, int y1);/*square rotation*/


void rotRec180Deg(struct Png* image, int x0, int y0, int x1, int y1);/*rectangle rotation on 180 deg*/


void rotRec90Deg(struct Png* image, int x0, int y0, int x1, int y1);/*rectangle rotation on 90 deg*/





int main(int argc, char **argv) {
    	if (argc != 3){
        	fprintf(stderr,"Usage: program_name <file_in> <file_out>\n");
		return 0;
   	}

    	struct Png image;
    	read_png_file(argv[1], &image);

    	printf("Hello, choose your function: 1 - draw a rectangle, 2 - make a pattern, 3 - image rotation.\n");
    
    	int a;
    	scanf("%d", &a);

    	int x0, y0, x1, y1, width, col1, col2, col3, bol, bolCol1, bolCol2, bolCol3, angle, choice, flag = 0;

    	switch(a){
    		case 1:
			printf("Input these args:x0, y0, x1, y1, width, col1, col2, col3, bol, bolCol1, bolCol2, bolCol3\n");
			scanf("%d %d %d %d %d %d %d %d %d %d %d %d", &x0, &y0, &x1, &y1, &width, &col1, &col2, &col3, &bol, &bolCol1, &bolCol2, &bolCol3);
			rectangle(&image, x0, y0, x1, y1, width, col1, col2, col3, bol, bolCol1, bolCol2, bolCol3);
			break;
    		case 2:
			printf("choice, width, col1, col2, col3\n");
			scanf("%d %d %d %d %d", &choice, &width, &col1, &col2, &col3);
			frame(&image, choice, width, col1, col2, col3);
			break;
		case 3:
			scanf("%d %d %d %d %d", &x0, &y0, &x1, &y1, &angle);
			rotation(&image, x0, y0, x1, y1, angle);
			break;
		default:
			printf("You've entered the wrong number. Try again!");
			break;	
    	}

    	write_png_file(argv[2], &image);

    	return 0;
}

void read_png_file(char *file_name, struct Png *image){
	int x,y;
    	char header[8];

    	FILE *fp = fopen(file_name, "rb");
    	if (!fp){
        	printf("Sorry! Can't open this file!\n");
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
        	printf("Sorry! There happened an error during tryint to initialize image structure.\n");
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
		printf("Sorry! There happened an error during reading image\n");
		exit(EXIT_SUCCESS);
    	}

    	image->row_pointers = (png_bytep *) malloc(sizeof(png_bytep) * image->height);
    	for(y = 0; y < image->height; y++){
        	image->row_pointers[y] = (png_byte *) malloc(png_get_rowbytes(image->png_ptr, image->info_ptr));
	}
    	png_read_image(image->png_ptr, image->row_pointers);

    	fclose(fp);
}

void write_png_file(char *file_name, struct Png *image){
    	int x,y;
    	FILE *fp = fopen(file_name, "wb");
    	if(!fp){
        	printf("Sorry, file can't be opened!\n");
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

void rectangle(struct Png* image, int x0, int y0, int x1, int y1, int width, int col1, int col2, int col3, int bol, int bolCol1, int bolCol2, int bolCol3){
	int pixelSize = 4;
	if (png_get_color_type(image->png_ptr, image->info_ptr) == PNG_COLOR_TYPE_RGB){
		pixelSize = 3;
	}
	int size = width/2;
	if(bol == 0){
		for(int y = y0 - size; y < y1 + size; y++){
			if(y < 0 || y > image->height - 1){
				continue;
			}
			png_bytep row = image->row_pointers[y];
			for(int x = x0 - size; x < x0 + size;x++){
				if(x >= 0 && x < image->width){
                        		png_bytep ptr = &(row[x*pixelSize]);
					ptr[0] = col1;
					ptr[1] = col2;
					ptr[2] = col3; 
                    		}
			}
			for (int x = x1 - size; x < x1 + size; x++){
                    		if(x >= 0 && x < image->width){
                        		png_bytep ptr = &(row[x*pixelSize]);
					ptr[0] = col1;
					ptr[1] = col2;
					ptr[2] = col3; 
        	            	}
        	        }

		}
		for(int y = y0-size; y <= y1+size; y++){
                	if(y < 0 || y > image->height-1){
                   		continue;
                	}
                	png_byte *row = image->row_pointers[y];
                	for(int x = x0; x <= x1; x++){
                 	   	if(x >= 0 && x < image->width){
					png_bytep ptr = &(row[x*pixelSize]);
					ptr[0] = col1;
					ptr[1] = col2;
					ptr[2] = col3;  
                    		}
                	}
            	}
            	for(int y = y1 -size; y <= y1+size; y++){
                	if(y < 0 || y > image->height-1){
                    		continue;
                	}
                	png_byte *row = image->row_pointers[y];
                	for(int x = x0; x <= x1; x++){
                    		if(x >= 0 && x < image->width){
                       			png_bytep ptr = &(row[x*pixelSize]);
					ptr[0] = col1;
					ptr[1] = col2;
					ptr[2] = col3; 
                    		}
                	}
            	}
	}if(bol == 1){
		for(int y = y0 - size; y <= y1 + size; y++){
                	if(y < 0 || y > image->height-1){
				continue;
                	}
                	png_byte *row = image->row_pointers[y];
                	for (int x = x0 - size; x <= x1 + size; x++){
                    		if(x >= 0 && x < image->width){
                        		png_bytep ptr = &(row[x*pixelSize]);
					ptr[0] = bolCol1;
					ptr[1] = bolCol2;
					ptr[2] = bolCol3; 
                    		}
                	}
            	}
            	for(int y = y0 - size; y <= y1 + size; y++){
               		if(y < 0 || y > image->height-1){
			        continue;
                	}
                	png_byte *row = image->row_pointers[y];
                	for (int x = x0 - size; x <= x0 + size; x++){
                    		if(x >= 0 && x < image->width){
                       			png_bytep ptr = &(row[x*pixelSize]);
					ptr[0] = bolCol1;
					ptr[1] = bolCol2;
					ptr[2] = bolCol3;
                    		}
                	}
                	for (int x = x1 - size; x <= x1 + size; x++){
                		if(x >= 0 && x < image->width){
                        		png_bytep ptr = &(row[x*pixelSize]);
					ptr[0] = bolCol1;
					ptr[1] = bolCol2;
					ptr[2] = bolCol3;
                    		}
                	}
            	}
            	for(int y = y0 - size; y <= y0 + size; y++){
	                if(y < 0 || y > image->height-1){
		                continue;
                	}
                	png_byte *row = image->row_pointers[y];
                	for(int x = x0; x <= x1; x++){
                    		if(x >= 0 && x < image->width){
                        		png_bytep ptr = &(row[x*pixelSize]);
					ptr[0] = bolCol1;
					ptr[1] = bolCol2;
					ptr[2] = bolCol3;
                    		}
                	}
            	}
            	for(int y = y1 -size; y <= y1 + size; y++){
	                if(y < 0 || y > image->height-1){
        	        	continue;
        		}
                	png_byte *row = image->row_pointers[y];
                	for(int x = x0; x <= x1; x++){
                    		if(x >= 0 && x < image->width){
                        		png_bytep ptr = &(row[x*pixelSize]);
					ptr[0] = bolCol1;
					ptr[1] = bolCol2;
					ptr[2] = bolCol3;
                    		}
                	}
            	}
	}else{
		return;
	}       
}

void frame(struct Png* image, int choice, int width, int col1, int col2, int col3){
	int pixelSize = 4;
	if (png_get_color_type(image->png_ptr, image->info_ptr) == PNG_COLOR_TYPE_RGB){
		pixelSize = 3;
	}
	float ler = image->height + image->width;
	switch(choice){
		case 1:
			for (int y = 0; y < image->height; y++){
				png_byte *row = image->row_pointers[y];
				for (int x = 0; x < image->width; x++){
					png_byte *ptr = &(row[x * pixelSize]);
					if (y < width || y > image->height - width || x < width || x > image->width - width){
						if ((x/10 + y/10) % 2){
							if(pixelSize ==3){
								ptr[0] = col1;
								ptr[1] = col2;
								ptr[2] = col3;
							}else{
								ptr[0] = col1;
								ptr[1] = col2;
								ptr[2] = col3;
								ptr[3]= 255;
							}
						}
					}else{
							if(pixelSize ==3){
								ptr[0] = 0;
								ptr[1] = 0;
								ptr[2] = 255;
							}else{
								ptr[0] = 0;
								ptr[1] = 0;
								ptr[2] = 255;
								ptr[3] = 255;
							}
						}
					}
			}
			break;
		case 2:/*переделать*/
                        for(int  y = 0; y < image->height; y++){
				png_bytep row = image->row_pointers[y];
				for(int x = 0; x < image->width; x++){
					png_bytep ptr = &(row[x * pixelSize]);
                                        if (y < width || y > image->height - width || x < width || x > image->width - width){
						if(y%2 == 0){
							if(pixelSize ==3){
                                                                ptr[0] = col1;
                                                                ptr[1] = col2;
                                                                ptr[2] = col3;
                                                        }else{
                                                                ptr[0] = col1;
                                                                ptr[1] = col2;
                                                                ptr[2] = col3;
                                                                ptr[3]= 255;
                                                        }

						}else{
							if(pixelSize ==3){
                                                                ptr[0] = col3;
                                                                ptr[1] = col2;
                                                                ptr[2] = col1;
                                                        }else{
                                                                ptr[0] = col3;
                                                                ptr[1] = col2;
                                                                ptr[2] = col1;
                                                                ptr[3]= 255;
                                                        }
						}
					}
				}
			}                        
                        break;
		case 3:
			for (int y = 0; y < image->height; y++){
				png_bytep row = image->row_pointers[y];
				for (int x = 0; x < image->width; x++){
					png_bytep ptr = &(row[x * pixelSize]);
					if (y < width || y > image->height - width || x < width || x > image->width - width){
						if (rand() % 2){
							if(pixelSize ==3){
								ptr[0] = col1;
								ptr[1] = col2;
								ptr[2] = col3;
							}else{
								ptr[0] = col1;
								ptr[1] = col2;
								ptr[2] = col3;
								ptr[3]= 255;
							}
						}else{	
							if(pixelSize ==3){
								ptr[0] = 180;
								ptr[1] = 130;
								ptr[2] = 150;
							}else{
								ptr[0] = 90;
								ptr[1] = 110;
								ptr[2] = 200;
								ptr[3]= 255;
							}
						}
					}
				}
			}
			break;
		default:
			return;	
	}	
}

void rotation(struct Png* image, int x0, int y0, int x1, int y1, int angle){
	int tmp = 0, flag = 0;
	if( ( (x0 < 0) && (y0 < 0) && (x1 < 0) && (y1 < 0) ) || ( (x0 == x1) && (y0 == y1) ) ){
		return;
	}
	if((angle != 90) && (angle != 180) && (angle != 270)){
		return;
	}
	
	if(x0 < 0){
		x1 = 0;
	}
	if(x0 > image->height - 1){
		x0 = image->height - 1;
	}
	if(x1 < 0){
		x1 = 0;
	}
	if(x1 > image->height - 1){
		x1 = image->height - 1;
	}
	if(y0 < 0 ){
		y0 = 0;
	}
	if(y0 > image->height - 1){
		y0 = image->height - 1;
	}
	if(y1 > image->height - 1){
		y1 = image->height - 1;
	}
	if(y1 < 0){
		y1 = 0;
	}
	if(x0 > x1){
		tmp = x0;
		x0 = x1;
		x1 = tmp;
	}
	if(y0 > y1){
		tmp = y0;
		y0 = y1;
		y1 = tmp;
	}
	int dx = x1 - x0;
	int dy = y1 - y0;
	if(dx == dy){
		for(int i = 0; i < angle/90; i++){
			rotationSquare90Deg(image, x0, y0, x1, y1);
		}
	}else{
		if(angle == 90){
			rotRec90Deg(image, x0, y0, x1, y1);
		}else if(angle == 180){
			rotRec180Deg(image, x0, y0, x1, y1);
		}else if(angle == 270){
			rotRec180Deg(image, x0, y0, x1, y1);
			rotRec90Deg(image, x0, y0, x1, y1);
		}
	}

}

void rotationSquare90Deg(struct Png* image, int x0, int y0, int x1, int y1){
	int pixelSize = 3;
	if (png_get_color_type(image->png_ptr, image->info_ptr) == PNG_COLOR_TYPE_RGB){
        	pixelSize = 3;
	}
        if (png_get_color_type(image->png_ptr, image->info_ptr) == PNG_COLOR_TYPE_RGBA){
		pixelSize = 4;
        }

	int rows = y1 - y0;
       	int cols = x1 - x0;
	
	png_bytep* matrix = malloc(rows*sizeof(png_bytep));

	for(int i = 0; i < rows; i++){
		matrix[i] = malloc(pixelSize*cols*sizeof(png_byte));
	}

	for(int y = 0; y < rows; y++){
	
		png_bytep row = image->row_pointers[y0 + y];
		for(int x = 0; x < cols; x++){
	
			png_bytep ptr = &(row[x0 + pixelSize*x]);
			
			png_bytep mrow = matrix[rows - 1 - x];
			png_bytep mptr = &(mrow[pixelSize*y]);
	
			if(pixelSize == 3){
				mptr[0] = ptr[0];
				mptr[1] = ptr[1];
				mptr[2] = ptr[2];
			}
		
			if(pixelSize == 4){
				mptr[0] = ptr[0];
                                mptr[1] = ptr[1];
                                mptr[2] = ptr[2];
                                mptr[3] = ptr[3];
			}

		}
	}

	for(int y = 0; y < rows; y++){
		
		png_bytep row = image->row_pointers[y0 + y];
		png_bytep mrow = matrix[y];
		
		for(int x = 0; x < cols; x++){
		
			png_bytep ptr = &(row[x0 + pixelSize*x]);
			png_bytep mptr = &(mrow[pixelSize*x]);
			
			if(pixelSize == 3){
				ptr[0] = mptr[0];
				ptr[1] = mptr[1];
				ptr[2] = mptr[2];
			}

			if(pixelSize == 4){
				ptr[0] = mptr[0];
                                ptr[1] = mptr[1];
                                ptr[2] = mptr[2];
                                ptr[3] = mptr[3];
			}

		}
	}
	
	for(int i = 0; i < rows; i++){
		free(matrix[i]);	
	}	
	free(matrix);
	
}	

void rotRec180Deg(struct Png* image, int x0, int y0, int x1, int y1){
	int pixelSize = 3;
	int epsilon = 0;
        if (png_get_color_type(image->png_ptr, image->info_ptr) == PNG_COLOR_TYPE_RGB){
                pixelSize = 3;
		epsilon = x0%3;
		x0 = x0 - epsilon;
		epsilon = x1%3;
                x1 = x1 - epsilon;
        }
        if (png_get_color_type(image->png_ptr, image->info_ptr) == PNG_COLOR_TYPE_RGBA){
                pixelSize = 4;
        }

        int rows = y1 - y0;
        int cols = x1 - x0;

        png_bytep* matrix = malloc(rows*sizeof(png_bytep));

        for(int i = 0; i < rows; i++){
                matrix[i] = malloc(pixelSize*cols*sizeof(png_byte));
        }

	for(int y = 0; y < rows; y++){
		png_bytep row = image->row_pointers[y0 + y];
		for(int x = 0; x < cols; x++){
			png_bytep ptr = &(row[pixelSize*(x1 - x)]);

			png_bytep mrow = matrix[rows - 1 - y];
			png_bytep mptr = &(mrow[pixelSize*x]);
			
			if(pixelSize == 3){
                                mptr[0] = ptr[0];
                                mptr[1] = ptr[1];
                                mptr[2] = ptr[2];
                        }
                        if(pixelSize == 4){
                                mptr[0] = ptr[0];
                                mptr[1] = ptr[1];
                                mptr[2] = ptr[2];
                                mptr[3] = ptr[3];
                        }
		}
	}
	for(int y = 0; y < rows; y++){
                png_bytep row = image->row_pointers[y0 + y];
                png_bytep mrow = matrix[y];
                for(int x = 0; x < cols; x++){
                        png_bytep ptr = &(row[x0 + pixelSize*x]);
                        png_bytep mptr = &(mrow[pixelSize*x]);
                        if(pixelSize == 3){
                                ptr[0] = mptr[0];
                                ptr[1] = mptr[1];
                                ptr[2] = mptr[2];
                        }
                        if(pixelSize == 4){
                                ptr[0] = mptr[0];
                                ptr[1] = mptr[1];
                                ptr[2] = mptr[2];
                                ptr[3] = mptr[3];
                        }
                }
        }

        for(int i = 0; i < rows; i++){
                free(matrix[i]);
        }
        free(matrix);
}

void rotRec90Deg(struct Png* image, int x0, int y0, int x1, int y1){
	int xc = (x1 - x0)/2 + x0;
	int yc = (y1 - y0)/2 + y0;
	int dx = x1 - x0;
	int dy = y1 - y0;
		
	int pixelSize = 4;

	if (png_get_color_type(image->png_ptr, image->info_ptr) == PNG_COLOR_TYPE_RGB){
                pixelSize = 3;
     	}

	png_bytep* matrix = malloc(dx*sizeof(png_bytep));
 
 	for(int i = 0; i < dx; i++){
                matrix[i] = malloc(pixelSize*dy*sizeof(png_byte));
        }		
	for(int y = 0; y < dy; y++){
		png_bytep row = image->row_pointers[y0 + y];
		for(int x = 0; x < dx; x++){
			png_bytep ptr = &(row[x0*pixelSize + pixelSize*x]);
	
			png_bytep mrow = matrix[dx - 1 - x];
			png_bytep mptr = &(mrow[pixelSize*y]);
	
			if(pixelSize == 3){
				mptr[0] = ptr[0];
				mptr[1] = ptr[1];
				mptr[2] = ptr[2];
			}else if(pixelSize == 4){
				mptr[0] = ptr[0];
				mptr[1] = ptr[1];
				mptr[2] = ptr[2];
				mptr[3] = ptr[3];
			}
		}
	}
	/*проверка выходов за границу*/
	int xn0 = 0, xn1 = 0, yn0 = 0, yn1 = 0, deltaYU = 0, deltaXL = 0, deltaYD = 0, deltaXR = 0, del = 0;
        del = dx - dy;
	if(del%2 == 1){
		del = del/2;
		del = del - 1;
	}else{
		del = del/2;
	}	
	if(dx > dy){ 
		xn0 = x0 + del;
        	xn1 = x1 - del;
       		yn0 = y0 - del;
	        yn1 = y1 + del;
	
		deltaYU = 0 - yn0;
		deltaYD = image->height - 1 - yn1;
	}
	del = dy - dx;
	if(del%2 == 1){
                del = del/2;
                del = del - 1;
        }else{
                del = del/2;
        }
	if(dx < dy){
		xn0 = x0 - del;
		xn1 = x1 + del;
		yn0 = y0 + del;
		yn1 = y1 - del;

		deltaXL = 0 - xn0;
		deltaXR = image->width - 1 - xn1;
	}
	/*deltaYU*/
	if(yn0 < 0){
  	        yn0 = 0;
	}
	if(deltaYU < 0){
		deltaYU = 0;
	}
	/*deltaYD*/
	if(yn1 >= image->height){
		yn1 = image->height - 1;
	}
	if(deltaYD > 0){
		deltaYD = 0;
	}
	/*deltaXL*/
	if(xn0 < 0){
		xn0 = 0;
	}
	if(deltaXL < 0){
		deltaXL = 0;
	}
	/*deltaXR*/
	if(xn1 >= image->width){
		xn1 = image->width - 1;
	}
	if(deltaXR > 0){
		deltaXR = 0;
	}
	/*печатаем в картину*/	
	for(int y = 0; y < dx - deltaYU + deltaYD; y++){

        	png_bytep row = image->row_pointers[yn0 + y];
                for(int x = 0; x < dy - deltaXL + deltaXR; x++){
        	        png_bytep ptr = &(row[xn0*pixelSize + pixelSize*x]);

                        png_bytep mrow = matrix[y + deltaYU];
                        png_bytep mptr = &(mrow[pixelSize*x + deltaXL*pixelSize]);

                        if(pixelSize == 3){
                                ptr[0] = mptr[0];
                                ptr[1] = mptr[1];
                                ptr[2] = mptr[2];
                        }else if(pixelSize == 4){
                                ptr[0] = mptr[0];
                                ptr[1] = mptr[1];
                                ptr[2] = mptr[2];
                                ptr[3] = mptr[3];
                        }
                }
        }
	/*корректировка обрезков*/	
	if(dx > dy){
		for(int y = 0; y < dy; y++){
			png_bytep row = image->row_pointers[y0 + y];
			for(int x = 0; x < (xn0 - x0); x++){
				png_bytep ptr = &(row[x0*pixelSize + pixelSize*x]);
				if(pixelSize == 3){
	                                ptr[0] = 255;
	                                ptr[1] = 255;
	                                ptr[2] = 255;
	                        }else if(pixelSize == 4){
	                                ptr[3] = 0;
	                        }
	
			}
		}
			
		for(int y = 0; y < dy; y++){
        	        png_bytep row = image->row_pointers[y0 + y];
	                for(int x = 0; x < (x1 - xn1); x++){
        	                png_bytep ptr = &(row[xn1*pixelSize + pixelSize*x]);
	                        if(pixelSize == 3){
                	                ptr[0] = 255;
        	                        ptr[1] = 255;
	                                ptr[2] = 255;
                        	}else if(pixelSize == 4){
                                	ptr[3] = 0;
                        	}

               		}
        	}
	}else{
                for(int y = 0; y < (yn0-y0); y++){
                        png_bytep row = image->row_pointers[y0 + y];
                        for(int x = 0; x < dx; x++){
                                png_bytep ptr = &(row[x0*pixelSize + pixelSize*x]);
                                if(pixelSize == 3){
                                        ptr[0] = 255;
                                        ptr[1] = 255;
                                        ptr[2] = 255;
                                }else if(pixelSize == 4){
                                        ptr[3] = 0;
                                }

                        }
                }

                for(int y = 0; y < (y1 - yn1); y++){
                        png_bytep row = image->row_pointers[yn1 + y];
                        for(int x = 0; x < dx; x++){
                                png_bytep ptr = &(row[x0*pixelSize + pixelSize*x]);
                                if(pixelSize == 3){
                                        ptr[0] = 255;
                                        ptr[1] = 255;
                                        ptr[2] = 255;
                                }else if(pixelSize == 4){
                                        ptr[3] = 0;
                                }

                        }
                }


	}
	
	for(int i = 0; i < dx; i++){
              free(matrix[i]);
        }
        free(matrix);
}
