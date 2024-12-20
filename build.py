import os
import sys
import shutil
import subprocess
import platform

def clean_and_copy_resources():
  if os.path.exists("build/res"):
    shutil.rmtree("build/res")
  shutil.copytree("res", "build/res")

def run_cmake():
  os.makedirs("build", exist_ok=True)
  os.chdir("build")
  if platform.system() == "Windows":
    subprocess.run(["cmake", "-G", "MinGW Makefiles", "..", "-DCMAKE_C_COMPILER=gcc", "-DCMAKE_EXPORT_COMPILE_COMMANDS=1"])
  else:
    subprocess.run(["cmake", "..", "-DCMAKE_C_COMPILER=gcc", "-DCMAKE_EXPORT_COMPILE_COMMANDS=1"])

def build_project():
  subprocess.run(["cmake", "--build", "."])

def run_executable(args=""):
  executable = "executable.exe" if platform.system() == "Windows" else "./executable"
  subprocess.run([executable] + ([args] if args else []))

def main():
  if len(sys.argv) < 2:
    print("Command keywords: [build, run, test]")
    return
  command = sys.argv[1]
  arg2 = sys.argv[2] if len(sys.argv) > 2 else ""
  arg3 = sys.argv[3] if len(sys.argv) > 3 else ""
  if command == "build" and not arg2:
    clean_and_copy_resources()
    run_cmake()
    build_project()
  elif command == "run" and not arg2:
    os.chdir("build")
    run_executable()
  elif command == "run":
    os.chdir("build")
    run_executable(arg2)
  elif command == "build" and arg2 == "run" and not arg3:
    clean_and_copy_resources()
    run_cmake()
    build_project()
    run_executable()
  elif command == "build" and arg2 == "run":
    clean_and_copy_resources()
    run_cmake()
    build_project()
    run_executable(arg3)
  else:
    print("Command keywords: [build, run]")

if __name__ == "__main__":
  main()

