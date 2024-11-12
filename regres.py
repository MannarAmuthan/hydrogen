import subprocess

try:
    for i in range(0, 1000):
        output = subprocess.check_output(["./main","test.js"])
except subprocess.CalledProcessError as e:
    errorCode = e.returncode
    print(e)
finally:
    print("done")
