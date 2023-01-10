fn fib(n)
	if n < 2: return n
	return fib(n - 2) + fib(n - 1)

// pp "Sol Demo:"
print 4567.toString

let x = 42
print 3(x)

print hash("abcd")
print read("Makefile")
print write("tmp/demo.txt", "It runs!")

class Point(x, y)
	+ (b) = Point(x + b.x, y + b.y)

let p1 = Point(4, 5)
let p2 = Point(6, 7)

print Point

print(p1.+(p2))
print(p1 + p2)
