#include "shell.h"

/**
 * chain_buf - Function buffers chained strings.
 * @check: parameter one.
 * @buffer: Buffer(main display).
 * @len: Address of the length.
 * Return: Returns the bytes.
 */
ssize_t chain_buf(info_t *check, char **buffer, size_t *len)
{
	ssize_t n = 0;
	size_t hold = 0;

	/*Fill the buffer if it is empty*/
	if (!*len)
	{
		free(*buffer);
		*buffer = NULL;
		signal(SIGINT, _block);
#if USE_GETLINE
		n = _getline(buffer, &hold, stdin);
#else
		n = _getline(check, buffer, &hold);
#endif
		if (n > 0)
		{
			if ((*buffer)[n - 1] == '\n')
			{
				(*buffer)[n - 1] = '\0';
				n--;
			}
			check->linecount_flag = 1;
			shell_prep(*buffer);
			append_history(check, *buffer, check->histcount++);
			{
				*len = n;
				check->cmd_buf = buffer;
			}
		}
	}
	return (n);
}

/**
 * shell_input - Function reads the string input.
 * @check: parameter one.
 * Return: Input obtained from the buffer.
 */
ssize_t shell_input(info_t *check)
{
	static char *buffer;
	static size_t n, a, len;
	ssize_t b = 0;
	char **hold = &(check->arg), *place;

	_putchar(BUF_FLUSH);
	b = chain_buf(check, &buffer, &len);
	if (b == -1)
		return (-1);
	/* If the buffer is not empty*/
	if (len)
	{
		a = n;
		/* represents curr buffer position*/
		place = buffer + n;

		halt_chain(check, buffer, &a, n, len);
		while (a < len)
		{
			if (is_chain(check, buffer, &a))
				break;
			a++;
		}
		n = a + 1;
		if (n >= len)
		{
			n = len = 0;
			check->cmd_buf_type = CMD_NORM;
		}
		*hold = place;
		/* represents curr command line position*/
		return (_strlen(place));
	}
	*hold = buffer;
	return (b);
	/* returns input obtained from buffer*/
}

/**
 * rd_buf - Function reads a buffer
 * @check: parameter one.
 * @buffer: buffer
 * @buf_size: size of the buffer.
 * Return: Function returns contents of the buffer.
 */
ssize_t rd_buf(info_t *check, char *buffer, size_t *buf_size)
{
	ssize_t n = 0;

	if (*buf_size)
		return (0);
	n = read(check->readfd, buffer, READ_BUF_SIZE);
	if (n >= 0)
		*buf_size = n;
	return (n);
}

/**
 * _getline - Function gets the string input from the standard input.
 * @check: parameter one.
 * @ptr: Pointer to the buffer.
 * @buf_size: Size of the buffer.
 * Return: s
 */
int _getline(info_t *check, char **ptr, size_t *buf_size)
{
	static char buffer[READ_BUF_SIZE];
	static size_t n, len;
	size_t a;
	ssize_t r = 0, s = 0;
	char *place = NULL, *new_place = NULL, *c;

	place = *ptr;
	if (place && buf_size)
		s = *buf_size;
	if (n == len)
		n = len = 0;

	r = rd_buf(check, buffer, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchr(buffer + n, '\n');
	a = c ? 1 + (unsigned int)(c - buffer) : len;
	new_place = my_realloc(place, s, s ? s + a : a + 1);
	if (!new_place)
		return (place ? free(place), -1 : -1);

	if (s)
		_strncat(new_place, buffer + n, a - n);
	else
		_strncpy(new_place, buffer + n, a - n + 1);

	s += a - n;
	n = a;
	place = new_place;

	if (buf_size)
		*buf_size = s;
	*ptr = place;
	return (s);
}

/**
 * _block - Function blocks ctrl-C command.
 * @num: parameter one.
 * Return: void
 */
void _block(__attribute__((unused))int num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}

