# Todo

- [ ] Native methods manipulate stack directly
- [ ] `match` expression
- [ ] Control-flow expressions
- [ ] OrderedSet
- [ ] Intern ranges
- [ ] ECS inside-out fields
- [ ] Integrate flecs
- [ ] Multi-methods
- [ ] Pattern Matching
- [ ] ~~Remove `fn` keyword~~
- [ ] Single argument functions? `foo x == foo (x) == foo(x)`
      `foo(x, y) == foo((x, y))` `(x, y) == ((x, y))` and so
      `foo(x, y) == foo((x, y))` `foo x, y == (foo(x), y)` or
      `foo x, y == foo(x, y)` What about multiple? `foo x y == foo(x)(y)`?

      - Another consideration is that `foo bar(x)` could be naively interpreted as `(foo bar)(x)`. That wouldn't be right, and thus `x y z` should be `x (y z)`
      - `foo (bar x), y` or `foo (bar x, y)`
        I think it should work like this: `foo (bar x), y` is `foo(bar(x), y)`.
        I think we're trying to reduce the number of nested parentheses and we need to allow `print x, y` as `print (x, y)`.

- [ ] Implement hypergraph Probably `uuid_v4` for AtomId and `uuid_v5` for
      DataId
