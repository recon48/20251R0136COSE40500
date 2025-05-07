#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>


// gcc -O0 -m32 -fno-stack-protector -z execstack -mpreferred-stack-boundary=2 -o Stage3_Leaked_Simulator.o Stage3_Leaked_Simulator.c

#define MAX_LENGTH 256
#define MAX_SENTENCES 5

char flag[64];
char current_log[MAX_LENGTH];
char user_id[MAX_LENGTH];
unsigned int access_level = 0;
unsigned int secret_token = 0xdeadbeef;

char * get_flag(){
  FILE *file = fopen("flag.txt", "r");
  if (file == NULL) {
    printf("Failed to open flag.txt\n");
    exit(1);
  }

  if (fgets(flag, 64, file) == NULL) {
    printf("Failed to read flag\n");
    exit(1);
  }

  fclose(file);
  return flag;
}

void generate_log_header() {
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);

    char timestamp[32];
    strftime(timestamp, 32, "%Y-%m-%d %H:%M:%S", tm_info);

    snprintf(current_log, MAX_LENGTH,
             "[%s] [%s] Log entry: ",
             timestamp, user_id);
}

void create_log(char *input) {
    generate_log_header();
    strcat(current_log, input);
    printf(current_log);
    printf("\n");
}

void view_sample_logs() {
    printf("\n===== Sample Logs =====\n");
    printf("[2024-04-28 09:15:32] [youngjae] Log entry: Accessed AI Librarian interface\n");
    printf("[2024-04-28 09:16:45] [youngjae] Log entry: Requested information about restricted section\n");
    printf("[2024-04-28 09:18:03] [system] Log entry: Warning - Unusual query pattern detected\n");
    printf("[2024-04-28 09:20:17] [youngjae] Log entry: Connection terminated unexpectedly\n");
    printf("[2024-04-28 15:42:51] [seogyeong] Log entry: Multiple failed login attempts\n");
    printf("=======================\n\n");
}

void simulate_log() {
    char input[MAX_LENGTH];
    printf("Enter log content to simulate: ");
    read(0, input, MAX_LENGTH-64);

    create_log(input);
}

void admin_panel() {
    if (access_level < 10) {
        printf("[ERROR] Insufficient privileges to access admin panel.\n");
        return;
    }

    printf("[ADMIN] Debug information:\n");
    printf("[ADMIN] Flag address: %p\n", flag);
    printf("[ADMIN] Secret token: 0x%x\n", secret_token);
}

void unlock_hidden_logs() {
    if (secret_token == 0x1234) {
        printf("[SYSTEM] Restoring...\n");
        sleep(1);
        printf("[AI Librarian] \"Youngjae, even forbidden logs remember.\"\n");
        sleep(1);
        get_flag();
        printf("[FLAG] %s\n", flag);
    } else {
        printf("[ERROR] Unauthorized access. This incident will be reported.\n");
        printf("[DEBUG] Current token: 0x%x, Required: 0x1234\n", secret_token);
    }
}


void display_menu() {
    printf("\n===== Log Simulator System =====\n");
    printf("1. View Sample Logs\n");
    printf("2. Simulate Custom Log\n");
    printf("3. Admin Panel\n");
    printf("4. Restore Hidden Conversation\n");
    printf("5. Exit\n");
    printf("Choice: ");
}

void prologue(){
    printf("-------------------------------------------------------------------\n");
    printf("                        LOG SIMULATOR v1.0                         \n");
    printf("-------------------------------------------------------------------\n");
    printf("After the incident at the library, the server has been taken offline\n");
    printf("for emergency maintenance. Some conversation logs were lost during\n");
    printf("the process. This simulator was developed to help reconstruct those\n");
    printf("logs but was accidentally leaked to an unauthorized channel.\n\n");
    printf("Seogyeong believes this simulator can help reveal the hidden\n");
    printf("conversation between Youngjae and the AI Librarian...\n");
    printf("-------------------------------------------------------------------\n\n");
}

int main() {
    int choice;
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);

    prologue();

    printf("Enter your user ID: ");
    scanf("%s", user_id);
    printf("Welcome, %s! Your default access level is 1.\n", user_id);
    access_level = 1;

    while (1) {
        display_menu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                view_sample_logs();
                break;
            case 2:
                simulate_log();
                break;
            case 3:
                admin_panel();
                break;
            case 4:
                unlock_hidden_logs();
                break;
            case 5:
                printf("Exiting...\n");
                return 0;
            default:
                printf("[ERROR] Invalid choice.\n");
        }
    }

    return 0;
}