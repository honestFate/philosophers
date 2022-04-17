#include "../philosophers.h"



int	main(int argc, char **argv)
{
	int				i;
	int				status;
	sem_t			*semaphore;
	char			*sem_name;
	t_philos_info	*philos;

	if (argc < 5 || argc > 6 || arg_parser(argv))
		return (error("INVALID ARGUMENTS"));
	sem_name = "/philo";
	semaphore = sem_open(sem_name, O_CREAT, 0644, 2);
	philos = initialization(argc, argv, semaphore);
	if (!philos)
	{
		sem_close(semaphore);
		sem_unlink(sem_name);
		return (error("INITIALIZATION ERR"));
	}
	waitpid(-1, &status, WUNTRACED);
	printf("returned status - %d\n", status);
	i = 0;
	free_all(philos);
	sem_close(semaphore);
	sem_unlink(sem_name);
}