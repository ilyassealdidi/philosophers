#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

int j = 0;;

void	*func()
{
	int i;
	while (++i <= 50000)
		j++;
	return (NULL);
}

int main()
{
	pthread_t	thread;
	pthread_t	thread2;

	pthread_create(&thread, NULL, func, NULL);
	pthread_create(&thread2, NULL, func, NULL);
	pthread_join(thread, NULL);
	pthread_join(thread2, NULL);
	printf("%d\n", j);
}
