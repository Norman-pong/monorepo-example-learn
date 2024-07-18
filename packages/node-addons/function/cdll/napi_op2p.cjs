const addon = require('./build/Release/addon.node')
const { clientConfig } = require('./config.json')

const conf = JSON.stringify(clientConfig)

const placeholder = Array.from('#'.repeat(60)).join('')
console.log(`
  ${new Date()}
  ${placeholder}
        CNewClient Start

        addon.NewClient(${conf})
  ${placeholder}
`)

try {
  const server = addon.NewClient(conf)
  console.log(server)

} catch (error) {
  console.log(error)
}
