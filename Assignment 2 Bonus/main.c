/********* main.c ********
    Student Name 	= Amina Hajiyeva
    Student Number	= 101303729
*/

// Includes go here
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "a2_nodes.h"
#include "a2_functions.h"
#include <ctype.h> // for to lower function -- approved by prof during lecture

int main()
{

// since not allowed to user global variables, define constants in main()
#define NUM_POSTS 3 // constant to hold num of posts to be shown to user
#define EXIT 3      // constant for exit menu option in friends and posts menu

    FILE *csv_file = fopen("user_details.csv", "r");
    if (csv_file == NULL)
    {
        perror("Error opening the CSV file");
        return 1;
    }
    // Parse CSV data and create users
    user_t *users = read_CSV_and_create_users(csv_file, 50);

    fclose(csv_file);

    int choice = 0; // declare and populate variables with default values to use later
    int user_choice = 0;
    char username[30];

    do // run program until user quits
    {
        // print out menu and options, then get user input for menu option
        print_menu();
        printf("\nEnter your choice: ");
        scanf("%d", &user_choice);

        while (user_choice > 3 || user_choice < 1) // if user enters an invalid menu option, prompt to try again
        {
            printf("Invalid choice. Please try again.\nEnter your choice: ");
            scanf("%d", &user_choice);
        }

        if (user_choice == 3)
            choice = 5;
        else if (user_choice == 1)
        {
            char pass[15];         // initialize variables with default values to hold users desired username and password
            bool in_user = false;  // initialize boolean to determine whether username is found in program or not
            user_t *index = users; // initialize pointer to iterate through each user
            printf("Enter a username: ");
            scanf("%s", username);

            for (int i = 0; username[i]; i++)       // iterate through each character of username
                username[i] = tolower(username[i]); // convert to lower case

            while (index) // iterate through list for each user
            {
                if (strcmp(index->username, username) == 0) // determine if users username is found in system by comparing to each username in system
                {
                    in_user = true; // if username is found, exit loop and set variable to true to indicate it
                    break;
                }
                index = index->next; // iterate to next index
            }

            if (in_user) // if username found in list
                printf("\nError -- username already exists.\n");
            else // if username not found in list, user can create password
            {
                do
                {
                    printf("Enter a password (8-15 characters): "); // ask user for password
                    scanf("%s", pass);
                    if (strlen(pass) < 8 || strlen(pass) > 15) // if password exceeds limitation
                    {
                        printf("\nError - password exceeds limitations.");
                    }
                    else
                    {
                        users = add_user(users, username, pass);
                        printf("\n********Account Made!********");
                        print_menu_2(username);
                        printf("\nEnter your choice: ");
                        scanf("%d", &choice);
                        while (choice > 6 || choice < 1) // if user enters an invalid menu option, prompt to try again
                        {
                            printf("Invalid choice. Please try again.\nEnter your choice: ");
                            scanf("%d", &choice);
                        }
                        break;
                    }
                } while (true);
            }
        }
        else if (user_choice == 2)
        {
            char pass[15];         // initialize variables with default values to hold users desired username and password
            bool in_user = false;  // initialize boolean to determine whether username is found in program or not
            user_t *index = users; // initialize pointer to iterate through each user
            printf("Enter a username: ");
            scanf("%s", username);

            for (int i = 0; username[i]; i++)       // iterate through each character of username
                username[i] = tolower(username[i]); // convert to lower case

            while (index) // iterate through list for each user
            {
                if (strcmp(index->username, username) == 0) // determine if users username is found in system by comparing to each username in system
                {
                    in_user = true; // if username is found, exit loop and set variable to true to indicate it
                    break;
                }
                index = index->next; // iterate to next index
            }

            if (!in_user) // if username not found in list
            {
                printf("\nError -- username not found.");
                // break;
            }
            else // if username found in list, user can enter password
            {

                printf("Enter your password (8-15 characters): "); // ask user for password
                scanf("%s", pass);
                if (strcmp(pass, index->password) == 0) // if old password matches password found in system, proceed
                {
                    print_menu_2(username);
                    printf("\nEnter your choice: ");
                    scanf("%d", &choice);
                    while (choice > 6 || choice < 1) // if user enters an invalid menu option, prompt to try again
                    {
                        printf("Invalid choice. Please try again.\nEnter your choice: ");
                        scanf("%d", &choice);
                    }
                }
                else
                    printf("Error - incorrect password entered.\nExiting to main menu...");
            }
        }
        switch (choice) // go to users desired menu option...
        {
        case 1: // manage profile
        {
            char old_pass[15], new_pass[15]; // initialize variables with default values to hold users desired username and password
            bool in_user = false;            // initialize boolean to determine whether username is found in program or not
            user_t *index = users;           // initialize pointer to iterate through each user

            while (index) // iterate through list for each user
            {
                if (strcmp(index->username, username) == 0) // determine if users username is found in system by comparing to each username in system
                {
                    in_user = true; // if username is found, exit loop and set variable to true to indicate it
                    break;
                }
                index = index->next; // iterate to next index
            }

            if (in_user) // if username found in list
            {
                printf("Enter the old password: "); // ask user for old password
                scanf("%s", old_pass);
                if (strcmp(old_pass, index->password) == 0) // if old password matches password found in system, proceed
                {
                    printf("Enter a new password. Up to 15 characters: "); // allow user to enter new password of choice
                    scanf("%s", new_pass);
                    strcpy(index->password, new_pass); // update old password with new passowrd
                    printf("**** Password changed! ****\n");
                }
                else
                    printf("Error - incorrect password entered.\nExiting to main menu...");
            }
            else // if username is not found in list, exit program and print user a message
                printf("\n--------------------------------------------------------------\nUser not found.\n--------------------------------------------------------------\n");
            break; // return to main menu
        }
        case 2: // manage posts
        {
            char post[250];        // initialize variables with default values to hold users desired username and password
            bool in_user = false;  // initialize boolean to determine whether username is found in program or not
            int post_choice = 0;   // variable to hold which post menu option user selects
            user_t *index = users; // pointer to go through users list

            while (index) // iterate through list for each user
            {
                if (strcmp(index->username, username) == 0) // determine if users username is found in system by comparing to each username in system
                {
                    in_user = true; // if username is found, exit loop and set variable to true to indicate it
                    break;
                }
                index = index->next; // iterate to next user
            }

            if (in_user) // if username found in list, print out menu and capture choice
            {
                do
                {
                    if (index->posts == NULL) // if no posts exist, inform user
                        printf("Note: No posts avaiable for %s", username);
                    // print posts menu to user
                    printf("\n\n-----------------------------------------------------------------------\nManaging %s's posts\n-----------------------------------------------------------------------\n", username);
                    printf("\n1. Add a new post\n2. Remove a post\n3. Return to main menu\nEnter your choice: ");
                    scanf("%d", &post_choice); // capture users menu choice

                    switch (post_choice) // go to users menu choice
                    {
                    case 1: // add post
                    {
                        printf("\nEnter your post content (Under 250 characters): "); // ask for and capture users new post
                        scanf(" %[^\n]s", post);
                        add_post(index, post); // post users new post

                        // print out username of user to show their posts are being managed
                        printf("\n-----------------------------------------------------------------------\n%s's posts\n-----------------------------------------------------------------------\n", username);
                        display_all_user_posts(index); // print updated list of all of user's posts
                        break;
                    }
                    case 2: // delete post
                    {
                        if (index->posts == NULL) // if user has no posts, there is nothing to delete so print error message
                        {
                            printf("\nError -- No posts exist.\n");
                            break;
                        }

                        delete_post(index); // remove users most recent post and inform of success
                        printf("\nPost removed!\n");
                        display_all_user_posts(index); // print updated list
                        break;
                    }
                    case 3: // return to main menu
                    {
                        printf("\nExiting to main menu...\n");
                        break; // return to main menu
                    }
                    }
                } while (post_choice != EXIT); // keep running post menu until user exits to main menu
            }
            else // if username is not found in list, exit program and print user a message
                printf("\n--------------------------------------------------------------\nUser not found.\n--------------------------------------------------------------\n");
            break; // return to main menu
        }
        case 3: // manage friends
        {
            char new_friend[30], deleted_friend[30];  // initialize variables with default values to hold users desired username and password
            bool in_users = false, in_friend = false; // booleans to check user and friends usernames
            int friend_choice = 0;                    // holds users menu choice
            user_t *index = users;                    // pointer to iterate through each user

            while (index != NULL) // iterate through list for each user
            {
                if (strcmp(index->username, username) == 0) // determine if users username is found in system by comparing to each username in system
                {
                    in_users = true; // if username is found, exit loop and set variable to true to indicate it
                    break;
                }
                index = index->next; // iterate to next user
            }

            if (in_users) // if username found in list, print menu and capture users menu choice
            {
                do
                {
                    bool in_friend = true;
                    // print friend menu to user
                    printf("\n\n-----------------------------------------------------------------------\nManaging %s's friends\n-----------------------------------------------------------------------\n", username);
                    printf("\n1. Add a new friend\n2. Remove a friend\n3. Return to main menu\nEnter your choice: ");
                    scanf("%d", &friend_choice); // capture menu choice for user

                    switch (friend_choice) // go to users desired menu choice
                    {
                    case 1: // add friend
                    {
                        printf("\nEnter a new friend's name: "); // ask for and capture users new friend's name
                        scanf("%s", new_friend);

                        for (int i = 0; new_friend[i]; i++)         // iterate through each character of username
                            new_friend[i] = tolower(new_friend[i]); // convert to lower case

                        while (index) // iterate through list for each user
                        {
                            if (strcmp(index->username, new_friend) == 0) // determine if users username is found in system by comparing to each username in system
                            {
                                in_friend = true; // if username is found, exit loop and set variable to true to indicate it
                                break;
                            }
                            index = index->next; // iterate to next index
                        }

                        if (!in_friend) // if friend found in list
                        {
                            printf("\nError -- user does exist.");
                            break;
                        }
                        else
                        {
                            add_friend(index, new_friend); // add new friend for user
                            printf("Friend added to the list.");
                            break;
                        }
                    }
                    case 2: // delete friend
                    {
                        friend_t *index_friend = index->friends; // pointer to go through each friend of user
                        if (index->friends == NULL)              // if user has no friends, there are no friends to remove, print error message
                        {
                            printf("\nError -- No friends exist.");
                            break;
                        }
                        else
                        {
                            // print list of users friends
                            printf("\nList of %s's friends:", username);
                            display_user_friends(index); // display all of user's friends

                            printf("\nEnter a friend's name to delete: "); // ask and capture friend user wishes to delete
                            scanf("%s", deleted_friend);

                            while (index_friend != NULL) // iterate through friends for user to find target friend
                            {
                                if (strcmp(index_friend->username, deleted_friend) == 0) // determine if friend username is found in system by comparing to each friends username in system
                                {
                                    in_friend = true;                     // if username is found, exit loop and set variable to true to indicate it
                                    delete_friend(index, deleted_friend); // remove users chosen friend and inform of success
                                    printf("Friend removed!\n\nUpdated list of %s's friends: ", username);
                                    display_user_friends(index); // print updated list of users friends
                                    break;
                                }

                                index_friend = index_friend->next; // iterate to user's next friend
                            }

                            if (!in_friend) // if friends name not found in list, show error message to user
                                printf("Invalid friend's name");
                            break;
                        }
                    }
                    case 3: // exit to main menu
                    {
                        printf("\nExiting to main menu...");
                        break; // return to main menu
                    }
                    }
                } while (friend_choice != EXIT); // keep popping friends menu up until user exits
            }
            else // if username is not found in list, exit program and print user a message
                printf("\n--------------------------------------------------------------\nUser not found.\n--------------------------------------------------------------\n");
            break; // return to main menu
        }
        case 4: // print posts in 'n' intervals
        {
            char friend[30];
            bool in_friend = false;
            friend_t *index = users->friends; // check all of users friends, to find friend's post to print

            printf("Enter a friend's username to view their posts: "); // capture name of friend user wants to see
            scanf("%s", friend);

            user_t *user_friend = find_user(users, friend); // check if friend is found

            if (user_friend != NULL) // if username of friend is found in database, check if user is friends with them
            {
                while (index != NULL) // iterate through friends for user to find target friend
                {
                    if (strcmp(index->username, user_friend->username) == 0) // determine if friend username is found in system by comparing to each friends username in system
                    {
                        in_friend = true; // if username is found, exit loop and set variable to true to indicate it
                        break;
                    }

                    index = index->next; // iterate to user's next friend
                }
            }

            if (in_friend && user_friend != NULL)
            {
                display_posts_by_n(user_friend, NUM_POSTS); // display posts in intervals of 3 as instructed
            }
            else
            {
                printf("\n\nError -- Friend does not exist.\n\n");
                break;
            }

            break;
        }
        case 5: // exit program
        {       // if user wants to exit program, print goodbye message and exit program
            printf("\nExiting program...Goodbye!\n\n");
            teardown(users); // call teardown function as instructed to free everything from everyone
            users = NULL;    // ensure users is null
            exit(0);         // exit program
        }
        }
    } while (true); // run until user exits program, case 6
}
