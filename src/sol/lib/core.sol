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
	inspect => start.inspect + ".." + end.inspect
	string => start.string + ".." + end.string

class String
	bold      => "\e[1m" + this + "\e[21m"
	dim       => "\e[2m" + this + "\e[22m"
	italic    => "\e[3m" + this + "\e[23m"
	underline => "\e[4m" + this + "\e[24m"
	invert    => "\e[7m" + this + "\e[27m"
	hide      => "\e[8m" + this + "\e[28m"
	strike    => "\e[9m" + this + "\e[29m"

	black   => "\e[30m" + this + "\e[39m"
	red     => "\e[31m" + this + "\e[39m"
	green   => "\e[32m" + this + "\e[39m"
	yellow  => "\e[33m" + this + "\e[39m"
	blue    => "\e[34m" + this + "\e[39m"
	magenta => "\e[35m" + this + "\e[39m"
	cyan    => "\e[36m" + this + "\e[39m"
	white   => "\e[37m" + this + "\e[39m"

	bg_black   => "\e[40m" + this + "\e[39m"
	bg_red     => "\e[41m" + this + "\e[39m"
	bg_green   => "\e[42m" + this + "\e[39m"
	bg_yellow  => "\e[43m" + this + "\e[39m"
	bg_blue    => "\e[44m" + this + "\e[39m"
	bg_magenta => "\e[45m" + this + "\e[39m"
	bg_cyan    => "\e[46m" + this + "\e[39m"
	bg_white   => "\e[47m" + this + "\e[39m"

class Table
	inspect()
		return "{" + "}"

class Tuple

class Atom(type, value, targets) // ...targets)
