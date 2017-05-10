#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu.h"

void menu(void) {
    int state, code;
    printf("\n%s\n", GRAPHIC);
    printf("|Choose a menu:\n");
    printf("| 1)Users\n");
    printf("| 2)MP3 files\n");
    printf("| 3)Database\n");
    printf("| 4)Purchase\n");
    printf("| 0)Exit\n");
    printf("\n%s\n", GRAPHIC);
    while((state=scanf("%d",&code))!=1 || (code<0||code>4)) {
        if(state!=1)scanf("%*s");
        printf("Choose an integer from 0 to 4.\n");
    }
    switch(code){
        case 1: menuUser(); break;
        case 2: menuMp3(); break;
        case 3: menuData(); break;
        case 4: menuPurch(); break;
        case 0: closing(); break;
    }
}
int menuUser(void) {
    int state, code;
    int i=0, j=0;
    printf("\n%s\n", GRAPHIC);
    printf("|Choose an action:\n");
    printf("| 1)Search an user\n");
    printf("| 2)Create new user\n");
    printf("| 3)Modify an user\n");
    printf("| 4)Delete an user\n");
    printf("| 5)Display all users\n");
    printf("| 0)Go back\n");
    printf("\n%s\n", GRAPHIC);
    while((state=scanf("%d",&code))!=1 || (code<0||code>5)){
        if(state!=1)scanf("%*s");
        printf("Choose an integer from 0 to 5.\n");
    }
    switch(code){
        case 1:
            if(searchUser(IDtemp, dataUser, MAXUSER)==0) puts("No results found.");
            else {
                printf("%s\n", USERHEAD);
                while(IDtemp[i]!=0 && i<MAXUSER) {
                    printUser(IDtemp[i]);
                    i++;
                }
                for(i=0;i<MAXUSER;i++) IDtemp[i]=0;
            }
            menuUser();
            break;
        case 2: newUser(); menuUser(); break;
        case 3: modifyUser(); menuUser(); break;
        case 4: deleteUser(); menuUser(); break;
        case 5:
            displayUser();
            for(i=0;i<MAXUSER;i++) IDtemp[i]=0;
            menuUser();
            break;
        default: menu();
    }
}
void menuMp3(void) {
    int state, code;
    int i=0, j=0;
    printf("\n%s\n", GRAPHIC);
    printf("|Choose an action:\n");
    printf("| 1)Search a mp3 file\n");
    printf("| 2)Create new mp3 file\n");
    printf("| 3)Modify a mp3 file\n");
    printf("| 4)Delete a mp3 file\n");
    printf("| 5)Display all mp3 files\n");
    printf("| 0)Go back\n");
    printf("\n%s\n", GRAPHIC);
    while((state=scanf("%d",&code))!=1 || (code<0||code>5)){
        if(state!=1)scanf("%*s");
        printf("Choose an integer from 0 to 5.\n");
    }
    switch(code){
        case 1:
            if (searchMp3(IDtemp, dataMp3, MAXMP3)==0)puts("No results found.");
            else {
                printf("%s\n", MP33HEAD);
                while(IDtemp[i]!=0 && i<MAXMP3) {
                    printMp3(IDtemp[i]);
                    i++;
                }
            }
            for(i=0;i<MAXMP3;i++) IDtemp[i]=0;
            menuMp3();
            break;
        case 2: newMp3(); menuMp3(); break;
        case 3: modifyMp3(); menuMp3(); break;
        case 4: deleteMp3(); menuMp3(); break;
        case 5:
            displayMp3();
            for(i=0;i<MAXMP3;i++) IDtemp[i]=0;
            menuMp3();
            break;
        default: menu();
    }
}
int menuData(void) {
    int state, code, ID;
    int i=0, j=0;
    printf("\n%s\n", GRAPHIC);
    printf("|Choose an action:\n");
    printf("| 1)Display users database\n");
    printf("| 2)Display mp3 files database\n");
    printf("| 3)Display list of directories\n");
    printf("| 4)Search a directory\n");
    printf("| 5)Display a directory\n");
    printf("| 6)Create new directory\n");
    printf("| 7)Delete a directory\n");
    printf("| 0)Go back\n");
    printf("\n%s\n", GRAPHIC);
    while((state=scanf("%d",&code))!=1 || (code<0||code>7)){
        if(state!=1)scanf("%*s");
        printf("Choose an integer from 0 to 7.\n");
    }
    switch(code){
        case 1:
            displayUser();
            for(i=0;i<MAXUSER;i++) IDtemp[i]=0;
            menuUser();
            break;
        case 2:
            displayMp3();
            for(i=0;i<MAXMP3;i++) IDtemp[i]=0;
            menuUser();
            break;
        case 3:
            puts("List of directories:");
            for(i=0;i<MAXDIR;i++)
                //if (dataDir[i].id !=0)
                    printf("%3d\t %s\n", dataDir[i].id, dataDir[i].name);
            menuData();
            break;
        case 4:
            if(searchDir(IDtemp, dataDir, MAXDIR)==0) puts("No results found.");
            else {
                puts("Found directories:");
                while(IDtemp[i]!=0 && i<MAXDIR) {
                    ID = IDtemp[i];
                    printf("%3d\t %s\n", dataDir[ID-1].id, dataDir[ID-1].name);
                    i++;
                }
                for(i=0;i<MAXUSER;i++) IDtemp[i]=0;
            }
            menuUser();
            break;
        case 5:
            printf("Enter directory's ID: ");
            while((state=scanf("%d",&ID))!=1 || (ID<1||ID>MAXDIR)){
                if(state!=1)scanf("%*s");
                printf("Choose an integer from 1 to %d.\n", MAXDIR);
            }
            if(checkIDDir(ID)==1){
                printDir(ID, dataDir, MAXDIR);
            }
            else puts("No directory's connected to this ID.");
            menuData();
            break;
        case 6: newDir(); menuData(); break;
        case 7: deleteDir(); menuData(); break;
        default: menu();
    }
}
int menuPurch(void) {
    int state, code;
    printf("\n%s\n", GRAPHIC);
    printf("|Choose an action:\n");
    printf("| 1)Add new purchase\n");
    printf("| 2)Delete an purchase\n");
    printf("| 0)Go back\n");
    printf("\n%s\n", GRAPHIC);
    while((state=scanf("%d",&code))!=1 || (code<0||code>2)){
        if(state!=1)scanf("%*s");
        printf("Choose an integer from 0 to 2.\n");
    }
    switch (code) {
        case 1: newPurch(); menuPurch(); break;
        case 2: deletePurch(); menuPurch(); break;
        default: menu();
    }
}
int closing() {
    char YN;
    int state;
    while(((state=scanf("%c",&YN))!=1) || ((YN!='Y')&&(YN!='N')&&(YN!='y')&&(YN!='n'))){
        if(state!=1)scanf("%*s");
        printf("Are you sure? Y/N\n");
    }
    if(YN=='Y'||YN=='y')exit(0);
    else menu();
}

