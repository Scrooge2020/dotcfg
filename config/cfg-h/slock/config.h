/* user and group to drop privileges to */
static const char *user  = "turnip";
static const char *group = "turnip";

static const char *colorname[NUMCOLS] = {
	[INIT]   = "#120a1a",    /* after initialization */
	[INPUT]  = "#2d1a40",   /* during input */
	[FAILED] = "#662a2a",   /* wrong password */
	[CAPS]   = "#482a66",   /* CapsLock on */
};

/* treat a cleared input like a wrong password (color) */
static const int failonclear = 0;

/* time in seconds before the monitor shuts down */
static const int monitortime = 10;
