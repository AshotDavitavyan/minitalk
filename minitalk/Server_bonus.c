#include "minitalk.h"

void	signal_handler(int signum, siginfo_t *info, void *context)
{
	static int				bit = 0;
	static unsigned char	symbol = 0;

	(void)context;
	if (signum == SIGUSR2)
		bit++;
	else if (signum == SIGUSR1)
	{
		symbol |= 1;
		bit++;
	}
	if (bit == 8)
	{
		bit = 0;
		if (!symbol)
		{
			kill(info->si_pid, SIGUSR2);
			return ;
		}
		kill(info->si_pid, SIGUSR1);
		write(1, &symbol, 1);
	}
	else
	       symbol <<= 1;
}

int	main(void)
{
	struct sigaction	signal_received;

	ft_printf("Server's id: %d\n", getpid());
	signal_received.sa_sigaction = signal_handler;
	signal_received.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &signal_received, NULL);
	sigaction(SIGUSR2, &signal_received, NULL);
	while (1)
		pause();
	return (0);
}
