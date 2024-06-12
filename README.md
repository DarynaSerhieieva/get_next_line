# get_next_line

## Description
`get_next_line` is a function that reads a line from a file descriptor, one line at a time, with the ability to handle various buffer sizes. This implementation allows for repeated calls to `get_next_line`, enabling sequential reading of a text file.

## Usage
To use `get_next_line` in your project, include the header file `get_next_line.h` and compile your code with the appropriate flags. You can adjust the buffer size by defining `BUFFER_SIZE` during compilation or in the header file.

Example compilation:
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 <files>.c

## Testing
To test the get_next_line function, compile the source files along with the test_main.c file, and execute the resulting binary. The test_main.c file contains a simple demonstration of how to use get_next_line to read lines from a file descriptor.

```sh
 cc -Wall -Wextra -Werror -D BUFFER_SIZE=1000 get_next_line.c get_next_line_utils.c test_main.c -o  get_next_line | ./get_next_line
```
