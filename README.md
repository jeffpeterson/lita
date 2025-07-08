# Lita Lang

An object-oriented language with python and ruby vibes.

Everything is an object. White-space significant.

See [[examples/assertions.lita]] for examples.

Someday this may be useful to someone. But for now, it's a playground for learning.

## Getting started

Run `make` to compile the `lita` and `lita-test` binaries, run the C tests,
and run the lita assertions.

## Debugger

Start the debugger with: `make db/<example>` E.g. `make db/basics`

### lldb cheatsheet

| Alias | Command | Help                             |
| ----- | ------- | -------------------------------- |
| `r`   | `run`   | Run the program.                 |
| `up`  |         | Move up a frame.                 |
| `v`   | `var`   | Show variables in current frame. |
| `p`   | `print` | Evaluate an expression.          |
| `q`   | `quit`  | Quit the debugger.               |
