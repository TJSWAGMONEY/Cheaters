
    Files necessary:
    - plagiarismCatcher.cpp
    - hashTable.h
    - makefile
    
    Instructions for using plagiarismCatcher:
    
    1. Make sure the folder containing the files you want to check
       is in the same directory as the files listed above.
    2. Type "make" in the console. After about a second, the screen
       should clear.
    3. To run the program, type:
       
       ./plagiarismCatcher directory chunkSize numberOfMatches
    
       where "directory" refers to the name of the folder your files
             "chunkSize" refers to the amount of words per chunk
             "numberOfMatchers" refers to the minimum amount of
                                possible instances of plagiarism
                                for the files to be flagged
   
       Example: ./plagiarismCatcher sm_doc_set 6 200

    Other concerns:

    - The program does not work for the large file set provided.
      Only the small and medium file sets work.

