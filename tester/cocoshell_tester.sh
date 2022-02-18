#! /bin/bash

export WHITE="\033[0;37m"
export BLACK="\033[0;30m"
export RED="\033[0;31m"
export YELLOW="\033[0;33m"
export BLUE="\033[0;34m"
export GREEN="\033[0;32m"

export prog_pathname="./minishell"
export tester_filepath="tester"
export tests_path="./tester/tests"

bash ${tester_filepath}/tester_loop.sh