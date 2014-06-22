// naive algorithm. Extra stuff just to test language
// This wont work as a solution because the number is
// too big to be held as a long

var primes = {2}
defun getPrimeAfter:lastPrime
  var size = [primes count]
  var increment = 2
  if lastPrime == 2
    increment = 1
  else 
    increment = 2
  endif
  while 1
    lastPrime = lastPrime + increment
    var i = 0
    while i < size
      if (lastPrime % [primes at:i]) != 0
        i = i + 1
      else
        break
      endif
    endwhile
    if i == size
      [primes append:lastPrime]
      return
    endif
  endwhile
endfun

defun findPrimeFactorsFor:n
  while 1
    var psize = [primes count] - 1
    var lastPrime = [primes at:psize]
    while (n % lastPrime) == 0
      [IO print: " " + lastPrime + " "]
      n = n / lastPrime
    endwhile
    if n == 1
      return
    else
      [getPrimeAfter: lastPrime]
    endif
  endwhile
endfun

[findPrimeFactorsFor:4005]
[IO println: " "]
