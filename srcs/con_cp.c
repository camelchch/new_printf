/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 13:49:22 by saxiao            #+#    #+#             */
/*   Updated: 2017/12/20 13:20:41 by saxiao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdlib.h>
#include <stdint.h>
#include "../libft/libft.h"
#include "../includes/ft_printf.h"

static	void	set_print_c(va_list args, t_data *data)
{

	data->len = max_2(1, data->width);
	if (ft_strchr(data->flags, '-'))
	{
		if (data->cast == l)
			ft_putwchar(va_arg(args, wchar_t));
		else
			ft_putchar((unsigned char)va_arg(args, int));
		ft_putnchar(' ', data->len - 1);
	}
	else
	{
		if (ft_strchr(data->flags, '0'))
			ft_putnchar('0', data->len - 1);
		else
			ft_putnchar(' ', data->len - 1);
		if (data->cast == l)
			ft_putwchar(va_arg(args, wchar_t));
		else
			ft_putchar((unsigned char)va_arg(args, int));
	}
}

void	con_c(va_list args, t_data *data, char *format, int size)
{
	set_cast(data, format, size);
	set_flags(data, format, size);
	set_print_c(args, data);
}

void	con_C(va_list args, t_data *data, char *format, int size)
{
	set_cast(data, format, size);
	set_flags(data, format, size);
	set_print_c(args, data);
}

void	con_p(va_list args, t_data *data, char *format, int size)
{
	int		i;

	i = 0;
	set_cast(data, format, size);
	data->ori = itoa_hex(va_arg(args, unsigned long), 'x');
	set_flags(data, format, size);
	while (data->flags[i])
		i++;
	data->flags[i] = '#';
	if (data->ori[0] != '0')
		set_print_oxu_hash(data, "0x");
	else
	{
		data->len = max_2(data->width, 3);
		if (ft_strchr(data->flags, '-'))
		{
			ft_putstr("0x0");
			ft_putnchar(' ', data->len - 3);
		}
		else
		{
			ft_putnchar(' ', data->len - 3);
			ft_putstr("0x0");
		}
	}
}

	void	con_per(va_list args, t_data *data, char *format, int size)
	{
		(void)args;
		set_cast(data, format, size);
		set_flags(data, format, size);
		data->ori = "%";
		data->len = max_2(1, data->width);
		if (ft_strchr(data->flags, '-'))
		{
			ft_putchar('%');
			ft_putnchar(' ', data->len - 1);
		}
		else
		{
			if (ft_strchr(data->flags, '0'))
				ft_putnchar('0', data->len - 1);
			else
				ft_putnchar(' ', data->len - 1);
			ft_putchar('%');
		}
	}
