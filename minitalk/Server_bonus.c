#include "minitalk.h"

int	power(int number, int power)
{
	int	result;

	result = number;
	if (power == 0)
		return (1);
	while (power > 1)
	{
		result *= number;
		power--;
	}
	return (result);
}

void	signal_handler(int signum)
{
	static int	bit = 0;
	static int	char_ascii = 0;

	if (signum == SIGUSR2)
		bit++;
	else if (signum == SIGUSR1)
	{
		char_ascii += power(2, bit);
		bit++;
	}
	if (bit == 8)
	{
		write(1, &char_ascii, 2);
		bit = 0;
		char_ascii = 0;
	}
}

int	main(void)
{
	struct sigaction	signal_received;

	ft_printf("Server's id: %d\n", getpid());
	signal_received.sa_handler = signal_handler;
	signal_received.sa_flags = 0;
	sigaction(SIGUSR1, &signal_received, NULL);
	sigaction(SIGUSR2, &signal_received, NULL);
	while (1)
		;
	return (0);
}
