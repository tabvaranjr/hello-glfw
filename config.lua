-- Default configuration

config = Parameters.new()
config.fullscreen = false
config.debug = true

app = TestApplication.new(config)
app:run()
