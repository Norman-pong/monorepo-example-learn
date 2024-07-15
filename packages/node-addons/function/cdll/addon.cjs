var addon = require('./build/Release/addon')


const server = addon.add('ts')
console.log('This should be eight:', addon.add('ts'))