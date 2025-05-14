#include "ft_printf.h"

static int	ft_print_out(char c, va_list data)
{
	int	ret;

	ret = 0;
	if (c == 'c')
		ret += ft_putchar((char)va_arg(data, int));
	else if (c == 's')
		ret += ft_putstr(va_arg(data, char *));
	else if (c == 'p')
		ret += ft_putptr((unsigned long)va_arg(data, unsigned long));
	else if (c == 'd' || c == 'i')
		ret += ft_putnbr(va_arg(data, int));
	else if (c == 'u')
		ret += ft_puthex(va_arg(data, unsigned int), 10, c);
	else if (c == 'x')
		ret += ft_puthex(va_arg(data, unsigned int), 16, c);
	else if (c == 'X')
		ret += ft_puthex(va_arg(data, unsigned int), 16, c);
	else if (c == '%')
		ret += ft_putchar(c);
	return (ret);
}

int	ft_printf(const char *str, ...)
{
	va_list	data;
	int		i;
	int		len;

	i = 0;
	len = 0;
	va_start(data, str);
	while (str[i] != '\0')
	{
		if (str[i] == '%' && str[i + 1] != '\0')
		{
			i++;
			len += ft_print_out(str[i], data);
		}
		else
			len += ft_putchar(str[i]);
		i++;
	}
	va_end(data);
	return (len);
}
