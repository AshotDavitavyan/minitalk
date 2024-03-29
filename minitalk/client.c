/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adavitav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 12:38:21 by adavitav          #+#    #+#             */
/*   Updated: 2023/05/12 12:52:47 by adavitav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	int	line;
	int	bit;

	line = 0;
	bit = 0;
	while (message[line])
	{
		bit = 0;
		while (bit <= 7)
		{
			if (((message[line] >> bit) & 1) == 1)
				kill(pid, SIGUSR1);
			else if (((message[line] >> bit) & 1) == 0)
				kill(pid, SIGUSR2);
			bit++;
			usleep(50);
		}
		line++;
	}
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
		send_signals(pid, message);
	}
	return (0);
}
