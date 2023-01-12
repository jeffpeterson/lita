/// Identifiers
let x
let x' = 1
let x₂' = 3

assert x' == 1
assert x₂' == 3

/// Literals
assert 1
assert 1, 2
assert 0..9
assert 1.class == Number

/// Natives
assert clock()
assert (3; 4) == 3

/// Math
let a = 2
let b = 4

assert 2 + 2 == 4
assert a + b == 6
assert 2(3) == 6
assert (2 b) == 8

/// Strings
assert "Strings"
assert ('0 + '5) == '05
assert ("hi " + "there") == "hi there"
assert 'foo / 'bar == "foo/bar"
assert '/ == "/"
assert '"hi there" == "\"hi there\""
assert '( == "("
assert "" nil == ""
assert nil.string == ""
assert "" 3 == "3"
assert "" 3.5 == "3.5"

/// Inspect
assert "hi".inspect == '"hi"
assert 3.inspect == "3"
assert (1, 2).inspect == "1, 2"

/// Tuples
assert (1, 2) == (1, 2)
assert (2, 3) != (1, 2)

/// Arrays
assert [1, 2, 3]
assert [1, 2].get(1) == 2
// assert [1, 2, 3].length == 3
// assert [1, 2] + [3] == [1, 2, 3]

/// Instances
class Point(x, y)
	fn magnitude = (x + y)
	fn + (b) = Point(x + b.x, y + b.y)
	fn == (b)
		return x == b.x and y == b.y

let p1 = Point(1, 2)
let p2 = Point(3, 4)

assert p1 + p2 == Point(4, 6)

/// Precedence
assert (assert 1) == 1

assert (3b) == 12
assert (b 3) == 12
assert (Point 1 2)

/// ?: operator
assert (1 ? 2) == 2
assert (1 ?: 2) == 1
assert (nil ? 2) == nil
assert (nil ?: 2) == 2

let i = 0
let j = 0
for ; i < 10; i++
	assert i == (j++)
assert i == 10
assert j == 10

fn empty_fn()

assert empty_fn() == nil

write "\n\nAssertions passed!\n".green
