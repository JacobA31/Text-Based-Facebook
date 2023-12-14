/********* definitions.c ********
    Student Name 	= Jacob Aydin
    Student Number	= 101264856
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include "a3_nodes.h"
#include "a3_functions.h"

// Your solution goes here

/*
   Function that creates a new user and adds it to a sorted (ascending order) linked list at
   the proper sorted location. Return the head of the list.
*/
user_t *add_user(user_t *users, const char *username, const char *password)
{
   user_t *new = malloc(sizeof(user_t));
   assert(new != NULL);

   strcpy(new->username, username);
   strcpy(new->password, password);
   new->friends = NULL;
   new->posts = NULL;
   new->next = NULL;

   if (users == NULL || username[0] < users->username[0])
   {
      new->next = users;
      return new;
   }

   user_t *pre = NULL;
   user_t *cur = users;
   while (cur != NULL && username[0] >= cur->username[0])
   {
      pre = cur;
      cur = cur->next;
   }

   pre->next = new;
   new->next = cur;

   return users;
}
/*
   Function that searches if the user is available in the database
   Return a pointer to the user if found and NULL if not found.
*/
user_t *find_user(user_t *users, const char *username)
{
   user_t *find = users;

   while (find != NULL)
   {
      if (strcmp(find->username, username) == 0)
      {
         return find;
      }
      find = find->next;
   }

   return NULL;
}
_Bool compare(user_t *users, const char *username, const char *password)
{
   user_t *find = find_user(users, username);
   if(find == NULL){
      return false;
   }
   if (strcmp(find->password, password) == 0)
   {
      return true;
   }
   return false;
}
/*
   Function that creates a new friend's node.
   Return the newly created node.
*/
friend_t *create_friend(const char *username)
{
   friend_t *new = malloc(sizeof(friend_t));
   assert(new != NULL);

   strcpy(new->username, username);
   new->next = NULL;

   return new;
}

/*
   Function that links a friend to a user. The friend's name should be added into
   a sorted (ascending order) linked list.
*/
void add_friend(user_t *user, const char *friend)
{
   friend_t *add = create_friend(friend);

   if (user->friends == NULL || friend[0] < user->friends->username[0])
   {
      add->next = user->friends;
      user->friends = add;
      return;
   }
   friend_t *pre = NULL;
   friend_t *cur = user->friends;

   while (cur != NULL && friend[0] >= cur->username[0])
   {
      pre = cur;
      cur = cur->next;
   }
   pre->next = add;
   add->next = cur;
}

/*
   Function that removes a friend from a user's friend list.
   Return true of the friend was deleted and false otherwise.
*/
_Bool delete_friend(user_t *user, char *friend_name)
{
   friend_t *del_f = user->friends;
   friend_t *prev = NULL;

   while (del_f != NULL && strcmp(del_f->username, friend_name) != 0)
   {
      prev = del_f;
      del_f = del_f->next;
   }
   if (del_f == NULL)
   {
      return false;
   }
   if (prev == NULL)
   {
      user->friends = del_f->next;
   }
   else
   {
      prev->next = del_f->next;
   }
   free(del_f);
   return true;
}

/*
   Function that creates a new user's post.
   Return the newly created post.
*/
post_t *create_post(const char *text)
{
   post_t *new = malloc(sizeof(post_t));
   assert(new != NULL);
   strcpy(new->content, text);
   new->next = NULL;
   return new;
}

/*
   Function that adds a post to a user's timeline. New posts should be added following
   the stack convention (LIFO) (i.e., to the beginning of the Posts linked list).
*/
void add_post(user_t *user, const char *text)
{
   if (user->posts == NULL)
   {
      user->posts = create_post(text);
   }
   else
   {
      post_t *last = user->posts;
      while (last->next != NULL)
      {
         last = last->next;
      }
      last->next = create_post(text);
   }
}

/*
   Function that removes a post from a user's list of posts.
   Return true if the post was deleted and false otherwise.
*/
_Bool delete_post(user_t *user, int number)
{
   if (user->posts == NULL)
   {
      return false;
   }
   if (number == 1)
   {
      post_t *del = user->posts;
      user->posts = user->posts->next;
      free(del);
      return true;
   }
   post_t *old = user->posts;
   for (int i = 1; i < number - 1 && old->next != NULL; i++)
   {
      old = old->next;
   }
   if (old == NULL || old->next == NULL)
   {
      return false;
   }
   post_t *del = old->next;
   old->next = del->next;
   free(del);
   return true;
}

/*
   Function that  displays a specific user's posts
*/
void display_user_posts(user_t *user)
{
   printf("------------------------------------\n");
   printf("              %s's posts            \n", user->username);
   if (user->posts == NULL)
   {
      printf("No posts available for %s\n", user->username);
   }
   else
   {
      post_t *cur = user->posts;
      int i = 1;
      while (cur != NULL)
      {
         printf("%d- %s\n", i, cur->content);
         cur = cur->next;
         i++;
      }
   }
   printf("------------------------------------\n");
}

/*
   Function that displays a specific user's friends
*/
void display_user_friends(user_t *user)
{
   printf("List of %s's friends:\n", user->username);
   if (user->friends == NULL)
   {
      printf("No friends available for %s\n", user->username);
   }
   else
   {
      friend_t *cur = user->friends;
      int i = 1;
      while (cur != NULL)
      {
         printf("%d- %s\n", i, cur->username);
         cur = cur->next;
         i++;
      }
   }
}
/*
   Function that displays all the posts of 2 users at a time from the database.
   After displaying 2 users' posts, it prompts if you want to display
   posts of the next 2 users.
   If there are no more post or the user types “n” or “N”, the function returns.
*/
void display_all_posts(user_t *users)
{
   user_t *find = users;
   while (find != NULL && find->next != NULL)
   {
      printf("%s's Posts:\n", find->username);
      display_user_posts(find);

      printf("%s's Posts:\n", find->next->username);
      display_user_posts(find->next);

      char ans;
      printf("\nDo you want to display next 2 users posts? (Y/N):");
      scanf(" %c", &ans);
      if (ans == 'N' || ans == 'n')
      {
         break;
      }
      if (find->next->next != NULL)
      {
         find = find->next->next;
      }
      else
      {
         break;
      }
   }
   printf("All posts have been displayed\n");
}

/*
   Fucntion that free all users from the database before quitting the application.
*/
void teardown(user_t *users)
{
   user_t *current = users;
   while (current != NULL)
   {
      user_t *del = current;
      current = current->next;

      friend_t *del_f = del->friends;
      while (del_f != NULL)
      {
         friend_t *old = del_f;
         del_f = del_f->next;
         free(old);
      }
      post_t *del_p = del->posts;
      while (del_p != NULL)
      {
         post_t *old = del_p;
         del_p = del_p->next;
         free(old);
      }
      free(del);
   }
}

/*
   Function that prints the main menu with a list of options for the user to choose from
*/
void print_menu()
{
   printf("************************************\n");
   printf("              MAIN MENU:            \n");
   printf("************************************\n");
   printf("1. Register a new User\n");
   printf("2. Login with existing user's information\n");
   printf("3. Exit\n");
   printf("\nEnter your choice: ");
}
void print_login(user_t *user)
{
   printf("************************************\n");
   printf("            Welcome %s:            \n",user->username);
   printf("************************************\n");
   printf("1. Manage a user's profile (change password)\n");
   printf("2. Manage a user's posts (display/add/remove)\n");
   printf("3. Manage a user's friends (display/add/remove)\n");
   printf("4. Display All Posts\n");
   printf("5. Exit\n");
   printf("\nEnter your choice: ");
}
void connect_friend(user_t *user, const char *friend){
   friend_t *node = user->friends;
   while ((node != NULL && strcmp(node->username, friend) != 0))
   {
      node = node->next;
   }
   if(node != NULL){
      node->posts = &(user->posts);
   }
   
}
/*
   ******** DONT MODIFY THIS FUNCTION ********
   Function that reads users from the text file.
   IMPORTANT: This function shouldn't be modified and used as is
   ******** DONT MODIFY THIS FUNCTION ********
*/
user_t *read_CSV_and_create_users(FILE *file, int num_users)
{
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
