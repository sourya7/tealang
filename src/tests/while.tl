import IO

defun test
  var a = 4
  while a != 0 
    [IO println:a]
    a = a - 1
  endwhile
endfun

defun main:args
  [test]
endfun

