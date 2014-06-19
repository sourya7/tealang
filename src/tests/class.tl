defclass Animal
  var sound
  defcon init
    sound = "Generic Animal Sound!"
  endcon
  defun talk
    [IO println:sound]
  endfun
endclass

defclass Dog isa Animal
  defcon init
    sound = "Woof!"
  endcon
endclass

var generic = [Animal init]
var dog = [Dog init]

[dog talk]
[generic talk]
