#include <stdio.h>

int sum_of_divisors(int num) {
    int sum = 0;
    for (int i = 1; i <= num / 2; i++) {
        if (num % i == 0) {
            sum += i;
        }
    }
    return sum;
}

int main() {
    int n;
    
    printf("Enter a number n: ");
    scanf("%d", &n);
    
    printf("\tAmicable pairs less than or equal to %d:\n", n);
    
    for (int i = 1; i <= n; i++) {
        int sum1 = sum_of_divisors(i);
        
        if (sum1 > i && sum1 <= n) {
            int sum2 = sum_of_divisors(sum1);
            if (sum2 == i) {
                printf("(%d, %d)\n",i,sum1);
            }}
    }
    
    return 0;
}65445