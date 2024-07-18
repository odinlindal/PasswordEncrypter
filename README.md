# CS132 Ultra Secure Code Checker

## Overview

This project is a simplistic encryption tool to store and reload user access codes. The user will use strings and string manipulation to save an encrypted password to a file named `masterFile.txt`, and check codes against it to see if they are already added. The encryption consists of converting all the characters in the user-inputted string into Morse code. Input validation checks that the code contains 8 letters, 4 numbers, and 1 special character.

### Features

- Save encrypted passwords to a file
- Check if a code already exists in the file
- Convert characters to Morse code
- Input validation for entry codes

## File Structure

- `main.cpp`: Main file with function implementations and program flow.
- `masterFile.txt`: Text file to store encrypted codes.
