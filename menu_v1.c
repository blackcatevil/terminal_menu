#include <stdlib.h>
#include <stdio.h>
#include <termios.h>	//termios struct, tcgetattr(), tcsetattr()
#include <string.h>

void show_main_menu()
{
	printf("=========================================\n");
	printf("[0]: Exit.\n");
	printf("[1]: Option1.\n");
	printf("[2]: Option2.\n");
	printf("[3]: Option3.\n");
	printf("=========================================\n");
}

int main()
{
	char tmp[1];
	struct termios init_setting, new_setting;
	unsigned int op;

	tcgetattr(fileno(stdin), &init_setting);

	new_setting = init_setting;
	new_setting.c_lflag &= ~ICANON;
	new_setting.c_lflag &= ~ECHO;
	new_setting.c_cc[VTIME]=0;
	new_setting.c_cc[VMIN]=1;

	show_main_menu();
	while(1){

		tcsetattr(fileno(stdin), TCSAFLUSH, &new_setting);

		do{
			*tmp = getchar();
		}while(*tmp=='\n' || *tmp=='\r');

		tcsetattr(fileno(stdin), TCSANOW, &init_setting);

		op = atoi(tmp);
		switch(op)
		{
			case 0:
				return 0;
			case 1:
				break;
			case 2:
				break;
			case 3:
				break;
			default:
				printf("No such option.\n");
				break;
		}
		show_main_menu();
	}

	return 0;
}
