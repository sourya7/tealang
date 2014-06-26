import IO

defun main:args
  var a = {1,2,3,4,5}
  for x in a
    [IO println: x]
  endfor
endfun
