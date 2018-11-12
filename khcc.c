#include<stdio.h>
#include<windows.h>
#include<time.h>

void gotoxy();
void play();
void user();
void admin();
void finish();
void list_prize();
void lost();
void stored_question();
void add_question();
void add_pass();
void user_records();
void check_pass();
void edit();
void credit();
int check_ans(int x, int y);
int nextquest();
int get_taka(int x);

COORD xy={0,0};

struct play
{
    char ques[100];
    char opt1[50];
    char opt2[50];
    char opt3[50];
    char opt4[50];
    char pass[50];
    int ans;
    int no;
};

struct user
{
    char name[50];
    int age;
};

struct play p;
struct user u;
char yes[]="Congratulation!";
char no[]="Wrong!";
int taka=0;

int main()
{
    FILE *mborder;
    mborder = fopen("border.txt", "rb");
    char brdr[1002];
    fread(&brdr, sizeof(brdr), 1, mborder);
    while(1)
    {
        system("cls");
        system("COLOR E0");
        gotoxy(20,5);
        printf("WELCOME\t TO\t KHCC\t GAME!");
        gotoxy(0,8);
        printf("%s", brdr);
        gotoxy(30,10);
        printf("Choose an option:");
        gotoxy(32,12);
        printf("1. Play game");
        gotoxy(32,14);
        printf("2. For Admin");
        gotoxy(32,16);
        printf("3. Credit");
        gotoxy(32,18);
        printf("4. Exit\n\n\n");

        switch(getch())
        {
        case '1':
            user();
            break;
        case '2':
            check_pass();
            break;
        case '3':
            credit();
            break;
        case '4':
            exit(0);
        }
    }
    fclose(mborder);
    return 0;
}

void user()
{
    system("cls");
    gotoxy(30, 14);
    printf("Enter your name:");
    scanf("%s", u.name);
    gotoxy(30, 16);
    printf("Enter your Age:");
    scanf("%d", &u.age);

    if(u.age>17 && u.age<77){
        play();
    }
    else if(u.age>77){
        gotoxy(30, 18);
        printf("Take rest please!\n\npress enter to back.");
        getch();
        main();
    }
    else{
        gotoxy(20, 18);
        printf("First make yourself experienced(age 18 or above)!\n\tpress enter to back.");
        getch();
        main();
    }
}

void play()
{
    system("cls");
    system("COLOR B3");
    FILE *fplay;
    fplay=fopen("questions.txt", "rb");

    int answer,l, next=0;
    char input;

    while(fread(&p, sizeof(p), 1, fplay)==1){
        next++;
        if(next>10){
            finish();
            break;
            fclose(fplay);
        }
        system("cls");
        gotoxy(10, 5);
        printf("Welcome %s !", u.name);
        gotoxy(10, 7);
        printf("Now u have %d taka.", taka);
        if(next==1){
            gotoxy(50, 11);
            printf("<==>");
        }
        else if(next==2){
            gotoxy(50, 10);
            printf("<==>");
        }
        else if(next==3){
            gotoxy(50, 9);
            printf("<==>");
        }
        else if(next==4){
            gotoxy(50, 8);
            printf("<==>");
        }
        else if(next==5){
            gotoxy(50, 7);
            printf("<==>");
        }
        else if(next==6){
            gotoxy(50, 6);
            printf("<==>");
        }
        else if(next==7){
            gotoxy(50, 5);
            printf("<==>");
        }
        else if(next==8){
            gotoxy(50, 4);
            printf("<==>");
        }
        else if(next==9){
            gotoxy(50, 3);
            printf("<==>");
        }
        else if(next==10){
            gotoxy(50, 2);
            printf("<==>");
        }
        list_prize();
        gotoxy(0,14);
        for(l=1; l<=80; l++){
            printf("=");
        }
        gotoxy(7,15);
        printf("%d.",p.no);
        gotoxy(10,15);
        puts(p.ques);
        gotoxy(10,19);
        printf("1. ");
        puts(p.opt1);
        gotoxy(50,19);
        printf("2. ");
        puts(p.opt2);
        gotoxy(10,23);
        printf("3. ");
        puts(p.opt3);
        gotoxy(50,23);
        printf("4. ");
        puts(p.opt4);
        input = getch();
        answer = (int)input-48;
        if(check_ans(p.no,answer) == 1){
            list_prize();
            get_taka(next);
            gotoxy(7,10);
            for(l = 0; yes[l]!='\0'; l++){
                Sleep(50);
                printf("%c",yes[l]);
            }
            Sleep(1000);
            gotoxy(7,12);
            continue;
        }
        else{
           gotoxy(7,10);
            for(l = 0; no[l]!='\0'; l++){
                Sleep(50);
                printf("%c",no[l]);
            }
            Sleep(1000);
            lost();
            getch();
            main();
        }
    }

    taka=0;
    fclose(fplay);
}

void admin()
{
    while(1)
    {
        system("cls");
        gotoxy(30,10);
        printf("1. View Stored Questions.");
        gotoxy(30,12);
        printf("2. Add more questions.");
        gotoxy(30,14);
        printf("3. Edit saved questions.");
        gotoxy(30,16);
        printf("4. Back.");

        switch(getch())
        {
        case '1':
            stored_question();
            break;
        case '2':
            add_question();
            break;
        case '3':
            edit();
            break;
        case '4':
            main();
            break;
        }
    }
}

void add_question()
{
    FILE *fplay;
    fplay=fopen("questions.txt", "ab");
    char yn='y';
    while(yn=='y')
    {
        system("cls");
        system("COLOR CF");
        p.no=nextquest();
        printf("\n Enter Question no %d: ", p.no);
        fflush(stdin);
        gets(p.ques);

        printf("\nOption 1: ");
        gets(p.opt1);

        printf("\nOption 2: ");
        gets(p.opt2);

        printf("\nOption 3: ");
        gets(p.opt3);

        printf("\nOption 4: ");
        gets(p.opt4);

        printf("Correct ans: ");
        scanf("%d", &p.ans);

        fseek(fplay,0,SEEK_END);
        fwrite(&p, sizeof(p), 1, fplay);
        fclose(fplay);
        printf("add another(y/n) ");
        yn = getche();
    }
}

int nextquest()
{
    FILE *nqp;
    nqp=fopen("questions.txt", "rb+");
    while(fread(&p, sizeof(p), 1, nqp)==1);
    return p.no+1;
    fclose(nqp);
}

int check_ans(int q,int a){
    FILE *fplay;
    fplay = fopen("questions.txt","rb+");
    while(fread(&p,sizeof(p),1,fplay)){
        if(q == p.no && a == p.ans){
            return 1;
        }
    }
    return 0;
}

void stored_question()
{
    system("cls");
    FILE *fplay;
    fplay = fopen("questions.txt", "rb+");
    while(fread(&p, sizeof(p), 1 , fplay)==1){
        printf("%d. ", p.no);
        puts(p.ques);
        printf("Option 1:");
        puts(p.opt1);
        printf("Option 2:");
        puts(p.opt2);
        printf("Option 3:");
        puts(p.opt3);
        printf("Option 4:");
        puts(p.opt4);
        printf("Correct ans: %d\n", p.ans);
    }
    getch();
    fclose(fplay);
}

void check_pass()
{
    system("cls");
    FILE *fpass;
    fpass= fopen("pass.txt", "r+");
    fread(&p, sizeof(p), 1, fpass);
    while(1){
        system("cls");
        gotoxy(17, 2);
        printf("\tYou can type back for go home.\n");
        char password[50];
        char bck[]="back";
        gotoxy(32, 12);
        printf("Enter password:");
        gets(password);

        if(strcmp(p.pass,password) == 0){
            fclose(fpass);
            admin();
        }
        else if(strcmp(bck,password) == 0){
            main();
            break;
        }
        else{
            gotoxy(32, 14);
            printf("\n\t\t\t\tWrong!\n");
            Sleep(150);
            continue;
        }
    }
}

void finish()
{
    system("cls");
    gotoxy(30, 10);
    printf("Wow ! You have finished the full game.");
    gotoxy(30, 12);
    printf("You get %d taka.", taka);
    gotoxy(30, 14);
    printf("Press enter to exit.");
    getch();
}

void list_prize(){
    int l;
    gotoxy(55,12);
    for(l=1; l<=23; l++){
        printf("=");
    }
    gotoxy(55,11);
    printf("||1. Rs.1,000");
    gotoxy(55,10);
    printf("||2. Rs.5,000");
    gotoxy(55,9);
    printf("||3. Rs.10,000");
    gotoxy(55,8);
    printf("||4. Rs.50,000");
    gotoxy(55,7);
    printf("||5. Rs.100,000");
    gotoxy(55,6);
    printf("||6. Rs.500,000");
    gotoxy(55,5);
    printf("||7. Rs.1,000,000");
    gotoxy(55,4);
    printf("||8. Rs.5,000,000");
    gotoxy(55,3);
    printf("||9. Rs.10,000,000");
    gotoxy(55,2);
    printf("||10. Rs.50,000,000");
    gotoxy(55,1);
    for(l=1; l<=23; l++){
        printf("=");
    }
}

void lost()
{
    system("cls");
    system("COLOR 70");
    gotoxy(30, 12);
    printf("You get %d taka", taka);
    gotoxy(30, 14);
    printf("See u again !");
    gotoxy(30, 16);
    printf("Press enter to exit.");
}

int get_taka(int x)
{
    if(x==1){
        taka=1000;

    }
    else if(x==2){
        taka=5000;
    }
    else if(x==3){
        taka=10000;
    }
    else if(x==4){
        taka=50000;
    }
    else if(x==5){
        taka=100000;
    }
    else if(x==6){
        taka=500000;
    }
    else if(x==7){
        taka=1000000;
    }
    else if(x==8){
        taka=5000000;
    }
    else if(x==9){
        taka=10000000;
    }
    else if(x==10){
        taka=50000000;
    }
}

void edit()
{
    FILE *fplay;
    fplay=fopen("questions.txt","rb+");
    system("cls");
    char edit_next= 'y';
    int num;
    while(edit_next == 'y'){
        printf("Enter the question number: ");
        scanf("%d", &num);
        rewind(fplay);
        while(fread(&p,sizeof(p),1,fplay)==1){
            if(num==p.no){
                printf("\n Enter Question no %d: ", p.no);
                fflush(stdin);
                gets(p.ques);

                printf("\nOption 1: ");
                gets(p.opt1);

                printf("\nOption 2: ");
                gets(p.opt2);

                printf("\nOption 3: ");
                gets(p.opt3);

                printf("\nOption 4: ");
                gets(p.opt4);

                printf("Correct ans: ");
                scanf("%d", &p.ans);
                fseek(fplay,-sizeof(p),SEEK_CUR);
                fwrite(&p,sizeof(p),1,fplay);
                break;
            }
        }
        printf("\nEdit another question?(y/n)");
        fflush(stdin);
        edit_next = getch();
    }
    fclose(fplay);
}

void gotoxy(int x, int y)
{
    xy.X = x;
    xy.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), xy);
}

void credit()
{
    system("cls");
    system("COLOR DF");
    gotoxy(28,10);
    printf("Me - Shadhin Khan");
    gotoxy(28,12);
    printf("My faculty - Ahad Sir");
    gotoxy(28,14);
    printf("My Lab Instructor - Rahat Bhaiya");
    getch();
}
