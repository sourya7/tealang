defclass Range
  var container
  var index

  defcon init
    container = {1,2,3,4,5,6}
    index = 0
  endcon

  defun next
    if index <= [container count]
      index = index + 1
      return 1
    endif
    return 0
  endfun

  defun get
    return [container at: index]
  endfun
endclass

var newRange = [Range init]
for x in newRange
  [IO println: x]
endfor
