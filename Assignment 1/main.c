/*
******** main.c ********

    Student Name 	= Amina Hajiyeva
    Student Number	= 101303729
*/

// Complete the includes
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "a1_functions.h"

const int MAX_MILES = 5;
const int MAX_ACT = 3;
const int MAX_CAPACITY = 100;

int main()
{
    // initialize variables for program
    project_t project;
    milestone_t milestones[MAX_MILES];
    int num_activities[MAX_ACT];
    /** 1-  Display a welcome message **/

    printf("\n\nWelcome to the Project Management Program!\n\n");

    /** 2- Get the project's name and number of milestones **/

    char name_proj[MAX_CAPACITY]; // set char array size to a default value
    // int num_miles;
    printf("\nEnter Project Name: "); // ask and store users input for project name
    scanf("%s", name_proj);

    printf("\nEnter the number of milestone (1-5): "); // ask user to enter number of milestones
    unsigned short int num_miles = get_input_usi();    // check if user enters a positive integer

    while (num_miles < 1 || num_miles > MAX_MILES) // check if user entered a value between 1-5 as required
    {
        printf("\nInvalid Input. Please Enter A Value Between 1 and 5: ");
        num_miles = get_input_usi();
    }

    /** 3- Initialize all milestones and activities.
     * You need an array of milestones.
     * The capacity of the array must be the max number of milestones the program
     * can handle as per the instructions **/

    for (int i = 0; i < num_miles; i++) // iterate through each milestone to determine the number of activities per milestone
    {
        printf("\nEnter the number of activities for milestone %d (1-3): ", i + 1); // ask user to enter number of milestones
        num_activities[i] = get_input_usi();                                        // check if user enters a positive integer

        while (num_activities[i] < 1 || num_activities[i] > MAX_ACT) // check if user entered a value between 1-3 as required, if not, let user try again
        {
            printf("\nInvalid Input. Please Enter A Value Between 1 and 3: ");
            num_activities[i] = get_input_usi();
        }

        init_milestone(&milestones[i], num_activities[i]); // initialize each milestone with its number of activities

        for (int j = 0; j < i; j++) // iterate through milestones
        {
            while (milestones[j].id == milestones[j + 1].id) // check if milestone ID is unique
            {
                for (int k = 0; k < i; k++) // if duplicate ID found, prompt user to enter another ID
                {
                    printf("\nInvalid Input. Please Enter a Valid Unique ID: \n");
                    milestones[k].id = get_input_usi();
                }
            }
        }
    }

    /** 4- Initialize the project **/

    project = init_project(name_proj, milestones, num_miles, num_activities);

    /** 5- Print the main menu **/

    print_main_menu();

    /** 6- Get user choice and handle it as per the instructions**/

    while (true) // allow user to continusously use program until exit is selected
    {
        // determine which menu item user wants to select and store it
        int input;
        printf("\nEnter your selection: (1-3): ");
        scanf("%d", &input);

        if (input < 1 || input > 3) // ensure valid menu item is selected
        {
            printf("\nInvalid Input. Please Enter A Value Between 1 and 3: ");
            scanf("%d", &input);
        }
        else if (input == 3) // quit program if user selects so
        {
            printf("\n\nGoodbye! \n");
            break;
        }
        else if (input == 2) // print project and milestones if user selects so
        {
            print_project_stats(project, milestones, num_miles, num_activities);
            print_milestone_stats(milestones, num_miles, num_activities);
        }
        else if (input == 1)
        {
            for (int i = 0; i < num_miles; i++) // iterate through each milestone
            {
                for (int j = 0; j < num_activities[i]; j++) // iterate through each activity in each milestone
                {
                    if (milestones[i].activity_list[j].completed) // if the activity is complete or incomplete, print it as a sub menu informing user of its status
                        printf("\nActivity Name: %s, ID: %d, Status: Complete ", milestones[i].activity_list[j].name, milestones[i].activity_list[j].id);
                    else
                        printf("\nActivity Name: %s, ID: %d, Status: Still In Progress... ", milestones[i].activity_list[j].name, milestones[i].activity_list[j].id);
                }
            }
        }

        // create initialize variables with default values to be used later on
        int id;
        bool program = false;

        while (true)
        {
            printf("\nPlease enter the ID you will update: "); // get id user will edit
            scanf("%d", &id);

            for (int i = 0; i < num_miles; i++) // iterate through each milestone
            {
                for (int j = 0; j < num_activities[i]; j++) // iterate through each activity in each milestone
                {
                    if (milestones[i].activity_list[j].id == id) // if user enters a valid id, update it to its new value and exit the program
                    {
                        update_activity(&milestones[i].activity_list[j]);
                        break;
                    }
                }

                if (true)
                    break;
            }
            if (false)
                printf("\nInvalid Input. Please enter a valid ID: ");
        }
        print_main_menu(); // bring user back to main menu
    }

    return EXIT_SUCCESS;
}