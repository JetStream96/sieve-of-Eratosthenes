const fs = require('fs')

function isPrime(x, allPrimes) {
    for (let i of allPrimes) {
        if (x % i === 0) {
            return false
        } else if (i * i > x) {
            break
        }
    }

    return true
}

/** 
 * Encode [11, 13, 17, 19, 23, 29, 31, 37] in a single byte.
 * Similar for [41, 43, ..., 67], [71, 71, ..., 97], etc.
 * Returns a byte array. First input should be 11, and the array length 
 * should be divisible by 8.
 */
function encode(primes) {
    if (primes[0] !== 11) {
        throw new Error()
    }

    let len = primes.length
    let byteCount = Math.ceil((primes[len - 1] - 10) / 30)

    let bytes = new Buffer(byteCount)
    let remainders = [11, 13, 17, 19, 23, 29, 31, 37]
    let index = 0

    for (let i = 0; i < byteCount; i++) {
        let byte = 0
        for (let j = 0; j < 8; j++) {
            if (index === len) {
                break
            }

            if (primes[index] === 30 * i + remainders[j]) {
                byte |= 1 << j
                index++
            }
        }

        bytes[i] = byte
    }

    return bytes
}

/**
 * Make sure the range of numbers is divisible by 8.
 * Maps:
 * 11 - 40 => 40
 * 41 - 70 => 70
 * 71 - 100 => 100
 * @param {*} max 
 */
function extendRange(max) {
    if (max < 11) {
        return 40
    }

    return Math.ceil((max - 10) / 30) * 30 + 10
}

function getPrimes(max) {
    let r = extendRange(max)
    let primes = [2]
    for (let i = 3; i <= max; i += 2) {
        if (isPrime(i, primes)) {
            primes.push(i)
        }
    }

    return encode(primes.slice(4))
}

let max = Number.parseInt(process.argv[2])
fs.writeFileSync('./1.bin', getPrimes(max), 'binary')
