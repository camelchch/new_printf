/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 14:11:07 by saxiao            #+#    #+#             */
/*   Updated: 2017/12/21 18:30:57 by saxiao           ###   ########.fr       */
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

static	void	move_i(char *format, t_mark *m)
{
	(m->i)++;
	if (format + m->i && format[m->i] == '%')
		m->per = 1;
}

static	void	move_format(char **format, t_mark *m)
{
	ft_putchar(**format);
	(*format)++;
	(m->nbr)++;
}

static	void	ini_m(t_mark *m, t_data *data)
{
	m->j = 0;
	m->i = 0;
	m->per = 0;
	data->len = 0;
}

int		ft_printf(const char *restrict format, ...)
{
	va_list		args;
	va_start(args, format);
	t_mark		m;
	t_data		data;

	m.nbr = 0;
	while (*format)
	{
		ini_m(&m,  &data);
		if( *format == '%')
		{
			while(format + m.i && format[m.i] && !is_format(format[m.i]) && !m.per)
				move_i((char *)format, &m);
			while (format && m.j < NB_CON && set[m.j].c != format[m.i])
				(m.j)++;
			if (format && m.j < NB_CON)
				(set[m.j].func)(args, &data, (char *)format, m.i);
			m.nbr = m.nbr + data.len;
			format = format + m.i + 1;
		}
		else
			move_format((char **)&format, &m);
	}
	return (m.nbr);
}
