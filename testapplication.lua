-- Default script

ticktock = Timer.new()

config = Parameters.new()
config.fullscreen = false
config.debug = true

app = TestApplication.new(config)
app:run()

print("Took " .. ticktock:getTime() .. " seconds")
