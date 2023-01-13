print clock()
print "✓\tfirst"
print "✓\t" + 'second
print ("✓ third", "✓ tuple")
print 2 + 2
print '0 + '5

let a = 2
let b = 4

print a + b
print b = 7
print 8..9

for let i = a; i < b; i++
	let x = i + 8
	let y = i - 1
	print ("✓", x, y)

class Ainu(name)
	fn kind = 'Ainu

class Maia < Ainu
	fn kind = "Maia < " + super.kind

class Istar < Maia
	fn kind = "Istar < " + super.kind

let Gandalf = Istar('Gandalf)

print Gandalf.kind

class MyClass
	fn myMethod = 20

print MyClass

let inst = MyClass()

print inst

inst.x = 17
print inst.x++
print inst.x
print inst.x += 1
print inst.myMethod

// print inst.to_string()

// nil values default to 0
print inst.missing++ // 0
print inst.missing // 1
print inst.missing // 2
print inst.missing2 += 1 // 1

let empty
print empty++
// print 20.to_string()

__END__
✓ first
✓ second
("✓ third", "✓ tuple")
4
"05"
6
7
8..9
("✓", 10, 1)
("✓", 11, 2)
("✓", 12, 3)
("✓", 13, 4)
("✓", 14, 5)
MyClass (1 entries) {
	"myMethod" => <fn myMethod/0>
}

<MyClass instance>
17
18
19
<bound myMethod/0>
20
0
1
1
1
0
