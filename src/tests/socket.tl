import IO
import Socket

defun main:args
  var HOST = "localhost"
  var PORT = [Integer fromStr:[args at:1]]
  var socket = [Socket initWithFamily:Socket.AF_INET andStream:Socket.SOCK_STREAM]

  [socket bindHost:HOST andPort:PORT]
  [socket listen:1]
  [socket accept]
  
  while true 
    var data = [socket recvN:1024]
    [IO print: data]
    [socket send:data]
  endwhile
endfun
