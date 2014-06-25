import IO
defun printSumOfA:a andB:b
  [IO println: "Sum of a and b is: " + (a+b)]
endfun

defun main:args
  [printSumOfA:2 andB:3]
endfun
