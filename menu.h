#define MAX 10
#define MAXUSER 100*MAX
#define MAXMP3 1000*MAX
#define MAXPURCH MAX //max number of owners of song or owned songs
#define MAXDIR MAX //max number of directories
#define MAXINDIR MAX //max number of elements in directory
#define MAXID MAXMP3 //max number of ID's in temporary ID array
#define GRAPHIC "==========================================================================================================================================="
#define USERHEAD " ID number                NAME                          SURNAME"
#define MP33HEAD " ID number                               TITLE                          ARTIST                           ALBUM            GENRE"
typedef struct user {
    int id;
    char name[15];
    char surname[32];
    int mp3files[MAXPURCH];
} USER;
typedef struct mp3 {
    int id;
    char title[30];
    char artist[30];
    char album[30];
    char genre[15];
    int owners[MAXPURCH];
} MP3;
typedef struct dir {
    int id;
    char name[15];
    int contentId[MAXINDIR];
    char type;
} DIR;
USER dataUser[MAXUSER];
MP3 dataMp3[MAXMP3];
DIR dataDir[MAXDIR];
int IDtemp[MAXID];
