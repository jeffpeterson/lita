macro assert(...args)
	match args
		(x, '==, y) ->
			if eval(x) == eval(y)
				print '.
				return x
			else
				print "Expected: "
				return x
		x ->
			if x
				print '.
				return x
			else
				print 'F
				return x
