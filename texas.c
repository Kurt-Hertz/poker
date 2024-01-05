#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define CARDS 52

int balance[8];
int out[8];
int pot;
int inc;
int deck[52];
int sdeck[52];

void play();
void turn();
void one(int p);
int hit(int *val);
void flop(int p);
void hand(int v);
char *cface(int v);
char *csuit(int v);
void bet(int v);
void result(int players);
void initdeck();
void shuffle();
void quit();


int main(){ 
    printf("Welcome to my Texas holdem! Input 'play' or 'quit' you or 'help' to get a list of valid commands.\n");
    char input[6];
    scanf("%5s", input);
    while(strcmp(input, "quit") != 0){
        while(strcmp(input, "play") != 0){
            if(strcmp(input, "help") == 0)
                printf("Type 'play' to begin the game.\n");
            else if(strcmp(input, "quit")==0){
                quit();
                printf("Enter 'play' to start the game.\n");
            }else
                printf("Invalid command, type 'play' to begin.\n");
            scanf("%s", input);
        }       
        play();
        scanf("%5s", input);
    }
}

void play(){
    printf("Lets start you off.\n");

    initdeck();
    shuffle();
    turn();
    
    char input[6];
    printf("type 'quit' if you are done.\n");
    scanf("%5s", input);
    if(strcmp(input,"quit")==0){
        quit();    
    }
    printf("Good game.\n");
}

void initdeck(){
    int i=0;
    for(i;i<52;i++){
        deck[i] = i+1;  
    }
}

void shuffle(){
    srand(time(NULL));
    int i=0;
    for(i;i<52;i++){
        sdeck[i] = deck[i];
    }
    i=0;
    for(i=CARDS-1;i>0;i--){
        int j = rand()%(i+1);
        int n = sdeck[i];
        sdeck[i] = sdeck[j];
        sdeck[j] = n;
    }
}

void turn(){
   int players; 
   pot = 0;
   
   printf("how many players do you want\n");
   scanf("%d", &players);
   printf("We will start you off with 500 credits\n");
   for (int i = 0; i < players; i++){
        out[i] = 1;
        balance[i] = 500;
   }
   flop(players);
   hand(players);
   one(players);

   result(players);
   
    
}

void hand(int players){
   int i=0;
   for(i;i<players;i++){

      int d1 = hit(&inc);
      char *cn1 = csuit(d1);
      char *cf1 = cface(d1);
   
      printf("player %d got a %s of %s, and ",i+1, cf1, cn1);

      int d2 = hit(&inc);
      char *cn2 = csuit(d2);
      char *cf2 = cface(d2);

      printf("a %s of %s.\n", cf2, cn2);
      
    }
    bet(players);
}

void bet(int players){
int i;
    for(i = 0; i < players; i++){
        if(out[i] == 1){
        
            char input[6];
            int val;
            printf("type 'bet' or 'stay' or 'fold' (player %d).\n", i+1);
            scanf("%5s", input);
            if(strcmp(input, "bet") == 0){
        
                printf("Enter a bet amount, you have %d credits to work with.\n", balance[i]);
                scanf("%d", &val);
                printf("bet amount %d .\n", val);
                while(val > balance[i] || val <= 10 ){
                    if(val > balance[i])
                        printf("You cannot bet more than your balance. Your balance is: %d.\n", balance[i]);
                    else if(val <= 0)
                        printf("You must make a bet. Enter a valid bet amount.\n");
                    else if(balance[i] > val)
                        printf("Your bet is to small. Enter a valid bet amount.\n");
                    else
                        printf("Invalid entry. Try again.\n");
                    scanf("%d", &val);
                }

                balance[i] -= val;
                printf("You've made a bet of %d player %d. Good luck!\n\n", val, i+1);
                pot += val; 
                

            }
            else if(strcmp(input,"help") == 0)
                printf("Type 'bet'or 'stay' or 'fold' followed by a bet amount. For example, you could type 'bet 50'.\n"); 
            else if(strcmp(input, "stay") == 0){

            }
            else if(strcmp(input, "fold") == 0)
            {
            out[i] = 0;
            }
            
            else if(strcmp(input,"quit")==0){
                quit();
                
            }else
                printf("You've entered an invalid command. Type 'help' for a list of valid commands.\n");

        
        }
    }   
}

void flop(int p){
      inc = 0;

      int f1 = hit(&inc);
      char *hn1 = csuit(f1);
      char *hf1 = cface(f1);
   
      printf("The flop is a %s of %s, and ", hf1, hn1);

      int f2 = hit(&inc);
      char *hn2 = csuit(f2);
      char *hf2 = cface(f2);

      printf("a %s of %s, and ", hf2, hn2);

      int f3 = hit(&inc);
      char *hn3 = csuit(f3);
      char *hf3 = cface(f3);

      printf("a %s of %s.\n\n", hf3, hn3);
}

int hit(int *i){
    int a = sdeck[*i];
    *i = *i + 1;
    return a;
}

void one(int p){
    int inc = 0;

      int o1 = hit(&inc);
      char *gn1 = csuit(o1);
      char *gf1 = cface(o1);

      printf("The next card is a %s of %s\n", gf1, gn1);
      bet(p);
      inc = inc + 1;

      int o2 = hit(&inc);
      char *gn2 = csuit(o2);
      char *gf2 = cface(o2);

      printf("The next card is a %s of %s\n", gf2, gn2);
      bet(p);
}

char *csuit(int v){
    v = v%4;
    switch(v){
        case 0 :
            return "Hearts";
        case 1 :
            return "Clubs";
        case 2 :
            return "Diamonds";
        case 3 :
            return "Spades";
    }
}

char *cface(int v){
    v = v%13+1;
    char *output;
    switch(v){
        case 1 :
            output = "Ace";
            break;
        case 2 :
            output = "Two";
            break;
        case 3 :
            output = "Three";
            break;
        case 4 :
            output = "Four";
            break;
        case 5 :
            output = "Five";
            break;
        case 6 :
            output = "Six";
            break;
        case 7 :
            output = "Seven";
            break;
        case 8 :
            output = "Eight";
            break;
        case 9 :
            output = "Nine";
            break;
        case 10 :
            output = "Ten";
            break;
        case 11 :
            output = "Jack";
            break;
        case 12 :
            output = "Queen";
            break;
        case 13 :
            output = "King";
    }
    return output;
}

void result(int players){

   printf("Input which person won the round.\n");
    int winner;
    scanf("%d", &winner);
    balance[winner-1] += pot;
    printf("Congraulation on player %d will his balence is at %d\n",winner, balance[winner-1]);
}

void quit(){
    printf("Are you sure you want to quit? Type 'y' or 'n'.\n");
    char input[6];
    scanf("%s",input);
    if(strcmp(input,"y")==0)
        exit(0);
    else 
        printf("Quit cancelled.\n");
}