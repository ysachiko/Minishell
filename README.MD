<h1 align="center">Minishell</h1>

<h3>This project was about creating a simple shell. <br>
Like your own little <b>bash.<br></h3>

------------

<h2>FEATURES</h2>

<h3>Environment variables </h3>

    Environment variables ($ followed by a sequence of characters) which expand to their values.

<h3>Builtins</h3>

    Minishell implement the following builtins:

        ◦ echo with option -n
        ◦ cd with only a relative or absolute path
        ◦ pwd with no options
        ◦ export with no options
        ◦ unset with no options
        ◦ env with no options or arguments
        ◦ exit with no options

<h3>Pipes:</h3>

    ls | sort 

<h3>Redirections:</h3>

    ◦ < redirect input.

    ◦ > redirect output.

    ◦ << be given a delimiter, then read the input until a line containing the
    delimiter is seen.

    ◦ >> redirect output in append mode

<h3>Signals</h3>

    ctrl-C, ctrl-D and ctrl-\ which behave like in bash.

    • In interactive mode:
        ◦ ctrl-C displays a new prompt on a new line.
        ◦ ctrl-D exits the shell.
        ◦ ctrl-\ does nothing.

<h3> History:</h3>

    Have a working history.

------------

<h2>INSTALLATION</h2>

------------

<h3>1. Install brew and readline(for MacOS)</h3>

    curl -fsSL https://rawgit.com/kube/42homebrew/master/install.sh | zsh

    brew install readline

<h3>2. Replace username in Makefile</h3>

    Replace USER with your username

    RDLN = -L /Users/USER/.brew/Cellar/readline/8.1.2/lib -I /Users/USER/.brew/Cellar/readline/8.1.2/include/ -lreadline

<h2>COMPILATION</h2>

------------

<h3>Use "make" to compile minishell</h3>

    make

<h3>Use "make re" to compile minishell</h3>

    make re

<h3>Use "make fclean" to delete obj files</h3>

    make fclean

