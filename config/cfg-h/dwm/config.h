/* See LICENSE file for copyright and license details. */

#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int borderpx  = 4;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int rmaster            = 1;        /* 1 means master-area is initially on the right */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 0;        /* 0 means bottom bar */
static const char *fonts[]          = { "Source Code Pro:size=11", "NotoColorEmoji:size=11" };
static const char col_gray1[]       = "#333333";
static const char col_gray2[]       = "#000000";
static const char col_gray3[]       = "#999999";
static const char col_gray4[]       = "#FFFFFF";
static const char col_theme[]       = "#9292f7";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_gray2, col_theme },
};

/* tagging */
static const char *tags[] = { "A", "R", "C", "H", "M", "C" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class              instance           title                     tags mask  isfloating  monitor */
	{ "Galculator",       NULL,              NULL,                     0,         1,          -1 },
	{ "Xarchiver",        NULL,              NULL,                     0,         1,          -1 },
	{ "Gimp",            "gimp",            "GIMP Startup",            0,         1,          -1 },
	{ "Libfm-pref-apps", "libfm-pref-apps", "Preferred Applications",  0,         1,          -1 },
	{ "Lxappearance",    "lxappearance",    "Customize Look and Feel", 0,         1,          -1 },
	{ "firefox",         "Browser",         "About Mozilla Firefox",   0,         1,          -1 },
	{ "Pcmanfm",         "pcmanfm",         "Execute File",            0,         1,          -1 }
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[T]",      tile },    /* first entry is default */
	{ "[F]",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define ALTKEY Mod1Mask
#define WINKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ KeyPress,   WINKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ KeyPress,   WINKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ KeyPress,   WINKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ KeyPress,   WINKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *webbcmd[]  = { "firefox", NULL };
static const char *webbpvt[]  = { "firefox","--private-window", NULL };
static const char *filecmd[]  = { "pcmanfm", NULL };
static const char *taskcmd[]  = { "st", "-e", "htop", NULL };
static const char *calccmd[]  = { "galculator", NULL };
static const char *clipcmd[]  = { "clipmenu", NULL };
static const char *lockcmd[]  = { "slock", NULL };
static const char *infocmd[]  = { "st", "-e", "sysinfo.sh", NULL };

static Key keys[] = {
	/* type       modifier                           key   function        argument */
	{ KeyPress,   WINKEY,                           XK_r,  spawn,          {.v = dmenucmd } },
	{ KeyPress,   WINKEY,                           XK_t,  spawn,          {.v = termcmd } },
	{ KeyPress,   ControlMask|ALTKEY,               XK_t,  spawn,          {.v = termcmd } },
	{ KeyPress,   WINKEY,                           XK_w,  spawn,          {.v = webbpvt } },
	{ KeyPress,   ControlMask|ALTKEY,               XK_w,  spawn,          {.v = webbcmd } },
	{ KeyRelease, 0,                            XK_Print,  spawn,          SHCMD("scrot ~/Pictures/Screenshots/ss-%Y-%m-%d.png") },
	{ KeyPress,   ControlMask,                  XK_Print,  spawn,          SHCMD("scrot -u ~/Pictures/Screenshots/ss-%Y-%m-%d.png") },
	{ KeyPress,   ControlMask|ShiftMask,        XK_Print,  spawn,          SHCMD("scrot -s -f ~/Pictures/Screenshots/ss-%Y-%m-%d.png") },
	{ KeyPress,   WINKEY,                           XK_e,  spawn,          {.v = filecmd } },
	{ KeyPress,   ControlMask|ShiftMask,       XK_Escape,  spawn,          {.v = taskcmd } },
	{ KeyPress,   WINKEY,                           XK_c,  spawn,          {.v = calccmd } },
	{ KeyPress,   0,                   XF86XK_Calculator,  spawn,          {.v = calccmd } },
	{ KeyPress,   WINKEY,                           XK_v,  spawn,          {.v = clipcmd } },
//	{ KeyRelease, 0,                        XK_Caps_Lock,  spawn,          SHCMD("dsess.sh") },
//	{ KeyRelease, 0,                         XK_Num_Lock,  spawn,          SHCMD("dsess.sh") },
	{ KeyPress,   0,             XF86XK_AudioLowerVolume,  spawn,          SHCMD("amixer -q sset Master 5%- && dsess.sh") },
	{ KeyPress,   0,             XF86XK_AudioRaiseVolume,  spawn,          SHCMD("amixer -q sset Master 5%+ && dsess.sh") },
	{ KeyPress,   0,                    XF86XK_AudioMute,  spawn,          SHCMD("amixer -q sset Master toggle && dsess.sh") },
	{ KeyPress,   WINKEY,                       XK_comma,  spawn,          SHCMD("amixer -q sset Master 5%- && dsess.sh") },
	{ KeyPress,   WINKEY,                      XK_period,  spawn,          SHCMD("amixer -q sset Master 5%+ && dsess.sh") },
	{ KeyPress,   WINKEY,                           XK_m,  spawn,          SHCMD("amixer -q sset Master toggle && dsess.sh") },
	{ KeyPress,   WINKEY,                       XK_grave,  spawn,          SHCMD("emojiKeys.sh") },
//	{ KeyPress,   0,              XF86XK_MonBrightnessUp,  spawn,          SHCMD("brightnessctl -q s +5%") },
//	{ KeyPress,   0,            XF86XK_MonBrightnessDown,  spawn,          SHCMD("brightnessctl -q s 5%-") },
	{ KeyPress,   0,                  XF86XK_ScreenSaver,  spawn,          {.v = lockcmd } },
	{ KeyPress,   WINKEY,                           XK_l,  spawn,          {.v = lockcmd } },
	{ KeyPress,   ALTKEY,                          XK_F5,  spawn,          SHCMD("dunstctl close") },
	{ KeyPress,   WINKEY,                           XK_i,  spawn,          {.v = infocmd } },
	{ KeyPress,   ALTKEY,                      XK_Return,  togglebar,      {0} },
	{ KeyPress,   ALTKEY,                         XK_Tab,  focusstack,     {.i = +1 } },
	{ KeyPress,   ALTKEY|ShiftMask,               XK_Tab,  focusstack,     {.i = -1 } },
	{ KeyPress,   WINKEY,                       XK_equal,  incnmaster,     {.i = +1 } },
	{ KeyPress,   WINKEY,                       XK_minus,  incnmaster,     {.i = -1 } },
	{ KeyPress,   WINKEY,                        XK_Left,  setmfact,       {.f = -0.05} },
	{ KeyPress,   WINKEY,                       XK_Right,  setmfact,       {.f = +0.05} },
	{ KeyPress,   WINKEY,                          XK_Up,  zoom,           {0} },
	{ KeyPress,   WINKEY,                         XK_Tab,  view,           {0} },
	{ KeyPress,   ALTKEY,                          XK_F4,  killclient,     {0} },
	{ KeyPress,   ALTKEY,                          XK_F1,  setlayout,      {.v = &layouts[0]} },
	{ KeyPress,   ALTKEY,                          XK_F3,  setlayout,      {.v = &layouts[1]} },
	{ KeyPress,   ALTKEY,                          XK_F2,  setlayout,      {.v = &layouts[2]} },
//	{ KeyPress,   WINKEY,                       XK_space,  setlayout,      {0} },
	{ KeyPress,   ALTKEY|ShiftMask,                XK_F3,  togglefloating, {0} },
	{ KeyPress,   ALTKEY,                          XK_F6,  togglermaster,  {0} },
	{ KeyPress,   WINKEY,                           XK_0,  view,           {.ui = ~0 } },
	{ KeyPress,   WINKEY|ShiftMask,                 XK_0,  tag,            {.ui = ~0 } },
	{ KeyPress,   ALTKEY,                          XK_F9,  focusmon,       {.i = -1 } },
	{ KeyPress,   ALTKEY,                         XK_F10,  focusmon,       {.i = +1 } },
	{ KeyPress,   ALTKEY|ShiftMask,                XK_F9,  tagmon,         {.i = -1 } },
	{ KeyPress,   ALTKEY|ShiftMask,               XK_F10,  tagmon,         {.i = +1 } },
	{ KeyPress,   ALTKEY|ShiftMask,                XK_F4,  quit,           {0} },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask        button          function        argument */
	{ ClkLtSymbol,          0,                Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,                Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,                Button2,        zoom,           {0} },
	{ ClkStatusText,        0,                Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         WINKEY,           Button1,        movemouse,      {0} },
	{ ClkClientWin,         WINKEY,           Button2,        togglefloating, {0} },
	{ ClkClientWin,         WINKEY|ShiftMask, Button1,        resizemouse,    {0} },
	{ ClkTagBar,            0,                Button1,        view,           {0} },
	{ ClkTagBar,            0,                Button3,        toggleview,     {0} },
	{ ClkTagBar,            WINKEY,           Button1,        tag,            {0} },
	{ ClkTagBar,            WINKEY,           Button3,        toggletag,      {0} },
};

