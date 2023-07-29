#include "headers.h"
#include "pngStruct.h"
#include "rotation.h"

void rotation(struct Png* image, int x0, int y0, int x1, int y1, int angle){
	if( ( (x0 < 0) && (y0 < 0) && (x1 < 0) && (y1 < 0) ) || ( (x0 == x1) && (y0 == y1) ) || ( (x0 > image->width - 1) && (x1 > image->width - 1) && (y0 > image->height -1) && (y1 > image->height -1) ) ||( (x0 == x1) && (y0 == y1) ) ){
                for (int y = 0; y < image->height; y++){
        		free(image->row_pointers[y]);
		}
    		free(image->row_pointers);		
		printf("Check your coordinates!\n");		
		exit(EXIT_SUCCESS);
        }
	if(angle == 0 || angle == 360){
		for (int y = 0; y < image->height; y++){
        		free(image->row_pointers[y]);
		}
    		free(image->row_pointers);		
		printf("There is no need to rotate image's part for this angle.\n");		
		exit(EXIT_SUCCESS);
	}
	if(angle%90 != 0){
		for (int y = 0; y < image->height; y++){
        		free(image->row_pointers[y]);
		}
 		free(image->row_pointers);
		printf("Check your angle! It must be a multiple of 90 degrees.\n");		
		exit(EXIT_SUCCESS);
	}
	if((x0 > x1) || (y0 > y1)){
		for (int y = 0; y < image->height; y++){
        		free(image->row_pointers[y]);
		}
 		free(image->row_pointers);	
                printf("Check your coordinates!\n");
                exit(EXIT_SUCCESS);
        }
        if(x0 < 0){
                x0 = 0;
        }
        if(y0 < 0){
                y0 = 0;
        }
        if(x1 > image->width - 1){
                x1 = image->width - 1;
        }
        if(y1 > image->height - 1){
                y1 = image->height - 1;
        }
	int dx = x1 - x0;
	int dy = y1 - y0;
	while(angle > 360){
		angle = angle - 360;
	}
	if(dx == dy){
		for(int i = 0; i < angle/90; i++){
			rotationSquare(image, x0, y0, x1, y1);
		}
	}else{
		if(angle == 90){
			rotationRectangle90(image, x0, y0, x1, y1);
		}else if(angle == 180){
			rotationRectangle180(image, x0, y0, x1, y1);
		}else if(angle == 270){
			rotationRectangle180(image, x0, y0, x1, y1);
			rotationRectangle90(image, x0, y0, x1, y1);
		}
	}
}

void rotationSquare(struct Png* image, int x0, int y0, int x1, int y1){
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
	
			png_bytep ptr = &(row[pixelSize*x0 + pixelSize*x]);
			
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
		
			png_bytep ptr = &(row[x0*pixelSize + pixelSize*x]);
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

void rotationRectangle180(struct Png* image, int x0, int y0, int x1, int y1){
	int pixelSize = 3;

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
                        png_bytep ptr = &(row[x0*pixelSize + pixelSize*x]);
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

void rotationRectangle90(struct Png* image, int x0, int y0, int x1, int y1){
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
	if(dx > dy){ 
		del = dx - dy;
		if(del%2 == 1){
			del = del/2;
			del = del - 1;
		}else{
			del = del/2;
		}
		xn0 = x0 + del;
        	xn1 = x1 - del;
       		yn0 = y0 - del;
	        yn1 = y1 + del;
	
		deltaYU = 0 - yn0;
		deltaYD = image->height - 1 - yn1;
	}
	if(dx < dy){
		del = dy - dx;
		if(del%2 == 1){
           		del = del/2;
        	        del = del - 1;
       		}else{
        	        del = del/2;
        	}
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
