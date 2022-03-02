#build environment:  
windos10  
qt creator 5.0  
Compiler: winlibs personal build version gcc-9.3.1-snapshot20210402-mingw-w64-8.0.0-r1  

#reduce the problem:  
1\ click start to run the app  
2\ when a bar plots list show, click one of the plots.  
3\ at this time, the app maybe crashe. but sometime it wouldn't crash and success to open a new window.  

 for there isn't any code that is used by cross threads, so I can't know where to place QMutex lock. so, I have trie to add  here and there. all those not work.
 the app still often crashes.
 
 
