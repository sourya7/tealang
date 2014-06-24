import IO

defun test
  var a = 2
  while a < 40
    [IO println:a]
    a = a + 1
  endwhile
endfun

[test]

