class Range
	init(start, end)
		this.start = start;
		this.end = end;

	inspect()
		this.start.inspect() + ".." + this.end.inspect();

	toString()
		this.inspect();
