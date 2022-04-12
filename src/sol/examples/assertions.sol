/// Literals
assert 1
assert 1, 2
assert "Strings"
assert 0..9

/// Natives
assert clock()
// assert pp(1)

/// Math
assert 2 + 2 == 4
assert ('0 + '5) == '05
assert ("hi " + "there") == "hi there"

let a = 2
let b = 4

assert a + b == 6

/// Instances
class Point(x, y)
	magnitude() => (x + y)
	+ (b) => Point(this.x + b.x, this.y + b.y)
	== (b) => this.x == b.x and this.y == this.y

let p1 = Point(1, 2)
let p2 = Point(3, 4)

// assert p1 + p2 == Point(4, 6)

write("\n\nAssertions passed!\n".green)
