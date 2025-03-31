#include <limits.h>
#include <stdlib.h>
#include <stdio.h>

int main() {
    long long int N, l_of_arr, sum=0;

    if ((scanf("%lld", &N)!=1) || (N < 1 || N > 10)){
        printf("bad input");
        return 0;
    }

    long long int arr[N];
    l_of_arr = sizeof(arr)/sizeof(N);

    for(int i=0;i<N;i++){
        if (scanf("%lld", &arr[i])!=1 || (INT_MAX<arr[i] || INT_MIN>arr[i])){
            printf("bad input");
            return 0;
        }

    }

    if (l_of_arr!=N){
        printf("bad input");
        return 0;
    }

    for (int i=0;i<N;i++){
        sum+=arr[i];
    }

    if (INT_MAX<sum || INT_MIN>sum){
        printf("overflow");
        return 0;

    }
    else{
        printf("%lld", sum);
        return 0;
    }

}

