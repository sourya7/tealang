import IO

defun main:args
  var a = {
    1 => "abc",
    2 => "bcd",
    3 => "def",
    4 => "ggg",
    5 => "ddd"
  }
  [IO println: [a at:1]]
endfun
