import IO

defun main:args
  var a = 0 
  while true
    if a < 10
      a = a + 1
      [IO println: a]
    else
      break
    endif
  endwhile
endfun
