import IO

defun rangeFrom:x to:y
  while x < y
    yield x + 1
  endwhile
endfun

var ob = [rangeFrom:2 to:10]
for x in ob
  [IO println:x]
endfor
