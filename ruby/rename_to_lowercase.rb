Dir.glob("./**/*").each do |file_path|
  next if !file_path.split("/").last.include?(".")

  split_path = file_path.split("/")
  old_path = split_path[0..-2].dup
  old_name = split_path[-1].dup
  new_name = old_name.split(".").first.upcase
  new_ext = old_name.split(".").last.downcase
  new_full_path = [[old_path, new_name].join("/"), new_ext].join(".")
  File.rename(file_path, new_full_path)
end
