var memoize = function(f) {
  var memo = [];
  return function(i) {
    if (memo[i]) {
      return memo[i];
    }
    result = f(i);
    memo[i] = result;
    return result;
  }
}

var mfib = memoize(function(i) {
  if (i === 0 || i === 1) {
    return i;
  }
  return mfib(i - 1) + mfib(i - 2);
})

console.log(mfib(8));
console.log(mfib(1000));
