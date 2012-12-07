
// TODO: Write a tokenizer for file format returned by /proc/self/status (/proc/1234/status)
// This is a colon delimeted file.

// Key: Value\n
// Key2: Val\n

// For simplicity, you can do either a destructive parse, or make a copy of the original data.
// Go with copy, but have the real version (_myfunc) do destructive, and function make the copy.

// The return data should be a set of char* pairs, whitespace eliminated.
// For all elements, add a new pair. If last pair, add a dummy "0,0" nullptr pair.
// However! Secretly place a pointer to the source data pointer in the entry right after dummy
// new_ and delete_ function, delete should know this detail and clean-up the data.
// Way to traverse, or alternatively, make a special code for the first string that points to the data
// "__!@#$__", (const char*)DataStartPtr,
// Or make it always element 0, and skip element 0 in searches... no, that wont work.
// Could always return a char** to the 1st element (not 0th). Yes. This only breaks typical delete, which is broke anyway.

// First, scan for key: value pairs.
//   Per line (i.e. from start to newline)
//     is there a colon here?
//     if yes, this is a pair

// Destructive parse is
//   On key
//     find first letter, note it. Usually on this line, but could be after some newlines.
//     find first colon (:), note it.
//     zero the colon (text[colonpos] = 0)
//     Set Key in pair
//     next character
//     find first non whitespace, note it.
//     find last non whitespace, note it. It's considered last once you hit a newline.
//     zero the character after the last non whitespace.
//     Set Val in pair
//     next character
//     repeat
