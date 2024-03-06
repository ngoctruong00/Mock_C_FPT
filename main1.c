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
    // create a pointer struct and allocate for it
    struct Node* New_player = (struct Node*)malloc(sizeof(struct Node));
    if(New_player == NULL){
        printf("Fail: Memory allocation fail");
    }

    // enter player and assign value for each element of struct
    printf("Enter Your Player: ");
    scanf("%s",New_player->Player);
    New_player->Score = 0;
    New_player->next = NULL;

    // check head 
    if(head == NULL){
        head = New_player;
    }else{
        // access to final player of linked list struct to save
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
        
		printf("Number Guesting is 0 to 9999\n");
		nhaplai:
        printf("Enter number you guest: ");
        scanf("%d",&guest_number);
        int b = guest_number / 1000;
        if(b > 9){
			printf("You enter the number bigger the random number\n");
			printf("Enter again\n");
			goto nhaplai;
		}  
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

    // save score of players
    current->Score = (1/dem)*100;
}

void savetofile(struct Node* current){
    // open file to save data
    FILE *file = fopen("Player.txt","a+");

    //check file
    if(file == NULL){
        printf("FAIL: Open fail");
        exit(1);
    }
    // Save the data you just played
    while(current != NULL){
        fprintf(file, "%s %.2f \n",current->Player,current->Score);
        current = current->next;
    }
    fclose(file);
}
void printtofile(const char *filename){
    // Open file save data
    FILE *file = fopen(filename,"r");
    // check open
    if(file == NULL){
        printf("FAIL: Open fail");
        exit(1);
    }
    // create name and score variable
    char name[MAX];
    float score;

    // create number_player to count player in the linked list struct
    int number_player = 0 ;
    while (fscanf(file, "%s %f",name,&score) == 2) {
        number_player++;
    }
    // Rewind file pointer to the beginning
    rewind(file);

    // create a struct array corresponding to the number of saved players
    struct Node players[number_player];

    // assign value for each struct element
    int i = 0;
    while (fscanf(file, "%s %f",name,&score) == 2) {
        strcpy(players[i].Player, name);
        players[i].Score = score;
        i++;
    }

    // Arranged from largest to smallest
    for(int i = 0; i < number_player;i++){
		for(int j = 0; j < number_player - i;j++){
			if(players[j].Score < players[j+1].Score){
				struct Node tmp = players[j];
				players[j] = players[j+1];
				players[j+1] = tmp;
			}
		}
	}
    // print data of player
	if(number_player < 6){
		for(int i = 0;i<number_player;i++){
		printf("player: %s, score: %f\n",players[i].Player,players[i].Score);
		}
		printf("There are only %d players\n",number_player);
	}
	else{
		for(int i = 0;i<5;i++){
		printf("player: %s, score: %f\n",players[i].Player,players[i].Score);
		}
	}

	// check the pointer position at the end of the array
	if (feof(file)) {
        printf("End of file reached.\n");
    } else if (ferror(file)) {
        perror("Error reading from file");
    }
    fclose(file);
}

// function show select
void manual(){
	
    printf("----------------------Number Guesting Game------------------------\n");
	printf("Enter\'1\'. Start Game \n");
	printf("Enter\'2\'. Exit Game \n");
	printf("Enter\'3\'. Show High Player \n");
	printf("Enter\'4\'. Delete All Player\n");
    printf("Your selection: ");

}
int main(){
	
	
    int choose = 0;
    resel:
//	nhaplai:
    manual();              
    scanf("%d",&choose);
    switch (choose)
    {
    case 1:
//        printf("Enter\'1\'. Start Game \n");
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
            // save file
            savetofile(current);

        }while(con_ti_nue == 'Y' || con_ti_nue == 'y');
        // print file
        printtofile("Player.txt");
        goto resel;
    case 2:
        exit(0);
        break;
    case 3:
        // print file
        printtofile("Player.txt");
        goto resel;
    case 4:
    {
        // open file and select "W"
    	FILE *f = fopen("Player.txt","w");
    	if(f == NULL){
			printf("Erorr: Don't open file");
		}else{
			printf("Delete Success Full");
		}
		goto resel;
	}
        // Detele file
        // int ret;
        // ret = remove("Player.txt");
        // if(ret == 0) 
        // {
        //     printf("Delete Successful!!!");
        // }
        // else 
        // {
        //     printf("Error: Cannot delete above file");
        // }
        // goto resel;
    default:
        printf("Enter diffrent 1 to 4\n");
        printf("Enter again\n");
        goto resel;
    }
    
    
    // printtofile("Player.txt");
    return 0;
}