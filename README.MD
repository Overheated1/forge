Lexer -> Parser -> Code Generator


typedef -> is to do an specie of alias 
example:
    typedef int notes_int
    notes_int notes = 100;

is like int changes his name to notes_int but for behind is other form to call the same     

*malloc(size_t size) allocates the requested memory and returns a pointer to it.

example:
    str = (char *) malloc(15);
    strcpy(str, "tutorialspoint");
    printf("String = %s,  Address = %u\n", str, str);
size_t:
    in C is an unsigned data type used to represent sizes of objects. It is an integer type that is capable of holding the maximum theoretical size of any object in the system where the program is running. It is commonly used in operations related to memory size, such as dynamic memory allocation.
fseek():
    fseek() is used to move the file pointer associated with a given file to a specific position.
    Syntax: int fseek(FILE *stream, long offset, int origin);
    stream is a pointer to a FILE object that identifies the stream.
    offset is the number of bytes to shift the position relative to origin.
    origin specifies the reference position for the offset (can be SEEK_SET, SEEK_CUR, or SEEK_END).
    Example: fseek(file, 0, SEEK_END); moves the file pointer to the end of the file.
fread():
    fread() is used to read data from a file.
    Syntax: size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream);
    ptr is a pointer to the buffer where the data is read into.
    size is the size in bytes of each element to be read.
    nmemb is the number of elements to be read.
    stream is a pointer to a FILE object that specifies the stream to read from.
    Example: fread(buffer, 1, length, file); reads length bytes from the file into the buffer.




