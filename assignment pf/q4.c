#include <stdio.h>

int getValidDays() {
    int d;
    while(1) {
        printf("Number of days: ");
        scanf("%d", &d);
        if(d >= 1 && d <= 7) {
            return d;
        }
        printf("Invalid duration! Please enter a value between 1 and 7.\n");
    }
}

float calculateDailySales(int dayNumber) {
    int n;
    printf("\nDay %d - Number of orders: ", dayNumber);
    scanf("%d", &n);
    
    float total = 0;
    float max = -1;
    
    printf("Order amounts: ");
    for(int i = 0; i < n; i++) {
        float amt;
        scanf("%f", &amt);
        while(amt <= 0) {
            printf("Invalid amount! Amount must be greater than zero. Re-enter: ");
            scanf("%f", &amt);
        }
        total += amt;
        if(amt > max) {
            max = amt;
        }
    }
    
    float avg = total / n;
    
    printf("Total sales: Rs. %.2f\n", total);
    printf("Average order: Rs. %.2f\n", avg);
    printf("Highest order: Rs. %.2f\n", max);
    
    return total;
}

int findHighestSalesDay(float dailySales[], int numberOfDays) {
    int best = 0;
    float peak = dailySales[0];
    
    for(int i = 1; i < numberOfDays; i++) {
        if(dailySales[i] > peak) {
            peak = dailySales[i];
            best = i;
        }
    }
    return best + 1;
}

void displayBarChart(float dailySales[], int numberOfDays) {
    printf("\n===== DAILY SALES BAR CHART =====\n");
    for(int i = 0; i < numberOfDays; i++) {
        printf("Day %d: ", i + 1);
        int stars = (int)(dailySales[i] / 100);
        for(int s = 0; s < stars; s++) {
            printf("*");
        }
        printf(" (Rs. %.2f)\n", dailySales[i]);
    }
}

int main() {
    int days = getValidDays();
    float dailySales[7];
    float totalSales = 0;
    
    for(int i = 0; i < days; i++) {
        dailySales[i] = calculateDailySales(i + 1);
        totalSales += dailySales[i];
    }
    
    int bestDay = findHighestSalesDay(dailySales, days);
    float highestSales = dailySales[bestDay - 1];
    
    printf("\n=\tFESTIVAL SUMMARY\t\n");
    printf("Total festival sales: Rs. %.2f\n", totalSales);
    printf("Day with highest sales: Day %d\n", bestDay);
    printf("Highest daily sales: Rs. %.2f\n", highestSales);
    
    displayBarChart(dailySales, days);
    
    return 0;
}
