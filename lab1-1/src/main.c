#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define PATTERN_SIZE 18
#define MAIN_SIZE 1000


long long int make_hash(char const *str, unsigned long long int i_s, unsigned long long int i_end) { // считаем хэш
    long long int count_hash=0, degree = 1;
    for (unsigned long long int k=i_s; k < i_end; k++) {
        count_hash += (unsigned int)(str[k])%3*degree; // считаем сумму хэша
        degree*=3;
    }
    return count_hash;
}


unsigned long long int global_index=0;

void Rabin_Carp(char const *sub_str, char const * str, unsigned long long int sub_str_hash, unsigned long long int sub_len, unsigned long long int str_len) { // функция рабин карп
    for (unsigned long long int i=0; i<=str_len-sub_len+1; i++) { // идем по циклу пока не закончится основная строка
        unsigned long long int hash_count=make_hash(str, i, sub_len+i);
        if (hash_count == sub_str_hash) { // проверяем равенство хэшей текущей подстроки и паттерна
            for (unsigned long long int j=0+i; j<sub_len+i; j++) {
                    printf("%llu ", j+1+global_index); // выводим символы с которыми сравниваем
                    if (sub_str[j-i]!=str[j]) {
                        break;
                    }
                }
            }
        }
    global_index+=sub_len;
}


int main() {
    char sub_str[PATTERN_SIZE]; // инициализируем буфер для шаблона
    char main_str[MAIN_SIZE]; // инициализируем буфер для строки

    if (fgets(sub_str, sizeof(sub_str), stdin) == NULL) {
        printf("%d", 0);
        return 0;
    }; // записываем в строку для шаблона

    unsigned long long int sub_len = strlen(sub_str)-1;
    long long int sub_hash = make_hash(sub_str, 0, sub_len);

    printf("%lld ", sub_hash);

    while (1) {// ввод основной строки
        if (fgets(main_str, sizeof(main_str), stdin) == NULL) {
            return 0;
        }
        unsigned long long int main_len = strlen(main_str)-1;
        Rabin_Carp(sub_str,main_str, sub_hash, sub_len, main_len);
    };
    return 0;
}
