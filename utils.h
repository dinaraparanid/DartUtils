#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

bool arrow(const bool a, const bool b) {
    return !(a && !b);
}

typedef struct
{
    void* first;
    void* second;
} pair;

/**
 * Gets first param from pair
 * @param PAIR pair itself
 * @param FIELD field (first or second)
 * @param TYPE type of first
 * @return param of field
 */

#define GET_FROM_PAIR(PAIR, FIELD, TYPE) (*(TYPE*)(PAIR).FIELD)

 /**
  * Sets values to pair
  * @param PAIR pair itself
  * @param FIRST first value
  * @param SECOND second value
  * @param TYPE1 type of first
  * @param TYPE2 type of second
  */

#define SET_TO_PAIR(PAIR, FIRST, SECOND, TYPE1, TYPE2) \
    (PAIR).first = malloc(sizeof(TYPE1)); \
    (PAIR).second = malloc(sizeof(TYPE2)); \
	*(TYPE1*)(PAIR).first = (FIRST); \
	*(TYPE2*)(PAIR).second = (SECOND);

void reverse(void* arr, const size_t arr_size, const size_t size_of_elem) {
    const size_t size_in_bytes = arr_size * size_of_elem;
    const size_t border = arr_size / 2;
    const size_t border_in_bytes = size_in_bytes / 2;
    char* p = arr;

    for (size_t i = 0; i < border; i++) {
        void* t = malloc(size_of_elem);
        memmove(t, p + i * size_of_elem, size_of_elem);

        char* first = p + i * size_of_elem;
        char* second = p + (arr_size - i - 1) * size_of_elem;
        memmove(first, second, size_of_elem);
        memmove(second, t, size_of_elem);
    }
}

#define TO_REDIX(N, TYPE, REDIX, SET_VARIABLE_NAME) \
    TYPE __TO_REDIX_N = N; \
    char* __TO_REDIX_S = malloc(sizeof(char)); \
    size_t __TO_REDIX_SIZE = 0; \
    do { \
        __TO_REDIX_S = realloc(__TO_REDIX_S, ++__TO_REDIX_SIZE * sizeof(char)); \
        __TO_REDIX_S[__TO_REDIX_SIZE - 1] = '0' + __TO_REDIX_N % REDIX; \
        __TO_REDIX_N /= REDIX; \
    } while (__TO_REDIX_N != 0); \
    REVERSE(__TO_REDIX_S, __TO_REDIX_SIZE, char); \
    __TO_REDIX_S = realloc(__TO_REDIX_S, (__TO_REDIX_SIZE + 1) * sizeof(char)); \
    __TO_REDIX_S[__TO_REDIX_SIZE] = '\0'; \
    char* SET_VARIABLE_NAME = __TO_REDIX_S;

char* repeat_str(const char* str, const int n) {
    const size_t str_size = strlen(str);
    const size_t final_size = n * str_size;
    char* ans = malloc((final_size + 1) * sizeof(char));

    for (size_t i = 0; i < final_size; i += str_size)
        strcpy(ans + i, str);

    ans[final_size] = '\0';
    return ans;
}

char* replace_first_str(char* s, char* replacable, char* pattern) {
    char* substr = strstr(s, replacable);

    if (!substr)
        return NULL;

    const size_t size_of_replacable = strlen(replacable);
    const size_t size_of_start = substr - s;
    const size_t size_of_pattern = strlen(pattern);
    const size_t size_of_original = strlen(s);
    const size_t size_of_finish = size_of_original - size_of_start - size_of_replacable;
    const size_t final_size = size_of_start + size_of_pattern + size_of_finish;
    char* new_s = malloc((final_size + 1) * sizeof(char));

    memmove(new_s, s, size_of_start);
    strcpy(new_s + size_of_start, pattern);
    memmove(new_s + size_of_start + size_of_pattern, s + size_of_start + size_of_replacable, size_of_finish);

    new_s[final_size] = '\0';
    return new_s;
}

size_t count_arr(void* arr, const size_t arr_size, const void* pattern, const size_t elem_size) {
    const size_t size_in_bytes = arr_size * elem_size;
    size_t ans = 0;

    for (char* p = arr; p != arr + size_in_bytes; p += elem_size)
        if (memcmp(p, pattern, elem_size) == 0)
            ans++;

    return ans;
}
