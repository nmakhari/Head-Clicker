#include <graphics.h>
#include <windows.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include <ctime>
#include <conio.h>
#include <cmath>
#include <stdio.h>
#include <cstdlib>
#include "header.h"
#include <fstream>

using namespace std;


int main(){

ofstream fout;

//be sure to enable winmm in the settings in order for sound to play
PlaySound("Halo Theme Song Original.wav", NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);

srand(time(NULL));//used for rng generation

POINT cursorPos;//mouse click point class

slope click;//slope struct to the click of the mouse

int hit;//represents which zombie the player has hit

int zombrad=20;//the radius of the zombie enemies

enemy zombie[8];//structure array for each zombie enemy

int numbersUsed[8]= {0};//integer array to prevent repeated numbers in rng spawn process

int spawnNum=3;//integer to represent how many zombie enemies are spawned each round

int zombcounter=0;//number of zombies alive

int spawnloc;//declared int variable for the rng spawn location between 0 and 7

int velocity=1;//velocity of the zombies

int round=1;//counts up the rounds survived

bool gameend=false;//checks and represents whether or not the player has lost

int i;//for loop counter

int width;//width and height variables to center text

int height;

char arr[2];//used for adding the integers to string using sprintf

int difficulty;//difficulty level inputed by user

int wait;//delay variable changes the difficulty of the game

int zdefeated=0;



initwindow(screenWidth, screenHeight, "Headclicker XTREME");
width=textwidth("Welcome to Headclicker XTREME");//use witdth and height variables to center the text on the screen
height=textheight("Welcome to Headclicker XTREME");
outtextxy(screenWidth/2-width/2, screenHeight/2-height/2, "Welcome to Headclicker XTREME");

width=textwidth("Input your desired difficulty");
height=textheight("Input your desired difficulty");
outtextxy(screenWidth/2-width/2, screenHeight/2-height/2+50, "Input your desired difficulty");

width=textwidth("3-> Hardest / 2->Medium / 1->Easy");
height=textheight("3-> Hardest / 2->Medium / 1->Easy");
outtextxy(screenWidth/2-width/2, screenHeight/2-height/2+100, "3-> Hardest / 2->Medium / 1->Easy");

while(!GetAsyncKeyState(' ')){//to take the input of difficulty between 1 & 3
    if(GetAsyncKeyState('1')){
    difficulty=1;
    break;
    }
    else if(GetAsyncKeyState('2')){
    difficulty=2;
    break;
    }
    else if(GetAsyncKeyState('3')){
    difficulty=3;
    break;
    }
}

if(difficulty==1){//assigns the related delay to the difficulty chosen, faster delay is more responsive but more difficult
    wait=250;
}
else if(difficulty==2){
    wait=150;
}
else if(difficulty==3){
    wait=100;
}
else{//to prevent bugs, if a number between 1 & 3 was some how inputed, the hardest delay is used to end the game quicker
    wait=100;
}

cleardevice();

width=textwidth("The instructions are as follows:");//same process as above to center text on screen for each line
height=textheight("The instructions are as follows:");
outtextxy(screenWidth/2-width/2, screenHeight/2-height-100, "The instructions are as follows:");
width=textwidth("Use your mouse and click on the zombies to remove them");
height=textheight("Use your mouse and click on the zombies to remove them");
outtextxy(screenWidth/2-width/2, screenHeight/2-height-50, "Use your mouse and click on the zombies to remove them");
width=textwidth("As the rounds progress, more and more zombies will spawn");
height=textheight("As the rounds progress, more and more zombies will spawn");
outtextxy(screenWidth/2-width/2, screenHeight/2-height/2, "As the rounds progress, more and more zombies will spawn");
width=textwidth("If a zombie reaches the inner circle, you lose");
height=textheight("If a zombie reaches the inner circle, you lose");
outtextxy(screenWidth/2-width/2, screenHeight/2-height/2+50, "If a zombie reaches the inner circle, you lose");
width=textwidth("Keep in mind, the click coordinates are actually on the bottom left of the cursor");
height=textheight("Keep in mind, the click coordinates are actually on the bottom left of the cursor");
outtextxy(screenWidth/2-width/2, screenHeight/2-height/2+100, "Keep in mind, the click coordinates are actually on the bottom left of the cursor");
width=textwidth("Ready?");
height=textheight("Ready?");
outtextxy(screenWidth/2-width/2, screenHeight/2-height/2+150, "Ready?");
width=textwidth("Press SPACE to start");
height=textheight("Press SPACE to start");
//outtextxy(screenWidth/2-width/2, screenHeight/2-height/2+250, "Press SPACE to start");

while(1){//loops while the user doesnt press space, flashing the message by changing betweeen white and black
setcolor(WHITE);
outtextxy(screenWidth/2-width/2, screenHeight/2-height/2+250, "Press SPACE to start");
delay(250);
setcolor(BLACK);
outtextxy(screenWidth/2-width/2, screenHeight/2-height/2+250, "Press SPACE to start");
delay(250);
if(GetAsyncKeyState(' ')){break;}
}

cleardevice();//once space is pressed, the game starts

for(round=1; round<9; round++){//counts up, restting each completed round

//below is the code for displaying the round, between rounds
cleardevice();
sprintf(arr, "Round %d", round);//converts round into string
width=textwidth(arr);//width and height to center the text
height=textheight(arr);
outtextxy(screenWidth/2-width/2, screenHeight/2-height/2, arr);//printing the round
delay(800);//delay to you can read the round

for(i=0;i<8;i++){//resets rng array
numbersUsed[i]=0;
}

if(round>6){}//at and after round 6 there can be no more zombies so do nothing

else if(round==1){
    spawnNum=3;//start with three zombies on round 1
}

else{spawnNum++;}//if its not round one, or after round 5 then increase the zombie spawn cound each time

resetbool(zombie);//sets all 'alive' structure members to false so rng spawn works

for (i=0; i<spawnNum; i++)
        {
            spawnloc=(rand() % 8);//generates random number
            if (numbersUsed[spawnloc]!=11)//if that number isnt used yet then set that zombie to alive and prevent it from being used again
            {
            zombie[spawnloc].alive=true;
            numbersUsed[spawnloc]=11;
            }

            else{//if the number is already in use
            while(numbersUsed[spawnloc]==11)
            {//keep generating until one thats not in use is found
                spawnloc=(rand() % 8);
            }
            numbersUsed[spawnloc]=11;//prevent new number from being used again
            zombie[spawnloc].alive=true;//set the new zombie to alive
            }

        }


         for (int y=0;y<8;y++){//prints the rng spawn array used to check bugs

            cout<<numbersUsed[y]<<endl;
        }

spawn(zombie, zombrad);//spawns the zombies randomly selected above

zombcounter=spawnNum;//the number of zombies alive is now equal to the number spawned

circle(screenWidth/2, screenHeight/2, 50);

    while(zombcounter>0){//while there are more than 0 zombies alive

        GetCursorPos(&cursorPos);
        if ((GetAsyncKeyState(VK_LBUTTON)))//if user clicks, run hit detection
        {

            hit=clickhitdetect(cursorPos, zombie, zombrad);//hit detection through click method
            if (hit>=0 && hit<=7){//if it returns a valid index

                zombie[hit].alive=false;//kill that zombie
                zombcounter--;//reduce counter of alive zombies
                zdefeated++;

            }
        }



    cleardevice();//clear the screen to print new enemy positions

    move(zombie, zombrad, velocity);//zombies moved towards center

    circle(screenWidth/2, screenHeight/2, 50);//inner circle being drawn

    readimagefile("mccree.jpg", screenWidth/2-32,screenHeight/2-32,screenWidth/2+32,screenHeight/2+32);//puts jpeg in the game

    setcolor(WHITE);//filling the middle circle white
    floodfill(screenWidth/2-33,screenHeight/2-33, WHITE);
    floodfill(screenWidth/2-33,screenHeight/2-33, WHITE);

    delay(wait);//delay to make game easier,represents difficulty level, without it due to the graphics engine used the game would be impossible

            if ((GetAsyncKeyState(VK_LBUTTON)))//same hit detection as above, again in the same loop to make it easier to land clicks before they move again
        {
            click=calculation(cartesian(screenWidth/2,screenHeight/2,cursorPos.x,cursorPos.y));


            hit=clickhitdetect(cursorPos, zombie, zombrad);//hit detection through click method
            if (hit>=0 && hit<=7){//if it returns a valid index

                zombie[hit].alive=false;//kill that zombie
                zombcounter--;//reduce counter of alive zombies
                zdefeated++;

            }
        }

    if (gameover(zombie,zombrad)==true)//if a zombie has reached the inner circle, the game is over
    {
        gameend=true;
        break;
    }


    }

    if(gameend==true){//if the player has lost, stop producing more rounds
    cleardevice();
    width=textwidth("You have been PENALIZED");
    height=textheight("You have been PENALIZED");
    outtextxy(screenWidth/2-width/2, screenHeight/2-height/2, "You have been PENALIZED");
    width=textwidth("Press SPACE to exit");
    height=textheight("Press SPACE to exit");

    while(1){//flashes the press space to exit message
        setcolor(WHITE);
        outtextxy(screenWidth/2-width/2, screenHeight/2-height/2+250, "Press SPACE to exit");
        delay(250);
        setcolor(BLACK);
        outtextxy(screenWidth/2-width/2, screenHeight/2-height/2+250, "Press SPACE to exit");
        delay(250);
        if(GetAsyncKeyState(' ')){break;}
        }
    //while the user hasnt clicked space keep the screen open
    break;
    }
}
if(gameend==false){
    cleardevice();
    width=textwidth("You got POGALIZED");
    height=textheight("You got POGALIZED");
    outtextxy(screenWidth/2-width/2, screenHeight/2-height/2, "You got POGALIZED");
    width=textwidth("Press SPACE to exit");
    height=textheight("Press SPACE to exit");
while(1){//flashes the press space to exit message
setcolor(WHITE);
outtextxy(screenWidth/2-width/2, screenHeight/2-height/2+250, "Press SPACE to exit");
delay(250);
setcolor(BLACK);
outtextxy(screenWidth/2-width/2, screenHeight/2-height/2+250, "Press SPACE to exit");
delay(250);
if(GetAsyncKeyState(' ')){break;}
}//while the user hasnt clicked space keep the screen open


}

if(gameend==true){
fout.open("results.txt");
fout<<"You defeated "<<zdefeated<<" zombies and survived "<<round-1<<" rounds on difficulty "<<difficulty<<".";
fout.close();
}
else if(gameend==false){
fout.open("results.txt");
fout<<"You defeated "<<zdefeated<<" zombies and survived "<<round-1<<" rounds on difficulty "<<difficulty<<" and won the game.";
fout.close();
}

getch();
closegraph();




return 0;
}


slope calculation(POINT coordinate){//returns the slope to any coordinate on the screen from the middle (0,0) cartesian
slope answer;
int ycar, xcar;
ycar=coordinate.y;//takes inputs from struct for calculation
xcar=coordinate.x;
answer.rise=coordinate.y;//since the middle is always (0,0) the rise and run are always their respective coordinates
answer.run=coordinate.x;
answer.ror=(ycar*1.0/xcar);//assigns a slope to the rise over run parameter
//if both rise and run are negative the slope will be positive but we can determine direction by looking at them individually
return answer;
}

POINT cartesian(int midx, int midy, int x, int y){//converts any screen coordinate to cartesian coordinates
POINT answer;
int ycar, xcar;//variables so converting to struct is easier

if(x<midx){//if the click input is to the left of middle then its negative so subtract to get cartesian coordinate
    xcar=x-midx;
}
else if(x>midx){//if click input is to the right of middle then its positive so keep subtract to get cartesian coordinate
    xcar=x-midx;
}
else if(x==midx){
    xcar=0;
}

if(y>midy){//if the y click input is below the middle then subtract and multiply by -1 to get a negative cartesian coordinate
    ycar=(y-midy)*-1;
}
else if(y<midy){//if the y click is above, do the same but this time itll yeild a positve y cartesian
    ycar=(y-midy)*-1;
}
else if(y==midy){
    ycar=0;
}

answer.x=xcar;//sets the point x parameter to the cartesian x equivalent of the input
answer.y=ycar;//does the same for y
return answer;//returns the point struct answer


}

void spawn (enemy a[], int zrad){//spawns the zombies on the screen, takes the enemy struct array, where the randomly selected ones have alive=true

    slope direction;
    int reduce;

    for (int i=0; i<8; i++){//runs through array

        if (a[i].alive==true){//if its alive=true

            if (i==0){//inputs the required information to the enemy structure depending on the index

                direction=calculation(cartesian(screenWidth/2, screenHeight/2, screenWidth-zrad, zrad));
                reduce=gcd(direction.rise, direction.run);
                a[i].rise=direction.rise/(reduce*2);//here the rise and run are reduced to be more playable and less choppy while maintaing same direction
                a[i].run=(direction.run*-1)/(reduce*2);
                a[i].xpos=screenWidth-zrad;
                a[i].ypos=zrad;
                circle(screenWidth-zrad, zrad, zrad);

                cout<<direction.ror<<endl;
            }
            else if (i==1){

                direction=calculation(cartesian(screenWidth/2, screenHeight/2, screenWidth/2, zrad));
                a[i].rise=10;
                a[i].run=0;
                a[i].xpos=screenWidth/2;
                a[i].ypos=zrad;
                circle(screenWidth/2, zrad, zrad);
            }
             else if (i==2){

                direction=calculation(cartesian(screenWidth/2, screenHeight/2,zrad, zrad));
                reduce=gcd(direction.rise, direction.run);
                a[i].rise=direction.rise/(reduce*2);
                a[i].run=(direction.run*-1)/(reduce*2);
                a[i].xpos=zrad;
                a[i].ypos=zrad;
                circle(zrad, zrad, zrad);

                cout<<direction.ror<<endl;

            }
            else if (i==3){

                direction=calculation(cartesian(screenWidth/2, screenHeight/2, zrad, screenHeight/2));
                a[i].rise=0;
                a[i].run=10;
                a[i].xpos=zrad;
                a[i].ypos=screenHeight/2;
                circle(zrad, screenHeight/2, zrad);
            }
            else if (i==4){

                direction=calculation(cartesian(screenWidth/2, screenHeight/2, zrad, screenHeight-zrad));
                reduce=gcd(direction.rise, direction.run);
                a[i].rise=direction.rise/(reduce*2);
                a[i].run=(direction.run*-1)/(reduce*2);
                a[i].xpos=zrad;
                a[i].ypos=screenHeight-zrad;
                circle(zrad, screenHeight-zrad, zrad);

                cout<<direction.ror<<endl;
            }
            else if (i==5){

                direction=calculation(cartesian(screenWidth/2, screenHeight/2, screenWidth/2, screenHeight-zrad));
                a[i].rise=-10;
                a[i].run=0;
                a[i].xpos=screenWidth/2;
                a[i].ypos=screenHeight-zrad;
                circle(screenWidth/2, screenHeight-zrad, zrad);
            }
            else if (i==6){

                direction=calculation(cartesian(screenWidth/2, screenHeight/2, screenWidth-zrad, screenHeight-zrad));
                reduce=gcd(direction.rise, direction.run);
                a[i].rise=direction.rise/(reduce*2);
                a[i].run=(direction.run*-1)/(reduce*2);
                a[i].xpos=screenWidth-zrad;
                a[i].ypos=screenHeight-zrad;
                circle(screenWidth-zrad, screenHeight-zrad, zrad);

                cout<<direction.ror<<endl;
            }
            else if (i==7){

                direction=calculation(cartesian(screenWidth/2, screenHeight/2, screenWidth-zrad, screenHeight/2));
                a[i].rise=0;
                a[i].run=-10;
                a[i].xpos=screenWidth-zrad;
                a[i].ypos=screenHeight/2;
                circle(screenWidth-zrad, screenHeight/2, zrad);
            }
        }
    }
}

void resetbool(enemy a[]){//sets all 'alive' structure members to false, so rng spawn works
    for (int i=0;i<8;i++){
    a[i].alive=false;//make all zombies dead to start
    }

}


void move(enemy a[],int zrad, int velocity){//adds the rise and run kept in the enemy structure to the current pos of alive zombies


for (int i=0; i<8; i++){

        if (a[i].alive==true){//only move if its alive
                a[i].xpos += (a[i].run*velocity);//add rise and run to current pos to move towards center
                a[i].ypos += (a[i].rise*velocity);
                circle(a[i].xpos, a[i].ypos, zrad);

                }
    }

}

int gcd(int x, int y){//function used to effectively reduce the rise and run of the slope from the corners to make game more playable while maintaining their direction
int px, py;//positive x and positive y
px=abs(x);//abs function to assign the x and y as positive regardless of the sign
py=abs(y);
int count=0;//counts the number of reps the function has successfully completed
    int i=1, answer;
        for(i=2; i<px && i<py && count<20; i++){//finds the 20th occurence of the reduction factor, making a small rise and run but keeping the slope
            if(px%i==0 && py%i==0){
                answer=i;
                count++;
            }
        }
        return answer;//once the runs are completed the answer is returned
}

int clickhitdetect(POINT click, enemy a[], int zrad){//checks if the player clicks within a zombie
int i=0;

for(i=0; i<8; i++){//goes through each zombie

    if(a[i].alive==true){//checks if its alive, if its not then it cant be hit

        if(click.x > (a[i].xpos - zrad) && click.x < (a[i].xpos + zrad)){//if the x coordinate of click is within the x of the zombie

            if(click.y >(a[i].ypos - zrad) && click.y < (a[i].ypos + zrad)){//if the y coordinate of the click is within the y of the zombie
                return i;//if both are true then return which zombie it hit
            }
        }
    }
}
return 9;
}

bool gameover(enemy a[], int zrad){//checks if the game is over
    int xdifference;
    int ydifference;
    int answer;

    for(int i=0; i<8; i++)
    {//goes through each zombie

    if(a[i].alive==true){//checks if its alive, if its not then it cant be hit
    xdifference=screenWidth/2-a[i].xpos;//if the distance between the center and the middle of the zombie is less than the sum of their radii its in the inner circle
    ydifference=screenHeight/2-a[i].ypos;
    answer=sqrt((xdifference*xdifference)+(ydifference*ydifference));

    if (answer<50+zrad)
    {
        return true;
    }

    }
    }
    return false;//if true wasnt returned in the loop, there is no gameover
    }


//below is the old slope hit detection method, which unfortunately wasnt used
/*int hitdetect(POINT coordinate, int xmax, int ymax, slope equation, int zrad, int brad){
slope parameter[16];

int xr, xl;//right and left most coordinates for zones 2 and 6
xr=xmax/2-zrad-brad;//calculating right and left most x coordinats for zones 2 and 6
xl=xmax/2+zrad+brad;

int yt, yb;//topmost and bottommost coordinates for zones 4 and 8
yt=ymax/2-zrad-brad;
yb=ymax/2+zrad+brad;

//calculating all the slopes for comparison
parameter[0]=calculation(cartesian(xmax/2, ymax/2, xmax, 14));//the slope to the bottom part of zone one corner
parameter[1]=calculation(cartesian(xmax/2, ymax/2, xmax-14, 0));//the slope to the top part of zone one corner
parameter[2]=calculation(cartesian(xmax/2, ymax/2, xr, 0));//slope to the right most x of zone 2
parameter[3]=calculation(cartesian(xmax/2, ymax/2, xl, 0));//slope to the left most x of zone 2
parameter[4]=calculation(cartesian(xmax/2, ymax/2, 14, 0));//slope to the top part of zone 3
parameter[5]=calculation(cartesian(xmax/2, ymax/2, 0, 14));//slope to the bottom part of zone 3
parameter[6]=calculation(cartesian(xmax/2, ymax/2, 0, yt));//slope to the top most y of zone 4
parameter[7]=calculation(cartesian(xmax/2, ymax/2, 0, yb));//slope to the bottom most y of zone 4
parameter[8]=calculation(cartesian(xmax/2, ymax/2, 0, ymax-14));//slope to top part of zone 5 corner
parameter[9]=calculation(cartesian(xmax/2, ymax/2, 14, ymax));//slope to the bottom part of zone 5 corner
parameter[10]=calculation(cartesian(xmax/2, ymax/2, xl, ymax));//slope to the left most x of zone 6
parameter[11]=calculation(cartesian(xmax/2, ymax/2, xr, ymax));//slope to the right most x of zone 6
parameter[12]=calculation(cartesian(xmax/2, ymax/2, xmax-14, ymax));//the slope to the bottom part of zone 7 corner
parameter[13]=calculation(cartesian(xmax/2, ymax/2, xmax, ymax-14));//the slope to the top part of zone 7 corner
parameter[14]=calculation(cartesian(xmax/2, ymax/2, xmax, yb));//slope to the bottom most y of zone 8
parameter[15]=calculation(cartesian(xmax/2, ymax/2, xmax, yt));//slope to the top most y of zone 8



if(equation.ror>=parameter[14].ror && equation.ror<=parameter[15].ror && equation.run>0){//if the input slope is in zone 8
return 8;
}

if(equation.ror>=parameter[6].ror && equation.ror<=parameter[7].ror && equation.run<0){//if the input slope is in zone 4
return 4;
}

if((equation.ror>=parameter[3].ror && equation.ror>=parameter[2].ror && equation.rise>0) || (equation.run=0 && equation.rise>0)){//if the input slope is in zone 2
return 2;
}

if((equation.ror>=parameter[11].ror && equation.ror>=parameter[10].ror && equation.rise<0)|| (equation.run=0 && equation.rise<0)){//if the input slope is in zone 6
return 6;
}

if(equation.ror>=parameter[0].ror && equation.ror<=parameter[1].ror && coordinate.x>0 && coordinate.y>0){//input slope in zone 1
return 1;
}

if(equation.ror>=parameter[4].ror && equation.ror<=parameter[5].ror && equation.run<0 && equation.rise>0){//input slope in zone 3
return 3;
}

if(equation.ror>=parameter[8].ror && equation.ror<=parameter[9].ror && coordinate.x<0 && coordinate.y<0){//input slope in zone 5
return 5;
}

if(equation.ror>=parameter[12].ror && equation.ror<=parameter[13].ror && equation.run>0 && equation.rise<0){//input slope in zone 7
return 7;
}

}*/
