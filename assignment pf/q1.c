#include <stdio.h>

int main() {
    int rows, cols;
    
    printf("Enter number of rows: ");
    scanf("%d", &rows);
    printf("Enter number of seats per row: ");
    scanf("%d", &cols);
    
    int seats[50][50];
    
    printf("Enter the current seating status (0 for available, 1 for booked):\n");
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            scanf("%d", &seats[i][j]);
        }
    }
    
    printf("\n--- Current Seating Arrangement ---\n");
    printf("   ");
    for(int j = 0; j < cols; j++) {
        printf("%d ", j);
    }
    printf("\n");
    
    for(int i = 0; i < rows; i++) {
        printf("%d: ", i);
        for(int j = 0; j < cols; j++) {
            if(seats[i][j] == 0) {
                printf("_ ");
            } else {
                printf("X ");
            }
        }
        printf("\n");
    }
    
    int total_free = 0;
    printf("\n--- Seat Availability Report ---\n");
    for(int i = 0; i < rows; i++) {
        int row_free = 0;
        for(int j = 0; j < cols; j++) {
            if(seats[i][j] == 0) {
                row_free++;
            }
        }
        total_free += row_free;
        printf("Row %d: %d available seats\n", i, row_free);
    }
    printf("Total available seats in the hall: %d\n", total_free);
    
    int k;
    printf("\nEnter number of customers (k) who want to sit together: ");
    scanf("%d", &k);
    
    if(k <= 0 || k > cols) {
        printf("Invalid group size! Must be between 1 and %d.\n", cols);
        return 0;
    }
    
    int mid = rows / 2;
    int target_row = -1;
    int target_start_col = -1;
    
    int row_order[50];
    int count = 0;
    
    row_order[count++] = mid;
    
    for(int d = 1; d < rows; d++) {
        int up = mid - d;
        int down = mid + d;
        
        if(up >= 0) {
            row_order[count++] = up;
        }
        if(down < rows) {
            row_order[count++] = down;
        }
    }
    
    for(int idx = 0; idx < rows; idx++) {
        int r = row_order[idx];
        int consecutive_zeros = 0;
        int current_start = -1;
        
        for(int j = 0; j < cols; j++) {
            if(seats[r][j] == 0) {
                if(consecutive_zeros == 0) {
                    current_start = j;
                }
                consecutive_zeros++;
                
                if(consecutive_zeros == k) {
                    target_row = r;
                    target_start_col = current_start;
                    break;
                }
            } else {
                consecutive_zeros = 0;
            }
        }
        
        if(target_row != -1) {
            break;
        }
    }
    
    if(target_row != -1) {
        printf("\nBooking Successful!\n");
        printf("Group of %d seated in Row %d, Seats %d to %d\n", k, target_row, target_start_col, target_start_col + k - 1);
        
        for(int j = target_start_col; j < target_start_col + k; j++) {
            seats[target_row][j] = 1;
        }
        
        printf("\n--- Updated Seating Arrangement ---\n");
        printf("   ");
        for(int j = 0; j < cols; j++) {
            printf("%d ", j);
        }
        printf("\n");
        
        total_free = 0;
        for(int i = 0; i < rows; i++) {
            printf("%d: ", i);
            int row_free = 0;
            for(int j = 0; j < cols; j++) {
                if(seats[i][j] == 0) {
                    printf("_ ");
                    row_free++;
                } else {
                    printf("X ");
                }
            }
            total_free += row_free;
            printf("\n");
        }
        printf("\nRemaining available seats in the hall: %d\n", total_free);
        
    } else {
        printf("\nBooking Unsuccessful: No row contains %d consecutive available seats. Seating plan remains unchanged.\n", k);
    }
    
    return 0;
}