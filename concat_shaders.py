import os
# Fragment Combine
fragment_files = ["Utils.glsl", "Ray.glsl", "Interval.glsl", "Material.glsl", "HitRecord.glsl", "Scatter.glsl", "Sphere.glsl", "Cylinder.glsl", "Cube.glsl", "World.glsl"]
output_file = "Shaders/combined.glsl"
temp_file = "Shaders/combined_compute.glsl"

for i in range(len(fragment_files)):
	fragment_files[i] = "Shaders/Compute Components/" + fragment_files[i]

with open(temp_file, "w") as f:
	pass

with open(temp_file, "a") as outfile:
	for file in fragment_files:
		with open(file, "r") as infile:
			outfile.write(infile.read())
			outfile.write("\n")


# Final Combine
files_to_combine = ["vertex.glsl", "fragment.glsl", temp_file, "compute.glsl"]

for i in range(len(files_to_combine)):
	if i == 2:
		continue
	files_to_combine[i] = "Shaders/" + files_to_combine[i]

with open(output_file, "w") as f:
	pass

with open(output_file, "a") as outfile:
	for i in range(len(files_to_combine)):
		with open(files_to_combine[i], "r") as infile:
			if files_to_combine[i] == "Shaders/vertex.glsl":
				outfile.write("# Shader Vertex\n# version 430 core\n")
				outfile.write(infile.read())
			elif files_to_combine[i] == "Shaders/fragment.glsl":
				outfile.write("\n\n# Shader Fragment\n# version 430 core\n")
				outfile.write(infile.read())
				outfile.write("\n\n# Shader Compute \n# version 430\n")
			else:
				outfile.write(infile.read())
				outfile.write("\n")

print(f"Concatenation complete! Output written to {output_file}")
