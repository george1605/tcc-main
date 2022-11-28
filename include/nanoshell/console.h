#define DefaultConsoleColor 0x1F

enum ConsoleType {
	CONSOLE_TYPE_NONE, // uninitialized
	CONSOLE_TYPE_TEXT, // always full screen
	CONSOLE_TYPE_FRAMEBUFFER, // can either be the entire screen or just a portion of it. TODO
	CONSOLE_TYPE_SERIAL, // just plain old serial
	CONSOLE_TYPE_E9HACK, // Port E9 hack - qemu and bochs support this.
	CONSOLE_TYPE_WINDOW,
};

#define KB_BUF_SIZE 128
