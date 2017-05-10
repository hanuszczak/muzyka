#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu.h"

void scanLine(int dim, char tab[]){
    int ch, index;
    getchar();
    for(index=0;((ch=getchar())!='\n')&&(ch!=EOF);index++) {
        if (index<dim-1) {
            tab[index]=(char) ch;
            tab[index+1]='\0';
        }
    }
}
void printUser (int ID){
    int i, j;
    for(i=0; i<MAXUSER; i++) {
        if(dataUser[i].id==ID) {
            printf("| %7d\t%15s\t%32s\tOwned mp3 files:\n", dataUser[i].id, dataUser[i].name, dataUser[i].surname);
            for(j=0; j<MAXPURCH; j++)
                if(dataUser[i].mp3files[j]!=0)
                printf("| \t%78d\n",dataUser[i].mp3files[j]);
        }
    }
}
void printMp3(int ID){
    int i, j;
    for(i=0; i<MAXMP3; i++) {
        if(dataMp3[i].id==ID) {
            printf("| %7d\t%30s\t%30s\t%30s\t%15s\t\tOwners:\n", dataMp3[i].id, dataMp3[i].title, dataMp3[i].artist, dataMp3[i].album, dataMp3[i].genre);
            for(j=0; j<MAXPURCH; j++)
                if(dataMp3[i].owners[j]!=0)
                printf("| \t%136d\n",dataMp3[i].owners[j]);
        }
    }
}
void printDir (int ID, DIR tab[], int N) {
    int i, j;
    for(i=0; i<N; i++){
        if(tab[i].id==ID) {
            printf("| Directory's name: %s\n", tab[i].name);
            if (tab[i].type=='u'||tab[i].type=='U') {
                puts("| Type of file: users");
                puts("| Content:");
                printf("%s\n", USERHEAD);
                for(j=0; j<MAXINDIR; j++)
                    if(tab[i].contentId[j]!=0)
                        printUser(j+1);
            }
            else {
                puts("| Type of file: Mp3 files");
                puts("| Content:");
                printf("%s\n", MP33HEAD);
                for(j=0; j<MAXINDIR; j++)
                    if(tab[i].contentId[j]!=0)
                        printMp3(j+1);
            }
        }
    }
}
int checkIDinDIR(int i, int ID, DIR tab[], int N) { // i - directory's ID-1, N - number of elements in directory
    int j=0, state=0;
    for (j=0;j<N; j++)
        if(tab[i].contentId[j]==ID) state=1;
    return state;
}
int checkIDUser(int ID, USER tab[], int N){
    int i=0, state=0;
    for (i=0; i<N; i++)
        if(tab[i].id==ID) state=1;
    return state;
}
int checkIDMp3(int ID, MP3 tab[], int N){
    int i=0, state=0;
    for (i=0; i<N; i++)
        if(tab[i].id==ID) state=1;
    return state;
}
int checkIDDir(int ID){
    int i=0, state=0;
    for (i=0; i<MAXDIR; i++)
        if(dataDir[i].id==ID) state=1;
    return state;
}
void modifyUser () {
    puts("Enter user's ID");
    int ID;
    scanf("%d", &ID);
    printf("Enter new user's name (max 14 characters):\n");
    scanf("%s", dataUser[ID-1].name);
    printf("Enter new user's surname (max 31 characters):\n");
    scanf("%s", dataUser[ID-1].surname);
    printf("\n%s\n",USERHEAD);
    printUser(ID);
    menuUser();
}
void modifyMp3 () {
    puts("Enter mp3 file's ID");
    int ID;
    scanf("%d", &ID);
    printf("Enter new mp3's title (max 29 characters):\n");
    scanf("%s", dataMp3[ID-1].title);
    printf("Enter new mp3's artist (max 29 characters):\n");
    scanf("%s", dataMp3[ID-1].artist);
    printf("Enter new mp3's album (max 29 characters):\n");
    scanf("%s", dataMp3[ID-1].album);
    printf("Enter new mp3's genre (max 14 characters):\n");
    scanf("%s", dataMp3[ID-1].genre);
    printf("\n%s\n",MP33HEAD);
    printMp3(ID);
    menuMp3();
}
int searchUser (int IDtab[], USER tab[], int N) {
    int i=0, j=0, k=0, found=0;
    int state, code, ID;
    char phrase[32];
    printf("\n%s\n", GRAPHIC);
    printf("|Search an user:\n");
    printf("| 1)by ID\n");
    printf("| 2)by name\n");
    printf("| 3)by surname\n");
    printf("| 4)by owned song\n");
    printf("| 0)cancel\n");
    printf("\n%s\n", GRAPHIC);
    while((state=scanf("%d",&code))!=1 || (code<0||code>4)){
        if(state!=1)scanf("%*s");
        printf("Choose an integer from 0 to 4.\n");
    }
    switch(code){
        case 1:
            printf("Enter an ID: ");
            while((state=scanf("%d",&ID))!=1 || (ID<1||ID>MAXUSER)){
                if(state!=1)scanf("%*s");
                printf("Choose an integer from 1 to %d.\n", MAXUSER);
            }
            for (i=0; i<N; i++) {
                if (ID==tab[i].id) {
                    IDtab[k++]=tab[i].id;
                    found = 1;
                }
            }
            break;
        case 2:
            printf("Enter name: ");
            while((state=scanf("%s",&phrase))!=1){
                if(state!=1)scanf("%*s");
                printf("Wrong input. Try again.\n");
            }
            for (i=0; i<N; i++) {
                if (stricmp(tab[i].name, phrase)== 0) {
                    IDtab[k++]=tab[i].id;
                    found = 1;
                }
            }
            break;
        case 3:
            printf("Enter surname: ");
             while((state=scanf("%s",&phrase))!=1){
                if(state!=1)scanf("%*s");
                printf("Wrong input. Try again.\n");
            }
            for (i=0; i<N; i++) {
                if (stricmp(tab[i].surname, phrase)== 0) {
                    IDtab[k++]=tab[i].id;
                    found = 1;
                }
            }
            break;
        case 4:
            printf("Enter song's ID: ");
            while((state=scanf("%d",&ID))!=1 || (ID<1||ID>MAXMP3)){
                    if(state!=1)scanf("%*s");
                    printf("Choose an integer from 1 to %d.\n", MAXMP3);
                }
                for (i=0; i<N; i++) {
                    for (j=0; j<MAXPURCH; j++) {
                        if (ID==tab[i].mp3files[j]) {
                    IDtab[k++]=tab[i].id;
                    found = 1;
                }
                    }
                }
            break;
        case 5: break;
        default: menu();
    }
    return found;
}
int searchMp3 (int IDtab[], MP3 tab[], int N) {
    int i=0, j=0, k=0, found=0;
    int state, code, ID;
    char phrase[32];
    printf("\n%s\n", GRAPHIC);
    printf("|Search a mp3 file:\n");
    printf("| 1)by ID\n");
    printf("| 2)by title\n");
    printf("| 3)by artist\n");
    printf("| 4)by album\n");
    printf("| 5)by genre\n");
    printf("| 6)by owner\n");
    printf("| 0)cancel\n");
    printf("\n%s\n", GRAPHIC);
    while((state=scanf("%d",&code))!=1 || (code<0||code>6)){
        if(state!=1)scanf("%*s");
        printf("Choose an integer from 0 to 6.\n");
    }
    switch(code){
        case 1:
            printf("Enter an ID: ");
            while((state=scanf("%d",&ID))!=1 || (ID<1||ID>MAXMP3)){
                if(state!=1)scanf("%*s");
                printf("Choose an integer from 1 to %d.\n", MAXMP3);
            }
            for (i=0; i<N; i++) {
                if (ID==tab[i].id) {
                    IDtab[k++]=tab[i].id;
                    found = 1;
                }
            }
            break;
        case 2:
            printf("Enter title: ");
            while((state=scanf("%s",&phrase))!=1){
                if(state!=1)scanf("%*s");
                printf("Wrong input. Try again.\n");
            }
            for (i=0; i<N; i++) {
                if (stricmp(tab[i].title, phrase)== 0) {
                    IDtab[k++]=tab[i].id;
                    found = 1;
                }
            }
            break;
        case 3:
            printf("Enter artist: ");
             while((state=scanf("%s",&phrase))!=1){
                if(state!=1)scanf("%*s");
                printf("Wrong input. Try again.\n");
            }
            for (i=0; i<N; i++) {
                if (stricmp(tab[i].artist, phrase)== 0) {
                    IDtab[k++]=tab[i].id;
                    found = 1;
                }
            }
            break;
        case 4:
            printf("Enter album: ");
             while((state=scanf("%s",&phrase))!=1){
                if(state!=1)scanf("%*s");
                printf("Wrong input. Try again.\n");
            }
            for (i=0; i<N; i++) {
                if (stricmp(tab[i].album, phrase)== 0) {
                    IDtab[k++]=tab[i].id;
                    found = 1;
                }
            }
            break;
        case 5:
            printf("Enter genre: ");
             while((state=scanf("%s",&phrase))!=1){
                if(state!=1)scanf("%*s");
                printf("Wrong input. Try again.\n");
            }
            for (i=0; i<N; i++) {
                if (stricmp(tab[i].genre, phrase)== 0) {
                    IDtab[k++]=tab[i].id;
                    found = 1;
                }
            }
            break;
        case 6:
            printf("Enter owner's ID: ");
            while((state=scanf("%d",&ID))!=1 || (ID<1||ID>MAXUSER)){
                    if(state!=1)scanf("%*s");
                    printf("Choose an integer from 1 to %d.\n", MAXUSER);
                }
                for (i=0; i<N; i++) {
                    for (j=0; j<MAXPURCH; j++) {
                        if (ID==tab[i].owners[j]) {
                            IDtab[k++]=tab[i].id;
                            found = 1;
                        }
                    }
                }
            break;
        case 0: break;
        default: menu();
    }
    return found;
}
int searchDir (int IDtab[], DIR tab[], int N) {
    int i=0, j=0, k=0, found=0;
    int state, code, ID;
    char phrase[32], type;
    printf("\n%s\n", GRAPHIC);
    printf("|Search a directory:\n");
    printf("| 1)by ID\n");
    printf("| 2)by name\n");
    printf("| 3)by type\n");
    printf("| 4)by user's ID\n");
    printf("| 5)by mp3 file's ID\n");
    printf("| 0)cancel\n");
    printf("\n%s\n", GRAPHIC);
    while((state=scanf("%d",&code))!=1 || (code<0||code>6)){
        if(state!=1)scanf("%*s");
        printf("Choose an integer from 0 to 6.\n");
    }
    switch(code){
        case 1:
            printf("Enter an ID: ");
            while((state=scanf("%d",&ID))!=1 || (ID<1||ID>MAXDIR)){
                if(state!=1)scanf("%*s");
                printf("Choose an integer from 1 to %d.\n", MAXDIR);
            }
            for (i=0; i<N; i++) {
                if (ID==tab[i].id) {
                    IDtab[k++]=tab[i].id;
                    found = 1;
                }
            }
            break;
        case 2:
            printf("Enter directory's name: ");
            while((state=scanf("%s",&phrase))!=1){
                if(state!=1)scanf("%*s");
                printf("Wrong input. Try again.\n");
            }
            for (i=0; i<N; i++) {
                if (stricmp(tab[i].name, phrase)== 0) {
                    IDtab[k++]=tab[i].id;
                    found = 1;
                }
            }
            break;
        case 3:
            printf("Enter a type: U - users, M - mp3 files");
            while(((state=scanf("%c",&type))!=1) || ((type!='U')&&(type!='u')&&(type!='M')&&(type!='m'))){
                if(state!=1)scanf("%*s");
                printf("Enter \"U\" or \"M\".\n");
            }
            for (i=0; i<N; i++) {
                if (tab[i].type==type||tab[i].type==type+32) {
                    IDtab[k++]=tab[i].id;
                    found = 1;
                }
            }
            break;
        case 4:
            printf("Enter user's ID: ");
            while((state=scanf("%d",&ID))!=1 || (ID<1||ID>MAXUSER)){
                if(state!=1)scanf("%*s");
                printf("Choose an integer from 1 to %d.\n", MAXUSER);
            }
            for (i=0; i<N; i++) {
                for (j=0; j<MAXINDIR; j++) {
                    if (ID==tab[i].contentId[j]) {
                        IDtab[k++]=tab[i].id;
                        found = 1;
                    }
                }
            }
            break;
        case 5:
            printf("Enter mp3 file's ID: ");
            while((state=scanf("%d",&ID))!=1 || (ID<1||ID>MAXMP3)){
                if(state!=1)scanf("%*s");
                printf("Choose an integer from 1 to %d.\n", MAXMP3);
            }
            for (i=0; i<N; i++) {
                for (j=0; j<MAXINDIR; j++) {
                    if (ID==tab[i].contentId[j]) {
                        IDtab[k++]=tab[i].id;
                        found = 1;
                    }
                }
            }
            break;
    }
}
void newUser() {
    int i=0, j=0;
    while(dataUser[i].id!=0 || i>=MAXUSER)i++; //value of id in empty row is 0.
    if (i>=MAXUSER) {
            puts("User database is full");
            menuUser();
    }
    else {
        dataUser[i].id=(i+1); //numbers of ID - from 1 to MAXUSER
        printf("Enter user's name (max 14 characters):\n");
        scanf("%s", dataUser[i].name);
        printf("Enter user's surname (max 31 characters):\n");
        scanf("%s", dataUser[i].surname);
        for(j=0; j<MAXPURCH; j++) dataUser[i].mp3files[j]=0;
        printf("\n%s\n",USERHEAD);
        printUser(i+1);
    }
    menuUser();
}
void newMp3() {
    int i=0, j=0;
    while(dataMp3[i].id!=0 || i>=MAXMP3)i++; //value of id in empty row is 0.
    if (i>=MAXMP3) {
            puts("MP3 database is full");
            menuMp3();
    }
    else {
        dataMp3[i].id=(i+1); //number of ID - from 1 to MAXMP3
        printf("Enter mp3's title (max 31 characters):\n");
        scanf("%s", dataMp3[i].title);
        printf("Enter mp3's artist (max 31 characters):\n");
        scanf("%s", dataMp3[i].artist);
        printf("Enter mp3's album (max 31 characters):\n");
        scanf("%s", dataMp3[i].album);
        printf("Enter mp3's genre (max 14 characters):\n");
        scanf("%s", dataMp3[i].genre);
        for(j=0; j<MAXPURCH; j++) dataMp3[i].owners[j]=0;
        printf("\n%s\n", MP33HEAD);
        printMp3(i+1);
    }
    menuMp3();
}
void deleteUser (){
    puts("Enter user's ID");
    int j, ID, i, k;
    scanf("%d", &ID);
    dataUser[ID-1].id=0;
    for(j=0; j<MAXPURCH; j++) dataUser[ID-1].mp3files[j]=0;
    for(i=0; i<MAXMP3; i++)
        for(k=0; k<MAXPURCH; k++)
            if(dataMp3[i].owners[k]==ID) dataMp3[i].owners[k]=0;
    puts("User deleted");
    menuUser();
}
void deleteMp3 (){
    puts("Enter mp3 file's ID");
    int j, ID, i, k;
    scanf("%d", &ID);
    dataMp3[ID-1].id=0;
    for(j=0; j<MAXPURCH; j++) dataMp3[ID-1].owners[j]=0;
    for(i=0; i<MAXUSER;i++)
        for(k=0; k<MAXPURCH;k++)
            if(dataUser[i].mp3files[k]==ID) dataUser[i].mp3files[k]=0;
    puts("Mp3 file deleted");
    menuMp3();
}
void newDir() {
    int i=0, j=0, k=0;
    int state, ID;
    while(dataDir[i].id!=0 || i>=MAXDIR)i++; //value of id in empty row is 0.
    if (i>=MAXDIR) {
            puts("You cannot create new directory. Database full.");
            menuData();
    }
    else {
        dataDir[i].id=(i+1); //numbers of ID - from 1 to MAXDIR
        for (k=0;k<MAXINDIR;k++){
            dataDir[i].contentId[k]=0; //for start all content in new directory is set on 0 (empty positions in new directory)
        }
        puts("Enter directory's name (max 14 characters).");
        scanLine(15,dataDir[i].name);
        puts("Enter a type of data: U - users, M - mp3files");
        char type;
        while(((state=scanf("%c",&type))!=1) || ((type!='U')&&(type!='u')&&(type!='M')&&(type!='m'))){
            if(state!=1)scanf("%*s");
            printf("Enter \"U\" or \"M\".\n");
        }
        int maxID;
        if (type == 'u'||type == 'U') {
            maxID = MAXUSER;
            dataDir[i].type='U';
        }
        else {
            maxID = MAXMP3;
            dataDir[i].type='M';
        }
        puts("Enter data's IDs (max 100 elements) or 0 to exit.");
        while (1) {
            if ((state=scanf("%d",&ID))!=1||(ID<0||ID>maxID)) {
                if (state!=1){
                    scanf("%*s");
                }
            printf("Invalid ID. Please enter an integer from 1 to %d or 0 to exit\n", maxID);
            continue;
            }
            else if (ID==0) break;
            else {
                if (type == 'u'||type == 'U'){
                    if(checkIDUser(ID, dataUser, MAXUSER)==0){
                        puts("There is no user connected to that ID. Try again or enter 0 to cancel.");
                        continue;
                    }
                    else if (checkIDinDIR(i, ID, dataDir, MAXINDIR)==1){
                        puts("User connected to this ID is already in this directory. Try another ID or enter 0 to cancel.");
                        continue;
                    }
                    else {
                        while(dataDir[i].contentId[j]!=0 || j>=MAXINDIR)j++;
                        if (j==MAXINDIR){
                            puts("Directory is full. You cannot put more data.");
                            j=0;
                            break;
                        }
                        else {
                            dataDir[i].contentId[j]=ID;
                            continue;
                        }
                    }
                }
                else {
                    if(checkIDMp3(ID, dataMp3, MAXMP3)==0){
                        puts("There is no user connected to that ID. Try again or enter 0 to cancel");
                        continue;
                    }
                    else if (checkIDinDIR(i, ID, dataDir, MAXINDIR)==1){
                        puts("Mp3 file connected to this ID is already in this directory. Try another ID or enter 0 to cancel.");
                        continue;
                    }
                    else {
                        while(dataDir[i].contentId[j]!=0 || j>=MAXINDIR)j++;
                        dataDir[i].contentId[j]=ID;
                        if (j=MAXINDIR){
                            puts("Directory is full. You cannot put more data.");
                            j=0;
                            break;
                        }
                        else {
                            dataDir[i].contentId[j]=ID;
                            continue;
                        }
                    }
                }
            }
        }
    }
    menuData();
}
void deleteDir(){
    puts("Enter directory's ID");
    int ID;
    scanf("%d", &ID);
    dataDir[ID-1].id=0;
    puts("Directory deleted");
    menuData();
}
void newPurch() {
    int IDUser, IDmp3, state, code;
    int i=0, j=0;
    puts("Enter user's ID.");
    while(1){
        if ((state=scanf("%d",&IDUser))!=1 || (IDUser<0||IDUser>MAXUSER)){
            if(state!=1) {
                scanf("%*s");
            }
            printf("Invalid ID. Choose an integer from 1 to %d.\n", MAXUSER);
            continue;
        }
        else if (IDUser==0) menuPurch();
        else if (checkIDUser(IDUser, dataUser, MAXUSER)==0){
            puts("There is no user connected to that ID. Try again or enter 0 to cancel");
            continue;
        }
        else {
            while(dataUser[IDUser-1].mp3files[i]!=0 || i>=MAXPURCH) {
                i++; //value of id in empty row is 0.
            }
            if (i>=MAXPURCH) {
                puts("User reached limit of owned mp3 files.");
                menuPurch();
            }
            else break;
        }
    }
        puts("Enter MP3's ID.");
    while(1){
        if ((state=scanf("%d",&IDmp3))!=1 || (IDmp3<0||IDmp3>MAXMP3)){
            if(state!=1) {
                scanf("%*s");
            }
            printf("Invalid ID. Choose an integer from 1 to %d.\n", MAXMP3);
            continue;
        }
        else if (IDUser==0) menuPurch();
        else if (checkIDMp3(IDmp3, dataMp3, MAXMP3)==0){
            puts("There is no user connected to that ID. Try again or enter 0 to cancel");
            continue;
        }
        else {
            while(dataMp3[IDmp3-1].owners[j]!=0 || j>=MAXPURCH){
                j++; //value of id in empty row is 0.
            }
            if (j>MAXPURCH) {
                puts("Mp3 file reached limit of owners.");
                menuPurch();
            }
            else break;
        }
    }
    dataUser[IDUser-1].mp3files[i]=IDmp3;
    dataMp3[IDmp3-1].owners[j]=IDUser;
    puts("Purchase added successfully.");
}
void deletePurch() {
int IDUser, IDmp3, state, code;
    int i=0, j=0;
    puts("Enter user's ID.");
    while(1){
        if ((state=scanf("%d",&IDUser))!=1 || (IDUser<0||IDUser>MAXUSER)){
            if(state!=1) {
                scanf("%*s");
            }
            printf("Invalid ID. Choose an integer from 1 to %d.\n", MAXUSER);
            continue;
        }
        else if (IDUser==0) menuPurch();
        else if (checkIDUser(IDUser, dataUser, MAXUSER)==0){
            puts("There is no user connected to that ID. Try again or enter 0 to cancel");
            continue;
        }
        else  break;
    }

    puts("Enter MP3's ID.");
    while(1){
        if ((state=scanf("%d",&IDmp3))!=1 || (IDmp3<0||IDmp3>MAXMP3)){
            if(state!=1) {
                scanf("%*s");
            }
            printf("Invalid ID. Choose an integer from 1 to %d.\n", MAXMP3);
            continue;
        }
        else if (IDUser==0) menuPurch();
        else if (checkIDMp3(IDmp3, dataMp3, MAXMP3)==0){
            puts("There is no user connected to that ID. Try again or enter 0 to cancel");
            continue;
        }
        else {
            int found = 0;
            int k;
            for (k=0; k<MAXPURCH; k++)
                if(dataMp3[IDmp3-1].owners[k]=IDUser) found = 1;
            if (found = 0){
                puts("This purchase doesn't exist in database.");
                menuPurch();
            }
            else break;

        }
    }
    dataUser[IDUser-1].mp3files[i]=0;
    dataMp3[IDmp3-1].owners[j]=0;
    puts("Purchase deleted successfully.");
}
void displayUser() {
    int i=0, j=0, k=0;
    int state, code;
    printf("|Display user database sorted by:\n");
    printf("| 1)IDs\n");
    printf("| 2)names\n");
    printf("| 3)surnames\n");
    printf("| 0)cancel\n");
    while((state=scanf("%d",&code))!=1 || (code<0||code>3)){
        if(state!=1)scanf("%*s");
        printf("Choose an integer from 0 to 3.\n");
    }
    switch (code){
        case 1:
            printf("%s\n",USERHEAD);
            for(i=0; i<MAXUSER; i++)
                if(dataUser[i].id!=0)
                    printUser(i+1);
            break;
        case 2:
            for(i=0;i<MAXUSER;i++){
                if(dataUser[i].id!=0){
                    if(IDtemp[0]==0){
                        IDtemp[0]=dataUser[i].id;
                    }
                    else {
                        while (IDtemp[j]!=0&&j<MAXUSER&&strcasecmp(dataUser[IDtemp[j]-1].name, dataUser[i].name)<=0) j++;
                        for(k=i;k>j;k--){
                            IDtemp[k]=IDtemp[k-1];
                        }
                        IDtemp[j]=dataUser[i].id;
                        j=0;
                    }
                }
            }
            printf("%s\n", USERHEAD);
            for (i=0;i<MAXUSER;i++){
                if (IDtemp[i]!=0){
                    printUser(IDtemp[i]);
                }
            }
            break;
        case 3:
            for(i=0;i<MAXUSER;i++){
                if(dataUser[i].id!=0){
                    if(IDtemp[0]==0){
                        IDtemp[0]=dataUser[i].id;
                    }
                    else {
                        while (IDtemp[j]!=0&&j<MAXUSER&&strcasecmp(dataUser[IDtemp[j]-1].surname, dataUser[i].surname)<=0) j++;
                        for(k=i;k>j;k--){
                            IDtemp[k]=IDtemp[k-1];
                        }
                        IDtemp[j]=dataUser[i].id;
                        j=0;
                    }
                }
            }
            printf("%s\n", USERHEAD);
            for (i=0;i<MAXUSER;i++){
                if (IDtemp[i]!=0){
                    printUser(IDtemp[i]);
                }
            }
            break;
        default: break;
    }
}
void displayMp3() {
    int i=0, j=0, k=0;
    int state, code;
    printf("|Display user database sorted by:\n");
    printf("| 1)IDs\n");
    printf("| 2)titles\n");
    printf("| 3)artists\n");
    printf("| 4)albums\n");
    printf("| 5)genre\n");
    printf("| 0)cancel\n");
    while((state=scanf("%d",&code))!=1 || (code<0||code>5)){
        if(state!=1)scanf("%*s");
        printf("Choose an integer from 0 to 5.\n");
    }
    switch (code){
        case 1:
            printf("%s\n",MP33HEAD);
            for(i=0; i<MAXMP3; i++)
                if(dataMp3[i].id!=0)
                    printMp3(i+1);
            break;
        case 2:
            for(i=0;i<MAXMP3;i++){
                if(dataMp3[i].id!=0){
                    if(IDtemp[0]==0){
                        IDtemp[0]=dataMp3[i].id;
                    }
                    else {
                        while (IDtemp[j]!=0&&j<MAXMP3&&strcasecmp(dataMp3[IDtemp[j]-1].title, dataMp3[i].title)<=0) j++;
                        for(k=i;k>j;k--){
                            IDtemp[k]=IDtemp[k-1];
                        }
                        IDtemp[j]=dataMp3[i].id;
                        j=0;
                    }
                }
            }
            printf("%s\n", MP33HEAD);
            for (i=0;i<MAXMP3;i++){
                if (IDtemp[i]!=0){
                    printMp3(IDtemp[i]);
                }
            }
            break;
        case 3:
            for(i=0;i<MAXMP3;i++){
                if(dataMp3[i].id!=0){
                    if(IDtemp[0]==0){
                        IDtemp[0]=dataMp3[i].id;
                    }
                    else {
                        while (IDtemp[j]!=0&&j<MAXMP3&&strcasecmp(dataMp3[IDtemp[j]-1].artist, dataMp3[i].artist)<=0) j++;
                        for(k=i;k>j;k--){
                            IDtemp[k]=IDtemp[k-1];
                        }
                        IDtemp[j]=dataMp3[i].id;
                        j=0;
                    }
                }
            }
            printf("%s\n", MP33HEAD);
            for (i=0;i<MAXMP3;i++){
                if (IDtemp[i]!=0){
                    printMp3(IDtemp[i]);
                }
            }
            break;
        case 4:
            for(i=0;i<MAXMP3;i++){
                if(dataMp3[i].id!=0){
                    if(IDtemp[0]==0){
                        IDtemp[0]=dataMp3[i].id;
                    }
                    else {
                        while (IDtemp[j]!=0&&j<MAXMP3&&strcasecmp(dataMp3[IDtemp[j]-1].album, dataMp3[i].album)<=0) j++;
                        for(k=i;k>j;k--){
                            IDtemp[k]=IDtemp[k-1];
                        }
                        IDtemp[j]=dataMp3[i].id;
                        j=0;
                    }
                }
            }
            printf("%s\n", MP33HEAD);
            for (i=0;i<MAXMP3;i++){
                if (IDtemp[i]!=0){
                    printMp3(IDtemp[i]);
                }
            }
            break;
        case 5:
            for(i=0;i<MAXMP3;i++){
                if(dataMp3[i].id!=0){
                    if(IDtemp[0]==0){
                        IDtemp[0]=dataMp3[i].id;
                    }
                    else {
                        while (IDtemp[j]!=0&&j<MAXMP3&&strcasecmp(dataMp3[IDtemp[j]-1].genre, dataMp3[i].genre)<=0) j++;
                        for(k=i;k>j;k--){
                            IDtemp[k]=IDtemp[k-1];
                        }
                        IDtemp[j]=dataMp3[i].id;
                        j=0;
                    }
                }
            }
            printf("%s\n", MP33HEAD);
            for (i=0;i<MAXMP3;i++){
                if (IDtemp[i]!=0){
                    printMp3(IDtemp[i]);
                }
            }
            break;
        default: break;
    }
}
