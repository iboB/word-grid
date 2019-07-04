# removes words shorter than 3 and longer than 16 characters from a dictionary file
input = ARGV[0]
input = 'common-en.txt' if !input

pruned = []

num_lines = 0
File.open(input, 'r').each_line do |line|
  num_lines += 1
  tline = line.strip
  pruned << tline if tline.length > 2 && tline.length < 17
end

if num_lines == pruned.length
  puts "Nothing to do"
  exit(0)
end

File.open(input, 'w').puts(pruned)

puts "Trimmed #{num_lines - pruned.length} lines"
