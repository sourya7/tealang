defclass Controller
  var view_
  var model_

  defcon init
  endcon

  defun render
    return [view_ render]
  endfun
endclass


