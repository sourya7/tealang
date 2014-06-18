var HOST = "localhost"
var PORT = 5007
var socket = [Socket initWithAF: "AF_INET" withStream: "SOCK_STREAM"]

[socket bindHost: HOST andPort: PORT]
[socket listen: 1]

var res = [socket accept]
var addr = [res get:"addr"]
var conn = [res get:"conn"]

[IO println: "Connected by" + addr]
while True
  var data = [conn recv: 1024]
  if [data len] == 0: 
    break
  endif
  [conn send: data]
endwhile

