Question: What happens if you define a static variable in a header file and include the header in multiple source files. Do the header guards prevent that multiple copies of the static variables are created?

Answer: No.

```
staticvars frey$ ./meh 
a from bar: 0x105fd601c a from foo: 0x105fd6018
```
