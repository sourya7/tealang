defclass ClassImp
  var name
  defcon initName:n
    name = n
  endcon
  
  defun sayHi
    [IO println: name]
  endfun
endclass

import ClassImp.ClassImp
import Socket

import Socket
import ClassImp
import ClassImp.ClassImp

var obj = [ClassImp initName: "Sourya Sharma"]
[obj sayHi]

1. Read the ClassImp file
2. Load the ClassImp class into the ClassImp variable in the root structure
