# Phonebook Application

This is a simple command-line phonebook application written in C. It allows users to manage their contacts by performing various operations such as adding contacts, displaying contacts, 
searching for contacts, updating contact details, and deleting contacts.

## Table of Contents

- [Features](#features)
- [Getting Started](#getting-started)
- [Usage](#usage)
- [Contact Structure](#contact-structure)
- [Function Descriptions](#function-descriptions)
- [Contributing](#contributing)
- [License](#license)

## Features

- Add new contacts with details like name, country code, contact number, and email.
- Display all saved contacts in a formatted manner.
- Search for contacts by name.
- Update contact details.
- Delete contacts by name.
- Delete all contacts at once.

## Getting Started

1. Clone or download the repository to your local machine.

2. Open a terminal or command prompt and navigate to the directory where you've placed the code files.

3. Compile the code using a C compiler. For example, using GCC:

   
   gcc main.c -o phonebook
  

## Usage

1. Run the compiled executable:

 
   ./phonebook
   

2. The application will present you with a menu of options. Use the provided numbers to select an action.

3. Follow the prompts to perform various actions such as adding contacts, searching, updating, or deleting.

## Contact Structure

The `contact` structure contains the following fields:

- `name` (30 characters) - Name of the contact.
- `country_code` (4 characters) - Country code for the contact's phone number.
- `contact_no` (long int) - Contact's phone number.
- `mail` (100 characters) - Contact's email address.

## Function Descriptions

- `print_choices()`: Displays the main menu choices for the user.
- `add_contact()`: Allows the user to add a new contact with details.
- `display_all_contacts()`: Displays all contacts stored in the phonebook.
- `search_contact()`: Allows the user to search for a contact by name.
- `delete_contact()`: Allows the user to delete a contact by name.
- `update_contact()`: Allows the user to update the details of a contact.
- `sorted_insert()`: Sorts the contacts in the phonebook alphabetically by name.
- `delete_all_contacts()`: Deletes all contacts from the phonebook.
- `start_phonebook()`: Main control loop of the program that presents the user interface and handles user input.

## Contributing

Contributions are welcome! If you have any suggestions or improvements, feel free to fork the repository and create a pull request.


