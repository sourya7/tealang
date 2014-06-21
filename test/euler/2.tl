defun sumfib
  var start = 1
  var next = 2
  var sum = 0
  while start < 4000000
    if start % 2 == 0
      sum = sum + start
    endif
    var tmp = start
    start = next
    next = next + tmp
  endwhile
  return sum
endfun
    
[IO println: "The sum is: " + [sumfib]]
