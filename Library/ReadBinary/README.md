ReadBinary
==========

The ReadBinary class can read binary data produced by Data Acquisition system and give you the corresponding decimal value which is the very first step of any kind of analysis done in Physics or other fields. 

How To Use
------------
In your your analysis script --
   1. Include the header called ReadBinary.h 
   2. Define an ReadBinary object with the binary file as argument in your analysis. 
   3. Call GetValue member function to get the corresponding vale.
   4. GetVale can take two arguments : i. The ADC channel number ii. The entry number.
   5. Write codes for what ever analysis or plotting you want to do in C or C++.
   6. Save the script as .cpp file in the same directory.
   7. From the directory where you have makefile just do: make 
   8. Run the binary "Program" that is produced. 



What are the advantages
------------------------
   1. Do the analysis in a programmer's style.
   2. Core analysis (except plotting) independent of ROOT.
   3. Better stability and error message (since independent of ROOT).
   4. Can be integrated to any other library or ROOT class easily.
 

To run the example(scan.cpp) included
------------------------------------- 
   1. From the directory where you have Makefile do:`make`
   2. Run the executable `scan` 
   3. Enter the channel number,starting point and number of entries to be printed
   4. This will print the values for the desired entries
