defclass Model
  var dict_
  defcon initWithList:l
    dict_ = {
      "Class" => [l at:0]
      "Title" => [l at:1]
      "Track" => [l at:2]
    }
  endfun

  defun get:a
    return [dict_ at:a]
  endfun

  defun set:a to:b
    [dict_ insertVal:a At:b]
  endfun
endclass


