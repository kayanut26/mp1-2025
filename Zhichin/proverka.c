#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


//int main() {
//    int rows, cols;
//
//    printf("Enter rows: ");
//    scanf_s("%d", &rows);
//    printf("Enter cols: ");
//    scanf_s("%d", &cols);
//
//
//    int** matr = (int**)malloc(rows * sizeof(int*));
//    for (int i = 0; i < rows; i++) {
//        matr[i] = (int*)malloc(cols * sizeof(int));
//    }
//
// 
//    printf("\nEnter elements matrix (%d x %d):\n", rows, cols);
//    for (int i = 0; i < rows; i++) {
//        printf("Stroka %d: ", i + 1);
//        for (int j = 0; j < cols; j++) {
//            scanf_s("%d", &matr[i][j]);
//        }
//    }
//
//
//    printf("\nMatrix:\n");
//    for (int i = 0; i < rows; i++) {
//        for (int j = 0; j < cols; j++) {
//            printf("%d ", matr[i][j]);
//        }
//        printf("\n");
//    }
//
//    for (int i = 0; i < rows; i++) {
//        for (int j = 0; j < cols; j++) {
//            int val = matr[i][j];
//            int col_min = 1, col_max = 1, row_min = 1, row_max = 1;
//
//
//            for (int k = 0; k < cols; k++) {
//                if (matr[i][k] < val) row_min = 0;
//                if (matr[i][k] > val) row_max = 0;
//            }
//
//
//            for (int k = 0; k < rows; k++) {
//                if (matr[k][j] < val) col_min = 0;
//                if (matr[k][j] > val) col_max = 0;
//            }
//
//
//            if ((row_min && col_max) || (row_max && col_min)) {
//                printf("[%d,%d] = %d\n", i, j, val);
//
//            }
//        }
//    }
//    for (int i = 0; i < rows; i++) {
//        free(matr[i]);
//    }
//    free(matr);
//
//    return 0;
//}






///===================================



//void LowString(char* str) {
//    for (int i = 0; str[i] != '\0'; i++) {
//        str[i] = tolower(str[i]);
//    }
//}
//
//
//int SplitString(const char* s, const char* del, char words[][100]) {
//    const char* pst = s;
//    const char* pend = NULL;
//    int k = 0;
//
//    pend = strpbrk(pst, del);
//
//    while (pend != NULL) {
//        if (pend != pst) {
//            int len = pend - pst;
//            if (len < 100) {
//                strncpy(words[k], pst, len);
//                words[k][len] = '\0';
//                k++;
//            }
//        }
//        pst = pend + 1;
//        pend = strpbrk(pst, del);
//    }
//
//    if (!strchr(del, s[strlen(s) - 1])) {
//        strcpy(words[k], pst);
//        k++;
//    }
//
//    return k;
//}
//
//int main() {
//    char str[1000];
//    char words[100][100];
//    char unique_words[100][100];
//    int word_count[100] = { 0 };
//    int unique_count = 0;
//
//    const char* del = " .,:;!?-\n\t";
//
//    printf("Enter poem:\n");
//
//    while (1) {
//        fgets(str, sizeof(str), stdin);
//        str[strcspn(str, "\n")] = '\0';
//        if (strlen(str) == 0) break;
//        int k = SplitString(str, del, words);
//
//        for (int i = 0; i < k; i++) {
//            LowString(words[i]);
//            if (strlen(words[i]) <= 2) {
//                continue;
//            }
//            int found = -1;
//            for (int j = 0; j < unique_count; j++) {
//                if (strcmp(words[i], unique_words[j]) == 0) {
//                    found = j;
//                    break;
//                }
//            }
//            if (found == -1) {
//                strcpy(unique_words[unique_count], words[i]);
//                word_count[unique_count] = 1;
//                unique_count++;
//            }
//            else {
//                word_count[found]++;
//            }
//        }
//    }
//    printf("Unique words: %d\n\n", unique_count);
//
//    if (unique_count > 0) {
//        for (int i = 0; i < unique_count; i++) {
//            printf("%s: %d\n", unique_words[i], word_count[i]);
//        }
//    }
//    else {
//        printf("There are no words to count.\n");
//    }
//    return 0;
//}
//


//==========================================



//    int rows, cols;
//    printf("Enter rows: ");
//    scanf_s("%d", &rows);
//    printf("Enter cols: ");
//    scanf_s("%d", &cols);
//
//
//    int** matr = (int**)malloc(rows * sizeof(int*));
//
//    for (int i = 0; i < rows; i++) {
//        matr[i] = (int*)malloc(cols * sizeof(int));
//    }
//
//    printf("\nEnter elements matrix (%d x %d):\n", rows, cols);
//    for (int i = 0; i < rows; i++) {
//        printf("Stroka %d: ", i + 1);
//        for (int j = 0; j < cols; j++) {
//            scanf_s("%d", &matr[i][j]);
//        }
//    }
//    printf("\nMatrix:\n");
//    for (int i = 0; i < rows; i++) {
//        for (int j = 0; j < cols; j++) {
//            printf("%d ", matr[i][j]);
//        }
//        printf("\n\n");
//    }
//    int max_mest = 0, max_vagon = 0;
//    for (int i = 0; i < rows; i++) {
//        int max_mest_local = 0;
//        for (int k = 0; k < cols; k++) {
//            if (matr[i][k] == matr[i][k + 1])
//                if (matr[i][k] == 0)
//                    max_mest_local++;
//                else {
//                    if (max_mest_local > max_mest) {
//                        max_mest = max_mest_local;
//                        max_vagon = i + 1;
//                    }
//                    max_mest_local = 0;
//                }
//        }
//        if (max_mest_local > max_mest) {
//            max_mest = max_mest_local;
//            max_vagon = i + 1;
//        }
//
//
//    }
//    max_mest++;
//    printf("%d, %d\n", max_mest, max_vagon);
//    for (int i = 0; i < rows; i++) {
//        free(matr[i]);
//    }
//    free(matr);
//    return 0;
//}int main() {





































int factorial(int n) {
    int result = 1;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}

double ryad_maclorena_e(double x, int n) {
    double res = 0.0;

    for (int i = 0; i < n; i++) {
        double t = 1.0;
        double x_pow = 1.0;
        for (int j = 0; j < i; j++) {
            x_pow = x_pow * x;
        }
        t = x_pow / factorial(i);
        res += t;
    }
    return res;
}

// x_n
// x_n+1 = x_n * x / (n+1)

// x_n+1 = x_n * f(x, n)

//typedef double (f_t)(double, double);
//
//typedef double (ff_t)(double);
//
//double sum(f_t s, double x)
//{
//    x =f_t(x, x);
//}




int main() {
    int n = 33;
    double x = 2.3;
    printf("%lf\n", ryad_maclorena_e(x, n));
    return 0;
}

