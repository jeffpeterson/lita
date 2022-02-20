# Language Ideas

Some distinction between checking if a value is empty
and checking if it's falsy. I think a postfix `?` would make sense
for one of those operations.

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

Sadly, this prevents methods ending with `?` such as `even?`, which are otherwis great. We could still do `?` as prefix?

`?"string" //=> true` and `?"" //=> false`

---

Remove commas from parameters?

```
get "/foo" (foo, bar, baz) // Tuples still need them
[1 2 3] -> sum
foo bar, foo baz // (foo bar), (foo baz)
add 1 2
```
