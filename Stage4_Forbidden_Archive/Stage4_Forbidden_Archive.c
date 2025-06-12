#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

// gcc -O0 -m32 -mpreferred-stack-boundary=2 -o Stage4_Forbidden_Archive.o Stage4_Forbidden_Archive.c -lpthread

#define MAX_QUEUE_SIZE 10
#define MAX_NAME_LEN 40
#define MAX_BOOK_LEN 40
#define MAX_MAJOR_LEN 40
#define MAX_THREADS 5

typedef struct
{
    int id;
    int is_waiting;
    char major[MAX_MAJOR_LEN];
    char name[MAX_NAME_LEN];
    char book[MAX_BOOK_LEN];
} User;

typedef struct
{
    User users[MAX_QUEUE_SIZE + 1];
    int size;
} Queue;

Queue waitingQueue;

void initQueue()
{
    memset(&waitingQueue, 0, sizeof(Queue));
    waitingQueue.size = 0;
}

void process()
{
    usleep(50000);
}

User registerUser()
{
    User newUser = {107, 0, "CS", "", ""};

    printf("\n\n===== Sign up =====\n");
    printf("User name: ");
    read(0, newUser.name, MAX_NAME_LEN);
    printf("Book title to borrow: ");
    read(0, newUser.book, MAX_BOOK_LEN);

    return newUser;
}

void *displayQueue()
{
    process();
    printf("\n\n===== Current Waiting Users =====\n");
    if (waitingQueue.size == 0)
    {
        printf("\n[!] No users currently waiting.\n\n");
    }
    else
    {
        printf("Waiting Users: [%d]\n", waitingQueue.size);
        for (int i = 0; i < waitingQueue.size; i++)
        {
            printf(" - ID: %d, Name: %s, Major: %s, Book: %s\n",
                   waitingQueue.users[i].id, waitingQueue.users[i].name,
                   waitingQueue.users[i].major, waitingQueue.users[i].book);
        }
    }
    printf("===================================\n");
}

void *enqueue(void *arg)
{
    User *user = (User *)arg;
    if (user->is_waiting == 1)
    {
        return NULL;
    }

    if (waitingQueue.size < MAX_QUEUE_SIZE)
    {
        process();
        strcpy(waitingQueue.users[waitingQueue.size].major, user->major);
        strcpy(waitingQueue.users[waitingQueue.size].name, user->name);
        strcpy(waitingQueue.users[waitingQueue.size].book, user->book);
        waitingQueue.users[waitingQueue.size].id = user->id;
        waitingQueue.size++;
    }
    user->is_waiting = 1;
    return NULL;
}

void *removeFromQueue(void *arg)
{
    User *user = (User *)arg;
    int found = -1;
    for (int i = 0; i < waitingQueue.size; i++)
    {
        if (waitingQueue.users[i].id == user->id)
        {
            found = i;
            break;
        }
    }

    if (found != -1 && user->is_waiting == 1)
    {
        process();
        user->is_waiting = 0;
        for (int i = found; i < waitingQueue.size - 1; i++)
        {
            strcpy(waitingQueue.users[i].major, waitingQueue.users[i + 1].major);
            strcpy(waitingQueue.users[i].name, waitingQueue.users[i + 1].name);
            strcpy(waitingQueue.users[i].book, waitingQueue.users[i + 1].book);
            waitingQueue.users[i].id = waitingQueue.users[i + 1].id;
        }

        waitingQueue.size--;
    }
    return NULL;
}

void *borrowBook(void *arg)
{
    User *user = (User *)arg;
    process();
    if (waitingQueue.users[0].id == user->id &&
        strcmp(waitingQueue.users[0].major, "Literature") == 0)
    {
        removeFromQueue(user);
        printf("%s borrowed '%s'.\n", user->name, user->book);
        system("/bin/cat flag.txt");
    }
    else
    {
        printf("\n[!] Cannot borrow.\n\n");
    }
    return NULL;
}

void display_menu()
{
    printf("\n\n===== Book Rental Program =====\n");
    printf("\nPlease select an operation:\n");
    printf("1. View waiting list\n");
    printf("2. Reserve a book\n");
    printf("3. Cancel reservation\n");
    printf("4. Borrow a book\n");
    printf("5. Exit\n");
    printf("Choice: ");
}

void prologue()
{
    printf("-------------------------------------------------------------------\n");
    printf("                    FORBIDDEN ARCHIVE ACCESS SYSTEM v2.0           \n");
    printf("-------------------------------------------------------------------\n");
    printf("After the incident at the library, the archive system was sealed.\n");
    printf("To evade detection, the AI Librarian deployed a fake book rental\n");
    printf("queue system. On the surface, it allows users to borrow books.\n\n");
    printf("But Seogyeong discovered that only Literature majors at the front\n");
    printf("of the waiting queue are granted access to forbidden knowledge.\n");
    printf("If you can reach the front of the line... the truth may be yours.\n");
    printf("-------------------------------------------------------------------\n\n");
}

int main()
{
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);

    prologue();

    initQueue();

    User user1 = {101, 0, "Literature", "Jururu", "Demian"};
    User user2 = {102, 0, "Literature", "Gosegu", "Ficciones"};
    User user3 = {103, 0, "Literature", "JingBurger", "The Unbearable Lightness of Being"};
    User user4 = {104, 0, "Literature", "Lilpa", "The Moon and Sixpence"};
    User user5 = {105, 0, "Literature", "Viichan", "Do Androids dream of electric sheep?"};
    User user6 = {106, 0, "Literature", "Ine", "Norwegian Wood"};

    enqueue(&user1);
    enqueue(&user2);
    enqueue(&user3);
    enqueue(&user4);
    enqueue(&user5);
    enqueue(&user6);

    printf("=== Welcome to the Book Rental Program! ===\n");

    displayQueue();

    User user7 = registerUser();

    int choice = 0;
    pthread_t threads[MAX_THREADS];
    int thread_count = 0;

    while (1)
    {
        if (thread_count >= MAX_THREADS)
        {
            printf("Too many operations! Please wait for some to complete.\n");
            for (int i = 0; i < thread_count; i++)
            {
                pthread_join(threads[i], NULL);
            }
            thread_count = 0;
        }
        display_menu();
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            pthread_create(&threads[thread_count++], NULL, &displayQueue, NULL);
            break;
        case 2:
            pthread_create(&threads[thread_count++], NULL, &enqueue, &user7);
            break;
        case 3:
            pthread_create(&threads[thread_count++], NULL, &removeFromQueue, &user7);
            break;
        case 4:
            pthread_create(&threads[thread_count++], NULL, &borrowBook, &user7);
            break;
        case 5:
            for (int i = 0; i < thread_count; i++)
            {
                pthread_join(threads[i], NULL);
            }
            printf("Goodbye!\n");
            return 0;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
