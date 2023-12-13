/********* main.c ********
    Student Name 	=
    Student Number	=
*/

// Includes go here
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "a3_nodes.h"
#include "a3_functions.h"

int main()
{
    /******** DONT MODIFY THIS PART OF THE CODE ********/
    /* THIS CODE WILL LOAD THE DATABASE OF USERS FROM THE FILE
       AND GENERATE THE STARTING LINKED LIST.
    */
    FILE *csv_file = fopen("user_details.csv", "r");
    if (csv_file == NULL)
    {
        perror("Error opening the CSV file");
        return 1;
    }
    // Parse CSV data and create users
    user_t *users = read_CSV_and_create_users(csv_file, 50);
    fclose(csv_file);
    /******** DONT MODIFY THIS PART OF THE CODE ********/

    /* IMPORTANT: You must use the users linked list created in the code above.
                  Any new users should be added to that linked list.
    */

    // Your solution goes here
    printf("************************************\n");
    printf("   Welcome to Text-Based Facebook   \n");
    printf("************************************\n");
    int ans = 0;
    print_menu();
    scanf("%d", &ans);

    while (ans != 3)
    {
        if (ans < 1 || ans > 3)
        {
            printf("Invalid choice. Please try again.\n");
        }
        if (ans == 1)
        {
            char name[100];
            char password[20];
            printf("Enter a username: ");
            scanf("%s", name);
            user_t *find = find_user(users, name);
            if (find == NULL)
            {
                printf("Enter an upto 15 characters password: ");
                scanf("%s", password);
                add_user(users, name, password);
                printf("**** User Added! ****\n");
            }
            else
            {
                printf("ERROR. The user already exists!\n");
            }
        }
        if (ans == 2)
        {
            char name[100];
            char password[20];
            printf("Enter your username: ");
            scanf("%s", name);
            printf("Enter your password: ");
            scanf("%s", password);
            _Bool cont = compare(users, name, password);
            user_t *search = find_user(users, name);
            if (cont == false)
            {
                printf("ERROR. The username or password you entered is incorrect\n");
            }
            else
            {
                int c = 0;
                print_login(search);
                scanf("%d", &c);
                while (c != 5)
                {
                    if (c < 1 || c > 5)
                    {
                        printf("Invalid choice. Please try again.\n");
                    }
                    if (c == 1)
                    {
                        char password[20];
                        printf("Enter a new password that is upto 15 characters: ");
                        scanf("%s", password);
                        strcpy(search->password, password);
                        printf("**** Password changed! ****\n");
                    }
                    if (c == 2)
                    {
                        int chc = 0;
                        while (chc != 3)
                        {
                            display_user_posts(search);
                            printf("1. Add a new user post\n");
                            printf("2. Remove a users post\n");
                            printf("3. Return to main menu\n");
                            printf("Your choice: ");
                            scanf("%d", &chc);
                            if (chc == 1)
                            {
                                char post[260];
                                printf("Enter your post content: ");
                                scanf(" %[^\n]s", post);
                                add_post(search, post);
                                printf("Post added to your profile.\n");
                            }
                            if (chc == 2)
                            {
                                int del;
                                printf("which post you want to delete? ");
                                scanf("%d", &del);
                                _Bool ans = delete_post(search, del);
                                if (ans == true)
                                {
                                    printf("Post %d was deleted successfully!\n", del);
                                }
                                else
                                {
                                    printf("Invalid post's number\n");
                                    break;
                                }
                            }
                            if (chc == 3)
                            {
                                break;
                            }
                        }
                    }
                    if (c == 3)
                    {
                        int ans = 0;
                        while (ans != 5)
                        {
                            printf("------------------------------------\n");
                            printf("             %s's friends           \n", search->username);
                            printf("------------------------------------\n");
                            printf("1. Display all user's friends \n");
                            printf("2. Add a new friend \n");
                            printf("3. Delete a friend \n");
                            printf("4. Display a friend's posts \n");
                            printf("5. Return to main menu \n");
                            printf("\nYour choice: ");
                            scanf("%d", &ans);
                            if (ans == 1)
                            {
                                display_user_friends(search);
                            }
                            if (ans == 2)
                            {
                                char new_friend[100];
                                printf("Enter a new friends' name: ");
                                scanf("%s", new_friend);
                                user_t *check = find_user(users, new_friend);
                                if (check == NULL)
                                {
                                    printf("ERROR. The user does not exist!\n");
                                }
                                else
                                {
                                    add_friend(search, new_friend);
                                    printf("Friend added to the list.\n");
                                    connect_friend(search, new_friend);
                                    printf("Friend's posts are now connected\n");
                                }
                            }

                            if (ans == 3)
                            {
                                display_user_friends(search);
                                char del[100];
                                printf("Enter a friends' name to delete: ");
                                scanf("%s", del);
                                _Bool deleted = delete_friend(search, del);
                                if (deleted == true)
                                {
                                    display_user_friends(search);
                                }
                                else
                                {
                                    printf("Invalid friend's name\n");
                                }
                            }
                            if (ans == 4)
                            {
                                display_user_friends(search);
                                if (search->friends != NULL)
                                {
                                    char display[100];
                                    printf("Which friend's posts do you want to display? \n");
                                    scanf("%s", display);
                                    user_t *point = find_user(users, display);
                                    display_user_posts(point);
                                }
                            }
                            if (ans == 5)
                            {
                                break;
                            }
                        }
                    }
                    if (c == 4)
                    {
                        display_all_posts(users);
                    }
                    print_login(search);
                    scanf("%d", &c);
                }
            }
        }
        print_menu();
        scanf("%d", &ans);
    }

    printf("***************************************\n");
    printf("Thank you for using Text-Based Facebook\n");
    printf("              GoodBye!                 \n");
    printf("***************************************\n");
    teardown(users);
}