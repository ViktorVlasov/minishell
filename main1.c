#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int		get_next_line(int fd, char **line)
{
	int			read_len;
	char		buf[BUFFER_SIZE + 1];
	static char	*stock = NULL;

	if (line == NULL || fd < 0 || BUFFER_SIZE < 1 || (read(fd, buf, 0)) < 0)
		return (-1);
	read_len = 1;
	while (!(newline_check(stock, read_len)))
	{
		if ((read_len = read(fd, buf, BUFFER_SIZE)) == -1)
			return (-1);
		buf[read_len] = '\0';
		(read_len == 0 || buf[read_len - 1] != '\n') ? ft_printf("  \b\b") : 0;
		if ((stock = buf_join(stock, buf)) == NULL)
			return (-1);
	}
	if (newline_check(stock, read_len) == 2 && (*line = stock))
		return (-2);
	if ((*line = get_line(stock)) == NULL)
		return (-1);
	if ((stock = stock_trim(stock)))
		return (-1);
	ft_memdel(stock);
	return (read_len != 0 ? 1 : 0);
}

int main(void)
{
	int check;
	int i = 0;
	char *buf;
	buf = (char*)malloc(1 + 1);
	while (i < 5)
	{
		check = read(0, buf, 1);
		printf("%d", check);
		i++;
	}
}


