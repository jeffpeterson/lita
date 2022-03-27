// class Precedence
// 	class None
// 	class Semi       // ; NEWLINE
// 	class Comma      // ,
// 	class Assignment // = += -= /= *=
// 	class Or         // or
// 	class And        // and
// 	class Equality   // == !=
// 	class Comparison // < > <= >=
// 	class Term       // + -
// 	class Factor     // * /
// 	class Range      // ..
// 	class Prefix     // ! - ++ -- aka PREC_UNARY
// 	class Postfix    // ++ --
// 	class Call       // . ()
// 	class Primary

class Parser
	init(source)
		this.source = source
