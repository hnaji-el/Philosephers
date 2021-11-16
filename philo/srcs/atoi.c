
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int	ft_atoi(const char *str)
{
	long	nb;
	int		sign;

	sign = 1;
	nb = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-')
		sign = sign * (-1);
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		nb = nb * 10 + (*str - '0');
		str++;
	}
	if (nb < 0 && sign > 0)
		return (-1);
	if (nb < 0 && sign < 0)
		return (0);
	return (sign * nb);
}

int	all_elements_isvalid(char *str)
{
	int		i;

	i = 0;
	if ((*str == '+' || *str == '-') && str[1] != '\0')
		i++;
	while (str[i] != '\0')
	{
		if (!isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}


int	main(void)
{
	int		ret;

	ret = all_elements_isvalid("-0");
	if (ret == 0)
		printf("FALSE\n");
	if (ret == 1)
		printf("TRUE\n");
//	char	*str = "      -";
//
//	printf("%d\n", atoi(str));
//	printf("%d\n", ft_atoi(str));
	return (0);
}
