defclass ListIterator
  var container
  var index

  defcon initWithContainer:c
    container = c
    index = -1
  endcon

  defun next
    if (index + 1) < [container count]
      index = index + 1
      return 1
    endif
    return 0
  endfun

  defun get
    return [container at:index]
  endfun
endclass


var list = {1,2,3,4,5,6}
var rangeIterator = [ListIterator initWithContainer:list]
for x in rangeIterator 
  [IO println: x]
endfor
