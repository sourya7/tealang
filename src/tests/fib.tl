import IO
defun fib:n
  if n < 2
    return n
  endif
  return [fib: n-1] + [fib: n-2]
endfun

defun main:args
  if [args size] == 2 
    [IO println: [fib: [Integer fromStr: [args at:1]]]]
  else
    [IO println: "Usage: " + [args at:0] + " <fib n>"]
  endif
endfun
