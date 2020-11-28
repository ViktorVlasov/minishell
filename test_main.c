#include "minishell.h"
#include <unistd.h>
#include <errno.h>
#include <stdio.h>

int main(int argc, char *argv[], char *envp[])
{   
    // ft_putstr_fd(envp[1], 1);
    // ft_putchar_fd('\n', 1);

    // ft_echo(argv);
    // ft_pwd();
    ft_env(envp);
}