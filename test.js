const Index = require('./index.js')

Index.eventEmitter.on('gc', () => {
  console.log('gc--')
})

Index.initialize()

setInterval(() => {
  if (global.gc) {
    global.gc()
  }
}, 2000)