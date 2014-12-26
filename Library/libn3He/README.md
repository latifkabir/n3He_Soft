Instructions for n3He Library
================================

0. Make any necessary changes in Constants.h file that is required.

1. Do 'make' to compile the library. 

2. The produced .so (shared library will be inside lib directory).

3. Place the .so file in a directory under LD_LIBRARY_PATH.

4. Now start root and load the Library as: gSystem->Load("libTree")  & gSystem->Load("libn3He.so")  . (For Online analysis)

5.  For analysis from a script if you include TTree.h file then you need not to do gSystem->Load("linTree"); Just load 
    gSystem->Load("libn3He.so").  You need to give full path unless the directory is included in LD_LIBRARY_PATH.

6. Now from your root script create a Tree by calling: TTreeRaw *my_tree = new TreeRaw(runNumber#) or Just TTreeRaw t(runNumber#)

7. It will also print the tree and branch structure.

8. Now do what ever analysis you want using my_tree.

9. Try running example analysis scripts in "analysis" directory.

10. To make life easier you might want to add line in rootlogon.C to load the library automatically each time you start ROOT or even better 
     it's convenient to put this source command into your ~/.bash_profile or ~/.bashrc file:

 
```
if [ -f /path/to/libn3He/bin/thisn3He.sh ]; then 
        . /path/to/libn3He/bin/thisn3He.sh
 fi 
```

                                                                   
                                          

										-Last Updated on 12/25/14
                                                                                          Latiful Kabir
