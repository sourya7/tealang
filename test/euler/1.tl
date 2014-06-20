
var sum = 0
var i = 3
while i < 1000
  if i % 3 == 0 || i % 5 == 0
    sum = sum + i
  endif
  i = i + 1
endwhile

[IO println: sum]
  
