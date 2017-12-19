/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 14:11:07 by saxiao            #+#    #+#             */
/*   Updated: 2017/12/16 01:24:49 by saxiao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <wchar.h>
#include <wctype.h>
#include "../libft/libft.h"
#include "../includes/ft_printf.h"

static int		is_format(char c)
{
	return (c == 's' || c == 'S' || c == 'p' || c == 'd' || c == 'D' || c == 'i' ||\
			c == 'o' || c == 'O' || c == 'u' || c == 'U' || c == 'x' || c == 'X' ||\
			c == 'c' || c == 'C');
}

static	void	init(t_data *data)
{
	data->ori = NULL;
	ft_bzero(data->flags, 10);
	data->width = 0;
	data->precison = -1;
	data->len = 0;
	data->no_pre = 0;
	data->blank = 0;
	data->cast = none;
}

void	set_cast(t_data *data, char *format, int size)
{
	init(data);
	if (ft_strnchr(format, 'h', size))
	{
		if (ft_strnchr_double(format, 'h', size))
			data->cast = hh;
		else
			data->cast = h;
	}
	else if (ft_strnchr(format, 'l', size))
	{
		if (ft_strnchr_double(format, 'l', size))
			data->cast = ll;
		else
			data->cast = l;
	}
	else if(ft_strnchr(format, 'j',size))
		data->cast = j;
	else if(ft_strnchr(format, 'z',size))
		data->cast = z;
	else data->cast = none;
}


void	set_flags(t_data *data, char *format, int size)
{
	int		i;
	int		j;

	i = 1;
	j = 0;
	while (i < size && j < 10)
	{
		if (format[i] == '0')
		{
			if (!(ft_strchr(data->flags, '0')))
				data->flags[j++] = '0';
			i++;
		}
		else if ('0' < format[i] && format[i] <= '9')
		{
			data->width = ft_atoi(format + i);
			i = i + nb_digit(format + i);
		}
		else if (format[i] == '.')
		{
			//if ('0' <= format[i + 1] &&  format[i + 1] <= '9')
				data->precison = ft_atoi(format + 1 + i);
			i = i + nb_digit(format + i + 1) + 1;
		}
		else
		{
			if(ft_strchr("#-+ ", format[i]))
				data->flags[j++] = format[i];
			i++;
		}
	}
}


int		ft_printf(const char *restrict format, ...)
{
	va_list		args;
	va_start(args, format);
	int			i;
	int			nbr;
	int			j;
	t_data		data;
	t_fu	set[NB_CON] = {
		{'s',con_s},
		{'S',con_S},
		{'o',con_o},
		{'O',con_O},
		{'d',con_d},
		{'D',con_D},
		{'i',con_d},
		{'c',con_c},
		{'C',con_c},
		{'u',con_u},
		{'p',con_p},
		{'U',con_U},
		{'x',con_x},
		{'X',con_XX},
	};
	nbr = 0;
	while (*format)
	{
		j = 0;
		i = 0;
		if( *format == '%')
		{
			if ((format + 1) && *(format + 1) == '%')
			{
				ft_putchar('%');
				format = format + 2;
				nbr++;
			}
			else
			{
				while(format && format[i] && !is_format(format[i]))
					i++;
				while (format && j < NB_CON && set[j].c != format[i])
					j++;
				if (format && j < NB_CON)
				{
					(set[j].func)(args, &data, (char *)format, i);
				nbr = nbr + data.len;
				}
				format = format + i + 1;
			}
		}
		else
		{
			ft_putchar(*format++);
			nbr++;
		}
	}
	return (nbr);
}
/*
int		main()
{
	ft_printf("%5.0d", 0);
	return (0);
}
*/
