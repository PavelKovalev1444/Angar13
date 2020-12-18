#include "headers.h"
#include "pngStruct.h"

#include "readFile.h"
#include "writeFile.h"
#include "rectangle.h"
#include "frame.h"
#include "rotation.h" 

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



int main(int argc, char **argv) {
	if(argc == 1){
		printHelp();
		return 0;
	}
	struct Png image;	
	
	int idx = -1, outIdx = -2;
	
	for(int i = 0; i < argc; i++){
		if(strstr(argv[i], ".png")){
			idx = i;
			break;
		}
	}

	for(int i = 0; i < argc; i++){
		if(strstr(argv[i], "--output")){
			outIdx = i;
			break;
		}
	}

	if(outIdx == idx){
		for(int i = outIdx + 2; i < argc; i++){
			if(strstr(argv[i], ".png")){
				idx = i;
				break;
			}
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
	
	int recFlag = 0, frameFlag = 0, rotFlag = 0, writeFlag = 0;
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
				writeFlag = 1; 
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
				writeFlag = 1; 
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
				writeFlag = 1; 
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
 	if(writeFlag){
		writeFile(arguments.outFile, &image);
		return 0;
	}else{
		printf("You've entered not enough keys!\n\n");
		printHelp();
		return 0;
	}
}
