# strip

```
Usage:
		./strip <"string"> [options]
Options:
		-x <"characters">	characters to be extracted.
		-f <"characters">	characters to be inserted instead of removed characters.
		-s 			characters are added periodically.
```
```
$ ./strip "strip this string with default options"
stripthisstringwithdefaultoptions
```
```
$ ./strip "70:66:55:06:20:07" -x ":"
706655062007
```
```
./strip "70:66:55:06:20:07" -x ":" -f ","
70,66,55,06,20,07
```
```
$ ./strip "70:66:55:06:20:07" -x 3 -f "::" -s
70:::66:::55:::06:::20:::07
```
