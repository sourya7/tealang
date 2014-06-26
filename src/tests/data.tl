import IO

defun main:args
  var a = {1,2,3,4,5}
  [IO println: "a[0] = " + [a at:0]]

  var b = {1 => "one", 2 => "two", 3 => "three"}
  [IO println: "b[1] = " + [b at:1]]

  var c = {"nigeria" => "abuja", "ghana" => "accura", "jordan" => "amman"}
  [IO println: "c[nigeria] = " + [c at:"nigeria"]]
endfun

