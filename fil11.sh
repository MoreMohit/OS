#!/bin/bash

# Function to create a new address book
CREATE() {
    echo " >> Enter Name of the Address Book: "
    read name
    result=$(ls | grep -w "$name" | wc -w)
    if [ $result -gt 0 ]; then
        echo " ---> Sorry, file already exists!"
    else
        touch "$name"
        echo " ---> File created successfully!"
    fi
}

# Function to display contents of the address book
DISPLAY() {
    result=$(ls | grep -w "$name" | wc -w)
    if [ $result -gt 0 ]; then
        cat "$name"
    else
        echo " ---> File does not exist!"
    fi
}

# Function to insert a new record
INSERT() {
    result=$(ls | grep -w "$name" | wc -w)
    if [ $result -gt 0 ]; then
        echo " >> Enter your E-mail: "
        read email
        len=$(grep -w "$email" "$name" | wc -w)
        if [ $len -gt 0 ]; then
            echo " ---> Record already exists!"
        else
            echo " Enter First Name: "
            read fname
            echo " Enter Last Name: "
            read lname
            echo " Enter Mob-No: "
            read mobno
            record="$fname $lname $email $mobno"
            echo "$record" >> "$name"
            echo " ---> Record inserted successfully!"
        fi
    else
        echo " ---> File does not exist!"
    fi
}

# Function to modify an existing record
MODIFY() {
    result=$(ls | grep -w "$name" | wc -w)
    if [ $result -gt 0 ]; then
        echo " >> Enter your E-mail: "
        read email
        len=$(grep -w "$email" "$name" | wc -w)
        if [ $len -gt 0 ]; then
            echo " Enter First Name: "
            read fname
            echo " Enter Last Name: "
            read lname
            echo " Enter Mob-No: "
            read mobno
            new="$fname $lname $email $mobno"
            old=$(grep -w "$email" "$name")
            echo " --> Old Record: $old"
            echo " --> New Record: $new"
            sed -i "s|$old|$new|g" "$name"
            echo " ---> Record modified successfully!"
        else
            echo " ---> Record not found!"
        fi
    else
        echo " ---> File does not exist!"
    fi
}

# Function to delete a record
DELETE() {
    result=$(ls | grep -w "$name" | wc -w)
    if [ $result -gt 0 ]; then
        echo " >> Enter your E-mail: "
        read email
        len=$(grep -w "$email" "$name" | wc -w)
        if [ $len -gt 0 ]; then
            old=$(grep -w "$email" "$name")
            sed -i "s|$old||g" "$name"
            sed -i '/^$/d' "$name"
            echo " ---> Record deleted successfully!"
        else
            echo " ---> Record not found!"
        fi
    else
        echo " ---> File does not exist!"
    fi
}

# Function to search for a record by email
SEARCH() {
    result=$(ls | grep -w "$name" | wc -w)
    if [ $result -gt 0 ]; then
        echo " >> Enter E-mail: "
        read email
        len=$(grep -w "$email" "$name" | wc -w)
        if [ $len -gt 0 ]; then
            rec=$(grep -w "$email" "$name")
            echo " ---> Record found!"
            echo "$rec"
        else
            echo " ---> Record not found!"
        fi
    else
        echo " ---> File does not exist!"
    fi
}

# Main program loop with menu
while true; do
    echo " <<<<< MENU >>>>> "
    echo " 1] Create."
    echo " 2] Display."
    echo " 3] Insert Record."
    echo " 4] Modify Record."
    echo " 5] Delete Record."
    echo " 6] Search Record."
    echo " 7] Exit."
    echo " >> Enter Your Choice: "
    read choice
    case $choice in
        1) CREATE ;;
        2) DISPLAY ;;
        3) INSERT ;;
        4) MODIFY ;;
        5) DELETE ;;
        6) SEARCH ;;
        7) exit ;;
        *) echo " ---> Wrong choice!" ;;
    esac
done
