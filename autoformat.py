import os
print(os.getcwd())
for dirpath, dirnames, filenames in os.walk(os.getcwd()):
    print("当前目录：", dirpath)
    for file in filenames:
        if ".cpp" in file:
            if file[-4:] == ".cpp":
                print(f"Formating:{dirpath}/{file}")
                os.system(f"clang-format --style=file \"{dirpath}\\{file}\" -i")
