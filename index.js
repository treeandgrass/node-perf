const { NativeModule } = require('bindings')('addon.node')
const EventEmitter = require('events');
const eventEmitter = new EventEmitter()

/**
 * gc callback
 */
function gc_callback () {
  eventEmitter.emit('gc')
}

/**
 * initialize
 */
module.exports.initialize = () => {
  const nativeModule = new NativeModule(gc_callback)
  nativeModule.initialize()
}

/**
 * expose gc event
 */
module.exports.eventEmitter = eventEmitter