defclass IndexView
  var model_
  defcon initWithModel:m
    model_ = m
  endcon

  defun render
    var str = "Yay I'm the view!" 
    return str
  endfun
endclass
