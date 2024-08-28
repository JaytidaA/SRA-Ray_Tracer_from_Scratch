import os

# Define file paths
fragment_files = [
    "utility.glsl",
    "ray.glsl",
    "interval.glsl",
    "material.glsl",
    "hitrecord.glsl",
    "scatter.glsl",
    "cube.glsl"
]

# Define directories and output files
base_dir = "final_cube"  # Base directory containing all files
fragment_dir = os.path.join(base_dir, "Fragment")  # Fragment directory path
temp_file = os.path.join(base_dir, "combined_compute.glsl")  # Temporary combined file
output_file = os.path.join(base_dir, "combined.glsl")  # Final combined output

# Ensure 'Fragment' directory exists
if not os.path.isdir(fragment_dir):
    print(f"Fragment directory not found: {fragment_dir}")
    exit(1)

# Combine fragment shader files into temp_file
with open(temp_file, "w") as outfile:
    for file_name in fragment_files:
        file_path = os.path.join(fragment_dir, file_name)
        if os.path.isfile(file_path):
            with open(file_path, "r") as infile:
                outfile.write(infile.read())
                outfile.write("\n")
        else:
            print(f"File not found: {file_path}")

# Files to combine into the final combined output
files_to_combine = ["vertex.glsl", "fragment.glsl", "combined_compute.glsl", "compute.glsl"]

with open(output_file, "w") as outfile:
    for file_name in files_to_combine:
        file_path = os.path.join(base_dir, file_name)
        if os.path.isfile(file_path):
            with open(file_path, "r") as infile:
                # Write specific headers based on file type
                if file_name == "vertex.glsl":
                    outfile.write("# Shader Vertex\n# version 430 core\n")
                elif file_name == "fragment.glsl":
                    outfile.write("\n\n# Shader Fragment\n# version 430 core\n")
                elif file_name == "compute.glsl":
                    outfile.write("\n\n# Shader Compute\n# version 430\n")
                # Write the content of each file
                outfile.write(infile.read())
                outfile.write("\n")
        else:
            print(f"File not found: {file_path}")

print(f"Concatenation complete! Output written to {output_file}")
