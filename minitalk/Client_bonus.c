
#include "minitalk.h"

void	error_message(char c)
{
	if (c == 'a')
	{
		ft_printf("Wrong number of arguments\nMake sure to run the program ");
		ft_printf("the following way:\n./client <Server PID> <Text Message>\n");
	}
	else if (c == 'b')
		ft_printf("Invalid process Id\n");
	else if (c == 'c')
		ft_printf("Invalid message\n");
	exit (1);
}

int	ft_atoi(const char *str)
{
	int	mult;
	int	res;

	mult = 1;
	res = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-')
	{
		mult *= -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		res *= 10;
		res += (*str - '0');
		str++;
	}
	return (res * mult);
}

void	send_signals(int pid, char *message)
{
 	int			line;
 	int			bit;

 	line = 0;
 	bit = 0;
 	while (message[line])
 	{
 		bit = 7;
 		while (bit >= 0)
		{
 			if (((message[line] >> bit) & 1) == 1)
 				kill(pid, SIGUSR1);
 			else if (((message[line] >> bit) & 1) == 0)
 				kill(pid, SIGUSR2);
 			bit--;
 			usleep(50);
 		}
 		line++;
 	}
	bit = 8;
	while (bit--)
	{
		kill(pid, SIGUSR2);
		usleep(50);
	}
}
void	receive(int sig)
{
	static int	bytes = 0;
	
	if (sig == SIGUSR1)
	{
		ft_printf("asdasd\n");
		bytes++;
	}
	else
		ft_printf("%d\n", bytes);
}

int	main(int argc, char **argv)
{
	int		pid;
	char	*message;

	if (argc != 3)
		error_message('a');
	else
	{
		pid = ft_atoi(argv[1]);
		if (!pid)
			error_message('b');
		message = argv[2];
		if (!message[0])
			error_message('c');
		printf("Bytes:");
		signal(SIGUSR1, receive);
		signal(SIGUSR2, receive);
		send_signals(pid, message);
	}
	while (1)
	;
	return (0);
}
