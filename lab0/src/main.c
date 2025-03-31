#include <stdlib.h>
#include <stdio.h>
#include <string.h>


void char_check(char k, int *digit, int b1, int *flag) { // функция преобразования число-символ

    if (k=='.') {
        *flag = 1;
        return;
    }
    if (k>='0' && k<='9') {
        *digit = k-'0';
    }
    else if (k>='A' && k<='F') {
        *digit = k-'A'+10;
    }
    else if (k>='a' && k<='f') {
        *digit = k-'a'+10;
    }
    else {
        *flag=0;
        return;
    }
    if (*digit >= b1) {
        *flag=0;
        return;
    }
}


int num_is_valid(char *num, int b1) {
    int flag = 2;
    for (int i=0; num[i]!='\0'; i++) {
        if ((num[0]=='.') || (num[i]=='.' && num[i+1]=='\0') || (num[i]=='.' && (num[i+1]=='.' || num[i+1]=='('))) { // проверяем валидность числа т.е. место точки и открывающую скобку
            return 0;
        }
        int digit=0;

        char k = num[i];

        char_check(k, &digit, b1, &flag);

        if (flag!=2) {
            return flag;
        }
    }
    return 1;
}

void split_with_point(char *num, int size, char *before_point, char *after_point) { // функция на разделение на целую и дробную часть
    int i=0;
    while (i < size && num[i]!='.' && num[i]!='\0') { //  копируем символы до точки
        before_point[i] = num[i];
        i++;
    }
    before_point[i] = '\0';
    if (num[i]=='.') {
        i++;
        int k=0;
        while (i < size && num[i]!='\0') { // копируем после точки
            after_point[k++] = num[i++];
        }
        after_point[k]='\0';
    } else {
        after_point[0] = '\0';
    }
}

void make_num_to_ten(long long *int_before, long double *double_after, char *before_point, char *after_point, int b1, int size) {// функция перевод числа до точки в десятичное
    long long result1 = 0;
    long double result2 = 0.0;
    long double dot_shift = 1.0/b1;
    int flag=2;

    for (int i=0; i < size && before_point[i]!='\0'; i++) { // идем по цифрам пока не кончится список до точки
        char current_dig = before_point[i];
        int digit = 0;
        char_check(current_dig, &digit, b1, &flag);
        result1 = result1 * b1 + digit; // перевод в 10сс
    }

    for (int i=0; i < size && after_point[i]!='\0'; i++) {
        int digit = 0;
        char current_dig = after_point[i];
        char_check(current_dig, &digit, b1, &flag);
        result2 = result2 + dot_shift * digit;
        dot_shift/=b1;
    }
    *int_before = result1;
    *double_after = result2;
}


void make_num_before_to_b2(long long int_before, int b2, char *before_point, int size) { // переводим целую часть из 10сс в b2сс
    int i=0;
    while(int_before>0 && i<size) {
        int digit = int_before % b2;
        if (digit<10) {
            before_point[i++] = digit+'0';
        } else {
            before_point[i++] = digit-10+'A';
        }
        int_before/=b2;
    } // стандартная функция перевода в b2сс из 10сс
    before_point[i] = '\0';
    int len=strlen(before_point);
    for (int k=0; k<len/2; k++) {
        char t = before_point[k];
        before_point[k] = before_point[len-k-1];
        before_point[len-k-1] = t;
    }// ^ переворачиваем полученное число
}


void make_num_after_to_b2(long double double_after, int b2, char *after_point, int size) {
    int i=0;
    int maximum = 13; // ограничение по дробной части
    while (double_after>0 && i<size-1 && i<maximum) {
        double_after = double_after * b2;
        int digit = (int)double_after;
        if (digit<10) {
            after_point[i++] = digit+'0';
        } else {
            after_point[i++] = digit-10+'A';
        }
        double_after -= digit;
    }
    after_point[i] = '\0';
}



int main() {
    long long int_before;
    long double double_after;
    int b1, b2;
    char num[100];
    if (scanf("%d %d %99s",  &b1, &b2, &num[0])!=3 || b1<2 || b1> 16 || b2<2 || b2> 16) { // проверяем введенные значения по условиям
        printf("bad input");
        return 0;
    }

    if (!num_is_valid(num, b1)) { // валидируем b1 при помощи функции
        printf("bad input");
        return 0;
    }
    char before_point_b1[100];
    char after_point_b1[100];

    split_with_point(num, 100, before_point_b1, after_point_b1);

    make_num_to_ten(&int_before, &double_after, before_point_b1, after_point_b1, b1, 100);


    char before_point_b2[100];
    char after_point_b2[100];


    make_num_before_to_b2(int_before, b2, before_point_b2, 100);
    make_num_after_to_b2(double_after, b2, after_point_b2, 100);


    if (strlen(before_point_b2)==0) {
        printf("0");
    } else {
        printf("%s", before_point_b2);
    }

    if (strlen(after_point_b2) > 0) {
        printf(".%s", after_point_b2);
    }
    return 0;
}


