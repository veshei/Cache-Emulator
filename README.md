# Cache-Emulator
A cache emulator written in C and tested on a given sequence. There is an n-way set associative cache of size s, with blocks or
cache lines of size l and a direct-mapped cache that corresponds to a 1-way set associative cache (n=1), and a fully associative cache that corresponds to a n-way set associative cache with n=s/l, the number of rows (lines) in the cache. The cache emulator accepts a sequence of addresses from the CPU, and determines what the contents of the cache will be after receiving each address. 
All addresses are read-only and they request only one byte of data.  The sequence of addresses may be input in any manner. 
Test Sequence: 0, 4, 8, 12, 16, 20, 24, 28, 32, 36, 40, 44, 48, 52, 56, 60, 64, 68, 72,
  76, 80, 0, 4, 8, 12, 16, 71, 3, 41, 81, 39, 38, 71, 15, 39, 11, 51, 57, 41


