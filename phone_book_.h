typedef struct contact{
    char name[30];
    char country_code[4];
    long int contact_no;
    char mail[100];
}contact;

void start_phonebook();
void sorted_insert();
void delete_all_contacts();
void print_choices();
void add_contact();
void display_all_contacts();
void search_contact();
void delete_contact();
void update_contact();
void enter_details(contact *p);