/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtod.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 00:14:59 by sunko             #+#    #+#             */
/*   Updated: 2023/12/23 23:29:01 by seunan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <float.h>
#include "libft.h"

// 2^53 - 1
#define MAX_SAFE_INTEGER 9007199254740990 

static void	make_double(char *s, double *integer, double *fractional, int *neg);
static void	make_fractional(char *s, double *fractional);

double	ft_strtod(char *s)
{
	double	integer;
	double	fractional;
	int		neg;

	integer = 0;
	fractional = 0;
	neg = 0;
	make_double(s, &integer, &fractional, &neg);
	if (neg)
		return (-integer - fractional);
	else
		return (integer + fractional);
}

static void	make_double(char *s, double *integer, double *fractional, int *neg)
{
	if (*s == '-' || *s == '+')
	{
		if (*s == '-')
			*neg = 1;
		s++;
	}
	if (!ft_isdigit(*s))
		ft_error("File Format Error");
	while (ft_isdigit(*s))
	{
		if (*integer >= MAX_SAFE_INTEGER / 10)
			ft_error("File Format Error");
		*integer = *integer * 10 + *s - '0';
		++s;
	}
	make_fractional(s, fractional);
}

static void	make_fractional(char *s, double *fractional)
{
	double	len;

	len = 0;
	if (*s == '.')
	{
		++s;
		while (ft_isdigit(*s))
		{
			*fractional = *fractional * 10 + *s - '0';
			++len;
			++s;
		}
		if (len == 0)
			ft_error("File Format Error");
		while (len > 0)
		{
			*fractional /= 10;
			--len;
		}
	}
	if (*s != '\0')
		ft_error("File Format Error");
}

/* TEST */

// #include <stdio.h>

// int	main(void)
// {
// 	printf("%lf\n", ft_strtod("32123.123"));
// 	printf("%lf\n", ft_strtod("32123.123456789"));
// 	printf("%lf\n", ft_strtod("0.999999"));
// 	printf("%lf\n", ft_strtod("0.9999999"));
// 	printf("%lf\n", ft_strtod("-123456789.123456789"));
// 	printf("%lf\n", ft_strtod("0.0"));
// 	printf("%lf\n", ft_strtod("-0.0"));
// 	printf("%lf\n", ft_strtod("-9007199254740990"));
// 	printf("%lf\n", ft_strtod("9007199254740990"));

// 	// 오차
// 	printf("%lf\n", ft_strtod("-900719925474099.1"));
// 	printf("%lf\n", ft_strtod("-9007199254740990.123456"));

// 	// ERROR
// 	printf("%lf\n", ft_strtod(".12312"));
// 	printf("%lf\n", ft_strtod("0."));

// 	printf("%ld\n", -9007199254740990);
// 	printf("%lld\n", (long long)ft_strtod("-9007199254740990"));

// 	/* -MAX_SAFE_INTEGER ~ MAX_SAFE_INTEGER TEST*/
// 	for (long long i = -MAX_SAFE_INTEGER; i <= MAX_SAFE_INTEGER; i++)
// 	{
// 		if (i != (long long)ft_strtod(ft_itoa(i)))
// 		{
// 			printf("i                     : %lld\n", i);
// 			printf("ft_strtod(ft_itoa(i)) : %lf\n", ft_strtod(ft_itoa(i)));
// 		}
// 	}

// 	for (long long i = 0; i <= MAX_SAFE_INTEGER; i++)
// 	{
// 		if (i != (long long)ft_strtod(ft_itoa(i)))
// 		{
// 			printf("i                     : %lld\n", i);
// 			printf("ft_strtod(ft_itoa(i)) : %lf\n", ft_strtod(ft_itoa(i)));
// 		}
// 		else
// 		{
// 			printf("\033[0;32mOK\n");
// 		}
// 	}
// 	return (0);
// }
