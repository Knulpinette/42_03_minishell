
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

I shall write nice things about our executor. For now, here's a note on why I think valgrind doesn't like my cd: https://bugs.freedesktop.org/show_bug.cgi?id=112201

## Useful Links

> **General links**
>> [Bash Manual](https://www.gnu.org/savannah-checkouts/gnu/bash/manual/bash.html#What-is-Bash_003f) <br>
>> [A Guide to Parsing](https://tomassetti.me/guide-parsing-algorithms-terminology/) <br>
>> [Dimitri's and Gonçalo's Tuto](https://github.com/DimitriDaSilva/42_minishell/blob/master/README.md#1-extracting-information) (⚠️ careful they did the old minishell)

> **Links from Maria**
>> [Minishell Notions](https://www.notion.so/Minishell-Materials-7bbd45a806e04395ab578ca3f805806c) <br>
>> [Bash parser](https://vorpaljs.github.io/bash-parser-playground/) <br>
>> [Shell Command Langage Details](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html#tag_18_01)

> **Links from Discord**
>> [AST viewer](https://ast-viewer.datacamp.com/editor?code=echo%20alo%20%3E%20aqui.txt%20bla%20bla%20%3E%3E%20alo.txt%20test%20%7C%20wc%20%7C%20ls%20%3E%20aqui.txt&start=NA&grammar=shell) <br>
>> [Termcaps](https://github.com/Olbrien/42Lisboa-lvl_3_minishell/blob/main/extras/termcaps_history_explanation/termcaps.c) <br>
>> [Pipes, forks & dups](https://www.rozmichelle.com/pipes-forks-dups/)

