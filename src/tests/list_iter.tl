import IO

defun main:args
  var list = {"potato", "bhajiya", "something", "random", "boo", "doo"}
  for x in list
    [IO println:x]
  endfor
endfun
