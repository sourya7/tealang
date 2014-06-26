import IO
import Folder.animal

defun main:args
  var Dog = [Animal initWithSound:[args at:0]]
  [Dog makeSound]
endfun
