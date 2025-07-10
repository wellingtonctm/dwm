/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappih    = 5;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 5;       /* vert inner gap between windows */
static const unsigned int gappoh    = 5;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 5;       /* vert outer gap between windows and screen edge */
static const int smartgaps          = 1;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = {
	"JetBrainsMono Nerd Font:size=11:antialias=true:autohint=true",
	"Noto Sans CJK KR:size=10:antialias=true:autohint=true"
};
static const char col_gray1[]       = "#000000";
static const char col_gray2[]       = "#000000";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const unsigned int baralpha = 0xcc;
static const unsigned int borderalpha = OPAQUE;
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};
static const unsigned int alphas[][3]      = {
    /*               fg      bg        border*/
    [SchemeNorm] = { OPAQUE, baralpha, borderalpha },
	[SchemeSel]  = { OPAQUE, baralpha, OPAQUE },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#define FORCE_VSPLIT 0  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
	/* symbol   arrange function */
	{ "[T]",    tile },    /* first entry is default */
	{ "[M]",    monocle },
	{ "[S]",    spiral },
	{ "[A]",    dwindle },
	{ "[D]",    deck },
	{ "[B]",    bstack },
	{ "[H]",    bstackhoriz },
	{ "[F]",    NULL },    /* no layout function means floating behavior */
	{ NULL,     NULL },
};

/* key definitions */
#include <X11/XF86keysym.h>
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[] = { "st", NULL };
static const char *browsercmd[] = { "brave-browser-stable", NULL };
static const char *volumecentercmd[] = { "pavucontrol-qt", NULL };
static const char *screenshotcmd[] = { "flameshot", "gui", NULL };
static const char *lockscreencmd[] = { "slock", NULL };


static const Key keys[] = {
	/* modifier                     key                       function        argument */
	{ MODKEY,                       XK_p,                     spawn,             {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return,                spawn,             {.v = termcmd } },
	{ MODKEY,                       XK_n,                     spawn,             {.v = browsercmd } },
	{ MODKEY|ShiftMask,             XK_f,                     fullscreen,        {0} },
	{ MODKEY|ShiftMask,             XK_p,                     spawn,             {.v = volumecentercmd } },
	{ MODKEY|ShiftMask,             XK_l,                     spawn,             {.v = lockscreencmd } },
	{ MODKEY,                       XK_b,                     togglebar,         {0} },
	{ MODKEY,                       XK_j,                     focusstack,        {.i = +1 } },
	{ MODKEY,                       XK_k,                     focusstack,        {.i = -1 } },
	{ MODKEY,                       XK_s,                     togglesticky,      {0} },
	// { MODKEY,                       XK_i,                     incnmaster,     {.i = +1 } },
	// { MODKEY,                       XK_d,                     incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,                     setmfact,          {.f = -0.05} },
	{ MODKEY,                       XK_l,                     setmfact,          {.f = +0.05} },
	{ MODKEY,                       XK_Return,                zoom,              {0} },
	{ MODKEY,                       XK_Tab,                   view,              {0} },
	{ MODKEY|ShiftMask,             XK_c,                     killclient,        {0} },
	{ MODKEY,                       XK_t,                     setlayout,         {.v = &layouts[0]} },
	{ MODKEY,                       XK_m,                     setlayout,         {.v = &layouts[1]} },
	{ MODKEY,                       XK_r,                     setlayout,         {.v = &layouts[2]} },
	{ MODKEY|ShiftMask,             XK_r,                     setlayout,         {.v = &layouts[3]} },
	{ MODKEY|ShiftMask,             XK_d,                     setlayout,         {.v = &layouts[4]} },
	{ MODKEY,                       XK_u,                     setlayout,         {.v = &layouts[5]} },
	{ MODKEY,                       XK_o,                     setlayout,         {.v = &layouts[6]} },
	{ MODKEY,                       XK_f,                     setlayout,         {.v = &layouts[7]} },
	{ MODKEY,                       XK_space,                 setlayout,         {0} },
	{ MODKEY|ShiftMask,             XK_space,                 togglefloating,    {0} },
	{ MODKEY,                       XK_0,                     view,              {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,                     tag,               {.ui = ~0 } },
	{ MODKEY,                       XK_comma,                 focusmon,          {.i = -1 } },
	{ MODKEY,                       XK_period,                focusmon,          {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,                 tagmon,            {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period,                tagmon,            {.i = +1 } },
	{ MODKEY,                       XK_z,                     incrgaps,          {.i = +3 } },
	{ MODKEY,                       XK_x,                     incrgaps,          {.i = -3 } },
	{ MODKEY,                       XK_a,                     togglegaps,        {0} },
	{ MODKEY|ShiftMask,             XK_a,                     defaultgaps,       {0} },
	{ MODKEY,                       XK_minus,                 scratchpad_show,   {0} },
	{ MODKEY|ShiftMask,             XK_minus,                 scratchpad_hide,   {0} },
	{ MODKEY,                       XK_equal,                 scratchpad_remove, {0} },
	{ MODKEY,                       XK_y,                     spawn,             SHCMD("~/suckless/custom/plugins/dmenu/yt-cli.sh") },
	{ MODKEY|ShiftMask,             XK_b,                     spawn,             SHCMD("~/suckless/custom/plugins/dmenu/bluetooth.sh") },
	{ 0,                            XK_Print,                 spawn,             {.v = screenshotcmd } },
	{ 0,                            XF86XK_AudioRaiseVolume,  spawn,             SHCMD("volume-plugin -i 5") },
	{ 0,                            XF86XK_AudioLowerVolume,  spawn,             SHCMD("volume-plugin -d 5") },
	{ 0,                            XF86XK_AudioMute,         spawn,             SHCMD("volume-plugin -t") },
	{ 0,                            XF86XK_AudioMicMute,      spawn,             SHCMD("volume-plugin -m") },
	{ 0,                            XF86XK_MonBrightnessUp,   spawn,             SHCMD("brightnessctl set +5%") },
	{ 0,                            XF86XK_MonBrightnessDown, spawn,             SHCMD("brightnessctl set 5%-") },
	{ 0,                            XF86XK_AudioPlay,         spawn,             SHCMD("yt-cli --toggle") },
	{ 0,                            XF86XK_AudioPause,        spawn,             SHCMD("yt-cli --toggle") },
	{ 0,                            XF86XK_AudioNext,         spawn,             SHCMD("yt-cli --next") },
	{ 0,                            XF86XK_AudioPrev,         spawn,             SHCMD("yt-cli --prev") },
	{ 0,                            XF86XK_AudioStop,         spawn,             SHCMD("yt-cli --kill") },
	TAGKEYS(                        XK_1,                                        0)
	TAGKEYS(                        XK_2,                                        1)
	TAGKEYS(                        XK_3,                                        2)
	TAGKEYS(                        XK_4,                                        3)
	TAGKEYS(                        XK_5,                                        4)
	TAGKEYS(                        XK_6,                                        5)
	TAGKEYS(                        XK_7,                                        6)
	TAGKEYS(                        XK_8,                                        7)
	TAGKEYS(                        XK_9,                                        8)
	{ MODKEY|ShiftMask,             XK_q,                     quit,              {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
