#include "minitalk.h"

static int	g_is_signal_came;

static void	signal_handler(int sig)
{
	if (sig == SIGUSR1)
		g_is_signal_came = 1;
}

static void	send_signal(pid_t pid, char c)
{
	int	i;

	i = 7;
	while (i >= 0)
	{
		g_is_signal_came = 0;
		if (c & (1 << i))
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		i--;
		while (!g_is_signal_came)
			pause();
	}
}

static int	ft_atoi(const char *str)
{
	int	i;
	int	res;
	int	sign;

	i = 0;
	res = 0;
	sign = 1;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r' || str[i] == ' ')
		i++;
	while (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - 48;
		i++;
	}
	return (res * sign);
}

static int	error_check(char *str)
{
	int	len;
	int	i;
	int	num;

	i = 0;
	len = 0;
	num = 0;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r' || str[i] == ' '
		|| str[i] == '+' || str[i] == '-' || str[i] == '0')
		i++;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			len++;
		i++;
	}
	if (len > 7)
		return (1);
	num = ft_atoi(str);
	if (num < 1 || num > 4194304)
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	pid_t	server_pid;
	char	*message;
	int		i;

	if (argc != 3)
	{
		ft_printf("Usage: %s <PID> <Message>\n", argv[0]);
		return (1);
	}
	if (error_check(argv[1]))
	{
		ft_printf("Invalid PID!\n");
		return (1);
	}
	server_pid = ft_atoi(argv[1]);
	message = argv[2];
	i = -1;
	signal(SIGUSR1, signal_handler);
	while (message[++i])
		send_signal(server_pid, message[i]);
	send_signal(server_pid, '\n');
	return (0);
}
