import IO

defun bla:a
  if a > 2
      return 1
  endif
  return 0
endfun

defun main:args
  var a = [bla:3]
  [IO println:a]
endfun
