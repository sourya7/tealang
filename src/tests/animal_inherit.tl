import IO

defclass Animal
  var sound
  defcon init
    sound = "Generic animal Sound!"
  endcon
  defun speak
    [IO println:sound]
  endfun
endclass

defclass Dog isa Animal
  defcon init
    sound = "Woof!"
  endcon
endclass

defun main:args
  var animal = [Animal init]
  var dog = [Dog init]

  [IO println: dog.sound]
endfun
