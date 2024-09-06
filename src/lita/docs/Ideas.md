# Language Ideas

Some distinction between checking if a value is empty and checking if it's
falsey. I think a postfix `?` would make sense for one of those operations.

Some form of optional chaining. This could be implemented on `nil`:
`nil.foo.bar //=> nil`. `!` could be used to prevent this:
`nil.foo!.bar //=> error`.

What would `?` do then? It could check if something is empty?

```lox
"string"?  //=> true
1.even??   //=> true
1?         //=> true

nil?       //=> false
""?        //=> false
[]?        //=> false
nil.foo?   //=> false
1.foo?     //=> false
1.is_even? //=> true
```

Sadly, this prevents methods ending with `?` such as `even?`, which are
otherwise great. We could still do `?` as prefix?

`?"string" //=> true` and `?"" //=> false`

---

Remove commas from parameters?

```
get "/foo" (foo, bar, baz) // Tuples still need them
[1 2 3] -> sum
foo bar, foo baz // (foo bar), (foo baz)
add 1 2
```

---

`{}` defines a tag-set. Indexed by tag. `x: 1` tags `1` with `x:`. `Path "/etc"`
tags `"/etc"` with `Path`. `{x: 1, y: 2}`

---

`ObjTable` represents a table of fields, and `ObjInstance` points to a
`ObjClass` and a parent `Value`.

For example, a `Name` instance would point to an `String` and a `Name` class,
and a `Point` instance would point to a `Tuple`.

---

Method lookups and related should be cached for a given prototype chain. Each
class should be immutable under-the-hood. We need to ensure, though, though that
all dependencies close over a reference to the class, not the immutable
instance.

---

_ObjPointer_ references an immutable _Value_, and behaves just like that value,
but can be mutated to point to a different value. _ObjRef_?

_ObjCursor_ is a pointer and an offset into some memory range. It can be mutated
to point to a different offset via pointer arithmetic.

---

Reject inheritance. A `Name` is not a kind of `String`. A name is composed of
a `String`. In fact, a `Name` could be composed of something else, as long as it
behaves like a `Name`; and behaving like a `Name` means to be transformable to
a `String`.

---

I don't like `x.in 1..9`. I think it should be `x in 1..9`.

    def x 'in start..end
        start <= x <= end

However, this says the `'in` is a string literal, so that can't be quite right.
Expressions could be designated with parentheses:

    def (x) in (start..end)
        start <= x <= end
