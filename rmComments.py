import re
import sys
import os
from pathlib import Path

def remove_comments(content, skip_lines=12):
    """
    Remove both single-line and multi-line comments from C code content,
    skipping the specified number of lines at the start.
    Returns the cleaned content as a string.
    """
    # Split content into lines
    lines = content.split('\n')
    
    # Separate the lines to preserve and lines to process
    preserved_lines = lines[:skip_lines]
    lines_to_process = lines[skip_lines:]
    
    # Join the lines to process back into a single string
    content_to_process = '\n'.join(lines_to_process)
    
    # Handle multi-line comments (/* */)
    content_to_process = re.sub(r'/\*[^*]*\*+(?:[^/*][^*]*\*+)*/', '', content_to_process)
    
    # Handle single-line comments (//)
    cleaned_lines = []
    for line in content_to_process.split('\n'):
        line = re.sub(r'//.*$', '', line)
        cleaned_lines.append(line)
    
    # Combine preserved lines with cleaned content
    final_content = '\n'.join(preserved_lines + cleaned_lines)
    
    # Remove extra blank lines (but not in the preserved section)
    preserved_content = '\n'.join(preserved_lines)
    cleaned_content = '\n'.join(cleaned_lines)
    cleaned_content = re.sub(r'\n\s*\n', '\n\n', cleaned_content)
    
    return preserved_content + '\n' + cleaned_content

def process_file(input_path, output_path):
    """
    Process a single C file and save the result.
    """
    try:
        with open(input_path, 'r') as file:
            content = file.read()
        
        cleaned_content = remove_comments(content)
        
        # Create output directory if it doesn't exist
        os.makedirs(os.path.dirname(output_path), exist_ok=True)
        
        with open(output_path, 'w') as file:
            file.write(cleaned_content)
            
        print(f"Processed: {input_path} -> {output_path}")
        return True
        
    except Exception as e:
        print(f"Error processing {input_path}: {str(e)}")
        return False

def process_path(input_path, output_base_path):
    """
    Process either a single file or recursively process a directory.
    """
    input_path = Path(input_path)
    output_base_path = Path(output_base_path)
    
    if not input_path.exists():
        print(f"Error: {input_path} does not exist")
        return
    
    if input_path.is_file():
        if input_path.suffix == '.c':
            output_path = output_base_path
            process_file(input_path, output_path)
    
    elif input_path.is_dir():
        # Walk through directory recursively
        for c_file in input_path.rglob('*.c'):
            # Preserve directory structure in output
            rel_path = c_file.relative_to(input_path)
            output_path = output_base_path / rel_path
            process_file(c_file, output_path)

def main():
    if len(sys.argv) != 3:
        print("Usage:")
        print("  For single file: python script.py input.c output.c")
        print("  For directory:   python script.py input_dir output_dir")
        return
        
    input_path = sys.argv[1]
    output_path = sys.argv[2]
    
    process_path(input_path, output_path)
    print("Processing complete!")

if __name__ == "__main__":
    main()