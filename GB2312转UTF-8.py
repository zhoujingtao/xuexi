import os

def convert_encoding(file_path, from_encoding, to_encoding):
    try:
        with open(file_path, 'r', encoding=from_encoding) as file:
            content = file.read()
        with open(file_path, 'w', encoding=to_encoding) as file:
            file.write(content)
        print(f"Converted {file_path} from {from_encoding} to {to_encoding}")
    except Exception as e:
        print(f"Error converting {file_path}: {e}")

def convert_folder_encoding():
    current_directory = os.getcwd()
    for root, dirs, files in os.walk(current_directory):
        for file in files:
            if file.endswith(('.h', '.c')):
                file_path = os.path.join(root, file)
                with open(file_path, 'rb') as f:
                    content = f.read()
                    try:
                        content = content.decode('gb2312')
                    except UnicodeDecodeError:
                        print(f"Error decoding {file_path} as GB2312")
                        continue
                with open(file_path, 'wb') as f:
                    f.write(content.encode('utf-8'))
                print(f"Converted {file_path} from GB2312 to UTF-8")

convert_folder_encoding()