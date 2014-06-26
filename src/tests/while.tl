import IO

defun test
  var a = 0
  while a < 40
    [IO println:a]
    a = a + 1
  endwhile
endfun

defun main:args
  [test]
endfun

