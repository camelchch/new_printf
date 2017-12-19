/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 13:49:22 by saxiao            #+#    #+#             */
/*   Updated: 2017/12/15 22:47:27 by saxiao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdlib.h>
#include <stdint.h>
#include "../libft/libft.h"
#include "../includes/ft_printf.h"

static	void	set_print_c(va_list args, t_data *data)
{
	int		len;

	len = max_2(1, data->width);
	if (ft_strchr(data->flags, '-'))
	{
		if (data->cast == l)
			ft_putwchar(va_arg(args, wchar_t));
		else
			ft_putchar((unsigned char)va_arg(args, int));
		ft_putnchar(' ', len - 1);
	}
	else
	{
		if (ft_strchr(data->flags, '0'))
			ft_putnchar('0', len - 1);
		else
			ft_putnchar(' ', len - 1);
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
	data->len = 1;
}

void	con_C(va_list args, t_data *data, char *format, int size)
{
	set_cast(data, format, size);
	set_flags(data, format, size);
	set_print_c(args, data);
	data->len = 1;
}

void	con_p(va_list args, t_data *data, char *format, int size)
{
	set_cast(data, format, size);
	data->ori = itoa_hex(va_arg(args, unsigned long), 'x');
	set_flags(data, format, size);
	ft_putstr("0x");
	ft_putstr(data->ori);
	data->len = ft_strlen(data->ori) + 2;
}