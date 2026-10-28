#include <stdio.h>

int main() {
    int r, c;
    
    printf("Enter number of sensors: ");
    scanf("%d", &r);
    printf("Enter number of hourly readings: ");
    scanf("%d", &c);
    
    int a[100][100];
    
    printf("Enter the temperature readings:\n");
    for(int i = 0; i < r; i++) {
        for(int j = 0; j < c; j++) {
            scanf("%d", &a[i][j]);
        }
    }
    
    printf("\n--- Individual Sensor Reports ---\n");
    
    int bestSensor = 0;
    float maxAvg = -1;
    
    for(int i = 0; i < r; i++) {
        int sum = 0;
        int max = a[i][0];
        int min = a[i][0];
        int critical = 0;
        int warning = 0;
        int streak = 0;
        int maxStreak = 0;
        
        for(int j = 0; j < c; j++) {
            int val = a[i][j];
            sum += val;
            
            if(val > max) {
                max = val;
            }
            if(val < min) {
                min = val;
            }
            
            if(val >= 40) {
                critical++;
            }
            if(val >= 35 && val <= 39) {
                warning++;
            }
            
            if(val >= 35) {
                streak++;
                if(streak > maxStreak) {
                    maxStreak = streak;
                }
            } else {
                streak = 0;
            }
        }
        
        float avg = (float)sum / c;
        
        if(avg > maxAvg) {
            maxAvg = avg;
            bestSensor = i;
        }
        
        printf("Sensor %d: Total=%d Avg=%.2f Max=%d Min=%d\n", i + 1, sum, avg, max, min);
        printf("          Critical=%d Warning=%d Longest hot streak=%d\n", critical, warning, maxStreak);
    }
    
    printf("\nHighest average: Sensor %d (%.2f)\n", bestSensor + 1, maxAvg);
    
    return 0;
}