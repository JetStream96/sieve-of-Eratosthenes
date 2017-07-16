function checkPrime(n) {
    if (n === 2) {
        return true
    }

    if (n % 2 === 0) {
        return false
    }

    let x = 3
    while (x * x <= n) {
        if (n % x === 0) {
            return false
        }
        x += 2
    }

    return true
}

let n = Number.parseInt(process.argv[2])
console.log(checkPrime(n))
