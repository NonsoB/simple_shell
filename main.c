#include "main.h"

/**
 * main - This will; init data
 * @argc: inputs size of @argv
 * @argv: inputs array of command line arguments
 * Return: Always 0.
 */
int main(int argc, char **argv)
{
	data d;
	(void)argc;
	init_data(&d, argv[0]);
	_exec(&d);

	return (0);
}
