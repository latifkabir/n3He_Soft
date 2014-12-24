Steps:

0. Make any necessary changes in Constants.h file that is required.

1. Open root using 'root -l' 

2. Compile the library using: .L TBranchBinary.cc+ (Right now compilation with g++ or Root-6 are not compatible)

3. Quit Root. and rename the .so file produced as libn3He.so , this is just to remind that it's n3He shared library.( 2 & 3 are only one   
   time procedure).

4. Now start root and load the Library as: gSystem->Load("libn3He.so")  .

   You need to give full path unless the directory is included in LD_LIBRARY_PATH.

5. Now from your root script create a Tree by calling: TTree *my_tree = n3HeTree(#run_number)

6. It will also print the tree and branch structure.

7. Now do what ever analysis you want using my_tree.
