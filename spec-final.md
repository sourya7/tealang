Lexical Difinitions
===================
lowercase  ::=  "a"..."z"
uppercase  ::=  "A"..."Z"
digit      ::=  "0"..."9"
letter     ::=  lowercase | uppercase
identifier ::=  (letter | _) (letter | digit | _)*
keywords ::= and | or | fun | endfun | class | endclass | for | endfor | 
             if | else | elif | endif | continue | as | while | endwhile | 
             continue | try | catch | finally  

literal ::= strings | integers | floats | imaginary

Comments
========
1. Single line comments begin with '//'
|   // this is a single line comment

2. Multiple line comments begin with '\*' and end with '*/'
|   /* This is a comment spanning multiple 
|      lines */

Variables
=========
1. Variables are used to store values. 
|   x = 24 // valid form

2. The names of variables are identifiers and must follow their lexical definitions. That is, the first letter of a variable must be a letter or an underscore. It can be followed by a number of other letters,digits, or underscore. 

3. Variable always has a local scope to the block it was created within. A global variable is shadowed by a variable in an inner block. 
|   defun hello
|       x = 24
|       anonFun = fun 
|           x = 25 // the global var is shadowed
|       endfun
|       [print: x] // x = 24, as the local scope is anonFun has ended
|   endfun

4. A keyword cannot be used as a variable

Statements 
==========
1. Literals
A literal is a way to represent a fixed value. Tealang supports the string and various numerical literals including integers, floating numbers, and imaginary numbers.
|   var x = "abc" // a string literal assigned to x
|   var y = 12    // an integer literal
|   var z = 42.1  // a floting literal

2. Calls
Calls are made to objects and messages or arguemtns can be passed to them.
|   [object method:args] // the message 'method: args' is sent to the object 'object'
Calls that arent directed towards an object are directed towards the global object under local scope. That is, it has access to local and global properties. 
|   var globalVar = 42
|   [printFormat:"Hello world %d" withArgs:@[globalVar]]
3. Variable declaration
Basically, a variable must always be declared before it is used. There are multiplys ways that can be used to declare a variable. They are as following, 
a. When within a for statement there is no need to declare a variable
for x in rangeFrom:0 To:10  
b. Within a parameter. Here name is a declared variable
defun hellTo:name

Objects
=======
Everything is an object. This includes the classes. The basis of all the objects is the metaobject which is constructed from the metaclass. There can be multiple metaclasses but each object in the language is derived from one and only one metaclass. 

Functions
=========
1. Functions are defined using the 'defun' keyword and end with the 'endfun' keyword
By default they are defined for the global object '::'
|   defun hello 
|       [printStr:"Hello"]
|   endfun 
|   [hello]  // calls the hello function    

2. Arguments can be seperated with a ':'
|   defun fib:n
|       if n == 0 or n == 1 
|           return 1
|       else
|           return [fib:n-1] + [fib:n-2]
|       endif
|   endfun           
|   [fib:10] // calls the fib: function with 10 as the argument

3. Class methods can be called similarly,
|   [clsObj clsMethod]

4. Functions are first-class objects. 
|   var anonFun = hello
|   [anonFun]  // As there is no white space, and as an object is not callable, this is treated as a function call
|   [anonFun __call:@[]] // anonFun is treated as an object. The base function __call is called with nothing
|   var anonFib = fib:
|   [anonFib __call:@[1]] // the anonFib function is called with the argument 1

|   var anonFibFun: = fib:
|   [anonFibFun: 10]

|   defun mapFun:mfun onList:list
|       for x in list
|           [mfun __call:@[x]] 
|       endfor
|   end

|   [mapFun:(fib:) onList:@[1,2,3]]

|   var funDefine = fun 
|       [printStr: "A new function defined anonymously"]
|   endfun
|   [funDefine]

Classes
=======
Every class has a method that is marked as @init. This is the constructor for the class. 
|   defclass ClassExample
|       // Why do we need an defcon?. Because by convention we have a verbose variable naming
|       // system. What happens when init has parameter? We would like to have something like
|       // [class initWithX:x andY: y]. Defcon allows this. What defcon does is this,
        // 1. Takes what ever is inside the init. 
|       defcon init
|       endfun
|
|       defun sayHiTo:name
|           [printStr: "Hi, " + name]
|       endfun
|   endclass

|   var classEx = [ClassExample init]
|   [classEx sayHiTo:"John Doe"]

|   //why do we need to have add a #' in from of the function? So that we can support the 
    //passing formulas with parameters (for ex.: "sayHiTo:" is an ambigious argument in the parameter. Would that be sayHiTo a parameter or a function? 
var boundHiFun: = fun (:x)
    [classEx sayHiTo:x]
endfun   
[map boundHiFun: 

