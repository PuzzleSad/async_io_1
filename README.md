# async_io_i #

This is an educational project to explore the potential performance characteristics of asynchronous
file loading via the liburing/io_uring linux interface

The idea is to see if I can beat the following:

```
FILE *fp = fopen( path, "r" );

fseek( fp, 0, SEEK_END );
filelen = ftell( fp );
rewind( fp );

uint8_t* buff;
buff = (uint8_t*)malloc( filelen );

fread( buff, sizeof(uint8_t), filelen, fp );
```

This operating requires that the entire file is loaded to disk before any operations can be done on
the data. 
Of course, async IO buffers the file in blocks. This implies that it's possible to start prosessing
data without having to wait for the entire file to load first.

The specific test would be to use some arbitrary function to "process" the data. If the file is
excessively large, such as a 400Mb file being loaded by a raspberry pi into ram the results of this
test would become evident.
