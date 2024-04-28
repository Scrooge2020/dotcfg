# .bash_profile

# Get the aliases and functions
[ -f $HOME/.bashrc ] && . $HOME/.bashrc

# Customized Config
export EDITOR=/usr/bin/nvim
export PAGER=/usr/bin/less

export CM_SELECTIONS="clipboard"
export CM_MAX_CLIPS=10

export LESS=-R
export LESS_TERMCAP_mb=$'\e[1;31m'     # begin bold
export LESS_TERMCAP_md=$'\e[1;36m'     # begin blink
export LESS_TERMCAP_so=$'\e[01;44;37m' # begin reverse video
export LESS_TERMCAP_us=$'\e[01;37m'    # begin underline
export LESS_TERMCAP_me=$'\e[0m'        # reset bold/blink
export LESS_TERMCAP_se=$'\e[0m'        # reset reverse video
export LESS_TERMCAP_ue=$'\e[0m'        # reset underline
export GROFF_NO_SGR=1                  # for konsole and gnome-terminal

# Start X
if [ -z "${DISPLAY}" ] && [ "$(tty)" == "/dev/tty1" ]; then
        exec startx -- vt1 &> /dev/null
fi
