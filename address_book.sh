#!/bin/bash

# File to store address book records
address_book="address_book.txt"

# Create the address book file if it doesn't exist
touch "$address_book"

while true; do
  # Display menu
  echo -e "\nAddress Book Menu:"
  echo "1. Create Address Book"
  echo "2. View Address Book"
  echo "3. Insert a Record"
  echo "4. Delete a Record"
  echo "5. Modify a Record"
  echo "6. Exit"
  
  echo -e "\nEnter your choice: "
  read choice
  
  case $choice in
    1) # Create Address Book
      > "$address_book"
      echo "Address book created (or cleared) successfully!"
      ;;
      
    2) # View Address Book
      if [ -s "$address_book" ]; then
        echo -e "\nAddress Book:"
        cat "$address_book"
      else
        echo "Address book is empty!"
      fi
      ;;
      
    3) # Insert a Record
      echo -e "Enter Employee Number: "
      read e_no
      echo -e "Enter Employee Name: "
      read e_name
      echo -e "Enter Employee Mobile Number: "
      read e_mob
      echo -e "Enter Employee City: "
      read e_city
      echo -e "$e_no\t$e_name\t$e_mob\t$e_city" >> "$address_book"
      echo "Record inserted successfully!"
      ;;
      
    4) # Delete a Record
      echo -e "Enter Employee Number to delete: "
      read e_no
      grep -v "$e_no" "$address_book" > temp.txt && mv temp.txt "$address_book"
      echo "Record deleted successfully!"
      ;;
      
    5) # Modify a Record
      echo -e "Enter Employee Number to modify: "
      read e_no
      echo -e "Enter new Employee Number: "
      read new_no
      echo -e "Enter new Employee Name: "
      read new_name
      echo -e "Enter new Employee Mobile Number: "
      read new_mob
      echo -e "Enter new Employee City: "
      read new_city
      # Delete old record and insert the modified one
      grep -v "$e_no" "$address_book" > temp.txt && mv temp.txt "$address_book"
      echo -e "$new_no\t$new_name\t$new_mob\t$new_city" >> "$address_book"
      echo "Record modified successfully!"
      ;;
      
    6) # Exit
      echo "Exiting..."
      exit 0
      ;;
      
    *) # Invalid choice
      echo "Invalid choice! Please try again."
      ;;
  esac
done