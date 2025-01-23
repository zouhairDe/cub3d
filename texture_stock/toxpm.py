import os
from PIL import Image

# Function to convert PNG to XPM
def png_to_xpm(input_file, output_file):
    try:
        # Open the PNG image
        img = Image.open(input_file)

        # Convert to RGBA if not already in that mode
        img = img.convert("RGBA")

        # Get image size and pixel data
        width, height = img.size
        pixels = img.load()

        # Generate the XPM palette (unique colors in the image)
        color_map = {}
        color_count = 0

        # Create the XPM color map (dictionary)
        for y in range(height):
            for x in range(width):
                pixel = pixels[x, y]
                if pixel not in color_map:
                    color_map[pixel] = f'c{color_count}'
                    color_count += 1

        # Create the XPM header
        header = f"/* XPM */\nstatic char *{os.path.splitext(output_file)[0]}[] = {{\n"
        header += f"/* width height num_colors chars_per_pixel */\n"
        header += f"\"{width} {height} {len(color_map)} 1\",\n"

        # Create the color definitions
        for color, symbol in color_map.items():
            r, g, b, a = color
            # Convert RGBA to a hex value
            hex_color = f"#{r:02x}{g:02x}{b:02x}"
            header += f"\"{symbol} c {hex_color}\",\n"

        # Create the pixel data
        pixel_data = []
        for y in range(height):
            row = ""
            for x in range(width):
                pixel = pixels[x, y]
                symbol = color_map[pixel]
                row += symbol
            pixel_data.append(f"\"{row}\",")

        # Combine header and pixel data
        xpm_data = header + "\n".join(pixel_data) + "\n};"

        # Write the XPM data to the output file
        with open(output_file, 'w') as f:
            f.write(xpm_data)

        print(f"Converted {input_file} -> {output_file}")

    except Exception as e:
        print(f"Error processing {input_file}: {e}")

# Create the 'xpm' directory if it doesn't exist
if not os.path.exists('xpm'):
    os.makedirs('xpm')

# Get all files in the current directory
for filename in os.listdir('.'):
    # Check if the file is a PNG (you can add other formats as needed)
    if filename.lower().endswith('.png'):
        # Define the path for the output XPM file
        output_file = os.path.join('xpm', os.path.splitext(filename)[0] + '.xpm')

        # Convert the PNG to XPM
        png_to_xpm(filename, output_file)
