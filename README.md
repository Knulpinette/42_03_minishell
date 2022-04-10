
# Minishell
Write a simple version of a shell.
<br/>

## TO DO
Ophélie
* Do the parsing (tokenise, interpret, validate)
* Qualify the tokens
* Put them in the right variable <br/>
Sara
* for your to do list

<br/>

## TO FIGURE OUT
* Figure out how we need to parse the commands => do all commands need to be executable (even non-built-in?), so do we need to figure out how to parse the options (and see if they are executable)?
* Have a working history (cf [add_history function](https://linux.die.net/man/3/history))
* Get the PATH variable (cf [pipex](https://github.com/Knulpinette/Cursus42/blob/main/02-pipex/srcs/utils.c))
* No need to interpret \ or ; (unless required by the subject).
* Handle multiple pipes
* Do the built in functions. (echo (-n), cd (relative & absolute path), pwd, export, unset, env, exit)
<br/>

## Parsing
Analyse the text and divide it into categories and sub-categories. We went with a linear parsing since we are only dealing with pipes and redirections as operators. (The parsing would need to be more abstract if we were dealing with && or ||, for example).
Special characters that will need to be handled: 
```
* | (pipe)
* <, <<, >, >> (redirections)
* $ (environement variable)
* ', '' (quotes)
* alphanumerical (text / commands / flags) [to delimitate with whitespaces]
```
* /!\ Quotes /!\
Quotes are handled from the beginning and all throughout the the process. A boolean like function allows to know if we are at the beginning, the end or in the middle of a quote and will allow the stage we're at to treat that information accordingly.
* Step 0. Instructions (pipes)
We split the input line into an array** of instructions with '|' as the delimiter.
* Step 1. Translate (environement variables)
Then we replace the environement variables ($HOME, $CMD, $PWD...) by they real value (home/cocoshells, ls -l, home/cocoshells/minishell...). <br>
<b>/!\ If the environement variable is in between single quotes, it shouldn't be translated. /!\</b>
* Step 2. Redirections ('>' '<' '<<' '>>')
The redirection operator type and the following argument are saved as redirections (in a dedicated struct). The instruction line is then rewritten without the redirections text.
* Step 3. Lexer (tokenise)
All words left are then separated into single elements (in little boxes let's say) using spaces as delimiters.
* Step 4. Parse (grammar)
The parsing stage gives the tokens their type : command, flag or word while handling a few exceptions and, more importantly, removing the closed quotes. Then it assigns those tokens to their rightful variable. 
* Step 5. Semantics (validation)
We validate and verify the meaning of the result given by the parser (that a given name IS a name (David) and not a name that doesn't exist (Philosopher).
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

