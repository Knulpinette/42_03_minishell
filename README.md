
# Minishell
Write a simple version of a shell.
<br/>

## TO DO
* Figure out how we need to parse the commands => do all commands need to be executable (even non-built-in?), so do we need to figure out how to parse the options (and see if they are executable)?
* Display a prompt (loop GNL). Print to stderr? (>msh)
* Have a working history (cf [add_history function](https://linux.die.net/man/3/history))
* Get the PATH variable (cf [pipex](https://github.com/Knulpinette/Cursus42/blob/main/02-pipex/srcs/utils.c))
* No need to interpret \ or ; (unless required by the subject). Figure out when it is required by the subject lol
* Handle multiple pipes
* Figure out why & when we need / have an interactive mode and a non interactive mode.
* Do the built in functions. (echo (-n), cd (relative & absolute path), pwd, export, unset, env, exit)
* Figure out which is the ONE global variable we can use (environement?)
<br/>

## Parsing
Analyse the text and divide it into categories and sub-categories.
* Lexer. Tokenise characters and place them in box/categories
* Parser. Grammatically interprets the tokens
* Semantics. Validate and verify the meaning of the result given by the parser (that a given name IS a name (David) and not a name that doesn't exist (Philosopher), for example)

Among characters to tokenise : 
* | (pipe)
* >, >>, <, << (redirections)
* $ (environement variable)
* ', '' (quotes)
* alphanumerical (text) [to delimitate with whitespaces]

<br/>

## Useful Links

* [Bash Manual](https://www.gnu.org/savannah-checkouts/gnu/bash/manual/bash.html#What-is-Bash_003f)
* [A Guide to Parsing](https://tomassetti.me/guide-parsing-algorithms-terminology/)
* [Dimitri's and Gonçalo's Tuto](https://github.com/DimitriDaSilva/42_minishell/blob/master/README.md#1-extracting-information) (⚠️ careful they did the old minishell)
