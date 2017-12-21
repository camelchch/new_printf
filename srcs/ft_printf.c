/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 14:11:07 by saxiao            #+#    #+#             */
/*   Updated: 2017/12/21 17:57:44 by saxiao           ###   ########.fr       */
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
	{'%',con_per},
	{'p',con_p},
	{'U',con_U},
	{'x',con_x},
	{'X',con_XX}
};

int		ft_printf(const char *restrict format, ...)
{
	va_list		args;
	va_start(args, format);
	int			i;
	int			nbr;
	int			j;
	int			is_per;
	t_data		data;

	nbr = 0;
	while (*format)
	{
		j = 0;
		i = 0;
		is_per = 0;
		if( *format == '%')
		{
			while(format + i && format[i] && !is_format(format[i]) && !is_per)
			{
				i++;
				if (format + i && format[i] == '%')
					is_per = 1;
			}
			while (format && j < NB_CON && set[j].c != format[i])
				j++;
			if (format && j < NB_CON)
			{
				(set[j].func)(args, &data, (char *)format, i);
				nbr = nbr + data.len;
			}
			format = format + i + 1;
		}
		else
		{
			ft_putchar(*format++);
			nbr++;
		}
	}
	return (nbr);
}
