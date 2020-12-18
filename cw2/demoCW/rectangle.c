#include "headers.h"
#include "pngStruct.h"
#include "rectangle.h"


void rectangle(struct Png* image, int x0, int y0, int x1, int y1, int width, char* col1, int bol, char* col2){	
	int r1, g1, b1, r2, g2, b2;
	if(col1){
		if(strcmp(col1, "red") == 0){
			r1 = 255;
			g1 = 0;
			b1 = 0;
		}else if(strcmp(col1, "green") == 0){
                        r1 = 0;
                        g1 = 255;
			b1 = 0;
                }else if(strcmp(col1, "blue") == 0){
                        r1 = 0;
                        g1 = 0;
                        b1 = 200;
                }else if(strcmp(col1, "yellow") == 0){
                        r1 = 255;
                        g1 = 255;
                        b1 = 0;
                }else if(strcmp(col1, "orange") == 0){
			r1 = 255;
			g1 = 165;
			b1 = 0;
		}else if(strcmp(col1, "purple") == 0){
                        r1 = 128;
                        g1 = 128;
                        b1 = 0;
                }else if(strcmp(col1, "white") == 0){
                        r1 = 255;
                        g1 = 255;
                        b1 = 255;
                }else if(strcmp(col1, "black") == 0){
                        r1 = 0;
                        g1 = 0;
                        b1 = 0;
                }else{
			printf("You've input the wrong colorRe argument!\n");
			for (int y = 0; y < image->height; y++){
               			free(image->row_pointers[y]);
        		}
        		free(image->row_pointers);
			exit(EXIT_SUCCESS);
		}
	}else{
		for (int y = 0; y < image->height; y++){
               		free(image->row_pointers[y]);
        	}
        	free(image->row_pointers);
		printf("Sorry, you didn't enter color of rectangle's border!\n");
		exit(EXIT_SUCCESS);
	}
	if(bol == 1){
		if(col2){
	                if(strcmp(col2, "red") == 0){
				r2 = 255;
				g2 = 0;
				b2 = 0;
			}else if(strcmp(col2, "green") == 0){
	                        r2 = 0;
                      		g2 = 255;
				b2 = 0;
        	        }else if(strcmp(col2, "blue") == 0){
        	                r2 = 0;
        	                g2 = 0;
        	                b2 = 200;
        	        }else if(strcmp(col2, "yellow") == 0){
        	                r2 = 255;
        	                g2 = 255;
        	                b2 = 0;
        	        }else if(strcmp(col2, "orange") == 0){
				r2 = 255;
				g2 = 165;
				b2 = 0;
			}else if(strcmp(col2, "purple") == 0){
        	                r2 = 128;
        	                g2 = 128;
        	                b2 = 0;
        	        }else if(strcmp(col2, "white") == 0){
        	                r2 = 255;
        	                g2 = 255;
        	                b2 = 255;
        	        }else if(strcmp(col2, "black") == 0){
        	                r2 = 0;
        	                g2 = 0;
        	                b2 = 0;
        	        }else{
				printf("You've input the wrong fillColor argument!\n");
				for (int y = 0; y < image->height; y++){
               				free(image->row_pointers[y]);
        			}
        			free(image->row_pointers);
				exit(EXIT_SUCCESS);
			}
	        }else{
	                for (int y = 0; y < image->height; y++){
	                        free(image->row_pointers[y]);
	                }
	                free(image->row_pointers);
	                printf("Sorry, you didn't enter color of rectangle's fill!\n");
	                exit(EXIT_SUCCESS);
	        }
	}	
	int pixelSize = 3;
	if (png_get_color_type(image->png_ptr, image->info_ptr) == PNG_COLOR_TYPE_RGBA){
		pixelSize = 4;
	}
	if(bol == 0){
		/*рисование вертикальных сторон*/
		for(int y = y0 - width/2; y < y1 + width/2; y++){
			if(y < 0 || y > image->height - 1){
				continue;
			}
			png_bytep row = image->row_pointers[y];
			for(int x = x0 - width/2; x < x0 + width/2;x++){
				if(x >= 0 && x < image->width){
                        		png_bytep ptr = &(row[x*pixelSize]);
					ptr[0] = r1;
					ptr[1] = g1;
					ptr[2] = b1; 
                    		}
			}
			for (int x = x1 - width/2; x < x1 + width/2; x++){
                    		if(x >= 0 && x < image->width){
                        		png_bytep ptr = &(row[x*pixelSize]);
					ptr[0] = r1;
                                        ptr[1] = g1;
                                        ptr[2] = b1; 
        	            	}
        	        }

		}
		/*рисование горизонтальных сторон*/
		for(int y = y0 - width/2; y <= y0 + width/2; y++){
                	if(y < 0 || y > image->height-1){
                   		continue;
                	}
                	png_byte *row = image->row_pointers[y];
                	for(int x = x0; x <= x1; x++){
                 	   	if(x >= 0 && x < image->width){
					png_bytep ptr = &(row[x*pixelSize]);
					ptr[0] = r1;
                                        ptr[1] = g1;
                                        ptr[2] = b1;  
                    		}
                	}
            	}
            	for(int y = y1 -width/2; y <= y1 + width/2; y++){
                	if(y < 0 || y > image->height-1){
                    		continue;
                	}
                	png_byte *row = image->row_pointers[y];
                	for(int x = x0; x <= x1; x++){
                    		if(x >= 0 && x < image->width){
                       			png_bytep ptr = &(row[x*pixelSize]);
					ptr[0] = r1;
                                        ptr[1] = g1;
                                        ptr[2] = b1; 
                    		}
                	}
            	}
		return;
	}
	if(bol == 1){
		/*заливка*/
		for(int y = y0 - width/2; y <= y1 + width/2; y++){
                	if(y < 0 || y > image->height-1){
				continue;
                	}
                	png_byte *row = image->row_pointers[y];
                	for (int x = x0 - width/2; x <= x1 + width/2; x++){
                    		if(x >= 0 && x < image->width){
                        		png_bytep ptr = &(row[x*pixelSize]);
					ptr[0] = r2;
                                        ptr[1] = g2;
                                        ptr[2] = b2; 
                    		}
                	}
            	}
		/*рисование вертикальных границ*/
            	for(int y = y0 - width/2; y <= y1 + width/2; y++){
               		if(y < 0 || y > image->height-1){
			        continue;
                	}
                	png_byte *row = image->row_pointers[y];
                	for (int x = x0 - width/2; x <= x0 + width/2; x++){
                    		if(x >= 0 && x < image->width){
                       			png_bytep ptr = &(row[x*pixelSize]);
					ptr[0] = r1;
                                        ptr[1] = g1;
                                        ptr[2] = b1;
                    		}
                	}
                	for (int x = x1 - width/2; x <= x1 + width/2; x++){
                		if(x >= 0 && x < image->width){
                        		png_bytep ptr = &(row[x*pixelSize]);
					ptr[0] = r1;
                                        ptr[1] = g1;
                                        ptr[2] = b1;
                    		}
                	}
            	}/*рисование горизонтальных границ*/
            	for(int y = y0 - width/2; y <= y0 + width/2; y++){
	                if(y < 0 || y > image->height-1){
		                continue;
                	}
                	png_byte *row = image->row_pointers[y];
                	for(int x = x0; x <= x1; x++){
                    		if(x >= 0 && x < image->width){
                        		png_bytep ptr = &(row[x*pixelSize]);
					ptr[0] = r1;
                                        ptr[1] = g1;
                                        ptr[2] = b1;
                    		}
                	}
            	}
            	for(int y = y1 -width/2; y <= y1 + width/2; y++){
	                if(y < 0 || y > image->height-1){
        	        	continue;
        		}
                	png_byte *row = image->row_pointers[y];
                	for(int x = x0; x <= x1; x++){
                    		if(x >= 0 && x < image->width){
                        		png_bytep ptr = &(row[x*pixelSize]);
					ptr[0] = r1;
                                        ptr[1] = g1;
                                        ptr[2] = b1;
                    		}
                	}
            	}
	}else{
		for (int y = 0; y < image->height; y++){
        		free(image->row_pointers[y]);
		}
    		free(image->row_pointers);
		printf("Sorry, you didn't enter the fill argument! It can be 1 or 0. Chech the manual!\n");
		exit(EXIT_SUCCESS);
	}       
}
