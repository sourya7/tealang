var a = 0
var l = {}
while a != 10
  [l append:a]
  a = a + 1
endwhile

[IO println: "Im here"]
while a > 0
  [IO println: [l at:a-1]]
  a = a - 1
endwhile
