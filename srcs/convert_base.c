/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/18 23:04:19 by saxiao            #+#    #+#             */
/*   Updated: 2017/12/20 16:15:35 by saxiao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "../includes/ft_printf.h"
#include "../libft/libft.h"

static uintmax_t	nb_dg(uintmax_t n, unsigned int base_to)
{
	uintmax_t i;

	i = 1;
	while (n > base_to - 1)
	{
		i++;
		n = n / base_to;
	}
	return (i);
}

char	*ft_itoa_unmax(uintmax_t n)
{
	char	*number;
	uintmax_t		len;

	len = nb_dg(n, 10);
	if (!(number = (char *)malloc(len + 1)))
		return (NULL);
	number[len] = '\0';
	if (!n)
		number[0] = '0';
	while (n)
	{
		number[--len] = n % 10 + '0';
		n = n / 10;
	}
	return (number);
}

static	intmax_t		base_length(char *base)
{
	intmax_t		i;

	i = 0;
	while (base[i])
		i++;
	return (i);
}

static	int		position_in_base(char *base, char search)
{
	int		i;

	i = 0;
	while (search != *base)
	{
		i++;
		base++;
	}
	return (i);
}

static	char	*reverse_delect_first_zeros(char *tab, char *base_to)
{
	char	temp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (tab[j])
		j++;
	while (i < j - 1)
	{
		temp = tab[i];
		tab[i] = tab[j - 1];
		tab[j - 1] = temp;
		i++;
		j--;
	}
	while (!position_in_base(base_to, *tab))
		tab++;
	return (tab);
}

static	char	*ft_convert_base(char *nbr, char *base_from, char *base_to)
{
	uintmax_t		in_ten_b;
	char	*result;
	intmax_t		number_base;
	intmax_t		i;

	i = 0;
	in_ten_b = 0;
	number_base = base_length(base_from);
	while (*nbr)
		in_ten_b = in_ten_b * number_base + position_in_base(base_from, *nbr++);
	result = malloc(sizeof(*result) * (nb_dg(in_ten_b, 10) + 1));
	if (!in_ten_b)
	{
		result[0] = base_to[0];
		result[1] = '\0';
		return (result);
	}
	while (in_ten_b > 0)
	{
		result[i++] = base_to[in_ten_b % base_length(base_to)];
		in_ten_b = in_ten_b / base_length(base_to);
	}
	result[i] = '\0';
	result = reverse_delect_first_zeros(result, base_to);
	return (result);
}

char		*itoa_base(uintmax_t nb, int from, int to)
{
	int		i;
	char	*ori;
	char	base_from[from + 1];
	char	base_to[from + 1];
	char	*result;

	i = 0;
	char	a = '0';
	while (i < from)
		base_from[i++] = a++;
	base_from[i] = '\0';
	i = 0;
	a = '0';
	while (i < to)
		base_to[i++] = a++;
	base_to[i] = '\0';
	ori = ft_itoa_unmax(nb);
	result = ft_convert_base(ori, base_from, base_to);
	return (result);
}

char		*itoa_hex(uintmax_t nb,  char x)
{
	char	*result;
	char	*ori;

	ori = ft_itoa_unmax(nb);
	if (x == 'x')
	result = ft_convert_base(ori, "0123456789", "0123456789abcdef");
	if (x == 'X')
	result = ft_convert_base(ori, "0123456789", "0123456789ABCDEF");
	free(ori);
	return (result);
}
