defun fib:a                    
    if a==0             
        return 0
    endif                   
    if a==1                 
        return 1            
    endif                   
    var l = [fib: a-1]         
    var r = [fib: a-2]         
    return l + r            
endfun                          


var f = [fib: 30]
[printf: "The fibonacci of " + 10 + " is " + f + "\n"]

