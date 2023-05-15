#include "minitalk.h"

void	signal_handler(int signum, siginfo_t *info, void *context)
{
	static int				bit = 0;
	static unsigned char	symbol = 0;

	(void)context;
	(void)info;
	if (signum == SIGUSR2)
	{
		symbol = symbol << 1;
		bit++;
	}
	else if (signum == SIGUSR1)
	{
		symbol = symbol | 1;
		symbol = symbol << 1;
		bit++;
	}
	if (bit == 8 && symbol)
	{
		write(1, &symbol, 1);
		bit = 0;
		symbol = 0;
	}
//	else if (bit == 8 && !symbol)
//		kill(info->si_pid, SIGUSR1);
	return ;
}
// void	ft_putchar_fd(char c, int fd)
// {
// 	write (fd, &c, 1);
// }

// static void	signal_handler(int sig, siginfo_t *info, void *context)
// {
// 	static int				i = 0;
// 	static pid_t			client_pid = 0;
// 	static unsigned char	c = 0;

// 	(void)context;
// 	if (!client_pid)
// 		client_pid = info->si_pid;
// 	c |= (sig == SIGUSR2);
// 	if (++i == 8)
// 	{
// 		i = 0;
// 		if (!c)
// 		{
// 			client_pid = 0;
// 			return ;
// 		}
// 		ft_putchar_fd(c, 1);
// 		c = 0;
// 	}
// 	else
// 		c <<= 1;
// }

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
