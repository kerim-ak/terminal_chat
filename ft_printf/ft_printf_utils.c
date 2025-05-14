#include <unistd.h>

int	ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_putstr(char *s)
{
	int	i;

	i = 0;
	if (!s)
	{
		write(1, "(null)", 6);
		return (6);
	}
	while (s[i] != '\0')
		i += write(1, &s[i], 1);
	return (i);
}

int	ft_putnbr(int n)
{
	int		len;

	len = 0;
	if (n == -2147483648)
	{
		len += ft_putnbr(-214748364);
		len += ft_putnbr(8);
	}
	else if (n < 0)
	{
		len += ft_putchar('-');
		len += ft_putnbr(-n);
	}
	else if (n >= 10)
	{
		len += ft_putnbr(n / 10);
		len += ft_putnbr(n % 10);
	}
	else
		len += ft_putchar(n + 48);
	return (len);
}

int	ft_puthex(unsigned long num, unsigned long base, char c)
{
	int	len;

	len = 0;
	if (num >= base)
	{
		len += ft_puthex(num / base, base, c);
		len += ft_puthex(num % base, base, c);
	}
	else
	{
		if (num < 10)
		{
			c = num + 48;
			len += ft_putchar(c);
		}
		else if (num >= 10)
		{
			if (c == 'x')
				c = num % 10 + 'a';
			else
				c = num % 10 + 'A';
			len += ft_putchar(c);
		}
	}
	return (len);
}

int	ft_putptr(unsigned long address)
{
	if (!address)
		return (ft_putstr("(nil)"));
	return (ft_putstr("0x") + ft_puthex(address, 16, 'x'));
}
