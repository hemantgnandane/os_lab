#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 5
#define MAX_RESOURCES 3

int available[MAX_RESOURCES];
int maximum[MAX_PROCESSES][MAX_RESOURCES];
int allocation[MAX_PROCESSES][MAX_RESOURCES];
int need[MAX_PROCESSES][MAX_RESOURCES];

void initialize_data();
void display_state();
bool request_resources(int process_id, int request[]);
void release_resources(int process_id, int release[]);

int main() {
    initialize_data();

    while (true) {
        display_state();

        int choice;
        printf("\nEnter 1 to request resources, 2 to release resources, or any other number to exit: ");
        scanf("%d", &choice);

        if (choice == 1) {
            int process_id;
            printf("Enter process ID (0 to %d): ", MAX_PROCESSES - 1);
            scanf("%d", &process_id);

            int request[MAX_RESOURCES];
            printf("Enter the requested resources:\n");
            for (int i = 0; i < MAX_RESOURCES; i++) {
                scanf("%d", &request[i]);
            }

            if (request_resources(process_id, request)) {
                printf("Resources allocated.\n");
            } else {
                printf("Request denied. Process must wait to avoid deadlock.\n");
            }
        } else if (choice == 2) {
            int process_id;
            printf("Enter process ID (0 to %d): ", MAX_PROCESSES - 1);
            scanf("%d", &process_id);

            int release[MAX_RESOURCES];
            printf("Enter the resources to release:\n");
            for (int i = 0; i < MAX_RESOURCES; i++) {
                scanf("%d", &release[i]);
            }

            release_resources(process_id, release);
            printf("Resources released.\n");
        } else {
            break;
        }
    }

    return 0;
}

void initialize_data() {
    // Initialize available resources
    printf("Enter the number of available instances for each resource:\n");
    for (int i = 0; i < MAX_RESOURCES; i++) {
        scanf("%d", &available[i]);
    }

    // Initialize maximum resources for each process
    printf("Enter the maximum resources needed for each process:\n");
    for (int i = 0; i < MAX_PROCESSES; i++) {
        for (int j = 0; j < MAX_RESOURCES; j++) {
            scanf("%d", &maximum[i][j]);
            need[i][j] = maximum[i][j];
        }
    }
}

void display_state() {
    printf("\nCurrent State:\n");

    // Display available resources
    printf("Available resources: ");
    for (int i = 0; i < MAX_RESOURCES; i++) {
        printf("%d ", available[i]);
    }
    printf("\n");

    // Display maximum resources for each process
    printf("Maximum resources:\n");
    for (int i = 0; i < MAX_PROCESSES; i++) {
        for (int j = 0; j < MAX_RESOURCES; j++) {
            printf("%d ", maximum[i][j]);
        }
        printf("\n");
    }

    // Display allocated resources for each process
    printf("Allocated resources:\n");
    for (int i = 0; i < MAX_PROCESSES; i++) {
        for (int j = 0; j < MAX_RESOURCES; j++) {
            printf("%d ", allocation[i][j]);
        }
        printf("\n");
    }

    // Display needed resources for each process
    printf("Needed resources:\n");
    for (int i = 0; i < MAX_PROCESSES; i++) {
        for (int j = 0; j < MAX_RESOURCES; j++) {
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }
}

bool request_resources(int process_id, int request[]) {
    // Check if the request is within the need and available limits
    for (int i = 0; i < MAX_RESOURCES; i++) {
        if (request[i] > need[process_id][i] || request[i] > available[i]) {
            return false;
        }
    }

    // Pretend to allocate resources and check if it results in a safe state
    for (int i = 0; i < MAX_RESOURCES; i++) {
        available[i] -= request[i];
        allocation[process_id][i] += request[i];
        need[process_id][i] -= request[i];
    }

    // Check if the state is safe
    bool safe = false;
    bool finish[MAX_PROCESSES] = {false};

    for (int i = 0; i < MAX_PROCESSES; i++) {
        if (!finish[i]) {
            bool possible = true;
            for (int j = 0; j < MAX_RESOURCES; j++) {
                if (need[i][j] > available[j]) {
                    possible = false;
                    break;
                }
            }

            if (possible) {
                finish[i] = true;
                for (int j = 0; j < MAX_RESOURCES; j++) {
                    available[j] += allocation[i][j];
                }
                safe = true;
                break;
            }
        }
    }

    // If not safe, roll back changes
    if (!safe) {
        for (int i = 0; i < MAX_RESOURCES; i++) {
            available[i] += request[i];
            allocation[process_id][i] -= request[i];
            need[process_id][i] += request[i];
        }
    }

    return safe;
}

void release_resources(int process_id, int release[]) {
    for (int i = 0; i < MAX_RESOURCES; i++) {
        available[i] += release[i];
        allocation[process_id][i] -= release[i];
        need[process_id][i] += release[i];
    }
}
