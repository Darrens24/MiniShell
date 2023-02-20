#include <stdio.h>

int ft_strlen(char *str)
{
	int i = 0;

	while (str[i])
		i++;
	return(i);
}

int main(int ac, char **av)
{
	int i = 0;

	if(ac > 1)
	{
		i = ft_strlen(av[1]);
		printf("la longueur de la chaine est : %d \n", i);
		printf("la chaine est %s \n", av[1]);
		while(i > 0)
			printf("a");
	}
	return (0);
}

		
