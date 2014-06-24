import IO
defclass Bla
  var someProp
  defcon init
    someProp = 1
  endcon
endclass


var bla = [Bla init]
[IO println: bla.someProp]
