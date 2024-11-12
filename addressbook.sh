#!/usr/bin/bash

while true; do
    printf "\n MENU"
    printf "\n 1) Create Address Book.\n 2) View Address Book.\n 3) Insert a record.\n 4) Delete a Record.\n 5) Modify a Record.\n 6) Exit"

    echo -e "\nEnter Choice (1-6):"
    read choice

    case $choice in
        1) echo "Enter Address Book Name:"
           read file_name
           if [ -e "$file_name" ]; then
               rm "$file_name"
           fi
           touch "$file_name"
           printf "Name \t Phone_no \t Address\n______________________" > "$file_name"
           printf "\nAddress Book '$file_name' is created successfully!\n"
           ;;
        
        2) cat "$file_name"
           ;;

        3) n=1
           while (( n == 1 )); do
               echo "Name:"
               read Name
               echo "Phone_no:"
               read Phone_no
               echo "Address:"
               read Address

               printf "\n$Name \t $Phone_no \t $Address" >> "$file_name"
               echo -e "\nRecord inserted successfully."
               echo "Do you want to continue? [1/0]"
               read n
           done
           ;;
        
        4) printf "Delete a Record\nEnter Name/Phone Number:"
           read pattern
           temp="temp"
           grep -v "$pattern" "$file_name" > "$temp"
           mv "$temp" "$file_name"
           printf "Record of '$pattern' deleted successfully!\n"
           ;;

        5) printf "Modify a Record\nEnter Name/Phone Number:"
           read pattern
           temp="temp"
           grep -v "$pattern" "$file_name" > "$temp"
           mv "$temp" "$file_name"

           printf "Enter new Name: "
           read name
           printf "Enter new Phone_no: "
           read phno
           printf "Enter new Address: "
           read add
           
           printf "\n$name \t $phno \t $add" >> "$file_name"
           printf "\nRecord modified successfully!\n"
           ;;

        6) echo "Goodbye!"
           exit 0
           ;;
        
        *) echo "Invalid option."
           ;;
    esac
done

