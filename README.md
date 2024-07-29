# Lita Lang

Lita is a Relational-Logical programming language.

* Immutable data structures.
* Programs can be in _superpositions_; that is, their execution and
state can fork into multiple branches. These branches either collapse back
together or are pruned.
* Symbolic: The language can represent its own syntax.
* Pattern matching


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
