/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 13:49:22 by saxiao            #+#    #+#             */
/*   Updated: 2017/12/20 11:49:38 by saxiao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdlib.h>
#include <stdint.h>
#include "../libft/libft.h"
#include "../includes/ft_printf.h"

static	int	nb_dg_short(intmax_t n)
{
	int i;
	uintmax_t nb;

	i = 1;
	if (n < 0)
	{
		i = 2;
		nb = (uintmax_t)n * -1;
	}
	else
		nb = (uintmax_t)n;
	while (nb > 9)
	{
		i++;
		nb = nb / 10;
	}
	return (i);
}

char	*ft_itoa_short(short n)
{
	char	*number;
	int		len;
	unsigned short	cp_n;

	len = nb_dg_short(n);
	if (!(number = (char *)malloc(len + 1)))
		return (NULL);
	number[len] = '\0';
	if (!n)
		number[0] = '0';
	if (n < 0)
	{
		number[0] = '-';
		cp_n = (unsigned short)n * -1;
	}
	else
		cp_n = (unsigned short)n;
	while (cp_n)
	{
		number[--len] = cp_n % 10 + '0';
		cp_n = cp_n / 10;
	}
	return (number);
}

static	int	nb_dg(intmax_t n)
{
	int i;
	uintmax_t nb;

	i = 1;
	if (n < 0)
	{
		i = 2;
		nb = (uintmax_t)n * -1;
	}
	else
		nb = (uintmax_t)n;
	while (nb > 9)
	{
		i++;
		nb = nb / 10;
	}
	return (i);
}

char	*ft_itoa_max(intmax_t n)
{
	char	*number;
	int		len;
	intmax_t	cp_n;

	len = nb_dg(n);
	if (!(number = (char *)malloc(len + 1)))
		return (NULL);
	number[len] = '\0';
	if (!n)
		number[0] = '0';
	if (n < 0)
	{
		number[0] = '-';
		cp_n = (uintmax_t)n * -1;
	}
	else
		cp_n = (uintmax_t)n;
	while (cp_n)
	{
		number[--len] = cp_n % 10 + '0';
		cp_n = cp_n / 10;
	}
	return (number);
}

char	*ft_itoa_signchar(char n)
{
	char	*number;
	int		len;
	unsigned	char	cp_n;

	len = nb_dg(n);
	if (!(number = (char *)malloc(len + 1)))
		return (NULL);
	number[len] = '\0';
	if (!n)
		number[0] = '0';
	if (n < 0)
	{
		number[0] = '-';
		cp_n = (unsigned char)n * -1;
	}
	else
		cp_n = (unsigned char)n;
	while (cp_n)
	{
		number[--len] = cp_n % 10 + '0';
		cp_n = cp_n / 10;
	}
	return (number);
}

size_t	ft_wstrlen(wchar_t *we)
{
	size_t	i;

	i = 0;
	while(*we++)
		i++;
	return (i);
}

void	ft_putwstr(wchar_t *we)
{
	while(*we)
		ft_putwstr(we++);
}

static	void	set_print_s(t_data *data)
{
	int		nbr_l;

	nbr_l = 0;
	if (data->precison == -1)
		data->precison = ft_strlen(data->ori);
	if (data->precison > (int)ft_strlen(data->ori))
		nbr_l = ft_strlen(data->ori);
	else
		nbr_l = data->precison;
	data->len = max_2(data->width, nbr_l);
	if (ft_strchr(data->flags, '-'))
	{
		ft_putnstr(data->ori, nbr_l);
		ft_putnchar(' ', data->len - nbr_l);
	}
	else
	{
		ft_putnchar(' ', data->len - nbr_l);
		ft_putnstr(data->ori, nbr_l);
	}
}

static	void	set_print_S(t_data *data, wchar_t *we)
{
	int		nbr_l;

	nbr_l = 0;
	if (data->precison == -1)
		data->precison = ft_wstrlen(we);
	if (data->precison > (int)ft_strlen(data->ori))
		nbr_l = ft_strlen(data->ori);
	else
		nbr_l = data->precison;
	data->len = max_2(data->width, nbr_l);
	if (ft_strchr(data->flags, '-'))
	{
		ft_putnwstr(we, nbr_l);
		ft_putnchar(' ', data->len - nbr_l);
	}
	else
	{
		ft_putnchar(' ', data->len - nbr_l);
		ft_putnwstr(we, nbr_l);
	}
}

void	con_s(va_list args, t_data *data, char *format, int size)
{
	wchar_t		*we;

	set_cast(data, format, size);
	set_flags(data, format, size);
	if (data->cast == l)
	{
		we = va_arg(args, wchar_t *);
		set_print_S(data, we);
	}
	else
	{
		data->ori = va_arg(args, char *);
		if (!data->ori)
			data->ori = ft_strdup("(null)");
		set_print_s(data);
	}
}

void	con_S(va_list args, t_data *data, char *format, int size)
{
	wchar_t		*we;

	we = va_arg(args, wchar_t *);
	set_cast(data, format, size);
	set_flags(data, format, size);
	set_print_S(data, we);
}
