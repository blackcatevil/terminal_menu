#include <stdlib.h>
#include <stdio.h>
#include <termios.h>	//termios struct, tcgetattr(), tcsetattr()
#include <string.h>

#define ARRAY_SIZE(x)  (sizeof(x) / sizeof((x)[0]))

int func1(int x, int y)
{
    printf("%d+%d = %d\n", x, y, x+y);

    return 0;
}

int func2(int x, int y)
{
    printf("%d-%d = %d\n", x, y, x-y);

    return 0;
}

int func3(int x, int y)
{
    printf("%d*%d = %d\n", x, y, x*y);

    return 0;
}

struct option_attr{
    char* id;
    char opt;
    char *title;
    int (*func)(int arg1, int arg2);
};

struct option_attr menu[] = {
    {
        .id = "0",
        .opt = '0',
        .title = "Exit.",
        .func = NULL,
    },
    {
        .id = "1",
        .opt = '1',
        .title = "function #1",
        .func = &func1,
    },
    {
        .id = "a",
        .opt = 'a',
        .title = "function #2",
        .func = &func2,
    },
    {
        .id = "^U",
        .opt = 0x15,
        .title = "function #3",
        .func = &func3,
    },
};

int main()
{
	char tmp[1];
	struct termios init_setting, new_setting;
	unsigned int op, i;

	tcgetattr(fileno(stdin), &init_setting);

	new_setting = init_setting;
	new_setting.c_lflag &= ~ICANON;
	new_setting.c_lflag &= ~ECHO;
	new_setting.c_cc[VTIME]=0;
	new_setting.c_cc[VMIN]=1;

	while(1){

        for(i = 0; i < ARRAY_SIZE(menu); i++){
            printf("[%s]: %s\n", menu[i].id, menu[i].title);
        }

        tcsetattr(fileno(stdin), TCSAFLUSH, &new_setting);

        do{
            *tmp = getchar();
        }while(*tmp=='\n' || *tmp=='\r');

        tcsetattr(fileno(stdin), TCSANOW, &init_setting);

        for(i = 0; i < ARRAY_SIZE(menu); i++){
            if(*tmp == menu[i].opt){
                if(menu[i].func == NULL)
                    return 0;
                else
                    menu[i].func(3, 2);
            }
        }
    }
	return 0;
}
