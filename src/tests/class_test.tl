import IO

defclass Test isa bla,bla2,bla3
  var sound
  var dot 
  defcon initSound:s andDot:d
    sound = s
    dot = d
  endcon
  defun getSound
    return sound
  endfun
  defun getDot
    return dot
  endfun
endclass

defun main:args
  var first = [Test initSound:"first" andDot:"f"]
  var second = [Test initSound:"second" andDot:"s"]
  var third = [Test initSound:"third" andDot:"t"]

  [IO println: "First Sound:" + [first getSound] + " Dot:" + [first getDot]]
  [IO println: "Second Sound:" + [second getSound] + " Dot:" + [second getDot]]
  [IO println: "Third Sound:" + [third getSound] + " Dot:" + [third getDot]]
endfun


