import IO

defun bla:a
  if a > 2
      return 1
  endif
  return 0
endfun

var a = [bla:3]
[IO println:a]
