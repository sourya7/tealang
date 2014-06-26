defclass IndexView
  var model_
  defun initWithModel:m
    model_ = m
  endfun

  defun render
    return "Yay I'm the view!"
  endfun
endclass
