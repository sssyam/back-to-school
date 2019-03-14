#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
using namespace std;

//////////////////////////////////////
//    GETCH Implementation Start    //
//////////////////////////////////////

/////////////////////////
//  PLAGUARIZED CODE   //
/////////////////////////
/*
+-------+
| o   o |
|       |
| \___/ |
+-------+
*/
#include <termios.h>
#include <stdio.h>
 
static struct termios old, New;
 
/* Initialize new terminal i/o settings */
void initTermios(int echo) 
{
  tcgetattr(0, &old); //grab old terminal i/o settings
  New = old; //make new settings same as old settings
  New.c_lflag &= ~ICANON; //disable buffered i/o
  New.c_lflag &= echo ? ECHO : ~ECHO; //set echo mode
  tcsetattr(0, TCSANOW, &New); //apply terminal io settings
}
 
/* Restore old terminal i/o settings */
void resetTermios(void) 
{
  tcsetattr(0, TCSANOW, &old);
}
 
/* Read 1 character - echo defines echo mode */
char getch_(int echo) 
{
  char ch;
  initTermios(echo);
  ch = getchar();
  resetTermios();
  return ch;
}

/* Read 1 character without echo getch() function definition.*/
char getch(void) 
{
  return getch_(0);
}

//////////////////////////////////////
//    GETCH Implementation Ends     //
//////////////////////////////////////

struct node {
    char value;
    bool finish;
    node *link[26];
};

void clrscr(){
    // LOL !!
    system("clear");
}

node* newnode(char c){
    node *t = new node;
    t->value = c;
    t->finish = false;

    for( int i=0; i < 26; i++){
        t->link[i] = NULL;
    }

    return t;
}

node* push_to_trie( node *root, string t){
    node *tmp = root;

    for( int i=0; i<t.length(); i++){
        
        if( root->link[ t[i] - 'a' ] == NULL ){
            node *temp = newnode(t[i]);
            root->link[ t[i] - 'a' ] = temp;
        }
        
        // Why for every letter ? Why not at the end
        if (i + 1 == t.length())
            root->link[ t[i] - 'a' ]->finish = true;

        root = root->link[ t[i] - 'a' ];
    }

    return tmp;
}

void scanall(node *t, char buffer[], int last){
    // Recursive Backtracking ! Really !!!
    // You should just quit development

    if(t->value != '^')
        buffer[last] = t->value;    
    else
        last = -1;

    if( t->finish){
        buffer[last+1] = '\0';
        cout << buffer << endl;
    }
    
    for( int i=0; i<26; i++){
        if(t->link[i] != NULL)
            scanall(t->link[i], buffer, last + 1);
    }
}

void print_related(node *root, char s[], int len){
    // What the fuck !!
    // for every word you are parsing char buffer and at the end rendering the tree
    // That is bullshit !!
    // You need store the addresses with every increment
    // Find a better way 

    char buffer[10000];
    int index = 0;
    for ( int i=0; i<len; i++){
        root = root->link[ s[i] - 'a' ];
        if(root == NULL)
            break;
        else
            buffer[index++]=root->value;
    }

    if(root != NULL){
        // Asshole ! That is a poor workaround
        // overwriting the last character index to fix the repetitive character append at scanall
        // This is just not done ! 
        scanall(root, buffer, index-1);
    }
}

int main(){

    // init variables
    string s;
    node *trie = new node;
    trie->value = '^';
    trie->finish = false;
    for( int i=0; i < 26; i++){
        trie->link[i] = NULL;
    }

    // Read from file and push to trie
    fstream f;
    f.open("wordlist");
    while (!f.eof()){
        f >> s;
        trie = push_to_trie(trie, s);
    }

    char buffer[10000];
    int index = 0; 
    
    // NOT NEEDED: scanall(trie, buffer, index);
    // for future 
    
    node *lookup[10000];
    cout << ">> "; // AHA! You are emulating terminal

    while( true ){
        char a = getch();
        clrscr();
        if ( a >= 'a' && a <= 'z'){
            buffer[index] = a;
            buffer[index+1] = '\0';
            cout << ">> " << buffer << endl;
            index ++;
            print_related(trie, buffer, index);
        }
        else if(a == ((char)(127))){
            index --;
            buffer[index] = '\0';
            cout << ">> " << buffer << endl;
            if(index > 0)
                print_related(trie, buffer, index);
        }
        else{
            cout << "Quitting..." << endl;
            break;
        }
    }
}
