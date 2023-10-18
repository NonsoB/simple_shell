#include "shell.h"

/**
 * _shell_input_buff - chain command buffer
 * @inf: struct of parameter
 * @buffe: address of buffer
 * @ln: address of len var
 *
 * Return: bytes read
 */
ssize_t _shell_input_buff(info_t *inf, char **buffe, size_t *ln)
{
	ssize_t a = 0;
	size_t ln_pt = 0;

	if (!*ln) /* if nothing left in the buffer, fill it */
	{
		/*bfree_ptr((void **)info->cmd_buf);*/
		free(*buffe);
		*buffe = NULL;
		signal(SIGINT, shell_sigHandler);
#if USE_GETLINE
		r = getline(buf, &len_p, stdin);
#else
		a = shell_getline(inf, buffe, &ln_pt);
#endif
		if (a > 0)
		{
			if ((*buffe)[a - 1] == '\n')
			{
				(*buffe)[a - 1] = '\0'; /* remove trailing newline */
				a--;
			}
			inf->sh_linecnt_flag = 1;
			rm_comments(*buffe);
			shell_bld_hist_list(inf, *buffe, inf->sh_hist_cnt++);
			/* if (_strchr(*buf, ';')) is this a command chain? */
			{
				*ln = a;
				inf->cmd_buffer_address = buffe;
			}
		}
	}
	return (a);
}


/**
 * shell_read_buffe - buffer
 * @inf: parameter struct
 * @buffe: the buffer
 * @s: size of buffer
 * Return: buffer contents
 */

ssize_t shell_read_buffe(info_t *inf, char *buffe, size_t *s)
{
	ssize_t x = 0;

	if (*s)
		return (0);
	x = read(inf->sh_read_filedes, buffe, READ_BUF_SIZE);
	if (x >= 0)
		*s = x;
	return (x);
}

/**
 * shell_get_input - this funct line less the newline
 * @inf: struct of a parameter
 * Return: bytes read
 */

ssize_t shell_get_input(info_t *inf)
{
	static char *buffe;
	static size_t x;
	static size_t y;
	static size_t ln;
	ssize_t a = 0;
	char **buff_ptr = &(inf->arg), *p;

	_shell_putchar(BUF_FLUSH);
	a = _shell_input_buff(inf, &buffe, &ln);
	if (a == -1)
		return (-1);
	if (ln)
	{
		y = x;
		p = buffe + x;

		sh_chain_check(inf, buffe, &y, x, ln);
		while (y < ln) /* iterate to semicolon or end */
		{
			if (sh_test_is_chain(inf, buffe, &y))
				break;
			y++;
		}

		x = y + 1; /* increment past nulled ';'' */
		if (x >= ln) /* reached end of buffer? */
		{
			x = ln = 0; /* reset position and length */
			inf->sh_cmd_buf_type = CMD_NORM;
		}

		*buff_ptr = p; /* pass back pointer to the current command position */
		return (sh_strlen(p)); /* return length of the current command */
	}

	*buff_ptr = buffe; /* else not a chain, pass back buffer from _getline() */
	return (a); /* return length of buffer from _getline() */
}

/**
 * shell_sigHandler - This function is to ctrl-C block
 * @sig_nb: a signal number
 * Return: void
 */

void shell_sigHandler(__attribute__((unused))int sig_nb)
{
	_shell_puts("\n");
	_shell_puts("$ ");
	_shell_putchar(BUF_FLUSH);
}

/**
 * shell_getline - The next line input
 * @inf: struct of a parameter
 * @pt: pt to address a buffer
 * @ln: preallocated ptr buffer size
 * Return: b
 */

int shell_getline(info_t *inf, char **pt, size_t *ln)
{
	static char buffe[READ_BUF_SIZE];
	static size_t x;
	static size_t lng;
	size_t y;
	ssize_t a = 0;
	ssize_t b = 0;
	char *q = NULL, *new_q = NULL, *c;

	q = *pt;
	if (q && ln)
		b = *ln;
	if (x == lng)
		x = lng = 0;

	a = shell_read_buffe(inf, buffe, &lng);
	if (a == -1 || (a == 0 && lng == 0))
		return (-1);

	c = _shell_strch(buffe + x, '\n');
	y = c ? 1 + (unsigned int)(c - buffe) : lng;
	new_q = sh_mem_realloc(q, b, b ? b + y : y + 1);
	if (!new_q)
		return (q ? free(q), -1 : -1);

	if (b)
		_shell_strncat(new_q, buffe + x, y - x);
	else
		_shell_strncpy(new_q, buffe + x, y - x + 1);

	b += y - x;
	x = y;
	q = new_q;

	if (ln)
		*ln = b;
	*pt = q;
	return (b);
}
