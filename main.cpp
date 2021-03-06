#include <cstdio>
#include <cstring>
#include <iostream>
#include <fstream>
int learning[10][25][2] = {0};
int data[25] = {0};
void draw(int num){
	for(int i = 0; i < 25; i+=5){
		printf("%d %d %d %d %d\n",i,i+1,i+2,i+3,i+4);	
	}
}
void learn(int num, bool fair){
	if(fair){
		for(int n = 0; n < 10; n++){
			for(int i = 0; i < 25; i++){
				if(n != num){
					learning[n][i][1]++;
				}
			}
		}
	}
	for(int i = 0; i < 25; i++){
		if(data[i] == learning[num][i][0]){
			learning[num][i][1] += 1;
		}else{
			learning[num][i][1] -= 1;
		}
		if(learning[num][i][1] < 0){
			if(learning[num][i][0] == 1){
				learning[num][i][0] = 0;
			}else{
				learning[num][i][0] = 1;
			}
			learning[num][i][1] = 1;	
		}
	}	
}
int read(){
	int activator[10] = {0};
	int max[2] = {0};
	for(int n = 0; n < 10; n++){
		for(int i = 0; i < 25; i++){
			if(data[i] == learning[n][i][0]){
				activator[n] += learning[n][i][1];	
			}else{
				activator[n] -= learning[n][i][1];
			}
		}
		if(n == 0){
			max[0] = activator[0];
			max[1] = 0;
		}else if(activator[n] > max[0]){
			max[0] = activator[n];
			max[1] = n;
		}
	}
	return(max[1]);
			
}
void save(){
	std::ofstream file;
	file.open("memory");
	for(int n = 0; n < 10; n++){
		for(int i = 0; i < 25; i++){
			for(int x = 0; x < 2; x++){
				file << learning[n][i][x] << std::endl;
			}
		}
	}
	file.close();
}
void load(){
	std::ifstream file;
	file.open("memory");
	for(int n = 0; n < 10; n++){
		for(int i = 0; i < 25; i++){
			for(int x = 0; x < 2; x++){
				file >> learning[n][i][x];
			}
		}	
	}
}
void align(){
	for(int i = 0; i < 5; i++){
		for(int i = 0; i < 5; i++){
			if(data[4-i] == 0 && data[9-i] == 0 && data[14-i] == 0 && data[19-i] == 0 && data[24-i] == 0){
				data[4-i] = data[3-i];
				data[9-i] = data[8-i];
				data[14-i] = data[13-i];
				data[19-i] = data[18-i];
				data[24-i] = data[23-i];
			}
		}
	}
}
int main(){
	load();
	bool quit = false;
	int tempkey;	
	while(!quit){
	printf("Select an option:\n1: Full learning mode\n2: Read mode\n");
	std::cin >> tempkey;
	switch(tempkey){
		case 1:
			printf("Draw a number 5x5 space seperated 1 being a full box and a 0 being an empty box\n");
			for(int i = 0; i < 25; i+=5){
				std::cin >> data[i] >> data[i+1] >> data[i+2] >> data[i+3] >> data[i+4];
			}	
			printf("Enter in what number you drew\n");
			std::cin >> tempkey;
			align();
			learn(tempkey,false);
			save();
			break;
		case 2:
			printf("Draw a number 5x5 space seperated 1 being a full box and a 0 being an empty box\n");
                        for(int i = 0; i < 25; i+=5){
                                std::cin >> data[i] >> data[i+1] >> data[i+2] >> data[i+3] >> data[i+4];
                        }
			align();
			tempkey = read();
			printf("The number %d was read, what was the correct number?\n",tempkey);
			std::cin >> tempkey;
			learn(tempkey,true);
			break;
		default:
			break;
	}
	}
}
