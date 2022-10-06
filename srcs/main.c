#include "laendrun.h"

int	main(int ac, char **av)
{
	t_document	document;
	t_config 		config;

	config.logo_path = "./images/logo_transparent_background.jpg";
	config.twint_dir_path = "./images/Twint_directives.jpg";
	config.twint_qr_path = "./images/Twint_QR.jpg";

	if (ac != 4)
		error("Wrong number of arguments.");
	else
	{
		if (ft_char_is_num(av[1][0]))
			document.type = ft_atoi(&av[1][0]);
		else
			error("Argument 1 has to be numeric.");

		if (ft_check_client_format(av[2]))
			document.client = av[2];
		else
			error("Please check client number format.");

		if (ft_str_is_num(av[3]))
			document.number = av[3];
		else
			error("Please check document number.");

		if (document.type == 0)
		{
			ft_putstr("Not implemented yet");
			//gen_oc(document);
		}
		else if (document.type == 1)
		{
			ft_putstr("Not implemented yet");
			//gen_cv(document);
		} 
		else if (document.type == 2)
		{
			gen_fa(document, config);
		}

		return (0);
	}
}
