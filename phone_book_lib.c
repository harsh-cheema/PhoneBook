#include <stdio.h>
#include <stdlib.h>

#include <string.h>

typedef struct contact{
    char name[30];
    char country_code[4];
    long int contact_no;
    char mail[100];
}contact;

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
                add_contact();
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
                system("clear"); //to clear terminal
                printf("All changes saved. Thanks for using phonebook,visit again\n");
               	return;
        }
    }
}


void print_choices(){
    system("clear");
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
    system("clear");
    FILE* fp;
    fp=fopen("phonebook_database.txt","a+");
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
        sorted_insert();
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
    system("clear");
    FILE* fp;
    fp=fopen("phonebook_database.txt","r"); //i specifically used binary mode for security
    if(fp==NULL){
        printf("Unable to open the file. Try again !\n");
        printf("Press any key to continue..\n");
        return;
    }
    else{
        contact p;
        printf("\n\t\t********************************************************\n");
        printf("\t\t*        Here is all records listed in phonebook           *\n");
        printf("\t\t**********************************************************\n\n\n");
        printf("  NAME\t\t   COUNTRY CODE\t\t     CONTACT NO\t\t            EMAIL\n");
        printf("-------------------------------------------------------------------------------------\n");
        
        while (fread(&p, sizeof(p), 1, fp) == 1)
        {
            int i;
            int len1 = 30 - strlen(p.name);
            int len2 = 15 - strlen(p.country_code);
            int len3 = 12;
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
    system("clear");
    char name[30];
    printf("Enter the name of person you want to search : ");
    scanf("%s",&name);

    FILE* fp;
    fp=fopen("phonebook_database.txt","r"); 
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
                printf("  NAME\t\t     COUNTRY CODE\t\t    CONTACT NO\t\t        EMAIL\n");
                printf("-------------------------------------------------------------------------------------\n");
                int i;
                int len1 = 30 - strlen(c.name);
                int len2 = 15 - strlen(c.country_code);
                int len3 = 12;
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
                system("clear");
                printf("Contact not found\n");
            }
            fflush(stdin);
            fclose(fp);
            printf("\nPress any key to continue..\n");
        }
    }
}

void delete_contact(){
    system("clear");
    contact p;
    char name[20];
    printf("Enter name of the person you want to remove from phonebook : ");
    scanf("%s",&name);

    FILE *fp,*temp;
    fp = fopen("phonebook_database.txt", "r");
    temp = fopen("temp.txt","w");
    if (fp == NULL)
    {
        printf("Unable to open the file, Plz try again !\n");
        printf("Press any key to continue..\n");
        return;
    }
    else
    {
        
        int flag = 0;
        
        while ( fread ( & p , sizeof ( p) , 1 , fp ) == 1) {
              if(strcmp(name,p.name)==0){
                flag=1;
                continue;
              }
                fwrite ( & p, sizeof ( p ) , 1 , temp ) ;   
        }
        fclose ( fp ) ;  
        fclose ( temp) ; 
        if(flag==1){
            temp=fopen("temp.txt","r");
            fp=fopen("phonebook_database.txt","w");
            while(fread(&p,sizeof(p),1,temp)==1){
                fwrite( & p, sizeof ( p ) , 1 , fp);
            }
            printf("Contact removed successfully\n");
            fclose ( fp ) ;  
            fclose ( temp) ;
        }
        else{
            printf("Contact not found\n");
        }
        remove ( "temp.txt" ) ;  
       
        
    }

}

void update_contact(){
    system("clear");
    contact p;
    char name[20];
    printf("Enter name of the person you want to update details : ");
    scanf("%s",&name);
    

    FILE *fp,*temp;
    fp = fopen("phonebook_database.txt", "r");
    temp = fopen("temp.txt","w");
    if (fp == NULL)
    {
        printf("Unable to open the file, Plz try again !\n");
        printf("Press any key to continue....\n");
        return;
    }
    else
    {
        int flag = 0;
        while (fread(&p, sizeof(p), 1, fp) == 1)
        {
            if(strcmp(p.name,name)==0) 
            {   
                fflush(stdin);
                enter_details(&p);
                flag=1;
            }
            fwrite(&p,sizeof(p),1,temp);
        }
        fclose(fp);
        fclose(temp);
        if(flag == 1)
        {
            temp=fopen("temp.txt","r");
            fp=fopen("phonebook_database.txt","w");
            while(fread(&p,sizeof(p),1,temp)==1){
                fwrite(&p,sizeof(p),1,fp);
            }
            fclose(fp);
            fclose(temp);
            printf("Contact updated successfully\n");
        }
        else{
            printf("Contact Not found\n");
        }
        sorted_insert();
        remove("temp.txt");
        fflush(stdin);
        printf("Press any key to continue..\n");
    }
}
void sorted_insert(){
    contact* p,c;   //p for storing data and c for reading file
    FILE* fp=fopen("phonebook_database.txt","r");
    fseek(fp,0,SEEK_END);
    int n=ftell(fp)/sizeof(contact); //tells no. of contacts
    rewind(fp);
    p=(contact*)calloc(n,sizeof(contact));
    int i,j;
    for(i=0;i<n;i++){
        fread(&p[i],sizeof(contact),1,fp);
    }

    fclose(fp);
    for(i=0;i<n;i++){
        for(j=i+1;j<n;j++){
            if(strcmp(p[i].name,p[j].name)>0){
                c=p[i];
                p[i]=p[j];
                p[j]=c;
            }
        }
    }

    fp=fopen("phonebook_database.txt","w");

    for(i=0;i<n;i++){
        fwrite(&p[i],sizeof(contact),1,fp);
    }
    fclose(fp);

}
void delete_all_contacts(){
    system("clear");
    remove("phonebook_database.txt");
    printf("All contacts deleted successfully.Phonebook is empty now\n");
    printf("Press any key to continue..\n");
}

