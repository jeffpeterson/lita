class Nil < Any
class Object < Any

// class Bytes(str)
// class Inspect(String)
// class Literal(String)
// class Point(x, y)

class Function
class Method < Function
class NativeFunction < Function
class Class < Function

class Array
	fn == (b)
		if length != b.length: return false
		if objectId == b.objectId: return true
		for let i = 0; i < length; i++
			if get(i) != b.get(i): return false
		return true

class Bool
class Error
class Number

class Range(start, end)
	fn inspect = start.inspect + ".." + end.inspect
	fn string  = start.string + ".." + end.string

class String
	fn string = this

	fn / (str) = this + "/" + str

	fn bold      = "\e[1m" + this + "\e[21m"
	fn dim       = "\e[2m" + this + "\e[22m"
	fn italic    = "\e[3m" + this + "\e[23m"
	fn underline = "\e[4m" + this + "\e[24m"
	fn invert    = "\e[7m" + this + "\e[27m"
	fn hide      = "\e[8m" + this + "\e[28m"
	fn strike    = "\e[9m" + this + "\e[29m"

	fn black   = "\e[30m" + this + "\e[39m"
	fn red     = "\e[31m" + this + "\e[39m"
	fn green   = "\e[32m" + this + "\e[39m"
	fn yellow  = "\e[33m" + this + "\e[39m"
	fn blue    = "\e[34m" + this + "\e[39m"
	fn magenta = "\e[35m" + this + "\e[39m"
	fn cyan    = "\e[36m" + this + "\e[39m"
	fn white   = "\e[37m" + this + "\e[39m"

	fn bg_black   = "\e[40m" + this + "\e[39m"
	fn bg_red     = "\e[41m" + this + "\e[39m"
	fn bg_green   = "\e[42m" + this + "\e[39m"
	fn bg_yellow  = "\e[43m" + this + "\e[39m"
	fn bg_blue    = "\e[44m" + this + "\e[39m"
	fn bg_magenta = "\e[45m" + this + "\e[39m"
	fn bg_cyan    = "\e[46m" + this + "\e[39m"
	fn bg_white   = "\e[47m" + this + "\e[39m"

class Table
	fn inspect = "{" + "}"

class Tuple

class Atom(type, value, targets) // ...targets)
