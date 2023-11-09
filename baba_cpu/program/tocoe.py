import sys

def add_comma(input_file, output_file):
    try:
        print("File processing start.")
        with open(input_file, 'r') as f_in, open(output_file, 'w') as f_out:
            str = ""
            f_out.write("memory_initialization_radix=16;\nmemory_initialization_vector=\n")
            for line in f_in:
                line_with_comma = line.rstrip()
                if str != "":
                    f_out.write(str + ',\n')
                str = line_with_comma
            f_out.write(str+';')
        print("File processing complete.")
    except IOError as e:
        print("Error:", e)

if __name__ == '__main__':
    if len(sys.argv) != 3:
        print("Usage: python script.py <input_file> <output_file>")
    else:
        input_file = sys.argv[1]
        output_file = sys.argv[2]
        add_comma(input_file, output_file)