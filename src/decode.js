const fs = require('fs')
const path = require('path')

/**
 * @param {*} num Should be an integer no smaller than 2.
 * @returns [Boolean: is out-of-range, Boolean: is prime]
 */
function isPrime(num, bytes) {
    if (num === 2 || num === 3 || num === 5 || num === 7) {
        return [false, true]
    }
    if (num % 2 === 0 || num % 3 === 0 || num % 5 === 0) {
        return [false, false]
    }

    let index = Math.floor((num - 10) / 30)

    if (index >= bytes.length) {
        return [true, false]
    }

    let byte = bytes[index]
    let remainders = [11, 13, 17, 19, 23, 29, 1, 7]
    let x = 1 << (remainders.indexOf(num % 30))
    return [false, ((byte & x) === x)]
}

let bytes = fs.readFileSync(path.join(__dirname, '1.bin'))
console.log('Enter number:')

let stdin = process.openStdin()
stdin.addListener("data", d => {
    try {
        let n = Number.parseInt(d.toString().trim())
        let [outOfRange, numIsPrime] = isPrime(n, bytes)
        if (outOfRange) {
            console.log('Input too large')
        } else {
            console.log(numIsPrime)
        }
    } catch (e) {
        console.log('Error: ' + e.stack)
    }

    console.log('Enter number:')
});
