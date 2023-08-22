#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct contact{
    char name[30];
    char country_code[4];
    long int contact_no;
    char mail[100];
}contact;

void sorted_insert();
void delete_all_contacts();
void print_choices();
void add_contact();
void display_all_contacts();
void search_contact();
void delete_contact();
void update_contact();
void enter_details(contact *p);

void start_phonebook(){
    int choice;
    while(1){
        print_choices();
        printf("\t\t\tEnter your choice : ");
        scanf("%d",&choice);
        switch(choice){
            case 1:
                display_all_contacts();
                getchar();  //to catch whatever above called function returns
                getchar();  //to pause window for a while
                break;
            case 2:
                sorted_insert();
                getchar();
                getchar();
                break;
            case 3:
                search_contact();
                getchar();
                getchar();
                break;
            case 4:
                delete_contact();
                getchar();
                getchar();
                break;
            case 5:
                update_contact();
                getchar();
                getchar();
                break;
            case 6:
                delete_all_contacts();
                getchar();
                getchar();
                break;
            default:
                system("cls"); //to clear terminal
                printf("All changes saved. Thanks for using phonebook,visit again\n");
                exit(1);
        }
    }
}


void print_choices(){
    system("cls");
   printf("\t****************************************************************\n");
    printf("\t*                  Welcome TO Your phone book                    *\n");
    printf("\t****************************************************************\n\n");
    printf("\t\t1. Display all contacts\n\n");
    printf("\t\t2. Add new contact\n\n");
    printf("\t\t3. Search for an existing contact\n\n");
    printf("\t\t4. Delete a contact\n\n");
    printf("\t\t5. Update an existing contact\n\n");
    printf("\t\t6. Delete all contacts\n\n");
    printf("\t\t7. Exit Phonebook\n\n");

}

void add_contact(){
    system("cls");
    FILE* fp;
    fp=fopen("phonebook_database","a+");
    if(fp==NULL){
        printf("Unable to open the file.Try again !\n");
        printf("Press any key to continue..\n");
        return;
    }
    else{
        contact c;
        enter_details(&c);
        fwrite(&c,sizeof(c),1,fp); //1 indicates number of contacts being added
        fflush(stdin);
        fclose(fp);
        system("clear");
        printf("Contact added Successfully\n");
        printf("Press any key to continue..\n");
    }
}

void enter_details(contact* p){
    getchar();
    printf("Enter name : ");
    // Here we are using scanset '^' - >  until get
    scanf("%[^\n]s",p->name);

    printf("Enter country code : ");
    scanf("%s",p->country_code); 
    
    printf("Enter contact no : ");
    scanf("%ld",&p->contact_no); 
    
    printf("Enter email : ");
    scanf("%s",p->mail);
}

void display_all_contacts(){
    system("cls");
    FILE* fp;
    fp=fopen("phonebook_database","r"); //i specifically used binary mode for security
    if(fp==NULL){
        printf("Unable to open the file. Try again !\n");
        printf("Press any key to continue..\n");
        return;
    }
    else{
        contact p;
        printf("\n\t\t\t\t******************************************************************************\n");
        printf("\t\t\t\t*                  Here is all records listed in phonebook                   *\n");
        printf("\t\t\t\t******************************************************************************\n\n\n");
        printf("  NAME\t\t\t   COUNTRY CODE\t\t    CONTACT NO\t\t             EMAIL\n");
        printf("---------------------------------------------------------------------------------------------------------------------------------------------\n");
        
        while (fread(&p, sizeof(p), 1, fp) == 1)
        {
            int i;
            int len1 = 40 - strlen(p.name);
            int len2 = 19 - strlen(p.country_code);
            int len3 = 15;
            printf("%s",p.name);
            for(i=0;i<len1;i++) printf(" ");

            printf("%s",p.country_code);
            for(i=0;i<len2;i++) printf(" ");

            printf("%ld",p.contact_no);
            for(i=0;i<len3;i++) printf(" ");


            printf("%s",p.mail);
            printf("\n");
            fflush(stdin); // just as garbage collector
        }
        fflush(stdin);
        fclose(fp);
        printf("\n\nPress any key to continue..\n");
    }
}

void search_contact(){
    system("cls");
    char name[30];
    printf("Enter the name of person you want to search : ");
    scanf("%s",&name);

    FILE* fp;
    fp=fopen("phonebook_database","r"); //i specifically used binary mode for security
    if(fp==NULL){
        printf("Unable to open the file. Try again !\n");
        printf("Press any key to continue..\n");
        return;
    }
    else{
        contact c;
        int found=0;
       
        while(fread(&c,sizeof(c),1,fp)==1){
            
            if(strcmp(name,c.name)==0){
                printf("  NAME\t\t\t\t   COUNTRY CODE\t\t    CONTACT NO\t\t             EMAIL\n");
                printf("---------------------------------------------------------------------------------------------------------------------------------------------\n");
                int i;
                int len1 = 40 - strlen(c.name);
                int len2 = 19 - strlen(c.country_code);
                int len3 = 15;
                printf("%s",c.name);
                for(i=0;i<len1;i++) printf(" ");

                printf("%s",c.country_code);
                for(i=0;i<len2;i++) printf(" ");

                printf("%ld",c.contact_no);
                for(i=0;i<len3;i++) printf(" ");


                printf("%s",c.mail);
                printf("\n");
                fflush(stdin);

                found=1;
                break;
            }
            if(found==0){
                system("cls");
                printf("Contact not found\n");
            }
            fflush(stdin);
            fclose(fp);
            printf("\nPress any key to continue..\n");
        }
    }
}

void delete_contact(){
    system("cls");
    char name[20];
    printf("Enter name of the person you want to remove from phonebook : ");
    scanf("%s",name);

    FILE *fp,*temp;
    fp = fopen("phonebook_database", "r");
    temp = fopen("temp","w+");
    if (fp == NULL)
    {
        printf("Unable to open the file, Plz try again !\n");
        printf("Press any key to continue..\n");
        return;
    }
    else
    {
        contact p;
        int flag = 0;
        
        while ( fread ( & p , sizeof ( p) , 1 , fp ) != 0 ) {
              if(strcmp(name,p.name)!=0)
                fwrite ( & p, sizeof ( p ) , 1 , temp ) ;  
            else
                flag=1;
        }
        if(flag==0){
            printf("Contact not found\n");
        }
        else
        printf("Contact removed successfully\n");
        fclose ( fp ) ;  
        fclose ( temp) ;  
        remove ( "phonebook_database" ) ;  
        rename ( "temp" , "phonebook_database" ) ;
        
    }

}

void update_contact(){
    system("cls");
    char name[20];
    printf("Enter name of the person you want to update details : ");
    scanf("%s",&name);
    

    FILE *fp,*temp;
    fp = fopen("phonebook_database", "r");
    temp = fopen("temp","w+");
    if (fp == NULL)
    {
        printf("Unable to open the file, Plz try again !\n");
        printf("Press any key to continue....\n");
        return;
    }
    else
    {
        int flag = 0;
        contact p;
        while (fread(&p, sizeof(p), 1, fp) == 1)
        {
            if(strcmp(p.name,name)==0) 
            {   
                enter_details(&p);
                fwrite(&p, sizeof(p), 1, temp);
                system("cls");
                printf("Data updated successfully\n");
                flag = 1;
            }
            else fwrite(&p,sizeof(p),1,temp);
            fflush(stdin);
        }
        if(flag == 0)
        {
            system("cls");
            printf("No record found\n");
        }
        fclose(fp);
        fclose(temp);
        remove("phonebook_database");
        rename("temp","phonebook_database");
        fflush(stdin);
        printf("Press any key to continue..\n");
    }
}
void sorted_insert(){
    system("cls");
    FILE* fp;
    fp=fopen("phonebook_database","a+");
    if(fp==NULL){
        printf("Unable to open the file.Try again !\n");
        printf("Press any key to continue..\n");
        return;
    }
    int flag=0;
    contact c,p;
    enter_details(&c);
    char* remaining_data;
    while (fread(&p, sizeof(p), 1, fp) == 1)
        {
            if(strcmp(p.name,c.name)>0) 
            {   
                long int curr=ftell(fp);
                fseek(fp,0,SEEK_END);
                long int end=ftell(fp);
                long int len=end-curr;
                remaining_data=(char*)malloc(sizeof(char)*len);
                fread(remaining_data,1,len,fp);
                flag = 1;
                break;
            }
            else fwrite(&p,sizeof(p),1,fp);
            fflush(stdin);
        }
        if(flag==1){
            fwrite(&c,sizeof(c),1,fp);
            fputs(remaining_data,fp);
        }
        else{
            fwrite(&c,sizeof(c),1,fp);
        }
}
void delete_all_contacts(){
    system("cls");
    remove("./phonebook_database");
    printf("All contacts deleted successfully.Phonebook is empty now\n");
    printf("Press any key to continue..\n");
}
int main(){
    start_phonebook();
}