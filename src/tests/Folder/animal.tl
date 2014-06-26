import IO

defclass Animal
  var sound
  defcon initWithSound:s
    sound = s
  endcon
  defun makeSound
    [IO println: sound]
  endfun
endclass

