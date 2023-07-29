#include "headers.h"
#include "pngStruct.h"
#include "frame.h"

void frame(struct Png* image, int choice, int width, char* col){
	int r1, g1, b1;
	if(col){
		if(strcmp(col, "red") == 0){
			r1 = 255;
			g1 = 0;
			b1 = 0;
		}else if(strcmp(col, "green") == 0){
                        r1 = 0;
                        g1 = 255;
                        b1 = 0;
                }else if(strcmp(col, "blue") == 0){
                        r1 = 0;
                        g1 = 0;
                        b1 = 255;
                }else if(strcmp(col, "yellow") == 0){
                        r1 = 255;
                        g1 = 255;
                        b1 = 0;
                }else if(strcmp(col, "orange") == 0){
			r1 = 255;
			g1 = 165;
			b1 = 0;
		}else if(strcmp(col, "purple") == 0){
                        r1 = 128;
                        g1 = 0;
                        b1 = 128;
                }else if(strcmp(col, "white") == 0){
                        r1 = 255;
                        g1 = 255;
                        b1 = 255;
                }else if(strcmp(col, "black") == 0){
                        r1 = 0;
                        g1 = 0;
                        b1 = 0;
                }else{
			for (int y = 0; y < image->height; y++){
               			free(image->row_pointers[y]);
        		}
        		free(image->row_pointers);
			printf("You've input the wrong colorFr argument!\n");
			exit(EXIT_SUCCESS);
		}
	}else{
		for (int y = 0; y < image->height; y++){
               		free(image->row_pointers[y]);
        	}
        	free(image->row_pointers);
		printf("Sorry, you didn't enter color of frame!\n");
		exit(EXIT_SUCCESS);
	}	
	int pixelSize = 4;
	if (png_get_color_type(image->png_ptr, image->info_ptr) == PNG_COLOR_TYPE_RGB){
		pixelSize = 3;
	}
	switch(choice){
		case 1:
			for (int y = 0; y < image->height; y++){
				png_byte *row = image->row_pointers[y];
				for (int x = 0; x < image->width; x++){
					png_byte *ptr = &(row[x * pixelSize]);
					if (y < width || y > image->height - width || x < width || x > image->width - width){
						if ((x/10 + y/10) % 2){
							if(pixelSize ==3){
								ptr[0] = r1;
                                       				ptr[1] = g1;
                                        			ptr[2] = b1;
							}else{
								ptr[0] = r1;
                                       				ptr[1] = g1;
                                        			ptr[2] = b1;
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
		case 2:
                        for(int  y = 0; y < image->height; y++){
				png_bytep row = image->row_pointers[y];
				for(int x = 0; x < image->width; x++){
					png_bytep ptr = &(row[x * pixelSize]);
                                        if (y < width || y > image->height - width || x < width || x > image->width - width){
						if(y%2 == 0){
							if(pixelSize ==3){
                                                                ptr[0] = r1;
                                       				ptr[1] = g1;
                                        			ptr[2] = b1;
                                                        }else{
                                                                ptr[0] = r1;
                                       				ptr[1] = g1;
                                        			ptr[2] = b1;
                                                                ptr[3]= 255;
                                                        }

						}else{
							if(pixelSize ==3){
                                                                ptr[0] = ~(r1);
                                       				ptr[1] = ~(g1);
                                        			ptr[2] = ~(b1);
                                                        }else{
                                                                ptr[0] = ~(r1);
                                       				ptr[1] = ~(g1);
                                        			ptr[2] = ~(b1);
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
						if (rand() % 3){
							if(pixelSize ==3){
								ptr[0] = r1;
                                       				ptr[1] = g1;
                                        			ptr[2] = b1;
							}else{
								ptr[0] = r1;
                                       				ptr[1] = g1;
                                        			ptr[2] = b1;
								ptr[3]= 255;
							}
						}else{	
							if(pixelSize ==3){
								ptr[0] = 90;
								ptr[1] = 130;
								ptr[2] = 135;
							}else{
								ptr[0] = 90;
								ptr[1] = 110;
								ptr[2] = 135;
								ptr[3]= 255;
							}
						}
					}
				}
			}
			break;
		default:
			for (int y = 0; y < image->height; y++){
        			free(image->row_pointers[y]);
			}
    			free(image->row_pointers);
			printf("Sorry, you've entered the wrong argument!");
			exit(EXIT_SUCCESS);	
	}	
}
