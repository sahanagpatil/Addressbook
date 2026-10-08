# 📱 Address Book in C

Overview:
Address Book is a menu-driven C programming application designed to efficiently manage contact information. The application provides essential contact management operations such as adding, searching, editing, deleting, and displaying contacts.
The project demonstrates practical implementation of structures, pointers, functions, file handling, and modular programming, with contact information stored persistently using files.

# ✨ Key Features:
➕ Add new contacts
🔍 Search contacts
✏️ Edit existing contact details
🗑️ Delete contacts
📋 Display all saved contacts
💾 Store and retrieve contact information using file handling
✅ Input validation
📂 Modular and well-structured implementation
🖥️ Simple menu-driven interface

# 🛠️ Technologies & Concepts
| Category                 | Details                         |
| ------------------------ | ------------------------------- |
| **Language**             | C                               |
| **Compiler**             | GCC                             |
| **Platform**             | Linux / Windows                 |
| **Data Storage**         | File Handling                   |
| **Core Concepts**        | Structures, Pointers, Functions |
| **Programming Approach** | Modular Programming             |
| **Interface**            | Menu-driven                     |

📁 Project Structure
AddressBook/
│
├── main.c
├── contact.c
├── contact.h
├── file.c
├── file.h
├── populate.c
├── populate.h
├── contacts
└── README.md

# File Description
| File         | Purpose                                                  |
| ------------ | -------------------------------------------------------- |
| `main.c`     | Controls the application flow and displays the main menu |
| `contact.c`  | Implements contact management operations                 |
| `contact.h`  | Contains contact structures and function declarations    |
| `file.c`     | Handles reading and writing contact data                 |
| `file.h`     | Contains file-handling function declarations             |
| `populate.c` | Handles initial/population of contact records            |
| `populate.h` | Contains declarations related to population              |
| `contacts`   | Stores contact information                               |
| `README.md`  | Project documentation                                    |

⚙️ Application Workflow
When the application starts, the user is presented with a menu:
========== ADDRESS BOOK ==========

1. Add Contact
2. Search Contact
3. Edit Contact
4. Delete Contact
5. Display Contacts
6. Exit

Enter your choice:
The selected operation is performed based on the user's choice.

➕ Add Contact
Allows the user to enter and save new contact information.

🔍 Search Contact
Searches for an existing contact using the available contact details.

✏️ Edit Contact
Allows the user to modify the details of an existing contact.

🗑️ Delete Contact
Removes the selected contact from the address book.

📋 Display Contacts
Displays all available contacts stored in the address book.

🚪 Exit
Safely terminates the application.

💻 Compilation:
Open the terminal inside the project directory and compile all C source files:
gcc *.c
This generates the executable:
a.out

▶️ Execution
Run the application using:
./a.out

🧠 Concepts Implemented:

This project provides practical experience with:
Structures – to represent contact information
Pointers – for efficient data manipulation
Functions – for separating different operations
File Handling – for permanent data storage
Header Files – for declarations and code organization
Modular Programming – for maintaining a clean project structure
String Handling – for processing contact details
Input Validation – for handling user input
Menu-driven Programming – for interactive application control

🎯 Key Learning Outcomes:

Through this project, I gained hands-on experience in:
Designing a real-world application using C
Managing structured data using structures
Performing CRUD operations on contact records
Implementing persistent storage using files
Developing modular and reusable C programs
Understanding the interaction between .c and .h files
Improving debugging and problem-solving skills
Building a user-friendly command-line application

🚀 Future Enhancements:

The Address Book can be further enhanced by implementing:
📧 Email address management
🔤 Alphabetical contact sorting
🚫 Duplicate contact detection
🔐 Password-based access
📤 Import and export functionality
💾 Automatic backup and restore
🔎 Advanced search and filtering
🎨 Improved user interface

🏆 Conclusion

The Address Book in C project demonstrates how fundamental C programming concepts can be combined to develop a practical, real-world application.
By integrating structures, pointers, functions, file handling, and modular programming, the project provides an efficient solution for managing contact information while strengthening core programming and problem-solving skills.

👩‍💻 Author:
Sahana Patil
B.E. – Electrical and Electronics Engineering
Embedded Systems Trainee
