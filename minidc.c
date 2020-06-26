#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define STACK_CAP 100

int stack[STACK_CAP];
int stack_size = 0;

void stack_push(int val)
{
	if (stack_size == STACK_CAP) 
		printf("error: stack full\n");
	else
		stack[stack_size++] = val;
}

void stack_add(void)
{
	stack[stack_size - 2] += stack[stack_size - 1];
	stack_size--;
}

void stack_sub(void)
{
	stack[stack_size - 2] -= stack[stack_size - 1];
	stack_size--;
}

void stack_mul(void)
{
	stack[stack_size - 2] *= stack[stack_size - 1];
	stack_size--;
}

void stack_div(void)
{
	if (stack[stack_size - 1] == 0) {
		printf("error: divide by zero\n");
	} else {
		stack[stack_size - 2] /= stack[stack_size - 1];
		stack_size--;
	}
}

void stack_mod(void)
{
	if (stack[stack_size - 1] == 0) {
		printf("error: divide by zero\n");
	} else {
		stack[stack_size - 2] %= stack[stack_size - 1];
		stack_size--;
	}
}

void stack_pop(void)
{
	if (stack_size)
		printf("%d\n", stack[--stack_size ]);
	else
		printf("error: stack empty\n");
}

void stack_print(void)
{
	if (stack_size)
		printf("%d\n", stack[stack_size - 1]);
	else
		printf("error: stack empty\n");
}

void stack_full_print(void)
{
	int i;
	for (i = stack_size - 1; i >= 0; i--)
		printf("%d\n", stack[i]);
}

void stack_clear(void)
{
	stack_size = 0;
}

void stack_dup(void)
{
	if (stack_size < 1) {
		printf("error: stack empty\n");
	} else if (stack_size == STACK_CAP) {
		printf("error: stack full\n");
	} else {
		printf("%d\n", stack[stack_size] = stack[stack_size - 1]);
		stack_size++;
	}
}

void stack_swap(void)
{
		int val = stack[stack_size - 1];
		stack[stack_size - 1] = stack[stack_size - 2];
		stack[stack_size - 2] = val;
}

void exec_line(char * lineptr)
{
	while (*lineptr && *lineptr != '\n') {
		if (isspace(*lineptr)) {
			lineptr++;
			continue;
		} else if (isdigit(*lineptr) || *lineptr == '_') {
			if (*lineptr == '_')
				*lineptr = '-';
			stack_push(strtol(lineptr, &lineptr, 10));
			continue;

		} else if ((*lineptr == '+' || *lineptr == '-' || *lineptr == '*' 
				|| *lineptr == '/' || *lineptr == '%' 
				|| *lineptr == 'r') && stack_size < 2) {
			printf("error: at least 2 values needed in stack\n");
			lineptr++;
			continue;
		}
		switch(*lineptr) {
		case '+':
			stack_add();
			break;
		case '-':
			stack_sub();
			break;
		case '*':
			stack_mul();
			break;
		case '/':
			stack_div();
			break;
		case '%':
			stack_mod();
			break;
		case 'p':
			stack_print();
			break;
		case 'n':
			stack_pop();
			break;
		case 'c':
			stack_clear();
			break;
		case 'd':
			stack_dup();
			break;
		case 'r':
			stack_swap();
			break;
		case 'f':
			stack_full_print();
			break;
		default:
			printf("error: invalid character %c\n", *lineptr); 
		}
		lineptr++;
	}
}

int main(void)
{
	char * lineptr = NULL;
	size_t n = 0;
	ssize_t len;

	while ((len = getline(&lineptr, &n, stdin)) >= 0) {
		exec_line(lineptr);
	}
	free(lineptr);
	return 0;
}
