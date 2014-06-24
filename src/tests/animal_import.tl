import IO
import animal

defun main:args
  var Dog = [Animal initWithSound:[args at:2]]
  [Dog makeSound]
endfun
