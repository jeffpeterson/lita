fn outer()
	let x = "third";
	fn middle()
		fn inner()
			print x;

		print "second";
		return inner;

	print "first";
	return middle;

let mid = outer();
let inn = mid();
inn();

__END__
"first"
"second"
"third"
