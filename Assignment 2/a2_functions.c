/*****************
    Student Name 	= Amina Hajiyeva
    Student Number	= 101303729
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <time.h>
#include "a2_nodes.h"
#include "a2_functions.h"

// Your solution goes here

/*
   Function that creates a new user and adds it to a sorted (ascending order) linked list at
   the proper sorted location. Return the head of the list.
*/
user_t *add_user(user_t *users, const char *username, const char *password)
{
   user_t *user_new = malloc(sizeof(user_t)); // allocate memory for a new user
   assert(user_new != NULL);                  // make sure allocation worked, otherwise terminate program

   strcpy(user_new->username, username); // set new user's username to given username
   strcpy(user_new->password, password); // set new user's password to given password
   user_new->friends = NULL;             // since user has no friends for now, set to NULL
   user_new->posts = NULL;               // since user has no posts for now, set to NULL
   user_new->next = NULL;                // set next to NULL

   if (users == NULL) // check if no users in list
   {
      user_new->next = users; // set new user's next to users, which is empty, which is NULL
      return user_new;        // return one and only user (since its the head of the list)
   }

   // check if user's username should come first in ordered list of users already in list...
   if (strcmp(user_new->username, users->username) < 0)
   {
      user_new->next = users->next; // new user's next pointer will point to next user in list
      users->next = user_new;       // first user in list is now the new user
      return user_new;              // return new user (as its head of the list)
   }
   else
   {
      user_t *current_user = users; // user pointer to later go through each user in list
      // go through each user in list, until position for new user is located
      while (current_user->next != NULL && strcmp(user_new->username, current_user->username) < 0)
      {
         current_user = current_user->next; // go to next user
      }

      user_new->next = current_user->next; // new user's next pointer points to next user in list
      current_user->next = user_new;       // previous user is now the new user
      return users;                        // return head of list
   }
}

/*
   Function that searches if the user is available in the database
   Return a pointer to the user if found and NULL if not found.
*/
user_t *find_user(user_t *users, const char *username)
{
   user_t *user = users; // pointer to iterate through each user

   while (user != NULL) // iterate through each user in list
   {
      if (strcmp(username, user->username) == 0) // if user's username matches target username...
         return user;                            // return found user

      user = user->next; // go to next user
   }
   return NULL; // if user not found, return null
}

/*
   Function that creates a new friend's node.
   Return the newly created node.
*/
friend_t *create_friend(const char *username)
{
   friend_t *new_friend = malloc(sizeof(friend_t)); // allocate memory for friend
   assert(new_friend != NULL);                      // make sure allocation worked, otherwise terminate program

   strcpy(new_friend->username, username); // copy new friend username, into new friend's username
   new_friend->next = NULL;                // set next pointer to null, since no other friends
   return new_friend;                      // return new friend to user
}

/*
   Function that links a friend to a user. The friend's name should be added into
   a sorted (ascending order) linked list.
*/
void add_friend(user_t *user, const char *friend)
{
   friend_t *new_friend = create_friend(friend); // create new friend using given information by calling function

   // if user has no friends, or new friend comes first by order...
   if (user->friends == NULL || (strcmp(new_friend->username, user->friends->username) < 0))
   {
      new_friend->next = user->friends; // insert friend at beginning of list
      user->friends = new_friend;       // make new friend first in list of friends
      return;                           // exit function since friend has been added...no need to continue
   }

   friend_t *current_friend = user->friends; // iterate through user's each friend

   // go through list of user's friends until position is found
   while (current_friend->next != NULL && (strcmp(new_friend->username, current_friend->next->username) > 0))
   {
      current_friend = current_friend->next; // go to next friend
   }

   new_friend->next = current_friend->next; // make new friend the next friend
   current_friend->next = new_friend;       // and make previous friend the new friend
}

/*
   Function that removes a friend from a user's friend list.
   Return true of the friend was deleted and false otherwise.
*/
_Bool delete_friend(user_t *user, char *friend_name)
{
   friend_t *index_friends = user->friends; // pointer to go through all of users friends, starts at beginning
   friend_t *index_previous = NULL;         // pointer for previous friend

   while (index_friends != NULL) // go through each friend of user
   {
      if (strcmp(friend_name, index_friends->username) == 0) // if target username to delete is found...
      {
         if (index_previous == NULL)             // if friend to delete is first in list...
            user->friends = index_friends->next; // change head to next friend

         else                                           // if friend to delete is not first
            index_previous->next = index_friends->next; // previous friend next pointer can skip to next node

         free(index_friends); // delete friend
         return true;         // return true to indicate successfull deletion of friend
      }

      index_previous = index_friends;      // previous friend is now current friend
      index_friends = index_friends->next; // move to next friend
   }

   return false; // return false if friend was not sucessfully deleted
}

/*
   Function that creates a new user's post.
   Return the newly created post.
*/
post_t *create_post(const char *text)
{
   post_t *new_post = malloc(sizeof(post_t)); // allocate memory for post
   assert(new_post != NULL);                  // make sure allocation worked, otherwise terminate program

   strcpy(new_post->content, text); // copy new post content, into new post
   new_post->next = NULL;           // set next pointer to null, since no other posts
   return new_post;                 // return new post to user
}

/*
   Function that adds a post to a user's timeline following a stack.
*/
void add_post(user_t *user, const char *text)
{
   post_t *post = create_post(text); // create post by calling function
   post->next = user->posts;         // link new post to list of posts
   user->posts = post;               // make new post head of posts
}

/*
   Function that removes a post from a user's list of posts.
   Return true if the post was deleted and false otherwise.
*/
_Bool delete_post(user_t *user)
{
   if (user->posts != NULL) // if user has posts
   {
      post_t *post = user->posts; // pointer to hold post (first in list) to be deleted
      user->posts = post->next;   // set head of posts to next post, since head will be deleted
      free(post);                 // free, or delete, post
      return true;                // return true to indicate succesfull deletion of post
   }
   else             // if user does not have posts
      return false; // return false if post was not sucessfully deleted or if there was no post to delete
}

/*
   Function that  displays a specific user's posts (All posts)
*/
void display_all_user_posts(user_t *user)
{
   post_t *post = user->posts; // user pointer to iterate through each post of user
   int num = 1;                // keep count of number of posts

   while (post != NULL) // iterate through each post
   {
      printf("\n%d - %s", num, post->content); // print using given format the content and number of post
      post = post->next;                       // go to next post
      num++;                                   // increment counter to correctly keep track of posts
   }
}

/*
   Function that displays a specific user's friends (All friends)
*/
void display_user_friends(user_t *user)
{
   friend_t *friend = user->friends; // user pointer to iterate through each friend of user
   int num = 1;                      // keep count of number of friends

   while (friend != NULL) // iterate through each friend
   {
      printf("\n%d - %s", num, friend->username); // print using given format the username and number of friend
      friend = friend->next;                      // go to next friend
      num++;                                      // increment counter to correctly keep track of friends
   }
}

/*
   Function that displays "number" of posts for a given user.
   After displaying "number" posts, it prompts if you want to display
   more posts.
   If there are no more post or the user types “n” or “N”, the function returns.
*/
void display_posts_by_n(user_t *users, int number)
{
   post_t *post_count = users->posts; // user pointer to find number of posts of user
   char more_posts;                   // variable to hold whether user wants more posts, later
   int count = 0;                     // counts how many posts there are

   while (post_count != NULL) // find number of posts
   {
      count++;                       // increase counter for number of posts
      post_count = post_count->next; // go to next post
   }

   post_t *post = users->posts; // user pointer to go through each post of user

   for (int i = 1; i <= number; i++) // iterate through 'n' posts
   {
      printf("\n%d - %s", i, post->content); // print posts in given format
      post = post->next;                     // go to next post
      count--;                               // decrement counter
   }

   printf("\nDo you want to display more posts? (y/n) "); // determine if user wants more posts printed
   scanf("%s", &more_posts);

   if (post != NULL && (more_posts == 'Y' || more_posts == 'y')) // if more posts available and user wants to print more...
   {
      if (count < number)                           // if the number of posts remaning to print is less than 'n' number of posts to be printed at once...
         display_posts_by_n(users, count + number); // print remaning posts, ignoring 'n'
      else
         display_posts_by_n(users, number += number); // call function to post more 'n' posts
      count--;                                        // decrement counter
   }
   else if (more_posts == 'N' || more_posts == 'n') // if user doesnt want any more posts printed, exit back to menu
      return;
   else
   {
      printf("\nAll posts have been displayed!"); // if all posts are printed, inform user
      return;                                     // otherwise return function
   }
}

/*
   Function that free all users from the database before quitting the application.
*/
void teardown(user_t *users)
{
   /*
    while (users != NULL)
    {
       user_t *delete = users;
       users = users->next;

       friend_t *friend = delete->friends;
       while (friend != NULL)
       {
          friend_t *delete_f = friend;
          friend = friend->next;
          free(delete_f);
       }

       post_t *post = delete->posts;
       while (post != NULL)
       {
          post_t *delete_p = post;
          post = post->next;
          free(delete_p);
       }
       free(delete);
    }*/

   while (users != NULL) // iterate through each post
   {
      user_t *user = users; // pointer to go through each user

      friend_t *friend = user->friends; // pointer to go through each user's friends
      post_t *post = user->posts;       // pointer to go through each user's posts

      while (friend != NULL) // iterate through each friend
      {
         friend_t *deleted_friend = friend; // capture current friend as friend to delete
         friend = friend->next;             // go to next friend
         free(deleted_friend);              // delete current friend
      }

      while (post != NULL) // iterate through each post
      {
         post_t *deleted_post = post; // capture current post as post to delete
         post = post->next;           // go to next post
         free(deleted_post);          // delete current post
      }

      free(user);          // delete user
      users = users->next; // go to next user
   }
}

/*
   Function that prints the main menu with a list of options for the user to choose from
*/
void print_menu()
{
   // print out menu options
   printf("\n\n***********************************************\n\t\tMAIN MENU:\t\t\n***********************************************\n");
   printf("\n1. Register a new user\n2. Manage a user's profile (change password)\n3. Manage a user's posts (add/remove)\n4. Manage a user's friends (add/remove)\n5. Display a user's posts\n6. Exit\n");
}

/*
   ******** DONT MODIFY THIS FUNCTION ********
   Function that reads users from the text file.
   IMPORTANT: This function shouldn't be modified and used as is
   ******** DONT MODIFY THIS FUNCTION ********
*/
user_t *read_CSV_and_create_users(FILE *file, int num_users)
{
   srand(time(NULL));
   user_t *users = NULL;
   char buffer[500];
   fgets(buffer, sizeof(buffer), file); // Read and discard the header line
   int count = 0;
   for (int i = 0; i < num_users; i++)
   {
      fgets(buffer, sizeof(buffer), file);
      buffer[strcspn(buffer, "\r\n")] = 0; // Remove newline characters

      char *token = strtok(buffer, ",");
      char *token2 = strtok(NULL, ",");
      users = add_user(users, token, token2);
      char *username = token;

      token = strtok(NULL, ",");

      user_t *current_user = users;
      for (; current_user != NULL && strcmp(current_user->username, username) != 0; current_user = current_user->next)
         ;

      while (token != NULL && strcmp(token, ",") != 0 && count < 3)
      {
         if (strcmp(token, " ") != 0)
         {
            add_friend(current_user, token);
         }
         token = strtok(NULL, ",");
         count++;
      }
      count = 0;

      // token = strtok(NULL, ",");
      while (token != NULL && strcmp(token, ",") != 0)
      {
         add_post(current_user, token);
         token = strtok(NULL, ",");
      }
   }
   return users;
}
