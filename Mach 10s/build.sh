#!bin/bash

# Jaime Bohorquez

# Wireless upload build script

# Ensures that the program doesn't upload if it doesn't
# compile sucessfully.
prosv5 make && echo "y" | prosv5 upload

# pros CLI commands:
# prosv5 make
# prosv5 upload
# prosv5 terminal
