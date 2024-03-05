#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include <time.h>
#include <string.h>

#define MAX 20


// create a struct to store elements
struct Node{
    char Player[MAX];
    float Score;
    struct Node* next;
};

// create first player
struct Node* head = NULL;

struct Node* Add_player(){
    struct Node* New_player = (struct Node*)malloc(sizeof(struct Node));
    if(New_player == NULL){
        printf("Fail: Memory allocation fail");
    }
    // enter player
    printf("Enter Your Player: ");
    scanf("%s",New_player->Player);
    New_player->Score = 0;
    New_player->next = NULL;
    // check head 
    if(head == NULL){
        head = New_player;
    }else{
        struct Node* Now = head;
        while(Now->next != NULL){
            Now = Now->next;
        }
        Now->next = New_player;

    }
    return New_player;

}
// create the function random number generator
int random(int min, int max){
    return min + rand() % (max + 1 - min);
} 
//number separation
void Devide_number(int test[],int magic_number){
    // Separate numbers for comparison
    int ngan = magic_number / 1000;
    int tram = (magic_number / 100) % 10;
    int chuc = (magic_number / 10) % 10;
    int donvi = magic_number % 10;

    // save in array to easy access
	test[0] = ngan;
	test[1] = tram;
	test[2] = chuc;
	test[3] = donvi;
}

// function compare
void compare_magicNumber(struct Node* current, int a[]){

    // variable to count the loop
    float dem = 0.00;

    int guest_number = 0;

	//Create an array to store the number entered by the user
	int check[4] = {0,0,0,0};
	
    // Enter number
    do{
        

        printf("Enter number you guest: ");
        scanf("%d",&guest_number);
        Devide_number(check,guest_number);    

        // Check the random number is the same
        for(int j = 0; j < 4; j++){
            if(a[j] == check[j]){
                printf("%d",check[j]);
            }else{
                printf("-");
            }
        }
        printf("\n");
    	dem++;
    }while(a[0] != check[0] || a[1] != check[1] || a[2] != check[2] || a[3] != check[3]);

    current->Score = (1/dem)*100;
}

void savetofile(struct Node* current){
    FILE *file = fopen("Player.txt","a");
    if(file == NULL){
        printf("FAIL: Open fail");
        exit(1);
    }
    while(current != NULL){
        fprintf(file, "%s %.2f \n",current->Player,current->Score);
        current = current->next;
    }
    fclose(file);
}
void printtofile(const char *filename){
    FILE *file = fopen(filename,"r");
    if(file == NULL){
        printf("FAIL: Open fail");
        exit(1);
    }
    char name[MAX];
    float score;
    int number_player = 0 ;
    while (fscanf(file, "%s %f",name,&score) == 2) {
        number_player++;
    }
    // Rewind file pointer to the beginning
    rewind(file);
    struct Node players[number_player];
    int i = 0;
    while (fscanf(file, "%s %f",name,&score) == 2) {
        strcpy(players[i].Player, name);
        players[i].Score = score;
        i++;
    }
    for(int i = 0; i < number_player;i++){
		for(int j = 0; j < number_player - i;j++){
			if(players[j].Score < players[j+1].Score){
				struct Node tmp = players[j];
				players[j] = players[j+1];
				players[j+1] = tmp;
			}
		}
	}
	for(int i = 0;i<5;i++){
		printf("player: %s, score: %f\n",players[i].Player,players[i].Score);
	}
	if (feof(file)) {
        printf("End of file reached.\n");
    } else if (ferror(file)) {
        perror("Error reading from file");
    }
    fclose(file);
}

int main(){

    printf("----------------------Number Guesting Game------------------------\n");
    
    // variable to continue the loop
    char con_ti_nue;

    do{
        // create the number player must guest
	    srand((unsigned int) time(NULL));
	    int magic_number = random (0,9999);
        printf("magic number: %d\n",magic_number);

        // save in array to easy access
	    int a[4] = {0,0,0,0};
        Devide_number(a,magic_number);

        // create New_player
        struct Node* current = Add_player();

        // compare
        compare_magicNumber(current,a);
		
		printf("%s\n",current->Player);
        printf("%.3f\n",current->Score);

        // ask to continue
        printf("Do you want to play continue? [Y/N]?");
        scanf(" %c",&con_ti_nue);
        savetofile(current);

    }while(con_ti_nue == 'Y' || con_ti_nue == 'y');
    printtofile("Player.txt");
    return 0;
}