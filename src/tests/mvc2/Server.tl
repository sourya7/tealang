import IO
import Socket
import IndexController

defun main:args
  var cntrl = [IndexController init]
  var render = [cntrl render]

  var HOST = "localhost"
  var PORT = [Integer fromStr:[args at:1]]
  var socket = [Socket initWithFamily:Socket.AF_INET andStream:Socket.SOCK_STREAM]

  [socket bindHost:HOST andPort:PORT]
  [socket listen:1]
  [socket accept]
  
  while true 
    var data = [socket recvN:1024]
    [IO print: data]
    if [String find:"\r\n\r\n" In:data] != -1
      [IO print: "Control end found!"]
    endif
    if [String lengthOf:data] <= 0
      break
    endif
  endwhile

  [socket send:"HTTP/1.0 200 OK\r\n"]
  [socket send:"Date: Fri, 31 Dec 1999 23:59:59 GMT\r\n"]
  [socket send:"Server: Apache/0.8.4\r\n"]
  [socket send:"Content-Type: text/html\r\n"]
  [socket send:"Content-Length: 59\r\n"]
  [socket send:"Expires: Sat, 01 Jan 2000 00:59:59 GMT\r\n"]
  [socket send:"Last-modified: Fri, 09 Aug 1996 14:21:40 GMT\r\n"]
  [socket send:"\r\n"]
  [socket send:"<TITLE>Exemple</TITLE>"]
  [socket send:"<P>Ceci est une page d'exemple.</P>"]
endfun

endfun
