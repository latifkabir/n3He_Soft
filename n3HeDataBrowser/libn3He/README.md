Instructions for n3He Library
================================

0. Make any necessary changes in Constants.h file that is required.

1. Do 'make' to compile the library. 

2. This will produce  libn3He.so (shared library will be inside lib directory).

3. Place the .so file in a directory under LD_LIBRARY_PATH.

4. Now start root and load the Library as: gSystem->Load("libTree")  & gSystem->Load("libn3He.so")  . (For Online analysis)

5.  For analysis from a script if you include TTree.h file then you need not to do gSystem->Load("libTree"); Just load 
    gSystem->Load("libn3He.so").  You need to give full path unless the directory is included in LD_LIBRARY_PATH.

6. If you put the rootlogon.C file in "macros" directory under Root installation directory, then the library will be loaded automatically 
and step-4 is NOT necessary.

7. Now from your root script create a Tree by calling: TTreeRaw *my_tree = new TreeRaw(runNumber#) or Just TTreeRaw t(runNumber#)

8. It will also print the tree and branch structure.

9. Now do what ever analysis you want using my_tree.

10. Try running example analysis scripts in "analysis" directory.

11. To make life easier it's convenient to put the following command into your ~/.bash_profile or ~/.bashrc file:

 
```
if [ -f /path/to/libn3He/bin/thisn3He.sh ]; then 
        . /path/to/libn3He/bin/thisn3He.sh
 fi 
```

Note: This version works both for ROOT 5 and ROOT 6.

                                                                   

										 Last Updated on 1/18/15
                                                                                 -Latiful Kabir
