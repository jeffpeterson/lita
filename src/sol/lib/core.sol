class Nil < Any
class Object < Any

// class Bytes(str)
// class Inspect(String)
// class Literal(String)

// class Point(x, y)

// class Any < nil

class Bool
class Error
class Number

class Range(start, end)
	inspect()
		return this.start.inspect() + ".." + this.end.inspect()

	string()
		return this.start.string() + ".." + this.end.string()

class String
class Table
	inspect()
		return "{" + "}"

class Tuple

class Function

class Method < Function
class NativeFunction < Function

class Class < Function
