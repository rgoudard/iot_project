import sys
from ftplib import FTP
from os import remove

print(len(sys.argv))
path = sys.argv[1]
if len(sys.argv) >= 3:
    name = sys.argv[2]
else:
    name = "test.JPG"

print(path)

ftp = FTP("HOST")
ftp.login("user", "password")
print("connection OK")
ftp.cwd("path")
print("start upload of " + name)
ftp.storbinary("STOR " + name, open(path, 'rb'))
print("upload OK")
remove(path)
print("temp file deleted")