#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"

void listContacts(AddressBook *addressBook) 
{
  int i,j;
  Contact temp;
  for(i = 0;i < addressBook->contactCount - 1;i++)
  {
    for(j = 0;j < addressBook->contactCount -i-1;j++)
    {
      if(strcmp(addressBook->contacts[j].name,addressBook->contacts[j+1].name) > 0)
      {
        temp = addressBook->contacts[j];
        addressBook->contacts[j] = addressBook->contacts[j+1];
        addressBook->contacts[j+1] = temp;
      }
    }
  }
  //DISPLAY
  printf("\n=========== CONTACT LIST(SORTED) ===========\n");
  printf("%5s %-20s %-15s %-30s\n","Serial No","Name","Phone","Email");
  printf("-----------------------------------------------------------\n");
  for(i = 0; i < addressBook->contactCount;i++)
  {
    printf("%-5d %-20s %-15s %-30s\n",i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
  }
  printf("-------------------------------------------------------------\n");
}
void initialize(AddressBook *addressBook)
{
    addressBook->contactCount = 0;
    loadContactsFromFile(addressBook);
}
void saveAndExit(AddressBook *addressBook)
{
  saveContactsToFile(addressBook);
  printf("Exiting program...\n");
  exit(0);
}
int validate_name(char *name)
{
    int i = 0;
    if(name[0] == '\0')
      return 0;
    while(name[i] != '\0')
    {
      if((name[i] >= 'A' && name[i] <= 'Z') || 
      (name[i] >= 'a' && name[i] <= 'z') ||
      (name[i] == ' ' ) || 
      (name[i] == '.') ||
      (name[i] == '='))
      {
        i++;
      }
      else
      {
        return 0;
      }
    }
    return 1;
}
int is_duplicate_phone(AddressBook *addressBook,char *phone)
{
    int i =0;
    while(i < addressBook->contactCount)
    {
      if(strcmp(addressBook->contacts[i].phone,phone)==0)
      {
        return 1;
      }
      i++;
    }
    return 0;
}
int validate_phone(char *phone)
{
  int i = 0, len = 0;
  while(phone[len] != '\0')
    len++;
    if(len != 10)
      return 0;
    if(phone[0] < '6' || phone[0] >'9')
      return 0;
    while(phone[i] != '\0')
    {
      if(phone[i] < '0' || phone[i] >'9')
        return 0;
      i++;
    }
    for(i = 1; i < 10;i++)
    {
      if(phone[i] != phone[0])
        return 1;
    }
    return 0;
}
int is_duplicate_email(AddressBook *addressBook,char *email)
{
  int i = 0;
  while(i < addressBook->contactCount)
  {
    if(strcmp(addressBook->contacts[i].email,email) == 0)
    {
      return 1;
    }
    i++;
  }
  return 0;
}
int validate_email(char *email)
{
  int i = 0;
  int at_count = 0,at_pos = -1;
  int dot_pos = -1;
  
  while(email[i] != '\0')
  {
    if(!((email[i] >= 'a' && email[i] <= 'z') ||(email[i] >= '0' && email[i] <= '9') ||
    email[i] == '@'||
    email[i] == '.'||
    email[i] =='_'))
    {
      return 0;
    }
    if(email[i] == '@')
    {
      at_count++;
      at_pos = i;
    }
    if(email[i] == '.')
    {
      dot_pos = i;
    }
    i++;
  }
  int len = i;
  if(at_count ==1 && at_pos > 0 && dot_pos > at_pos + 1 && dot_pos < len -1)
  {
    return 1;
  }
  return 0;
}
void createContact(AddressBook *addressBook)
{
  /* Define the logic to create a Contacts */
  char name[20];
  int valid;

  while(1)
  {
     printf("Enter the name : ");
     fgets(name,sizeof(name),stdin);
     name[strcspn(name, "\n")] = '\0';
     if(validate_name(name))
        break;
     else
          printf("Invalid name! Try again.\n");
  }
  char phone[11];
  while(1)
  {
      printf("Enter Phone No : ");
      scanf(" %[^\n]",phone);
      valid = validate_phone(phone);
      if(!valid)
      {
        printf("Invalid Phone Number !Try again.\n");
      }
      else if(is_duplicate_phone(addressBook,phone))
      {
        printf("The Phone number already exists! Enter different number.\n");
      }
      else
        break;
   }
  char email[30];
  while(1)
  {
     printf("Enter email: ");
     scanf(" %[^\n]",email);
     valid = validate_email(email);
     if(!valid)
     {
      printf("Invalid email! Try again.\n");
     }
     else if(is_duplicate_email(addressBook,email))//valid
     {
        printf("Email already exists! Enter different email.\n");
      }
      else
        break;
  }
  strcpy(addressBook->contacts[addressBook->contactCount].name,name);
  strcpy(addressBook->contacts[addressBook->contactCount].phone,phone);
  strcpy(addressBook->contacts[addressBook->contactCount].email,email);
  addressBook->contactCount++;
  printf("Contact added successfully!\n");
}
int search_by_name(AddressBook *addressBook)
{
   char name[20];
   int foundCount = 0;
   int indices[100];
        
   printf("Enter the name: ");
   scanf(" %[^\n]",name);
   if(!validate_name(name))
   {
        printf("Invalid Name! Please enter only alphabets.\n");
        return -1;
   }
   for(int i = 0;i < addressBook->contactCount; i++)
   {
      if(strstr(addressBook->contacts[i].name,name))
      {
          indices[foundCount] = i;
          foundCount++;
      }
    }
    if(foundCount == 0)
    {
        printf("No match found\n");
        return -1;
    }
    else if(foundCount ==1)//one match
    {
        int i = indices[0];
        printf("Match found:\n");
        printf("S.No\tName\tPhone\t\tEmail\n");
        printf("----------------------------------------------------------------------\n");
        
        printf("1\t%-10s\t%-12s\t%20s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
        return i;
    }
    else//multiple choices
    {
        printf("\n%d contacts are matched:\n\n",foundCount);
        //table header
        printf("S.No\tNames\t\tPhone\t\tEmail\n");
        printf("--------------------------------------------------------------------\n");
        for(int i = 0; i < foundCount; i++)
        {
          int idx = indices[i];
          printf("%-5d %-20s %-15s %-30s\n",i+1,addressBook->contacts[idx].name,addressBook->contacts[idx].phone,addressBook->contacts[idx].email);
        }
        int choice;
        printf("\nEnter Serial number to select contact: ");
        scanf("%d",&choice);
        if(choice >= 1 && choice <= foundCount)
        {
          int selectedIndex = indices[choice -1];
          printf("\nSelected Contact:\n");
          printf("Name: %s\nphone: %s\nEmail: %s\n",addressBook->contacts[selectedIndex].name,addressBook->contacts[selectedIndex].phone,addressBook->contacts[selectedIndex].email);
          return selectedIndex;
        }
        else
        { 
          printf("Invalid choice\n");

          return -1;
        }
    }
}
int search_by_phone(AddressBook *addressBook)
{
          char phone[11];
          printf("Enter phone number: ");
          scanf("%s",phone);
          if(!validate_phone(phone))
          {
            printf("Invalid Phone No! Please enter Numbers only.\n");
            return -1;
          }
          for(int  i = 0;i < addressBook->contactCount; i++)
          {
            if(strcmp(addressBook->contacts[i].phone,phone) == 0)
            {
               printf("\nMatch Found: \n\n");
               printf("%-20s %-15s %-30s\n","Name","Phone","Email");
               printf("-----------------------------------------------\n");
               printf("%-20s %-15s %-30s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
               return i;
           }
         }
         printf("NO match found\n");
         return -1;
}
int search_by_email(AddressBook *addressBook)
{
          char email[30];
          printf("Enter email id: ");
          scanf("%s",email);
          if(!validate_email(email))
          {
            printf("Invalid Email ID! Please enter correct Email ID.\n");
            return -1;
          }
          for(int  i = 0;i < addressBook->contactCount; i++)
          {
            if(strcmp(addressBook->contacts[i].email,email) == 0)
              {
                printf("\nMatch Found: \n\n");
                printf("%-20s %-15s %-30s\n","Name","Phone","Email");
                printf("----------------------------------------------\n");
                printf("%-20s %-15s %-30s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                return i;
              }
          }
          printf("NO match found\n");
          return -1;
}
void edit_name(AddressBook *addressBook,int ind)
{
  char newValue[20];
  do
  {
      printf("Enter new name:");
      scanf(" %[^\n]",newValue);
      if(!validate_name(newValue))
      {
        printf("Invalid name! Try again.\n");
      }
  }while(!validate_name(newValue));
  strcpy(addressBook->contacts[ind].name,newValue);
  printf("Name updated successfully\n");
  return;
}
void edit_phone(AddressBook *addressBook,int ind)
{
  char newValue[11];
  do
  {
        printf("Enter the new Phone no:");
        scanf("%s",newValue);
        if(!validate_phone(newValue))
        {
          printf("Invalid phone! Try again.\n");
        }
        else if(is_duplicate_phone(addressBook,newValue))
        {
          printf("Phone No already exists! Try again.\n");
        }
        else
        {
          strcpy(addressBook->contacts[ind].phone,newValue);
          printf("Phone Number Updated successfully!\n");
          break;
        }
  }while(1);
}
void edit_email(AddressBook *addressBook,int ind)
{
  char newValue[30];
  do
  {
        printf("Enter the new Email id:");
        scanf("%s",newValue);
        if(!validate_email(newValue))
        {
          printf("Invalid email! Try again.\n");
        }
        else if(is_duplicate_email(addressBook,newValue))
        {
          printf("Email id already exists! Try again.\n");
        }
        else
        {
          strcpy(addressBook->contacts[ind].email,newValue);
          printf("Email id is updated successfully\n");
          break;
        }
  }while(1);
}   
int searchContact(AddressBook *addressBook) 
{
    int option;
    printf("Search by\n");
    printf("1.Name\n");
    printf("2.Phone\n");
    printf("3.Email\n");
    
    printf("Select based on the above option\n");
    scanf("%d",&option);
    
    switch(option)
    {
        case 1:
          return
        search_by_name(addressBook);
        
        case 2:
          return
        search_by_phone(addressBook);
        
        case 3:
          return 
        search_by_email(addressBook);
        
        default:
          printf("Invalid option\n");
          return -1;
    }
}
void editContact(AddressBook *addressBook)
{
    int searchOption,editOption;
    int ind = -1;
  
    printf("\nEdit contact by searching:\n");
    printf("1.Name\n");
    printf("2.Phone\n");
    printf("3.Email\n");
    printf("Edit by selecting one of the above option:");
    scanf("%d",&searchOption);
    switch(searchOption)
    {
      case 1:
      ind = search_by_name(addressBook);
      break;
      
      case 2:
      ind = search_by_phone(addressBook);
      break;
      
      case 3:
      ind = search_by_email(addressBook);
      break;
      
      default:
        printf("Invalid option\n");
      return;
    }
    if(ind == -1)
    { 
      printf("Contact not found!\n");
      return;
    }
    printf("Editing: %s\n",addressBook->contacts[ind].name);
    printf("\nEdit by: \n");
    printf("1.Name\n");
    printf("2.Phone\n");
    printf("3.Email\n");
    printf("Select the above field to edit : ");
    scanf(" %d",&editOption);
    switch(editOption)
    {
      case 1:
      edit_name(addressBook,ind);
      break;
      
      case 2:
      edit_phone(addressBook,ind);
      break;
      
      case 3:
      edit_email(addressBook,ind);
      break;
      
      default:
      printf("Invalid choice\n");
      return;
    }
    printf("\n================== Contact Updated ==================\n");
    printf("Name : %s\n",addressBook->contacts[ind].name);
    printf("Phone : %s\n",addressBook->contacts[ind].phone);
    printf("Email : %s\n",addressBook->contacts[ind].email);
    printf("=====================================================\n");
}
void delete_contact(AddressBook *addressBook,int ind)
{
  for(int i = ind;i < addressBook->contactCount-1;i++)
  {
    addressBook->contacts[i] = addressBook->contacts[i+1];
  }
  addressBook->contactCount--;
  printf("Contact deleted successfully\n");
}
void deleteContact(AddressBook *addressBook)
{
  int option;
  int ind = -1;
  printf("Delete contact by:\n");
  printf("1.Name\n");
  printf("2.Phone\n");
  printf("3.Email\n");
  printf("Select the above option to delete:");
  scanf("%d",&option);
  switch(option)
  {
    case 1:
    ind = search_by_name(addressBook);
    break;
    
    case 2:
    ind = search_by_phone(addressBook);
    break;
    
    case 3:
    ind = search_by_email(addressBook);
    break;
    
    default:
      printf("invalid option\n");
    return;
  }
  if(ind == -1)
  {
    printf("Contact not found\n");
    return;
  }
  delete_contact(addressBook,ind);
}

