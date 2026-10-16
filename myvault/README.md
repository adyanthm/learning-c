# Intro

This project took me around 4 days to complete but it was worth it! I kept running into this issue where I had some random ideas which were good but I failed to note them down so I kept forgetting them. It was really annoying when I get ideas when I am busy with something else and I have a lack of ideas when I am free. Hence, I built this "vault" of ideas for my personal use.

# Features

1) Add and list ideas! (`add`, `list`)
2) Modifying existing ideas. (`edit`)
3) Deleting ideas (`del`) or (`delete`)
4) It's persistent. Uses sqlite to store your ideas even after you close the application. By default, it stores at `%APPDATA%` on windows and `$XDG_DATA_HOME` on linux which defaults to `~/.local/share` when unset.
5) It's lightweight, portable, and cross platform (Written in C!).
6) It's beautiful and clean to work with :)

# What is `ezsqlite.c` for?

I created this `ezsqlite.c` as something that can be used with any project easily to initialize the sqlite db, exec commands and close the db. If I ever wanted to work with another project that uses sqlite, I could always just copy this file along with its header into the new project and use it easily :)

Feel free to use it in some of your projects too!

# How did you make it colourful?

I used ANSI terminal color sequences conveniently defined as macros in `utils.h`

```C
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define RESET   "\x1b[0m"
#define STRIKETHROUGH "\x1b[9m"
```

You can use them in your projects too if you want! Just copy paste this definitions into a header or your C file, then just use them along with strings like

```C
printf(BLUE "I am blue!" RESET)
```

**NOTE:** The `RESET` is used for resetting terminal to default text formatting. If you dont reset, even after you quit your program, the terminal is going to be blue. Of course, you don't want that do you?

# How to use it?

First, compile by linking all these together.
> I used gcc, use whatever C compiler you want.

```bash
gcc .\main.c .\sqlite3.c .\ezsqlite.c .\utils.c -o todo
```

Next run it and you can use these commands! (This run command `todo.exe` is for windows but the commands themselves are same across all OS. Just make sure to use the right run command for your OS). And, the colours are way better in the actual application

```
$> todo.exe
>>> add test

=> Added task: test

>>> list

01. [ ] test

>>> edit 1 edited test!

=> Updated task: 1. edited test!

>>> list

01. [ ] edited test!

>>> done 1

=> Finished task: 1

>>> list

01. [x] edited test!

>>> del 1

=> Deleted task: 1

>>> list

### No task visible here. This is a comment btw not shown in the actual program.

>>> quit

=> Quitting Program.

### program terminates here.
```

# Note

Since its designed to run on your own PC locally, I did **NOT** handle sql injection, syntax breaking stuff and all those. Why do you want hack yourselves lol?

And yeah dont follow these "practices" when pushing production code especially when handling untrusted code or exposing your db through a network!
