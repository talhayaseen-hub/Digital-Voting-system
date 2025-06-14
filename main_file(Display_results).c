# include <stdio.h>
# include <conio.h>
# include <string.h>
# include <stdbool.h>
# include <windows.h>
# include <ctype.h>
typedef struct Candidate
{
    char name[100];
    char Party_name[20];
    int votes;
    long long int ID;
}candidate;
typedef struct Voter
{
    long long int ID;
    char name[100];
    bool hasvoted;
} voter;
candidate candid_list[6];
voter voter_list[100];
int candidate_count=0;
int voter_count=0;
long long int admin_ID=3730179608047;
char admin_password[10]="ALiHAIDER";
bool Loggedin=false;
void Admin();
void Admin_Login();
void Entry_candidates();
void Candidate_list_show();
void Votes_casted();
void Display_Result();
void Add_voters();
void delete_voters();
void candidate_load();
void voter_load();
void candidate_count_updater();
void voter_count_updater();
void voter_list_updater();
void candidate_list_updater();
bool name_input_validation(char *s);
void MainMenu();
int main()
{
    candidate_load();
    voter_load();
    MainMenu();
    candidate_count_updater();
    voter_count_updater();
    return 0;
}
void Admin_Login()
{
    int password_attempts=0;
    long long int ID_input;
        printf("=====================================Welcome to the Admin Panel=====================================");
        printf("\n\nKindly enter your ID: ");
        scanf("%lld",&ID_input);
        if(admin_ID!=ID_input)
        {
            printf("\nThis is invalid ID\n");
            return;
        }
        char admin_password_input[10];
        while(password_attempts<3)
        {
            printf("\nEnter your password: ");
            scanf("%9s",admin_password_input);
            if(strcmp(admin_password,admin_password_input)==0)
            {
                printf("LOGGEDIn\n");
                Loggedin=true;
            }
            else
            {
                printf("\nInvalid Password");
                password_attempts++;
                if(password_attempts==2)
                    {
                        printf("You have reached the password limit (Admin panel in locked)");
                    }
            }
            if(Loggedin==true)
            {
                Admin();
                break;
            }
        }
        return;
}
void Admin()
{
    system("cls");
    int password_attempts=0;
    while(true)
    {
        int admin_input;
        printf("==========================================\tEnter your choice for further processing(1-7)\t ========================================");
        printf("\n\n1.Enter Candidate inforamtion\n");
        printf("2.Check total votes casted\n");
        printf("3.Add Voters\n");
        printf("4.Delete Voters\n");
        printf("5.Display Result\n");
        printf("6.Display all candidates\n");
        printf("7.Back to main menu\n");
        printf("==========================================\t=============================================\t ========================================\n");
        printf("Enter your choice here:  ");
        scanf("%d",&admin_input);
        if(admin_input==1)
        {
            Entry_candidates();
        }
        else if(admin_input==2)
        {   
            Votes_casted();
        }
        else if(admin_input==3)
        {
            Add_voters();
        }
        else if(admin_input==4)
        {
            delete_voters();
        }
        else if(admin_input==5)
        {
            Display_Result();
            printf("Press any key to return to the main menu");
            getch();
            MainMenu();
        }
        else if(admin_input==6)
        {
            Candidate_list_show();
            printf("Press any key to return to the main menu");
            getch();
            MainMenu();
        }
        else if(admin_input==7)
        {
            MainMenu();
        }
        else
        {
            printf("Invalid Input Please try again");
            MainMenu();
            return;
        }
    }
}
void Entry_candidates()
{
    
    int candid;
    printf("How many Candidates do you want to Add(only enter an integer): ");
    if(scanf("%d",&candid)!=1)
    {
        printf("You didn't enter the right type of input\n");
        while (getchar()!='\n')system("cls");
        return;
    }
    if(candid+candidate_count>6)
    {
        printf("you can't store candidates more than %d as already %d candidates have been registered",6-candidate_count,candidate_count);
        return;
    }
    FILE *candidate_infoo;
    candidate_infoo=fopen("Candidate_info.txt","a");
    for(int i=0;i<candid;i++)
    {
        bool duplicate_ID=false;
        printf("Enter ID: ");
        scanf("%lld",&candid_list[candidate_count].ID);
        for(int j=0;j<candidate_count;j++)
        {
            if(candid_list[j].ID==candid_list[candidate_count].ID)
            {
                printf("\nID already exists\n");
                duplicate_ID=true;
            }
        }
        if(duplicate_ID==true)
        {
            i--;
            candid_list[candidate_count].ID=0;
            continue;
        }
        fprintf(candidate_infoo,"%lld ",candid_list[candidate_count].ID);
        printf("Enter name: ");
        scanf("%s",candid_list[candidate_count].name);
        if(!name_input_validation(candid_list[candidate_count].name))
        {
            printf("Entered the wrong Name\n");
            candid_list[candidate_count].ID=0;
            i--;
            strcpy(candid_list[candidate_count].name,"");
            continue;
        }
        fprintf(candidate_infoo,"%s ",candid_list[candidate_count].name);
        printf("Enter Party name: ");
        scanf("%s",candid_list[candidate_count].Party_name);
        if(!name_input_validation(candid_list[candidate_count].Party_name))
        {
            printf("Entered the wrong Name\n");
            candid_list[candidate_count].ID=0;
            i--;
            strcpy(candid_list[candidate_count].name,"");
            strcpy(candid_list[candidate_count].Party_name,"");
            continue;
        }
        fprintf(candidate_infoo,"%s",candid_list[candidate_count].Party_name);
        candid_list[candidate_count].votes=0;
        fprintf(candidate_infoo, "%d\n", candid_list[candidate_count].votes);
        printf("\nName %s,Id %lld ,Party %s,votes %d\n",candid_list[candidate_count].name,candid_list[candidate_count].ID,candid_list[candidate_count].Party_name,candid_list[candidate_count].votes);
        candidate_count++;
        candidate_count_updater();
    }
    fclose(candidate_infoo);
    Candidate_list_show();
    Display_Result();
}
void Candidate_list_show()
{
    printf("Following are the candidates appearing in the election\n");
        for(int i=0;i<candidate_count;i++)
        {
            printf("Name: %s ID: %lld Party: %s Votes: %d\n",candid_list[i].name,candid_list[i].ID,candid_list[i].Party_name,candid_list[i].votes);
        }
}
void Votes_casted()
{
    printf("Following are the total votes casted against each candidate\n");
    printf("Name\t\tParty\t\tID\t\t\tVotes\n");
    for(int i=0;i<candidate_count;i++)
    {
        printf("%s\t\t%s\t\t%lld\t\t%d\n",candid_list[i].name,candid_list[i].Party_name,candid_list[i].ID,candid_list[i].votes);
    }
}
void Display_Result()
{
     int result=0;
    bool tie=false;
     int tie_total[6],total=0;
    for( int i=0;i<candidate_count;i++)
    {
        if(candid_list[i].votes>candid_list[result].votes)
        {
            result=i;
        }
    }
    for(int j=0;j<candidate_count;j++)
    {
        if(result!=j)
        {
            if(candid_list[result].votes==candid_list[j].votes)
            {
                tie=true;
                tie_total[total++]=j;
            }
        }
    }
    if(tie==true)
    {
        tie_total[total++]=result;
        printf("There is a tie between\n");
        for(long long int z=0;z<total;z++)
        {
            printf("The  %s with %d Votes\n",candid_list[tie_total[z]].name,candid_list[tie_total[z]].votes);
        }
        return;
    }
    printf("The Winner is %s with %d Votes\n",candid_list[result].name,candid_list[result].votes);
}
void Add_voters()
{
    int num;
    bool duplicate_ID;
    FILE *voters_list_ptr;
    voters_list_ptr=fopen("voter_info.txt","a");
    printf("How many voters do you want to add(1-100)\n");
    scanf("%d",&num);
    if(voter_count+num>100)
    {
        printf("you can't store voters more than %d as already %d voters have been registered",100-voter_count,voter_count);
        return;
    }
    for(int i=0;i<num;i++)
    {
        duplicate_ID=false;
        printf("Enter the Voter ID: ");
        scanf("%lld",&voter_list[voter_count].ID);
        for(int j=0;j<voter_count;j++)
        {
            if(voter_list[j].ID==voter_list[voter_count].ID)
            {
                printf("\nID already exists\n");
                duplicate_ID=true;
            }
        }
        if(duplicate_ID==true)
        {
            i--;
            voter_list[voter_count].ID=0;
            continue;
        }
        fprintf(voters_list_ptr,"%lld ",voter_list[voter_count].ID);
        printf("Enter the Voter Name: ");
        scanf("%s",voter_list[voter_count].name);
        if(!name_input_validation(voter_list[voter_count].name))
        {
            printf("Entered the wrong Name\n");
            voter_list[voter_count].ID=0;
            i--;
            strcpy(voter_list[voter_count].name,"");
            continue;
        }
        fprintf(voters_list_ptr,"%s ",voter_list[voter_count].name);
        voter_list[voter_count].hasvoted=false;
        fprintf(voters_list_ptr,"%d\n",voter_list[voter_count].hasvoted);
        printf("ID: %lld Name:%s Hasvoted:%d\n",voter_list[voter_count].ID,voter_list[voter_count].name);
        voter_count++;
        voter_count_updater();
    }
    fclose(voters_list_ptr);
}
void delete_voters()
{
    int new_voter_count=0;
    bool voter_found=false;
    long long int ID;
    FILE *ptr2=fopen("temp_voter_info.txt","w");
    printf("Enter the ID you want to delete:");
    scanf("%lld",&ID);
    for(int i=0;i<voter_count;i++)
    {
        if(ID!=voter_list[i].ID)
        {
            fprintf(ptr2,"%lld %s %d\n",voter_list[i].ID,voter_list[i].name,voter_list[i].hasvoted);
            new_voter_count++;
        }
        else
        {
            voter_found=true;
        }
    }
    if(!voter_found)
    {
        printf("This voter doesnot exist\nKindly press y to delete any other voter or e to exit the program\n");
        char input;
        input =getch();
        if(input=='y'||input=='Y')
        {
            delete_voters();
        }
        else{
            return;
        }
    }
    voter_count=new_voter_count;
    fclose(ptr2);
    remove("voter_info.txt");
    rename("temp_voter_info.txt","voter_info.txt");
}
void candidate_load()
{
    FILE *candid_list_ptr;
    candid_list_ptr=fopen("candidate_count.txt","r");
    int a;
    fscanf(candid_list_ptr,"%d",&a);
    fclose(candid_list_ptr);
    candidate_count=a;
    FILE *ptr=fopen("Candidate_info.txt","r");
    for(int i=0;i<candidate_count;i++)
    {
        fscanf(ptr,"%lld",&candid_list[i].ID);
        fscanf(ptr,"%s",candid_list[i].name);
        fscanf(ptr,"%s",candid_list[i].Party_name);
        fscanf(ptr,"%d",&candid_list[i].votes);
    }
    fclose(ptr);
}
void voter_load()
{
    FILE *ptr_for_voter_count=fopen("voter_count.txt","r");
    int a;
    fscanf(ptr_for_voter_count,"%d",&a);
    fclose(ptr_for_voter_count);
    voter_count=a;
    FILE *ptr=fopen("voter_info.txt","r");
    for(int i=0;i<voter_count;i++)
    {
        fscanf(ptr,"%lld",&voter_list[i].ID);
        fscanf(ptr, "%s",voter_list[i].name);
        fscanf(ptr,"%d",&voter_list[i].hasvoted);
    }
    fclose(ptr);
}
void candidate_count_updater()
{
    FILE *candid_list_ptr;
    candid_list_ptr=fopen("candidate_count.txt","w");
    fprintf(candid_list_ptr,"%d",candidate_count);
    fclose(candid_list_ptr);
}
void voter_count_updater()
{
    FILE *voter_list_ptr;
    voter_list_ptr=fopen("voter_count.txt","w");
    fprintf(voter_list_ptr,"%d",voter_count);
    fclose(voter_list_ptr);
}
void candidate_list_updater()
{
    FILE *ptr=fopen("Candidate_info.txt","w");
    for(int i=0;i<candidate_count;i++)
    {
        fprintf(ptr,"%lld ",candid_list[i].ID);
        fprintf(ptr,"%s ",candid_list[i].name);
        fprintf(ptr,"%s ",candid_list[i].Party_name);
        fprintf(ptr,"%d\n",candid_list[i].votes);
    }
    fclose(ptr);
}
void voter_list_updater()
{
    FILE *ptr=fopen("voter_info.txt","w");
    for(int i=0;i<voter_count;i++)
    {
        fprintf(ptr,"%lld ",voter_list[i].ID);
        fprintf(ptr,"%s ",voter_list[i].name);
        fprintf(ptr,"%d\n",voter_list[i].hasvoted);
    }
    fclose(ptr);
}
bool name_input_validation(char *s)
{
    int flag=0;
    for(int i=0;s[i]!='\0';i++)
    {
        if(isalpha(s[i])==0)
        {
            flag=1;
            break;
        }
    }
    if(flag==1)
    {
        return false;
    }
    return true;
}
void MainMenu()
 {
int choice;

system("cls");
    
  printf("\n\n");

    printf("==================================\n");

  printf(" SIMPLE VOTING SYSTEM MENU \n");

    printf("======================================\n");

 printf("1. Admin Login\n");

 printf("2. Voter Panel\n");

    printf("3. View Candidates\n");

   printf("4. Display Results\n");

   printf("5. Exit\n");

   printf("=========================================\n");

    printf("Enter your choice (1-5):");

   scanf("%d", &choice);
    
     switch(choice)
     {
     case 1:
     
            Admin_Login();

            break;
            
     case 2:

     printf("Press any key to return to main menu");

     getch();

     MainMenu();
     break;
            
    case 3:
     // Show candidate list

    Candidate_list_show();

     printf("\nPress any key to return to main menu...");

     getch();

     MainMenu();
     break;

    case 4:
     printf("These are the results:\n");

     Display_Result();

     printf("\nPress any key to return to main menu...");

     getch();

     MainMenu();
     break;      
    case 5:
     printf("Exiting program. Thank you!\n");

     return;
     break;
            
default:
     printf("Invalid choice! Please try again.\n");

        getch();

        MainMenu();
    }
}
