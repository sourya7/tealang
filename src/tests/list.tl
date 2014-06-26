import IO

defun main:args
  var l = {1,2,3,4,5,6}
  var index = 4

  if (index + 1) < [l size]
    [IO println: "L is bigger than index + 1"]
  endif
endfun
