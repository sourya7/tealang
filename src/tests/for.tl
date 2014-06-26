import IO
defclass SomeClassIter 
  var container
  var index

  defcon initWithContainer:c
    container = c
    index = -1
  endcon

  defun next
    if (index + 1) < [container size]
      index = index + 1
      return 1
    endif
    return 0
  endfun

  defun get
    return [container at:index]
  endfun
endclass

defclass SomeClass
  var list
  defcon init
    list = {1,2,3,4,5}
  endcon
  defun __iter__
    var rangeIterator = [SomeClassIter initWithContainer:list]
    return rangeIterator
  endfun
endclass

defun main:args
  var sc = [SomeClass init]
  for x in sc
    [IO println: x]
  endfor
endfun
