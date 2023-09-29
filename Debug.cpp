#include "Debug.h"

#include <stdio.h>

#include "ANSI_colors.h"

enum Errors {
    ERROR_NO =                          0,
    ERROR_STACK_EMPTY =                 1 << 0,
    ERROR_STACK_DATA_EMPTY =            1 << 1,
    ERROR_STACK_CAPACITY =              1 << 2,
    ERROR_STACK_SIZE =                  1 << 3,
    ERROR_STACK_CAPACITY_LESS_SIZE =    1 << 4,
    ERROR_LEFT_CANARY_STRUCT =          1 << 5,
    ERROR_RIGHT_CANARY_STRUCT =         1 << 6,
    ERROR_HASH =                        1 << 7,
    ERROR_LEFT_CANARY_DATA =            1 << 8,
    ERROR_RIGHT_CANARY_DATA =           1 << 9
};

struct ProcessErrors {
    int error;
    const char *description;
};

const ProcessErrors errors[] = {
    {ERROR_NO,                          "no errors"},
    {ERROR_STACK_EMPTY,                 "pointer stack is empty"},
    {ERROR_STACK_DATA_EMPTY,            "pointer stack->data is empty"},
    {ERROR_STACK_CAPACITY,              "stack->capacity < 0"},
    {ERROR_STACK_SIZE,                  "stack->size < 0"},
    {ERROR_STACK_CAPACITY_LESS_SIZE,    "stack->capacity < stack->size"},
    {ERROR_LEFT_CANARY_STRUCT,          "stack->left_canary_struct was changed"},
    {ERROR_RIGHT_CANARY_STRUCT,         "stack->right_canary_struct was changed"},
    {ERROR_HASH,                        "stack->hash was changed"},
    {ERROR_LEFT_CANARY_DATA,            "stack->left_canary_data was changed"},
    {ERROR_RIGHT_CANARY_DATA,           "stack->right_canary_data was changed"}
};
const int COUNT_ERRORS = sizeof(errors) / sizeof(ProcessErrors);

static int stack_check_error(Stack *stack);

static void print_error(int error, const char *s);

static int powf(int x, int st);

static int calculate_hash(void *data, int size);

int stack_dump_(Stack *stack, const char *file, const char *func, int line, const char *stk)
{
    int type_error = stack_check_error(stack);

    if (type_error == ERROR_NO)
        return ERROR_NO;

    fprintf(stderr, print_lred("ERROR: in stack[%p], called from FILE = %s, FUNCTION = %s, LINE = %d, with %s\n"), 
                               stack, file, func, line, stk);

    for (int i = 1; i < COUNT_ERRORS; i++) {
        if (type_error & powf(2, i - 1))
            print_error(type_error, errors[i].description);
    }
    return type_error;
}

int stack_check_error(Stack *stack)
{
    int error = ERROR_NO;
    if (!stack)                                                                return error |= ERROR_STACK_EMPTY;
    if (!stack->data)                                                          return error |= ERROR_STACK_DATA_EMPTY;
    if (stack->capacity < 0)                                                   return error |= ERROR_STACK_CAPACITY;
    if (stack->size < 0)                                                       return error |= ERROR_STACK_SIZE;
    if (stack->capacity < stack->size)                                         return error |= ERROR_STACK_CAPACITY_LESS_SIZE;
    if (stack->left_canary_struct != DEFAULT_CANARY)                           return error |= ERROR_LEFT_CANARY_STRUCT;
    if (stack->right_canary_struct != DEFAULT_CANARY)                          return error |= ERROR_RIGHT_CANARY_STRUCT;
    int hash = get_data_hash(stack);
    if (stack->hash != hash)                                                   return error |= ERROR_HASH;
    if (*((long long *)stack->data) != DEFAULT_CANARY)                          return error |= ERROR_LEFT_CANARY_DATA;
    if (*((long long *)stack->data + get_right_canary_ptr(stack)) != DEFAULT_CANARY)  return error |= ERROR_RIGHT_CANARY_DATA;
    return error; 
}

void print_error(int error, const char *s)
{
    fprintf(stderr, print_lred("ERROR: %d: %s\n"), error, s);
}

int check_alloc_(void *pointer, const char *file, const char *func, int line, const char *ptr)
{
    if (pointer) return 0;
    fprintf(stderr, print_lred("ERROR: in pointer = %p, called from FILE = %s, FUNCTION = %s, LINE = %d, with %s\n"), 
                               pointer, file, func, line, ptr);
    return 1;
}

void print_stack_pointers(const Stack *stack)
{
    printf("left_can =  %p\n",   &stack->left_canary_struct);
    printf("data =      %p\n",   &stack->data);
    printf("size =      %p\n",   &stack->size);
    printf("capacity =  %p\n",   &stack->capacity);
    printf("hash =      %p\n",   &stack->hash);
    printf("hash =      %p\n",   &stack->hash);
    printf("right_can = %p\n",   &stack->right_canary_struct);
}

int powf(int x, int st)
{
    if (st == 0) return 1;
    if (st % 2 == 1) return x * powf(x, st - 1);
    int z = powf(x, st / 2);
    return z * z;
}

int long long make_number_canary()
{
    srand((unsigned int)time(NULL));
    return (rand() % 555 + 35 + abs(atoi("CHE") % 37)) * (rand() % 1000 + 35 + abs(atoi("ABOBA") % 555)) * (rand() % 10000 + 7777) * (rand() % 909 + 35 + abs(atoi("777")));
}

int get_data_hash(Stack *stack)
{
    int size_struct = sizeof(long long) + sizeof(type_el *) + sizeof(int) * 2;
    return calculate_hash(stack, size_struct) + 
           calculate_hash(stack->data, sizeof(type_el) * stack->capacity);
}

int calculate_hash(void *data, int size)
{
    int hash = 777;
    const int base = 31;
    const int mod = 1e9 + 7;

    for (int i = 0; i < size; i++)
        hash = ((hash * base) % mod + (*((char *)data + i)) * base) % mod;

    return hash;
}

void write_hash(Stack *stack) 
{
    stack->hash = get_data_hash(stack);
}