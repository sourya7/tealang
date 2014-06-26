import IO

defun main:args
  var a = -2 * 2
  var b = a * 3
  var c = a ** 3 * 5 + b - (20 % 3)
  [IO println: "Value of a: " + a]
  [IO println: "Value of b: " + b]
  [IO println: "Value of c: " + c]
endfun
