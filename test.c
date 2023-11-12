#include <stdio.h>
#include <string.h>
#include <stdlib.h>


union Flag {
    int value;
};


struct User {
    char* username;
    union Flag accessFlag;
};

int main(void) {
    struct User* users = NULL;
    int userCount = 0;

    while (1) {
        printf("Enter 'register' to add a new user or 'login' to log in: ");
        char choice[10];
        scanf("%s", choice);

        if (strcmp(choice, "register") == 0) {
            char newUser[10];
            printf("Enter a new username: ");
            scanf("%s", newUser);

            int usernameExists = 0;
            for (int i = 0; i < userCount; i++) {
                if (strcmp(newUser, users[i].username) == 0) {
                    printf("Username already exists. Registration failed.\n");
                    usernameExists = 1;
                    break;
                }
            }

            if (!usernameExists) {
                users = (struct User*)realloc(users, (userCount + 1) * sizeof(struct User));
                users[userCount].username = (char*)malloc(10 * sizeof(char));
                strcpy(users[userCount].username, newUser);

                int flagValue;
                printf("Enter the access flag value (1 for true, 0 for false): ");
                scanf("%d", &flagValue);


                users[userCount].accessFlag.value = flagValue;
                userCount++;
                printf("User registered successfully.\n");
            }
        } else if (strcmp(choice, "login") == 0) {
            char user[10];
            printf("Enter your username: ");
            scanf("%s", user);

            int found = 0;
            for (int i = 0; i < userCount; i++) {
                if (strcmp(user, users[i].username) == 0) {
                    found = 1;
                    if (users[i].accessFlag.value == 1) {
                        printf("Login successful. Welcome, %s!\n", user);
                    } else {
                        printf("Login failed. User not allowed.\n");
                    }
                    break;
                }
            }

            if (!found) {
                printf("Login failed. User not found.\n");
            }
        } else {
            printf("Invalid choice. Please enter 'register' or 'login'.\n");
        }
    }
    for (int i = 0; i < userCount; i++) {
        free(users[i].username);
    }
    free(users);

    return 0;
}
