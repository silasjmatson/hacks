i = 0
start = Time.new

[
  Thread.new do
    while i <= (10**9)
      puts i
    end
  end,

  Thread.new do
    while i <= (10**9)
      i += 1
    end
  end
].map(&:join)
total = Time.new - start
puts "This calculation took #{total} seconds"

