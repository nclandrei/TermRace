/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////                                                               Racing Game using an Unbuffered Terminal                                                                      /////////
///////                                                               User can steer a motorcycle left or right                                                                     /////////
///////                                                                                                                                                                             /////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <pthread.h>
#include <unistd.h>
#include <termios.h>
#include <ctime>
#include <cstdlib>

using namespace std;

char buffer[10000];                                                          // buffer contains ASCII chars for the motorcycle
int pos=0;                                                                   // current position of the motorcycle, updated in real time; it can go to +13 and -13, as the motorcycle is not allowed
int z=7116;                                                                  // this is used for printing the obstacles (memorizing )
char temporary[10000],game_over[10000],new_game[20000];

/* void *printRoad(void *threadid){                                          // code can be modified to use the road and automobile as two separate objects( to switch, uncomment this section
                                                                             // and activate the third thread in main)         
    for(;;)
    {
     cout << "|                                      |" << endl;
     cout << "|                                      |" << endl;
     cout << "|                                      |" << endl;
     cout << "|                                      |" << endl;
     cout << "|                                      |" << endl;
     cout << "|                                      |" << endl;
     cout << "|                                      |" << endl;
     cout << "|                                      |" << endl;
     cout << "|                                      |" << endl;
     cout << "|                                      |" << endl;
     cout << "|                                      |" << endl;
     cout << "|                                      |" << endl;
        usleep(300000);
    }

    pthread_exit(NULL);
} */

void *printCar(void *threadid){
    srand(time(NULL));
    for(;;)
       { for(z=rand()% 70 +7117;z>=67;z=z-150){
        strcpy(temporary,buffer);
        temporary[z] = '_';
        temporary[z+1] = '_';
        temporary[z+2] = '_';
        temporary[z+3] = '_';
        temporary[z+4] = '_';
        temporary[z+5] = '_';
        temporary[z+6] = '_';
        temporary[z+7] = '_';
        temporary[z+8] = '_';
        temporary[z+9] = '_';
        temporary[z+10] = '_';
        temporary[z+11] = '_';
        temporary[z+12] = '_';
        temporary[z+13] = '_';
        temporary[z+14] = '_';
        temporary[z+15] = '_';
        temporary[z+16] = '_';
        temporary[z+17] = '_';
        temporary[z+18] = '_';
        temporary[z+19] = '_';
        if(buffer[z] == '#' || buffer[z] == '0' || buffer[z] == '|' || buffer[z] == '-' || buffer[z] == '(' || buffer[z] == ')' || buffer[z] == '/' || buffer[z] == '=' || 
           buffer[z+1] == '#' || buffer[z+1] == '0' || buffer[z+1] == '|' || buffer[z+1] == '-' || buffer[z+1] == '(' || buffer[z+1] == ')' || buffer[z+1] == '/' || buffer[z+1] == '=' ||
           buffer[z+2] == '#' || buffer[z+2] == '0' || buffer[z+2] == '|' || buffer[z+2] == '-' || buffer[z+2] == '(' || buffer[z+2] == ')' || buffer[z+2] == '/' || buffer[z+2] == '=' ||
           buffer[z+3] == '#' || buffer[z+3] == '0' || buffer[z+3] == '|' || buffer[z+3] == '-' || buffer[z+3] == '(' || buffer[z+3] == ')' || buffer[z+3] == '/' || buffer[z+3] == '=' ||
           buffer[z+4] == '#' || buffer[z+4] == '0' || buffer[z+4] == '|' || buffer[z+4] == '-' || buffer[z+4] == '(' || buffer[z+4] == ')' || buffer[z+4] == '/' || buffer[z+4] == '=' ||
           buffer[z+5] == '#' || buffer[z+5] == '0' || buffer[z+5] == '|' || buffer[z+5] == '-' || buffer[z+5] == '(' || buffer[z+5] == ')' || buffer[z+5] == '/' || buffer[z+5] == '=' ||
           buffer[z+6] == '#' || buffer[z+6] == '0' || buffer[z+6] == '|' || buffer[z+6] == '-' || buffer[z+6] == '(' || buffer[z+6] == ')' || buffer[z+6] == '/' || buffer[z+6] == '=' ||
           buffer[z+7] == '#' || buffer[z+7] == '0' || buffer[z+7] == '|' || buffer[z+7] == '-' || buffer[z+7] == '(' || buffer[z+7] == ')' || buffer[z+7] == '/' || buffer[z+7] == '=' ||
           buffer[z+8] == '#' || buffer[z+8] == '0' || buffer[z+8] == '|' || buffer[z+8] == '-' || buffer[z+8] == '(' || buffer[z+8] == ')' || buffer[z+8] == '/' || buffer[z+8] == '=' ||
           buffer[z+9] == '#' || buffer[z+9] == '0' || buffer[z+9] == '|' || buffer[z+9] == '-' || buffer[z+9] == '(' || buffer[z+9] == ')' || buffer[z+9] == '/' || buffer[z+9] == '=' ||
           buffer[z+10] == '#' || buffer[z+10] == '0' || buffer[z+10] == '|' || buffer[z+10] == '-' || buffer[z+10] == '(' || buffer[z+10] == ')' || buffer[z+10] == '/' || buffer[z+10] == '=' || 
           buffer[z+11] == '#' || buffer[z+11] == '0' || buffer[z+11] == '|' || buffer[z+11] == '-' || buffer[z+11] == '(' || buffer[z+11] == ')' || buffer[z+11] == '/' || buffer[z+10] == '=' ||
           buffer[z+12] == '#' || buffer[z+12] == '0' || buffer[z+12] == '|' || buffer[z+12] == '-' || buffer[z+12] == '(' || buffer[z+12] == ')' || buffer[z+12] == '/' || buffer[z+10] == '=' ||
           buffer[z+13] == '#' || buffer[z+13] == '0' || buffer[z+13] == '|' || buffer[z+13] == '-' || buffer[z+13] == '(' || buffer[z+13] == ')' || buffer[z+13] == '/' || buffer[z+10] == '=' ||
           buffer[z+14] == '#' || buffer[z+14] == '0' || buffer[z+14] == '|' || buffer[z+14] == '-' || buffer[z+14] == '(' || buffer[z+14] == ')' || buffer[z+14] == '/' || buffer[z+10] == '=' ||
           buffer[z+15] == '#' || buffer[z+15] == '0' || buffer[z+15] == '|' || buffer[z+15] == '-' || buffer[z+15] == '(' || buffer[z+15] == ')' || buffer[z+15] == '/' || buffer[z+10] == '=' ||
           buffer[z+16] == '#' || buffer[z+16] == '0' || buffer[z+16] == '|' || buffer[z+16] == '-' || buffer[z+16] == '(' || buffer[z+16] == ')' || buffer[z+16] == '/' || buffer[z+10] == '=' ||
           buffer[z+17] == '#' || buffer[z+17] == '0' || buffer[z+17] == '|' || buffer[z+17] == '-' || buffer[z+17] == '(' || buffer[z+17] == ')' || buffer[z+17] == '/' || buffer[z+10] == '=' ||
           buffer[z+18] == '#' || buffer[z+18] == '0' || buffer[z+18] == '|' || buffer[z+18] == '-' || buffer[z+18] == '(' || buffer[z+18] == ')' || buffer[z+18] == '/' || buffer[z+10] == '=' ||
           buffer[z+19] == '#' || buffer[z+19] == '0' || buffer[z+19] == '|' || buffer[z+19] == '-' || buffer[z+19] == '(' || buffer[z+19] == ')' || buffer[z+19] == '/' || buffer[z+10] == '=')   {
              
                cout << game_over; return 0; }
        else {cout << temporary;
             usleep(100000);} } }
    // cout << flush;
    pthread_exit(NULL);

}

void *readDir(void *threadid){
    for(;;){
    char *ptr,aux,temp[10000];
    int length,j=0;

    struct termios old_tio, new_tio;
    unsigned char c;

    /* get the terminal settings for stdin */
    tcgetattr(STDIN_FILENO,&old_tio);

    /* we want to keep the old setting to restore them a the end */
    new_tio=old_tio;

    /* disable canonical mode (buffered i/o) and local echo */
    new_tio.c_lflag &=(~ICANON & ~ECHO);

    tcsetattr(STDIN_FILENO,TCSANOW,&new_tio);
    c=getchar();
     if(c=='d' && pos<=34){
     ptr = strtok(buffer,"\n");
     while(ptr!=NULL){
        length = strlen(ptr);
        aux = ptr[length-2];
        int i = length-2;  
        while(i>=68){
            ptr[i] = ptr[i-1];
            i--;
        }
        ptr[67] = aux;
        int l=0;
        while(l<length){
            temp[j]=ptr[l];
            l++;j++;
        }
        temp[j]='\n';
        j++;
        ptr = strtok(NULL,"\n");
      }
        strcpy(buffer,temp);
        buffer[strlen(buffer)-1] = '\n';
        pos++;
      }
    else if(c=='a' && pos>=-32){
     ptr = strtok(buffer,"\n");
     while(ptr!=NULL){
        length = strlen(ptr);
        aux = ptr[length-2];
        int i = 67;  
        while(i<=length-2){
            ptr[i] = ptr[i+1];
            i++;
        }
        ptr[length-2] = aux;
        int l=0;
        while(l<length){
            temp[j]=ptr[l];
            l++;j++;
        }
        temp[j]='\n';
        j++;
        ptr = strtok(NULL,"\n");
      }
        strcpy(buffer,temp);
        buffer[strlen(buffer)-1] = '\n';
        pos--;

      }
    tcsetattr(STDIN_FILENO,TCSANOW,&old_tio);
    }
    pthread_exit(NULL);   
}

/* void *printObst(void *threadid){
  for(;;){
    int random = rand()%7180 + 7117;
    buffer[random] = '-';
    buffer[random+1] = '-';
    buffer[random+2] = '-';
    buffer[random+3] = '-';
    buffer[random+4] = '-';
    buffer[random+5] = '-';
    . . . .

  }
  pthread_exit(NULL);
} */

int main(){
    pthread_t threads[3];
    srand(time(NULL));
    char ch;
    char choice;                        // choice for the game (n for new game, q for quit)
    int i = 0;

    ifstream gameover;
    gameover.open("game_over.txt");
    while(!gameover.eof()){
      gameover.get(ch);
      game_over[i] = ch;
      i++;
    }
    game_over[strlen(game_over)-1] = '\0';
    gameover.close();
    i=0;
    if (system("CLS")) system("clear");

    ifstream newgame;
    newgame.open("new_game.txt");
    while(!newgame.eof()){
      newgame.get(ch);
      new_game[i] = ch;
      i++;
    }
    new_game[strlen(new_game)-1] = '\0';
    newgame.close();
    cout << new_game;
    cin >> choice;
    if( choice == 'n'){
    i=0;
    int rc;

    ifstream myfile;                    // opening a file text with the ASCII drawing of the automobile used
    myfile.open("bike.txt");

    while ( !myfile.eof() )
    {
      myfile.get(ch);
      buffer[i] = ch;                   // coppy char by char into a buffer used for moving
      i++;	
    }	
    buffer[strlen(buffer)-1] = '\0';    // used because these characters are 2 newlines
    // buffer[strlen(buffer)-2] = '\0';
    myfile.close();

        rc = pthread_create(&threads[1], NULL, readDir, (void *)1);
              if (rc){
                cout << "Error:unable to create thread," << rc << endl;
                exit(-1);
              }        

        rc = pthread_create(&threads[0], NULL, printCar, (void *)0);
              if (rc){
                cout << "Error:unable to create thread," << rc << endl;
                exit(-1);
              }

        /* rc = pthread_create(&threads[2], NULL, printObst, (void *)2);
              if (rc){
                 cout << "Error:unable to create thread," << rc << endl;
                 exit(-1);
              } */

    pthread_exit(NULL);
    myfile.close();
   }
   else return 0;
}
