#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>

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


struct argsFunc{
	int x0re; 			/*rectangle*/
	int y0re;			/*rectangle*/
	int x1re;			/*rectangle*/
	int y1re;			/*rectangle*/
	int x0ro;			/*rotation*/
	int y0ro;			/*rotation*/
	int x1ro;			/*rotation*/
	int y1ro;			/*rotation*/
	int widthRe;			/*rectangle*/
	int widthFr;			/*frame*/
	char* colorRe;			/*reactangle*/
	char* colorFr;			/*frame*/
	int fill;			/*rectangle*/
	char* fillColor;		/*rectangle*/
	int type;			/*frame*/
	int angle;			/*rotation*/
	char* outFile;
};


void readFile(char *file_name, struct Png *image);/*reading*/


void writeFile(char *file_name, struct Png *image);/*writing*/


void rectangle(struct Png* image, int x0, int y0, int x1, int y1, int width, char* col1, int bol, char* col2);/*draw rectangle*/


void frame(struct Png* image, int choice, int width, char* col);


void rotation(struct Png* image, int x0, int y0, int x1, int y1, int angle);/*part rotation*/


void rotationSquare(struct Png* image, int x0, int y0, int x1, int y1);/*square rotation*/


void rotationRectangle180(struct Png* image, int x0, int y0, int x1, int y1);/*rectangle rotation on 180 deg*/


void rotationRectangle90(struct Png* image, int x0, int y0, int x1, int y1);/*rectangle rotation on 90 deg*/


void printHelp();


int main(int argc, char **argv) {
	if(argc == 1){
		printHelp();
		return 0;
	}
	struct Png image;	
	
	int idx = -1;
	
	for(int i = 0; i < argc; i++){
		if(strstr(argv[i], ".png")){
			idx = i;
			break;
		}
	}

	if(idx == -1 && argc > 2){
		printf("You didn't enter input file!\n");
		return 0;
	}else if(idx == -1 && argc == 2){
		printHelp();
		return 0;
	}
	int opt;
	char* opts = "r:f:t:s:S:e:E:n:N:p:P:w:W:c:C:k:K:l:L:o:h?";
		
	readFile(argv[idx], &image);

	struct argsFunc arguments;
	
	arguments.x0re = 0;                       
        arguments.y0re = 0;                       
        arguments.x1re = 0;                       
        arguments.y1re = 0;                       
        arguments.x0ro = 0;                       
        arguments.y0ro = 0;                       
	arguments.x1ro = 0;                       
	arguments.y1ro = 0;                       
        arguments.widthRe = 0;                    
        arguments.widthFr = 0;                    
        arguments.colorRe = NULL;                  
        arguments.colorFr = NULL;                  
        arguments.fill = 0;                       
        arguments.fillColor = NULL;                
        arguments.type = 0;                       
        arguments.angle = 0;
	arguments.outFile = "out.png";

	struct option longOpts[]={
		{"rectangle", 0, NULL, 'r'},
		{"frame", 0, NULL, 'f'},
		{"rotation", 0, NULL, 't'},
		{"help", 0, NULL, 'h'},

		{"start_x_rec", 1, NULL, 's'},
		{"start_y_rec", 1, NULL, 'S'},
		{"end_x_rec", 1, NULL, 'e'},
		{"end_y_rec", 1, NULL, 'E'},
		
		{"start_x_rot", 1, NULL, 'n'},
                {"start_y_rot", 1, NULL,'N'},
                {"end_x_rot", 1, NULL, 'p'},
                {"end_y_rot", 1, NULL, 'P'},

		{"widthRe", 1, NULL, 'w'},
		{"widthFr", 1, NULL, 'W'},

		{"colorRe", 1, NULL, 'c'},
		{"fillColor", 1, NULL, 'C'},
		{"fill", 1, NULL, 'k'},	
		{"colorFr", 1, NULL, 'K'},

		{"type", 1, NULL, 'l'},
		{"angle", 1, NULL, 'L'},

		{"output", 1, NULL, 'o'},

		{NULL, 0, NULL, 0},
	};
	
	int flagsRec[8] = {0, 0, 0, 0, 0, 0, 0, 0};

	int flagsFra[3] = {0, 0, 0};

	int flagsRot[5] = {0, 0, 0, 0, 0};

	char* endptr;
	int longIndex;
	int iter = 0;
	
	int recFlag = 0, frameFlag = 0, rotFlag = 0;
	int funcOnRect = 0, funcOnFram = 0, funcOnRot = 0;

	opt = getopt_long(argc, argv, opts, longOpts, &longIndex); 

	while(opt != -1){
		switch(opt){
			case 'r':
				recFlag = 1;
				break;

			case 'f':
				frameFlag = 1;
				break;	

			case 't':
				rotFlag = 1; 
				break;
			
			case 'o':
				arguments.outFile = optarg;
				break;

			case 's':
				strtol(optarg, &endptr, 10);
				if(endptr == optarg + strlen(optarg)){
					arguments.x0re = atoi(optarg);
					flagsRec[0] = 1;
					break;
				}else{
					printf("Incorrect start_x_rec value!\n\n");
					printHelp();
					return 0;
				}

			case 'S':
				strtol(optarg, &endptr, 10);
				if(endptr == optarg + strlen(optarg)){
					arguments.y0re = atoi(optarg);
					flagsRec[1] = 1;
					break;
				}else{
					printf("Incorrect start_y_rec value!\n\n");
					printHelp();
					return 0;
				}

			case 'e':
				strtol(optarg, &endptr, 10);
				if(endptr == optarg + strlen(optarg)){
					arguments.x1re = atoi(optarg);
					flagsRec[2] = 1;
					break;
				}else{
					printf("Incorrect end_x_rec value!\n\n");
					printHelp();
					return 0;
				}
				
			case 'E':
				strtol(optarg, &endptr, 10);
				if(endptr == optarg + strlen(optarg)){
					arguments.y1re = atoi(optarg);
					flagsRec[3] = 1;
					break;
				}else{
					printf("Incorrect end_y_rec value!\n\n");
					printHelp();
					return 0;
				}

			case 'n':
				strtol(optarg, &endptr, 10);
				if(endptr == optarg + strlen(optarg)){
					arguments.x0ro = atoi(optarg);				
					flagsRot[0] = 1;
					break;
				}else{
					printf("Incorrect start_x_rot value!\n\n");
					printHelp();
				
				return 0;
				}

			case 'N':
				strtol(optarg, &endptr, 10);
				if(endptr == optarg + strlen(optarg)){
					arguments.y0ro = atoi(optarg);
					flagsRot[1] = 1;
					break;
				}else{
					printf("Incorrect start_y_rot value!\n\n");
					printHelp();
					return 0;
				}

			case 'p':
				strtol(optarg, &endptr, 10);
				if(endptr == optarg + strlen(optarg)){
					arguments.x1ro = atoi(optarg);
					flagsRot[2] = 1;
					break;
				}else{
					printf("Incorrect end_x_rot value!\n\n");
					printHelp();
					return 0;
				}
			
			case 'P':
				strtol(optarg, &endptr, 10);
				if(endptr == optarg + strlen(optarg)){
					arguments.y1ro = atoi(optarg);
					flagsRot[3] = 1;
					break;
				}else{
					printf("Incorrect end_y_rot value!\n\n");
					printHelp();
					return 0;
				}

			case 'w':
				strtol(optarg, &endptr, 10);
				if(endptr == optarg + strlen(optarg)){
					arguments.widthRe = atoi(optarg);
					flagsRec[4] = 1;
					break;
				}else{
					printf("Incorrect widthRe value!\n\n");
					printHelp();
					return 0;
				}

			case 'W':
				strtol(optarg, &endptr, 10);
				if(endptr == optarg + strlen(optarg)){
					arguments.widthFr = atoi(optarg);
					flagsFra[1] = 1;
					break;
				}else{
					printf("Incorrect widthFr value!\n\n");
					printHelp();
					return 0;
				}

			case 'c':
				arguments.colorRe = optarg;
				flagsRec[5] = 1;
				break;

			case 'C':
				arguments.fillColor = optarg;
				flagsRec[7] = 1;
				break;

			case 'k':
				strtol(optarg, &endptr, 10);
				if(endptr == optarg + strlen(optarg)){
					arguments.fill = atoi(optarg);
					flagsRec[6] = 1;
					break;
				}else{
					printf("Incorrect fill value!\n\n");
					printHelp();
					return 0;
				}

			case 'K':
				arguments.colorFr = optarg;
				flagsFra[2] = 1;
				break;
				
			case 'l':
				strtol(optarg, &endptr, 10);
				if(endptr == optarg + strlen(optarg)){
					arguments.type = atoi(optarg);
					flagsFra[0] = 1;
					break;
				}else{
					printf("Incorrect type value!\n\n");
					printHelp();
					return 0;
				}

			case 'L':
				strtol(optarg, &endptr, 10);
				if(endptr == optarg + strlen(optarg)){
					arguments.angle = atoi(optarg);
					flagsRot[4] = 1;
					break;
				}else{
					printf("Incorrect angle value!\n\n");
					printHelp();
					return 0;
				}

			case 'h':
			case '?':
				printHelp();
				return 0;
			default:
				printHelp();
				return 0;
		}
	
		if(recFlag){
			for(int i = 0; i < 8; i++){
		                if(flagsRec[i] == 1){
		                    funcOnRect += flagsRec[i];
		                }
		        }
			if(funcOnRect == 8 || (funcOnRect == 7 && arguments.fill == 0)){
				rectangle(&image, arguments.x0re, arguments.y0re, arguments.x1re, arguments.y1re, arguments.widthRe, arguments.colorRe, arguments.fill, arguments.fillColor);
				for(int i = 0; i < 8; i++){
			        	flagsRec[i] = 0;
			        }
			        funcOnRect = 0;
				recFlag = 0;
            		}else{
			        funcOnRect = 0;
			}
		}
		
		if(frameFlag){
			for(int i = 0; i < 3; i++){
		                if(flagsFra[i] == 1){
		                    funcOnFram += flagsFra[i];
		                }
		        }
			if(funcOnFram == 3){
				frame(&image, arguments.type, arguments.widthFr, arguments.colorFr);
				for(int i = 0; i < 3; i++){
			        	flagsRec[i] = 0;
			        }
			        funcOnFram = 0;
				frameFlag = 0;
            		}else{
			        funcOnFram = 0;
			}
		}
		
		if(rotFlag){
			for(int i = 0; i < 5; i++){
		                if(flagsRot[i] == 1){
		                    funcOnRot += flagsRot[i];
		                }
		        }
			if(funcOnRot == 5){
				rotation(&image, arguments.x0ro, arguments.y0ro, arguments.x1ro, arguments.y1ro, arguments.angle);
				for(int i = 0; i < 5; i++){
			        	flagsRec[i] = 0;
			        }
			        funcOnRot = 0;
				rotFlag = 0;
            		}else{
			        funcOnRot = 0;
			}
		}
	
		opt = getopt_long(argc, argv, opts, longOpts, &longIndex);
	}
 
	writeFile(arguments.outFile, &image);
	return 0;
}

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

void rectangle(struct Png* image, int x0, int y0, int x1, int y1, int width, char* col1, int bol, char* col2){	
	int r1, g1, b1, r2, g2, b2;
	if(col1){
		if(strcmp(col1, "red") == 0){
			r1 = 255;
			g1 = 0;
			b1 = 0;
		}
		if(strcmp(col1, "green") == 0){
                        r1 = 0;
                        g1 = 255;
			b1 = 0;
                }
		if(strcmp(col1, "blue") == 0){
                        r1 = 0;
                        g1 = 0;
                        b1 = 255;
                }
		if(strcmp(col1, "yellow") == 0){
                        r1 = 255;
                        g1 = 255;
                        b1 = 0;
                }
		if(strcmp(col1, "orange") == 0){
			r1 = 255;
			g1 = 165;
			b1 = 0;
		}
		if(strcmp(col1, "purple") == 0){
                        r1 = 128;
                        g1 = 128;
                        b1 = 0;
                }
		if(strcmp(col1, "white") == 0){
                        r1 = 255;
                        g1 = 255;
                        b1 = 255;
                }
		if(strcmp(col1, "black") == 0){
                        r1 = 0;
                        g1 = 0;
                        b1 = 0;
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
				r1 = 255;
				g1 = 0;
				b1 = 0;
			}
			if(strcmp(col2, "green") == 0){
	                        r1 = 0;
                      		g1 = 255;
				b1 = 0;
        	        }
			if(strcmp(col2, "blue") == 0){
        	                r1 = 0;
        	                g1 = 0;
        	                b1 = 255;
        	        }
			if(strcmp(col2, "yellow") == 0){
        	                r1 = 255;
        	                g1 = 255;
        	                b1 = 0;
        	        }
			if(strcmp(col2, "orange") == 0){
				r1 = 255;
				g1 = 165;
				b1 = 0;
			}
			if(strcmp(col2, "purple") == 0){
        	                r1 = 128;
        	                g1 = 128;
        	                b1 = 0;
        	        }
			if(strcmp(col2, "white") == 0){
        	                r1 = 255;
        	                g1 = 255;
        	                b1 = 255;
        	        }
			if(strcmp(col2, "black") == 0){
        	                r1 = 0;
        	                g1 = 0;
        	                b1 = 0;
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
	int pixelSize = 4;
	if (png_get_color_type(image->png_ptr, image->info_ptr) == PNG_COLOR_TYPE_RGB){
		pixelSize = 3;
	}
	int size = width/2;
	if(bol == 0){
		/*рисование вертикальных сторон*/
		for(int y = y0 - size; y < y1 + size; y++){
			if(y < 0 || y > image->height - 1){
				continue;
			}
			png_bytep row = image->row_pointers[y];
			for(int x = x0 - size; x < x0 + size;x++){
				if(x >= 0 && x < image->width){
                        		png_bytep ptr = &(row[x*pixelSize]);
					ptr[0] = r1;
					ptr[1] = g1;
					ptr[2] = b1; 
                    		}
			}
			for (int x = x1 - size; x < x1 + size; x++){
                    		if(x >= 0 && x < image->width){
                        		png_bytep ptr = &(row[x*pixelSize]);
					ptr[0] = r1;
                                        ptr[1] = g1;
                                        ptr[2] = b1; 
        	            	}
        	        }

		}
		/*рисование горизонтальных сторон*/
		for(int y = y0-size; y <= y0+size; y++){
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
            	for(int y = y1 -size; y <= y1+size; y++){
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
		for(int y = y0 - size; y <= y1 + size; y++){
                	if(y < 0 || y > image->height-1){
				continue;
                	}
                	png_byte *row = image->row_pointers[y];
                	for (int x = x0 - size; x <= x1 + size; x++){
                    		if(x >= 0 && x < image->width){
                        		png_bytep ptr = &(row[x*pixelSize]);
					ptr[0] = r2;
                                        ptr[1] = g2;
                                        ptr[2] = b2; 
                    		}
                	}
            	}
		/*рисование вертикальных границ*/
            	for(int y = y0 - size; y <= y1 + size; y++){
               		if(y < 0 || y > image->height-1){
			        continue;
                	}
                	png_byte *row = image->row_pointers[y];
                	for (int x = x0 - size; x <= x0 + size; x++){
                    		if(x >= 0 && x < image->width){
                       			png_bytep ptr = &(row[x*pixelSize]);
					ptr[0] = r1;
                                        ptr[1] = g1;
                                        ptr[2] = b1;
                    		}
                	}
                	for (int x = x1 - size; x <= x1 + size; x++){
                		if(x >= 0 && x < image->width){
                        		png_bytep ptr = &(row[x*pixelSize]);
					ptr[0] = r1;
                                        ptr[1] = g1;
                                        ptr[2] = b1;
                    		}
                	}
            	}/*рисование горизонтальных границ*/
            	for(int y = y0 - size; y <= y0 + size; y++){
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
            	for(int y = y1 -size; y <= y1 + size; y++){
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

void frame(struct Png* image, int choice, int width, char* col){
	int r1, g1, b1;
	if(col){
		if(strcmp(col, "red") == 0){
			r1 = 255;
			b1 = 0;
			g1 = 0;
		}
		if(strcmp(col, "green") == 0){
                        r1 = 0;
                        b1 = 255;
                        g1 = 0;
                }
		if(strcmp(col, "blue") == 0){
                        r1 = 0;
                        b1 = 0;
                        g1 = 255;
                }
		if(strcmp(col, "yellow") == 0){
                        r1 = 255;
                        b1 = 255;
                        g1 = 0;
                }
		if(strcmp(col, "orange") == 0){
			r1 = 255;
			g1 = 165;
			b1 = 0;
		}
		if(strcmp(col, "purple") == 0){
                        r1 = 128;
                        b1 = 0;
                        g1 = 128;
                }
		if(strcmp(col, "white") == 0){
                        r1 = 255;
                        b1 = 255;
                        g1 = 255;
                }
		if(strcmp(col, "black") == 0){
                        r1 = 0;
                        b1 = 0;
                        g1 = 0;
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
                                                                ptr[0] = b1;
                                       				ptr[1] = g1;
                                        			ptr[2] = r1;
                                                        }else{
                                                                ptr[0] = b1;
                                       				ptr[1] = g1;
                                        			ptr[2] = r1;
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
								ptr[0] = 120;
								ptr[1] = 130;
								ptr[2] = 150;
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

void printHelp(){
	printf("Использование программы:\n");
	printf("Есть 3 ключа для следующих операций: рисование прямоугольника, рисование рамки (есть 3 на выбор), поворот изображения на угол кратный 90 градусов:\n");
	printf("\tКлюч для рисования прямогуольника: --rectangle\n");
	printf("\tКлюч для рисования рамки: --frame\n");
	printf("\tКлюч для поворота: --rotation\n\n");
	printf("После того, как введен один из ключей выше - нужно ввести следующие ключи, соответствующие выбранной операции, которые принимают только один аргумент:\n");
	printf("\tДля --rectangle:\n");
	printf("\t\t--start_x_rec - абсцисса левого верхнего угла\n");
	printf("\t\t--start_y_rec - ордината левого верхнего угла\n");
	printf("\t\t--end_x_rec - абсцисса правого нижнего угла\n");
	printf("\t\t--end_Y_rec - ордината правого нижнего угла\n");
	printf("\t\t--widthRe - толщина сторон прямоугольника\n");
	printf("\t\t--colorRe - цвет сторон прямоугольника(может принимать аргумент \"red\", \"green\", \"blue\", \"yellow\", \"orange\", \"purple\", \"white\", \"black\")\n");
	printf("\t\t--fill - заливка (аргумент может быть 1 - заливка есть, может быть 0 - заливки нет)\n");
	printf("\t\t--fillColor - цвет заливки (может принимать аргумент \"red\", \"green\", \"blue\", \"yellow\", \"orange\", \"purple\", \"white\", \"black\")\n");
	printf("\tДля --frame:\n");
	printf("\t\t--type - абсцисса левого верхнего угла.\n");
	printf("\t\t--widthFr - ордината левого верхнего угла:\n");
	printf("\t\t--colorFr - абсцисса правого нижнего угла\n");
	printf("\tДля --rotation:\n");
	printf("\t\t--start_x_rot - абсцисса левого верхнего угла\n");
	printf("\t\t--start_y_rot - ордината левого верхнего угла\n");
	printf("\t\t--end_x_rot - абсцисса правого нижнего угла\n");
	printf("\t\t--end_Y_rot - ордината правого нижнего угла\n");
	printf("\t\t--angle - угол поворота(должен быть кратным 90 градусов)\n\n");
}

