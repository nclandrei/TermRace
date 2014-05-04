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

using namespace std;

char buffer[10000];                                                          // buffer contains ASCII chars for the motorcycle
int pos=0;                                                                   // current position of the motorcycle, updated in real time; it can go to +13 and -13, as the motorcycle is not allowed

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
    for(;;)
       { 
        cout << buffer;
        usleep(500000);}
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



int main(){
    pthread_t threads[3];

    char ch;
    int i=0,rc;

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

        /* rc = pthread_create(&threads[0], NULL, printRoad, (void *)0);
              if (rc){
                 cout << "Error:unable to create thread," << rc << endl;
                 exit(-1);
              }*/
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

    pthread_exit(NULL);
    myfile.close();

    return 0;
}
