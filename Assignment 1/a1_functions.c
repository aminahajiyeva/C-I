/*
******** a1_functions.c ********

   Student Name 	= Amina Hajiyeva
   Student Number	= 101303729
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "a1_functions.h"

const int HOURLY_PAY = 30;
const int HOURS = 8;
const float DAY = 24.0;
const int MAX_PRINT = 10;

/*
   Get unsigned short integer user input.wh
   The value entered by the user must be positive.
   If the user enters a negative value, the function asks user to re-enter a positive value.
*/
unsigned short int get_input_usi(void)
{
   unsigned short int user_input;
   do
   {
      scanf("%hu", &user_input);
      if (user_input < 0)
      {
         printf("ERROR: Must Enter a positive unsigned short integer value.\nPlease Try Again.\nEnter a positive unsigned short integer value: ");
      }
   } while (user_input < 0);
   return user_input;
}

/*
   Get float user input. The value must be positive.
   The value entered by the user must be positive.
   If the user enters a negative value, the function asks user to re-enter a positive value.
*/
float get_input_f(void)
{
   float user_input;
   do
   {
      printf("Enter a positive float value: ");
      scanf("%f", &user_input);
      if (user_input < 0)
         printf("ERROR: Must Enter a positive float value.\nPlease Try Again: ");
   } while (user_input < 0);
   return user_input;
}

/*
   Initialize all fields in an activity as per the instructions (3)
*/
void init_activity(activity_t *activity_to_int)
{
   printf("Please enter activity ID: "); // prompt user and store answer for activity ID
   activity_to_int->id = get_input_usi();

   printf("Please Enter Activity Name:"); // prompt user and store answer for activity name
   scanf("%s\n", activity_to_int->name);

   printf("Please Enter Activity Planned Duration (Hours): \n"); // prompt user and store answer for activity duration in hours
   activity_to_int->planned_duration = get_input_usi();

   // calculate planned cost using given equation
   activity_to_int->planned_cost = activity_to_int->planned_duration * HOURLY_PAY; // average company salary is $30/hour so use that in formula for hourly pay

   // assign default values to rest of memebers
   activity_to_int->actual_cost = 0;
   activity_to_int->actual_duration = 0;
   activity_to_int->completed = false;
}
/*
   Initialize all fields in the milestone as per the instructions (3)
   The implementation of your function MUST call the function init_activity.
*/
void init_milestone(milestone_t *milestone_to_int, unsigned short int num_activities)
{
   printf("Please enter milestone ID: "); // prompt user and store answer for milestone ID
   milestone_to_int->id = get_input_usi();

   printf("\nPlease Enter Milestone Name: "); // prompt user and store answer for milestone name
   scanf("%s", milestone_to_int->name);

   for (int i = 0; i < num_activities; i++) // iterate through each activity in the milestone and initialize it
   {
      printf("\nInitializing activity number: %d \n", i + 1); // show which acitivity is being initialized to user
      init_activity(&milestone_to_int->activity_list[i]);
   }

   // assign default values to rest of memebers
   milestone_to_int->actual_cost = 0;
   milestone_to_int->actual_duration = 0;
   milestone_to_int->completed = false;
}

/*
   Initialize all fields in the project as per the instructions (4)
   number_activities contains the number of activities per milestone
*/
project_t init_project(char name[], milestone_t *milestone_list, int number_milestones, const int *number_activities)
{
   project_t project; // create new project to store all given information

   // assign default values to rest of members
   project.actual_cost = 0.0;
   project.actual_duration = 0;
   project.completed = false;
   project.planned_cost = 0.0;

   int total_days = 0; // create variable to hold all days totaled from all the activites

   strcpy(project.name, name); // initialize project name

   for (int i = 0; i < number_milestones; i++) // iterate through all milestones in project
   {
      printf("\nInitializing activity number: %d \n", i + 1);   // show which milestone is being initialized to user
      init_milestone(&milestone_list[i], number_activities[i]); // initialize milestones

      for (int j = 0; j < number_activities[i]; j++) // iterate through each activity within milestone
      {
         // Sum planned costs from all activities
         project.planned_cost += milestone_list[i].activity_list[j].planned_cost;

         // Sum planned durations from all activities (in days)
         total_days += milestone_list[i].activity_list[j].planned_duration;
      }
   }

   project.planned_duration = ceil((total_days) / HOURS); // find sum of days by diving by hours in a day, 8 hours = 1 day, as instructed

   return project; // return the project to the user
}

/*
   Print the main menu as per the instructions (5)
*/
void print_main_menu(void)
{
   printf("\nPlease select one of the following options:\n1. Update activity\n2. Print stats\n3. Exit");
}

/*
   Print out milestone stats as per the instructions (6)
   number_activities contains the number of activities per milestone
*/
void print_milestone_stats(const milestone_t *list_milestones, int num_milestones, const int *number_activities)
{
   for (int i = 0; i < num_milestones; i++) // iterate through each milestone
   {
      // declare and populate default values in variable which will be used later on
      float planned_cost = 0.0, actual_cost = 0.0;
      short int planned_time = 0, actual_time = 0;
      int completed = 0;

      for (int j = 0; j < number_activities[i]; j++) // iterate through each activity
      {
         // calculate the total planned and actual cost and time amoungst all the activities as instructed
         planned_cost += list_milestones[i].activity_list[j].planned_cost;
         planned_time += list_milestones[i].activity_list[j].planned_duration;

         actual_cost += list_milestones[i].activity_list[j].actual_cost;
         actual_time += list_milestones[i].activity_list[j].actual_duration;

         if (list_milestones[i].activity_list[j].completed) // if the milestone's activity is completed, indicate so through a counter
            completed++;
      }

      bool complete = (completed == number_activities[i]); // determine if all the activities are complete

      if (complete) // if all the activites in the milestone are complete
      {
         printf("Milestone name: %s", list_milestones[i].name); // show user which milestone is being accessed
         float budget = actual_cost - planned_cost;             // calculate the overall budget difference (over, under, on budget)

         // indicate to user how much over, under or if the cost was on budget
         if (budget > 0.0)
            printf("\nCost: $%.2f over budget\n", budget);
         else if (budget < 0.0)
            printf("\nCost: $%.2f under budget\n", budget * -1);
         else
            printf("\nCost: $%.2f and was on budget\n", budget);

         // determine times in days
         float planned_days = planned_time / DAY;
         float actual_days = actual_time / DAY;
         // determine overall time - remember a day cannot be a decimal (no such thing as 1.37777 days)
         short int days_diff = (int)ceil(actual_days - planned_days);

         // indicate to user how much over, under or if the time was as expected
         if (days_diff > 0)
            printf("\nThis milestone is %d days delayed\n", days_diff);
         else if (days_diff < 0)
            printf("\nThis milestone is %d days early\n", days_diff * -1);
         else
            printf("\nThis milestone took %d days and was on time\n", days_diff);
      }
      else // if not complete, print information as instructed
         printf("\nMilestone name: %s\nActivities Completed: %d/%d\nPlanned Time in Days: %d\nPlanned Cost: $%.2f\n", list_milestones[i].name, completed, number_activities[i], planned_time / DAY, planned_cost);
   }
}

/*
   Print out project stats as per the instructions (6)
   number_activities contains the number of activities per milestone
   The implementation MUST call print_stats_milestone
*/
void print_project_stats(project_t details, const milestone_t *list_milestones, int num_milestones, const int *number_activities)
{
   // initialize variables to use later on
   int budget, time;
   char print_budget[MAX_PRINT], print_time[MAX_PRINT];

   if (details.completed) // as following instructions, if project is completed determine over/under time and budget
   {
      printf("\n\nProject Stats\nProject Name: %s \nProject Status: Completed!", details.name); // print out information about project as instructed - keeping in mind whether project is completed or not

      // Calculate and print over/under budget and time, also create strings indicating this to later return to user
      budget = details.actual_cost - details.planned_cost; // determine if project was over or under budget
      if (budget > 0)
         strcpy(print_budget, "Over");
      else if (budget < 0)
      {
         strcpy(print_budget, "Under");
         budget *= -1;
      }
      else
         strcpy(print_budget, "On Budget");

      time = details.actual_duration - details.planned_duration; // determine how many days project was early or delayed
      if (time > 0)
         strcpy(print_time, "Over");
      else if (time < 0)
      {
         strcpy(print_time, "Under");
         time *= -1;
      }
      else
         strcpy(print_time, "On Time");
   }
   else
   {
      printf("\n\nProject Stats\nProject Name: %s \nProject Status: Still In Progress...", details.name); // print out information about project as instructed - keeping in mind whether project is completed or not

      for (int i = 0; i < num_milestones; i++) // iterate through each milestone
      {
         int planned_time = 0, planned_cost = 0, completed = 0; // reset values for each milestone to ensure correct calcuations of each milestone
         printf("Milestone: %s\n", list_milestones[i].name);    // indicate to user which milestone is being accessed

         for (int j = 0; j < number_activities[i]; j++) // for each activity within the milestone determine the missing values
         {
            planned_cost += list_milestones[i].activity_list[j].planned_cost; // determine planned costs/time and actual costs/time by adding each member from each activity
            planned_time += list_milestones[i].activity_list[j].planned_duration;
            if (list_milestones[i].activity_list[j].completed) // determine how many activites from the milestone are completed
               completed++;
         }

         if (list_milestones[i].completed) // if the milestone is completed
         {
            // For completed milestones, calculate over/under budget and time, also create strings indicating this to later return to user
            budget = list_milestones[i].actual_cost - planned_cost;
            if (budget > 0)
               strcpy(print_budget, "Over");
            else if (budget < 0)
               strcpy(print_budget, "Under");
            else
               strcpy(print_budget, "On Budget");

            time = list_milestones[i].actual_duration - planned_time;
            if (time > 0)
               strcpy(print_time, "Over");
            else if (time < 0)
               strcpy(print_time, "Under");
            else
               strcpy(print_time, "On Time");

            printf("\n\nStatus: Completed!\nBudget: %s by $%d\nTime: %s by %d days\n", print_budget, budget, print_time, time); // show user findings
         }
         else
         {
            // For incomplete milestones, display planned cost, duration, and completed activities
            printf("\n\nStatus: Still In Progress...\nBudget: %d\nTime: %d\n%d out of %d activities completed\n", planned_cost, planned_time, completed, number_activities[i]);
         }
      }
   }
}

/*
   Update activity per the instructions (6)
*/
void update_activity(activity_t *activity_to_update)
{
   int completed;                                                            // initiate variable to hold whether the activity was completed or not
   printf("\nPlease enter the actual duration of this activity in hours: "); // update the activity with the actual duration of the activity in hours, as inputted by user
   activity_to_update->actual_duration = get_input_usi();

   do // determine if activity is completed or not
   {
      printf("\nPlease enter is the activity is complete (0 = No, 1 = Yes): "); // ensure user enters valid value of either 0 or 1, if not, prompt user to enter again until valid value entered
      completed = get_input_usi();
   } while (completed != 0 && completed != 1);

   activity_to_update->completed = completed;                                          // update activity with information on whether it was completed or not
   activity_to_update->actual_cost = activity_to_update->actual_duration * HOURLY_PAY; // update activity actual cost by calcuating it using the given formula in the instructions
}

/*
   Update milestone per the instructions (6)
*/
void update_milestone(milestone_t *milestone_to_update, int activities_in_milestone)
{
   // give default values to members that will be used later on
   milestone_to_update->actual_cost = 0.0;
   milestone_to_update->actual_duration = 0;
   bool completed = true;

   for (int i = 0; i < activities_in_milestone; i++) // iterate through each activity in milestone
   {
      update_activity(&milestone_to_update->activity_list[i]);
      if (!milestone_to_update->activity_list[i].completed) // determine if activity is completed or not
         completed = false;
   }

   milestone_to_update->completed = completed; // fill completed member of milestone structure with boolean indicating whether it is completed or not

   if (milestone_to_update->completed) // determine if milestone is completed
   {
      for (int i = 0; i < activities_in_milestone; i++) // for each activity in the milestone, calculate their actual cost and actual duration
      {
         milestone_to_update->actual_cost += milestone_to_update->activity_list[i].actual_cost;
         milestone_to_update->actual_duration += milestone_to_update->activity_list[i].actual_duration;
      }
      printf("\n\nMilestone is complete. "); // inform user of milestone completion
   }
   else
      printf("\n\nMilestone is still in progress. ");
}

/*
   Update project per the instructions (6)
   number_activities contains the number of activities per milestone
*/
void update_project(const milestone_t *milestone_array, int num_milestones, const int *number_activities, project_t *my_project)
{
   // give default values to members that will be used later on
   my_project->actual_cost = 0.0;
   my_project->actual_duration = 0;
   bool completed = true;

   for (int i = 0; i < num_milestones; i++) // iterate through each milestone in the project
   {
      update_milestone(&milestone_array[i], number_activities[i]);

      if (milestone_array[i].completed) // if the milestone is completed, recalculate its actual cost and actual duration
      {
         my_project->actual_cost += milestone_array[i].actual_cost;
         my_project->actual_duration += milestone_array[i].actual_duration;
      }
      else
         completed = false;
   }

   my_project->completed = completed; // finalize whether the project is completed or not

   if (my_project->completed) // inform user of whether project is completed or not
      printf("\n\nProject is complete. ");
   else
      printf("\n\nProject is still in progress. ");
}