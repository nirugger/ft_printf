*This project has been created as part of the 42 curriculum by nirugger.*

# ft_printf

## Description

`ft_printf` is a static library (`libftprintf.a`) that provides a re-implementation of
the C standard library function `printf()`.

The function has the following prototype:

```c
int	ft_printf(const char *format, ...);
```

It reads a format string, replaces every conversion specification it finds with the
corresponding variadic argument, writes the result on the standard output and returns
the number of characters printed.

The goal of the project is to work with **variadic functions** (`stdarg.h`) and to
design code that is structured and extensible enough to support a growing set of
conversions and flags without rewriting the parser every time a new case appears.

### Supported conversions

| Specifier | Meaning |
| --------- | ------- |
| `%c` | a single character |
| `%s` | a null-terminated string (`(null)` when the pointer is `NULL`) |
| `%p` | a `void *` pointer in hexadecimal, prefixed with `0x` (`(nil)` when `NULL`) |
| `%d` | a signed decimal integer |
| `%i` | a signed decimal integer |
| `%u` | an unsigned decimal integer |
| `%x` | an unsigned integer in lowercase hexadecimal |
| `%X` | an unsigned integer in uppercase hexadecimal |
| `%%` | a literal percent sign |

### Supported flags

The bonus flags are handled as well, in any combination:

| Flag | Effect |
| ---- | ------ |
| `-` | left-justify the conversion inside the field |
| `0` | pad the field with zeroes instead of spaces |
| `.` | precision: minimum number of digits, or maximum number of characters for `%s` |
| `#` | prefix `%x` / `%X` with `0x` / `0X` (ignored when the value is `0`) |
| ` ` | print a space before a non-negative signed number |
| `+` | print a sign before every signed number |

A minimum field width can be given for every conversion, e.g. `%-10.5d`.

If the sequence following a `%` is not a valid conversion specification, the `%` is
printed literally and parsing resumes from the next character.

## Instructions

### Requirements

* a Unix-like system (the library uses `write(2)` from `<unistd.h>`)
* `cc` and `make`

### Compilation

From the root of the repository:

```sh
make        # builds libftprintf.a
make clean  # removes the library
make fclean # removes the library and the object files
make re     # fclean + all
```

The sources are compiled with `-Wall -Wextra -Werror` and the archive is created with
`ar`.

### Usage

Include the header and link against the archive:

```c
#include "ft_printf.h"

int	main(void)
{
	int	count;

	count = ft_printf("%-10s|%+05d|%#x|%p\n", "hello", 42, 255, &count);
	ft_printf("%d characters printed\n", count);
	return (0);
}
```

```sh
cc main.c -I includes -L . -lftprintf -o test
./test
```

Output:

```
hello     |+0042|0xff|0x7ffee3b4c8ac
38 characters printed
```

### Project structure

```
.
├── includes/
│   └── ft_printf.h      # public prototype, structs, flag masks, base strings
├── srcs/
│   ├── ft_printf.c      # entry point: init, main loop, final flush
│   ├── buffer.c         # output buffer, base conversion, per-character dispatch
│   ├── flag_handler.c   # parsing of flags, width and precision
│   ├── type_handler.c   # conversion identification and routing to the formatters
│   ├── format_char.c    # %c
│   ├── format_string.c  # %s
│   ├── format_digits.c  # %d, %i
│   ├── format_unsigned.c# %u
│   ├── format_hex.c     # %x, %X
│   ├── format_pointer.c # %p
│   ├── checks.c         # character classification helpers
│   ├── utils.c          # length and power computation
│   └── libft.c          # ft_strlen, ft_memset, ft_min, ft_max, ft_basic_atoi
├── Makefile
└── README.md
```

## Algorithm and data structures

### General flow

`ft_printf()` initialises two structures on the stack (both zeroed with `ft_memset`),
opens the variadic list and then loops until the end of the format string:

```
while (format[flags.i])
	format_and_fill(format, &buffer, &flags, &args);
put_buffer(&buffer);
return (buffer.printed);
```

`format_and_fill()` is the only place that advances the cursor. It has three cases:

1. the current character is not `%` → it is copied as-is and the cursor moves forward;
2. the current character is `%` and `fill_flags()` recognises a complete conversion
   specification → `type_router()` consumes one variadic argument and calls the right
   formatter, and the cursor is placed after the conversion character;
3. the current character is `%` but no valid specification follows → the `%` itself is
   copied and the cursor moves forward by one.

After every `%` the specification state is cleared by `reset_flags()`, so each
conversion is parsed from a clean state while the cursor is preserved.

The parser is a **single left-to-right pass with no backtracking and no allocation**:
the format string is never copied, and nothing is allocated on the heap, so there is
nothing to free and no failure path to handle.

### `t_flags` — parsing state and conversion specification

```c
struct s_flags
{
	char	flags;      /* bitmask of the active flags */
	int		width;      /* minimum field width */
	int		precision;  /* precision, meaningful only if F_PREC is set */
	t_types	type;       /* conversion identified by assign_type() */
	size_t	i;          /* cursor inside the format string */
};
```

Keeping the cursor `i` inside the same structure as the specification means that a
single pointer is passed around: the parser, the router and `ft_printf()` itself all
share one state object, which keeps every prototype short (a requirement of the Norm)
and makes the position in the format string unambiguous.

The flags themselves are stored as a **bitmask** rather than as one boolean field per
flag:

```c
# define F_MINUS 1
# define F_ZERO  1 << 1
# define F_PREC  1 << 2
# define F_HASH  1 << 3
# define F_SPACE 1 << 4
# define F_PLUS  1 << 5
```

Six flags fit in a single `char`. Setting a flag is `flags |= F_X`, testing it is
`flags & F_X`, and testing a *combination* costs nothing extra — which matters here
because the behaviour of `printf` depends heavily on combinations (`0` is ignored when
`-` is present, `0` is ignored on integers when a precision is given, and so on).
Adding a new flag later only requires one more bit and one more branch in
`assign_flag()`, without touching the structure or any prototype.

The conversion is stored as an `enum` (`CHR`, `STR`, `PTR`, `DIG`, `INT`, `US`, `L_X`,
`U_X`, `PERC`) instead of the raw character. The comparison in `type_router()` is then
made against symbolic names, and `%x` and `%X` — which share the same code path but
differ in the digit alphabet and in the `#` prefix — can be distinguished with a single
test.

### `t_buffer` — output accumulation

```c
struct s_buffer
{
	char	buff[FT_BUFSIZ];
	int	now;      /* number of bytes currently held */
	int	printed;  /* total number of bytes already written */
};
```

Every formatter writes through `fill_buffer()`, which appends bytes to `buff` and calls
`write(1, ...)` only when the buffer is full; `put_buffer()` flushes whatever is left at
the very end. Emitting one `write()` per character would mean one system call per
character — for a call such as `%-40d` that is dozens of syscalls where one is enough.

`printed` is incremented at every flush, so the return value of `ft_printf()` is a
simple by-product of the output path instead of a count that each formatter would have
to compute and propagate correctly. This removes an entire class of bugs, since a
formatter cannot report a length that differs from what it actually printed.

`FT_BUFSIZ` is defined inside an `#ifndef` guard, so the size can be overridden at
compile time (`cc -D FT_BUFSIZ=4096 ...`). A deliberately small default value is useful
during development: it forces the flush path to be exercised in the middle of a
conversion rather than only at the end.

### Number conversion: one routine, several bases

Bases are described by the string of their digits:

```c
# define BASE_TEN    "0123456789"
# define BASE_LO_HEX "0123456789abcdef"
# define BASE_UP_HEX "0123456789ABCDEF"
```

`int_copy_base()` and `ul_copy_base()` take that string as a parameter, so decimal,
lowercase hexadecimal and uppercase hexadecimal all go through the same code; the base
*value* is simply `ft_strlen(base)` and the digit *character* is `base[n / power %
base_len]`. Supporting another base would mean adding a string, not a function.

Digits must be printed most-significant first, but they are naturally produced
least-significant first by repeated division. Two classic solutions are recursion and
an intermediate buffer that gets reversed. This implementation uses a third one:
`get_power_long()` / `get_power_unsigned()` first compute the largest power of the base
that is still smaller than or equal to the number, and the conversion then walks *down*
from that power:

```c
while (power > 0)
{
	c = base[n / power % base_len];
	fill_buffer(b, &c, 1);
	power /= base_len;
}
```

This keeps the conversion iterative and constant in memory: no recursion depth, no
temporary array, and no reversal step.

The signed variant takes a `long` rather than an `int` on purpose. `INT_MIN` has no
positive counterpart in `int`, so negating it would be undefined behaviour; widening to
`long` first makes `n *= -1` safe for every possible `int` input, and the sign itself is
printed separately by the formatter.

### Padding and precision

Each formatter follows the same three-step shape:

1. compute the length the conversion *would* have, including the sign or the `0x`
   prefix and taking the precision into account (`get_id_format_len()`,
   `get_us_format_len()`, `get_hex_format_len()`);
2. emit the payload before the padding if `-` is set, or after it otherwise;
3. fill the remaining width one character at a time, letting `fill_width()` decide
   between `' '` and `'0'`.

Centralising that decision in `fill_width()` keeps the interaction between `0`,
`-` and `.` in a single place: `0` is dropped when `-` is set, and a precision on an
integer conversion makes the field padding fall back to spaces, since the zeroes belong
to the number and not to the field.

Some cases of the reference `printf` are handled explicitly because they do not follow
from the general rules:

* `%.0d` with a value of `0` prints nothing at all, so the computed length is reduced by
  one and the digit emission is skipped;
* `%#x` with a value of `0` has no `0x` prefix, so the conversion is delegated to the
  unsigned formatter;
* `%s` with a `NULL` pointer prints `(null)`, unless a precision smaller than 6 truncates
  it — including down to an empty string;
* `%p` ignores precision entirely and prints `(nil)` for a null pointer.

## Resources

* `man 3 printf` — the reference behaviour this project is compared against
* `man 3 stdarg` — `va_start`, `va_arg`, `va_copy`, `va_end`
* `man 2 write` — the only output primitive used
* `tvanni` — the bestest peer

### Use of AI

AI (Claude) was used for the following tasks only:

* drafting this `README.md` from the already-written sources, including the description
  of the algorithm and of the data structures;

The design of the program (parser, flag bitmask, output buffer, base conversion by
powers), the implementation of every function and the debugging were done without AI
assistance, relying instead only on tvanni, the bestest peer anybody could dream of.