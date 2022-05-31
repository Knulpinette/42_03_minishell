
# Cocoshell 🥥
Meet our simple version of a shell.

## 🍴 Parsing
Analyse the text and divide it into categories and sub-categories. 
We went with a linear parsing since we are only dealing with pipes and redirections as operators. The parsing would need to be more abstract if we were dealing with `&&` or `||`, for example.

**Special characters that will need to be handled:**
> `|` pipe <br>
> `<` `<<` `>` `>>` redirections <br>
> `$` environement variable <br>
> `'` `''` quotes <br>
> `alphanumerical` text / commands / flags <br>

### ⚠️ Quotes (`'` `''`) ⚠️
Quotes are handled from the beginning and all throughout the the process. A boolean like function allows to know if we are at the beginning, the end or in the middle of a quote and will allow the stage we're at to treat that information accordingly. 

### Step 0. Instructions (`|`)
We split the input line into an array** of instructions with pipes as the delimiter.

### Step 1. Translate (`$`)
Then we replace the environement variables (`$HOME`, `$CMD`, `$PWD`...) by they real value (`home/cocoshells`, `ls -l`, `home/cocoshells/minishell`...). We do this when we handle redirections and in the lexer separately because of a few exceptions in the `<<` redirection. <br>
**Careful**: if the environement variable is in between single quotes, it shouldn't be translated.

### Step 2. Redirections (`>` `<` `<<` `>>`)
The redirection operator type and the following argument are saved as redirections (in a dedicated struct). The instruction line is then rewritten without the redirections text.

### Step 3. Lexer (`tokenise`)
All words left are then separated into single elements (in little boxes let's say) using spaces as delimiters.

### Step 4. Parse (`grammar`)
The parsing stage gives the tokens their type : `command`, `flag` or `word` while handling a few exceptions and, more importantly, removing the closed quotes. Then it assigns those tokens to their rightful variable. 

### Step 5. Validation (`semantics`)
We validate and verify the meaning of the result given by the parser. 
<i>That a given name IS a name `David` and not a name that doesn't exist `Philosopher`.</i>

</br>

## 🏃‍♂️ Executor

While looping over each command, I start by opening a pipe, if needed.
In our command struct, we keep track of the file descriptor from which input will be read (fd_in) and the one on which the output will be written (fd_out).
So as I open the pipe, I update the command's fd_out to the pipe's writting end, and the next command's fd_in to the pipe's reading end.

The second step is to take care of redirections.
I make sure to close any file descriptor in use before opening another one.
In this way, no matter how many pipes nor how many redirections we have, the number of file descriptors in use never goes beyond 5.
As we go through each redirection, each file is opened (and created if it doesn't exist and we're dealing with an output redirection), and then closed when it's no longer needed.

We deal with here docs by creating a temporary file, where the user input is written until the delimiter is given.
What is the best strategy to create a temporary file?
There are two potential problems to take into consideration: if someone creates a file with the same name and in the same directory as the temporary file, things will go wrong; if the temporary file has always the same name, and a here doc is being processed in two different minishells launched simultaneously, something will go wrong.
To deal with this, I created the temporary file inside the /tmp folder (where users usually don't go) and named it after the tty where the minishell is being launched from.
Environment variables are expanded, unless the delimiter is in between quotes.

I shall write nice things about our executor. For now, here's a note on why I think valgrind doesn't like my cd: https://bugs.freedesktop.org/show_bug.cgi?id=112201

</br>

## 🌱 Built-in commands

</br>

## 🚨 Signals

</br>

## 🔗 Useful Links

* [Bash Manual](https://www.gnu.org/savannah-checkouts/gnu/bash/manual/bash.html#What-is-Bash_003f)
* [Dimitri's and Gonçalo's Tutorial](https://github.com/DimitriDaSilva/42_minishell/blob/master/README.md#1-extracting-information) (⚠️ careful they did the old minishell)
* [Minishell Notions](https://www.notion.so/Minishell-Materials-7bbd45a806e04395ab578ca3f805806c)
* [A Guide to Parsing](https://tomassetti.me/guide-parsing-algorithms-terminology/)
* [Bash parser](https://vorpaljs.github.io/bash-parser-playground/)
* [Shell Command Langage Details](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html#tag_18_01)
* [AST viewer](https://ast-viewer.datacamp.com/editor?code=echo%20alo%20%3E%20aqui.txt%20bla%20bla%20%3E%3E%20alo.txt%20test%20%7C%20wc%20%7C%20ls%20%3E%20aqui.txt&start=NA&grammar=shell)
* [Termcaps](https://github.com/Olbrien/42Lisboa-lvl_3_minishell/blob/main/extras/termcaps_history_explanation/termcaps.c)
* [Pipes, forks & dups](https://www.rozmichelle.com/pipes-forks-dups/)

<br/>

## 🐚 The Cocoshells
This project was made by [Knulpinette](https://github.com/Knulpinette) and [areivs](https://github.com/arieivs).

Happy coding! 🦕
