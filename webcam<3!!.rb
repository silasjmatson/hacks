require 'av_capture'

# Create a recording session
session = AVCapture::Session.new

# Find the first video capable device
device = AVCapture.devices.find &:video?

# Output the Camera's name
$stderr.puts device.name

# Connect the camera to the recording session
session.run_with(device) do |connection|
  # Capture an image and write it to $stdout
  $stdout.write connection.capture
end

