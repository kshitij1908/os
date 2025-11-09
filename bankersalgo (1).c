#include <stdio.h>
#define MAX_ROWS 10
#define MAX_COLS 10

void input2DArray(int arr[MAX_ROWS][MAX_COLS], int *rows, int *cols) {
    printf("Enter the number of rows (max %d): ", MAX_ROWS);
    scanf("%d", rows);
    printf("Enter the number of columns (max %d): ", MAX_COLS);
    scanf("%d", cols);

    if (*rows > MAX_ROWS || *cols > MAX_COLS) {
        printf("Rows or columns exceed maximum limits!\n");
        return;
    }

    printf("Enter the elements of the array:\n");
    for (int i = 0; i < *rows; i++) {
        for (int j = 0; j < *cols; j++) {
            printf("Element [%d][%d]: ", i, j);
            scanf("%d", &arr[i][j]);
        }
    }
}

int main() {
    int numProcesses, numResources;

    int allocationMatrix[MAX_ROWS][MAX_COLS];
    int maxMatrix[MAX_ROWS][MAX_COLS];

    int rows, cols;

    // Input Allocation and Max matrices
    printf("Allocation Matrix:\n");
    input2DArray(allocationMatrix, &rows, &cols);
    numProcesses = rows;
    numResources = cols;

    printf("Max Matrix:\n");
    input2DArray(maxMatrix, &rows, &cols);
    
    // Ensure that the number of resources matches
    if (numResources != cols) {
        printf("Number of resources must match for Allocation and Max matrices.\n");
        return 1;
    }

    int availableResources[MAX_COLS] = {3, 3, 2}; // Change this to your actual available resources

    int isFinished[MAX_ROWS] = {0};
    int safeSequence[MAX_ROWS];
    int index = 0;

    // Compute Need matrix
    int needMatrix[MAX_ROWS][MAX_COLS];
    for (int i = 0; i < numProcesses; i++) {
        for (int j = 0; j < numResources; j++)
            needMatrix[i][j] = maxMatrix[i][j] - allocationMatrix[i][j];
    }

    // Banker's algorithm to find safe sequence
    for (int k = 0; k < numProcesses; k++) {
        for (int i = 0; i < numProcesses; i++) {
            if (!isFinished[i]) {
                int canFinish = 1; // Assume it can finish
                for (int j = 0; j < numResources; j++) {
                    if (needMatrix[i][j] > availableResources[j]) {
                        canFinish = 0; // Cannot finish
                        break;
                    }
                }
                if (canFinish) {
                    safeSequence[index++] = i;
                    isFinished[i] = 1; // Mark as finished
                    for (int y = 0; y < numResources; y++) {
                        availableResources[y] += allocationMatrix[i][y]; // Release resources
                    }
                }
            }
        }
    }

    // Print Need Matrix
    printf("The Need matrix is:\n");
    for (int i = 0; i < numProcesses; i++) {
        for (int j = 0; j < numResources; j++) {
            printf("%d ", needMatrix[i][j]);
        }
        printf("\n");
    }

    // Check if the system is in a safe state
    int systemIsSafe = 1;
    for (int i = 0; i < numProcesses; i++) {
        if (!isFinished[i]) {
            systemIsSafe = 0;
            printf("The system is not safe.\n");
            break;
        }
    }

    if (systemIsSafe) {
        printf("SAFE Sequence: ");
        for (int i = 0; i < numProcesses; i++) {
            printf("P%d", safeSequence[i]);
            if (i < numProcesses - 1) {
                printf(" -> ");
            }
        }
        printf("\n");
    }

    return 0;
}



