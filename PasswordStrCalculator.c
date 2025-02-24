#include <ncurses.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <stdlib.h>

#define digitRange 10
#define lowerRange 26
#define upperRange 26
#define specialRange 32
#define maxRange 94
#define maxInputLength 50

float entropy(char *password){
    int digit = 0;
    int lower = 0;
    int upper = 0;
    int special = 0;
    int passLength = (strlen(password));

    for(int i = 0; i<passLength ; i++){
        if(digit == 1 && lower == 1 && upper == 1 && special == 1){
            return passLength * (log(maxRange) / log(2));
        }else{
            if(islower(password[i])){
                lower = 1;
            }
            else if(isupper(password[i])){
                upper = 1;
            }
            else if(isdigit(password[i])){
                digit = 1;
            }
            else {
                special = 1;
            }
        }
    }
    float range = 0;
 
    if(digit == 1) range = range + digitRange;
    if(lower == 1) range = range + lowerRange;
    if(upper == 1) range = range + upperRange;
    if(special == 1) range = range + specialRange;
    
    return passLength * (log(range) / log(2));
}

int main(void){
    initscr();
    
    char ch = 0;
    int i = 0, x=0;
    char pass[51];
    float bits = 0;

    while(1){
    switch(x){
        case 1:
            clear();
            pass[0] = 0;
            bits = 0;
            i = 0;
            mvprintw(1,0,"-------------------------------------------------------------------------------");
            mvprintw(2,1,"!Your password has to be no longer than 50 characters!");
            mvprintw(3,1,"!What you are typing is visible so make sure that nobody can see your password!");
            mvprintw(4,0,"Write your password here:");
            mvprintw(6,0,"-------------------------------------------------------------------------------");
            move(5,0);
            curs_set(1);
            while((ch = getch()) != '\n' && i < maxInputLength){
                if(ch == '\b' || ch == 127){
                    if(i > 0){
                        i--;
                        move(5, i);
                        addch(' ');
                        move(5, i);
                    }
                }else{
                    pass[i] = ch;
                    i++;
                }
                refresh();
            }
            curs_set(0);

            pass[i] = 0;
            if(strlen(pass) < 1){
                break;
            }
            clear();
            bits = entropy(pass);
            mvprintw(1,0,"-------------------------------------------------------------------------------");
            if(bits < 35){
                mvprintw(2,0,"VERY WEAK - Your entropy is %.3f bits.", bits);
                mvprintw(3,0,"Someone could break your password in seconds / minutes.");
                mvprintw(4,0,"For tips on how to make it stronger check 'How does this work?'.");
            }
            else if(bits > 36 && bits < 59){
                mvprintw(2,0,"MEDIUM - Your entropy is %.3f bits.", bits);
                mvprintw(3,0,"Someone could break your password in minutes.");
                mvprintw(4,0,"For tips on how to make it stronger check 'How does this work?'.");
            }
            else if(bits > 60 && bits < 119){
                mvprintw(2,0,"STRONG - Your entropy is %.3f bits.", bits);
                mvprintw(3,0,"Someone could break your password in weeks / months.");
                mvprintw(4,0,"For tips on how to make it stronger check 'How does this work?'.");
            }
            else{
                mvprintw(2,0,"UNBREKABLE - Your entropy is %.3f bits.", bits);
                mvprintw(3,0,"Your password is almost impossible to crack with today's technology!");
                mvprintw(4,0,"CONGRATS");
            }
            mvprintw(5,0,"-------------------------------------------------------------------------------");
            mvprintw(6,0,"Press 0 to return to Main Menu.");
            noecho();
            while(1){
                ch = getch();
                if(ch == '0'){
                    x = 0;
                    break;
                }
            }
            echo();
            refresh();
            break;
        case 2:
            mvprintw(1,0,"-------------------------------------------------------------------------------");
            mvprintw(2,0,"The strength of a password is given by its entropy (randomness) but also by");
            mvprintw(3,0,"its length. Entropy is calculated by how many different characters it has");
            mvprintw(4,0,"(like lower/upper case letters, digits, special characters).");
            mvprintw(5,0,"If you want to create an unbreakable password, it must contain at least 1 lower");
            mvprintw(6,0,"case letter, 1 upper case letter, 1 digit, 1 special character but also a minimum");
            mvprintw(7,0,"of 18 characters for an entropy of 120+ bits");
            mvprintw(8,0,"GOOD LUCK!");
            mvprintw(9,0,"-------------------------------------------------------------------------------");
            mvprintw(10,0,"Press 0 to return to Main Menu.");
            noecho();
            while(1){
                ch = getch();
                if(ch == '0'){
                    x = 0;
                    break;
                }
            }
            echo();
            refresh();
            break;
        case 3:
            clear();
            refresh();
            endwin();
            return 0;
        default:
            clear();
            curs_set(0);
            mvprintw(1,0,"-----------------------------------------");
            mvprintw(2,0,"What's on the MENU:");
            mvprintw(3,0,"[1] I want to check my password strength.");
            mvprintw(4,0,"[2] How does this work?");
            mvprintw(5,0,"[3] EXIT");
            mvprintw(6,0,"-----------------------------------------");
            move(7,0);
            ch = getch();
            x = ch-'0';
            refresh();
            break;
    }
}
    endwin();
    return 0;
}
