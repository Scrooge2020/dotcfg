# .bashrc

# If not running interactively, don't do anything
[[ $- != *i* ]] && return

# Customized Config
alias ls='ls --color=auto'
alias grep='grep --color=auto'
alias egrep='grep -E --color=auto'
alias fgrep='grep -F --color=auto'
alias vim='nvim'
alias vi='nvim'

if [ ${EUID} -eq 0 ]; then
	PS1='\[\033[01;31m\]\u \[\033[01;37m\]> \[\033[00m\]'
else
	PS1='\[\033[01;33m\]\u \[\033[01;37m\]> \[\033[00m\]'
fi
