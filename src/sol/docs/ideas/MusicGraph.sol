// stdlib
atom Duration(Number seconds)

// Music
atom Name(String)
atom Title(String)


atom Song(Id) // Different tracks are often the same song.

atom Track(Id)
	-> Title
	-> Song
	-> Duration
	-> Album
	-> Artist

atom Album(Id)
	-> Title
	-> Artist

atom Artist(Id)
	-> Name


Artist, Name("Alabama Shakes")

Track,
	Title "Sound & Color",
	Artist.with(Name "Alabama Shakes"),
	Album.with(Name "Sound & Color"),
	Duration(182)

each: Track, Duration(60..180), Name(name) // tracks from 1 to 3 minutes
	puts name
