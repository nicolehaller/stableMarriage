//Nicole Haller 
#include <iostream>
using namespace std;

void nextWoman(int q[], int &c);
void nextMan(int q[], int &c);
void backtrack(int q[], int &c);
void print(int cross[], int c);
bool ok(int q[], int c);

//checks if stable match
bool ok(int q[], int c){
        /* 
        0= highest preference
        1= intermediate preference
        2= lowest preference
        */

       //mans preferences
        int mp[3][3] = {
            //{woman 0, woman 1, woman 2}
            {0, 2, 1}, //mans 0's preferences
            {0, 2, 1}, //man 1's preferences
            {1, 2, 0}}; //man 2's preferences

        //womens preferences 
        int wp[3][3] = {
            //{man 0, man 1, man 2}
            {2, 1, 0}, //woman 0's prefrences
            {0, 1, 2}, //woman 1's preferences
            {2, 0, 1}}; //woman 2 preferences

    //make sure woman isnt already married 
    for (int i = 0; i < c; i++){
        if (q[c]==q[i]) return false;
    }

    int nm= c; //sets new man to be c
    //check for instabilities
    for (int previousMan=0; previousMan<nm; previousMan++){ //check previous pairings
        //check each pairing
        int newWoman= q[nm];
        int previousWoman= q[previousMan]; // to get previous woman, see who is paired with pm
            if (mp[previousMan][newWoman] < mp[previousMan][previousWoman] && wp[newWoman][previousMan] < wp[newWoman][nm]) return false; //check pm and nw preferences for current vs other match, check previous man with new woman -if each prefer eachother more than current match its instable
            if (mp[nm][previousWoman] < mp[nm][newWoman] && wp[previousWoman][nm] < wp[previousWoman][previousMan]) return false; //  check nm an pw preferences for current match vs other match, check new man and previous womans preferences
     }
     //if passes both tests, its a stable configuration
     return true;
} 


void nextMan(int q[], int &c) {
    c++; //go to next man
	if (c == 3) print (q,c); //no man 3 so found solution and print it
	else nextWoman(q, c); //if c is less than 3 check next woman with the man
}


void nextWoman(int q[], int &c) {
    q[c]++; //try new women 
    //if woman is 3 there was no stable match so backtrack
	if (q[c] == 3){ 
		backtrack(q,c);
	}
    //if stable match then move on to next man
	if (ok(q,c)) nextMan(q,c); 
    //if the pairing was not stable try the next woman 
    else nextWoman(q, c); 
}

void backtrack(int q[], int &c) {
    //reset woman so not at wrong match and then increase q[c] by one (ex: if q[c]=3 and dont reset then when gets to it it will increase to 4 which isnt right)
    q[c] = -1; 
    c--;
	if (c == -1) {
		exit(1); //if man is -1 we have found every configuration and are done 
	}
	nextWoman(q, c);
}

void print(int q[], int c){
    static int sol = 0;
    cout << "Solution#" << ++sol << ":\n";
    //print the pairings
    //c represents the current man, q[c] represents the woman paired with man c
    for (int i=0; i<3; i++){
        cout << "man " << i << " is paired with woman " << q[i] << ", "; 
    }
    cout<< endl; 
    backtrack(q,c);
}

int main() {
    //c represents man currently on, start at -1 because next man is next
    int q[3] = {-1, -1, -1}, c = -1;
	nextMan(q, c);
    return 0;
}