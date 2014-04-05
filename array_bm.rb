#! /usr/bin/ruby
require 'benchmark'

arr = [].tap do |array|
  2000000.times do |n|
    array << { number: n }
  end
end

Benchmark.bm do |b|
  b.report("#select and #map    ") do
    arr.select { |n| n[:number] % 2 == 0 }.map! { |e| e[:number] }
  end

  b.report("#select and #collect") do
    arr.select { |n| n[:number] % 2 == 0 }.collect! { |e| e[:number] }
  end

  b.report("#collect            ") do
    arr.collect { |n| n[:number] % 2 == 0 ? n[:number] : nil }.compact!
  end
end