
# Minishell
Write a simple version of a shell.
<br/>

## TO DO
21/02 
<br/>
* Figure out the Makefile issue, set up libft // OPHELIE
* Get the (user) input // SARA 
27/02
<br/>
* Do the parsing (tokenise, interpret, validate) // OPHELIE, SARA

<br/>

## TO FIGURE OUT
* Figure out how we need to parse the commands => do all commands need to be executable (even non-built-in?), so do we need to figure out how to parse the options (and see if they are executable)?
* Display a prompt (loop GNL). Print to stderr? (>msh)
* Have a working history (cf [add_history function](https://linux.die.net/man/3/history))
* Get the PATH variable (cf [pipex](https://github.com/Knulpinette/Cursus42/blob/main/02-pipex/srcs/utils.c))
* No need to interpret \ or ; (unless required by the subject).
* Handle multiple pipes
* Do the built in functions. (echo (-n), cd (relative & absolute path), pwd, export, unset, env, exit)
* Figure out which is the ONE global variable we can use (environement?)
<br/>

## Parsing
Analyse the text and divide it into categories and sub-categories.
* Lexer. Tokenise characters and place them in box/categories (command (+ flags), text, operators (pipe, env variable, redirections...))
* Parser. Grammatically interprets the tokens
* Semantics. Validate and verify the meaning of the result given by the parser (that a given name IS a name (David) and not a name that doesn't exist (Philosopher) // For example => check the flags ! (be careful with that. Most time will show error but in cases like "echo", will print as text))

Among characters to tokenise : 
* | (pipe)
* <, <<, >, >> (redirections)
* $ (environement variable)
* ', '' (quotes)
* alphanumerical (text / commands / flags) [to delimitate with whitespaces]

<br/>

## Interactive / Non-interactive mode
* Interactive mode accepts input typed from the keyboard.
* Non-interactive mode will execute commands read from a file.
<br/>

## Useful Links

* [Bash Manual](https://www.gnu.org/savannah-checkouts/gnu/bash/manual/bash.html#What-is-Bash_003f)
* [A Guide to Parsing](https://tomassetti.me/guide-parsing-algorithms-terminology/)
* [Dimitri's and Gonçalo's Tuto](https://github.com/DimitriDaSilva/42_minishell/blob/master/README.md#1-extracting-information) (⚠️ careful they did the old minishell)
<br/>

## Links from Maria
* [Minishell Notions](https://www.notion.so/Minishell-Materials-7bbd45a806e04395ab578ca3f805806c)
* [Bash parser](https://vorpaljs.github.io/bash-parser-playground/)
* [Shell Command Langage Details](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html#tag_18_01)

<br/>

## Links from Discord
* [AST viewer](https://ast-viewer.datacamp.com/editor?code=echo%20alo%20%3E%20aqui.txt%20bla%20bla%20%3E%3E%20alo.txt%20test%20%7C%20wc%20%7C%20ls%20%3E%20aqui.txt&start=NA&grammar=shell)
* [Termcaps](https://github.com/Olbrien/42Lisboa-lvl_3_minishell/blob/main/extras/termcaps_history_explanation/termcaps.c)
* [Pipes, forks & dups](https://www.rozmichelle.com/pipes-forks-dups/)

