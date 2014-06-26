import IO

defun main:args
  [IO println: "Got: " + [args at:1]]
  [IO println: [String fromObj:[args at:1]]]
endfun

