/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/18 23:04:19 by saxiao            #+#    #+#             */
/*   Updated: 2017/12/21 18:45:13 by saxiao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "../includes/ft_printf.h"
#include "../libft/libft.h"

char	*ft_itoa_unmax(uintmax_t n)
{
	char	*number;
	uintmax_t		len;

	len = nb_dg_inbase(n, 10);
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
